#include <iostream>
#include <vector>
#include "global.h"
#include <algorithm>

#include "opencl.h"
#include <QImageReader>
#include <QImageWriter>
#include <QtCore>
#include <ppl.h>

#include <chrono>
#define qout qDebug().noquote()

void readImage(const std::string& filename, std::vector<float>& imageFloat, size_t& width, size_t& height)
{
    QImageReader reader(filename.c_str());
    QImage image = reader.read();
    QSize imageSize = image.size();
    width = imageSize.rwidth();
    height = imageSize.rheight();
    std::vector<uchar> vec(image.sizeInBytes());
    std::memcpy(vec.data(), image.constBits(), image.sizeInBytes());
    //    printf("size: %i\n", image.sizeInBytes());
    imageFloat.resize(image.sizeInBytes());
    std::transform(image.constBits(), image.constBits() + imageFloat.size(), imageFloat.data(), //
         [](const uchar& ch) -> float { return static_cast<float>(ch) / 255.f; });
}

void writeImage(const std::string& filename, const std::vector<float>& image, size_t width, size_t height)
{
    std::vector<uchar> buf(image.size());
    std::transform(image.begin(), image.end(), buf.begin(), //
         [](const float& f) -> uchar { return static_cast<uchar>(f * 255.f); });
    QImage img(buf.data(), (int)width, (int)height, QImage::Format_Grayscale8);
    QImageWriter writer(filename.c_str());
    writer.write(img);
}
inline float calcKernel(int xi, int xj, int yi, int yj, float Gx, float Gy, float hx, float hg)
{
    float norm2_xy = (xi - yi) * (xi - yi) + (xj - yj) * (xj - yj);
    float norm2_g = (Gx - Gy) * (Gx - Gy);
    return expf(-0.5f * norm2_xy / (hx * hx)) * expf(-0.5f * norm2_g / (hg * hg));
}

void BilateralFilterCore(float image_filt[],
     const int x,
     const float image[],
     const int width,
     const int height,
     const float hx,
     const float hg)
{
    const int row = x % width, col = x / width;
    const float Gx = image[x];
    const int halfWindowSize = (int)ceilf(3 * hx);

    float sum_kernel = 0;
    float sum_g_kernel = 0;
    /// Loop for neighbors:
    for (int i = (row - halfWindowSize); i <= (row + halfWindowSize); ++i)
    {
        if (i < 0 || i >= width) continue;
        for (int j = (col - halfWindowSize); j <= (col + halfWindowSize); ++j)
        {
            if (j < 0 || j >= (int)height) continue;
            /// Y : neighbors
            const float Gy = image[i + j * width];
            const float kernel = calcKernel(row, col, i, j, Gx, Gy, hx, hg);
            sum_kernel += kernel;
            sum_g_kernel += kernel * Gy;
        }
    }
    image_filt[x] = sum_g_kernel / sum_kernel;
}
std::vector<float> BilateralFilter(const std::vector<float>& image,
     const int width,
     const int height,
     const float hx,
     const float hg)
{
    const int imSize = static_cast<int>(image.size());
    std::vector<float> image_filt(image.size());

    for (int x = 0; x < imSize; ++x)
    {
        BilateralFilterCore(image_filt.data(), x, image.data(), width, height, hx, hg);
    }
    return image_filt;
}

std::vector<float> BilateralFilterCPU(const std::vector<float>& image,
     const int width,
     const int height,
     const float hx,
     const float hg)
{
    const int imSize = static_cast<int>(image.size());
    std::vector<float> image_filt(image.size());
    Concurrency::parallel_for(0, imSize, [&](int x) {
        BilateralFilterCore(image_filt.data(), x, image.data(), width, height, hx, hg);
    });
    return image_filt;
}
int main()
{
    typedef decltype(std::chrono::high_resolution_clock::now()) Time;
    Time t_start, t_end;
    std::vector<float> image_filt;
    printf("hi\n");

    std::vector<float> image;
    size_t width, height;
    readImage("image_noisy.png", image, width, height);
    printf("w: %llu, h: %llu \n", width, height);

    t_start = std::chrono::high_resolution_clock::now();
    image_filt = BilateralFilterCPU(image, (int)width, (int)height, 5.f, 0.1f);
    t_end = std::chrono::high_resolution_clock::now();
    printf("Elapsed time is %0.2f miliseconds\n", (t_end - t_start).count() * 1E-6);

    t_start = std::chrono::high_resolution_clock::now();
    image_filt = BilateralFilter(image, (int)width, (int)height, 5.f, 0.1f);
    t_end = std::chrono::high_resolution_clock::now();
    printf("Elapsed time is %0.2f miliseconds\n", (t_end - t_start).count() * 1E-6);

    writeImage("image_filt.png", image_filt, width, height);
    //    img.scaled(QSize(width, height), Qt::KeepAspectRatio);

    //    writer.write();
    //    //get all platforms (drivers)
    //    std::vector<cl::Platform> all_platforms;
    //    cl::Platform::get(&all_platforms);
    //    if (all_platforms.size() == 0)
    //    {
    //        std::cout << " No platforms found. Check OpenCL installation!\n";
    //        exit(1);
    //    }
    //    cl::Platform default_platform = all_platforms[0];
    //    std::cout << "Using platform: " << default_platform.getInfo<CL_PLATFORM_NAME>() << "\n";

    //    //get default device of the default platform
    //    std::vector<cl::Device> all_devices;
    //    default_platform.getDevices(CL_DEVICE_TYPE_ALL, &all_devices);
    //    if (all_devices.size() == 0)
    //    {
    //        std::cout << " No devices found. Check OpenCL installation!\n";
    //        exit(1);
    //    }
    //    cl::Device default_device = all_devices[0];
    //    std::cout << "Using device: " << default_device.getInfo<CL_DEVICE_NAME>() << "\n";

    //    cl::Context context({default_device});

    //    cl::Program::Sources sources;

    //    // kernel calculates for each element C=A+B
    //    std::string kernel_code = io::readTextFile("kernel.cl");
    //    std::cout << kernel_code << std::endl;
    //    sources.push_back({kernel_code.c_str(), kernel_code.length()});

    //    cl::Program program(context, sources);
    //    auto err = program.build("-cl-std=CL1.2");
    //    std::clog << "Status: " << (CL_ERROR_TO_STRING[err]) << " " << std::endl;
    //    //    auto err = program.build({default_device});
    //    if (err != CL_SUCCESS)
    //    {
    //        std::cerr << " Error building: " << program.getBuildInfo<CL_PROGRAM_BUILD_LOG>(default_device) << "\n";
    //        exit(1);
    //    }

    //    // create buffers on the device
    //    cl::Buffer buffer_A(context, CL_MEM_READ_WRITE, sizeof(int) * 10);
    //    cl::Buffer buffer_B(context, CL_MEM_READ_WRITE, sizeof(int) * 10);
    //    cl::Buffer buffer_C(context, CL_MEM_READ_WRITE, sizeof(int) * 10);

    //    int A[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    //    int B[] = {0, 1, 2, 0, 1, 2, 0, 1, 2, 0};

    //    //create queue to which we will push commands for the device.
    //    cl::CommandQueue queue(context, default_device);

    //    //write arrays A and B to the device
    //    queue.enqueueWriteBuffer(buffer_A, CL_TRUE, 0, sizeof(int) * 10, A);
    //    queue.enqueueWriteBuffer(buffer_B, CL_TRUE, 0, sizeof(int) * 10, B);

    //    //run the kernel
    //    //alternative way to run the kernel
    //    cl::Kernel kernel_add = cl::Kernel(program, "simple_add");
    //    kernel_add.setArg(0, buffer_A);
    //    kernel_add.setArg(1, buffer_B);
    //    kernel_add.setArg(2, buffer_C);
    //    queue.enqueueNDRangeKernel(kernel_add, cl::NullRange, cl::NDRange(100), cl::NDRange(5));
    //    queue.finish();

    //    int C[10];
    //    //read result C from the device to array C
    //    queue.enqueueReadBuffer(buffer_C, CL_TRUE, 0, sizeof(int) * 10, C);

    //    std::cout << " result: \n";
    //    for (int i = 0; i < 10; i++)
    //    {
    //        std::cout << C[i] << " ";
    //    }
    //    std::cout << std::endl;
    return 0;
}

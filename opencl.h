#ifndef OPENCL_H
#define OPENCL_H

#define CL_USE_DEPRECATED_OPENCL_2_0_APIS
#ifdef __APPLE__
#include <OpenCL/opencl.h>
#else
#include <CL/cl.hpp>
#endif

#include <map>
#include <string>
typedef int CL_ERROR;
#define OPENCL_ERROR_TO_STRING_PAIR(err) std::make_pair(err, (#err))
/* Error Codes */
std::map<CL_ERROR, std::string> CL_ERROR_TO_STRING{
     OPENCL_ERROR_TO_STRING_PAIR(CL_SUCCESS),
     OPENCL_ERROR_TO_STRING_PAIR(CL_DEVICE_NOT_FOUND),
     OPENCL_ERROR_TO_STRING_PAIR(CL_DEVICE_NOT_AVAILABLE),
     OPENCL_ERROR_TO_STRING_PAIR(CL_COMPILER_NOT_AVAILABLE),
     OPENCL_ERROR_TO_STRING_PAIR(CL_MEM_OBJECT_ALLOCATION_FAILURE),
     OPENCL_ERROR_TO_STRING_PAIR(CL_OUT_OF_RESOURCES),
     OPENCL_ERROR_TO_STRING_PAIR(CL_OUT_OF_HOST_MEMORY),
     OPENCL_ERROR_TO_STRING_PAIR(CL_PROFILING_INFO_NOT_AVAILABLE),
     OPENCL_ERROR_TO_STRING_PAIR(CL_MEM_COPY_OVERLAP),
     OPENCL_ERROR_TO_STRING_PAIR(CL_IMAGE_FORMAT_MISMATCH),
     OPENCL_ERROR_TO_STRING_PAIR(CL_IMAGE_FORMAT_NOT_SUPPORTED),
     OPENCL_ERROR_TO_STRING_PAIR(CL_BUILD_PROGRAM_FAILURE),
     OPENCL_ERROR_TO_STRING_PAIR(CL_MAP_FAILURE),
     OPENCL_ERROR_TO_STRING_PAIR(CL_MISALIGNED_SUB_BUFFER_OFFSET),
     OPENCL_ERROR_TO_STRING_PAIR(CL_EXEC_STATUS_ERROR_FOR_EVENTS_IN_WAIT_LIST),
     OPENCL_ERROR_TO_STRING_PAIR(CL_COMPILE_PROGRAM_FAILURE),
     OPENCL_ERROR_TO_STRING_PAIR(CL_LINKER_NOT_AVAILABLE),
     OPENCL_ERROR_TO_STRING_PAIR(CL_LINK_PROGRAM_FAILURE),
     OPENCL_ERROR_TO_STRING_PAIR(CL_DEVICE_PARTITION_FAILED),
     OPENCL_ERROR_TO_STRING_PAIR(CL_KERNEL_ARG_INFO_NOT_AVAILABLE),
     OPENCL_ERROR_TO_STRING_PAIR(CL_INVALID_VALUE),
     OPENCL_ERROR_TO_STRING_PAIR(CL_INVALID_DEVICE_TYPE),
     OPENCL_ERROR_TO_STRING_PAIR(CL_INVALID_PLATFORM),
     OPENCL_ERROR_TO_STRING_PAIR(CL_INVALID_DEVICE),
     OPENCL_ERROR_TO_STRING_PAIR(CL_INVALID_CONTEXT),
     OPENCL_ERROR_TO_STRING_PAIR(CL_INVALID_QUEUE_PROPERTIES),
     OPENCL_ERROR_TO_STRING_PAIR(CL_INVALID_COMMAND_QUEUE),
     OPENCL_ERROR_TO_STRING_PAIR(CL_INVALID_HOST_PTR),
     OPENCL_ERROR_TO_STRING_PAIR(CL_INVALID_MEM_OBJECT),
     OPENCL_ERROR_TO_STRING_PAIR(CL_INVALID_IMAGE_FORMAT_DESCRIPTOR),
     OPENCL_ERROR_TO_STRING_PAIR(CL_INVALID_IMAGE_SIZE),
     OPENCL_ERROR_TO_STRING_PAIR(CL_INVALID_SAMPLER),
     OPENCL_ERROR_TO_STRING_PAIR(CL_INVALID_BINARY),
     OPENCL_ERROR_TO_STRING_PAIR(CL_INVALID_BUILD_OPTIONS),
     OPENCL_ERROR_TO_STRING_PAIR(CL_INVALID_PROGRAM),
     OPENCL_ERROR_TO_STRING_PAIR(CL_INVALID_PROGRAM_EXECUTABLE),
     OPENCL_ERROR_TO_STRING_PAIR(CL_INVALID_KERNEL_NAME),
     OPENCL_ERROR_TO_STRING_PAIR(CL_INVALID_KERNEL_DEFINITION),
     OPENCL_ERROR_TO_STRING_PAIR(CL_INVALID_KERNEL),
     OPENCL_ERROR_TO_STRING_PAIR(CL_INVALID_ARG_INDEX),
     OPENCL_ERROR_TO_STRING_PAIR(CL_INVALID_ARG_VALUE),
     OPENCL_ERROR_TO_STRING_PAIR(CL_INVALID_ARG_SIZE),
     OPENCL_ERROR_TO_STRING_PAIR(CL_INVALID_KERNEL_ARGS),
     OPENCL_ERROR_TO_STRING_PAIR(CL_INVALID_WORK_DIMENSION),
     OPENCL_ERROR_TO_STRING_PAIR(CL_INVALID_WORK_GROUP_SIZE),
     OPENCL_ERROR_TO_STRING_PAIR(CL_INVALID_WORK_ITEM_SIZE),
     OPENCL_ERROR_TO_STRING_PAIR(CL_INVALID_GLOBAL_OFFSET),
     OPENCL_ERROR_TO_STRING_PAIR(CL_INVALID_EVENT_WAIT_LIST),
     OPENCL_ERROR_TO_STRING_PAIR(CL_INVALID_EVENT),
     OPENCL_ERROR_TO_STRING_PAIR(CL_INVALID_OPERATION),
     OPENCL_ERROR_TO_STRING_PAIR(CL_INVALID_GL_OBJECT),
     OPENCL_ERROR_TO_STRING_PAIR(CL_INVALID_BUFFER_SIZE),
     OPENCL_ERROR_TO_STRING_PAIR(CL_INVALID_MIP_LEVEL),
     OPENCL_ERROR_TO_STRING_PAIR(CL_INVALID_GLOBAL_WORK_SIZE),
     OPENCL_ERROR_TO_STRING_PAIR(CL_INVALID_PROPERTY),
     OPENCL_ERROR_TO_STRING_PAIR(CL_INVALID_IMAGE_DESCRIPTOR),
     OPENCL_ERROR_TO_STRING_PAIR(CL_INVALID_COMPILER_OPTIONS),
     OPENCL_ERROR_TO_STRING_PAIR(CL_INVALID_LINKER_OPTIONS),
     OPENCL_ERROR_TO_STRING_PAIR(CL_INVALID_DEVICE_PARTITION_COUNT),
     OPENCL_ERROR_TO_STRING_PAIR(CL_INVALID_PIPE_SIZE),
     OPENCL_ERROR_TO_STRING_PAIR(CL_INVALID_DEVICE_QUEUE),
};

#endif // OPENCL_H

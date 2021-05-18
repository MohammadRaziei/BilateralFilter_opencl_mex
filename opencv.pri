INCLUDEPATH += "D:\Packages\opencv\build\include"
#LIBS += "D:\Packages\opencv\build\x64\vc15\lib\opencv_world452.lib"
LIBS += "D:\Packages\opencv\build\x64\vc15\lib\opencv_world452d.lib"
#LIBS += "D:\Packages\opencv\build\x64\vc15\bin\opencv_world452.dll" \
#        "D:\Packages\opencv\build\x64\vc15\bin\opencv_videoio_msmf452_64.dll" \
#        "D:\Packages\opencv\build\x64\vc15\bin\opencv_videoio_ffmpeg452_64.dll" \



debug: {
        LIBS += -LD:\Packages\opencv\build\x64\vc15\lib\ -lopencv_world452d
}

release: {
        LIBS += -LD:\Packages\opencv\build\x64\vc15\lib\ -lopencv_world452
}

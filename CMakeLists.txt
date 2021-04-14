cmake_minimum_required(VERSION 3.5)

project(the_akkadian CXX C)


#SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -pthread")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

#set(Boost_USE_STATIC_LIBS OFF) 
#set(Boost_USE_MULTITHREADED ON)  
#set(Boost_USE_STATIC_RUNTIME OFF) 
#find_package( Boost REQUIRED ) 
#find_package( OpenCV REQUIRED )

set(CMAKE_CXX_FLAGS  "-O3")

set(WITH_OPENEXR  "OFF")

add_subdirectory(cpp-properties)
add_subdirectory(opencv)
add_subdirectory(tesseract)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(CTest)

#set(CMAKE_SHARED_LINKER_FLAGS "-Wl,--export-all-symbols")

#Rewiring some includes from opencv
include_directories( ${PROJECT_SOURCE_DIR}/include include opencv/include tesseract/include/tesseract cpp-properties/include)
include_directories( ${PROJECT_SOURCE_DIR}/opencv/include ${PROJECT_SOURCE_DIR}/opencv/include/opencv2)
include_directories( ${PROJECT_SOURCE_DIR}/opencv/modules/core/include/opencv2 ${PROJECT_SOURCE_DIR}/opencv/modules/core/include)
include_directories( ${PROJECT_SOURCE_DIR}/opencv/modules/core/include/opencv2/core)
include_directories( ${PROJECT_SOURCE_DIR}/opencv/modules/highgui/include/opencv2 ${PROJECT_SOURCE_DIR}/opencv/modules/highgui/include)
include_directories( ${PROJECT_SOURCE_DIR}/opencv/modules/features2d/include/opencv2 ${PROJECT_SOURCE_DIR}/opencv/modules/features2d/include)
include_directories( ${PROJECT_SOURCE_DIR}/opencv/modules/imgproc/include/opencv2 ${PROJECT_SOURCE_DIR}/opencv/modules/imgproc/include)
include_directories( ${PROJECT_SOURCE_DIR}/opencv/modules/imgcodecs/include/opencv2 ${PROJECT_SOURCE_DIR}/opencv/modules/imgcodecs/include)
include_directories( ${PROJECT_SOURCE_DIR}/opencv/modules/ml/include/opencv2 ${PROJECT_SOURCE_DIR}/opencv/modules/ml/include)
include_directories( ${PROJECT_SOURCE_DIR}/opencv/modules/objdetect/include/opencv2 ${PROJECT_SOURCE_DIR}/opencv/modules/objdetect/include)
include_directories( ${PROJECT_SOURCE_DIR}/opencv/modules/photo/include/opencv2 ${PROJECT_SOURCE_DIR}/opencv/modules/photo/include)
include_directories( ${PROJECT_SOURCE_DIR}/opencv/modules/stitching/include/opencv2 ${PROJECT_SOURCE_DIR}/opencv/modules/stitching/include)
include_directories( ${PROJECT_SOURCE_DIR}/opencv/modules/video/include/opencv2 ${PROJECT_SOURCE_DIR}/opencv/modules/video/include)
include_directories( ${PROJECT_SOURCE_DIR}/opencv/modules/videoio/include/opencv2 ${PROJECT_SOURCE_DIR}/opencv/modules/videoio/include)
include_directories( ${PROJECT_SOURCE_DIR}/opencv/modules/dnn/include/opencv2 ${PROJECT_SOURCE_DIR}/opencv/modules/dnn/include)
include_directories( ${PROJECT_SOURCE_DIR}/opencv/modules/flann/include/opencv2 ${PROJECT_SOURCE_DIR}/opencv/modules/flann/include)
include_directories( ${PROJECT_SOURCE_DIR}/opencv/modules/calib3d/include/opencv2 ${PROJECT_SOURCE_DIR}/opencv/modules/calib3d/include)

#Integration of WiringPi
include_directories( ${PROJECT_SOURCE_DIR}/WiringPi ${PROJECT_SOURCE_DIR}/WiringPi/wiringPi ${PROJECT_SOURCE_DIR}/WiringPi/devLib)

#Integration of picotts
include_directories( ${PROJECT_SOURCE_DIR}/picotts/pico/lib)

add_executable(the_akkadian
    src/Main.cpp
    src/CameraHandler.cpp
    src/AkkadianService.cpp
    src/SerialService.cpp
    src/GpioService.cpp
    src/ImageWriter.cpp
    src/TextLocatorService.cpp


    WiringPi/wiringPi/wiringPiI2C.c
    WiringPi/wiringPi/mcp23017.c
    WiringPi/wiringPi/bmp180.c
    WiringPi/wiringPi/drcSerial.c
    WiringPi/wiringPi/drcNet.c
    WiringPi/wiringPi/softServo.c
    WiringPi/wiringPi/pcf8574.c
    WiringPi/wiringPi/ads1115.c
    WiringPi/wiringPi/mcp23016.c
    WiringPi/wiringPi/max31855.c
    WiringPi/wiringPi/wpiExtensions.c
    WiringPi/wiringPi/mcp23008.c
    WiringPi/wiringPi/mcp3002.c
    WiringPi/wiringPi/wiringPi.c
    WiringPi/wiringPi/sn3218.c
    WiringPi/wiringPi/piThread.c
    WiringPi/wiringPi/mcp3422.c
    WiringPi/wiringPi/mcp23s08.c
    WiringPi/wiringPi/mcp4802.c
    WiringPi/wiringPi/softPwm.c
    WiringPi/wiringPi/mcp23s17.c
    WiringPi/wiringPi/sr595.c
    WiringPi/wiringPi/htu21d.c
    WiringPi/wiringPi/wiringShift.c
    WiringPi/wiringPi/max5322.c
    WiringPi/wiringPi/softTone.c
    WiringPi/wiringPi/pcf8591.c
    WiringPi/wiringPi/piHiPri.c
    WiringPi/wiringPi/mcp3004.c
    WiringPi/wiringPi/wiringSerial.c
    WiringPi/wiringPi/rht03.c
    WiringPi/wiringPi/ds18b20.c
    WiringPi/wiringPi/wiringPiSPI.c
    WiringPi/wiringPi/pseudoPins.c

    picotts/pico/lib/picoktab.c
    picotts/pico/lib/picosa.c
    picotts/pico/lib/picokpdf.c
    picotts/pico/lib/picokpr.c
    picotts/pico/lib/picoapi.c
    picotts/pico/lib/picosig2.c
    picotts/pico/lib/picodata.c
    picotts/pico/lib/picopam.c
    picotts/pico/lib/picowa.c
    picotts/pico/lib/picokfst.c
    picotts/pico/lib/picopr.c
    picotts/pico/lib/picoknow.c
    picotts/pico/lib/picokdt.c
    picotts/pico/lib/picoklex.c
    picotts/pico/lib/picorsrc.c
    picotts/pico/lib/picoctrl.c
    picotts/pico/lib/picoextapi.c
    picotts/pico/lib/picobase.c
    picotts/pico/lib/picosig.c
    picotts/pico/lib/picoos.c
    picotts/pico/lib/picokdbg.c
    picotts/pico/lib/picodbg.c
    picotts/pico/lib/picocep.c
    picotts/pico/lib/picotok.c
    picotts/pico/lib/picofftsg.c
    picotts/pico/lib/picotrns.c
    picotts/pico/lib/picoacph.c
    picotts/pico/lib/picopal.c
    picotts/pico/lib/picospho.c
   
    )

#set(LINK_FLAGS ${LINK_FLAGS} "-Wl,-whole-archive")

    configure_file(data/text_detection/frozen_east_text_detection.pb bin/frozen_east_text_detection.pb COPYONLY)
    configure_file(data/text_recognition/CRNN_VGG_BiLSTM_CTC_float16.onnx bin/CRNN_VGG_BiLSTM_CTC_float16.onnx COPYONLY)
    configure_file(data/text_recognition/CRNN_VGG_BiLSTM_CTC.onnx bin/CRNN_VGG_BiLSTM_CTC.onnx COPYONLY)
    configure_file(data/text_recognition/DenseNet_BiLSTM_CTC.onnx bin/DenseNet_BiLSTM_CTC.onnx COPYONLY)
    configure_file(data/text_recognition/DenseNet_CTC.onnx bin/DenseNet_CTC.onnx COPYONLY)
    configure_file(data/text_recognition/ResNet_CTC.onnx bin/ResNet_CTC.onnx COPYONLY)
    configure_file(data/text_recognition/VGG_CTC_float16.onnx bin/VGG_CTC_float16.onnx COPYONLY)
    configure_file(data/text_recognition/VGG_CTC.onnx bin/VGG_CTC.onnx COPYONLY)

target_link_libraries( the_akkadian opencv_core opencv_features2d opencv_videoio crypt pthread libtesseract rt m)






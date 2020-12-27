cmake_minimum_required(VERSION 3.5)

project(the_akkadian CXX C)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
#include_directories(PUBLIC ${PROJECT_SOURCE_DIR}/src)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -pthread")

#set(Boost_USE_STATIC_LIBS OFF) 
#set(Boost_USE_MULTITHREADED ON)  
#set(Boost_USE_STATIC_RUNTIME OFF) 
#find_package( Boost REQUIRED ) 
#find_package( OpenCV REQUIRED )



include(CTest)

add_subdirectory(cpp-properties)
add_subdirectory(opencv)
add_subdirectory(tesseract)
#add_subdirectory(WiringPi)

#Rewiring some includes
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


include_directories( ${PROJECT_SOURCE_DIR}/WiringPi ${PROJECT_SOURCE_DIR}/WiringPi/WiringPi ${PROJECT_SOURCE_DIR}/WiringPi/WiringPiD ${PROJECT_SOURCE_DIR}/WiringPi/devLib)

add_executable(the_akkadian
    src/Main.cpp
    src/CameraHandler.cpp
    src/AkkadianService.cpp
    src/SerialService.cpp
    src/GpioService.cpp
    src/ImageWriter.cpp
    src/EastTextLocatorService.cpp

    WiringPi/devLib/piFaceOld.c
    WiringPi/devLib/piGlow.c
    WiringPi/devLib/maxdetect.c
    WiringPi/devLib/piFace.c
    WiringPi/devLib/piNes.c
    WiringPi/devLib/lcd128x64.c
    WiringPi/devLib/gertboard.c
    WiringPi/devLib/scrollPhat.c
    WiringPi/devLib/ds1302.c
    WiringPi/devLib/lcd.c
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
    WiringPi/gpio/readall.c
    WiringPi/gpio/gpio.c
    WiringPi/wiringPiD/wiringpid.c
    WiringPi/wiringPiD/network.c
    WiringPi/wiringPiD/daemonise.c
    WiringPi/wiringPiD/runRemote.c
    


    )

target_link_libraries( the_akkadian )






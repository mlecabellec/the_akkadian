cmake_minimum_required(VERSION 3.5)

project(the_akkadian CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
#include_directories(PUBLIC ${PROJECT_SOURCE_DIR}/src)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -pthread")

set(Boost_USE_STATIC_LIBS OFF) 
set(Boost_USE_MULTITHREADED ON)  
set(Boost_USE_STATIC_RUNTIME OFF) 
find_package(Boost REQUIRED ) 
find_package( OpenCV REQUIRED )

include(CTest)

include_directories( ${PROJECT_SOURCE_DIR}/include ${OpenCV_INCLUDE_DIRS} ${Boost_INCLUDE_DIRS})
add_executable(the_akkadian
    src/Main.cpp
    src/CameraHandler.cpp
    src/AkkadianService.cpp
    src/SerialService.cpp
    src/GpioService.cpp
    src/ImageWriter.cpp
    )

target_link_libraries( the_akkadian ${OpenCV_LIBS} ${Boost_LIBS} wiringPi)

add_test(the_akkadian-test001 the_akkadian)





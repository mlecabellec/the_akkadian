/*
 * Configuration.hpp
 *
 *  Created on: 16 oct. 2020
 *      Author: vortigern
 */

#ifndef CONFIGURATION_H_
#define CONFIGURATION_H_

#include <thread>
#include <mutex>
#include <string>
#include <cstdint>

#include <opencv2/opencv.hpp>
#include <iostream>
#include "AkkadianService.hpp"
#include <list>
#include <chrono>

namespace akkadian
{

    using namespace std;
    using namespace cv;

    enum Game2020SideEnum : uint8_t
    {
        SIDE_UNKNOWN = 0x00,
        SIDE_YELLOW = 0x01,
        SIDE_BLUE = 0x02
    };

    enum SimpleColor : uint8_t
    {
        COLOR_UNKNOWN = 0x00,
        COLOR_BLUE = 0x01,
        COLOR_YELLOW = 0x02,
        COLOR_GREEN = 0x03,
        COLOR_RED = 0x04,
        COLOR_BLACK = 0x05,
        COLOR_WHITE = 0x06
    };

    enum Game2020CameraPosition : uint8_t
    {
        POSITION_UNKNOWN = 0x00,
        POSITION_YELLOW_SIDE = 0x01,
        POSITION_BLUE_SIDE = 0x02,
        POSITION_CENTER = 0x03
    };

    class Game2020CameraConfiguration
    {
    public:
        Game2020CameraConfiguration(std::string cameraDevice,
                                    int height,
                                    int width,
                                    Game2020CameraPosition position)
        {
            this->_cameraDevice = cameraDevice;
            this->_height = height;
            this->_width = width;
            this->_position = position;
        };

        ~Game2020CameraConfiguration()
        {
        }

        std::string _cameraDevice;
        int _height;
        int _width;
        Game2020CameraPosition _position;
    };

    class SimpleRect
    {
    public:
        SimpleRect(int x, int y, int width, int height)
        {
            this->_x = x;
            this->_y = y;
            this->_width = width;
            this->_height = height;
        };
        ~SimpleRect(){

        };

        int _x, _y, _width, _height;
    };

    class SimpleRectZone
    {
    public:
        SimpleRectZone(std::string name, int x, int y, int width, int height)
        {
            this->_name = name;
            this->_x = x;
            this->_y = y;
            this->_width = width;
            this->_height = height;
        };
        ~SimpleRectZone(){

        };
        std::string _name;
        int _x, _y, _width, _height;
    };

    class SimpleRectZoneInCamera
    {
    public:


        SimpleRectZoneInCamera(Game2020CameraPosition cameraPosition, std::string zoneName, int rank, int x, int y, int width, int height)
        {
            this->_cameraPosition = cameraPosition;
            this->_zoneName = zoneName;
            this->_rank = rank;
            this->_x = x;
            this->_y = y;
            this->_width = width;
            this->_height = height;
        };
        ~SimpleRectZoneInCamera(){

        };
        Game2020CameraPosition _cameraPosition;
        std::string _zoneName;
        int _rank, _x, _y, _width, _height;
    };

    class SerialConfiguration
    {
    public:
        SerialConfiguration(std::string device)
        {
            this->_device = device;
        };
        ~SerialConfiguration(){

        };

        std::string _device;
    };

    /*
    const std::map<std::string, Game2020CameraConfiguration> CONFIG_CAMERAS = {
        {"POSITION_BLUE_SIDE", Game2020CameraConfiguration("/dev/video0", 0, 0, Game2020CameraPosition::POSITION_BLUE_SIDE)},
        {"POSITION_YELLOW_SIDE", Game2020CameraConfiguration("/dev/video0", 0, 0, Game2020CameraPosition::POSITION_YELLOW_SIDE)},
        {"POSITION_CENTER", Game2020CameraConfiguration("/dev/video0", 0, 0, Game2020CameraPosition::POSITION_CENTER)}};
    */

    const std::map<std::string, Game2020CameraConfiguration> CONFIG_CAMERAS = {
        {"POSITION_BLUE_SIDE", Game2020CameraConfiguration("/dev/video2", 1280, 1024, Game2020CameraPosition::POSITION_BLUE_SIDE)},
        {"POSITION_YELLOW_SIDE", Game2020CameraConfiguration("/dev/video0", 1280, 1024, Game2020CameraPosition::POSITION_YELLOW_SIDE)},
        {"POSITION_CENTER", Game2020CameraConfiguration("/dev/video4", 800, 600, Game2020CameraPosition::POSITION_CENTER)}};

    const std::map<std::string , SimpleRectZoneInCamera> CONFIG_CAMZONES = {
        // Pour constructeur de zone: caméra, index zone, x , y , largeur, hauteur
        {"weatherVaneFromBlueSide",SimpleRectZoneInCamera(Game2020CameraPosition::POSITION_BLUE_SIDE, "weatherVaneFromBlueSide",        0,  0,      725,    470,    110)},
        {"weatherVaneFromYellowSide",SimpleRectZoneInCamera(Game2020CameraPosition::POSITION_YELLOW_SIDE, "weatherVaneFromYellowSide",  0,  750,    725,    470,    110)},

        {"centerCameraFullZone",SimpleRectZoneInCamera(Game2020CameraPosition::POSITION_CENTER, "centerCameraFullZone", 0, 0, 0, 800, 600)},
        {"yellowCameraFullZone",SimpleRectZoneInCamera(Game2020CameraPosition::POSITION_YELLOW_SIDE, "yellowCameraFullZone", 0, 0, 0, 1280, 1024)},
        {"blueCameraFullZone",SimpleRectZoneInCamera(Game2020CameraPosition::POSITION_BLUE_SIDE, "blueCameraFullZone", 0, 0, 0, 1280, 1024)},

        {"groundedBuoyAtYellowSideBand",SimpleRectZoneInCamera(Game2020CameraPosition::POSITION_YELLOW_SIDE, "groundedBuoyAtYellowSideBand", 0, 100, 870, 1050, 30)},
        {"groundedBuoyAtBlueSideBand",SimpleRectZoneInCamera(Game2020CameraPosition::POSITION_BLUE_SIDE, "groundedBuoyAtBlueSideBand", 0, 100, 870, 1050, 30)},

        {"groundedBuoyAtYellowSide0",SimpleRectZoneInCamera(Game2020CameraPosition::POSITION_YELLOW_SIDE, "groundedBuoyAtYellowSide", 0, 0, 0, 64, 64)},
        {"groundedBuoyAtYellowSide1",SimpleRectZoneInCamera(Game2020CameraPosition::POSITION_YELLOW_SIDE, "groundedBuoyAtYellowSide", 1, 0, 0, 64, 64)},
        {"groundedBuoyAtYellowSide2",SimpleRectZoneInCamera(Game2020CameraPosition::POSITION_YELLOW_SIDE, "groundedBuoyAtYellowSide", 2, 0, 0, 64, 64)},
        {"groundedBuoyAtYellowSide3",SimpleRectZoneInCamera(Game2020CameraPosition::POSITION_YELLOW_SIDE, "groundedBuoyAtYellowSide", 3, 0, 0, 64, 64)},
        {"groundedBuoyAtYellowSide4",SimpleRectZoneInCamera(Game2020CameraPosition::POSITION_YELLOW_SIDE, "groundedBuoyAtYellowSide", 4, 0, 0, 64, 64)},
        {"groundedBuoyAtYellowSide5",SimpleRectZoneInCamera(Game2020CameraPosition::POSITION_YELLOW_SIDE, "groundedBuoyAtYellowSide", 5, 0, 0, 64, 64)},
        {"groundedBuoyAtYellowSide6",SimpleRectZoneInCamera(Game2020CameraPosition::POSITION_YELLOW_SIDE, "groundedBuoyAtYellowSide", 6, 0, 0, 64, 64)},
        {"groundedBuoyAtYellowSide7",SimpleRectZoneInCamera(Game2020CameraPosition::POSITION_YELLOW_SIDE, "groundedBuoyAtYellowSide", 7, 0, 0, 64, 64)},
        {"groundedBuoyAtYellowSide8",SimpleRectZoneInCamera(Game2020CameraPosition::POSITION_YELLOW_SIDE, "groundedBuoyAtYellowSide", 8, 0, 0, 64, 64)},
        {"groundedBuoyAtYellowSide9",SimpleRectZoneInCamera(Game2020CameraPosition::POSITION_YELLOW_SIDE, "groundedBuoyAtYellowSide", 9, 0, 0, 64, 64)},
        {"groundedBuoyAtYellowSide10",SimpleRectZoneInCamera(Game2020CameraPosition::POSITION_YELLOW_SIDE, "groundedBuoyAtYellowSide", 10, 0, 0, 64, 64)},
        {"groundedBuoyAtYellowSide11",SimpleRectZoneInCamera(Game2020CameraPosition::POSITION_YELLOW_SIDE, "groundedBuoyAtYellowSide", 11, 0, 0, 64, 64)},
        {"groundedBuoyAtYellowSide12",SimpleRectZoneInCamera(Game2020CameraPosition::POSITION_YELLOW_SIDE, "groundedBuoyAtYellowSide", 12, 0, 0, 64, 64)},
        {"groundedBuoyAtYellowSide13",SimpleRectZoneInCamera(Game2020CameraPosition::POSITION_YELLOW_SIDE, "groundedBuoyAtYellowSide", 13, 0, 0, 64, 64)},
        {"groundedBuoyAtYellowSide14",SimpleRectZoneInCamera(Game2020CameraPosition::POSITION_YELLOW_SIDE, "groundedBuoyAtYellowSide", 14, 0, 0, 64, 64)},
        {"groundedBuoyAtYellowSide15",SimpleRectZoneInCamera(Game2020CameraPosition::POSITION_YELLOW_SIDE, "groundedBuoyAtYellowSide", 15, 0, 0, 64, 64)},

        {"groundedBuoyAtBlueSide0",SimpleRectZoneInCamera(Game2020CameraPosition::POSITION_BLUE_SIDE, "groundedBuoyAtBlueSide", 0, 0, 0, 64, 64)},
        {"groundedBuoyAtBlueSide1",SimpleRectZoneInCamera(Game2020CameraPosition::POSITION_BLUE_SIDE, "groundedBuoyAtBlueSide", 1, 0, 0, 64, 64)},
        {"groundedBuoyAtBlueSide2",SimpleRectZoneInCamera(Game2020CameraPosition::POSITION_BLUE_SIDE, "groundedBuoyAtBlueSide", 2, 0, 0, 64, 64)},
        {"groundedBuoyAtBlueSide3",SimpleRectZoneInCamera(Game2020CameraPosition::POSITION_BLUE_SIDE, "groundedBuoyAtBlueSide", 3, 0, 0, 64, 64)},
        {"groundedBuoyAtBlueSide4",SimpleRectZoneInCamera(Game2020CameraPosition::POSITION_BLUE_SIDE, "groundedBuoyAtBlueSide", 4, 0, 0, 64, 64)},
        {"groundedBuoyAtBlueSide5",SimpleRectZoneInCamera(Game2020CameraPosition::POSITION_BLUE_SIDE, "groundedBuoyAtBlueSide", 5, 0, 0, 64, 64)},
        {"groundedBuoyAtBlueSide6",SimpleRectZoneInCamera(Game2020CameraPosition::POSITION_BLUE_SIDE, "groundedBuoyAtBlueSide", 6, 0, 0, 64, 64)},
        {"groundedBuoyAtBlueSide7",SimpleRectZoneInCamera(Game2020CameraPosition::POSITION_BLUE_SIDE, "groundedBuoyAtBlueSide", 7, 0, 0, 64, 64)},
        {"groundedBuoyAtBlueSide8",SimpleRectZoneInCamera(Game2020CameraPosition::POSITION_BLUE_SIDE, "groundedBuoyAtBlueSide", 8, 0, 0, 64, 64)},
        {"groundedBuoyAtBlueSide9",SimpleRectZoneInCamera(Game2020CameraPosition::POSITION_BLUE_SIDE, "groundedBuoyAtBlueSide", 9, 0, 0, 64, 64)},
        {"groundedBuoyAtBlueSide10",SimpleRectZoneInCamera(Game2020CameraPosition::POSITION_BLUE_SIDE, "groundedBuoyAtBlueSide", 10, 0, 0, 64, 64)},
        {"groundedBuoyAtBlueSide11",SimpleRectZoneInCamera(Game2020CameraPosition::POSITION_BLUE_SIDE, "groundedBuoyAtBlueSide", 11, 0, 0, 64, 64)},
        {"groundedBuoyAtBlueSide12",SimpleRectZoneInCamera(Game2020CameraPosition::POSITION_BLUE_SIDE, "groundedBuoyAtBlueSide", 12, 0, 0, 64, 64)},
        {"groundedBuoyAtBlueSide13",SimpleRectZoneInCamera(Game2020CameraPosition::POSITION_BLUE_SIDE, "groundedBuoyAtBlueSide", 13, 0, 0, 64, 64)},
        {"groundedBuoyAtBlueSide14",SimpleRectZoneInCamera(Game2020CameraPosition::POSITION_BLUE_SIDE, "groundedBuoyAtBlueSide", 14, 0, 0, 64, 64)},
        {"groundedBuoyAtBlueSide15",SimpleRectZoneInCamera(Game2020CameraPosition::POSITION_BLUE_SIDE, "groundedBuoyAtBlueSide", 15, 0, 0, 64, 64)}};

    const std::string CONFIG_MAIN_SERIAL_PORT = std::string("/dev/ttyS0");

} /* namespace akkadian */

#endif /* FRAMEHANDLER_H_ */

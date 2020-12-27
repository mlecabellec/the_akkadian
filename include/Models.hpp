/*
 * Configuration.hpp
 *
 *  Created on: 16 oct. 2020
 *      Author: vortigern
 */

#ifndef MODELS_H_
#define MODELS_H_

#include <thread>
#include <mutex>
#include <string>
#include <cstdint>

#include "opencv.hpp"
#include <iostream>
#include "AkkadianService.hpp"
#include <list>
#include <chrono>

namespace akkadian
{

    using namespace std;
    using namespace cv;

    //-------------------------------------------------------

    enum Game2020WeatherVanePositionENum : uint8_t
    {
        WEATHERVANE_POSITION_UNKNOWN = 0x00,
        WEATHERVANE_POSITION_BLACK_UPSIDE_NORTH = 0x01,
        WEATHERVANE_POSITION_WHITE_UPSIDE_SOUTH = 0x02,
    };

    class Game2020WeatherVanePosition
    {
    public:
        Game2020WeatherVanePositionENum _weatherVanePosition;
    };

    //-------------------------------------------------------

    enum Game2020AkkadianPositionENum : uint8_t
    {
        AKKADIAN_POSITION_UNKNOWN = 0x00,
        AKKADIAN_POSITION_YELLOW_SIDE = 0x01,
        AKKADIAN_POSITION_BLUE_SIDE = 0x02,
    };

    class Game2020AkkadianPosition
    {
    public:
        Game2020AkkadianPositionENum _akkadianPosition;
    };

    //-------------------------------------------------------

    enum Game2020GroundedBuoyCodeENum : uint8_t
    {
        GROUNDED_BUOY_CODE_UNKNOWN = 0x00,
        GROUNDED_BUOY_CODE_1 = 0x01,
        GROUNDED_BUOY_CODE_2 = 0x02,
        GROUNDED_BUOY_CODE_3 = 0x03,
    };

    class Game2020GroundedBuoyCode
    {
    public:
        Game2020GroundedBuoyCodeENum _groundedBuoyCode;
    };

    //-------------------------------------------------------

    struct Game2020SerialMessage
    {

        uint8_t _header1[6] = {0xac, 0xed, 0x00, 0x05, 0x77, 0xa2};
        uint8_t _header2[2] = {0x05, 0x35};
        uint8_t _emitter = 0x01;
        uint8_t _timestamp[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
        uint8_t _secondsSinceStartOfGame[2] = {0x00, 0x00};
        uint8_t _weatherVanePosition = 0x00;

        uint8_t _robot_01_aruco[2] = {0x00, 0x00};
        uint8_t _robot_01_team[2] = {0x00, 0x00};
        uint8_t _robot_01_type[2] = {0x00, 0x00};
        uint8_t _robot_01_color[2] = {0x00, 0x00};
        uint8_t _robot_01_position_error[2] = {0x00, 0x00};
        uint8_t _robot_01_position_x[2] = {0x00, 0x00};
        uint8_t _robot_01_position_y[2] = {0x00, 0x00};
        uint8_t _robot_01_position_delta_error[2] = {0x00, 0x00};
        uint8_t _robot_01_position_delta_x[2] = {0x00, 0x00};
        uint8_t _robot_01_position_delta_y[2] = {0x00, 0x00};
        uint8_t _robot_01_status[16] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

        uint8_t _robot_02_aruco[2] = {0x00, 0x00};
        uint8_t _robot_02_team[2] = {0x00, 0x00};
        uint8_t _robot_02_type[2] = {0x00, 0x00};
        uint8_t _robot_02_color[2] = {0x00, 0x00};
        uint8_t _robot_02_position_error[2] = {0x00, 0x00};
        uint8_t _robot_02_position_x[2] = {0x00, 0x00};
        uint8_t _robot_02_position_y[2] = {0x00, 0x00};
        uint8_t _robot_02_position_delta_error[2] = {0x00, 0x00};
        uint8_t _robot_02_position_delta_x[2] = {0x00, 0x00};
        uint8_t _robot_02_position_delta_y[2] = {0x00, 0x00};
        uint8_t _robot_02_status[16] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

        uint8_t _robot_03_aruco[2] = {0x00, 0x00};
        uint8_t _robot_03_team[2] = {0x00, 0x00};
        uint8_t _robot_03_type[2] = {0x00, 0x00};
        uint8_t _robot_03_color[2] = {0x00, 0x00};
        uint8_t _robot_03_position_error[2] = {0x00, 0x00};
        uint8_t _robot_03_position_x[2] = {0x00, 0x00};
        uint8_t _robot_03_position_y[2] = {0x00, 0x00};
        uint8_t _robot_03_position_delta_error[2] = {0x00, 0x00};
        uint8_t _robot_03_position_delta_x[2] = {0x00, 0x00};
        uint8_t _robot_03_position_delta_y[2] = {0x00, 0x00};
        uint8_t _robot_03_status[16] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

        uint8_t _robot_04_aruco[2] = {0x00, 0x00};
        uint8_t _robot_04_team[2] = {0x00, 0x00};
        uint8_t _robot_04_type[2] = {0x00, 0x00};
        uint8_t _robot_04_color[2] = {0x00, 0x00};
        uint8_t _robot_04_position_error[2] = {0x00, 0x00};
        uint8_t _robot_04_position_x[2] = {0x00, 0x00};
        uint8_t _robot_04_position_y[2] = {0x00, 0x00};
        uint8_t _robot_04_position_delta_error[2] = {0x00, 0x00};
        uint8_t _robot_04_position_delta_x[2] = {0x00, 0x00};
        uint8_t _robot_04_position_delta_y[2] = {0x00, 0x00};
        uint8_t _robot_04_status[16] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

        uint8_t _akkadian_side[2] = {0x00, 0x00};
        uint8_t _buoyCode[2] = {0x00, 0x00};
    };

} /* namespace akkadian */

#endif /* FRAMEHANDLER_H_ */

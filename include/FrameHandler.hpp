/*
 * CameraHandler.h
 *
 *  Created on: 16 oct. 2020
 *      Author: vortigern
 */

#ifndef FRAMEHANDLER_H_
#define FRAMEHANDLER_H_

#include <thread>
#include <mutex>
#include <string>

#include "opencv.hpp"
#include <iostream>
#include "AkkadianService.hpp"
#include <list>
#include <chrono>

namespace akkadian
{

    using namespace std;
    using namespace cv;

    class FrameHandler
    {
    public:
        FrameHandler(std::string id)
        {
            this->_id = id;
        };
        virtual ~FrameHandler(){

        };

        virtual bool processFrame(std::shared_ptr<cv::Mat> frame, std::string sourceDevice = "", std::chrono::time_point<std::chrono::system_clock> timepoint = std::chrono::system_clock::now())
        {
            return false;
        };

        std::string getId()
        {
            return this->_id;
        };

    private:
        std::string _id;
    };

} /* namespace akkadian */

#endif /* FRAMEHANDLER_H_ */

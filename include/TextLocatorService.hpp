/*
 * CameraHandler.h
 *
 *  Created on: 16 oct. 2020
 *      Author: vortigern
 */

#ifndef EASTTEXTLOCATOR_H_
#define EASTTEXTLOCATOR_H_

#include <thread>
#include <mutex>
#include <string>

#include "opencv.hpp"
#include <iostream>
#include "AkkadianService.hpp"
#include "FrameHandler.hpp"
#include <list>
#include <chrono>

namespace akkadian
{
    using namespace akkadian;
    using namespace std;
    using namespace cv;

    class TextLocatorService : public akkadian::AkkadianService, public FrameHandler
    {
    public:
        TextLocatorService();
        virtual ~TextLocatorService();

        bool init();
        bool start();
        bool stop();
        bool reset();
        void run();
        bool processFrame(std::shared_ptr<cv::Mat> frame, std::string sourceDevice = "", std::chrono::time_point<std::chrono::system_clock> timepoint = std::chrono::system_clock::now()) override;

		bool addFrameHandler(FrameHandler *handler);
		bool removeFrameHandler(FrameHandler *handler);

    private:
        std::chrono::milliseconds _cycleDuration = 1517ms;
        std::queue<std::shared_ptr<Mat>> *_frames;
        std::string _name;

        std::map<std::string, FrameHandler *> *_handlers;
    };
} /* namespace akkadian */

#endif /* FRAMEHANDLER_H_ */

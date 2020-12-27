/*
 * CameraHandler.h
 *
 *  Created on: 16 oct. 2020
 *      Author: vortigern
 */

#ifndef CAMERAHANDLER_H_
#define CAMERAHANDLER_H_

#include <thread>
#include <mutex>
#include <string>

#include "opencv.hpp"
#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include "AkkadianService.hpp"
#include "Configuration.hpp"
#include "FrameHandler.hpp"

#include <list>
#include <chrono>

namespace akkadian
{

	using namespace std;
	using namespace akkadian;

	class CameraHandler : public akkadian::AkkadianService
	{
	public:
		CameraHandler(std::string device);
		CameraHandler(std::string device, int width, int height);
		CameraHandler(const Game2020CameraConfiguration config);

		virtual ~CameraHandler();

		bool init();
		bool start();
		bool stop();
		bool reset();
		void run();

		bool addFrameHandler(FrameHandler *handler);
		bool removeFrameHandler(FrameHandler *handler);

	private:
		std::string _device;
		std::unique_ptr<cv::VideoCapture> _videoCapture;
		std::chrono::milliseconds _cycleDuration = 100ms;

		std::map<std::string, FrameHandler *> *_handlers;

		int _requestedWidth;
		int _requestedHeight;
	};

} /* namespace akkadian */

#endif /* CAMERAHANDLER_H_ */

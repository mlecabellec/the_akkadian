/*
 * CameraHandler.h
 *
 *  Created on: 16 oct. 2020
 *      Author: vortigern
 */

#ifndef BUOYCODEDETECTOR_H_
#define BUOYCODEDETECTOR_H_

#include <thread>
#include <mutex>
#include <string>

#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include "AkkadianService.hpp"
#include "AkkadianEvents.hpp"
#include "FrameHandler.hpp"
#include "Configuration.hpp"
#include "Models.hpp"

#include <vector>
#include <list>
#include <chrono>
#include <limits>
#include <algorithm>

#include <ios>
#include <iostream>
#include <fstream>
#include <functional>

namespace akkadian
{

	using namespace std;

	class BuoyCodeDetector : public akkadian::AkkadianService, public FrameHandler, public AkkadianEventProducer<Game2020GroundedBuoyCode *>
	{
	public:
		BuoyCodeDetector(int x, int y, int width, int height, std::string name, int samplingWindowSize = 30, int samplingWindowMoveIncrement = 3); //
		BuoyCodeDetector(SimpleRectZoneInCamera zone, int samplingWindowSize = 30, int samplingWindowMoveIncrement = 3);
		virtual ~BuoyCodeDetector();

		bool init();
		bool start();
		bool stop();
		bool reset();
		void run();
		bool processFrame(std::shared_ptr<cv::Mat> frame, std::string sourceDevice = "", std::chrono::time_point<std::chrono::system_clock> timepoint = std::chrono::system_clock::now()) override;

	private:
		std::chrono::milliseconds _cycleDuration = 600ms;
		std::queue<std::shared_ptr<Mat>> *_frames;
		int _x;
		int _y;
		int _width;
		int _height;

		int _samplingWindowSize = 10;
		int _samplingWindowMoveIncrement = 3;

		std::ofstream _csvFileStream;
	};

} /* namespace akkadian */

#endif /* CAMERAHANDLER_H_ */

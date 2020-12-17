/*
 * CameraHandler.h
 *
 *  Created on: 16 oct. 2020
 *      Author: vortigern
 */

#ifndef GPIOSERVICE_H_
#define GPIOSERVICE_H_

#include <thread>
#include <mutex>
#include <string>

#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include "AkkadianService.hpp"
#include "Configuration.hpp"
#include "AkkadianEvents.hpp"
#include "Models.hpp"
#include "FrameHandler.hpp"

#include <list>
#include <chrono>

// C library headers
#include <stdio.h>

// Linux headers
#include <wiringPi.h>

namespace akkadian
{

	using namespace std;
	using namespace akkadian;

	const int GPIO_SIDESENSING_YELLOW_SIDE_SENSOR_PIN = 24;
	const int GPIO_SIDESENSING_YELLOW_SIDE_HIGH_PIN = 25;
	const int GPIO_SIDESENSING_YELLOW_SIDE_LOW_PIN = 29;

	const int GPIO_SIDESENSING_BLUE_SIDE_SENSOR_PIN = 27;
	const int GPIO_SIDESENSING_BLUE_SIDE_HIGH_PIN = 28;
	const int GPIO_SIDESENSING_BLUE_SIDE_LOW_PIN = 29;

	class GpioService : public akkadian::AkkadianService, public AkkadianEventListener<Game2020WeatherVanePosition>, public AkkadianEventProducer<Game2020AkkadianPosition *>
	{
	public:
		GpioService();

		virtual ~GpioService();

		bool init();
		bool start();
		bool stop();
		bool reset();
		void run();

		bool processEvent(AkkadianEvent<Game2020WeatherVanePosition> *event) override;

	private:
		std::string _device;
		std::chrono::milliseconds _cycleDuration = 2304ms;
	};

} /* namespace akkadian */

#endif /* CAMERAHANDLER_H_ */

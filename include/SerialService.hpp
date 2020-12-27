/*
 * CameraHandler.h
 *
 *  Created on: 16 oct. 2020
 *      Author: vortigern
 */

#ifndef SERIALSERVICE_H_
#define SERIALSERVICE_H_

#include <thread>
#include <mutex>
#include <string>

#include "opencv.hpp"
#include "core.hpp"
#include "videoio.hpp"
//#include <opencv2/highgui.hpp>
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
#include <fcntl.h>	 // Contains file controls like O_RDWR
#include <errno.h>	 // Error integer and strerror() function
#include <termios.h> // Contains POSIX terminal control definitions
#include <unistd.h>	 // write(), read(), close()

namespace akkadian
{

	using namespace std;
	using namespace akkadian;

	class SerialService : public akkadian::AkkadianService,
						  public AkkadianEventListener<Game2020WeatherVanePosition *>,
						  public AkkadianEventListener<Game2020AkkadianPosition *>,
						  public AkkadianEventListener<Game2020GroundedBuoyCode *>
	{
	public:
		SerialService(std::string device);

		virtual ~SerialService();

		bool init();
		bool start();
		bool stop();
		bool reset();
		void run();

		bool processEvent(AkkadianEvent<Game2020WeatherVanePosition *> *event) override;
		bool processEvent(AkkadianEvent<Game2020AkkadianPosition *> *event) override;
		bool processEvent(AkkadianEvent<Game2020GroundedBuoyCode *> *event) override;

	private:
		std::string _device;
		std::chrono::milliseconds _cycleDuration = 163ms;

		int _serialPortHandle;
		struct termios _tty;

		Game2020SerialMessage *_message;
	};

} /* namespace akkadian */

#endif /* CAMERAHANDLER_H_ */

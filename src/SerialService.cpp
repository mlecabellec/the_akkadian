/*
 * SerialService.cpp
 *
 *  Created on: 16 oct. 2020
 *      Author: vortigern
 */

#include "SerialService.hpp"

namespace akkadian
{

	using namespace akkadian;
	using namespace std;
	using namespace cv;

	SerialService::SerialService(std::string device) : AkkadianService(),
													   AkkadianEventListener<Game2020WeatherVanePosition *>(std::string("serialService")),
													   AkkadianEventListener<Game2020AkkadianPosition *>(std::string("serialService")),
													   AkkadianEventListener<Game2020GroundedBuoyCode *>(std::string("serialService"))
	{
		// TODO Auto-generated constructor stub
		this->_device = device;
	}

	SerialService::~SerialService()
	{
		// TODO Auto-generated destructor stub
	}

	bool SerialService::init()
	{
		std::cout << "SerialService::init()\r\n";
		std::lock_guard<std::mutex> lock(this->_mutex);
		if (this->_status != ServiceStatusEnum::UNKNOWN && this->_status != ServiceStatusEnum::READY)
		{
			std::cout << "SerialService::init(), not in READY or UNKNOWN state\r\n";
			return false;
		}

		std::cout << "SerialService::init(), this->_device = " << this->_device << "\r\n";

		this->_message = new Game2020SerialMessage();

		//https://blog.mbedded.ninja/programming/operating-systems/linux/linux-serial-ports-using-c-cpp/

		this->_serialPortHandle = open(this->_device.c_str(), O_RDWR);

		if (tcgetattr(this->_serialPortHandle, &this->_tty) != 0)
		{
			std::cout << "SerialService::init(), tcgetattr failed. \r\n";
			this->_status = ServiceStatusEnum::UNKNOWN;
			return false;
		}

		this->_tty.c_cflag &= ~PARENB;		  // Clear parity bit, disabling parity (most common)
		this->_tty.c_cflag &= ~CSTOPB;		  // Clear stop field, only one stop bit used in communication (most common)
		this->_tty.c_cflag &= ~CSIZE;		  // Clear all bits that set the data size
		this->_tty.c_cflag |= CS8;			  // 8 bits per byte (most common)
		this->_tty.c_cflag &= ~CRTSCTS;		  // Disable RTS/CTS hardware flow control (most common)
		this->_tty.c_cflag |= CREAD | CLOCAL; // Turn on READ & ignore ctrl lines (CLOCAL = 1)

		this->_tty.c_lflag &= ~ICANON;
		this->_tty.c_lflag &= ~ECHO;														// Disable echo
		this->_tty.c_lflag &= ~ECHOE;														// Disable erasure
		this->_tty.c_lflag &= ~ECHONL;														// Disable new-line echo
		this->_tty.c_lflag &= ~ISIG;														// Disable interpretation of INTR, QUIT and SUSP
		this->_tty.c_iflag &= ~(IXON | IXOFF | IXANY);										// Turn off s/w flow ctrl
		this->_tty.c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP | INLCR | IGNCR | ICRNL); // Disable any special handling of received bytes

		this->_tty.c_oflag &= ~OPOST; // Prevent special interpretation of output bytes (e.g. newline chars)
		this->_tty.c_oflag &= ~ONLCR; // Prevent conversion of newline to carriage return/line feed
		// tty.c_oflag &= ~OXTABS; // Prevent conversion of tabs to spaces (NOT PRESENT ON LINUX)
		// tty.c_oflag &= ~ONOEOT; // Prevent removal of C-d chars (0x004) in output (NOT PRESENT ON LINUX)

		this->_tty.c_cc[VTIME] = 10; // Wait for up to 1s (10 deciseconds), returning as soon as any data is received.
		this->_tty.c_cc[VMIN] = 0;

		// Set in/out baud rate to be 115200
		cfsetispeed(&this->_tty, B115200);
		cfsetospeed(&this->_tty, B115200);

		// Save tty settings, also checking for error
		if (tcsetattr(this->_serialPortHandle, TCSANOW, &this->_tty) != 0)
		{
			std::cout << "SerialService::init(), tcgetattr failed. \r\n";
			return 1;
		}

		this->_status = ServiceStatusEnum::READY;
		return true;
	}

	bool SerialService::start()
	{
		std::cout << "SerialService::start()\r\n";
		std::lock_guard<std::mutex> lock(this->_mutex);
		if (this->_status != ServiceStatusEnum::READY)
		{
			std::cout << "SerialService::start(), service is not in READY state\r\n";
			return false;
		}

		this->_status = ServiceStatusEnum::STARTING;

		//std::cout << "SerialService::start(), checking if device is opened...\r\n";

		this->_thread = new thread(&SerialService::run, this);

		return true;
	}
	bool SerialService::stop()
	{
		std::lock_guard<std::mutex> lock(this->_mutex);
		if (this->_status != ServiceStatusEnum::RUNNING)
		{
			std::cout << "SerialService::stop(), not in RUNNING state\r\n";
			return false;
		}

		this->_status = ServiceStatusEnum::STOPPING;

		return true;
	}

	bool SerialService::processEvent(AkkadianEvent<Game2020WeatherVanePosition *> *event)
	{
		std::cout << "SerialService::processEvent(AkkadianEvent<Game2020WeatherVanePosition> *event), received event\r\n";

		this->_message->_weatherVanePosition = event->_data->_weatherVanePosition;

		return true;
	}

	bool SerialService::processEvent(AkkadianEvent<Game2020AkkadianPosition *> *event)
	{
		std::cout << "SerialService::processEvent(AkkadianEvent<Game2020AkkadianPosition> *event), received event\r\n";

		this->_message->_akkadian_side[1] = event->_data->_akkadianPosition;

		return true;
	}

	bool SerialService::processEvent(AkkadianEvent<Game2020GroundedBuoyCode *> *event)
	{
		std::cout << "SerialService::processEvent(AkkadianEvent<Game2020GroundedBuoyCode> *event), received event\r\n";

		this->_message->_buoyCode[1] = event->_data->_groundedBuoyCode;

		return true;
	}

	void SerialService::run()
	{
		if (this->_status == ServiceStatusEnum::STARTING)
		{
			this->_status = ServiceStatusEnum::RUNNING;
		}

		std::cout << "SerialService::run(), going in the loop\r\n";
		while (this->_status == ServiceStatusEnum::RUNNING)
		{
			try
			{

				std::chrono::time_point<std::chrono::system_clock> t0 = std::chrono::system_clock::now();
				std::chrono::time_point<std::chrono::system_clock> t1 = t0;
				t1 += this->_cycleDuration;

				std::cout << "SerialService::run(), writing to serial port...\r\n";
				int numBytesSent = write(this->_serialPortHandle, this->_message, sizeof(Game2020SerialMessage));
				std::cout << "SerialService::run(), wrote " << numBytesSent << " byte(s) to serial port.\r\n";

				char incomingData[2048];

				std::cout << "SerialService::run(), reading from serial port...\r\n";
				int numBytesReceived = read(this->_serialPortHandle, &incomingData, sizeof(incomingData));

				if (numBytesReceived == 0)
				{
					std::cout << "SerialService::run(), No data received...\r\n";
				}
				else
				{
					std::cout << "SerialService::run(), incoming data" << incomingData << "\r\n";
				}

				std::this_thread::sleep_until(t1);
			}
			catch (const std::exception &e)
			{

				//TODO: log
			}
		}
		std::cout << "SerialService::run(), leaving in the loop\r\n";
	}

} /* namespace akkadian */

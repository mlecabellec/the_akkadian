/*
 * CameraHandler.cpp
 *
 *  Created on: 16 oct. 2020
 *      Author: vortigern
 */

#include "CameraHandler.hpp"

namespace akkadian
{

	using namespace akkadian;
	using namespace std;
	using namespace cv;

	CameraHandler::CameraHandler(std::string device) : AkkadianService()
	{
		// TODO Auto-generated constructor stub
		this->_device = device;
		this->_handlers = new std::map<std::string, FrameHandler *>();
		this->_requestedHeight = 0;
		this->_requestedWidth = 0;
	}

	CameraHandler::CameraHandler(std::string device, int width, int height) : AkkadianService()
	{
		// TODO Auto-generated constructor stub
		this->_device = device;
		this->_handlers = new std::map<std::string, FrameHandler *>();
		this->_requestedHeight = height;
		this->_requestedWidth = width;
	}
	CameraHandler::CameraHandler(const Game2020CameraConfiguration config) : AkkadianService()
	{
		this->_device = config._cameraDevice;
		this->_handlers = new std::map<std::string, FrameHandler *>();
		this->_requestedHeight = config._height;
		this->_requestedWidth = config._width;
	}

	CameraHandler::~CameraHandler()
	{
		// TODO Auto-generated destructor stub
		delete this->_handlers;
	}

	bool CameraHandler::init()
	{
		std::cout << "CameraHandler::init()\r\n";
		std::lock_guard<std::mutex> lock(this->_mutex);
		if (this->_status != ServiceStatusEnum::UNKNOWN && this->_status != ServiceStatusEnum::READY)
		{
			std::cout << "CameraHandler::init(), not in READY or UNKNOWN state\r\n";
			return false;
		}

		std::cout << "CameraHandler::init(), this->_device = " << this->_device << "\r\n";
		this->_videoCapture = std::make_unique<cv::VideoCapture>(this->_device.c_str(), cv::VideoCaptureAPIs::CAP_ANY);
		if (this->_requestedWidth > 0)
		{
			this->_videoCapture->set(cv::VideoCaptureProperties::CAP_PROP_FRAME_WIDTH, this->_requestedWidth);
			this->_videoCapture->set(cv::VideoCaptureProperties::CAP_PROP_FRAME_HEIGHT, this->_requestedHeight);
		}

		this->_status = ServiceStatusEnum::READY;
		return true;
	}

	bool CameraHandler::start()
	{
		std::cout << "CameraHandler::start()\r\n";
		std::lock_guard<std::mutex> lock(this->_mutex);
		if (this->_status != ServiceStatusEnum::READY)
		{
			std::cout << "CameraHandler::start(), service is not in READY state\r\n";
			return false;
		}

		this->_status = ServiceStatusEnum::STARTING;

		std::cout << "CameraHandler::start(), checking if device is opened...\r\n";
		bool isOpened = this->_videoCaptur	e->isOpened();
		if (!isOpened)
		{
			std::cout << "CameraHandler::start(), video capture object not open\r\n";
			this->_status = ServiceStatusEnum::FAILED;
		}
		else
		{
			std::cout << "CameraHandler::start(), device is opened...\r\n";
		}

		this->_thread = new thread(&CameraHandler::run, this);

		return isOpened;
	}
	bool CameraHandler::stop()
	{
		std::lock_guard<std::mutex> lock(this->_mutex);
		if (this->_status != ServiceStatusEnum::RUNNING)
		{
			std::cout << "CameraHandler::stop(), not in RUNNING state\r\n";
			return false;
		}

		this->_status = ServiceStatusEnum::STOPPING;

		return true;
	}

	void CameraHandler::run()
	{
		if (this->_status == ServiceStatusEnum::STARTING)
		{
			this->_status = ServiceStatusEnum::RUNNING;
		}

		std::cout << "CameraHandler::run(), going in the loop\r\n";
		while (this->_status == ServiceStatusEnum::RUNNING)
		{
			try
			{

				std::chrono::time_point<std::chrono::system_clock> t0 = std::chrono::system_clock::now();
				std::chrono::time_point<std::chrono::system_clock> t1 = t0;
				t1 += this->_cycleDuration;

				Mat frame;
				if (!this->_videoCapture->read(frame) || frame.empty())
				{
					std::cout << "device " << this->_device << ", "
							  << "CameraHandler::run(), Frame is empty\r\n";
				}
				else
				{
					std::cout << "device " << this->_device << ", "
							  << "CameraHandler::run(), Frame was captured\r\n";

					std::cout << "CameraHandler::run(), frame width = " << frame.size().width << "\r\n";
					std::cout << "CameraHandler::run(), frame height = " << frame.size().height << "\r\n";

					std::shared_ptr<Mat> sFrame = std::make_shared<Mat>(frame);

					for (std::map<std::string, FrameHandler *>::iterator it = this->_handlers->begin(); it != this->_handlers->end(); ++it)
					{
						FrameHandler *handler = it->second;
						handler->processFrame(sFrame);
						std::cout << "device " << this->_device << ", "
								  << "CameraHandler::run(), Frame was sent to " << it->second->getId() << "\r\n";
					}

					//delete sFrame ;
				}

				std::this_thread::sleep_until(t1);
			}
			catch (const std::exception &e)
			{

				//TODO: log
			}
		}
		std::cout << "CameraHandler::run(), leaving in the loop\r\n";
	}

	bool CameraHandler::addFrameHandler(FrameHandler *handler)
	{
		if (handler == nullptr)
		{
			return false;
		}

		std::pair<std::map<std::string, FrameHandler *>::iterator, bool> result = this->_handlers->insert_or_assign(handler->getId(), handler);

		if (result.second)
		{
			std::cout << "CameraHandler::addFrameHandler(), added handler with id " << handler->getId() << "\r\n";
		}else
		{
			std::cout << "CameraHandler::addFrameHandler(), handler with id " << handler->getId() << " NOT ADDED !!\r\n";
		}
		

		return result.second;
	}
	bool CameraHandler::removeFrameHandler(FrameHandler *handler)
	{
		if (handler == nullptr)
		{
			return false;
		}

		std::string id = handler->getId();

		std::map<std::string, FrameHandler *>::iterator it = this->_handlers->find(id);
		if (it != this->_handlers->end())
		{
			this->_handlers->erase(it);
			std::cout << "CameraHandler::removeFrameHandler(), handler removed " << id << "\r\n";
			return true;
		}

		return false;
	}

} /* namespace akkadian */

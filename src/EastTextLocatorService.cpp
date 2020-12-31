/*
 * CameraHandler.cpp
 *
 *  Created on: 16 oct. 2020
 *      Author: vortigern
 */

#include "EastTextLocatorService.hpp"

namespace akkadian
{

    using namespace akkadian;
    using namespace std;
    using namespace cv;

    EastTextLocatorService::EastTextLocatorService() : AkkadianService(), FrameHandler(std::string("EastTextLocatorService"))
    {
        // TODO Auto-generated constructor stub
        this->_frames = new std::queue<std::shared_ptr<Mat>>();

        this->_handlers = new std::map<std::string, FrameHandler *>();

        this->_name = std::string("EastTextLocatorService");
    }

    EastTextLocatorService::~EastTextLocatorService()
    {
        // TODO Auto-generated destructor stub
        delete this->_frames;
    }

    bool EastTextLocatorService::init()
    {
        std::cout << "EastTextLocatorService::init()\r\n";
        std::lock_guard<std::mutex> lock(this->_mutex);
        if (this->_status != ServiceStatusEnum::UNKNOWN && this->_status != ServiceStatusEnum::READY)
        {
            std::cout << "EastTextLocatorService::init(), not in READY or UNKNOWN state\r\n";
            return false;
        }

        this->_status = ServiceStatusEnum::READY;
        return true;
    }

    bool EastTextLocatorService::start()
    {
        std::cout << "EastTextLocatorService::start()\r\n";
        std::lock_guard<std::mutex> lock(this->_mutex);
        if (this->_status != ServiceStatusEnum::READY)
        {
            std::cout << "EastTextLocatorService::start(), service is not in READY state\r\n";
            return false;
        }

        this->_status = ServiceStatusEnum::STARTING;

        this->_thread = new thread(&EastTextLocatorService::run, this);

        return true;
    }
    bool EastTextLocatorService::stop()
    {
        std::lock_guard<std::mutex> lock(this->_mutex);
        if (this->_status != ServiceStatusEnum::RUNNING)
        {
            std::cout << "EastTextLocatorService::stop(), not in RUNNING state\r\n";
            return false;
        }

        this->_status = ServiceStatusEnum::STOPPING;

        this->_thread->join();

        return true;
    }

    void EastTextLocatorService::run()
    {
        if (this->_status == ServiceStatusEnum::STARTING)
        {
            this->_status = ServiceStatusEnum::RUNNING;
        }

        vector<int> compression_params;
        //        compression_params.push_back(IMWRITE_PNG_COMPRESSION);
        //        compression_params.push_back(9);

        int cycleCounter = 0;

        std::cout << "EastTextLocatorService::run(), going in the loop\r\n";
        while (this->_status == ServiceStatusEnum::RUNNING && (cycleCounter < 2000))
        {
            try
            {

                cycleCounter++;

                std::chrono::time_point<std::chrono::system_clock> t0 = std::chrono::system_clock::now();
                std::chrono::time_point<std::chrono::system_clock> t1 = t0;
                t1 += this->_cycleDuration;

                std::cout << "EastTextLocatorService::run(), queue contains " << this->_frames->size() << " frames "
                          << "\r\n";

                if (this->_frames->size() > 0)
                {
                    std::shared_ptr<cv::Mat> frame = this->_frames->front();

                    int frameWidth = frame->size().width;
                    int frameHeight = frame->size().height;

                    std::cout << "EastTextLocatorService::run(), frame width = " << frameWidth << "\r\n";
                    std::cout << "EastTextLocatorService::run(), frame height = " << frameHeight << "\r\n";

                    while (!this->_frames->empty())
                    {
                        this->_frames->pop();
                    }
                    //this->_frames->pop();
                    //delete frame ;
                }
                else
                {
                    std::cout << "EastTextLocatorService::run(), no frame... "
                              << "\r\n";
                }

                std::this_thread::sleep_until(t1);
            }
            catch (const std::exception &e)
            {

                //TODO: log
            }
        }
        std::cout << "EastTextLocatorService::run(), leaving in the loop\r\n";
    }

    bool EastTextLocatorService::processFrame(std::shared_ptr<cv::Mat> frame, std::string sourceDevice, std::chrono::time_point<std::chrono::system_clock> timepoint)
    {

        if (frame == nullptr)
        {
            std::cout << "EastTextLocatorService::processFrame(), frame is null "
                      << "\r\n";
            return false;
        }

        std::cout << "EastTextLocatorService::processFrame(), frame width = " << frame->size().width << "\r\n";
        std::cout << "EastTextLocatorService::processFrame(), frame height = " << frame->size().height << "\r\n";

        this->_frames->emplace(frame);
        std::cout << "EastTextLocatorService::processFrame(), queue contains " << this->_frames->size() << " frames "
                  << "\r\n";

        return true;
    };

    bool EastTextLocatorService::addFrameHandler(FrameHandler *handler)
    {
        if (handler == nullptr)
        {
            return false;
        }

        std::pair<std::map<std::string, FrameHandler *>::iterator, bool> result = this->_handlers->insert_or_assign(handler->getId(), handler);

        if (result.second)
        {
            std::cout << "CameraHandler::addFrameHandler(), added handler with id " << handler->getId() << "\r\n";
        }
        else
        {
            std::cout << "CameraHandler::addFrameHandler(), handler with id " << handler->getId() << " NOT ADDED !!\r\n";
        }

        return result.second;
    }
    bool EastTextLocatorService::removeFrameHandler(FrameHandler *handler)
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

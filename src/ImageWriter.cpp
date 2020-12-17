/*
 * CameraHandler.cpp
 *
 *  Created on: 16 oct. 2020
 *      Author: vortigern
 */

#include "ImageWriter.hpp"

namespace akkadian
{

    using namespace akkadian;
    using namespace std;
    using namespace cv;

    ImageWriter::ImageWriter(SimpleRectZoneInCamera zone) : AkkadianService(), FrameHandler(std::string("ImageWriter_") + zone._zoneName)
    {
        // TODO Auto-generated constructor stub
        this->_frames = new std::queue<std::shared_ptr<Mat>>();

        this->_x = zone._x;
        this->_y = zone._y;
        this->_width = zone._width;
        this->_height = zone._height;
        this->_name = zone._zoneName;
    }

    ImageWriter::~ImageWriter()
    {
        // TODO Auto-generated destructor stub
        delete this->_frames;
    }

    bool ImageWriter::init()
    {
        std::cout << "ImageWriter::init()\r\n";
        std::lock_guard<std::mutex> lock(this->_mutex);
        if (this->_status != ServiceStatusEnum::UNKNOWN && this->_status != ServiceStatusEnum::READY)
        {
            std::cout << "ImageWriter::init(), not in READY or UNKNOWN state\r\n";
            return false;
        }

        this->_status = ServiceStatusEnum::READY;
        return true;
    }

    bool ImageWriter::start()
    {
        std::cout << "ImageWriter::start()\r\n";
        std::lock_guard<std::mutex> lock(this->_mutex);
        if (this->_status != ServiceStatusEnum::READY)
        {
            std::cout << "ImageWriter::start(), service is not in READY state\r\n";
            return false;
        }

        this->_status = ServiceStatusEnum::STARTING;

        this->_thread = new thread(&ImageWriter::run, this);

        return true;
    }
    bool ImageWriter::stop()
    {
        std::lock_guard<std::mutex> lock(this->_mutex);
        if (this->_status != ServiceStatusEnum::RUNNING)
        {
            std::cout << "ImageWriter::stop(), not in RUNNING state\r\n";
            return false;
        }

        this->_status = ServiceStatusEnum::STOPPING;

        this->_thread->join();

        return true;
    }

    void ImageWriter::run()
    {
        if (this->_status == ServiceStatusEnum::STARTING)
        {
            this->_status = ServiceStatusEnum::RUNNING;
        }

        vector<int> compression_params;
        //        compression_params.push_back(IMWRITE_PNG_COMPRESSION);
        //        compression_params.push_back(9);

        int cycleCounter = 0;

        std::cout << "ImageWriter::run(), going in the loop\r\n";
        while (this->_status == ServiceStatusEnum::RUNNING && (cycleCounter < 2000 ) ) 
        {
            try
            {

                cycleCounter++;

                std::chrono::time_point<std::chrono::system_clock> t0 = std::chrono::system_clock::now();
                std::chrono::time_point<std::chrono::system_clock> t1 = t0;
                t1 += this->_cycleDuration;

                std::cout << "ImageWriter::run(), queue contains " << this->_frames->size() << " frames "
                          << "\r\n";

                if (this->_frames->size() > 0)
                {
                    std::shared_ptr<cv::Mat> frame = this->_frames->front();

                    int frameWidth = frame->size().width;
                    int frameHeight = frame->size().height;

                    std::cout << "ImageWriter::run(), frame width = " << frameWidth << "\r\n";
                    std::cout << "ImageWriter::run(), frame height = " << frameHeight << "\r\n";

                    if ((frameHeight >= this->_y + this->_height) && (frameWidth >= this->_x + this->_width))
                    {
                        const Rect cropRect(this->_x, this->_y, this->_width, this->_height);
                        Mat *subImage = new cv::Mat((*frame), cropRect);

                        std::cout << "ImageWriter::run(), subimage width = " << subImage->size().width << "\r\n";
                        std::cout << "ImageWriter::run(), subimage height = " << subImage->size().height << "\r\n";

                        std::string filename = this->_name + std::string("_") + std::to_string(cycleCounter) + std::string(".jpg");
                        std::cout << "ImageWriter::run(), writing " << filename << "\r\n";
                        imwrite(filename.c_str(), *subImage, compression_params);
                        std::cout << "ImageWriter::run(), wrote " << filename << "\r\n";
                        delete subImage;
                    }
                    else
                    {
                        std::cout << "ImageWriter::run(), " << this->_name << ", out of bound, fixing it ! \r\n";
                        this->_x = 0;
                        this->_y = 0;
                        this->_width = frame->size().width;
                        this->_height = frame->size().height;

                        std::string filename = this->_name + std::string("_") + std::to_string(cycleCounter) + std::string(".jpg");
                        std::cout << "ImageWriter::run(), writing " << filename << "\r\n";
                        imwrite(filename.c_str(), *frame, compression_params);
                        std::cout << "ImageWriter::run(), wrote " << filename << "\r\n";
                    }

                    while (!this->_frames->empty())
                    {
                        this->_frames->pop();
                    }
                    //this->_frames->pop();
                    //delete frame ;
                }
                else
                {
                    std::cout << "ImageWriter::run(), no frame... "
                              << "\r\n";
                }

                std::this_thread::sleep_until(t1);
            }
            catch (const std::exception &e)
            {

                //TODO: log
            }
        }
        std::cout << "ImageWriter::run(), leaving in the loop\r\n";
    }

    bool ImageWriter::processFrame(std::shared_ptr<cv::Mat> frame, std::string sourceDevice, std::chrono::time_point<std::chrono::system_clock> timepoint)
    {

        if (frame == nullptr)
        {
            std::cout << "ImageWriter::processFrame(), frame is null "
                      << "\r\n";
            return false;
        }

        std::cout << "ImageWriter::processFrame(), frame width = " << frame->size().width << "\r\n";
        std::cout << "ImageWriter::processFrame(), frame height = " << frame->size().height << "\r\n";

        this->_frames->emplace(frame);
        std::cout << "ImageWriter::processFrame(), queue contains " << this->_frames->size() << " frames "
                  << "\r\n";

        return true;
    };

} /* namespace akkadian */

#include "class_pa_tracker.h"
#include <sstream>
#include <time.h>
#include <chrono>

#define CNUM (20)
int main()
{
	//
	cv::RNG rng(0xFFFFFFFF);
	cv::Scalar_<int> randColor[CNUM];
	for (int i = 0; i < CNUM; i++)
		rng.fill(randColor[i], cv::RNG::UNIFORM, 0, 256);
	
	//
	PaTracker pa_tracker;

	std::string detector_engine_path = "../lib/extra/detector/lib/yolov5s_fp16_b1.engine";
	std::string reid_engine_path = "../lib/extra/reid/lib/sbs_R50-ibn.engine";
	pa_tracker.init(detector_engine_path, reid_engine_path);

#if 0
	for (int i = 0; i < 205; i++)
	{
		std::stringstream ss;
		ss << "../data/pics1/" << i * 15 << ".jpg";
		cv::Mat img = cv::imread(ss.str());

		//
		auto start = std::chrono::system_clock::now();

		std::vector<cv::Rect> rects_tracked;
		std::vector<int> ids_tracked;
		pa_tracker.run(img, rects_tracked, ids_tracked);

		for (int j = 0; j < rects_tracked.size(); j++)
        {
            cv::rectangle(img, rects_tracked[j], randColor[ids_tracked[j] % CNUM], 4);
            cv::putText(img, std::to_string((int)ids_tracked[j]), 
			            cv::Point(rects_tracked[j].x, rects_tracked[j].y - 1), 
						cv::FONT_HERSHEY_PLAIN, 2, randColor[ids_tracked[j] % CNUM], 4);
        }

		//
		auto end = std::chrono::system_clock::now();
    	std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " total ms" << std::endl;
    

		{
			std::stringstream ss;
			// ss << "../data/output/" << i * 15 << ".jpg";
			ss << "../data/output/0.jpg";
			cv::imwrite(ss.str(), img);
			std::cout << i * 15 << std::endl;
			std::cin.get();
		}
	}
#else
	cv::VideoCapture capture;
	capture.open("../data/test.avi");
	if(!capture.isOpened())
	{
		printf("can not open ...\n");
		return -1;
	}

	int cnt = 0;
	cv::Mat img;
	while (capture.read(img))
	{
		std::cout << cnt++ << std::endl;
		
		//
		auto start = std::chrono::system_clock::now();

		std::vector<cv::Rect> rects_tracked;
		std::vector<int> ids_tracked;
		pa_tracker.run(img, rects_tracked, ids_tracked);

		for (int j = 0; j < rects_tracked.size(); j++)
        {
            cv::rectangle(img, rects_tracked[j], randColor[ids_tracked[j] % CNUM], 4);
            cv::putText(img, std::to_string((int)ids_tracked[j]), 
			            cv::Point(rects_tracked[j].x, rects_tracked[j].y - 1), 
						cv::FONT_HERSHEY_PLAIN, 2, randColor[ids_tracked[j] % CNUM], 4);
        }

		//
		auto end = std::chrono::system_clock::now();
    	std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " total ms" << std::endl;
    

		{
			std::stringstream ss;
			// ss << "../data/output/" << i * 15 << ".jpg";
			ss << "../data/output/0.jpg";
			cv::imwrite(ss.str(), img);
			std::cin.get();
		}
		
	}
	capture.release();


#endif
	
	return 0;
}
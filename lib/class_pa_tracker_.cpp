#include "class_pa_tracker_.h"

_PaTracker::_PaTracker() 
{
	
}
_PaTracker::~_PaTracker() 
{
   
}
bool _PaTracker::init(const std::string &detector_engine_path_,
                          const std::string &reid_engine_path_)
{

	bool is_detect = _detector.init(detector_engine_path_);
	bool is_reid = _reid.init(reid_engine_path_);
	return is_detect & is_reid;
}

bool _PaTracker::run(const cv::Mat &img_, 
             			std::vector<TrackedBox> &rects_tracked_)
{
	//detect
	std::vector<cv::Mat> imgs;
	imgs.push_back(img_);

	std::vector<std::vector<Detection> > vec_detections;
	bool is_detect = _detector.detect(imgs, vec_detections);
	if (!is_detect || (0 == vec_detections.size()))
	{
		return false;
	}

	// reid
	std::vector<Detection> detections = vec_detections[0];

	std::vector<cv::Rect> rects;
	std::vector<cv::Mat> person_imgs;
	for (int i = 0; i < detections.size(); i++)
	{
		if (detections[i].class_id == 0) // person
		{
			rects.push_back(detections[i].rect);
			person_imgs.push_back(img_(detections[i].rect).clone());
		}
	}

	std::vector<cv::Mat> features;
	_reid.extract_feature(person_imgs, features);

	// track
	return _tracker.run(rects, features, rects_tracked_);

}
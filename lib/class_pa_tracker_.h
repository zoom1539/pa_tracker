#pragma once

// std
#include <opencv2/opencv.hpp>
#include "class_tracker.h"
#include "class_detector.h"
#include "class_reid.h"

class _PaTracker
{
public:
    _PaTracker();
    ~_PaTracker();

public:
    bool init(const std::string &detector_engine_path_,
              const std::string &reid_engine_path_);
    bool run(const cv::Mat &img_, 
             std::vector<TrackedBox> &rects_tracked_);
    

private:
    Detector _detector;
    ReID     _reid;
    Tracker  _tracker;

};

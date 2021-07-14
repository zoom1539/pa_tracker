#pragma once

#include "opencv2/opencv.hpp"

class PaTracker
{
public:
    explicit PaTracker();
    ~PaTracker();

public:
    bool init(const std::string &detector_engine_path_,
              const std::string &reid_engine_path_);
    bool run(const cv::Mat &img_, 
             std::vector<cv::Rect> &rects_tracked_,
             std::vector<int> &ids_tracked_);
    

private:
    PaTracker(const PaTracker &);
    const PaTracker &operator=(const PaTracker &);

    class Impl;
    Impl *_impl;
};

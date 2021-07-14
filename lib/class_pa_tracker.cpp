#include "class_pa_tracker.h"
#include "class_pa_tracker_.h"

class PaTracker::Impl
{
public:
    _PaTracker _pa_tracker;
};

PaTracker::PaTracker() : _impl(new PaTracker::Impl())
{
}

PaTracker::~PaTracker()
{
    delete _impl;
    _impl = NULL;
}

bool PaTracker::init(const std::string &detector_engine_path_,
                         const std::string &reid_engine_path_)
{
    return _impl->_pa_tracker.init(detector_engine_path_, reid_engine_path_);
}

bool PaTracker::run(const cv::Mat &img_, 
                    std::vector<cv::Rect> &rects_tracked_,
                    std::vector<int> &ids_tracked_)
{
    std::vector<TrackedBox> rects_tracked;
    bool is_run = _impl->_pa_tracker.run(img_, rects_tracked);
    if (!is_run)
    {
        return false;
    }
    for (int i = 0; i < rects_tracked.size(); i++)
    {
        rects_tracked_.push_back(rects_tracked[i].rect);
        ids_tracked_.push_back(rects_tracked[i].id);
    }
}


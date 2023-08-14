#pragma once

#include <string>

#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>

///////////////////////////////////////////////////////////////////////////////////////////////////
class plateHaru {
public:
    // member variables ///////////////////////////////////////////////////////////////////////////
    cv::Mat plateCrop;
    cv::Mat imgGrayscale;
    cv::Mat threshCrop;

    cv::RotatedRect plateKoLocation;

    
    
    std::string plateChars;

    ///////////////////////////////////////////////////////////////////////////////////////////////
    static bool charsSortDesc(const plateHaru &ppLeft, const plateHaru &ppRight) {
        return(ppLeft.plateChars.length() > ppRight.plateChars.length());
    }

};



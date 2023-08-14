#pragma once

#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>

#include "Main.h"
#include "PossiblePlates.h"
#include "PossibleChar.h"
#include "Preprocess.h"
#include "DetectChars.h"

// global constants ///////////////////////////////////////////////////////////////////////////////
const double PLATE_WIDTH_PADDING_FACTOR = 1.3;
const double PLATE_HEIGHT_PADDING_FACTOR = 1.5;

// function prototypes ////////////////////////////////////////////////////////////////////////////
std::vector<plateHaru> plateHaruKhojne(cv::Mat &ogImage);

std::vector<PossibleChar> charsKhojne(cv::Mat &threshCrop);

plateHaru extractPlate(cv::Mat &imgOriginal, 
	
	
	std::vector<PossibleChar> &vectorOfMatchingChars);




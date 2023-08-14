#pragma once 

#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/ml/ml.hpp>

#include "Main.h"
#include "PossibleChar.h"
#include "PossiblePlates.h"
#include "Preprocess.h"

// global constants ///////////////////////////////////////////////////////////////////////////////

const int MIN_PIXEL_WIDTH = 2;
const int MIN_PIXEL_HEIGHT = 8;

const double MIN_ASPECT_RATIO = 0.25;
const double MAX_ASPECT_RATIO = 1.0;

const int MIN_PIXEL_AREA = 80;


const double MIN_DIAG_SIZE_MULTIPLE_AWAY = 0.3;
const double MAX_DIAG_SIZE_MULTIPLE_AWAY = 5.0;

const double MAX_CHANGE_IN_AREA = 0.5;

const double MAX_CHANGE_IN_WIDTH = 0.8;
const double MAX_CHANGE_IN_HEIGHT = 0.2;

const double MAX_ANGLE_BETWEEN_CHARS = 12.0;

const int MIN_NUMBER_OF_MATCHING_CHARS = 3;

const int RESIZED_CHAR_IMAGE_WIDTH = 20;
const int RESIZED_CHAR_IMAGE_HEIGHT = 30;

const int MIN_CONTOUR_AREA = 100;

// external global variables //////////////////////////////////////////////////////////////////////

extern const bool blnShowSteps;
extern cv::Ptr<cv::ml::KNearest>  kNearest;

// function prototypes ////////////////////////////////////////////////////////////////////////////

bool aiTrainData(void);

std::vector<plateHaru> charsHaruKhojne(std::vector<plateHaru> &plateHaruKoVector);

std::vector<PossibleChar> findPossibleCharsInPlate(cv::Mat &imgGrayscale, cv::Mat &threshCrop);

bool checkIfPossibleChar(PossibleChar &possibleChar);

std::vector<std::vector<PossibleChar> > charsKoVectorKoVectorKhojne(const std::vector<PossibleChar> &vectorOfPossibleChars);

std::vector<PossibleChar> findVectorOfMatchingChars(const PossibleChar &possibleChar, const std::vector<PossibleChar> &vectorOfChars);

double distanceBetweenChars(const PossibleChar &firstChar, const PossibleChar &secondChar);

double angleBetweenChars(const PossibleChar &firstChar, const PossibleChar &secondChar);

std::vector<PossibleChar> removeInnerOverlappingChars(std::vector<PossibleChar> &vectorOfMatchingChars);

std::string recognizeCharsInPlate(cv::Mat &threshCrop, std::vector<PossibleChar> &vectorOfMatchingChars);



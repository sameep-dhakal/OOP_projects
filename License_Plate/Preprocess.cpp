
#include "Preprocess.h"

void backGroundJob(cv::Mat &imgOriginal, cv::Mat &imgGrayscale, cv::Mat &threshCrop) {
    imgGrayscale = extractValue(imgOriginal);                          

    cv::Mat imgMaxContrastGrayscale = maximizeContrast(imgGrayscale);       

    cv::Mat imgBlurred;

    cv::GaussianBlur(imgMaxContrastGrayscale, imgBlurred, GAUSSIAN_SMOOTH_FILTER_SIZE, 0);          

                                                                                                   
    cv::adaptiveThreshold(imgBlurred, threshCrop, 255.0, cv::ADAPTIVE_THRESH_GAUSSIAN_C, cv::THRESH_BINARY_INV, ADAPTIVE_THRESH_BLOCK_SIZE, ADAPTIVE_THRESH_WEIGHT);
}

cv::Mat extractValue(cv::Mat &imgOriginal) {
    cv::Mat imgHSV;
    
    
    
    
    std::vector<cv::Mat> vectorOfHSVImages;
    cv::Mat imgValue;

    cv::cvtColor(imgOriginal, imgHSV, cv::COLOR_BGR2HSV);

    cv::split(imgHSV, vectorOfHSVImages);

    imgValue = vectorOfHSVImages[2];

    return(imgValue);
}

cv::Mat maximizeContrast(cv::Mat &imgGrayscale) {
    cv::Mat imgTopHat;
    cv::Mat imgBlackHat;
    cv::Mat imgGrayscalePlusTopHat;
    cv::Mat imgGrayscalePlusTopHatMinusBlackHat;

    cv::Mat structuringElement = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3));

    cv::morphologyEx(imgGrayscale, imgTopHat, cv::MORPH_TOPHAT, structuringElement);
    cv::morphologyEx(imgGrayscale, imgBlackHat, cv::MORPH_BLACKHAT, structuringElement);

    imgGrayscalePlusTopHat = imgGrayscale + imgTopHat;
    imgGrayscalePlusTopHatMinusBlackHat = imgGrayscalePlusTopHat - imgBlackHat;

    return(imgGrayscalePlusTopHatMinusBlackHat);
}





#include "DetectPlates.h"


std::vector<plateHaru> plateHaruKhojne(cv::Mat &ogImage) {
    std::vector<plateHaru> plateHaruKoVector;			

    cv::Mat grayImg;
    cv::Mat threshImg;
    cv::Mat imgContours(ogImage.size(), CV_8UC3, KALO);

    cv::RNG rng;

    cv::destroyAllWindows();



    backGroundJob(ogImage, grayImg, threshImg);       
  
    
    
    
    std::vector<PossibleChar> vectorOfPossibleCharsInScene = findPossibleCharsInScene(threshImg);

    std::vector<std::vector<PossibleChar> > vectorOfVectorsOfMatchingCharsInScene = findVectorOfVectorsOfMatchingChars(vectorOfPossibleCharsInScene);


    for (auto &vectorOfMatchingChars : vectorOfVectorsOfMatchingCharsInScene) {                    
        plateHaru possiblePlate = extractPlate(ogImage, vectorOfMatchingChars);       

        if (possiblePlate.plateCrop.empty() == false) {                                            
            plateHaruKoVector.push_back(possiblePlate);                                       
        }
    }

    std::cout << std::endl << plateHaruKoVector.size() << " possible plates found" << std::endl;       

    return plateHaruKoVector;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
std::vector<PossibleChar> findPossibleCharsInScene(cv::Mat &threshCrop) {
    std::vector<PossibleChar> vectorOfPossibleChars;           

    cv::Mat imgContours(threshCrop.size(), CV_8UC3, KALO);
    int intCountOfPossibleChars = 0;

    cv::Mat imgThreshCopy = threshCrop.clone();

    std::vector<std::vector<cv::Point> > contours;

    cv::findContours(imgThreshCopy, contours, cv::RETR_LIST, cv::CHAIN_APPROX_SIMPLE);        

    for (unsigned int i = 0; i < contours.size(); i++) {               

        PossibleChar possibleChar(contours[i]);

        if (checkIfPossibleChar(possibleChar)) {                
            intCountOfPossibleChars++;                         
            vectorOfPossibleChars.push_back(possibleChar);      
        }
    }

    return(vectorOfPossibleChars);
}


plateHaru extractPlate(cv::Mat &imgOriginal, std::vector<PossibleChar> &vectorOfMatchingChars) {
    plateHaru possiblePlate;            

                                            
    std::sort(vectorOfMatchingChars.begin(), vectorOfMatchingChars.end(), PossibleChar::sortCharsLeftToRight);

    
    double dblPlateCenterX = (double)(vectorOfMatchingChars[0].intCenterX + vectorOfMatchingChars[vectorOfMatchingChars.size() - 1].intCenterX) / 2.0;
    double dblPlateCenterY = (double)(vectorOfMatchingChars[0].intCenterY + vectorOfMatchingChars[vectorOfMatchingChars.size() - 1].intCenterY) / 2.0;
    cv::Point2d p2dPlateCenter(dblPlateCenterX, dblPlateCenterY);

    
    int intPlateWidth = (int)((vectorOfMatchingChars[vectorOfMatchingChars.size() - 1].boundGarneRect.x + vectorOfMatchingChars[vectorOfMatchingChars.size() - 1].boundGarneRect.width - vectorOfMatchingChars[0].boundGarneRect.x) * PLATE_WIDTH_PADDING_FACTOR);

    double intTotalOfCharHeights = 0;

    for (auto &matchingChar : vectorOfMatchingChars) {
        intTotalOfCharHeights = intTotalOfCharHeights + matchingChar.boundGarneRect.height;
    }

    double dblAverageCharHeight = (double)intTotalOfCharHeights / vectorOfMatchingChars.size();

    int intPlateHeight = (int)(dblAverageCharHeight * PLATE_HEIGHT_PADDING_FACTOR);

    
    double dblOpposite = vectorOfMatchingChars[vectorOfMatchingChars.size() - 1].intCenterY - vectorOfMatchingChars[0].intCenterY;
    double dblHypotenuse = distanceBetweenChars(vectorOfMatchingChars[0], vectorOfMatchingChars[vectorOfMatchingChars.size() - 1]);
    double dblCorrectionAngleInRad = asin(dblOpposite / dblHypotenuse);
    double dblCorrectionAngleInDeg = dblCorrectionAngleInRad * (180.0 / CV_PI);

    
    possiblePlate.plateKoLocation = cv::RotatedRect(p2dPlateCenter, cv::Size2f((float)intPlateWidth, (float)intPlateHeight), (float)dblCorrectionAngleInDeg);

    cv::Mat rotationMatrix;             
    cv::Mat imgRotated;
    cv::Mat imgCropped;

    rotationMatrix = cv::getRotationMatrix2D(p2dPlateCenter, dblCorrectionAngleInDeg, 1.0);         

    cv::warpAffine(imgOriginal, imgRotated, rotationMatrix, imgOriginal.size());           

                                                                                            
    cv::getRectSubPix(imgRotated, possiblePlate.plateKoLocation.size, possiblePlate.plateKoLocation.center, imgCropped);

    possiblePlate.plateCrop = imgCropped;            \

    return(possiblePlate);
}


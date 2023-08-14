// DetectChars.cpp

#include "DetectChars.h"

// global variables ///////////////////////////////////////////////////////////////////////////////
cv::Ptr<cv::ml::KNearest> kNearest = cv::ml::KNearest::create();

///////////////////////////////////////////////////////////////////////////////////////////////////
bool aiTrainData(void) {

    // read in training classifications ///////////////////////////////////////////////////

    cv::Mat matClassificationInts;             

    cv::FileStorage fsClassifications("classifications.xml", cv::FileStorage::READ);        // open the classifications file

    if (fsClassifications.isOpened() == false) {                                                        
        
        
        std::cout << "Unable to handle the classifications.xml file" << std::endl;
        return(false);                                                                                 
    }

    fsClassifications["classifications"] >> matClassificationInts;         
    fsClassifications.release();                                           

                                                                           

    cv::Mat matTrainingImagesAsFlattenedFloats;       

    cv::FileStorage fsTrainingImages("images.xml", cv::FileStorage::READ);              

    if (fsTrainingImages.isOpened() == false) {                                                 
        std::cout << "Error, Unable to open the cascade file\n\n";        
        return(false);                                                                         
    }

    fsTrainingImages["images"] >> matTrainingImagesAsFlattenedFloats;           
    fsTrainingImages.release();                                                 

                                                                               

                                                                              
                                                                               
    kNearest->setDefaultK(1);

    kNearest->train(matTrainingImagesAsFlattenedFloats, cv::ml::ROW_SAMPLE, matClassificationInts);

    return true;
}


std::vector<plateHaru> charsHaruKhojne(std::vector<plateHaru> &plateHaruKoVector) {
    cv::Mat imgContours;
    std::vector<std::vector<cv::Point> > contours;
    cv::RNG rng;

    if (plateHaruKoVector.empty()) {              
        return(plateHaruKoVector);                
    }
  

    for (auto &possiblePlate : plateHaruKoVector) {           

        backGroundJob(possiblePlate.plateCrop, possiblePlate.imgGrayscale, possiblePlate.threshCrop);        

        cv::resize(possiblePlate.threshCrop, possiblePlate.threshCrop, cv::Size(), 1.6, 1.6);

        cv::threshold(possiblePlate.threshCrop, possiblePlate.threshCrop, 0.0, 255.0, cv::THRESH_BINARY | cv::THRESH_OTSU);

        std::vector<PossibleChar> vectorOfPossibleCharsInPlate = findPossibleCharsInPlate(possiblePlate.imgGrayscale, possiblePlate.threshCrop);

        std::vector<std::vector<PossibleChar> > vectorOfVectorsOfMatchingCharsInPlate = findVectorOfVectorsOfMatchingChars(vectorOfPossibleCharsInPlate);

        if (vectorOfVectorsOfMatchingCharsInPlate.size() == 0) {               

            possiblePlate.plateChars = "";           
            continue;                               
        }

        for (auto &vectorOfMatchingChars : vectorOfVectorsOfMatchingCharsInPlate) {                                       
            std::sort(vectorOfMatchingChars.begin(), vectorOfMatchingChars.end(), PossibleChar::sortCharsLeftToRight);      
            vectorOfMatchingChars = removeInnerOverlappingChars(vectorOfMatchingChars);                                     
        }

        unsigned int intLenOfLongestVectorOfChars = 0;
        unsigned int intIndexOfLongestVectorOfChars = 0;
       
        for (unsigned int i = 0; i < vectorOfVectorsOfMatchingCharsInPlate.size(); i++) {
            if (vectorOfVectorsOfMatchingCharsInPlate[i].size() > intLenOfLongestVectorOfChars) {
                intLenOfLongestVectorOfChars = vectorOfVectorsOfMatchingCharsInPlate[i].size();
                intIndexOfLongestVectorOfChars = i;
            }
        }
        
        std::vector<PossibleChar> longestVectorOfMatchingCharsInPlate = vectorOfVectorsOfMatchingCharsInPlate[intIndexOfLongestVectorOfChars];


      
        possiblePlate.plateChars = recognizeCharsInPlate(possiblePlate.threshCrop, longestVectorOfMatchingCharsInPlate);
    }   

    return(plateHaruKoVector);
}


std::vector<PossibleChar> findPossibleCharsInPlate(cv::Mat &imgGrayscale, cv::Mat &threshCrop) {
    std::vector<PossibleChar> vectorOfPossibleChars;                           

    cv::Mat imgThreshCopy;

    std::vector<std::vector<cv::Point> > contours;

    imgThreshCopy = threshCrop.clone();				

    cv::findContours(imgThreshCopy, contours, cv::RETR_LIST, cv::CHAIN_APPROX_SIMPLE);      

    for (auto &contour : contours) {                          
        PossibleChar possibleChar(contour);

        if (checkIfPossibleChar(possibleChar)) {                
            vectorOfPossibleChars.push_back(possibleChar);     
        }
    }

    return(vectorOfPossibleChars);
}


bool checkIfPossibleChar(PossibleChar &possibleChar) {
    
    
    if (possibleChar.boundGarneRect.area() > MIN_PIXEL_AREA &&
        possibleChar.boundGarneRect.width > MIN_PIXEL_WIDTH && possibleChar.boundGarneRect.height > MIN_PIXEL_HEIGHT &&
        MIN_ASPECT_RATIO < possibleChar.dblAspectRatio && possibleChar.dblAspectRatio < MAX_ASPECT_RATIO) {
        return(true);
    }
    else {
        return(false);
    }
}


std::vector<std::vector<PossibleChar> > findVectorOfVectorsOfMatchingChars(const std::vector<PossibleChar> &vectorOfPossibleChars) {
    

    std::vector<std::vector<PossibleChar> > vectorOfVectorsOfMatchingChars;             

    for (auto &possibleChar : vectorOfPossibleChars) {                 

                                                                       
        std::vector<PossibleChar> vectorOfMatchingChars = findVectorOfMatchingChars(possibleChar, vectorOfPossibleChars);

        vectorOfMatchingChars.push_back(possibleChar);          

                                                                
        if (vectorOfMatchingChars.size() < MIN_NUMBER_OF_MATCHING_CHARS) {
            continue;                      
        }
       
        vectorOfVectorsOfMatchingChars.push_back(vectorOfMatchingChars);          

                                                                                    
        std::vector<PossibleChar> vectorOfPossibleCharsWithCurrentMatchesRemoved;

        for (auto &possChar : vectorOfPossibleChars) {
            if (std::find(vectorOfMatchingChars.begin(), vectorOfMatchingChars.end(), possChar) == vectorOfMatchingChars.end()) {
                vectorOfPossibleCharsWithCurrentMatchesRemoved.push_back(possChar);
            }
        }
        
        std::vector<std::vector<PossibleChar> > recursiveVectorOfVectorsOfMatchingChars;

      
        recursiveVectorOfVectorsOfMatchingChars = findVectorOfVectorsOfMatchingChars(vectorOfPossibleCharsWithCurrentMatchesRemoved);	

        for (auto &recursiveVectorOfMatchingChars : recursiveVectorOfVectorsOfMatchingChars) {      
            vectorOfVectorsOfMatchingChars.push_back(recursiveVectorOfMatchingChars);              
        }

        break;		
    }

    return(vectorOfVectorsOfMatchingChars);
}

std::vector<PossibleChar> findVectorOfMatchingChars(const PossibleChar &possibleChar, const std::vector<PossibleChar> &vectorOfChars) {
    
    std::vector<PossibleChar> vectorOfMatchingChars;               

    for (auto &possibleMatchingChar : vectorOfChars) {              

                                                                    
        if (possibleMatchingChar == possibleChar) {
           
            continue;          
        }
       
        double dblDistanceBetweenChars = distanceBetweenChars(possibleChar, possibleMatchingChar);
        double dblAngleBetweenChars = angleBetweenChars(possibleChar, possibleMatchingChar);
        double dblChangeInArea = (double)abs(possibleMatchingChar.boundGarneRect.area() - possibleChar.boundGarneRect.area()) / (double)possibleChar.boundGarneRect.area();
        double dblChangeInWidth = (double)abs(possibleMatchingChar.boundGarneRect.width - possibleChar.boundGarneRect.width) / (double)possibleChar.boundGarneRect.width;
        double dblChangeInHeight = (double)abs(possibleMatchingChar.boundGarneRect.height - possibleChar.boundGarneRect.height) / (double)possibleChar.boundGarneRect.height;

       
        if (dblDistanceBetweenChars < (possibleChar.dblDiagonalSize * MAX_DIAG_SIZE_MULTIPLE_AWAY) &&
            dblAngleBetweenChars < MAX_ANGLE_BETWEEN_CHARS &&
            dblChangeInArea < MAX_CHANGE_IN_AREA &&
            dblChangeInWidth < MAX_CHANGE_IN_WIDTH &&
            dblChangeInHeight < MAX_CHANGE_IN_HEIGHT) {
            vectorOfMatchingChars.push_back(possibleMatchingChar);      
        }
    }

    return(vectorOfMatchingChars);        
}


double distanceBetweenChars(const PossibleChar &firstChar, const PossibleChar &secondChar) {
    int intX = abs(firstChar.intCenterX - secondChar.intCenterX);
    int intY = abs(firstChar.intCenterY - secondChar.intCenterY);

    return(sqrt(pow(intX, 2) + pow(intY, 2)));
}


double angleBetweenChars(const PossibleChar &firstChar, const PossibleChar &secondChar) {
    double dblAdj = abs(firstChar.intCenterX - secondChar.intCenterX);
    double dblOpp = abs(firstChar.intCenterY - secondChar.intCenterY);

    double dblAngleInRad = atan(dblOpp / dblAdj);

    double dblAngleInDeg = dblAngleInRad * (180.0 / CV_PI);

    return(dblAngleInDeg);
}


std::vector<PossibleChar> removeInnerOverlappingChars(std::vector<PossibleChar> &vectorOfMatchingChars) {
    std::vector<PossibleChar> vectorOfMatchingCharsWithInnerCharRemoved(vectorOfMatchingChars);

    for (auto &currentChar : vectorOfMatchingChars) {
        for (auto &otherChar : vectorOfMatchingChars) {
            if (currentChar != otherChar) {                         

                if (distanceBetweenChars(currentChar, otherChar) < (currentChar.dblDiagonalSize * MIN_DIAG_SIZE_MULTIPLE_AWAY)) {
                    

                    
                    if (currentChar.boundGarneRect.area() < otherChar.boundGarneRect.area()) {
                       
                        std::vector<PossibleChar>::iterator currentCharIterator = std::find(vectorOfMatchingCharsWithInnerCharRemoved.begin(), vectorOfMatchingCharsWithInnerCharRemoved.end(), currentChar);
                        
                        if (currentCharIterator != vectorOfMatchingCharsWithInnerCharRemoved.end()) {
                            vectorOfMatchingCharsWithInnerCharRemoved.erase(currentCharIterator);      
                        }
                    }
                    else {        
                        std::vector<PossibleChar>::iterator otherCharIterator = std::find(vectorOfMatchingCharsWithInnerCharRemoved.begin(), vectorOfMatchingCharsWithInnerCharRemoved.end(), otherChar);
                       
                        if (otherCharIterator != vectorOfMatchingCharsWithInnerCharRemoved.end()) {
                            vectorOfMatchingCharsWithInnerCharRemoved.erase(otherCharIterator);      
                        }
                    }
                }
            }
        }
    }

    return(vectorOfMatchingCharsWithInnerCharRemoved);
}


std::string recognizeCharsInPlate(cv::Mat &threshCrop, std::vector<PossibleChar> &vectorOfMatchingChars) {
    std::string plateChars;             

    cv::Mat imgThreshColor;

    
    std::sort(vectorOfMatchingChars.begin(), vectorOfMatchingChars.end(), PossibleChar::sortCharsLeftToRight);

    cv::cvtColor(threshCrop, imgThreshColor, cv::COLOR_GRAY2BGR);      

    for (auto &currentChar : vectorOfMatchingChars) {          
        cv::rectangle(imgThreshColor, currentChar.boundGarneRect, HARIYO, 2);      

        cv::Mat imgROItoBeCloned = threshCrop(currentChar.boundGarneRect);                

        cv::Mat imgROI = imgROItoBeCloned.clone();      

        cv::Mat imgROIResized;
       
        cv::resize(imgROI, imgROIResized, cv::Size(RESIZED_CHAR_IMAGE_WIDTH, RESIZED_CHAR_IMAGE_HEIGHT));

        cv::Mat matROIFloat;

        imgROIResized.convertTo(matROIFloat, CV_32FC1);        

        cv::Mat matROIFlattenedFloat = matROIFloat.reshape(1, 1);      

        cv::Mat matCurrentChar(0, 0, CV_32F);                   

        kNearest->findNearest(matROIFlattenedFloat, 1, matCurrentChar);     

        float fltCurrentChar = (float)matCurrentChar.at<float>(0, 0);       

        plateChars = plateChars + char(int(fltCurrentChar));        
    }
    return(plateChars);               // return result
}


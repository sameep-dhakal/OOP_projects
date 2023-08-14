
#include "Main.h"
using namespace std;

int main(void) {

    bool aiTrain = aiTrainData();           

    if (aiTrain == false) {                           
                                                                       
        cout <<"AI TRAINING NOT SUCCESSFULL" <<endl;
        return 0;                                                     
    }

    cv::Mat ogImage;          


    ////////////////////////////////////// IMAGE INPUT HERE ////////////////////////////////////    
    string filename = "res/image1.png";


    ogImage = cv::imread(filename, cv::IMREAD_COLOR);        

    if (ogImage.empty()) {                             
        cout << "Could not find/read image from the file"<< endl;
        return 0;                                             
    }

    std::vector<plateHaru> plateHaruKoVector = plateHaruKhojne(ogImage);         

    plateHaruKoVector = charsHaruKhojne(plateHaruKoVector);                              

    cv::imshow("ogImage", ogImage);          

    if (plateHaruKoVector.empty()) {                                              
        cout << "No license plates were detected" <<endl;       
    }
    else {                                                                            
                                                                                     
                                                                                 
       sort(plateHaruKoVector.begin(), plateHaruKoVector.end(), plateHaru::charsSortDesc);

        
        plateHaru plateObj = plateHaruKoVector.front();

        cv::imshow("plateCrop", plateObj.plateCrop);            
        cv::imshow("threshCrop", plateObj.threshCrop);

        if (plateObj.plateChars.length() == 0) {                                                      
            cout<< "No readable/recognized characters were detected" <<endl;      
            return(0);                                                                             
        }

       ratoBaksaBanaune(ogImage, plateObj);                

        cout << "license plate read from image = " << plateObj.plateChars <<endl;  

        ogImageMaLekhne(ogImage, plateObj);             

        cv::imshow("ogImage", ogImage);                       

        cv::imwrite("ogImage.png", ogImage);                 
    }

    cv::waitKey(0);                

    return(0);
}

void ratoBaksaBanaune(cv::Mat &ogImage, plateHaru &plateObj) {
    cv::Point2f p2fRectPoints[4];

    plateObj.plateKoLocation.points(p2fRectPoints);           

    for (int i = 0; i < 4; i++) {                                      
        cv::line(ogImage, p2fRectPoints[i], p2fRectPoints[(i + 1) % 4], RATO, 2);
    }
}

void ogImageMaLekhne(cv::Mat &ogImage, plateHaru &plateObj) {
    cv::Point ptCenterOfTextArea;                  
    cv::Point ptLowerLeftTextOrigin;                

    int intFontFace = cv::FONT_HERSHEY_COMPLEX;                             
    double dblFontScale = (double)plateObj.plateCrop.rows / 30.0;            
    int intFontThickness = (int)std::round(dblFontScale * 1.5);            
    int intBaseline = 0;

    cv::Size textSize = cv::getTextSize(plateObj.plateChars, intFontFace, dblFontScale, intFontThickness, &intBaseline);     

    ptCenterOfTextArea.x = (int)plateObj.plateKoLocation.center.x;         

    if (plateObj.plateKoLocation.center.y < (ogImage.rows * 0.75)) {      
                                                                                          
        ptCenterOfTextArea.y = (int)std::round(plateObj.plateKoLocation.center.y) + (int)std::round((double)plateObj.plateCrop.rows * 1.6);
    }
    else {                                                                               
                                                                                         
        ptCenterOfTextArea.y = (int)std::round(plateObj.plateKoLocation.center.y) - (int)std::round((double)plateObj.plateCrop.rows * 1.6);
    }

    ptLowerLeftTextOrigin.x = (int)(ptCenterOfTextArea.x - (textSize.width / 2));           
    ptLowerLeftTextOrigin.y = (int)(ptCenterOfTextArea.y + (textSize.height / 2));          

                                                                                            
    cv::putText(ogImage, plateObj.plateChars, ptLowerLeftTextOrigin, intFontFace, dblFontScale, PAHELO, intFontThickness);
}



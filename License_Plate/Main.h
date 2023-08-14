#pragma once 

#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>

#include "DetectPlates.h"
#include "PossiblePlates.h"
#include "DetectChars.h"

#include<iostream>        


// global constants ///////////////////////////////////////////////////////////////////////////////
const cv::Scalar KALO = cv::Scalar(0.0, 0.0, 0.0);
const cv::Scalar SETO = cv::Scalar(255.0, 255.0, 255.0);
const cv::Scalar PAHELO = cv::Scalar(0.0, 255.0, 255.0);
const cv::Scalar HARIYO = cv::Scalar(0.0, 255.0, 0.0);
const cv::Scalar RATO = cv::Scalar(0.0, 0.0, 255.0);

// function prototypes ////////////////////////////////////////////////////////////////////////////
int main(void);
void ratoBaksaBanaune(cv::Mat &ogImage, plateHaru &plateObj);

void ogImageMaLekhne(cv::Mat &ogImage, plateHaru &plateObj);



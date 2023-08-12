#ifndef STUDENTBOOKCHOOSE_H
#define STUDENTBOOKCHOOSE_H
#include "StudentInput.h"
#include <iostream>
#include<string>
#include <vector>
#include<fstream>
using namespace std;

class displayBookChoice{
         public:
         string displayChoice(){
         StudentDetailsInput student;
         student.inputStudentFDetails();
         cout<<"Enter which book you want to choose  "<<student.getStudentName()<<endl;

         ofstream choiceFile("../txt file/ChoiceFile.txt", ios:: app);
         choiceFile << " Welcome to your Dashboard " <<student.getStudentName() << endl<<"Your Roll Number is "<< student.getStudentRoll_no()<<endl<<"Your choosen book are: "<<endl;
         cout<<"Your Choosen Book Details "<<endl;

         ifstream BookDetails("../txt file/BookDetails.txt");
         ofstream ChoiceFile("../txt file/ChoiceFile.txt", ios::app);
         string readBookDetails;
         if(BookDetails.is_open() && ChoiceFile.is_open()){
                  //read book details
                  while(getline(BookDetails,readBookDetails)){
                           //write book details
                           ChoiceFile << readBookDetails<<endl;
                  }
                  //close book details file
                  BookDetails.close();
                  ChoiceFile.close();
         }
         else{
                  cout<<"Files not opened correctly"<<endl;
         }
                  return " choiceFile.txt";
}
};

#endif
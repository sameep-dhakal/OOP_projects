#ifndef STUDENTINPUT_H
#define STUDENTINPUT_H
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;
class StudentDetailsInput
{
private:
         string name;
         int roll_no;

public:
         void setStudentDetails(string n, int r)
         {
                  name = n;
                  roll_no = r;
         }

         void inputStudentFDetails()
         {
                  cout << "Enter your name: " << endl;
                  cin.ignore();
                  getline(cin, name);

                  cout << "Enter your roll_no: " << endl;
                  cin >> roll_no;
         }

         string getStudentName()
         {
                  return name;
         }

         int getStudentRoll_no()
         {
                  return roll_no;
         }

         void getStudentDetails()
         {
                  getStudentName();
                  getStudentRoll_no();
         }
};

#endif
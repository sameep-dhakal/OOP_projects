#ifndef SHOWBOOKLIST_H
#define SHOWBOOKLIST_H
#include<iostream>
#include<string>
#include<vector>
#include<fstream>
using namespace std;
void ShowBookList(){
vector<string> BookLists;

ifstream  BookList("../txt file/ChoiceFile.txt", ios::app);
string line;

if(BookList.is_open()){
         while(getline(BookList, line)){
                  BookLists.push_back(line);
         }

         for(int i=0; i<BookLists.size();i++){
                  cout<< BookLists[i] <<endl;
         }
} 
else{
         cout<< "Unable to open file"<< endl;
}
BookList.close();
}
 #endif


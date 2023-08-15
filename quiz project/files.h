#ifndef FILEHANDLE_H
#define FILEHANDLE_H
#include"randomgenerator.h"
#include<iostream>
#include<fstream>
#include<cctype>
#include<vector>
class quiz{
	public:
		string question,op1,op2,op3,op4;
		char correctop;
		void getdata()
		{
			cout<<"enter the question followed by ?";
			cin.ignore();
			getline(cin,question);
			cout<<"\nenter the option 'a':";
			getline(cin,op1);
			cout<<"\nenter the option 'b':";
			getline(cin,op2);
			cout<<"\nenter the option 'c':";
			getline(cin,op3);
			cout<<"\nenter the option 'd':";
			getline(cin,op4);
			cout<<"\nenter the correct option:";
			cin>>correctop;
		}
		void showdata()
			{ static int i=1;
			cout<<i<<"."<<question<<endl;i++;
			cout<<"a."<<op1<<"\t\tb."<<op2<<endl<<"c."<<op3<<"\t\td."<<op4<<endl<<endl;}
	//		void add2file();
};
void add2file()
{	int n,j;
	cout<<"how many question you want to add";
	cin>>n;
	quiz q[n];
	fstream question_adder("question.txt",ios::app|ios::out);
	fstream op1_adder("op1.txt",ios::app|ios::out);
	fstream op2_adder("op2.txt",ios::app|ios::out);
	fstream op3_adder("op3.txt",ios::app|ios::out);
	fstream op4_adder("op4.txt",ios::app|ios::out);
	fstream cop_adder("cop.txt",ios::app|ios::out);
	
	for(j=0;j<n;j++)
		{
			q[j].getdata();
			 question_adder<<q[j].question<<endl;
			 op1_adder<<q[j].op1<<endl;
			 op2_adder<<q[j].op2<<endl;
			 op3_adder<<q[j].op3<<endl;
			 op4_adder<<q[j].op4<<endl;
			 cop_adder<<q[j].correctop<<endl;	 
		}
		question_adder.close();
		op1_adder.close();
		op2_adder.close();
		op3_adder.close();
		op4_adder.close();
		cop_adder.close();
		
}
void extractfromfile()
{
	std::ifstream test("question.txt"); // open the file
    int count = 0,i; // initialize the counter
    std::string line; // declare a string variable to store each line
    while (std::getline(test, line)) // read each line until end of file
    {
        count++; // increment the counter
    }
    test.close();
    fstream getquestion("question.txt",ios::app|ios::in);
	fstream getop1("op1.txt",ios::app|ios::in);
	fstream getop2("op2.txt",ios::app|ios::in);
	fstream getop3("op3.txt",ios::app|ios::in);
	fstream getop4("op4.txt",ios::app|ios::in);
	fstream getcop("cop.txt",ios::app|ios::in);	
    quiz q[count];
    for(i=0;i<count;i++)
    {
			getline(getquestion,q[i].question);
			getline(getop1,q[i].op1);
			getline(getop2,q[i].op2);
			getline(getop3,q[i].op3);
			getline(getop4,q[i].op4);
			getcop>>q[i].correctop;
			q[i].showdata();
	}
	getquestion.close();
	getop1.close();
	getop2.close();
	getop3.close();
	getop4.close();
	getcop.close();
    
}
void playquiz()
{	char name[50],userchoice;
std::ifstream test("question.txt"); // open the file
    int count = 0,i,no=1,score=0,totalscore=0; // initialize the counter
    std::string line; // declare a string variable to store each line
    while (std::getline(test, line)) // read each line until end of file
    {
        count++; // increment the counter
    }
    test.close();
    fstream getquestion("question.txt",ios::app|ios::in);
	fstream getop1("op1.txt",ios::app|ios::in);
	fstream getop2("op2.txt",ios::app|ios::in);
	fstream getop3("op3.txt",ios::app|ios::in);
	fstream getop4("op4.txt",ios::app|ios::in);
	fstream getcop("cop.txt",ios::app|ios::in);	
    quiz quizarray[count];
    for(i=0;i<count;i++)
    {
			getline(getquestion,quizarray[i].question);
			getline(getop1,quizarray[i].op1);
			getline(getop2,quizarray[i].op2);
			getline(getop3,quizarray[i].op3);
			getline(getop4,quizarray[i].op4);
			getcop>>quizarray[i].correctop;
	}
	getquestion.close();
	getop1.close();
	getop2.close();
	getop3.close();
	getop4.close();
	getcop.close();
	std::srand(static_cast<unsigned int>(std::time(0))); 
    int numValues = count;
    std::vector<int> randomArray = generateRandomValues(numValues);
    cout<<"Enter your name\n";
    cin>>name;
    for(i=0;i<10;i++){
		//quizarray[i].showdata();
    	cout<<no<<"."<<quizarray[randomArray[i]].question<<endl;
			cout<<"a."<<quizarray[randomArray[i]].op1<<"\t\tb."<<quizarray[randomArray[i]].op2<<endl;
			cout<<"c."<<quizarray[randomArray[i]].op3<<"\t\td."<<quizarray[randomArray[i]].op4<<endl;
			cout<<"enter your answer(a/b/c/d):";no++;
			cin>>userchoice;
			userchoice=tolower(userchoice);
			if(userchoice==quizarray[randomArray[i]].correctop){
				cout<<"Correct answer!!!!!!\n";score=score+10;
			}
			else{
				cout<<"Incorrect answer!!!\nThe correct answer was option"<<quizarray[randomArray[i]].correctop;
			}}
			system("cls");
			cout<<"**********************SCORE CARD**********************\n";
			cout<<"Name:"<<name<<endl;
			cout<<"Score:"<<score<<endl;
			if(score<=50){
				cout<<"Remark:you qualified for becoming roadpati!!!!!\n";
			}
			else if(score<=80){
				cout<<"Good but can be better!!!!!\n";
			}	
			else if(score>80){
				cout<<"You have potential to become crorepati!!!!\n";
			}
			else cout<<"Error while processing data!!!!!\n";   
}
#endif

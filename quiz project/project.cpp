#include<iostream>
#include<fstream>
#include<string.h>
#include <cwchar>
#include <windows.h>
#include"userlogin.h"
#include"files.h"
#include <cstdlib>
#include <stdlib.h>
using namespace std;
BOOL SetConsoleFontSize (COORD dwFontSize) {
  HANDLE output = GetStdHandle (STD_OUTPUT_HANDLE);
  CONSOLE_FONT_INFOEX info {sizeof (CONSOLE_FONT_INFOEX)};
  if (!GetCurrentConsoleFontEx (output, false, &info))
    return false;
  info.dwFontSize = dwFontSize;
  return SetCurrentConsoleFontEx (output, false, &info);
}
int main()
{	int choice;  
	SetConsoleFontSize ({0, 28});
	system("Color 0A");
open:	system ("cls");
	cout<<"\t\t\t\t*************WELCOME TO KO BANCHA ROADPATI*************"<<endl;
 	cout<<"which mode do you want to use?"<<endl;
	cout<<"------->press 1 for admin"<<endl;
	cout<< "------->press 2 for taking the quiz"<<endl;
	cout<<"------->press3 to terminate"<<endl<<"your choice:";
 	cin>>choice;
 	system ("cls");
 	switch(choice)
 	{
abc:	case 1:
		{ 		int ch;
				cout<<"\t\t\t\t*************WELCOME TO USER LOGIN INTERFACE*************"<<endl;
 				cout<<"------->press 1 for login"<<endl;
				cout<<"------->press 2 for creating new account"<<endl;
				cout<<"------->press 3 to return to previous page"<<endl;
				cout<<"\nYour choice:";
				cin>>ch;
					switch(ch)
					{
						case 1:
							{	int loginch;
							system ("cls");
								cout<<"\t\t\t\t*************WELCOME TO USER LOGIN INTERFACE*************"<<endl;
								cout<<"Enter your username and password"<<endl;
								UserLoginSection u1;
								u1.LoginAccount();
								if(u1.isLoginSuccessful())
								{
									cout<<"\t\t***********welcome user**********\n";
									cout<<"---------->press 1 to add questions"<<endl;
									cout<<"---------->press 2 to view questions"<<endl;
									cout<<"---------->press 3 to return to previous page"<<endl;
									cout<<"your choice:";
									cin>>loginch;
									switch(loginch)
										{
											case 1:
												{
													add2file();
													cout<<"Thank you for adding questions to our database"<<endl;
													cout<<"press 1 to return to previous page:";
													cin>>loginch;
													if (loginch==1) goto open;
													break;
													
												}
											case 2:
												{	int loginch;
													system("cls");
													cout<<"\t\t\t*********WELCOME TO OUR QUESTIONS DATABASE***********\n";
													extractfromfile();
													cout<<"press 1 to return to previous page:";
													cin>>loginch;
													if (loginch==1)goto open;
													break;
												}
											case 3:
												{goto open;
												break;}
										}
										loginch=0;
										cout<<"press 1 to continue and 0 to exit";
										if(loginch==1) goto open;	
								}
								break;
							}
						case 2:
							{	system ("cls");
								int yes=0;
								cout<<"\t\t\t\t*************WELCOME TO USER LOGIN INTERFACE*************"<<endl;
								UserLoginSection e1;
          						e1.CreateAccount();
					         	cout<<"Do you want to continue(press 1 for yes):";
					         	cin>>yes;
					         	if(yes==1){ goto abc;}
					         	break;
							}
						case 3:
							{
								goto open;
								break;
							}		
				break;
		 }
	 }
	 case 2:
	 	{	int ch;
	 		playquiz();
	 		cout<<"\ndo you want to play again(press 1 for yes):";
	 		cin>>ch;
	 		if(ch==1) goto open;
	 		break;
		}
	 	
 	
	//add2file();
	//extractfromfile();
	return 0;
}}

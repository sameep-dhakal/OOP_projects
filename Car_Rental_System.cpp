#include <iostream>
#include <string>
#include <fstream>
using namespace std;


//Global Declearation 
//definig the number of cars!
int tesla_num=3, ford_num=5, toyota_num=4,nexon_num=3,lamborghini_num=2;
//definig the rates of each cars!
float tesla_rate=100, ford_rate=50, toyota_rate=30,nexon_rate=15,lamborghini_rate=200;


class CarRent{
	//private Data Members
    string carName;
    int availableCars;
    float rentalCost;

    
protected:
    int carnumber,days,option,i;
	float rate;
	string name;
	fstream file;

public:
	//default constructor
    CarRent() : i(0), carName("None"), availableCars(0), rentalCost(0.0) {}
	
	//parameterized Constructor
    CarRent(int i1, string carName1, int availableCars1, float rentalCost1) :i(i1), carName(carName1), availableCars(availableCars1), rentalCost(rentalCost1) {}
	
	void user_ko_nam(){
		cout<<"\n\n\nEnter Your Name: ";
    	cin>>name;
    	
	}

	
    void display() {
        cout <<i<<".  Car Name: " << carName;
        cout << "   Available Cars: " << availableCars;
        cout << "   Rental Cost: $" << rentalCost << endl;
    }
    
    //choice function (BRAIN OF THE PROGRAM)
    //For Electric Car
    void electric_car(){
    
    		
				CarRent C1(1, "Tesla", tesla_num, tesla_rate);
				CarRent C2(2, "Nexon", nexon_num, nexon_rate);
				C1.display();
		    	C2.display();
		    	
		    		file.open("car.txt", ios::app);
		    		if (!file) {
		        		cout << "Error: Unable to open the file." << endl;
		        		exit(0);
		    		}else{
					
					cout<<"\nWhich Car You Want To Rent? ";
		    		cin>>carnumber;
		    		//Renting Tesla Car
		    			if(carnumber==1){
		    				if(tesla_num==0){
		    					cout<<"\nThere are no Tesla Cars to rent!";
							}else{
		    					tesla_num--;
		    					cout<<"\nEnter Number Of Days.";
		    					cin>>days;
		    					rate=days*tesla_rate;
		    					
								cout<<"\nThe Car You Rented is Tesla for "<<days<<" Days, Costing - $"<<rate<<endl;
								//writing the information in a file
		    					file<<"\nThe Car Rented is - Tesla for - "<<days<<" Days, Costing - $"<<rate<<endl;
		    				}
		    		//Renting Nexon Car	
		    			}else if(carnumber==2){
		    				if(nexon_num==0){
		    					cout<<"\nThere are no Nexon Cars to rent!";
							}else{
		    					nexon_num--;
		    					cout<<"\nEnter Number Of Days.";
		    					cin>>days;
		    					rate=days*nexon_rate;
		    					
		    					cout<<"\nThe Car You Rented is Nexon for "<<days<<" Days, Costing - $"<<rate<<endl;
								//writing the information in a file
		
		    					file<<"\nCar Rented is - Nexon for - "<<days<<" Days, Costing - $"<<rate<<endl;
		    				}
		    			
		    			}else{
		    				cout<<"\nError!!";
						}
		    			
							
						
	
		    	}
				cout<<"\nDo you Want to rent another car? '1' For YES '0' For NO ";
		    	cin>>option;
		    	if(option==1){
		    		choose_again();
				}else{
					cout<<"\nThank You";
				}

				file.close();
				
			
    	
	}
	
   //For Dieseal Car!
	
	 void dieseal_car(){
    	
    	
    	
				CarRent C3(1, "Toyota",toyota_num, toyota_rate);
		    	CarRent C4(2, "Ford", ford_num, ford_rate);
				CarRent C5(3, "Lamborghini ", lamborghini_num, lamborghini_rate);
				C3.display();
		    	C4.display();
		    	C5.display();
		    	
		    		file.open("car.txt", ios::app);
		    		if (!file) {
		        		cout << "Error: Unable to open the file." << endl;
		        		exit(0);
		    		}else{
					
					
					
		    		cout<<"\nWhich Car You Want To Rent? ";
		    		cin>>carnumber;
		    		//Renting a Toyota!
		    			if(carnumber==1){
		    				if(toyota_num==0){
		    					cout<<"\nThere are no Toyota Cars to rent!";
							}else{
		    					--toyota_num;
		    					cout<<"\nEnter Number Of Days.";
		    					cin>>days;
		    					rate=days*toyota_rate;
		    					
								cout<<"\nThe Car You Rented is Toyota for "<<days<<" Days, Costing - $"<<rate<<endl;
								//writing the information in a file
		    					file<<"\nThe Car Rented is - Toyota for - "<<days<<" Days, Costing - $"<<rate<<endl;
		    				}
		    		//Renting Ford		
		    			}else if(carnumber==2){
		    				if(ford_num==0){
		    					cout<<"\nThere are no Ford Cars to rent!";
							}else{
		    					--ford_num;
		    					cout<<"\nEnter Number Of Days.";
		    					cin>>days;
		    					rate=days*ford_rate;
		    					
		    					cout<<"\nThe Car You Rented is Ford for "<<days<<" Days, Costing - $"<<rate<<endl;
								//writing the information in a file
		
		    					file<<"\nThe Car Rented is - Ford for - "<<days<<" Days, Costing - $"<<rate<<endl;
		    				}
		    		//Renting Lambo		
		    			}else if(carnumber==3){
		    				if(lamborghini_num==0){
		    					cout<<"\nThere are no Tesla Cars to rent!";
							}else{
		    					--lamborghini_num;
		    					cout<<"\nEnter Number Of Days.";
		    					cin>>days;
		    					rate=days*lamborghini_rate;
		    					cout<<"\nThe Car You Rented is Lamborghini for "<<days<<" Days, Costing $"<<rate<<endl;
								
								//writing the information in a file
								
		    					file<<"\nThe car Rented is - Lamborghini for - "<<days<<" Days, Costing - $"<<rate<<endl;
		    				
							}
		    			}else{
		    				
		    				cout<<"\nError!!";
						}
						
		    		
		    	

		    	}
		    			    		
				cout<<"\nDo you Want to rent another car? '1' For YES '0' For NO ";
		    	cin>>option;
		    	if(option==1){
		    		choose_again();
				}else{
					cout<<"\nThank You";
				}
				file.close();
				

				
		
	}
void choose_again();
};

	void CarRent::choose_again(){
	
	int kun_car_chayo; CarRent car;
	cout<<"\nDo you want to rent Electric Car Or Dieseal Car";
    cout<<"\n1 == Electric";
    cout<<"\n2 == Dieseal\n";
    cin>>kun_car_chayo;
    
    if(kun_car_chayo==1){
    	car.electric_car();
	}else if(kun_car_chayo==2){
		car.dieseal_car();
	}else{
		cout<<"\nError!";
	}
	
}
//ACE078BCT071 SOHAN MEHTA
//ACE078BCT074 SUBRAT HUMAGAI

int main(){
	
    string name;
    CarRent car;
    cout<<"\n****CAR RENTAL SYSTEL****\n";
    car.user_ko_nam();
    car.choose_again();
    return 0;
}


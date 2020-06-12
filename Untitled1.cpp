#include <iostream>
#include <conio.h>
#include <fstream>
#include <string.h>
#include <time.h>
#include <stdlib.h>

using namespace std;

struct customerdata{									//struct customerdata
	char name[30];
	char id[30];
	char phone[30];
	char room[30];
	int numday;
	float price;
};

void getinput(customerdata room[],int x)				//get the input to fill customerdata room[]
{
	ifstream in;
	in.open("getinput.txt");							//open the inout file getinput.txt
	if(!in)
	{
		cout << "Error. 'getinput.txt doesn't exist." << endl;
		exit (EXIT_FAILURE);
	}
	for(int i = 0; i < x; i++)							//loop the input from getinput.txt. The amount of loop is based on x.
	{
		in.getline(room[i].name,30,';');
		in.getline(room[i].id,30,';');
		in.getline(room[i].phone,30,';');
		in.getline(room[i].room,30,';');
		in >> room[i].numday;
		room[i].price = room[i].numday * 80;
		in.ignore();
	}
	in.close();											//close the getinput.txt
}

void promptsearch(customerdata room[],int x)     //used to search for inhabitant details based off of ID
{
	char answer = 'Y',searchid[30];
	
	
	while(answer=='Y' || answer=='y')			//Pressing "y" initiates a search algorithm to look for the id input
	{
		cout << "Would you like to search the occupant's data [Y/N]?" << endl;
		cin >> answer;
		if(answer == 'y' || answer == 'Y')		// Inputting "y" start the loop
		{
			cout << "Enter the occupant's id: ";  //details based off of ID
			cin >> searchid;
			cout << endl;
			for(int i=0;i<x;i++)
			{
				if(strcmp(searchid,room[i].id)==0) // compares searchid with room[i] ID
				{
					cout << "Name: " << room[i].name << endl;
					cout << "ID: " << room[i].id << endl;
					cout << "Phone no.: " << room[i].phone << endl;
					cout << "Room no.: " << room[i].room << endl;
					cout << "No. of day: " << room[i].numday << endl;
					cout << "Price: " << room[i].price << endl;
					cout << "\n===========================\n" << endl;
				}
			}
		}
		else if(answer == 'n' || answer == 'N')    // Pressing "n" ends the loop
		{
			cout << "Thank you. Have a nice day." << endl; //byebye message
		}
	}
}
	
void minmax(customerdata room[],int x,int& max, int& min, int& counthigh, int& countlow)			//find the min and max & counthigh and countlow
{
	for(int i=1;i<x;i++)								//loop to find the max and min
	{
		if(room[i].numday > max)
		{
			max = room[i].numday;
		}
		if(room[i].numday < min)
		{
			min = room[i].numday;
		}
	}
}

void averagetotal(customerdata room[],int x,float& total,float& average)					//count and display the total price and average price
{
	for(int i=0;i<x;i++)
	{
		total += room[i].price;												//count total price
	}
	average = total/x;														//calculate average price
}

void sort(customerdata room[], int x)										//sort the room[] index position based on lowest numday to highest numday
{
	customerdata temp;
	for(int j = x-1; j>=0 ; j--)
	{
		for(int i = 0; i<j; i++)
		{
			if(room[i].price > room[i+1].price)
			{
				temp = room[i];
				room[i] = room[i+1];
				room[i+1] = temp;
			}
		}
	}
}

void printreceipt(customerdata room[],int x,float total,float average, int max, int min, int counthigh, int countlow)					//output the data to printreceipt.txt
{
	char date[9];
	_strdate(date);
	ofstream out;															
	out.open("printreceipt.txt");											//open the output file printreceipt.txt
	
	out<<"*************************************************************************"<<endl;
    out<<"*                              MUHADIB HOTEL                            *"<<endl;
    out<<"*                    -------------------------------                    *"<<endl;
    out<<"*                                                                       *"<<endl;
    out<<"*            HERE ARE THE CUSTOMER DETAILS BASED ON YOUR INPUT          *"<<endl;
    out<<"*                               "<<date<<"                                *"<<endl;
    out<<"*                  ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^                   *"<<endl;
    out<<"*                     THANKS FOR YOUR COOPERATION                       *"<<endl;
    out<<"*                  ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^                   *"<<endl;
    out<<"*************************************************************************"<<endl << endl << endl;
    
	for(int i=0;i<x;i++)
	{
		out << "No: " << i+1 << endl;
		out << "Name: " << room[i].name << endl;
		out << "ID: " << room[i].id << endl;
		out << "Phone no.: " << room[i].phone << endl;
		out << "Room no.: " << room[i].room << endl;
		out << "No. of day: " << room[i].numday << endl;
		out << "Price: " << room[i].price << endl;
		out << "---------------------------------------------" << endl;
	}
	out << "==============================================" << endl;
	out << "Total collection: " << total << endl;
	out << "Average collection: Rm " << average << endl;
	out << "==============================================" << endl;
	
	out << "Occupant with the highest number of stay:  " << endl;			//display the people with the highest numday
	for(int i=0;i<x;i++)
	{
		if(room[i].numday == max)
		{
			out << room[i].name;
			counthigh++;													//increment counthigh if requirement met to find the amount of people that have the highest numday
			out << endl;
		}
	}
	out << "----------------------------------------------" << endl;
	
	out << "Occupant with the lowest number of stay:  " << endl;			//display the people with the lowest numday
	for(int i=0;i<x;i++)
	{
		if(room[i].numday == min)
		{
			out << room[i].name;
			countlow++;														//increment countlow if requirement met to find the amount of people that have the lowest numday
			out << endl;
		}
	}
	out << "----------------------------------------------" << endl; 
	
	out << "No. of people with the highest stay: " << counthigh << endl;	//display the counthigh
	out << "No. of people with the lowest stay: " << countlow << endl;		//display rhe countlow

	out << "==============================================" << endl;
	
	out.close();															//close the printreceipt.txt
}

int main()
{
	int x;
	float total;
	float average;
	
	cout<<"*************************************************************************"<<endl;
    cout<<"*                              MUHADIB HOTEL                            *"<<endl;
    cout<<"*                    -------------------------------                    *"<<endl;
    cout<<"*               *Make sure the input is in the order of:                *"<<endl;
    cout<<"*            Name;id;phone number;room number;number of stay            *"<<endl;
    cout<<"*                                                                       *"<<endl;
    cout<<"*                  ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^                   *"<<endl;
    cout<<"*                     THANKS FOR YOUR COOPERATION,                      *"<<endl;
    cout<<"*                  ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^                   *"<<endl;
    cout<<"*************************************************************************"<<endl << endl << endl;
    
	cout << "Enter how many data entered: ";								//get the amount of number of people to determine the amount of loop in loop insteuction
	cin >> x;
	
	customerdata room[x];													//declare the array size of room based on the amount of x
	
	getinput(room,x);														//call getinput function to get the input from input file
	
	promptsearch(room,x);													//Calls promptsearch function to search for inhabitant details based off of ID
	
	int max = room[0].numday;												//set the first value as max
	int min = room[0].numday;												//set the first value as min
	int counthigh=0, countlow=0;											//declare and initialize count for high and low to find the amount of room with the highest and lowest numday
	
	averagetotal(room,x,total,average);										//calculate the total and average price
	sort(room,x);															//sort the room[] from the lowest price to the highest price
	minmax(room,x,max,min,counthigh,countlow);								//call minmax function to get the min and max numday and count the amount of people that have the min and max numday
	printreceipt(room,x,total,average,max,min,counthigh,countlow);			//print the data to an ouput file, printreceipt.txt
}

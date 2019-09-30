#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "strutils.h"

using namespace std;
bool isTimeTrue(string & time)
{
	bool isInt=false;
	int count=0;

	for(unsigned int i=0; i <2; i++)					//Checking first two
	{
		if(time.substr(i,1) <= "9" && time.substr(i,1) >= "0")
		{
			count++;
		}
	}
	for(unsigned int i=3; i <5; i++)				//checking last two
	{
		if(time.substr(i,1) <= "9" && time.substr(i,1) >= "0")
		{
			count++;
		}
	}
	if(time.substr(2,1) ==":")				
	{
		count++;
	}
	if(time.length()==5)			//checking length
	{
		count++;
	}
	if(count==6)					//checking is all conditions are true or not
	{
		isInt=true;
	}
	return isInt;

}
void outpt(istringstream &Routestream,ofstream &output,ifstream &inputTimes,int number,int TimeHour,int TimeMin,string Routeloc)		//if the departure loc equals to route in routes.txt this function will be calles
{
		string routeEnd;
		int HourCheck,MinCheck;
		Routestream>>routeEnd;		// taking from the routes.txt to write in output 
		inputTimes.clear();			// we need to start over every time that it come back to times because every time we come here we will look till the end of the txt
		inputTimes.seekg(0);	
		string lineT="";
		while(getline(inputTimes,lineT))				
		{
			int numberTime=0;
			istringstream inputTimestream(lineT);
			inputTimestream>>numberTime;
			if(number==numberTime)			// checking if the codes of busses are equal or not
			{
					
				string times;
				inputTimestream>>times;
				HourCheck=atoi(times.substr(0,2));	// to check the start time  that user gave
				MinCheck=atoi(times.substr(3,2));
				if(HourCheck>TimeHour)
						output<<Routeloc<<" "<<routeEnd<<" "<<times<<endl;		
				else if(HourCheck== TimeHour && MinCheck>TimeMin)
						output<<Routeloc<<" "<<routeEnd<<" "<<times<<endl;


				}



			}

}


void routescontrol(ifstream &Routes,ofstream &output,ifstream &inputTimes,int TimeHour,int TimeMin,string Deploc)
{
	string line;
		Routes.clear();			// we need to start over every time that it come back to times because every time we come here we will look till the end of the txt
		Routes.seekg(0);
	while(getline(Routes,line))				//gets first line of routes.txt
	{
		string Routeloc="";
		int number=0;
		istringstream Routestream(line);	//seperating first line
		Routestream>>number;				// reading code of bus
		Routestream>>Routeloc;				// to look if its equal to our departure loc

	if(Routeloc==Deploc)					// if its equal it will go for outpt function and look to the times.txt
	{
		outpt(Routestream,output,inputTimes,number,TimeHour,TimeMin,Routeloc);
	}
	}
}

int main ()
{
	int TimeHour,TimeMin;											// for the entered start time of travel
	string inputRoute,inpTimes,Time,DepLoc="";						//inputRoute is for the Routes input file ,  time is for the start time of travel , deploc is for departue location
	ifstream inputTimes;
	ifstream Routes;
	
	do
	{
	cout<<"Please enter a filename for route database: ";
	cin>>inputRoute;
	Routes.open(inputRoute.c_str());
		if(Routes.fail())
			cout<<"cannot open routes database file"<<endl;
	}while(Routes.fail());

	do
	{
	cout<<"Please enter a filename for time database: ";
	cin>>inpTimes;
	inputTimes.open(inpTimes.c_str());
	if(inputTimes.fail())											// checking if fail or not
		cout<<"cannot open times database file"<<endl;
	}while(inputTimes.fail());

	
	cout<<"Please enter departure location: ";
	cin>>DepLoc;

	while(DepLoc!="EXIT")
	{
	bool controlT =false;											//to control if time is true or not
	

			ofstream output;
			string DepFolder=DepLoc,routeEnd;
			DepFolder+=".txt";										//to add txt to ouput folder
			output.open(DepFolder.c_str());							//creating output folder
	do
	{
	cout<<"Please enter start time of travel: ";
	cin>>Time;
	controlT=isTimeTrue(Time);							// wrote a function to control that if its true function returns true
		if(!controlT)
			cout<<"Time is not in the correct format"<<endl;
	}while(!controlT);

	TimeHour=atoi(Time.substr(0,2));
	TimeMin=atoi(Time.substr(3,2));
	
	routescontrol(Routes,output,inputTimes,TimeHour,TimeMin,DepLoc);// calling function to continue
	cout<<"The search results are in the file: "<<DepFolder<<endl;
	
	cout<<"Please enter departure location: ";
	cin>>DepLoc;

	output.close();
	}
	Routes.close();
	inputTimes.close();
	
	cout<<"Press any key to continue . . .";


	return 0;
}

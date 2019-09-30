#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include<string>
#include "strutils.h"

using namespace std;

struct Games
{
	string Company,GameName;
	int Month,Sales;			//we dont need month but i just wrote in any case

};

void SortAndPrint(vector<Games>& v,ofstream& output)
{
	

	for(int k=0;k<v.size()-1;k++)					//we dont need to check last one
 {
	int BiggestNum=v[k].Sales;						//since it cannot be -1 sales

	for(int i=k;i<v.size()-1;i++)					//since we will check with i+1 we look -1
	{
		if(v[i+1].Sales > BiggestNum)				//if its bigger
		{
			swap(v[k],v[i+1]);						//swap with if its bigger
			BiggestNum=v[k].Sales;					//gets the new biggest number since we can have a new one
		}
		else if(v[i+1].Sales==BiggestNum)			//if its equal we will check comp name
		{
			string B=v[k].Company;
			string big=B;
			string com=v[i+1].Company;
			if(com.at(0)<big.at(0))					//checking company names	
				{
					swap(v[k],v[i+1]);
					BiggestNum=v[k].Sales;
				}	
			else if(com.at(0)==big.at(0))			//if comp names are equal we will look for game names
				{
				string D=v[k].GameName;
				string BIGcheck=D;
				string GAM=v[i+1].GameName;
				if(GAM.at(0)<BIGcheck.at(0))
					{
						swap(v[k],v[i+1]);
						BiggestNum=v[k].Sales;
					}
				}
		}	
		
	}
 }
	int c=1;																		//to write order
	output<<"RANK, COMPANY, GAME, SALES"<<endl;
	for(int z=0;z<v.size();z++)
	{
	
		output<<c<<", "<< v[z].Company<<", "<<v[z].GameName<<", "<<v[z].Sales<<endl;  //writing to the output
		c++;


 }

}

string inpCheck(ifstream& input,ofstream& output)		// to return output name i use string function because i will use it to display output name on the screen(i could display here since there is nothing more to display on screen but its more effective to return output name, also i could use ref parameter with void)
{
	string InputName,OutputName;
	do
	{
		cout<<"Please enter a filename for Board Game file: ";
		cin>>InputName;
		input.open(InputName.c_str());
		if(input.fail())
			cout<<"Can not find the specified file."<<endl;

	}while(input.fail());

	cout<<"Please enter a filename for output file: ";
	cin>>OutputName;
	output.open(OutputName.c_str());
	return OutputName;
}

void VecPut(ifstream& input,ofstream& output,vector<Games>& v)			//puts info to the vector
{
	string line;

	while(getline(input,line))											//since one line is one info about all i look line by line
	{
		Games Info;														//created to use struct
		string GameName1,GameName2,GameNameL;
		istringstream Game(line);										//make stream object to look word by word

		Game>>GameName1;												//read game name outside while to check it has one word or not (by looking coma(";"))
		GameName2=GameName1;
		while(GameName1.find(";")==string::npos)						//since there is a ";" after every specific info i look for ";" because the company name or game name can be more than one word 
			{
				Game>>GameName1;
				GameName2=GameName2+ " "+ GameName1;
			}
		GameNameL=GameName2.substr(0,GameName2.length()-1);				//deletes coma

		string StrMonthNum,StrMonthNumL;								//gets month number with first and delete coma with second
		Game>>StrMonthNum;
		StrMonthNumL=StrMonthNum.substr(0,StrMonthNum.length()-1);

		string CompName1,CompName2,CompNameL;							
		Game>>CompName1;												//read game name outside while to check it has one word or not by looking ";"
		CompName2=CompName1;
		while(CompName1.find(";")==string::npos)						//since there is a ";" after every specific info i look for ";" because the company name or game name can be more than one word
			{
				Game>>CompName1;
				CompName2=CompName2+ " "+ CompName1;
			}
		CompNameL=CompName2.substr(0,CompName2.length()-1);

		ToUpper(CompNameL);												//make upper both comp name and game name so it would be case-insensitive
		ToUpper(GameNameL);

		string SalesCount;												//takes sales count as a string
		Game>>SalesCount;
		int MonthNumber,SalesC;											//to make int both month number and sales count
		MonthNumber=atoi(StrMonthNumL);
		SalesC=atoi(SalesCount);

		Info.Company=Com	pNameL;
		Info.GameName=GameNameL;
		Info.Month= MonthNumber;
		Info.Sales=SalesC;
		bool check=false;

		for(int i=0; i< v.size() && check==false;i++)					//checking if this game used before or not !!!AND BOOL CONDITION IS EFFECTIVE TO FINISH WHEN IT FINDS,SO NO WASTE OF TÝME
		{
			if(v[i].GameName==GameNameL)	
			{	
				check=true;
				v[i].Sales+=SalesC;										//adds salesc if this game is written before
			}
		}
			if (check==false)											//if its not written before chech will stay false so i do push_back to add the vector
				v.push_back(Info);
	}
	
}



int main()
{
	ifstream input;
	ofstream output;
	string OutputN=inpCheck(input,output);

	vector<Games> v;
	string line;

	VecPut(input,output,v);
	SortAndPrint(v,output);
	cout<<"Results are in the file: "<<OutputN;

	input.close();
	output.close();


	return 0;
}

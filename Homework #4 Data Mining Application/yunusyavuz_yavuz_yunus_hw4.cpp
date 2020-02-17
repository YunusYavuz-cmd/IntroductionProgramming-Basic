#include <iostream>
#include <string>
using namespace std;

string extraction(string scramText)	//i used string so i can return and don't need to use functions inside eachother. also just need the scramText inside this function
{
	int index;
	unsigned int count;			// to prevent overflow
	string extractText;			// to find extracted text i need a new string
	index=scramText.length();	//wrote this so it won't calculate everytime when the while loop finished
	extractText="";				//empty string
	count=0;					// since we used that inside while at "at" function it must be start with 0 to give the first character
	while(count<index)			// it must stop when its in last character since index is equal to length it must be smaller than index because length start with one not 0
	{
		extractText= extractText + scramText.at(count); // wrote count and used +2 so it will write characters 0 , 2 , 4 ,6 ....
		count=count+2;
	}
	return extractText;
}

string deletechar(string delchar,string extractText)	// again i used string to give cout inside int main
	{
		int index,dellength;	
		int extlength;					
		unsigned int i=0;				//since it wont be minus used insigned to prevent overflow
		dellength=delchar.length();		//wrote this so it won't calculate everytime when the while loop finished
		extlength=extractText.length(); //wrote this so it won't calculate everytime inside while
		while(i<dellength)
		{	index=extractText.find(delchar.at(i));	// first index is outside while because while condition is index
			while(index!=string::npos)
			{   
				extractText=extractText.substr(0,index)+extractText.substr(index+1,extlength); //since it wont be longer than extractText i used extractText's length , it will stop at last character anyway
				index=extractText.find(delchar.at(i)); // as long as we change the word we dont need to add index for next character
			}
			i++;
		}
		return extractText;
	}

int main ()
{
	string scramText,delchar,hidmessage;
	scramText="";
	cout<<"This program deletes the words and numbers that you want so you can find out the hidden message."<<endl;
	cout<<"Scrambled Text: ";		  // i take the first one outside the while, so if its less then 40 characters it will get inside to while and give error
	cin>>scramText;					  //for scrambled text
		while(scramText.length()<40)  // it must calculate the length every time we get the scramText input
		{
			cout<<"Input string must be longer than 40 characters"<<endl; 
			cout<<"Scrambled Text: ";
			cin>>scramText;
		}
	cout<<"Characters to be deleted: ";
	cin>>delchar;
	cout<<"Extracted String: "<<extraction(scramText)<<endl;	//since it's a returning string function i can write like that so it will add the string to the output
	hidmessage = deletechar(delchar,extraction(scramText));
	cout<<"Hidden Message: "<<hidmessage;
	
	return 0;
}

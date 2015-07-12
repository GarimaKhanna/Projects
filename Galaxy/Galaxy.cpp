// Galaxy.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <conio.h>
#include <string>
#include <vector>
#include <iostream>
#include <map>
#include <regex>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdlib.h>

#define TABLE_SIZE 7

using namespace std;

//Roman Class: Responsible for the Roman Numeral String and the value it evaluates to
class Roman
{
	string romanStr;
	int romanVal;
	map<char,int> symbolTableMap;

public: 
	void printSymbolTable();
	void setSymbolTable();
	map<char,int> getSymbolTable(){
		return symbolTableMap;
	}
	Roman (string str, int val){
		romanStr = str;
		romanVal = val;
	}

	void setValue();
	void printValue(){
		cout<<"\n\n"<<romanStr<<"  "<<romanVal<<"\n\n";
	}
	int getValue(){
		return romanVal;
	}
	bool validateStr();

};

class BaseParser
{
	map<string,char> intergalacticalMap;	
	vector<string> inputLines;
	vector<string> intergalacticalData;
	
protected:
	vector<string> queries;
	vector<string> creditsData;	
	vector<string> output;
	map<string,int> metalCreditsMap;

	vector<string> getWordList(string str);
	string getRoman(vector<string> wordlist);
	int getUnits(string roman);
	virtual void parseInput(string str) = 0;
	virtual void getOutput() = 0;

public:

	void getIntergalacticalMap();
	void getMetalCreditsMap();	
	void readAndSetInput(vector<string> lines);

};

//Class Parser inherits BaseParser. 
//The function parseInput() is used to provide input in any desired format
//It can be used as complete string of input / or filename (different types of files can be given as input)
//It returns vector of strings which can be used further.

//function getOutput() in this case is used simply put to console the desired result.
//It can be inherited and implemented in a way to redirect the result in a file

class Parser:public BaseParser
{

public:
	void parseInput(string filename);
	void getOutput();
};

void Parser::parseInput(string filename)
{
	vector<string> inputLines;
	std::string line;

	std::ifstream infile;
	infile.open(filename);

	if (infile.is_open())
	{
		while (infile.good())
		{
			getline(infile,line);
			inputLines.push_back(line);
		}
		infile.close();
	}
	else
	{
		std::cout << "Unable to open file" << std::endl << std::endl;
	}
	readAndSetInput(inputLines);
	//return inputLines;
}

//Helper function to create tokens of words from the given input string
vector<string> BaseParser::getWordList(string str)
{
	istringstream iss(str);
	string word;
	vector<string> wordlist;
	while (getline( iss, word, ' ' ))
		wordlist.push_back(word);
	return wordlist;
}

//This function creates 3 types of vector strings:
//1. Which maps word to the Roman Symbols
//2. Which help to find information regarding Credits per unit Metal
//3. The queries
void BaseParser::readAndSetInput(vector<string> lines)
{
	inputLines = lines;
	vector<string>::iterator itr;
 
    for(itr = inputLines.begin(); itr != inputLines.end(); itr++)
    {
		//cout << *itr <<"\n";
		vector<string> wordlist;
		wordlist = getWordList( *itr );

		if (wordlist.size() == 3)
			intergalacticalData.push_back( *itr);

		else if (wordlist.back() == "Credits")
			creditsData.push_back(*itr);

		else
			queries.push_back(*itr);
	
    }
	getIntergalacticalMap();
	getMetalCreditsMap();
	
}

//Creates a map (word -> roman_symbol)
void BaseParser::getIntergalacticalMap()
{

	vector<string>::iterator itr;
    for(itr = intergalacticalData.begin(); itr != intergalacticalData.end(); itr++)
	{
		vector<string> wordlist = getWordList( *itr );

		if (wordlist[1] == "is")
			intergalacticalMap.insert(pair<string,char>(wordlist[0],wordlist[2][0]));
	}

	//Following can be uncommented to print the intergalacticalMap
	/*
	map <string,char>::iterator it; 
	for(it = intergalacticalMap.begin(); it != intergalacticalMap.end(); it++)
	{
		cout << (*it).first <<" = " <<(*it).second<<"\n";
	}
	cout<<"\n\n";
	*/

}

//helper function to find the Integer Value from the Roman String
int BaseParser::getUnits(string roman)
{
	
	Roman R(roman, 0);
	R.setSymbolTable();
	bool validString = R.validateStr();
	if (validString)
	{
		R.setSymbolTable();
		R.setValue();
		//R.printValue();
		return (R.getValue());
	}
	else
	{
		cout<<"\nInvalid Input!!";
		return -1;
	}

}

//Creates a map (metal -> credits(per unit))
void BaseParser::getMetalCreditsMap()
{
	vector<string>::iterator itr;
    for(itr = creditsData.begin(); itr != creditsData.end(); itr++)
	{
		vector<string> wordlist = getWordList( *itr );

		int len = wordlist.size();
		string metal = wordlist[len-4];
		int credits = atoi(wordlist[len-2].c_str());
		//metalCreditsMap.insert(pair<string,int>(metal, credits));

		vector<string> subWordlist;
		for (int i=0; i<len,wordlist[i] != metal; i++)
			subWordlist.push_back(wordlist[i]);

		string roman = getRoman(subWordlist);
			
		//cout<<roman<<"\n";

		int units = getUnits(roman);
		int creditsPerUnit = credits/units;
		metalCreditsMap.insert(pair<string,int>(metal, creditsPerUnit));	
		
	}

	//Can be uncommented to Print the metalCreditsMap
	/*
	map <string,int>::iterator it; 
	for(it = metalCreditsMap.begin(); it != metalCreditsMap.end(); it++)
	{
		cout << (*it).first <<" = " <<(*it).second<<"\n";
	}
	cout<<"\n\n";
	*/
}

//helper function to get equivalent roman string from the inter-galactical language words
string BaseParser::getRoman(vector<string> wordlist)
{
	string roman;
	for (int i=0; i<wordlist.size(); i++)
		roman.push_back(intergalacticalMap[wordlist[i]]);
	return roman;
}

//Function which dumps the output of the queries in a vector string.
void Parser::getOutput()
{
	string validQuery1 = "how much is ";
	int lenValidQuery1 = validQuery1.size();
	string validQuery2 = "how many Credits is ";
	int lenValidQuery2 = validQuery2.size();

	vector<string>::iterator itr;
    for(itr = queries.begin(); itr != queries.end(); itr++)
	{
		string out;
		//cout<< *itr << "\n";
		//output.push_back("correct");
		std::size_t found = (*itr).find(validQuery1);
		if (found!=std::string::npos){
			if ( found == 0 )
			{
				string remainString = (*itr).substr(lenValidQuery1);
				remainString.resize(remainString.size() - 2);
				vector<string> wordlist = getWordList(remainString);
				string roman = getRoman(wordlist);

				int units = getUnits(roman);
				out = remainString + " is " + to_string(static_cast<unsigned long long> (units)) + "\n";
				output.push_back(out);
			}
		}
		else
		{
			std::size_t found = (*itr).find(validQuery2);
			if (found!=std::string::npos)
			{
				if ( found == 0 )
				{
					string remainString = (*itr).substr(lenValidQuery2);
					remainString.resize(remainString.size() - 2);
					vector<string> wordlist = getWordList(remainString);

					string metal = wordlist.back();
					string roman = getRoman(wordlist);

					int units = getUnits(roman);
					int totalCredits = units * metalCreditsMap[metal];
					out = remainString + " is " + to_string(static_cast<unsigned long long> (totalCredits)) + " Credits\n";
					output.push_back(out);
				}
			}
			else
			{
				out = "I have no idea what you are talking about\n";
				output.push_back(out);
			}
				
		}
		
		
	}

	vector<string>::iterator it;
    for(int i = 0; i< output.size(); i++)
	{
		cout<<output[i];
	}
}


void Roman::printSymbolTable()
{
	map <char, int>::iterator itr;
 
    for(itr = symbolTableMap.begin(); itr != symbolTableMap.end(); itr++)
    {
        cout << (*itr).first <<" = " <<(*itr).second<<"\n";
    }
}

void  Roman::setSymbolTable()
{

	symbolTableMap.insert(pair<char, int>('I',1));
	symbolTableMap.insert(pair<char, int>('V',5));
	symbolTableMap.insert(pair<char, int>('X',10));
	symbolTableMap.insert(pair<char, int>('L',50));
	symbolTableMap.insert(pair<char, int>('C',100));
	symbolTableMap.insert(pair<char, int>('D',500));
	symbolTableMap.insert(pair<char, int>('M',1000));

	//printSymbolTable();

}


void Roman::setValue()
{
	//romanVal = symbolTableMap[romanStr[0]];
	for(int i=0; i < romanStr.length(); i++)
	{
		if ( (i+1) == romanStr.length())
		{
			romanVal += symbolTableMap[romanStr[i]];
			break;
		}
		if (symbolTableMap[romanStr[i]] >= symbolTableMap[romanStr[i+1]])
			romanVal += symbolTableMap[romanStr[i]];
		else
		{
			romanVal += symbolTableMap[romanStr[i+1]] - symbolTableMap[romanStr[i]];
			i++;
		}
	}

}

//function which validates if the given roman string is a valid string on the basis of the given rules.
bool Roman::validateStr()
{
	int countD=0, countL=0, countV=0;
	for (int i=0; i < romanStr.size(); i++)
	{
			if ( ( (i+2) < romanStr.size() ) && (romanStr[i] == romanStr[i+1]) &&  (romanStr[i+1] == romanStr[i+2])  )
				if(romanStr[i] == 'I' || romanStr[i] == 'X' || romanStr[i] == 'C' || romanStr[i] == 'M' )
					if( (i+3) < romanStr.size())
					{
						if (romanStr[i+3] == romanStr[i])
							return false;
						if (symbolTableMap[romanStr[i+3]] >= symbolTableMap[romanStr[i]] )
							return false;
					}
			if (romanStr[i] == 'D')
				countD++;
			if (romanStr[i] == 'L')
				countL++;
			if (romanStr[i] == 'V')
				countV++;
			if (countD > 1 || countL > 1  || countV > 1 )
				return false;

			if ( romanStr[i] == 'I')
				if ( (i+1) < romanStr.size() && symbolTableMap[romanStr[i+1]] > symbolTableMap[romanStr[i]] && (romanStr[i+1] != 'V' && romanStr[i+1] != 'X'))
					return false;
			if ( romanStr[i] == 'X')
				if ( (i+1) < romanStr.size() && symbolTableMap[romanStr[i+1]] > symbolTableMap[romanStr[i]] && (romanStr[i+1] != 'L' && romanStr[i+1] != 'C'))
					return false;
			if ( romanStr[i] == 'C')
				if ( (i+1) < romanStr.size() && symbolTableMap[romanStr[i+1]] > symbolTableMap[romanStr[i]] && (romanStr[i+1] != 'D' && romanStr[i+1] != 'M'))
					return false;

			if (romanStr[i] == 'D' || romanStr[i] == 'L' || romanStr[i] == 'V' )
				if ( (i+1) < romanStr.size() && symbolTableMap[romanStr[i+1]] > symbolTableMap[romanStr[i]] )
					return false;	

	}
		return true;


}

int main()
{

	Parser ob;
	ob.parseInput("inputFile.txt");
	ob.getOutput();
	cout<<"\n\n";
	
	return 0;
}


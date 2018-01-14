/***********************************************************************
 *   Author: Ben Shecter                                               *
 *   Date Created: Thu May 31 2007
 *   Date Modified: Thu May 31 2007
 ***********************************************************************/

#include "utilities.h"
#include <string>

namespace std 
{

Utilities::Utilities()
{

}

void Utilities::DrawBar( int Length, char Symbol)
{
	for ( int i = 0; i < Length; i++)
		cout << Symbol;
	cout << endl;
}

void Utilities::PromptInt( int &TheVariable, int Low, int High)
{
	do
	{
		cin >> TheVariable;
		if ((TheVariable < Low) || (TheVariable > High))
			cout << "Invalid entry, please re-enter: ";
	} while ((TheVariable < Low) || (TheVariable > High));
}

void Utilities::PromptDouble( double &TheVariable, double Low, double High)
{
	do
	{
		cin >> TheVariable;
		if ((TheVariable < Low) || (TheVariable > High))
			cout << "Invalid entry, please re-enter: ";
	} while ((TheVariable < Low) || (TheVariable > High));
}

void Utilities::YesNo(char &Result, string FillIn)
{
    string Temp;
    int Satisfactory = 0;
    
    cout << "Would you like " << FillIn << "?[Y/N]: ";
    do
    {
        cin >> Temp;
        Lowercase(Temp);
        
        if (Temp[0] == 'y')
            Satisfactory = 1;
        else if (Temp[0] == 'n')
            Satisfactory = 1;
    }
    while (Satisfactory != 1);
    Result = Temp[0];
}

void Utilities::Uppercase(string &TheString)
{
    for (int i = 0; i < TheString.length(); i++)
        if ((TheString[i] >= 97) && (TheString[i] <=122))
            TheString[i] -= 32;
}

void Utilities::Lowercase(string &TheString)
{
    for (int i = 0; i < TheString.length(); i++)
        if ((TheString[i] >= 65) && (TheString[i] <=90))
            TheString[i] += 32;
}

void Utilities::ReverseString(string &TheString)
{
    string temp = TheString;
    int countdown = TheString.length() - 1;
    
    for (int i = 0; i < TheString.length(); i++)
    {
        temp[countdown] = TheString[i];
        countdown--;
    }
    
    TheString = temp;
}

string Utilities::IntToString(int TheNumber)
{
	string NumString = "";
	int NegSign = 0;
	if (TheNumber < 0)
	{
		TheNumber = -TheNumber;
		NegSign = 1;
	}
	do
	{
		if ((TheNumber % 10) == 0)
			NumString += "0";
		else if ((TheNumber % 10) == 1)
			NumString += "1";
		else if ((TheNumber % 10) == 2)
			NumString += "2";
		else if ((TheNumber % 10) == 3)
			NumString += "3";
		else if ((TheNumber % 10) == 4)
			NumString += "4";
		else if ((TheNumber % 10) == 5)
			NumString += "5";
		else if ((TheNumber % 10) == 6)
			NumString += "6";
		else if ((TheNumber % 10) == 7)
			NumString += "7";
		else if ((TheNumber % 10) == 8)
			NumString += "8";
		else if ((TheNumber % 10) == 9)
			NumString += "9";
		TheNumber /= 10;
	} while (TheNumber != 0);
	
	if (NegSign ==1)
		NumString += "-";
	ReverseString(NumString);
	return NumString;
}

int Utilities::StringToInt( string TheInt)
{
	int  num = 0, Start = 0, PosNeg = 1;
	int length = TheInt.length();
	if (TheInt[0] == '-')
	{
		Start = 1;
		PosNeg = -1;
	}
	for(int i = Start; i< length; i++)
	{
		num = num * 10;
		if ( '0' == TheInt[i])
			num += 0;
		else if ( '1' == TheInt[i])
			num += 1;
		else if ( '2' == TheInt[i])
			num += 2;
		else if ( '3' == TheInt[i])
			num += 3;
		else if ( '4' == TheInt[i])
			num += 4;
		else if ( '5' == TheInt[i])
			num += 5;
		else if ( '6' == TheInt[i])
			num += 6;
		else if ( '7' == TheInt[i])
			num += 7;
		else if ( '8' == TheInt[i])
			num += 8;
		else if ( '9' == TheInt[i])
			num += 9;
		else
		{
			cout << "StrToInt error, non numeric data.";
			i = TheInt.length();
		}
	}
	num *= PosNeg;
	
	return num;
}

void Utilities::DisplayCenter(string TheString, int Space)
{
	if (TheString.length() > Space)
	{
		cout << " !Error with DisplayCenter, length exceeded space! ";
	}
	else
	{
		int WhiteSpace = (Space - TheString.length()) / 2;
		int Temp;
		
		for(Temp = 0; Temp < WhiteSpace; Temp++)
			cout << " ";
		cout << TheString;
		
		
		for(Temp = 0; Temp < WhiteSpace; Temp++)
			cout << " ";
		if (1 == ((Space-TheString.length()) % 2))
			cout << " ";
	}
}

Utilities::~Utilities()
{

}


}

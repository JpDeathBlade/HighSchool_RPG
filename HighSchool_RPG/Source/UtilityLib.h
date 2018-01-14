/*		
										Ben's Library

Created: 2/7/06
Modified 2/7/06

Functions included:
DrawBox()
DrawBar()
PromptInt()
PromptDouble()
YesNo()
Uppercase()
Lowercase()
FirstCap()
ReverseString()
IntToString()
StringToInt()
DisplayCenter()
*/
#include <iostream>

using namespace std;

void DrawBox( int, char);		//DrawBar() prototype
//Pre: Input the dimension of the box and optionally the char.
//Post: Prints a box to the screen.

void DrawBox( int, int, char);
//Pre: Input the height and width of the box, and optionally the symbol
//Post: Draws a box of Height by Width, of Symbol.

void DrawBar(int, char);
//Pre: Input the length and optionally the char
//Post: Draws a bar on screen and ends the line.

void PromptInt(int &, int, int);
//Pre:  Assumed cout of prompt beforehand. Input the varible to be set followed by the low and high value.
//Post: Sets the value of the variable.

void PromptDouble( double &, double, double);
//Pre: Assumed cout of prompt beforehand. Input the variable to be set and acceptable range
//Post: Sets the value of the variable.

void YesNo(char &, string);
//Pre: Specify the confirm variable and a peice of the question string "Would you like to " << (string here) << ".[Y/N]: "
//Post: Sets the char to yes or no based upon the user's yes or no.

void Uppercase(string &);
//Pre: Pass a string as a parameter.
//Post: Changes all lowercase letters in the string to uppercase ones.

void Lowercase(string &);
//Pre: Pass a string as a parameter.
//Post: Changes all uppercase letters to lowercase letters.

void FirstCap(string &);
//Pre: Pass a string as a parameter.
//Post: After changing all letters to lowercase, capitalizes the first letter. (only will capitolize the first space in the string)

void ReverseString(string &);
//Pre: Pass a string as a parameter.
//Post: Changes the letters of the string such that it is reversed.

string IntToString(int);
//Pre: Pass the int to be changed to a string
//Post: Returns the int as a string

int StringToInt(string);
//Pre: Specify a string containing an integer to be converted to an integer
//Post: Returns the integer version of the number

void DisplayCenter(string, int);
//Pre: Pass in the string to be centered and the the space to be centered in
//Post: Displays the string centered in the specified space.

void DrawBox( int Dimension, char Symbol = '*')		//DrawBar() definition
{
	for ( int i = 0; i < Dimension; i++)
	{
		DrawBar(Dimension, Symbol);
	}
}

void DrawBox( int Height, int Width, char Symbol = '*')
{
	for ( int i = 0; i < Height; i++)
	{
		DrawBar(Width, Symbol);
	}
}

void DrawBar( int Length, char Symbol = '*')
{
	for ( int i = 0; i < Length; i++)
		cout << Symbol;
	cout << endl;
}

void PromptInt( int &TheVariable, int Low, int High)
{
	do
	{
		cin >> TheVariable;
		if ((TheVariable < Low) || (TheVariable > High))
			cout << "Invalid entry, please re-enter: ";
	} while ((TheVariable < Low) || (TheVariable > High));
}

void PromptDouble( double &TheVariable, double Low, double High)
{
	do
	{
		cin >> TheVariable;
		if ((TheVariable < Low) || (TheVariable > High))
			cout << "Invalid entry, please re-enter: ";
	} while ((TheVariable < Low) || (TheVariable > High));
}

void YesNo(char &Result, string FillIn)
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

void Uppercase(string &TheString)
{
    for (int i = 0; i < TheString.length(); i++)
        if ((TheString[i] >= 97) && (TheString[i] <=122))
            TheString[i] -= 32;
}

void Lowercase(string &TheString)
{
    for (int i = 0; i < TheString.length(); i++)
        if ((TheString[i] >= 65) && (TheString[i] <=90))
            TheString[i] += 32;
}

void FirstCap(string &TheString)
{
    Lowercase(TheString);
    
    if ((TheString[0] >= 97) && (TheString[0] <=122))
        TheString[0] -= 32;
}

void ReverseString(string &TheString)
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

string IntToString(int TheNumber)
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

int StringToInt( string TheInt)
{
	int  num = 0, Start = 0, PosNeg = 1;
	int length = TheInt.length();
	if (TheInt[0] == '-')
	{
		Start = 1;
		PosNeg = -1;
	}
	cout << TheInt.length()<< endl;
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

void DisplayCenter(string TheString, int Space)
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

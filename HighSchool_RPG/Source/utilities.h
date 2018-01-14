/***********************************************************************
 *   Author: Ben Shecter                                               *
 *   Date Created: Thu May 31 2007
 *   Date Modified: Thu May 31 2007
 ***********************************************************************/
#ifndef STDUTILITIES_H
#define STDUTILITIES_H

#include <iostream>
#include <string>

namespace std {

class Utilities
{
	public:
		Utilities();
		void DrawBar( int Length, char Symbol = '*');
		void PromptInt( int &TheVariable, int Low, int High);
		void PromptDouble( double &TheVariable, double Low, double High);
		void YesNo(char &Result, string FillIn);
		void Uppercase(string &TheString);
		void Lowercase(string &TheString);
		void ReverseString(string &TheString);
		string IntToString(int TheNumber);
		int StringToInt( string TheInt);
		void DisplayCenter(string TheString, int Space);
		~Utilities();
	
};

}

#endif

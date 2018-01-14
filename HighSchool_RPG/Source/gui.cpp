/***********************************************************************
 *   Author: Ben Shecter                                               *
 *   Date Created: Tue May 22 2007
 *   Date Modified: Tue May 22 2007
 ***********************************************************************/

#include "gui.h"
#include <string>
#include "player.h"
#include "UtilityLib.h"

namespace std {

GUI::GUI()
  : ScrollState(1), EchoState(1), History(4)	//initalize states and the history length
{

}

int GUI::getEcho()
{
	return EchoState;
}

int GUI::getScroll()
{
	return ScrollState;
}

string GUI::Show(Player thePlayer)
{
	int vertLength, padding, inWidth = 77, iTemp;
	string sReturn;
	tvector<string> statLines(2);		//stat lines are the middle box
	cout << '+';						//draw the top line
	for (int i = 0; i < inWidth; i++)
		cout << '-';
	cout << '+' << endl
		 << '|';						//draw a padding line
	for (int i = 0; i < inWidth; i++)
		cout << ' ';
	cout << '|' << endl;
	vertLength = Display.length();
	padding = (13 - vertLength) / 2;	//find the number of lines needed before and after the display
	for (int i = 0; i < padding; i++)	//draw those blank lines
	{
		cout << '|';
		for (int i = 0; i < inWidth; i++)
			cout << ' ';
		cout << '|' << endl;
	}
	for (int i = 0; i < Display.length(); i++)		//draw the display. Each string is centered.
	{
		cout << '|';
		DisplayCenter(Display[i], inWidth);
		cout << '|' << endl;
	}
	for (int i = 0; i < padding; i++)				//draw the rest of the padding
	{
		cout << '|';
		for (int i = 0; i < inWidth; i++)
			cout << ' ';
		cout << '|' << endl;
	}
	if (Display.length() % 2 == 0)					// if the number of lines, is an even number one line will be missing, this will add it
	{
		cout << '|';
		for (int i = 0; i < inWidth; i++)
			cout << ' ';
		cout << '|' << endl;
	}
	cout << '|';									// draw the bottom padding line
		for (int i = 0; i < inWidth; i++)
			cout << ' ';
		cout << '|' << endl;
	cout << '+';									//close thie box.
	for (int i = 0; i < inWidth; i++)
		cout << '-';
	cout << '+' << endl;
	//player stat lines
	statLines[0] += thePlayer.getName();// + ' ' + IntToString(thePlayer.getLevel());
	iTemp = statLines[0].length();
	for (int i = iTemp; i < inWidth - thePlayer.getCash() - 1; i++)	//generate the first line with the name and cash
		statLines[0] += ' ';
	statLines[0] += '$' + thePlayer.getCash();
	if (thePlayer.getCash() == 0)
	{
		statLines[0][statLines[0].length() - 2] = '$';
		statLines[0][statLines[0].length() - 1] = '0';
	}
	//for (int i = 0; i < inWidth; i++)
	//	statLines[1] += ' ';		//generate the second line with stats
	statLines[1] += "HP: " + IntToString(thePlayer.getHp()) + '/' + IntToString(thePlayer.getMaxHp()) + ' ' + "MP: " + IntToString(thePlayer.getMp()) + '/' + IntToString(thePlayer.getMaxMp());
	iTemp = statLines[1].length();
	for (int i = iTemp; i < inWidth - IntToString(thePlayer.getLevel()).length() - IntToString(thePlayer.getExp()).length() - 11; i++)
		statLines[1] += ' ';
	statLines[1] += "Lvl: " + IntToString(thePlayer.getLevel()) + " Exp: " + IntToString(thePlayer.getExp());
	cout << '|' << statLines[0] << '|' << endl
		 << '|' << statLines[1] << '|' << endl;		//show them in their box
	
	//remaining lines
	cout << '+';
	for (int i = 0; i < inWidth; i++)		//close the box
		cout << '-';
	cout << '+' << endl;
	for (int i = 0; i < 3; i++)
	{
		cout << ' ' << History[i] << endl;		//show the history
	}
	cout << '>' << History[3];
	getline(cin, sReturn);						//hang it with the getline and store the input(input is returned for movement and menus)
	if (ScrollState == 1)						//if scroll is active scroll the display lines
	{
		History[0] = History[1];
		History[1] = History[2];
		History[2] = History[3];
		History[3] = "";
		if (EchoState == 1)						//if scroll and echo are active, append the user input to the 2nd to last history line
			History[2] += sReturn;
	}
	return sReturn;								//return the user input
}

string GUI::Show()
{
	int vertLength, padding, inWidth = 77;
	string sReturn;
	cout << '+';							//top line
	for (int i = 0; i < inWidth; i++)
		cout << '-';
	cout << '+' << endl
		 << '|';							//top padding
	for (int i = 0; i < inWidth; i++)
		cout << ' ';
	cout << '|' << endl;
	vertLength = Display.length();
	padding = (13 - vertLength) / 2;		//get display padding
	for (int i = 0; i < padding; i++)		//draw display padding
	{
		cout << '|';
		for (int i = 0; i < inWidth; i++)
			cout << ' ';
		cout << '|' << endl;
	}
	for (int i = 0; i < Display.length(); i++)		//draw display
	{
		cout << '|';
		DisplayCenter(Display[i], inWidth);
		cout << '|' << endl;
	}
	for (int i = 0; i < padding; i++)		//finish padding
	{
		cout << '|';
		for (int i = 0; i < inWidth; i++)
			cout << ' ';
		cout << '|' << endl;
	}
	if (Display.length() % 2 == 0)			//add the missing line if the display length was even
	{
		cout << '|';
		for (int i = 0; i < inWidth; i++)
			cout << ' ';
		cout << '|' << endl;
	}
	cout << '|';							//bottom pad
	for (int i = 0; i < inWidth; i++)
		cout << ' ';
	cout << '|' << endl;					//close box
	cout << '+';
	for (int i = 0; i < inWidth; i++)
		cout << '-';
	cout << '+' << endl
		 << '|';
	for (int i = 0; i < inWidth; i++)		//draw blank player lines
		cout << ' ';
	cout << '|' << endl << '|';
	for (int i = 0; i < inWidth; i++)
		cout << ' ';
	cout << '|' << endl
		 << '+';							//close the box
	for (int i = 0; i < inWidth; i++)
		cout << '-';
	cout << '+' << endl;
	for (int i = 0; i < 3; i++)				//show the history
	{
		cout << ' ' << History[i] << endl;
	}
	cout << '>' << History[3];
	getline(cin, sReturn);
	if (ScrollState == 1)					//deal with scrolling and echoing
	{
		History[0] = History[1];
		History[1] = History[2];
		History[2] = History[3];
		History[3] = "";
		if (EchoState == 1)
			History[2] += sReturn;
	}
	
	return sReturn;
}

void GUI::setDisplay(tvector<string> disp)
{
	Display = disp;
}

void GUI::setHistory(tvector<string> hist)
{
	History = hist;
}

void GUI::AppendLine(string line)
{
	if (ScrollState == 0)		//if it is not set to scroll, scroll the display then append
	{
		History[0] = History[1];
		History[1] = History[2];
		History[2] = History[3];
		History[3] = line;
	}
	else						//otherwise append
		History[3] = line;
}

tvector<string> GUI::getDisplay()
{
	return Display;
}

tvector<string> GUI::getHistory()
{
	return History;
}

void GUI::Echo()
{
	EchoState = 1;
}

void GUI::NoEcho()
{
	EchoState = 0;
}

void GUI::Scroll()
{
	ScrollState = 1;
}

void GUI::NoScroll()
{
	ScrollState = 0;
}

GUI::~GUI()
{

}


}

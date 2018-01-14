/***********************************************************************
 *   Author: Ben Shecter                                               *
 *   Date Created: Tue May 22 2007                                     *
 *   Date Modified: Tue May 22 2007                                    *
 ***********************************************************************/


#include <iostream>
#include <cstdlib>
#include "location.h"
#include "tvector.h"
#include "player.h"
#include "player.cpp"
#include "gui.h"
#include <fstream>
#include "utilities.h"

using namespace std;

Utilities Utils;

tvector<string> MainMenu()
{
	tvector<string> temp(7);		//generate menu strings
	temp[0] = "Main Menu";
	temp[2] = "1. View Stats    ";
	temp[3] = "2. View Items    ";
	temp[4] = "3. Save          ";
	temp[5] = "4. Return to game";
	temp[6] = "5. Exit          ";
	
	return temp;
}

void LoadPlayer(Player &);
//Pre:	Pass in a player
//Post: Loads in their data if found
void SavePlayer(Player &);
//pre:	pass in the player
//saves their data to the file

void SavePlayer(Player &thePlayer)
{
	ifstream inFile;
	ofstream outFile;
	tvector<string> temp;
	string sTemp;
	inFile.open("data");
	int written = 0;
	if (inFile.is_open())		//pull out the contents of the existing file
	{
		while (getline(inFile, sTemp))
		{
			temp.resize(temp.length() +1);
			temp[temp.length() -1] = sTemp;
		}
	}
	inFile.close();
	outFile.open("data");
	if (!outFile.is_open())
	{
		cout << "Could not open file to save" << endl;
	}
	else
	{
		for(int i =0; i < temp.length(); i++)
		{
			if (temp[0] == "(" + thePlayer.getName() + ")")	//if it's the player's section write their info instea of the old lines
			{
				outFile << "(" + thePlayer.getName() + ")" << endl
						<< thePlayer.getExp() << endl
						<< thePlayer.getMaxHp() << " " << thePlayer.getMaxMp() << " " << thePlayer.getStr() << " " << thePlayer.getDex() << " " << thePlayer.getCon() << " " << thePlayer.getInt() << " " << thePlayer.getWis() << " " << thePlayer.getCha() << " " << thePlayer.getDef() << " " << endl
						<< endl;
				i +=3;
				written = 1;
			}
			else		//write that line of the file
				outFile << temp[i] << endl;
		}
		if (written == 0)	//if not written add to the end
		{
			outFile << "(" + thePlayer.getName() + ")" << endl
					<< thePlayer.getExp() << endl
					<< thePlayer.getMaxHp() << " " << thePlayer.getMaxMp() << " " << thePlayer.getStr() << " " << thePlayer.getDex() << " " << thePlayer.getCon() << " " << thePlayer.getInt() << " " << thePlayer.getWis() << " " << thePlayer.getCha() << " " << thePlayer.getDef() << " " << endl
					<< endl;
		}
	}
}

void LoadPlayer(Player &thePlayer)
{
	string sTemp;
	Utilities Utils;
	ifstream inFile;
	inFile.open("data");
	if (!inFile.is_open())
	{
		cout << "No data To load, your getting new stats." << endl;
	}
	else
	{
		while (sTemp != "(" + thePlayer.getName() + ")")
			if (!getline( inFile, sTemp))
			{
				cout << "Sorry, didn't find you, your getting new stats" << endl;
				break;
			}
		if (sTemp == "(" + thePlayer.getName() + ")")	//pull in their data
		{
			getline(inFile, sTemp);
			thePlayer.addExp(Utils.StringToInt(sTemp));
			inFile >> sTemp;
			thePlayer.loadMaxHp(Utils.StringToInt(sTemp));
			thePlayer.healHp(Utils.StringToInt(sTemp));
			inFile >> sTemp;
			thePlayer.loadMaxMp(Utils.StringToInt(sTemp));
			thePlayer.healMp(Utils.StringToInt(sTemp));
			inFile >> sTemp;
			thePlayer.loadStr(Utils.StringToInt(sTemp));
			inFile >> sTemp;
			thePlayer.loadDex(Utils.StringToInt(sTemp));
			inFile >> sTemp;
			thePlayer.loadCon(Utils.StringToInt(sTemp));
			inFile >> sTemp;
			thePlayer.loadInt(Utils.StringToInt(sTemp));
			inFile >> sTemp;
			thePlayer.loadWis(Utils.StringToInt(sTemp));
			inFile >> sTemp;
			thePlayer.loadCha(Utils.StringToInt(sTemp));
			inFile >> sTemp;
			thePlayer.loadDef(Utils.StringToInt(sTemp));
		}
	}
}

int main()
{
	tvector<string> Display;
	tvector<string> History(4);
	tvector<string> Stats(2);
	string sTemp, MenuChoice;
	Location Map;			//our class variables
	GUI Interface;
	Player User("Foot Powder");
	
	Display.resize(10);		//title image
	Display[0] = "*     ******* *** *   * *******   ***  ****  ***      *";
	Display[1] = "***      *    *    * *     *      *  * *  * *       ***";
	Display[2] = "*****    *    **    *      *      *  * **** *  ** *****";
	Display[3] = "***      *    *    * *     *      * *  *    *   *   ***";
	Display[4] = "*        *    *** *   *    *      *  * *     ***      *";
	Display[5] = "";
	Display[6] = "1. New Game ";
	Display[7] = "2. Load Game";
	Display[8] = "3. Credits  ";
	Display[9] = "4. Exit     ";
	
	Interface.setDisplay(Display);
	Interface.AppendLine("What would you like to do?: ");		//inital prompt
	do
	{
		Stats = Interface.getHistory();
		do
		{
			MenuChoice = Interface.Show();
			if ((MenuChoice.length() == 0) || (MenuChoice.length() > 1))		//make sure valid input
				Interface.setHistory(Stats);
		} while ((MenuChoice.length() == 0) || (MenuChoice.length() > 1));
		if ((MenuChoice[0] != '1') && (MenuChoice[0] != '2') && (MenuChoice[0] != '3') && (MenuChoice[0] != '4') && (MenuChoice[0] != '5'))
			Interface.setHistory(Stats);
	} while ((MenuChoice[0] != '1') && (MenuChoice[0] != '2') && (MenuChoice[0] != '3') && (MenuChoice[0] != '4') && (MenuChoice[0] != '5'));
	if ((MenuChoice[0] == '1') || (MenuChoice[0] == '2'))		//if name needed
	{
		Interface.Echo();
		Interface.AppendLine("What is your name?: ");
		do
		{
			Stats = Interface.getHistory();
			sTemp = Interface.Show();
			if (sTemp.length() == 0)
				Interface.setHistory(Stats);
		} while (sTemp.length() == 0);
		User.loadName(sTemp);
		Interface.NoEcho();
		Interface.AppendLine("Hello " + sTemp + "!");
	}
	if (MenuChoice[0] == '2')		//if loading
		LoadPlayer(User);
	if (MenuChoice[0] == '4')		//if exit
		exit(0);
	if ((MenuChoice[0] == '2') || (MenuChoice[0] == '1'))		//if playing
	{
		Interface.NoScroll();
		Interface.AppendLine("");
		do
		{
			Interface.setDisplay(Map.Display());
			sTemp = Interface.Show(User);
			if (sTemp.length() == 1)
			{
				if (sTemp[0] == 'a')		//remap keys
					sTemp[0] = '1';
				else if (sTemp[0] == 's')
					sTemp[0] = '2';
				else if (sTemp[0] == 'd')
					sTemp[0] = '3';
				else if (sTemp[0] == 'w')
					sTemp[0] = '5';
					
				if ((sTemp[0] == '2') || (sTemp[0] == '1') ||(sTemp[0] == '3') ||(sTemp[0] == '5'))	//move
				{
					Map.Move(Interface, User, sTemp);
				}
				else if (sTemp[0] == 'm')		//menu open
				{
					Interface.setDisplay(MainMenu());
					do
					{
						Stats = Interface.getHistory();
						sTemp = Interface.Show(User);
						if (sTemp.length() != 1)
							Interface.setHistory(Stats);
					} while (sTemp.length() != 1);
					
					if (sTemp[0] == '3')		//if save
						SavePlayer(User);
					else if (sTemp[0] == '5')	//if exit
						exit(0);
				}
			}
		} while(1);		//to continue into infinity
	}
	
	return 0;
}

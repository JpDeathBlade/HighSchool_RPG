/***********************************************************************
 *   Author: Ben Shecter                                               *
 *   Date Created: Tue May 22 2007                                     *
 *   Date Modified: Tue May 22 2007                                    *
 ***********************************************************************/
#include "location.h"
#include "tvector.h"
#include "tmatrix.h"
#include "utilities.h"
#include <fstream>
#include "gui.h"
#include "player.h"
#include "randgen.h"

namespace std {

//int Battle(GUI &, Player &, int, int);
//Pre:	Pass in the interface, player, monster, and optionally if they can escape
//Post:	Takes the user through the battle, deals with adding exp and such

int EventHandler(GUI &, Player &, int eventCode);
//Pre:	Pass in the interface, player, and event code
//Post:	Finds out what the event does and acts upon it.

struct Monster			//a simple struct to contain monster stats
{
	string 			Name;
	tvector<string> Picture;
	int 			Hp;
	int 			MaxHp;
	int 			Attack;
	int 			Defense;
	int 			Dex;
	int 			Exp;
};

void Battle(GUI &Interface, Player &thePlayer, int id, int Escape = 1)
{
	Utilities Utils;
	if (Escape != 1)	//if the battle is specified as unescapeable, note it as so
		Escape = 0;
	ifstream inFile;	//loading stream
	tvector<string> hold;	//temporary storage of history
	inFile.open("monsters");	//open the monster file
	int iTemp = -id, preScroll = Interface.getScroll(), preEcho = Interface.getEcho(), returnCode = 0;	//other misc. variables
	string sTemp; //my favorite temp string
	Monster theMonster;	//An instance of the monster struct to store info
	if (!inFile.is_open())	//if not open
	{
		cerr << "Error opening the monsters file." << endl;
		exit(8);
	}
	else	//otherwise
	{
		do		//search for the monster id
		{
			if (!getline(inFile, sTemp))	//if the end of the file is hit, stop searching and alert the user
			{
				cout << "Monster number " << id << " is missing." << endl;
				exit(9);
			}
			if ((sTemp[0] == '[') && (sTemp[sTemp.length() -1] == ']'))	//id numbers are enclosed in brackets, so only convert what needs to be checked
				iTemp = Utils.StringToInt(sTemp.substr(1, sTemp.length() -2));
		} while (iTemp != id);
		
		getline(inFile, theMonster.Name);// pull in the name
		if (Escape == 1)		//if escape is true
		{
			sTemp = "You have encountered ";	//tell them what they are facing
			if (!((theMonster.Name[0] >= 65) && (theMonster.Name[0] <= 90)))
			{
				sTemp += "a";
				if ((theMonster.Name[0] == 'a') || (theMonster.Name[0] == 'e') || (theMonster.Name[0] == 'i') || (theMonster.Name[0] == 'o') || (theMonster.Name[0] == 'u'))
					sTemp += "n";
				sTemp += " ";
			}
			Escape = 0;		//set escape to false in case they want to battle
			Interface.NoScroll();
			Interface.AppendLine(sTemp + theMonster.Name);
			Interface.Show(thePlayer);
			Interface.AppendLine("Would you like to fight?[Y/N]: "); //ask them if they would like to fight
			Interface.Scroll();
			Interface.Echo();
			do		//this loop is to ensure valid input
			{
				hold = Interface.getHistory();
				do
				{
					sTemp = Interface.Show(thePlayer);
					if ((sTemp.length() == 0) || (sTemp.length() > 1))		//if invalid input, reset the history to the held history
						Interface.setHistory(hold);
				} while ((sTemp.length() == 0) || (sTemp.length() > 1));
				Utils.Lowercase(sTemp);
				if ((sTemp[0] != 'y') && (sTemp[0] != 'n'))
					Interface.setHistory(hold);
			} while ((sTemp[0] != 'y') && (sTemp[0] != 'n'));
			
			if (sTemp[0] == 'n')		//if they want to escape, set it to true again
				Escape = 1;
		}
		if (Escape == 0)		//if they're not running or can't run
		{
			getline(inFile, sTemp);	//the following loop searches line by line for something enclosed in paranthesis before the next set of brackets
			while (((sTemp[0] != '(') || (sTemp[sTemp.length() -1] != ')')) && ((sTemp[0] != '[') || (sTemp[sTemp.length() -1] != ']')))
				if (!getline(inFile, sTemp))
					break;
			Utils.Lowercase(sTemp);
			if (sTemp == "(display)")		//this loop reads in the monster's picture
			{
				if ((sTemp[0] != '[') || (sTemp[sTemp.length() -1] != ']'))
				{
					sTemp = "";
					while ((sTemp[0] != '(') || (sTemp[sTemp.length() -1] != ')'))
					{
						if (!getline(inFile, sTemp))
							break;
						if ((sTemp[0] != '(') || (sTemp[sTemp.length() -1] != ')'))
						{
							theMonster.Picture.resize(theMonster.Picture.length() +1);
							theMonster.Picture[theMonster.Picture.length() -1] = sTemp;
						}
					}
				}
			}
			else		//alert the user if the picture isn't there
			{
				cerr << "Could not find the picture for " << theMonster.Name << endl;
				exit(10);
			}
			//search for the next section
			while (((sTemp[0] != '(') || (sTemp[sTemp.length() -1] != ')')) && ((sTemp[0] != '[') || (sTemp[sTemp.length() -1] != ']')))
				if (!getline(inFile, sTemp))
					break;
			Utils.Lowercase(sTemp);
			
			if (sTemp == "(stats)")
			{	//read in the stats
				inFile >> theMonster.MaxHp;
				theMonster.Hp = theMonster.MaxHp;
				inFile >> theMonster.Attack;
				inFile >> theMonster.Defense;
				inFile >> theMonster.Dex;
				inFile >> theMonster.Exp;
			}
				
			/*cout << theMonster.Name << endl;
			for (int i = 0; i < theMonster.Picture.length(); i++)
				cout << theMonster.Picture[i] << endl;
			cout << "Max Hp: " << theMonster.MaxHp << endl
				 << "Attack: " << theMonster.Attack << endl
				 << "Defense: " << theMonster.Defense << endl
				 << "Dex: " << theMonster.Dex << endl
				 << endl;*/
			
			Interface.setDisplay(theMonster.Picture);		//set their picture
			int PlayerFirst = 0;
			string monsStat;
			Interface.NoScroll();
			if (thePlayer.getDex() >= theMonster.Dex)		//determine who attacks first
			{
				Interface.AppendLine("You attack first.");
				Interface.Show(thePlayer);
				PlayerFirst = 1;
			}
			else
			{
				Interface.AppendLine(theMonster.Name + " attacks first.");
				Interface.Show(thePlayer);
			}
			int damage;
			do		//this loop continues until someone dies
			{
				if (PlayerFirst == 1)		//if the player ins't first, the variable is set to 1 at the end of the loop to let them attack
				{
					monsStat = "";
					if (!((theMonster.Name[0] >= 65) && (theMonster.Name[0] <= 90)))
						monsStat = "The ";
					monsStat += theMonster.Name + " has " + Utils.IntToString(theMonster.Hp) + " hp.";
					Interface.AppendLine(monsStat);	//notify them of hp
					Interface.Show(thePlayer);
					Interface.AppendLine("Prepare to attack...");	//just for looks
					Interface.Show(thePlayer);
					damage = thePlayer.getStr() -  theMonster.Defense;	//simple damage calculation
					if (damage <= 0)	//make sure at least one damage is done
						damage = 1;
					if (damage > theMonster.Hp)		//if over monster's hp is done, set it to their hp
						damage = theMonster.Hp;
					Interface.AppendLine("You hit them for " + Utils.IntToString(damage) + " damage."); //tell the player the result
					Interface.Show(thePlayer);
					theMonster.Hp -= damage; //take the hp
					if (theMonster.Hp < 0)	//make sure the monster isn't les than dead =P
						theMonster.Hp = 0;
				}
				if (theMonster.Hp > 0)		//since this is the second part of the loop, gotta make sure the monster isn't dead.
				{
					monsStat = "";
					if (!((theMonster.Name[0] >= 65) && (theMonster.Name[0] <= 90)))
						monsStat = "The ";
					monsStat += theMonster.Name + " attacked.";
					if (PlayerFirst != 0)		//make sure to say this only after the player has had a turn
					{
						Interface.AppendLine(monsStat);
						Interface.Show(thePlayer);
					}
					damage = theMonster.Attack - thePlayer.getDef();		//simple damage again
					if (damage <= 0)	//ensure at least one damage
						damage = 1;
					if (damage > thePlayer.getHp())	// no overkill
						damage = thePlayer.getHp();
					Interface.AppendLine("They hit you for " + Utils.IntToString(damage) + " damage.");	//inform the player of the result
					thePlayer.lossHp(damage);
					PlayerFirst = 1;	//make sure the player gets a turn the next time
				}
				
			} while ((theMonster.Hp > 0) && (thePlayer.getHp() > 0));	//while someone's alive
			if (thePlayer.getHp() == 0)		//if the player won set the return code
				returnCode = 1;
				
			if (theMonster.Hp == 0)		//if the monster is dead, tell the user
				Interface.AppendLine("You killed the " + theMonster.Name + "!");
			if (thePlayer.getHp() == 0)		//if the player is dead, yell at them
				Interface.AppendLine("The " + theMonster.Name + " killed you!");
			Interface.Show(thePlayer);		//show
			if (theMonster.Hp == 0)			//if the  onster is dead, give them exp and show
			{
				Interface.AppendLine("You gained " + Utils.IntToString(theMonster.Exp) + " experience.");
				thePlayer.addExp(theMonster.Exp);
				Interface.Show(thePlayer);
			}
		}
		if (preScroll == 1)		//reset the scroll states and such
		{
			Interface.AppendLine("");
			Interface.Scroll();
		}
		else
		{
			Interface.NoScroll();
			Interface.AppendLine("");
		}
		if (preEcho == 1)
			Interface.Echo();
		else
			Interface.NoEcho();
	}
	inFile.close();
}

int Location::EventHandler(GUI &Interface, Player &thePlayer, int eventCode)
{
	tvector<string> newDisplay;
	tvector<string> newText;
	if (eventCode == -1)	//and event code of -1 means that they're on a bed
	{
		newDisplay.resize(5);
		newDisplay[0] = "zzzzZZZZZZZZZZZZZZZZZ";
		newDisplay[2] = "zzzzzzzzzZZZZZZZZZZZZ";
		newDisplay[4] = "zzzzzzzzzzzzzzzzZZZZZ";
		Interface.setDisplay(newDisplay);			//change display
		Interface.AppendLine("You slept in a bed.");
		Interface.AppendLine("You are fully restored.");		//notify
		thePlayer.healHp(thePlayer.getMaxHp());		//heal
		thePlayer.healMp(thePlayer.getMaxMp());
		Interface.Show(thePlayer);		//show
		
	}
	else
	{
		Utilities Utils;		//my utility class
		int iTemp = -eventCode, triggers = -1;
		ifstream inFile;		//reading stream
		string sTemp, eventName;	//temp and event name
		tvector<int> battles;		//things to act upon
		tvector<int> addItems;		//not used
		tvector<int> removeItems;	//not used
		inFile.open("events");		//open the file
		int chain = -2, warpRow, warpCol; 
		string warpName;
		if (!inFile.is_open())		//on failure, complain
		{
			cerr << "Missing file \"events\"!" << endl;
			exit(4);
		}
		else		//otherwise
		{
			do		//find the event
			{
				if (!getline(inFile, sTemp))
				{
					cout << "Event not found." << endl;
					exit(5);
				}
				if ((sTemp[0] == '[') && (sTemp[sTemp.length() -1] == ']'))
				iTemp = Utils.StringToInt(sTemp.substr(1, sTemp.length() -2));
			} while (iTemp != eventCode);
			
			getline(inFile, sTemp);		//pull in the next line and see if the event has a specific number of triggers
			Utils.Lowercase(sTemp);
			if (sTemp.substr(0, 10) == "triggers: ")
				triggers = Utils.StringToInt(sTemp.substr(10));
			
			while (((sTemp[0] != '(') || (sTemp[sTemp.length() -1] != ')')) && ((sTemp[0] != '[') || (sTemp[sTemp.length() -1] != ']')))
				if (!getline(inFile, sTemp))
					break;
			Utils.Lowercase(sTemp);		//^find the next section^
			
			if (sTemp == "(display)")		//pull in the display if there is one
			{
				if ((sTemp[0] != '[') && (sTemp[sTemp.length() -1] != ']'))
				{
					sTemp = "";
					while ((sTemp[0] != '(') && (sTemp[sTemp.length() -1] != ')'))
					{
						if (!getline(inFile, sTemp))
							break;
						if ((sTemp[0] != '(') && (sTemp[sTemp.length() -1] != ')'))
						{
							newDisplay.resize(newDisplay.length() +1);
							newDisplay[newDisplay.length() -1] = sTemp;
						}
					}
				}
			}
			while (((sTemp[0] != '(') || (sTemp[sTemp.length() -1] != ')')) && ((sTemp[0] != '[') || (sTemp[sTemp.length() -1] != ']')))
				if (!getline(inFile, sTemp))
					break;
			Utils.Lowercase(sTemp);		//^find the next section^
			
			if (sTemp == "(text)")		//pull in lines of text to say, if any
			{
				if ((sTemp[0] != '[') && (sTemp[sTemp.length() -1] != ']'))
				{
					sTemp = "";
					while ((sTemp[0] != '(') && (sTemp[sTemp.length() -1] != ')'))
					{
						if (!getline(inFile, sTemp))
							break;
						if ((sTemp[0] == '[') && (sTemp[sTemp.length() -1] == ']'))
							break;
						if ((sTemp[0] != '(') && (sTemp[sTemp.length() -1] != ')'))
						{
							newText.resize(newText.length() +1);
							newText[newText.length() -1] = sTemp;
						}
					}
				}
			}
			while (((sTemp[0] != '(') || (sTemp[sTemp.length() -1] != ')')) && ((sTemp[0] != '[') || (sTemp[sTemp.length() -1] != ']')))
				if (!getline(inFile, sTemp))
					break;
			Utils.Lowercase(sTemp);		//^find the next section^
			
			if (sTemp == "(battle)")		//record what battles should take place, if any
			{
				if ((sTemp[0] != '[') && (sTemp[sTemp.length() -1] != ']'))
				{
					sTemp = "1";
					while (((sTemp[0] != '(') && (sTemp[sTemp.length() -1] != ')')) && (sTemp.length() != 0))
					{
						if (!getline(inFile, sTemp))
							break;
						if (((sTemp[0] != '(') && (sTemp[sTemp.length() -1] != ')')) && (sTemp.length() != 0))
						{
							battles.resize(battles.length() +1);
							battles[battles.length() -1] = Utils.StringToInt(sTemp);;
						}
					}
				}
			}
			while (((sTemp[0] != '(') || (sTemp[sTemp.length() -1] != ')')) && ((sTemp[0] != '[') || (sTemp[sTemp.length() -1] != ']')))
				if (!getline(inFile, sTemp))
					break;
			Utils.Lowercase(sTemp);		//^find the next section^
			
			if (sTemp == "(add items)")	//get item ids, not implemented
			{
				if ((sTemp[0] != '[') && (sTemp[sTemp.length() -1] != ']'))
				{
					sTemp = "1";
					while (((sTemp[0] != '(') && (sTemp[sTemp.length() -1] != ')')) && (sTemp.length() != 0))
					{
						if (!getline(inFile, sTemp))
							break;
						if (((sTemp[0] != '(') && (sTemp[sTemp.length() -1] != ')')) && (sTemp.length() != 0))
						{
							addItems.resize(addItems.length() +1);
							addItems[addItems.length() -1] = Utils.StringToInt(sTemp);;
						}
					}
				}
			}
			while (((sTemp[0] != '(') || (sTemp[sTemp.length() -1] != ')')) && ((sTemp[0] != '[') || (sTemp[sTemp.length() -1] != ']')))
				if (!getline(inFile, sTemp))
					break;
			Utils.Lowercase(sTemp);		//^find the next section^
			
			if (sTemp == "(remove items)")// get item ids, not implemented
			{
				if ((sTemp[0] != '[') && (sTemp[sTemp.length() -1] != ']'))
				{
					sTemp = "1";
					while (((sTemp[0] != '(') && (sTemp[sTemp.length() -1] != ')')) && (sTemp.length() != 0))
					{
						if (!getline(inFile, sTemp))
							break;
						if (((sTemp[0] != '(') && (sTemp[sTemp.length() -1] != ')')) && (sTemp.length() != 0))
						{
							removeItems.resize(removeItems.length() +1);
							removeItems[removeItems.length() -1] = Utils.StringToInt(sTemp);;
						}
					}
				}
			}
			
			while (((sTemp[0] != '(') || (sTemp[sTemp.length() -1] != ')')) && ((sTemp[0] != '[') || (sTemp[sTemp.length() -1] != ']')))
				if (!getline(inFile, sTemp))
					break;
			Utils.Lowercase(sTemp);		//^find the next section^
			
			if (sTemp == "(link)")// get item ids, not implemented
			{
				getline(inFile, sTemp);
				chain = Utils.StringToInt(sTemp);
			}
			
			while (((sTemp[0] != '(') || (sTemp[sTemp.length() -1] != ')')) && ((sTemp[0] != '[') || (sTemp[sTemp.length() -1] != ']')))
				if (!getline(inFile, sTemp))
					break;
			Utils.Lowercase(sTemp);		//^find the next section^
			
			if (sTemp == "(send)")// get item ids, not implemented
			{
				inFile >> warpName >> warpRow >> warpCol;
			}
			
			/*cout << "Event code: " << eventCode << endl
				 << "Triggers: " << triggers << endl
				 << "Display:" << endl;
			for (int i = 0; i < newDisplay.length(); i++)
				cout << "  " << newDisplay[i] << endl;
			cout << "Text:" << endl;
			for (int i = 0; i < newText.length(); i++)
				cout << "  " << newText[i] << endl;
			cout << "Battles:" << endl;
			for (int i = 0; i < battles.length(); i++)
				cout << "  " << battles[i] << endl;
			cout << "Add items:" << endl;
			for (int i = 0; i < addItems.length(); i++)
				cout << "  " << addItems[i] << endl;
			cout << "Remove items:" << endl;
			for (int i = 0; i < removeItems.length(); i++)
				cout << "  " << removeItems[i] << endl;
			cout << endl;*/
		}
		int unUsed = 1, active = 1, slot;
		for (int i = 0; i < thePlayer.events.length(); i++)		//search to see if the event has been used previously
		{
			if (thePlayer.events[i].id == eventCode)		//if so
			{
				unUsed = 0;		//note
				slot = i;		//and record which slot
			}
		}
		if (unUsed == 1)		//if unused
		{
			if (triggers != -1)		//and not an infinite event
			{
				thePlayer.events.resize(thePlayer.events.length() + 1);		//note it
				thePlayer.events[thePlayer.events.length() -1].id = eventCode;
				thePlayer.events[thePlayer.events.length() -1].triggered = 1;
			}
		}
		else if (triggers != -1)		//if used
		{
			if (thePlayer.events[slot].triggered < triggers)	//if it is still active, up the counter
				thePlayer.events[slot].triggered++;
			else		//otherwise mark as inactive
				active = 0;
		}
		if (active == 1)		//if active
		{
			int priorScroll;	//record scroll
			priorScroll = Interface.getScroll();
			if (newDisplay.length() != 0)		//if there is a new display, set it
				Interface.setDisplay(newDisplay);
			Interface.NoScroll();
			for (int i = 0; i < newText.length(); i++)	//if there is text, add and show one line at a time
			{
				Interface.AppendLine(newText[i]);
				Interface.Show(thePlayer);
			}
			if (newText.length() == 0)			//if there was no text, show them the picture
				Interface.Show(thePlayer);
			if (priorScroll == 1)
				Interface.Scroll();
			for(int i = 0; i < battles.length(); i++)		//make them fight the battles, they are inescapable
				Battle(Interface, thePlayer, battles[i], 0);
			if (battles.length() == 0)			//if no battles, append a blank line
				Interface.AppendLine("");
			if (chain != -2)
			{
				EventHandler(Interface, thePlayer, chain);
			}
			if (warpName.length() > 0)
			{
				Teleport(warpName, warpRow, warpCol);
			}
		}
		if (chain != -2)
		{
			Interface.setDisplay(Display());
			EventHandler(Interface, thePlayer, chain);
		}
		if ((warpName.length() > 0) && (active == 1))
		{
			Teleport(warpName, warpRow, warpCol);
		}

	}
	return 0;
}

Location::Location()
{
	string sTemp;
	ifstream myFile;
	myFile.open("maps");		//open the maps file
	if (!myFile.is_open())
		cout << "Error opening maps file." << endl;
	else
	{
		do		//search for the default map
		{
			if (getline(myFile, sTemp));
			else
			{
				cerr << "No default map found" << endl;
				exit(1);
			}
		} while (sTemp != "default");
		getline(myFile, sTemp);
		sTemp = sTemp.substr(1, sTemp.length() - 2);		//get the name of the map
		Teleport(sTemp);		//call Teleport() to actually load the map
	}
	myFile.close();
}

tvector<string> Location::Display()
{
	tvector<string> temp(DisplayMat.numrows() + 2, "");		//create a blank vector with 2 extra rows for a box
	for(int i = 0; i < DisplayMat.numcols() + 2; i++)		//top line
		temp[0] += '#';
	for (int i = 0; i < DisplayMat.numrows(); i++)		//for each row
	{
		temp[i + 1] += '#';		//preceding hash mark
		for (int j = 0; j < DisplayMat.numcols(); j++)
		{
			if ((i == locRow) && (j == locCol))		//if it's the player's location, display @ in that space
				temp[i + 1] += '@';
			else if (DisplayMat[i][j] == 'e')		//if it's a hidden event, cover it
				temp[i + 1] += ' ';
			else if (DisplayMat[i][j] == '%')		//if it's hidden walkable area, make it look like a wall
				temp[i + 1] += '#';
			else if (DisplayMat[i][j] == '$')		//if it's hidden walkable area, make it look like a wall
				temp[i + 1] += 'X';
			else
				temp[i + 1] += DisplayMat[i][j];	//otherwise just use what's on the square
		}
		temp[i + 1] += '#';		//trailing hash mark
	}
	for(int i = 0; i < DisplayMat.numcols() + 2; i++)		//bottom line
		temp[temp.length() - 1] += '#';
	return temp;
}

void Location::Move(GUI &Interface, Player &thePlayer, string direction)
{
	tvector<int> temp(4,0);		//a vector to hold what moves they can make
	int sum, moved = 0, returnCode = 0;		//various variables
	string sTemp;							//my favorite string temp again
	sum = Moves[locRow][locCol];			//pull out the square's move value
	if (sum >= 8) 							//if it's 8 or greater they can move down, so note it and keep the remainder
	{
		sum %= 8;
		temp[3] = 1;
	}
	if (sum >= 4)  							//if it's 4 or greater they can move right, so note it and keep the remainder
	{
		sum %= 4;
		temp[2] = 1;
	}
	if (sum >= 2)  							//if it's 2 or greater they can move up, so note it and keep the remainder
	{
		sum %= 2;
		temp[1] = 1;
	}
	if (sum == 1) 
		temp[0] = 1;
	if (direction[0] == '1')		//if they want to move left and can, move them and note it
		if (temp[0] == 1)
		{
			moved = 1;
			locCol--;
		}
	if (direction[0] == '5')		//if they want to move up and can, move them and note it
		if (temp[1] == 1)
		{
			moved = 1;
			locRow--;
		}
	if (direction[0] == '3')		//if they want to move right and can, move them and note it
		if (temp[2] == 1)
		{
			moved = 1;
			locCol++;
		}
	if (direction[0] == '2')		//if they want to move down and can, move them and note it
		if (temp[3] == 1)
		{
			moved = 1;
			locRow++;
		}
	if ((DisplayMat[locRow][locCol] == 'T') && (moved == 1))	//if it is a town, teleport them and use the default location
	{
		for(int i = 0; i < Towns.length(); i++) //find the town associated with the square
			if ((Towns[i].Row == (locRow + 1)) && (Towns[i].Col == (locCol + 1)))
				sum = i;
		Teleport(Towns[sum].Name);
	}
	if (((DisplayMat[locRow][locCol] == 'X') || (DisplayMat[locRow][locCol] == '>') || (DisplayMat[locRow][locCol] == '<') ) && (moved == 1))	//if an exit, teleport them with the new co-ordinate
	{
		for(int i = 0; i < Exits.length(); i++)	//find the exit associated with the square
			if ((Exits[i].Row == (locRow + 1)) && (Exits[i].Col == (locCol + 1)))
				sum = i;
		Teleport(Exits[sum].Name, Exits[sum].tRow, Exits[sum].tCol);
	}
	Utilities Utils;
	if (((DisplayMat[locRow][locCol] == 'e') || (DisplayMat[locRow][locCol] == 'E') || (DisplayMat[locRow][locCol] == '$')) && (moved == 1))
	{		//if an event, call event handler to deal with it
		returnCode = 1;
		for(int i = 0; i < Events.length(); i++)		//find the event associated with the square
			if ((Events[i].Row == (locRow + 1)) && (Events[i].Col == (locCol + 1)))
				sum = i;
		EventHandler(Interface, thePlayer, Utils.StringToInt(Events[sum].Name));
	}
	else if (DisplayMat[locRow][locCol] == ' ') //moved check
	{
		RandGen myRand;		//if they're not on anything else
		if (BattlePercent > myRand.RandInt(100))	//see if they've encountered a monster
		{
			Interface.setDisplay(Display());		//update the display before sending them to battle
			Battle(Interface, thePlayer, Monsters[myRand.RandInt(Monsters.length())], 1);	//send them to battle
		}
	}
	
}

void Location::Teleport(string targetMap, int Row, int Col)
{
	Utilities Utils;
	string sTemp;
	int numRows, numCols;
	ifstream myFile;		//standard variables
	myFile.open("maps");	//open maps
	if (!myFile.is_open())
		cout << "Error opening maps file." << endl;
	else
	{
		do		//find the right map
		{
			if (getline(myFile, sTemp));
			else
			{
				cerr << "Map \"" << targetMap << "\" not found." << endl;
				exit(1);
			}
		}
		while (sTemp != ("[" + targetMap + "]"));
		MapName = targetMap;		//set the map name
		myFile >> numRows;			//pull in the size
		myFile >> numCols;
		if (Row != 0)		//if it's not using the default
		{
			myFile >> locRow;
			locRow = Row;		//pull in the default row then ignore it
		}
		else
			myFile >> locRow;	//otherwise just pull it in
		locRow--;				//adjust it to actually match the cell
		if (Col != 0)			//if not defaulting
		{
			myFile >> locCol;	//read and ignore
			locCol = Col;
		}
		else					//otherwise read
			myFile >> locCol;
		locCol--;				//adjust
		myFile.ignore(10, '\n');	//skip tot he next line
		Moves.resize( numRows, numCols);		//set the size of the moves vector
		DisplayMat.resize( numRows, numCols);// cout << "Map..."; // set the size of the charecter vector
		for (int i = 0; i < DisplayMat.numrows(); i++)		//read the charecters in one at a time into the charecter matrix
		{
			for ( int j = 0; j < DisplayMat.numcols(); j++)
				myFile.get(DisplayMat[i][j]);
			myFile.ignore(10, '\n');
		}	//cout << "Loaded." << endl << "Moves...";
		for (int i = 0; i < Moves.numrows(); i++)		//set up the moves matrix
		{
			for ( int j = 0; j < Moves.numcols(); j++)
			{
				Moves[i][j] = 0;
				if ((DisplayMat[i][j] == ' ') || (DisplayMat[i][j] == 'P'))		//since before conversin blank space is un-walkable, set it so
					Moves[i][j] = 0;
				else
				{
					if ((i - 1) >= 0)		//up- if there is a space above
						if ((DisplayMat[i - 1][j] != ' ') || (DisplayMat[i - 1][j] == 'P'))	//and it's walkable set it so
							Moves[i][j] += 2;
					if ((j - 1) >= 0)		//left- see above
						if ((DisplayMat[i][j - 1] != ' ') || (DisplayMat[i][j - 1] == 'P'))
							Moves[i][j] += 1;
					if ((j + 1) < Moves.numcols())	//right-see above
						if ((DisplayMat[i][j + 1] != ' ') || (DisplayMat[i][j + 1] == 'P'))
							Moves[i][j] += 4;
					if ((i + 1) < Moves.numrows())	//down- see above
						if ((DisplayMat[i + 1][j] != ' ') || (DisplayMat[i + 1][j] == 'P'))
							Moves[i][j] += 8;
				}
			}
		}// cout << "Set." << endl << "Drawing...";
		 //cout << "Complete." << endl;
		myFile.ignore(10, '\n');		//skip to the end of the line and make sure all the vectors are set to zero length
		Events.resize(0);
		Events.resize(0);
		Exits.resize(0);
		Exits.resize(0);
		Towns.resize(0);
		Towns.resize(0);
		Shops.resize(0);
		Shops.resize(0);
		Monsters.resize(0);
		Monsters.resize(0);
		//cout << "Couting...";
		for (int i = 0; i < DisplayMat.numrows(); i++)		//count the number of actions of each type
			for ( int j = 0; j < DisplayMat.numcols(); j++)
			{
				if (DisplayMat[i][j] == 'X')
					Exits.resize(Exits.size() + 1);
				else if ((DisplayMat[i][j] == '>') || (DisplayMat[i][j] == '<'))
					Exits.resize(Exits.size() + 1);
				else if (DisplayMat[i][j] == 'T')
					Towns.resize(Towns.size() + 1);
				else if (DisplayMat[i][j] == 'S')
					Shops.resize(Shops.size() + 1);
				else if ((DisplayMat[i][j] == 'e') || (DisplayMat[i][j] == 'E') || (DisplayMat[i][j] == '$'))
					Events.resize(Events.size() + 1);
			}
		//cout << "Done." << endl << "Towns...";
		if (Events.length() > 0)		//for each event, if ny, pull in event info
		{
			do
			{
				getline(myFile, sTemp);
			} while ( sTemp != "(Events)");
			for ( int i = 0; i < Events.length(); i++)
			{
				myFile >> Events[i].Row;
				myFile >> Events[i].Col;
				myFile >> Events[i].Name;
			}
		}
		if (Towns.length() > 0)		//for each town, if ny, pull in town info
		{
			do
			{
				getline(myFile, sTemp);
			} while ( sTemp != "(Towns)");
			for ( int i = 0; i < Towns.length(); i++)
			{
				myFile >> Towns[i].Row;
				myFile >> Towns[i].Col;
				myFile >> Towns[i].Name;
			}
		}// cout << "Loaded." << endl << "Shops...";
		if (Shops.length() > 0)		//for each shop, if ny, pull in shop info NOT USED
		{
			do
			{
				getline(myFile, sTemp);
			} while ( sTemp != "(Shops)");
			for ( int i = 0; i < Shops.length(); i++)
			{
				myFile >> Shops[i].Row;
				myFile >> Shops[i].Col;
				myFile >> Shops[i].Name;
			}
		} //cout << "Loaded." << endl << "Exits...";
		if (Exits.length() > 0)		//for each exit, if ny, pull in exit info
		{
			do
			{
				getline(myFile, sTemp);
			} while ( sTemp != "(Exits)");
			for ( int i = 0; i < Exits.length(); i++)
			{
				myFile >> Exits[i].Row;
				myFile >> Exits[i].Col;
				myFile >> Exits[i].Name;
				myFile >> Exits[i].tRow;
				myFile >> Exits[i].tCol;
			}
		} //cout << "Loaded." << endl;
		myFile.ignore(20, '\n'); //skip to the next line
		getline(myFile, sTemp);	//read a line
		BattlePercent = 0;		//set chance of batt to 0, jus in case
		if (sTemp == "(Battles)")		//if it is the battles section
		{
			getline(myFile, sTemp);		//read in the chance of battle
			BattlePercent = Utils.StringToInt(sTemp);
			do
			{
				if (!getline(myFile, sTemp))	//read in each possible battle
					break;
				if (sTemp.length() > 0)
				{
					Monsters.resize(Monsters.length() +1);
					Monsters[Monsters.length() -1] = Utils.StringToInt(sTemp);
				}
			} while (((sTemp[0] != '(') && (sTemp[0] != ')')) && ((sTemp[0] != '[') && (sTemp[0] != ']')) && (sTemp.length() != 0));
		}
		for (int i = 0; i < DisplayMat.numrows(); i++)		//this loop converts *'s to ' ' and non walkable area to hashes
		{
			for ( int j = 0; j < DisplayMat.numcols(); j++)
			{
				/*if ((DisplayMat[i][j] == '*') && ((Moves[i][j] == 1) || (Moves[i][j] == 4) || (Moves[i][j] == 5)))
					DisplayMat[i][j] = ' ';
				else if ((DisplayMat[i][j] == '*') && ((Moves[i][j] == 2) || (Moves[i][j] == 8) || (Moves[i][j] == 10)))
					DisplayMat[i][j] = ' ';
				else */if (DisplayMat[i][j] == '*')
					DisplayMat[i][j] = ' ';
				else if ((DisplayMat[i][j] == ' ') && (Moves[i][j] == 0))
					DisplayMat[i][j] = '#';
			}
		}
	}
	myFile.close();
}

Location::~Location()
{

}


}

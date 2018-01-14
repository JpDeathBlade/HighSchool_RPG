/***********************************************************************
 *   Author: Ben Shecter                                               *
 *   Date Created: Tue May 22 2007                                     *
 *   Date Modified: Tue May 22 2007                                    *
 ***********************************************************************/
#ifndef STDLOCATION_H
#define STDLOCATION_H
#include "tvector.h"
#include "tmatrix.h"
#include "player.h"
#include "gui.h"
/*
 *	Welcome to my location class.
 *	Ad you may have guessed, it deals with the player's location and movement, but also triggers event handling and battles.
 *
 *	Simply use the default constructor to take advantage of this class.
 *		Location Map;
 *
 *		The default constructor searches through the file "maps" for the word "default " by itself on a line, and after following it loads
 *	the name of the map on the following line. See the maps file for details on format.
 *	
 *		After the name of the default map is acquired, the Teleport(string) function is called with the name of the default map, which results in
 *	the loading of that map.
 *	
 *	A Visual representation of the map can be acquired by using the Display() function, which returns a tvector of strings equivalent to the map.
 *		tvector<string> = Map.Display();
 *	
 *		Movement is used through the Move(GUI, Player,string) function. It accepts a string arugement, and based on the first character 
 *	makes a move.'1' is left, '2' is down, '3' is right, and '5' is up. This function also calls other functions to deal with events and random 
 *	battles.
 *		Map.Move(GUI, Player, "2");
 *
 */
namespace std {

struct tEvent		//a struct to simply to hold event locations and targets
{
	int Row;
	int Col;
	string Name;
	int tRow;
	int tCol;
};

class Location
{
	public:
		Location();		//constructor
		tvector<string> Display();		//generates strings to represent the map
		void Move(GUI &Interface, Player &thePlayer, string direction);		//moves the charecter on the map and calls functions to handle events
		void Teleport(string targetMap, int Row = 0, int Col = 0);		//does the actual loading of maps...or forceful relocation
	~Location();
	
	private:
		tmatrix<int> 	Moves;				//all variables pertaining to the map that's loaded currently
		tmatrix<char> 	DisplayMat;
		tvector<tEvent> Events;
		tvector<tEvent> Towns;
		tvector<tEvent> Shops;
		tvector<tEvent> Exits;
		tvector<int> 	Monsters;
		int 			BattlePercent;
		int 			locRow;
		int 			locCol;
		string 			MapName;
		int EventHandler(GUI &Interface, Player &thePlayer, int eventCode);

};

}

#endif

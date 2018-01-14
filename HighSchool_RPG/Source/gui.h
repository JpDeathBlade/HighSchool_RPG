/***********************************************************************
 *   Author: Ben Shecter                                               *
 *   Date Created: Tue May 22 2007                                     *
 *   Date Modified: Tue May 22 2007                                    *
 ***********************************************************************/
#ifndef STDGUI_H
#define STDGUI_H

#include <string>
#include "tvector.h"
#include "player.h"

namespace std 
{
/*
 *								"GUI" class
 *		This class creates and handles a text based "gui" as I call it.
 *		
 *		There is only one constructor.
 *			GUI Interface;
 *		To make it display, use one of the Show() function calls
 *		One uses no player data, the other uses player data to display player info.
 *		Both use getline to hang the screen, and return the string that the getline retreves
 *			Interface.Show();      // yields something like this
 *		+-----------------------------------------------------------------------------+
 *		|                                                                             |
 *		|                                                                             |
 *		|           *     ******* *** *   * *******   ***  ****  ***      *           |
 *		|           ***      *    *    * *     *      *  * *  * *       ***           |
 *		|           *****    *    **    *      *      *  * **** *  ** *****           |
 *		|           ***      *    *    * *     *      * *  *    *   *   ***           |
 *		|           *        *    *** *   *    *      *  * *     ***      *           |
 *		|                                                                             |
 *		|                                1. New Game                                  |
 *		|                                2. Load Game                                 |
 *		|                                3. Credits                                   |
 *		|                                4. Exit                                      |
 *		|                                                                             |
 *		|                                                                             |
 *		|                                                                             |
 *		+-----------------------------------------------------------------------------+
 *		|                                                                             |
 *		|                                                                             |
 *		+-----------------------------------------------------------------------------+
 *
 *
 *
 *		>What would you like to do?: 
 * 
 *		While
 *		Interface.Show(thePlayer);   // yields something like this
 *		+-----------------------------------------------------------------------------+
 *		|                                                                             |
 *		|                                                                             |
 *		|                                                                             |
 *		|                                  #########                                  |
 *		|                                  #T#####T#                                  |
 *		|                                  #   #   #                                  |
 *		|                                  ### # ###                                  |
 *		|                                  #  @   X#                                  |
 *		|                                  # ### ###                                  |
 *		|                                  # ###  ##                                  |
 *		|                                  #X#### T#                                  |
 *		|                                  #########                                  |
 *		|                                                                             |
 *		|                                                                             |
 *		|                                                                             |
 *		+-----------------------------------------------------------------------------+
 *		|Ben                                                                        $0|
 *		|HP: 10/10 MP: 12/12                                             Lvl: 1 Exp: 0|
 *		+-----------------------------------------------------------------------------+
 *		 What would you like to do?: 1
 *		 What is your name?: Ben
 *		 Hello Ben!
 *		>
 *
 *		The display in the top box can be set with a vector of strings using
 *			Interface.setDisplay(tvector<string> variable here);
 *		The length of the vector should not exceed 13 lines.
 *		The current display can also be retreived as a tvector of strings with
 *			Interface.getDisplay();
 *
 *		The lower area is called the history. It is 4 lines long.
 *		Lines can be added to the end with
 *			Interface.AppendLine("some string here");
 *		The history can also be set and recalled like the display.
 *			Interface.setHistory(tvector<string> something);
 *				*Note, the length of the history should not exceed 4 lines
 *			Interface.getHistory();
 *
 *		Interface.getEcho();  // returns 0 or 1 based upn the echo state.
 *		Interface.noEcho();   // turns echo off
 *		Interface.Echo();     // turns echo on
 *		the same goes for the scroll series of functions
 *		
 */
class GUI
{
	public:
		//Constructor
		GUI();
		//show functions
		string          Show(Player thePlayer);
		string          Show();
		//display and history
		void            setDisplay(tvector<string> disp);
		void            setHistory(tvector<string> hist);
		void            AppendLine(string line);
		tvector<string> getDisplay();
		tvector<string> getHistory();
		//echo and scroll family
		int             getEcho();
		void            Echo();
		void            NoEcho();
		int             getScroll();
		void            Scroll();
		void            NoScroll();
		
		~GUI();
	private:
		tvector<string> Display;
		tvector<string> History;
		int             ScrollState;
		int             EchoState;
};

}

#endif

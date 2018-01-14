/*

    Application Name: Player Class - player.h
	Designed by: Joe Stuhr
	Date Created: Wednesday, May 23, 2007
	Date Modified: Monday, June 4, 2007
	
	Discription: Class to control all the players actions withing our texted based rgp.

*/

#ifndef _PLAYER_H
#define _PLAYER_H

#include <iostream>
#include "tvector.h"
using namespace std;

struct trackEvent
{
	int id;
	int triggered;
};

class Player
{
    public:
	
	    //Constructors
	    
        Player();  //Default
        Player(string PName);  //New Player Setup
		Player(string PName, int PLevel, int PCash, int PHp, int PMaxHp, int PMp, int PMaxMp, int PExp, int PStr, int PDex, int PCon, int PInt, int PWis, int PCha, int PDef, int PAttPow);
		  //Load Player Setup
		  // myPlayer(Name,Level,Cash,Hp,MaxHp,Mp,MaxMp,Exp,Str,Dex,Con,Int,Wis,Cha,Def,AttPow);
        
        string getName();
        
        int  getLevel();
        void levelUp();
        
        int  getCash();
        void addCash(int NewAmount);
        void subCash(int NewAmount);
        
        int  getHp();
		void healHp(int NewAmount);
		int lossHp(int NewAmount);
        int  getMaxHp();
        
        int  getMp();
		void healMp(int NewAmount);
	    int lossMp(int NewAmount);
        int  getMaxMp();
        
        int  getExp();
        void addExp(int NewAmount);
		
		int  getStr();
		int  getDex();
		int  getCon();
		int  getInt();
		int  getWis();
		int  getCha();
		
		int  getDef();
		int  getAttPow();
		
		tvector<trackEvent> events;
		
		//Load players stats individualy...
		
		void loadName(string PName);
		void loadLevel(int PLevel);
		void loadCash(int PCash);
		void loadHp(int PHp);
		void loadMaxHp(int PMaxHp);
		void loadMp(int PMp);
		void loadMaxMp(int PMaxMp);
		void loadExp(int PExp);
		void loadStr(int PStr);
		void loadDex(int PDex);
		void loadCon(int PCon);
		void loadInt(int PInt);
		void loadWis(int PWis);
		void loadCha(int PCha);
		void loadDef(int PDef);
		void loadAttPow(int PAttPow);
        
    private:
        string Name;
        int  Level;
        int  Cash; 
        int  Hp; 
        int  MaxHp;
        int  Mp;
        int  MaxMp;
        int  Exp;
        
        int  Str;
        int  Dex;
        int  Con;
        int  Int;
        int  Wis;
        int  Cha;
		
		int  Def;
		int  AttPow;
};

#endif    // _PLAYER_H not defined

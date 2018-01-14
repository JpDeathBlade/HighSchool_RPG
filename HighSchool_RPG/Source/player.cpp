/*

    Application Name: Player Class - player.cpp
	Designed by: Joe Stuhr
	Date Created: Wednesday, May 23, 2007
	Date Modified: Monday, June 4, 2007
	
	Discription: Class to control all the players actions withing our texted based rgp.

*/

#include <iostream>
#include "player.h"
#include "randgen.h"
using namespace std;

Player::Player()
{
        Name = "Warrior";  //If you use this you shouldnt be aloud to play...
        Level = 1;         // Default player function
        Cash = 0;          //   - Only for Mr Patel =)
        Hp = 0; 
        MaxHp = 0;
        Mp = 0;
        MaxMp = 0;
        Exp = 0;
        
        Str = 0;
        Dex = 0;
        Con = 0;
        Int = 0;
        Wis = 0;
        Cha = 0;
		Def = 0;  
}
Player::Player(string PName)
{
        RandGen myRand;
		myRand.RandInt(20);
		myRand.RandInt(20);
		
		Name = PName;
        Level = 1;   //Starting Level
        Cash = 0;    //Starting Cash
        MaxHp = myRand.RandInt(8,16);   //Starting Hp - Random from 8 to 16
		Hp = MaxHp;  //Full Hp
        MaxMp = myRand.RandInt(8,16);   //Starting Mp - Random from 8 to 16
		Mp = MaxMp;  //Full Mp
        Exp = 0;     //Starting Exp
        
        /* Each score will be in the range of 3 (really poor) to 18 (very good), 
        with 10 being average. Each ability score shows how good (or bad) you are 
        in a given field. Strength determines your muscluar ability, dexterity is 
        your speed and hand-eye cordination. Constitution is how tough you are. 
        Your intelligence determines how well you learn new things. 
        Wisdom is an indicater of how aware you are of the given situation and charisma 
        determines how well you interact with others. */
		
		//Str - Power of the Hit
		//Dex - Higher the Dex the faster you hit (higher dex, first hit)
		//Con - Hit Rate%
		
		//Int - Using certin items (lockpick, etc)
		//Wis - Random battles (higher wisdom, less battles)
		//Cha - Needed to start quests
        
        Str = myRand.RandInt(3,18);  //Starting Str - Random from 3 to 18
        Dex = myRand.RandInt(3,18);  //Starting Dex - Random from 3 to 18
        Con = myRand.RandInt(3,18);  //Starting Con - Random from 3 to 18
        Int = myRand.RandInt(3,18);  //Starting Int - Random from 3 to 18
        Wis = myRand.RandInt(3,18);  //Starting Wis - Random from 3 to 18
        Cha = myRand.RandInt(3,18);  //Starting Cha - Random from 3 to 18
		Def = myRand.RandInt(3,18);  //Starting Def - Random from 3 to 18
		AttPow = myRand.RandInt(3,18);  //Starting AttPow - Random from 3 to 18
}
Player::Player(string PName, int PLevel, int PCash, int PHp, int PMaxHp, int PMp, int PMaxMp, int PExp, int PStr, int PDex, int PCon, int PInt, int PWis, int PCha, int PDef, int PAttPow)
{
        Name = PName;    //Load a character from a text file
        Level = PLevel;  //Intakes players saved stats...
        Cash = PCash;    //And stores them into the variables
        Hp = PHp; 
        MaxHp = PMaxHp;  //Variable orders are the same
        Mp = PMp;
        MaxMp = PMaxMp;
        Exp = PExp;
        
        Str = PStr;
        Dex = PDex;
        Con = PCon;
        Int = PInt;
        Wis = PWis;
        Cha = PCha;  
		Def = PDef;
		AttPow = PAttPow;
}
string Player::getName()
{
       return Name;  //Prints your Name
}
int Player::getLevel()
{
       return Level;  //Prints your Level
}
void Player::levelUp()
{
       RandGen myRand;

       Level++;  //Level plus 1
	   MaxHp = MaxHp + myRand.RandInt(0,3);  //MaxHp + random number from 0 to 3
	   MaxMp = MaxMp + myRand.RandInt(0,3);  //MaxMp + random number from 0 to 3
	   
	   Str = Str + myRand.RandInt(0,3);  //Str + random number from 0 to 3
	   Dex = Dex + myRand.RandInt(0,3);  //Dex + random number from 0 to 3
	   Con = Con + myRand.RandInt(0,3);  //Con + random number from 0 to 3
	   Int = Int + myRand.RandInt(0,3);  //Int + random number from 0 to 3
	   Wis = Wis + myRand.RandInt(0,3);  //Wis + random number from 0 to 3
	   Cha = Cha + myRand.RandInt(0,3);  //Cha + random number from 0 to 3
	   Def = Def + myRand.RandInt(0,3);  //Def + random number from 0 to 3
	   AttPow = AttPow + myRand.RandInt(0,3);  //AttPow + random number from 0 to 3
}
int Player::getCash()
{
       return Cash; //Prints your Cash
}
void Player::addCash(int NewAmount)
{
      Cash = Cash + NewAmount;  //Adds cash to your current Cash
}
void Player::subCash(int NewAmount)
{
      Cash = Cash - NewAmount;  //Subtracts cash from your current Cash
}
int Player::getHp()
{
       return Hp;  //Prints current Hp
}
void Player::healHp(int NewAmount)
{
    Hp = Hp + NewAmount;  //Heals Hp
	
	if (Hp > MaxHp)  //If Hp greater then MaxHp
	    Hp = MaxHp;  //Hp set to MaxHp
}
int Player::lossHp(int NewAmount)
{
    Hp = Hp - NewAmount;  //Loss Hp
	
	if (Hp <= 0)  //If Hp less then 0
	    return 0;
	else
	    return 1;
}
int Player::getMaxHp()
{
       return MaxHp;  //Prints highest possable Hp
}
int Player::getMp()
{
       return Mp;  //Prints current Mp
}
void Player::healMp(int NewAmount)
{
    Mp = Mp + NewAmount;  //Heals Mp
	
	if (Mp > MaxMp)  //If Mp greater then MaxMp
	{
	    Mp = MaxMp;  //Mp set to MaxMp
	}
}
int Player::lossMp(int NewAmount)
{
    Mp = Mp - NewAmount;  //Use Mp
	
	if (Mp <= 0)  //If Hp less then 0
	    return 0;
	else
	    return 1;
}
int Player::getMaxMp()
{
       return MaxMp; //Prints highest possable Mp
}
int Player::getExp()
{
       return Exp;  //Prints current Exp
}
void Player::addExp(int NewAmount)
{
      Exp = Exp + NewAmount;  //Adds exp to current Exp
	  
	  if (Exp >= 7327081 && Level == 98)
		      levelUp();
	  else if (Exp >= 7052896 && Level == 97)
		      levelUp();
	  else if (Exp >= 6786408 && Level == 96)
		      levelUp();
	  else if (Exp >= 6527474 && Level == 95)
		      levelUp();
	  else if (Exp >= 6275953 && Level == 94)
		      levelUp();
	  else if (Exp >= 6031705 && Level == 93)
		      levelUp();
	  else if (Exp >= 5794590 && Level == 92)
		      levelUp();
	  else if (Exp >= 5564471 && Level == 91)
		      levelUp();
	  else if (Exp >= 5341212 && Level == 90)
		      levelUp();	  
	  else if (Exp >= 5124677 && Level == 89)
		      levelUp();
	  else if (Exp >= 4914733 && Level == 88)
		      levelUp();
	  else if (Exp >= 4711247 && Level == 87)
		      levelUp();
	  else if (Exp >= 4514087 && Level == 86)
		      levelUp();
	  else if (Exp >= 4323124 && Level == 85)
		      levelUp();
	  else if (Exp >= 4138229 && Level == 84)
		      levelUp();
	  else if (Exp >= 3959274 && Level == 83)
		      levelUp();
	  else if (Exp >= 3786134 && Level == 82)
		      levelUp();
	  else if (Exp >= 3618683 && Level == 81)
		      levelUp();
	  else if (Exp >= 3456797 && Level == 80)
		      levelUp();
	  else if (Exp >= 3300354 && Level == 79)
		      levelUp();
	  else if (Exp >= 3149233 && Level == 78)
		      levelUp();
	  else if (Exp >= 3003315 && Level == 77)
		      levelUp();
	  else if (Exp >= 2862480 && Level == 76)
		      levelUp();
	  else if (Exp >= 2726612 && Level == 75)
		      levelUp();
	  else if (Exp >= 2595594 && Level == 74)
		      levelUp();
	  else if (Exp >= 2469312 && Level == 73)
		      levelUp();
	  else if (Exp >= 2347653 && Level == 72)
		      levelUp();
	  else if (Exp >= 2230504 && Level == 71)
		      levelUp();
	  else if (Exp >= 2117755 && Level == 70)
		      levelUp();
	  else if (Exp >= 2009296 && Level == 69)
		      levelUp();
	  else if (Exp >= 1905019 && Level == 68)
		      levelUp();
	  else if (Exp >= 1804817 && Level == 67)
		      levelUp();
	  else if (Exp >= 1708584 && Level == 66)
		      levelUp();
	  else if (Exp >= 1616216 && Level == 65)
		      levelUp();
	  else if (Exp >= 1527611 && Level == 64)
		      levelUp();
	  else if (Exp >= 1442666 && Level == 63)
		      levelUp();
	  else if (Exp >= 1361281 && Level == 62)
		      levelUp();
	  else if (Exp >= 1283358 && Level == 61)
		      levelUp();
	  else if (Exp >= 1208798 && Level == 60)
		      levelUp();
	  else if (Exp >= 1137505 && Level == 59)
		      levelUp();
	  else if (Exp >= 1069384 && Level == 58)
		      levelUp();
	  else if (Exp >= 1004341 && Level == 57)
		      levelUp();
	  else if (Exp >= 942284 && Level == 56)
		      levelUp();
	  else if (Exp >= 883122 && Level == 55)
		      levelUp();
	  else if (Exp >= 826765 && Level == 54)
		      levelUp();
	  else if (Exp >= 773125 && Level == 53)
		      levelUp();
	  else if (Exp >= 722114 && Level == 52)
		      levelUp();
	  else if (Exp >= 673647 && Level == 51)
		      levelUp();
	  else if (Exp >= 627639 && Level == 50)
		      levelUp();
	  else if (Exp >= 584007 && Level == 49)
		      levelUp();
	  else if (Exp >= 542670 && Level == 48)
		      levelUp();
	  else if (Exp >= 503547 && Level == 47)
		      levelUp();
	  else if (Exp >= 466559 && Level == 46)
		      levelUp();
	  else if (Exp >= 431628 && Level == 45)
		      levelUp();
	  else if (Exp >= 398678 && Level == 44)
		      levelUp();
	  else if (Exp >= 367635 && Level == 43)
		      levelUp();
	  else if (Exp >= 338424 && Level == 42)
		      levelUp();
	  else if (Exp >= 310973 && Level == 41)
		      levelUp();
	  else if (Exp >= 285212 && Level == 40)
		      levelUp();
	  else if (Exp >= 261071 && Level == 39)
		      levelUp();
	  else if (Exp >= 238482 && Level == 38)
		      levelUp();
	  else if (Exp >= 217378 && Level == 37)
		      levelUp();
	  else if (Exp >= 197694 && Level == 36)
		      levelUp();
	  else if (Exp >= 179365 && Level == 35)
		      levelUp();
	  else if (Exp >= 162330 && Level == 34)
		      levelUp();
	  else if (Exp >= 146527 && Level == 33)
		      levelUp();
	  else if (Exp >= 131896 && Level == 32)
		      levelUp();
	  else if (Exp >= 118379 && Level == 31)
		      levelUp();
	  else if (Exp >= 105919 && Level == 30)
		      levelUp();  
	  else if (Exp >= 94460 && Level == 29)
		      levelUp();
	  else if (Exp >= 83948 && Level == 28)
		      levelUp();
	  else if (Exp >= 74331 && Level == 27)
		      levelUp();
	  else if (Exp >= 65557 && Level == 26)
		      levelUp();
	  else if (Exp >= 57576 && Level == 25)
		      levelUp();
	  else if (Exp >= 50340 && Level == 24)
		      levelUp();
	  else if (Exp >= 43802 && Level == 23)
		      levelUp();
	  else if (Exp >= 37916 && Level == 22)
		      levelUp();
	  else if (Exp >= 32639 && Level == 21)
		      levelUp();
	  else if (Exp >= 27927 && Level == 20)
		      levelUp();
	  else if (Exp >= 23740 && Level == 19)
		      levelUp();
	  else if (Exp >= 20037 && Level == 18)
		      levelUp();
	  else if (Exp >= 16781 && Level == 17)
		      levelUp();
	  else if (Exp >= 13934 && Level == 16)
		      levelUp();
	  else if (Exp >= 11462 && Level == 15)
		      levelUp();
	  else if (Exp >= 9331 && Level == 14)
		      levelUp();
	  else if (Exp >= 7508 && Level == 13)
		      levelUp();
	  else if (Exp >= 5963 && Level == 12)
		      levelUp();
	  else if (Exp >= 4666 && Level == 11)
		      levelUp();
	  else if (Exp >= 3590 && Level == 10)
		      levelUp();  
	  else if (Exp >= 2708 && Level == 9)
		      levelUp();
	  else if (Exp >= 1996 && Level == 8)
		      levelUp();
	  else if (Exp >= 1432 && Level == 7)
		      levelUp();
	  else if (Exp >= 993 && Level == 6)
		      levelUp();
	  else if (Exp >= 660 && Level == 5)
		      levelUp();
	  else if (Exp >= 414 && Level == 4)
		      levelUp();
	  else if (Exp >= 239 && Level == 3)
		      levelUp();
	  else if (Exp >= 121 && Level == 2)
		      levelUp();
	  else if (Exp >= 45 && Level == 1)
		      levelUp();
}
int Player::getStr()
{
       return Str;  //Prints current Str
}
int Player::getDex()
{
       return Dex;  //Prints current Dex
}
int Player::getCon()
{
       return Con;  //Prints current Con
}
int Player::getInt()
{
       return Int;  //Prints current Int
}
int Player::getWis()
{
       return Wis;  //Prints current Wis
}
int Player::getCha()
{
       return Cha;  //Prints current Cha
}
int Player::getDef()
{
       return Def;  //Prints current Cha
}
int Player::getAttPow()
{
       return AttPow;  //Prints current Cha
}
void Player::loadName(string PName)
{
       Name = PName;
}
void Player::loadLevel(int PLevel)
{
       Level = PLevel;
}
void Player::loadCash(int PCash)
{
       Cash = PCash;
}
void Player::loadHp(int PHp)
{
       Hp = PHp;
}
void Player::loadMaxHp(int PMaxHp)
{
       MaxHp = PMaxHp;
}
void Player::loadMp(int PMp)
{
       Mp = PMp;
}
void Player::loadMaxMp(int PMaxMp)
{
       MaxMp = PMaxMp;
}
void Player::loadExp(int PExp)
{
       Exp = PExp;
}
void Player::loadStr(int PStr)
{
       Str = PStr;
}
void Player::loadDex(int PDex)
{
       Dex = PDex;
}
void Player::loadCon(int PCon)
{
       Con = PCon;
}
void Player::loadInt(int PInt)
{
       Int = PInt;
}
void Player::loadWis(int PWis)
{
       Wis = PWis;
}
void Player::loadCha(int PCha)
{
       Cha = PCha;
}
void Player::loadDef(int PDef)
{
       Def = PDef;
}
void Player::loadAttPow(int PAttPow)
{
       AttPow = PAttPow;
}
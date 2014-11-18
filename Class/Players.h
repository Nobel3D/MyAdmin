#pragma once
#include "..\stdafx.h"
#include "Database.h"

/*This value is changeble, for more player in the game*/
#define MAXPLAYERSUPPORT 16

/*For System::String^ and maybe something*/
using namespace System;

/*Player Class by Nobel3D*/
ref class Players
{
private:
	/*The string of the currently name of the player*/
	String^ str_Name;
	/*The Steam's ID hexadecimal code?*/
	String^ str_ID;
	/*This is the old count of the player, now is useless*/
	static int Index;
	/*Real index of sam*/
	int Sam;
	/*database Index for loaded player*/
	int indexDB;
	/*Points of the player*/
	int all_Point;
	/*Deads of the player*/
	int all_Dead;
	/*Kills of the player*/
	int all_Kill;
	/*this match Deads*/
	int this_Dead;
	/*this match Kills*/
	int this_Kill;

	/*This player is joined on the server? (But Spectator)*/
	bool Initialize;
	/*This player is joined on the game?*/
	bool JoinGame;

	/*This is the char separator of all field on banlist, and ex ndb*/
	static array<String^>^ Separator = { "," };
	/*The pointer to the database used in MyRanked */
public: static Database^ dbUsed = gcnew Database("", "", "", "", "",false);

public:
	/*Constructor*/

	/*Player aren't initialize*/
	Players();
	/*Player has join into the lobby, but he not has join into the game*/
	Players(String^ ID, int SamIndex);
	/*Player has join into the game, but he wasn't load (first time joined) */
	Players(String^ ID, String^ Name, int SamIndex);
	/*Player has join into the game and he was loaded*/
	Players(String^ ID, String^ Name, int allKill, int allDead, int allPoint, int SamIndex, int _indexDB);

	/*It saves statistics of the player*/
	bool Save();
	/*It loads statistics of the player*/
	static Players^ Load(String^ ID, int SamIndex);
	/*It loads statistics of the player*/
	static Players^ Load(String^ ID,String^ Name, int SamIndex);

	/*The player has killed, Weapon is not yet supported*/
	void Ikill(String^ Weapon);
	/*The player was killed*/
	void Idead();
	/*The player committed suicide*/
	void Ikillme();
	/*The player has won the match*/
	void Iwin();
	/*It cleans the match stats*/
	void Clean();
	/*The player was banned*/
	void Ban(String^ Time);
	/*The player has left the game*/
	void Left();
	/*The player was unbanned*/
	static bool Unban(String^ IDBan);
	/*It check if the player was banned*/
	static bool IsBanned(String^ ID);
	/*Transform code adapted to markup*/
	static String^ markupCode(String^ ID);

	/*They have a so bad score*/
	static void Weloser(array<Players^>^ MyPlayers);
	/*The index of the winner on the match*/
	static int WinnerIndex(array<Players^>^ MyPlayers);
	/*Clean all player*/
	static void cleanAll(array<Players^>^ MyPlayers);
	/*Find the index of this string ID*/
	static int FindIndex(array<Players^>^ MyPlayers, String^ ID);
	/*Find the first free index -> this is useless, because already Sam manage it*/
	static int FreeIndex(array<Players^>^ MyPlayers);
	/*Anyone have gotten the win? never used, lol*/
	static int FragLimit(array<Players^>^ MyPlayers, int Limits);
	/*The player is already joined in the game?*/
	static bool AlreadyStarted(array<Players^>^ MyPlayers, String^ Ask);
	/*Who is the better player?*/
	static Players^ betterPlayer(array<Players^>^ MyPlayer);
	/*Save all stats about players*/
	static void SaveAll(array<Players^>^ MyPlayers);

	String^ getID();
	String^ getName();
	int getPoint();
	int getKill();
	int getDead();
	int getSamIndex();
	bool getInitialize();
	static int getIndex();

	/*mmh mmh mmh...*/
	bool operator!= (Players^ Equals);
};


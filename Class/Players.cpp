#include "..\stdafx.h"
#include "Players.h"


using namespace System;

Players::Players()
{
	Initialize = false;
}
Players::Players(String^ ID, int SamIndex)
{
	str_ID = ID;
	Sam = SamIndex;
	Initialize = true;
	JoinGame = false;
	Index++;
}
Players::Players(String^ ID, String^ Name, int SamIndex)
{
	str_ID = ID;
	str_Name = Name;
	Sam = SamIndex;
	all_Point = 1500;
	this_Dead = 0;
	this_Kill = 0;
	Initialize = true;
	JoinGame = true;
}
Players::Players(System::String^ ID, System::String^ Name, int allKill, int allDead, int allPoint, int SamIndex, int _indexDB)
{
	str_ID = ID;
	str_Name = Name;
	Sam = SamIndex;
	all_Kill = allKill;
	all_Dead = allDead;
	all_Point = allPoint;
	indexDB = _indexDB;
	Initialize = true;
	JoinGame = true;
}


bool Players::IsBanned(System::String ^ID)
{
	if (IO::File::Exists("BanList.ban"))
	{
		IO::StreamReader^ ReadBanList = gcnew IO::StreamReader("BanList.ban");
		array<String^>^ Separator = { "," };
		array<array<String^>^>^ Line = gcnew array<array<String^>^>(50);
		String^ Part;
		DateTime^ Time = DateTime::Now;
		int i = 0;
		bool ItsTrue = false;

		while (!ReadBanList->EndOfStream)
		{
			Line[i] = gcnew array<String^>(2);
			Part = ReadBanList->ReadLine();
			Line[i] = Part->Split(Separator, StringSplitOptions::None);
			if (Line[i][0] == ID&&Time->CompareTo(Convert::ToDateTime(Line[i][1]))<1)
			{
				ItsTrue = true;
			}
		}
		ReadBanList->Close();
		return ItsTrue;
	}
	else
		return false;
}

void Players::Ikill(String^ Weapon)
{

	this_Kill++;
	all_Kill++;
	all_Point++;
}

void Players::Idead()
{
	this_Dead++;
	all_Dead++;
	all_Point--;

}

void Players::Ikillme()
{
	this_Dead++;
	this_Kill--;
	all_Dead++;
	all_Kill--;
	all_Point -= 2;
}

void Players::Iwin()
{
	all_Point += 20;
}

void Players::Weloser(array<Players^>^ MyPlayers)
{
	for (int i = 0; i<Index; i++)
	{
		if (MyPlayers[i]->Initialize != false)
		{
			if (MyPlayers[i]->this_Kill>0 && MyPlayers[i]->this_Dead > 0)
			{

				if ((MyPlayers[i]->this_Kill / MyPlayers[i]->this_Dead) < 0.50)
				{
					MyPlayers[i]->all_Point -= 15;
				}
			}
			else
			{
				if (MyPlayers[i]->this_Kill < 1)
					MyPlayers[i]->all_Point -= 15;
			}
		}
	}
}

bool Players::Save()
{
	dbUsed->Query("UPDATE players SET killPlayer =" + Convert::ToString(this->all_Kill) +
	" , deadPlayer = " + Convert::ToString(this->all_Dead) +
	" , pointPlayer = " + Convert::ToString(this->all_Point) +
	" WHERE steamPlayer = '" + this->str_ID + "'");
	return true;
}

Players^ Players::Load(System::String^ ID, int SamIndex)
{
	Players^ notLoaded = gcnew Players(ID, SamIndex);
	return notLoaded;
}

Players^ Players::Load(System::String^ ID,System::String^ Name, int SamIndex)
{
	String^ NAME = markupCode(Name);
	array<array<String^>^>^ dbFind = dbUsed->Query("SELECT * FROM players WHERE steamPlayer");
	if (dbUsed->getInitialize())
	for (int i = 0; i < dbFind->Length;i++)
	if (dbFind[i][1] == ID)
	{
		Players^ Loaded = gcnew Players(dbFind[i][1], dbFind[i][6], Convert::ToInt32(dbFind[i][2]), Convert::ToInt32(dbFind[i][4]), Convert::ToInt32(dbFind[i][3]), SamIndex, Convert::ToInt32(dbFind[i][0]));
		return Loaded;
	}
	dbUsed->Query("INSERT INTO `players` (`steamPlayer`,`killPlayer`,`pointPlayer`,`deadPlayer`,`adminPlayer`,`namePlayer`) VALUES( '" + ID + "' ,0,1500,0,0, ' " + NAME + " ' )");
	Players^ notLoaded = gcnew Players(ID, Name, SamIndex);
	return notLoaded;
}


int Players::WinnerIndex(cli::array<Players^>^ MyPlayers)
{
	try
	{

		Players^ a = gcnew Players("","",-1);
		int nn;
		a->this_Kill = 0;
		for (int i = 0; i<MAXPLAYERSUPPORT; i++)
		{
			if (MyPlayers[i]->JoinGame == true)
			{

				if (MyPlayers[i]->this_Kill > a->this_Kill)
				{
					a = MyPlayers[i];
					nn = i;
				}
			}
		}
		return nn;
	}
	catch (Exception^ io){}
}

void Players::cleanAll(cli::array<Players^>^ MyPlayers)
{
	for (int i = 0; i<MAXPLAYERSUPPORT; i++)
		MyPlayers[i]->Clean();
}

int Players::FindIndex(cli::array<Players^>^ MyPlayers, String^ ID)
{
	int a = -1;
	for (int i = 0; i<MAXPLAYERSUPPORT; i++)
	{
		if (MyPlayers[i]->Initialize==true)
		if (MyPlayers[i]->getID() == ID)
			a = i;
	}
	return a;
}

int Players::FreeIndex(cli::array<Players^>^ MyPlayers)
{
	for (int i = 0; i<MAXPLAYERSUPPORT; i++)
	{
		if (MyPlayers[i]->Initialize == false)
			return i;
	}
}

int Players::FragLimit(cli::array<Players^>^ MyPlayers, int Limits)
{
	for (int i = 0; i<MAXPLAYERSUPPORT; i++)
	{
		if (MyPlayers[i]->JoinGame==true)
		if (MyPlayers[i]->this_Kill >= Limits)
		{
			return i;
		}
	}
	return -1;
}

Players^ Players::betterPlayer(cli::array<Players^>^ MyPlayers)
{
	Players^ ab;
	for (int i = 0; i<MAXPLAYERSUPPORT; i++)
	{
		if (MyPlayers[i]->JoinGame==true)
		if (MyPlayers[i]->this_Kill >= ab->this_Kill)
			ab = MyPlayers[i];
	}
	return ab;
}

bool Players::AlreadyStarted(cli::array<Players^>^ MyPlayers, String^ Ask)
{
	bool result = false;
	for (int i = 0; i < MAXPLAYERSUPPORT; i++)
	{
		if (MyPlayers[i]->JoinGame == true)
		if (MyPlayers[i]->getID() == Ask)
			return true;
	}
	return result;

}
void Players::SaveAll(cli::array<Players^>^ MyPlayers)
{
	for (int i = 0; i < MyPlayers->Length; i++)
	{
		if (MyPlayers[i]->JoinGame)
			MyPlayers[i]->Save();
	}
}

bool Players::operator !=(Players ^Equals)
{
	if (this->str_ID != Equals->str_ID)
		return true;
	else
		return false;
}

void Players::Clean()
{
	this_Dead = 0;
	this_Kill = 0;
}

void Players::Left()
{
	if (Initialize)
		Save();
	if (Index > 0)
		Index--;
	Clean();
	Initialize = false;
	str_Name = "";
	str_ID = "";
	all_Dead = 0;
	all_Kill = 0;
}

void Players::Ban(String^ Time)
{
	IO::StreamWriter^ BanList = gcnew IO::StreamWriter("BanList.ban", true);
	BanList->WriteLine(str_ID + "," + Time);
	BanList->Close();
}

bool Players::Unban(String^ IDBan)
{
	if (IO::File::Exists("BanList.ban"))
	{
		IO::StreamReader^ BanList = gcnew IO::StreamReader("BanList.ban");
		array<String^>^ Separator = { "," };
		array<array<String^>^>^ Line = gcnew array<array<String^>^>(50);
		String^ Part;
		array<array<String^>^>^ Safe = gcnew array<array<String^>^>(50);
		int i = 0;
		int f = 0;
		while (!BanList->EndOfStream)
		{
			Line[i] = gcnew array<String^>(2);
			Part = BanList->ReadLine();
			Line[i] = Part->Split(Separator, StringSplitOptions::None);
			if (Line[i][0] != IDBan)
			{
				Safe[f] = gcnew array<String^>(2);
				Safe[f] = Line[i];
				f++;
			}
			i++;
		}
		BanList->Close();
		IO::StreamWriter^ NewBanList = gcnew IO::StreamWriter("Banlist.ban", false);
		for (int i = 0; i < f; i++)
		{
			NewBanList->WriteLine(Safe[i][0] + "," + Safe[i][1]);
		}
		NewBanList->Close();
		return true;
	}
	else
		return false;
}

String^ Players::markupCode(String^ strText)
{
	String^ ret = strText;
	ret = ret->Replace("<", "&lt;");
	ret = ret->Replace(">","&gt;");
	ret = ret->Replace("\"", "&quot;");
	ret = ret->Replace("'", "&apos;");
	ret = ret->Replace("&", "&amp;");
	ret = ret->Replace("\n","\\n");
	return ret;
}

int Players::getDead()       { return this_Dead; }
int Players::getKill()       { return this_Kill; }
int Players::getPoint()      { return all_Point; }
int Players::getSamIndex()   { return Sam; }
String^ Players::getID()     { return str_ID; }
String^ Players::getName()   { return str_Name; }
bool Players::getInitialize(){ return Initialize; }
int Players::getIndex()		 { return Index; }
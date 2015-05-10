#pragma once 

using namespace System;

enum Permissions {Standard=0, Middle=1, Full=2, Total=3};

ref class Admin
{
private:
	Permissions levelAdmin;
	String^ NameID;

public:
	static int checkCredential(String^ UserID);
	static bool addCredential(String^ UserID, Permissions TypeUser);
	static bool isCommand(String^ strChat, int adminPermission);
	Admin(String^ UserID);
	bool static callKick(String^ idKicked);
	bool static callBan(String^ idBanned);
	bool static callPassVote();
	bool static callFailVote();
	bool static callCheat(int levelCheat);
	bool static callChangeMap(String^ Map);
};
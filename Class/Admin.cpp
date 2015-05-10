#include "Admin.h"

using namespace System;

Admin::Admin(String^ UserID)
{
	this->NameID = UserID;
}

int Admin::checkCredential(String^ UserID)
{
	if (IO::File::Exists("List.dat"))
	{
		IO::StreamReader^ fileCred = gcnew IO::StreamReader("List.dat");
		while (fileCred->EndOfStream)
		{
			array<String^>^ SavedAdmin = fileCred->ReadLine()->Split(gcnew array < String^ > {","}, StringSplitOptions::None);
			if (SavedAdmin[0] == UserID)
			{
				return Convert::ToInt32(SavedAdmin[1]);
			}
		}
		return -1;
	}
	return -1;
}
bool Admin::addCredential(String^ UserID, Permissions TypeUser)
{
	IO::StreamWriter^ fileCred = gcnew IO::StreamWriter("List.dat", true);
	fileCred->WriteLine(UserID + "," + TypeUser);
	fileCred->Close();
	return true;
}
bool Admin::isCommand(String^ strChat, int adminPermission)
{
	if (strChat == "votePass()"&&adminPermission>=1)
		callPassVote();
	else if (strChat == "voteFail()")
		callFailVote();
	else if (strChat->StartsWith("changeMap(\""))

}
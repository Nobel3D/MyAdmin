#pragma once
#include "..\stdafx.h"
using namespace MySql::Data::MySqlClient;
using namespace System;
using namespace System::Data;
using namespace System::Collections::Generic;
/*
** Thanks Angelo Geels for his notes about databases, you can see on https://github.com/AngeloG/SSNL-Manager
*/
ref class Database
{
private:
	/*The pointer of database connection*/
	MySqlConnection^ connection;
	/*The statament of database connection*/
	String^ connectionString;
	/*the Status about the databse connection*/
	String^ strStatus;
	/*Manager of Error into the connection*/
	int countTry;
	/*MyRanked is started, the connection is real?*/
	bool MyRanked;
public:
	/*Create a connection string for setting up all params*/
	Database(String^ host, String^ port, String^ database, String^ username, String^ password, bool MyRanked);

	/*Start the connection*/
	bool Open();
	/*Send a command on the database, if the connection is started*/
	array<array<String^>^>^ Query(String^ qry);
	/*The structure of the data that we receive from the server */
	array<array<String^>^>^ Rows(IDataReader^ rowdata);
	/*mmh, this is a cat*/
	String^ Safe(String^ str);
	/*Manager of the error of connection*/
	String^ dbError();

	/*The connection is stared?*/
	bool getInitialize();
};
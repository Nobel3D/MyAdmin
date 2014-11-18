#pragma once

/*
** Thanks Angelo Geels for his notes about databases, you can see on https://github.com/AngeloG/SSNL-Manager
*/
#include "..\stdafx.h"
#include "Database.h"

using namespace MySql::Data::MySqlClient;
using namespace System::Data;
using namespace System;
using namespace System::Collections::Generic;

	Database::Database(String^ host, String^ port, String^ database, String^ username, String^ password, bool _MyRanked)
	{
		MyRanked = _MyRanked;
		if (_MyRanked)
		{
			this->connectionString = "datasource=" + host + ";" +
				"port=" + port + ";" +
				"username=" + username + ";" +
				"password=" + password + ";" +
				"Database=" + database + ";" +
				"Pooling=false;CharSet=utf8;";
			Open();
		}
	}
	bool Database::Open()
	{
		if (MyRanked)
		{
			this->connection = gcnew MySqlConnection(this->connectionString);
			try
			{
				connection->Open();
				return true;
			}
			catch (Exception^ ex)
			{
				strStatus = "MySQL seems dead. Retrying...";
				dbError();
			}
		}
	}


	array<array<String^>^>^ Database::Query(String^ qry)
	{
		if (MyRanked)
		{
			IDbCommand^ dbcmd = this->connection->CreateCommand();
			dbcmd->CommandText = qry;
			IDataReader^ dr = nullptr;
			try
			{
				dr = dbcmd->ExecuteReader();
			}
			catch (Exception^ ex)
			{
				this->strStatus = "QUERY ERROR:" + ex->Message + "QUERY WAS:" + qry;
				dbError();
			}

			if (dr == nullptr && this->connection->State != ConnectionState::Connecting) {
				this->connection->Close();
				this->Open();

				return Query(qry);
			}

			return Rows(dr);
		}
	}

	array<array<String^>^>^ Database::Rows(IDataReader^ rowdata)
	{
		List<array<String^>^>^ rows = gcnew List<array<String^>^>();
		array<String^>^ field = gcnew array<String^>(rowdata->FieldCount);

		while (rowdata->Read()) 
		{
			for (int i = 0; i < rowdata->FieldCount; i++)
			{
				field[i] = (rowdata->GetValue(i)->ToString())->Trim();
			}

			rows->Add(field);
		}

		rowdata->Close();
		rowdata = nullptr;

		return rows->ToArray();
	}

	String^ Database::Safe(String^ str)
	{
		return str->Replace("\\", "\\\\")->Replace("'", "\\'")->Replace("`", "\\`");
	}

	String^ Database::dbError()
	{ 
		if (countTry < 10)
		{
			countTry++;
		}
		else
		{
			Windows::Forms::MessageBox::Show("DATABASE FATALERROR: "+strStatus);
			Windows::Forms::Application::Exit();
			return strStatus;
		}
		return "";
	}

	bool Database::getInitialize(){ return MyRanked; }
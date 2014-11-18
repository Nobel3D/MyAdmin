#pragma once
#include "..\stdafx.h"

using namespace System;

ref class Rcon
{
private:

	/*Connection is stated?*/
	static bool RconConnected;
	/*Ignore something*/
	bool ignoredFirst;

	//IP address of the server
	String^ IPServer;
	/*The port to which I connect*/
	int PortServer;
	/*Password of the Dedicated Server*/
	String^ Password;
	/*Status of the connection*/
	String^ Status;
	/*.NET Client connection*/
	Net::Sockets::TcpClient^ Client;
	/*DataStream*/
	static Net::Sockets::NetworkStream^ iStream;
	/*Stream Reader*/
	IO::StreamReader^ iReader;

	void setStatus(String^ _Status);

public:

	//Constructor of the connection
	Rcon(String^ _IPServer, int _PortServer, String^ _Password);
	//Try to connect
	bool connectRcon();
	/*Shut down the connection*/
	~Rcon();
	/*Send to server any string*/
	bool sendData(String^ command);
	/*get Byte from the stream and convert manually*/
	String^ getByteData();
	/*get string line from server*/
	String^ getLine();
	/*For Serious Sam chatSay method*/
	void SamChat(String^ Message);

	/*convert String to Byte, it used on send data*/
	static array<Byte>^ convertStrToByte(String^ Str);
	/*Add log in the log.txt*/
	static void addLog(String^ Log);


	static bool getOnline();
	String^ getIPServer();
	String^ getStatus();
	int getPortServer();
};


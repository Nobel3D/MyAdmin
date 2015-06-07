#pragma once
#include "Rcon.h"
#include "Players.h"

using namespace System::Net::Sockets;
using namespace System;

ref class Host
{
private:
	int netPort;
	TcpListener^ netServer;
	NetworkStream^ netStream;
	TcpClient^ netClient;
	bool isConnected;

public:
	Host(int Port);
	~Host();
	void Start();
	String^ Read();
	void Write(String^ data);
	
};
#include "Host.h"

using namespace System::Net::Sockets;
using namespace System::Net;

Host::Host(int Port)
{
	netServer = gcnew TcpListener(Port);
	netServer->Start();
}
Host::~Host()
{
	if (isConnected)
	netClient->Close();

	netServer->Stop();
}

void Host::Start()
{
	netClient = netServer->AcceptTcpClient();
	netStream = netClient->GetStream();
}

String^ Host::Read()
{
	array<Byte>^ ReadMe = gcnew array<Byte>(1024);
	while (int i = netStream->Read(ReadMe, 0, ReadMe->Length))
	{
		// Translate data bytes to a ASCII String
		return Text::Encoding::ASCII->GetString(ReadMe, 0, i);
	}
}
void Host::Write(String^ data)
{
	array<Byte>^msg = Text::Encoding::ASCII->GetBytes(data);

	netStream->Write(msg, 0, msg->Length);
}


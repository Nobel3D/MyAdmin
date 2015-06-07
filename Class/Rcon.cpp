#include "..\stdafx.h"
#include "Rcon.h"
#include "Players.h"

using namespace System::Net::Sockets;
using namespace System::IO;
using namespace System;
using namespace System::Runtime::InteropServices;

Rcon::Rcon(String^ _IPServer, int _PortServer, String^ _Password)
{
	IPServer = _IPServer;
	PortServer = _PortServer;
	Password = _Password;
}

Rcon::~Rcon()
{
	if (RconConnected == true)
	{
		sendData("chatSay(\"Log: Closing terminal of MyAdmin!\")");
		addLog("[SYS] Closing connection from " + IPServer + " : " + PortServer);
		Status = "Disconnecting";
		iReader->Close();
		iStream->Close();
		Client->Close();
		RconConnected = false;
	}
}

bool Rcon::connectRcon()
{
	try
	{
		if (RconConnected == true) //se è gia connesso non riconettere
		{
			addLog("[SYS] A socket is already connected.");
			setStatus("Already Connected!");
			return false;
		}
		addLog("[SYS] Connecting to server " + IPServer + " : " + PortServer);

		ignoredFirst = false;
		Client = gcnew TcpClient(); //creo con la gcnew un oggetto TcpClient
		Client->ReceiveTimeout = 15000; //setto il timeout di connessione
		Client->Connect(IPServer, PortServer); //apro la connessione che ha come parametri l' IP e la parta del server

		iStream = Client->GetStream(); //ottengo lo stream dati ONLINE
		iReader = gcnew StreamReader(iStream, Text::Encoding::UTF8);

		if (iStream->CanWrite == true && iStream->CanRead == true)  //Se gli stream funzionano allora continua a connetterti
		{
			addLog("[SYS] Connection initialised.");
			addLog("[SYS] Logging in...");


			String^ data = "";
			data = getLine(); //Ottieni dati dal server finche non ti chiede "login: "
			do
			{
				data = getLine();
			} while (data != "login: ");
			getLine();
			getLine();
			sendData(Password); //gli invio la password
			getLine();
			String^ LoginResult = getLine();//ottengo il risultato della connessione:
			if (LoginResult == "login: ")// se mi richiede il login: vuol dire che è sbagliata la password
			{
				addLog("[SYS] Rcon error: Incorrect login for Rcon. Rcon has to be terminated.");
				setStatus("Couldn't login to Rcon!");
				Client->Close(); //chiudo
				return false;
			}
			else
			{
				RconConnected = true;
				addLog("[SYS] Successful Connection to " + IPServer);
				setStatus("Connected!");
				return true; //mi sono connesso e ritorna vera!

			}
		}
		else
		if (iStream->CanRead == false) //non posso leggere
		{
			addLog("[SYS] Error: Can' t read. Connection will be terminated.");
			setStatus("Couldn't read!");
			Client->Close();
			return false;
		}
		else
		{
			if (iStream->CanWrite == false) //non posso scrivere
			{
				addLog("[SYS] Error: Can' t write. Connection will be terminated.");
				setStatus("Couldn't write!");
				Client->Close();
				return false;
			}

		}
	}
	catch (Exception^ Ex)
	{
		addLog("[SYS] Fatal Error tring the connection from " + IPServer + " : " + PortServer);
		Windows::Forms::MessageBox::Show("There was an error, probably the server is down, please check and retry", "ERROR CONNECTION",
			Windows::Forms::MessageBoxButtons::OK,
			Windows::Forms::MessageBoxIcon::Error);
		return false;
	}
}
String^ Rcon::getByteData()
{
	String^ myCompleteMessage = "";
	try
	{
		array<Byte>^ ReadMe = gcnew array<Byte>(1024);
		int numberOfBytesRead = 0;


		do
		{
			numberOfBytesRead = iStream->Read(ReadMe, 0,
				ReadMe->Length);
			myCompleteMessage = System::Text::Encoding::ASCII->GetString(ReadMe, 0, numberOfBytesRead);
		} 
		while (iStream->DataAvailable);
		return myCompleteMessage;
	}
	catch (IO::IOException^ Attack)
	{
		return myCompleteMessage;
	}
}

String^ Rcon::getLine()
{
	String^ Message="";
	try
	{
		Message = iReader->ReadLine();
		return Message;
	}
	catch (Exception^ xddd)
	{
		return "";
	}
}

array<Byte>^ Rcon::convertStrToByte(String^ Str)
{
	int nByte = Str->Length;

	array<Byte>^ arrayByte = gcnew array<Byte>(nByte + 1);
	IntPtr ptrNativeString = Marshal::StringToHGlobalAnsi(Str + "\r");
	char* nativeString = static_cast<char*>(ptrNativeString.ToPointer());

	for (int i = 0; i<nByte + 1; i++)
		arrayByte[i] = nativeString[i];


	return arrayByte;
}

bool Rcon::sendData(String^ command)
{
	try
	{
	int nByte = command->Length;

	iStream->Write(convertStrToByte(command), 0, nByte + 1);

	return true;
	}
	catch (Exception^ fail)
	{
		addLog("[SYS] fatal error on writing into stream");
		RconConnected = false;
		this->~Rcon();
		Status = "There was an error in writing into the stream data";
	}
}

void Rcon::SamChat(String^ Message)
{

	sendData("chatSay(\"" + Players::markupCode(Message) + "\")");
}


void Rcon::addLog(String^ Log)
{
	IO::StreamWriter^ LogWriter = gcnew StreamWriter("netlog.txt", true);
	LogWriter->WriteLine(this->getIPServer() + ":" + this->getPortServer() + "-" + DateTime::Now + " -> " + Log);
	LogWriter->Close();
}

void Rcon::addLog2(String^ Log)
{
	IO::StreamWriter^ LogWriter = gcnew StreamWriter("mainlog.txt", true);
	LogWriter->WriteLine(DateTime::Now + " -> " + Log);
	LogWriter->Close();
}

String^ Rcon::markupDecode(String^ strText)
{
	String^ ret = strText;
	ret = ret->Replace("&lt;", "<");
	ret = ret->Replace("&gt;", ">");
	ret = ret->Replace("&quot;", "\"");
	ret = ret->Replace("&apos;", "'");
	ret = ret->Replace("&amp;", "&");
	ret = ret->Replace("\\n", "\n");
	return ret;
}
/*Transform code adapted from normal text to markup code*/
String^ Rcon::markupEncode(String^ strText)
{
	String^ ret = strText;
	ret = ret->Replace("<", "&lt;");
	ret = ret->Replace(">", "&gt;");
	ret = ret->Replace("\"", "&quot;");
	ret = ret->Replace("'", "&apos;");
	ret = ret->Replace("&", "&amp;");
	ret = ret->Replace("\n", "\\n");
	return ret;
}

void Rcon::setStatus(String^ _Status) { Status = _Status; }
String^ Rcon::getStatus() { return Status; }
String^ Rcon::getIPServer() { return IPServer; }
int Rcon::getPortServer() { return PortServer; }
bool Rcon::getOnline() { return RconConnected; }

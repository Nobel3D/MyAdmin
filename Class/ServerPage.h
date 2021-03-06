#pragma once
#include "Rcon.h"
#include "Database.h"
#include "Players.h"
#include "Host.h"
#include "../Form/MyDedicated.h" //for Sam's path

using namespace System;
using namespace System::Windows::Forms;
using namespace System::Threading;

ref class ServerPage
{
private:
	Label^ addMainLabel(String^ serverIP, String^ serverPort);
	Button^ addShutdown();
	Button^ addRanked();
	Button^ addNobelBan();
	Button^ addPause();
	Button^ addDelete();
	Button^ addButtonChat();
	TextBox^ addTextChat();
	ComboBox^ addComboPlayer();
	ComboBox^ addPlayerRank();
	TextBox^ addTextRcon();
	Button^ addButtonRcon();
	Button^ addBan();
	Button^ addKick();
	Button^ addFail();
	Button^ addPass();
	Button^ addHost();
	PictureBox^ addPicture(System::ComponentModel::ComponentResourceManager^  resources);

	System::Void buttonShutdown_Click(System::Object^  sender, System::EventArgs^  e);
	System::Void buttonRanked_Click(System::Object^  sender, System::EventArgs^  e);
	System::Void buttonChat_Click(System::Object^  sender, System::EventArgs^  e);
	System::Void buttonRcon_Click(System::Object^  sender, System::EventArgs^  e);
	System::Void buttonFail_Click(System::Object^  sender, System::EventArgs^  e);
	System::Void buttonPass_Click(System::Object^  sender, System::EventArgs^  e);
	System::Void buttonKick_Click(System::Object^  sender, System::EventArgs^  e);
	System::Void buttonNobelBan_Click(System::Object^  sender, System::EventArgs^  e);
	System::Void buttonBan_Click(System::Object^  sender, System::EventArgs^  e);
	System::Void buttonPause_Click(System::Object^  sender, System::EventArgs^  e);
	System::Void buttonDelete_Click(System::Object^  sender, System::EventArgs^  e);
	System::Void comboBoxPlayerRank_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e);

	System::Void delRank(String^ AddMe);
	System::Void delPlayer(String^ AddMe);
	System::Void threadRank(String^ AddMe);
	System::Void threadPlayer(String^ AddMe);

	System::Void errorConnection();
	System::Void goodConnection();
	System::Void resolvingConnection();
	System::Void processHost();
	System::Void listenDedicated();
	bool sendData(String^ data);

	TabControl^ mainControl;
	TabPage^ thisTab;
	Label^ labelMain;
	Button^ btnShutdown;
	Button^ btnRanked;
	Button^ btnNobelBan;
	Button^ btnPause;
	Button^ btnDelete;
	Button^ btnChat;
	TextBox^ txtChat;
	ComboBox^ comboPlayer;
	ComboBox^ comboRank;
	TextBox^ txtRcon;
	Button^ btnRcon;
	Button^ btnBan;
	Button^ btnKick;
	Button^ btnFail;
	Button^ btnPass;
	Button^ btnHost;
	PictureBox^ immPicture;
	System::ComponentModel::ComponentResourceManager^ resourcePtr;

	Host^ netHost;
	Rcon^ netDedicated;
	Database^ dbSam;
	array<String^>^ arrayStream;
	array<String^>^ arrayMatch;
	List<Players^>^ listPlayer;
	String^ netArgs;
	int idPage;
	int playerJoined;
	bool StartRank;
	bool hostActive;

	//Connection Host
	bool netLocal;
	TcpClient^ netClient;
	NetworkStream^ netStream;

	//Threading
	Thread^ deThread;
	ThreadStart^ deStartThread;
	Thread^ hostThread;
	ThreadStart^ hostStartThread;

	System::Void LoadPlayer(array<String^>^ ArrayStream);
public:
	~ServerPage();
	ServerPage(Rcon^ netConnection, String^ args, TabControl^ controlTab);
	TabPage^ getPage(String^ netName, System::ComponentModel::ComponentResourceManager^  resources);
	System::Void connectServer();
	System::Void startHost(System::Object^  sender, System::EventArgs^  e);
	System::Void sendServer(String^ toServer);

};
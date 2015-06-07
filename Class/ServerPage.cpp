#include "ServerPage.h"


using namespace System;
using namespace System::Windows::Forms;
using namespace System::Diagnostics;

ServerPage::ServerPage(Rcon^ netConnection, String^ args, TabControl^ controlTab)
{
	mainControl = controlTab;
	netDedicated = netConnection;
	netArgs = args;
	listPlayer = gcnew List < Players^ > ;
	idPage++;
}

ServerPage::~ServerPage()
{
	this->thisTab->Controls->Clear();
	this->thisTab->Hide();
	this->mainControl->TabPages->Remove(thisTab);
	deThread->Abort();
	netDedicated->~Rcon();
}
TabPage^ ServerPage::getPage(String^ netName, System::ComponentModel::ComponentResourceManager^  resources)
{
	labelMain = addMainLabel(netDedicated->getIPServer(), Convert::ToString(netDedicated->getPortServer()));
	immPicture = addPicture(resourcePtr = resources);
	btnShutdown = addShutdown();
	btnRanked = addRanked();
	btnNobelBan = addNobelBan();
	btnPause = addPause();
	btnDelete = addDelete();
	comboPlayer = addComboPlayer();
	comboRank = addPlayerRank();
	txtChat = addTextChat();
	btnChat = addButtonChat();
	btnRcon = addButtonRcon();
	txtRcon = addTextRcon();
	btnBan = addBan();
	btnKick = addKick();
	btnFail = addFail();
	btnPass = addPass();
	btnHost = addHost();
	thisTab = gcnew TabPage();
	thisTab->Controls->Add(labelMain);
	thisTab->Controls->Add(immPicture);
	thisTab->Controls->Add(btnShutdown);
	thisTab->Controls->Add(btnRanked);
	thisTab->Controls->Add(btnNobelBan);
	thisTab->Controls->Add(btnPause);
	thisTab->Controls->Add(btnDelete);
	thisTab->Controls->Add(comboPlayer);
	thisTab->Controls->Add(comboRank);
	thisTab->Controls->Add(txtChat);
	thisTab->Controls->Add(btnChat);
	thisTab->Controls->Add(btnRcon);
	thisTab->Controls->Add(txtRcon);
	thisTab->Controls->Add(btnBan);
	thisTab->Controls->Add(btnKick);
	thisTab->Controls->Add(btnFail);
	thisTab->Controls->Add(btnPass);
	thisTab->Controls->Add(btnHost);
	thisTab->Location = System::Drawing::Point(4, 4);
	thisTab->Name = L"thisTab";
	thisTab->Padding = System::Windows::Forms::Padding(3);
	thisTab->Size = System::Drawing::Size(759, 432);
	thisTab->TabIndex = 2;
	thisTab->Text = netName;
	thisTab->UseVisualStyleBackColor = true;

	connectServer();

	return thisTab;
}

#pragma region Objects
Label^ ServerPage::addMainLabel(String^ serverIP, String^ serverPort)
{
	Label^ addLabel = gcnew Label();
	addLabel->AutoSize = true;
	addLabel->Font = (gcnew System::Drawing::Font(L"Unreal Tournament", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(0)));
	addLabel->ForeColor = System::Drawing::Color::Orange;
	addLabel->Location = System::Drawing::Point(40, 20);
	addLabel->Name = L"addLabel";
	addLabel->Size = System::Drawing::Size(83, 28);
	addLabel->TabIndex = 68;
	addLabel->Text = "Server " + serverIP + " " + serverPort;

	return addLabel;
}

Button^ ServerPage::addShutdown()
{
	Button^ buttonShutdown = gcnew Button();
	buttonShutdown->Location = System::Drawing::Point(6, 67);
	buttonShutdown->Name = L"buttonShutdown";
	buttonShutdown->Size = System::Drawing::Size(141, 36);
	buttonShutdown->TabIndex = 65;
	buttonShutdown->Text = L"Shutdown Server";
	buttonShutdown->UseVisualStyleBackColor = true;
	buttonShutdown->Click += gcnew System::EventHandler(this, &ServerPage::buttonShutdown_Click);

	return buttonShutdown;
}

Button^ ServerPage::addRanked()
{
	Button^ buttonRanked = gcnew Button();
	buttonRanked->Location = System::Drawing::Point(164, 67);
	buttonRanked->Name = L"buttonRanked";
	buttonRanked->Size = System::Drawing::Size(141, 36);
	buttonRanked->TabIndex = 67;
	buttonRanked->Text = L"Start MyRanked";
	buttonRanked->UseVisualStyleBackColor = true;
	buttonRanked->Click += gcnew System::EventHandler(this, &ServerPage::buttonRanked_Click);

	return buttonRanked;
}

Button^ ServerPage::addNobelBan()
{
	Button^ button1 = gcnew Button();
	button1->Location = System::Drawing::Point(17, 322);
	button1->Name = L"button1";
	button1->Size = System::Drawing::Size(163, 44);
	button1->TabIndex = 74;
	button1->Text = L"Nobel Ban System";
	button1->UseVisualStyleBackColor = true;
	button1->Click += gcnew System::EventHandler(this, &ServerPage::buttonNobelBan_Click);

	return button1;
}

Button^ ServerPage::addPause()
{
	Button^ buttonPause = gcnew Button();
	buttonPause->Location = System::Drawing::Point(323, 67);
	buttonPause->Name = L"buttonPause";
	buttonPause->Size = System::Drawing::Size(141, 36);
	buttonPause->TabIndex = 66;
	buttonPause->Text = L"Pause Game";
	buttonPause->UseVisualStyleBackColor = true;
	buttonPause->Click += gcnew System::EventHandler(this, &ServerPage::buttonPause_Click);

	return buttonPause;
}
Button^ ServerPage::addDelete()
{
	Button^ buttonPause = gcnew Button();
	buttonPause->Location = System::Drawing::Point(323 + 164, 67);
	buttonPause->Name = L"buttonDelete";
	buttonPause->Size = System::Drawing::Size(141, 36);
	buttonPause->TabIndex = 66;
	buttonPause->Text = L"Delete Connection";
	buttonPause->UseVisualStyleBackColor = true;
	buttonPause->Click += gcnew System::EventHandler(this, &ServerPage::buttonDelete_Click);

	return buttonPause;
}

Button^ ServerPage::addButtonChat()
{
	Button^ buttonChat = gcnew Button();
	buttonChat->Location = System::Drawing::Point(667, 117);
	buttonChat->Name = L"buttonChat";
	buttonChat->Size = System::Drawing::Size(92, 32);
	buttonChat->TabIndex = 70;
	buttonChat->Text = L"Send Chat";
	buttonChat->UseVisualStyleBackColor = true;
	buttonChat->Click += gcnew System::EventHandler(this, &ServerPage::buttonChat_Click);

	return buttonChat;
}

TextBox^ ServerPage::addTextChat()
{
	TextBox^ textBoxChat = gcnew TextBox();
	textBoxChat->Location = System::Drawing::Point(8, 124);
	textBoxChat->Name = L"textBoxChat";
	textBoxChat->Size = System::Drawing::Size(643, 20);
	textBoxChat->TabIndex = 69;
	textBoxChat->Text = L"Admin Chat";

	return textBoxChat;
}
ComboBox^ ServerPage::addComboPlayer()
{
	ComboBox^ comboBoxPlayer = gcnew ComboBox();
	comboBoxPlayer->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
	comboBoxPlayer->FormattingEnabled = true;
	comboBoxPlayer->Location = System::Drawing::Point(17, 163);
	comboBoxPlayer->Name = L"comboBoxPlayer";
	comboBoxPlayer->Size = System::Drawing::Size(194, 21);
	comboBoxPlayer->TabIndex = 72;

	return comboBoxPlayer;
}

ComboBox^ ServerPage::addPlayerRank()
{
	ComboBox^ comboBoxPlayerRank = gcnew ComboBox();
	comboBoxPlayerRank->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
	comboBoxPlayerRank->FormattingEnabled = true;
	comboBoxPlayerRank->Location = System::Drawing::Point(402, 163);
	comboBoxPlayerRank->Name = L"comboBoxPlayerRank";
	comboBoxPlayerRank->Size = System::Drawing::Size(194, 21);
	comboBoxPlayerRank->TabIndex = 71;
	comboBoxPlayerRank->SelectedIndexChanged += gcnew System::EventHandler(this, &ServerPage::comboBoxPlayerRank_SelectedIndexChanged);

	return comboBoxPlayerRank;
}

TextBox^ ServerPage::addTextRcon()
{
	TextBox^ textBoxRcon = gcnew TextBox();
	textBoxRcon->Location = System::Drawing::Point(6, 396);
	textBoxRcon->Name = L"textBoxRcon";
	textBoxRcon->Size = System::Drawing::Size(645, 20);
	textBoxRcon->TabIndex = 59;
	textBoxRcon->Text = L"Send Command";

	return textBoxRcon;
}

Button^ ServerPage::addBan()
{
	Button^ buttonBan = gcnew Button();
	buttonBan->Location = System::Drawing::Point(17, 266);
	buttonBan->Name = L"buttonBan";
	buttonBan->Size = System::Drawing::Size(163, 44);
	buttonBan->TabIndex = 62;
	buttonBan->Text = L"Ban Player";
	buttonBan->UseVisualStyleBackColor = true;
	buttonBan->Click += gcnew System::EventHandler(this, &ServerPage::buttonBan_Click);

	return buttonBan;
}

Button^ ServerPage::addKick()
{
	Button^ buttonKick = gcnew Button();
	buttonKick->Location = System::Drawing::Point(17, 216);
	buttonKick->Name = L"buttonKick";
	buttonKick->Size = System::Drawing::Size(163, 44);
	buttonKick->TabIndex = 61;
	buttonKick->Text = L"Kick Player";
	buttonKick->UseVisualStyleBackColor = true;
	buttonKick->Click += gcnew System::EventHandler(this, &ServerPage::buttonKick_Click);

	return buttonKick;
}

Button^ ServerPage::addFail()
{
	Button^ buttonFail = gcnew Button();
	buttonFail->Location = System::Drawing::Point(537, 266);
	buttonFail->Name = L"buttonFail";
	buttonFail->Size = System::Drawing::Size(163, 44);
	buttonFail->TabIndex = 64;
	buttonFail->Text = L"Vote Fail";
	buttonFail->UseVisualStyleBackColor = true;
	buttonFail->Click += gcnew System::EventHandler(this, &ServerPage::buttonFail_Click);

	return buttonFail;
}

Button^ ServerPage::addPass()
{
	Button^ buttonPass = gcnew Button();
	buttonPass->Location = System::Drawing::Point(301, 266);
	buttonPass->Name = L"buttonPass";
	buttonPass->Size = System::Drawing::Size(163, 44);
	buttonPass->TabIndex = 63;
	buttonPass->Text = L"Vote Pass";
	buttonPass->UseVisualStyleBackColor = true;
	buttonPass->Click += gcnew System::EventHandler(this, &ServerPage::buttonPass_Click);

	return buttonPass;
}

Button^ ServerPage::addButtonRcon()
{
	Button^ buttonRcon = gcnew Button();
	buttonRcon->Location = System::Drawing::Point(667, 389);
	buttonRcon->Name = L"buttonRcon";
	buttonRcon->Size = System::Drawing::Size(90, 32);
	buttonRcon->TabIndex = 60;
	buttonRcon->Text = L"Send Rcon";
	buttonRcon->UseVisualStyleBackColor = true;
	buttonRcon->Click += gcnew System::EventHandler(this, &ServerPage::buttonRcon_Click);

	return buttonRcon;
}
Button^ ServerPage::addHost()
{
	Button^ buttonHost = gcnew Button();
	buttonHost->Location = System::Drawing::Point(323, 18);
	buttonHost->Name = L"buttonHost";
	buttonHost->Size = System::Drawing::Size(141, 36);
	buttonHost->TabIndex = 24;
	buttonHost->Text = L"Create Host";
	buttonHost->UseVisualStyleBackColor = true;
	buttonHost->Click += gcnew System::EventHandler(this, &ServerPage::startHost);

	return buttonHost;
}

PictureBox^ ServerPage::addPicture(System::ComponentModel::ComponentResourceManager^  resources)
{
	PictureBox^ pictureBox3 = gcnew PictureBox();
	pictureBox3->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"Yellow")));
	pictureBox3->InitialImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"Yellow")));
	pictureBox3->Location = System::Drawing::Point(636, 6);
	pictureBox3->Name = L"pictureBox3";
	pictureBox3->Size = System::Drawing::Size(103, 102);
	pictureBox3->TabIndex = 73;
	pictureBox3->TabStop = false;

	return pictureBox3;
}

#pragma endregion
bool ServerPage::sendData(String^ data)
{
	if (netLocal)
	{
		return netDedicated->sendData(data);
	}
	else
	{
		try
		{
			int nByte = data->Length;
			netStream->Write(Rcon::convertStrToByte(data), 0, nByte + 1);
		}
		catch (Exception^ io)
		{
			return false;
		}
		return true;
	}
}
System::Void ServerPage::sendServer(String^ toServer)
{
	DialogResult^ messageReturn;

	do
	{
		if (sendData(toServer))
		{
			resolvingConnection();
			messageReturn = MessageBox::Show(netDedicated->getStatus(), "Error from " + netDedicated->getIPServer() + ":" + netDedicated->getPortServer(),
				MessageBoxButtons::AbortRetryIgnore, MessageBoxIcon::Error);
			netDedicated->addLog(netDedicated->getStatus());
		}
		else
		{
			messageReturn = DialogResult::OK;
		}
	} 
	while (messageReturn->Equals(DialogResult::Retry));

	if (messageReturn->Equals(DialogResult::Abort))
	{
		Application::Exit();
	}
	else if (messageReturn->Equals(DialogResult::Ignore))
	{
		errorConnection();
	}

}

System::Void ServerPage::buttonShutdown_Click(System::Object^  sender, System::EventArgs^  e)
{
	if (!netDedicated->getOnline())
	{
		this->connectServer();
		goodConnection();
	}
	else
	{
		netDedicated->~Rcon();
		errorConnection();
	}
}
System::Void ServerPage::buttonRanked_Click(System::Object^  sender, System::EventArgs^  e)
{
	btnRanked->Enabled = false;
	comboRank->Enabled = true;
	StartRank = true;
	sendServer("chatSay(\"[NRS] MyRanked by Nobel3D is started!\")");
	dbSam = gcnew Database("localhost", "27000", "serioussamhdplayer", "root", "121314", true);
	Players::dbUsed = dbSam;
	sendServer("gamRestartServer()");
}

System::Void ServerPage::buttonDelete_Click(System::Object^  sender, System::EventArgs^  e)
{
	this->~ServerPage();
}

System::Void ServerPage::buttonChat_Click(System::Object^  sender, System::EventArgs^  e)
{
	sendServer("chatSay(\"Admin: " + txtChat->Text + "\")");
	netDedicated->addLog("[ASP] Chat Send: " + txtChat->Text);
	txtChat->Clear();
	btnChat->Enabled = false;
}
System::Void ServerPage::buttonRcon_Click(System::Object^  sender, System::EventArgs^  e)
{
	sendServer(txtRcon->Text);
	txtRcon->Clear();
}
System::Void ServerPage::buttonFail_Click(System::Object^  sender, System::EventArgs^  e)
{
	sendServer("samVoteFail()");
}
System::Void ServerPage::buttonPass_Click(System::Object^  sender, System::EventArgs^  e)
{
	sendServer("samVotePass()"); 
}
System::Void ServerPage::buttonKick_Click(System::Object^  sender, System::EventArgs^  e)
{
	if (comboPlayer->Text == "")
	{
		MessageBox::Show("Please insert a name player", "ERROR 03", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
	}
	else
	{
		sendServer("gamKickByName(\"" + Rcon::markupEncode(comboPlayer->Text) + "\")");
		comboPlayer->Items->Remove(comboPlayer->Text);
	}
}
System::Void ServerPage::buttonNobelBan_Click(System::Object^  sender, System::EventArgs^  e)
{

}
System::Void ServerPage::buttonBan_Click(System::Object^  sender, System::EventArgs^  e)
{
	if (comboPlayer->Text == "")
	{
		MessageBox::Show("Please insert a name player", "ERROR 03", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
	}
	else
	{
		sendServer("gamBanByName(\"" + Rcon::markupEncode(comboPlayer->Text) + "\")");
		comboPlayer->Items->Remove(comboPlayer->Text);
	}
}
System::Void ServerPage::buttonPause_Click(System::Object^  sender, System::EventArgs^  e)
{
	sendServer("samPauseGame()");
}
System::Void ServerPage::comboBoxPlayerRank_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e)
{
	MessageBox::Show("Kills: " + listPlayer[comboRank->SelectedIndex]->getKill() +
		" Dead: " + listPlayer[comboRank->SelectedIndex]->getDead() +
		" Score: " + listPlayer[comboRank->SelectedIndex]->getPoint(),
		"Score", MessageBoxButtons::OK, MessageBoxIcon::Information);
}

System::Void ServerPage::errorConnection()
{
	immPicture->Image = cli::safe_cast<System::Drawing::Image^>(resourcePtr->GetObject(L"Red"));
	btnShutdown->Text = "Start Connection";
}
System::Void ServerPage::resolvingConnection()
{
	immPicture->Image = cli::safe_cast<System::Drawing::Image^>(resourcePtr->GetObject(L"Yellow"));
}
System::Void ServerPage::goodConnection()
{
	immPicture->Image = cli::safe_cast<System::Drawing::Image^>(resourcePtr->GetObject(L"Green"));
	btnShutdown->Text = "Shutdown Server";
}

System::Void ServerPage::listenDedicated()
{
	while (netDedicated->getOnline())
	{
		try
		{
			String^ str_Analyze = netDedicated->getLine();
			if (str_Analyze != "")
			{
				arrayStream = str_Analyze->Split(gcnew array < String^ > { ": ", ", "}, StringSplitOptions::None);

				if (arrayStream[0]->StartsWith("Server accepted connection from IP"))
				{
					arrayStream[3] = arrayStream[3]->Replace(".", "");
					playerJoined = Convert::ToInt32(arrayStream[3]);
					listPlayer->Add(gcnew Players(arrayStream[1], playerJoined));
					netDedicated->addLog("Server accepted connection from " + arrayStream[1]);
				}
				if (arrayStream[0]->StartsWith("<playerjoined player="))
				{
					arrayStream = arrayStream[0]->Split(gcnew array < String^ > { "\"" }, StringSplitOptions::None);
					LoadPlayer(arrayStream);
				}

				if (arrayStream[0]->StartsWith("<playerleft player=") ||
					arrayStream[0]->StartsWith("Server received a disconnect message from ") ||
					arrayStream[0]->StartsWith("Server sent a disconnect message to ") ||
					arrayStream[0]->StartsWith("Server terminating client "))
				{
					int Lefter = -1;
					if (arrayStream[0]->StartsWith("Server received a disconnect message from ") ||
						arrayStream[0]->StartsWith("Server sent a disconnect message to ") ||
						arrayStream[0]->StartsWith("Server terminating client "))
					{
						arrayStream = arrayStream[0]->Split(gcnew array < String^ > {"from ", "to ", "client ", "."}, StringSplitOptions::None);
						Lefter = Convert::ToInt32(arrayStream[1]);
						netDedicated->addLog("[RAS] Player: " + listPlayer[Lefter]->getName() + "; ID: " + listPlayer[Lefter]->getID() + "; Server disconnect");
					}
					else
					{
						arrayStream = arrayStream[0]->Split(gcnew array < String^ > { "\"" }, StringSplitOptions::None);
						Lefter = Players::FindIndex(listPlayer, arrayStream[3]);
					}
					if (Lefter <= -1)
					{
						try
						{
							netDedicated->addLog("[RAS] Player: " + arrayStream[1] + "; ID: " + arrayStream[3] + "; Unload");
						}
						catch (Exception^ ex)
						{
							netDedicated->addLog("[RAS] Player Unload + Exception into Stream: " + arrayStream->ToString());
						}
					}
					else
					{
						netDedicated->addLog("[RAS] Player: " + listPlayer[Lefter]->getName() + "; ID: " + listPlayer[Lefter]->getID() + "; Correct Left");
						delPlayer(listPlayer[Lefter]->getName());
						delRank(listPlayer[Lefter]->getName());
						listPlayer->Remove(listPlayer[Lefter]);
					}

				}
				if (arrayStream[0]->StartsWith("<chat player="))
				{
					arrayStream = arrayStream[0]->Split(gcnew array < String^ > {"\"", "<", ">"}, StringSplitOptions::None);
					//<chat player = "Nobel3D~" playerid = "110000105c1224c">che appena mi muovo< / chat>
				}
				if (arrayStream[0]->StartsWith("<roundstart gamemode="))
				{

						arrayStream = arrayStream[0]->Split(gcnew array < String^ > { "\"" }, StringSplitOptions::None);

						int IndexWinner = Players::WinnerIndex(listPlayer);
						if (IndexWinner != -1)
							listPlayer[IndexWinner]->Iwin();

						Players::Weloser(listPlayer);
						Players::SaveAll(listPlayer);

						arrayMatch[0] = arrayStream[1];
						arrayMatch[1] = arrayStream[3];
						arrayMatch[2] = arrayStream[5];
						arrayMatch[3] = arrayStream[7];
						arrayMatch[4] = arrayStream[9];
						arrayMatch[5] = arrayStream[11];
						arrayMatch[6] = arrayStream[13]; //variable index

						Players::cleanAll(listPlayer);
						netDedicated->addLog("[RAS] Match started");
						netDedicated->addLog("");
				}
				if (StartRank)
				{
					if (arrayStream[0]->StartsWith("<playerkilled player="))
					{
						arrayStream = arrayStream[0]->Split(gcnew array < String^ > { "\"" }, StringSplitOptions::None);

						int playerKiller, playerKilled;

						playerKilled = Players::FindIndex(listPlayer, arrayStream[3]);
						playerKiller = Players::FindIndex(listPlayer, arrayStream[13]);

						if (playerKilled == -1 || playerKiller == -1)
						{
							try
							{
								netDedicated->addLog("[NRS] player not found! Killed= " + arrayStream[3] + " ; Killer= " + arrayStream[13] + " ;");
							}
							catch (Exception^ ex)
							{
								netDedicated->addLog("[NRS] Player Killer error + Exception into Stream: " + arrayStream->ToString());
							}
						}
						else
						{
							if (playerKiller == playerKilled)
							{
								listPlayer[playerKilled]->Ikillme();
							}
							else
							{
								listPlayer[playerKiller]->Ikill(arrayStream[9]);
								listPlayer[playerKilled]->Idead();
							}
						}
					}
				}
			}
		}
		catch (Exception^ opo){ netDedicated->addLog(opo->ToString()); }
	}
}

System::Void ServerPage::LoadPlayer(array<String^>^ ArrayStream)
{
	try
	{

		String^ ID = ArrayStream[3]->Trim();
		String^ Nick = Rcon::markupDecode(ArrayStream[1]);

		if (!Players::AlreadyStarted(listPlayer, ID))
		{
			if (!Players::IsBanned(ID))
			{
				playerJoined = Players::FindIndex(listPlayer, ID);
				if (playerJoined <= -1)
				{
					if (StartRank)
					{
						sendServer("gamKickByIP(\"" + ID + "\")");
						netDedicated->SamChat("Log: Player Unloaded -> " + Nick);
						netDedicated->addLog("[RAS] Player: " + Nick + "; ID: " + ID + "; Unload Kicked! ");
					}
					else
					{
						netDedicated->addLog("[RAS] Player: " + Nick + "; ID: " + ID + "; Unload Warning! ");
					}
				}
				else
				{
					if (StartRank)
						listPlayer[playerJoined] = Players::Load(ID, Nick, playerJoined);
					else
						listPlayer[playerJoined] = gcnew Players(ID, Nick, playerJoined);

					threadPlayer(Nick);
					threadRank(Nick);
					netDedicated->addLog("[RAS] Player: " + Nick + "; ID: " + ID + "; Index:" + playerJoined + "; Loaded");
				}
			}
			else
			{
				sendServer("gamKickByIP(\"" + ID + "\")");
				netDedicated->addLog("[NSB] Player: " + Nick + "; ID: " + ID + "; Banned");
				netDedicated->SamChat("Ban Machine: " + Nick + " Bye Bye");
			}
		}
	}
	catch (Exception^ error)
	{
		Windows::Forms::MessageBox::Show(error->ToString());
	}
}

System::Void ServerPage::connectServer()
{
	if (netLocal)
	{
		if (netDedicated->connectRcon())
		{
			goodConnection();

			deStartThread = gcnew ThreadStart(this, &ServerPage::listenDedicated);
			deThread = gcnew Thread(deStartThread);
			deThread->Start();
			Thread::Sleep(1000);
			MessageBox::Show("Connection is started.", "Initialize", MessageBoxButtons::OK, MessageBoxIcon::Information);
			netDedicated->sendData("chatSay(\"Log: Some Admin has started a GUI MyAdmin by Nobel3D\")");
		}
		else
		{
			errorConnection();
			MessageBox::Show("Generic: Error connecting from Rcon.", "ERROR 02", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}
	}
	else
	{
		netClient = gcnew TcpClient(); //creo con la gcnew un oggetto TcpClient
		netClient->ReceiveTimeout = 15000; //setto il timeout di connessione
		netClient->Connect(netDedicated->getIPServer(), netDedicated->getPortServer()); //apro la connessione che ha come parametri l' IP e la parta del server
		                                                                                //mettere assolutamente una porta per la connessione col server.
		netStream = netClient->GetStream(); //ottengo lo stream dati ONLINE
		

		if (netStream->CanWrite == true && netStream->CanRead == true)
		{
			goodConnection();
		}
		else
		{
			errorConnection();
			MessageBox::Show("Error connecting server", "ERROR 10", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}
	}
}
System::Void ServerPage::startHost(System::Object^  sender, System::EventArgs^  e)
{
	if (!hostActive)
	{
		netHost = gcnew Host(13000);
		netHost->Start();
		hostStartThread = gcnew ThreadStart(this, &ServerPage::processHost);
		hostThread = gcnew Thread(hostStartThread);
		hostThread->Start();
		hostActive = true;
	}
	else
	{
		if (MessageBox::Show("MyAdmin has already started host, do you want close?", "Host", MessageBoxButtons::YesNo, MessageBoxIcon::Question)
			== Windows::Forms::DialogResult::Yes)
		{
			netHost->~Host();
			hostActive = false;
		}
	}
}

System::Void ServerPage::processHost()
{
	while (true)
	{
		String^ getData;
		if (getData == "KILL")
		{
			array<Process^>^ Processes = Process::GetProcessesByName("SamHD_TSE_DedicatedServer");
			for each (Process^ P in Processes)
				P->Kill();
			//it doesn't kill only dedicated of connection, but all process SamHD_TSE_DedicatedServer
		}
		else if (getData->Contains("SamHD_TSE_DedicatedServer.exe"))
		{
			System::Diagnostics::Process::Start(MyAdmin::MyDedicated::getDedicatedPath()+"\\"+getData);
		}
		else
		{
			netDedicated->sendData(getData);
		}
	}
}

/*Threading isn't secure if I don't use this method*/
#pragma region Threading secure
delegate void SetTextCallback(String^ text);

System::Void ServerPage::threadPlayer(String^ AddMe)
{
if (comboPlayer->InvokeRequired)
{

SetTextCallback^ d = gcnew SetTextCallback(this, &ServerPage::threadPlayer);
comboPlayer->Invoke(d, gcnew array<Object^> { AddMe });
}
else
{
comboPlayer->Items->Add(AddMe);
}
}

System::Void ServerPage::threadRank(String^ AddMe)
{
if (comboRank->InvokeRequired)
{

SetTextCallback^ d = gcnew SetTextCallback(this, &ServerPage::threadRank);
comboRank->Invoke(d, gcnew array<Object^> { AddMe });
}
else
{
comboRank->Items->Add(AddMe);
}
}

System::Void ServerPage::delPlayer(String^ AddMe)
{
if (comboPlayer->InvokeRequired)
{
SetTextCallback^ d = gcnew SetTextCallback(this, &ServerPage::delPlayer);
comboPlayer->Invoke(d, gcnew array<Object^> { AddMe });
}
else
{
comboPlayer->Items->Remove(AddMe);
}
}

System::Void ServerPage::delRank(String^ AddMe)
{
if (comboRank->InvokeRequired)
{
SetTextCallback^ d = gcnew SetTextCallback(this, &ServerPage::delRank);
comboRank->Invoke(d, gcnew array<Object^> { AddMe });
}
else
{
comboRank->Items->Remove(AddMe);
}
}
#pragma endregion
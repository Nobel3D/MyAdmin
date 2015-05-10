#pragma once

#include "..\stdafx.h"
#include "..\Class\Rcon.h"
#include "..\Class\Players.h"
#include "MyDedicated.h"
#include "SupportForm.h"
#include "Credits.h"
#include "YouKnow.h"
#include "../Class/ServerPage.h"
#include "..\Class\Database.h"
#include "..\Class\Host.h"

#define MAXMESSAGEKNOW 10

namespace MyAdmin {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Threading;

	public ref class MainForm : public System::Windows::Forms::Form
	{
	public:
		/*Constructor of the main form*/
		MainForm(void)
		{
			InitializeComponent();
			this->Text = "Serious Sam MyAdmin " + Version;
			textBoxStatus->Text = "Ready";
			Rcon::addLog2("[SYS] System Loading");

			array_Player = gcnew List<Players^>;
			array_match = gcnew array<String^>(7);
			Connection = gcnew List < Rcon^ > ;

			if (IO::File::Exists("MyAdmin.conf"))
			{
				ConfigFile("MyAdmin.conf");
			}
			else
			{
				Credits^ ShowCredits = gcnew Credits();
				ShowCredits->ShowDialog();
			}
			Rcon::addLog2("[SYS] Loaded and Ready");
			settingUpMessage();
			DidYouKnow();
		}

	protected:
		/*Destructor of the main form*/
		~MainForm()
		{
			if (components)
			{
					MessageBox::Show("This application will be closed and will disconnects from server",
						"WARNING", MessageBoxButtons::OK, MessageBoxIcon::Warning);
					stm_WriteConfig = gcnew IO::StreamWriter("MyAdmin.conf", false);
					Rcon::addLog2("[SYS] Saving Configurarion");
					stm_WriteConfig->WriteLine("LastIP=" + bufferIP);
					stm_WriteConfig->WriteLine("LastPort=" + bufferPort);
					stm_WriteConfig->WriteLine("Signature=" + str_Message);
					stm_WriteConfig->WriteLine("TimedString=" + str_Timer);
					stm_WriteConfig->WriteLine("TimedTime=" + int_Timer);
					stm_WriteConfig->WriteLine("ServerDedicatedPath=" + MyDedicatedPath);
					stm_WriteConfig->WriteLine("KillMessage=" + str_KillMessage);
					stm_WriteConfig->WriteLine("SuicideMessage=" + str_SuicideMessage);
					stm_WriteConfig->Close();

					textBoxStatus->Text = "Configuration Saved!";
					Rcon::addLog2("[SYS] Closing Application!");
					delete components;
			}
		}
	private: System::Void settingUpMessage()
	{
				 form_Message[0] = "You can get source code of MyAdmin on GitHub : https://github.com/Nobel3D/MyAdmin Feel free to change the source code, and report any bug.";
				 form_Message[1] = "You can change the signature on chat and set any timed message, Set your MyAdmin how you liking!";
				 form_Message[2] = "You can use all command of Serious Sam on the textbox \"Send Rcon\". For example you can use \"samShowBanList()\" for see sam's ban list.";
				 form_Message[3] = "You can use MyRanked, only if you have setted a database, and you must contact Nobel3D for this stuff: http://steamcommunity.com/groups/Nobel3DOfficial/discussions/1/";
				 form_Message[4] = "You can ban some player with temporary ban, you can ban a player for 30 min to one month.";
				 form_Message[5] = "You can create a local server, but keep in your mind that the local ip is: 127.0.0.1 (LocalHost)";
				 form_Message[6] = "Maybe I will make a version for Serious Sam 3 and Serious Sam Revolution, you stay connected!";
				 form_Message[7] = "You can see the score on real time, if you have MyRanked on your server";
				 form_Message[8] = "The òpò is your friend, but if you aren't italian, you can't understand!";
				 form_Message[9] = "For me, and my experience as admin for some server, the spectators on the match are untouchables!";
	}
	private: System::Void DidYouKnow()
	{
				 int iCount = 0;
				 do
				 {
					 form_YouKnow = gcnew YouKnow(form_Message[iCount]);
					 form_YouKnow->ShowDialog();
					 iCount++;
				 } 
				 while (form_YouKnow->getNext()&&iCount!=MAXMESSAGEKNOW);
	}
	
			 /*It reads the config file, and set all values (I don't like this method, in future it will be as MyDedicated config)*/
	private: System::Void ConfigFile(String^ Path)
	{
				 stm_ReadConfig = gcnew IO::StreamReader(Path);
				 Rcon::addLog2("[SYS] Loading Configuration");
				 array_Word = gcnew array<array<String^>^>(10);
				 for (int c = 0; c < 10; c++)
					 array_Word[c] = gcnew array<String^>(2);

				 int i = 0;
				 while (!(stm_ReadConfig->EndOfStream))
				 {
					 str_Analyze = stm_ReadConfig->ReadLine();
					 array_Word[i] = str_Analyze->Split(array_Split, StringSplitOptions::None);
					 i++;
				 }
				 stm_ReadConfig->Close();
				 for (int c = 0; c < 8; c++)
				 {
					 if (array_Word[c][0] == "LastIP")
					 {
						 comboBoxIP->Items->Add(array_Word[c][1]);
						 bufferIP = array_Word[c][1];
					 }
					 if (array_Word[c][0] == "LastPort")
					 {
						 if (array_Word[c][1] != "27015")
							 comboBoxPort->Items->Add(array_Word[c][1]);
						 bufferPort = array_Word[c][1];
					 }
					 if (array_Word[c][0] == "Signature")
						 str_Message = array_Word[c][1];
					 if (array_Word[c][0] == "TimedString")
						 str_Timer = array_Word[c][1];
					 if (array_Word[c][0] == "TimedTime")
						 int_Timer = Convert::ToInt32(array_Word[c][1]);
					 if (array_Word[c][0] == "ServerDedicatedPath")
						 MyDedicatedPath = array_Word[c][1];
					 if (array_Word[c][0] == "KillMessage")
						 str_KillMessage = array_Word[c][1];
					 if (array_Word[c][0] == "SuicideMessage")
						 str_SuicideMessage = array_Word[c][1];
				 }
				 if (str_SuicideMessage == "NULL")
				 {
					 EnabledMessage = false;
				 }
	}

#pragma endregion
			 //MyClass
	private: ServerPage^ listConnect;
	private: List<Rcon^>^ Connection;
	private: Database^ dbSam;
	private: List<Players^>^ array_Player;
	private: Host^ netHost;
			 //Main String
	private: static String^ str_KillMessage = "'opo'";
	private: static String^ str_SuicideMessage = "xddd";
	private: static String^ str_Message = "Admin";
	private: static String^ Version = "2.0 BETA 1";
	private: static String^ MyDedicatedPath = "";
	private: array<array<String^>^>^ FirstString;
			 //Config file MyAdmin.conf
	public: IO::StreamWriter^ stm_WriteConfig;
	public: IO::StreamReader^ stm_ReadConfig;
	public: String^ str_Analyze;
	public: array<array<String^>^>^ array_Word;
	public: static array<String^>^ array_Split = { "=" };
			//Main Timer
	private: static int Seconds;
	private: static int Minute;
			 //Spam protocol
	private: int ActiveSend;
	private: bool Spam;
			 //Forms
	private: SupportForm^ form_SupportVoid;
	private: SupportForm^ form_SupportInt;
	private: SupportForm^ form_SupportUnban;
	private: MyDedicated^ form_MyDedicated;
	private: YouKnow^ form_YouKnow;
	private: static array<String^>^ form_Message = gcnew array<String^>(MAXMESSAGEKNOW);
			 //Conditional Timer
	private: String^ str_Timer;
	private: int int_Timer;
	private: int secTime;
	private: int minTime;
	private: int CstdTime;
	private: static int Multy = 1;
			 //RAS (Runtime Administration Socket)
	private: bool StartRank;
	private: static String^ str_Help = "";
	private: static array<String^>^ Spliter = { ": ", ", " };
	private: static array<String^>^ localSplit = { "\"" };
	private: array<String^>^ array_Stream;
	private: array<String^>^ array_match;
	private: static String^ Buffer = "";
	private: int playerJoined;
	private: bool EnabledMessage;
			 //Other
	private: int netCount;
	private: int netCurrent;
	private: String^ bufferIP;
	private: String^ bufferPort;

#pragma region Form Pointer

	private: System::Windows::Forms::MenuStrip^  menuStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^  playerToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  unBanToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  cheatsToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  cheatEnable0ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  cheat1ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  cheat2ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  cheat3ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  mapsToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  nextMapToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  restartMapToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  changeMapToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  deathMatchToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  brkeenChevapToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  fortressToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  holeToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  jumpOverToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  medievalRageToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  royalPurgatoryToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  sunPalaceToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  theLostTombToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  weGotSkullToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  yodellerToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  chatToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  timedMessageToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  signatureChatToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  currentMatchToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  detailsToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  recentChatToolStripMenuItem;
	private: System::Windows::Forms::Timer^  timerRAS;
	private: System::Windows::Forms::ToolStripMenuItem^  killMessageToolStripMenuItem;
	private: System::Windows::Forms::TextBox^  textBoxStatus;
	private: System::Windows::Forms::LinkLabel^  linkLabel1;
	private: System::Windows::Forms::Button^  buttonUpdate;
	private: System::Windows::Forms::Button^  buttonExit;
	private: System::Windows::Forms::Button^  buttonCredits;
	private: System::Windows::Forms::ToolStripMenuItem^  helpToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  didYouKnowToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  creditsToolStripMenuItem;
	private: System::Windows::Forms::PictureBox^  pictureBox1;
private: List<System::Windows::Forms::TabPage^>  tabList;
private: System::Windows::Forms::PictureBox^  pictureBox2;
private: System::Windows::Forms::TabPage^  tabPage2;
private: System::Windows::Forms::TextBox^  textBoxName;
private: System::Windows::Forms::Label^  label4;
private: System::Windows::Forms::Button^  buttonConfig;
private: System::Windows::Forms::Button^  buttonHost;
private: System::Windows::Forms::Button^  buttonLocal;
private: System::Windows::Forms::Label^  label2;
private: System::Windows::Forms::ComboBox^  comboBoxPort;
private: System::Windows::Forms::Button^  buttonAdd;
private: System::Windows::Forms::ComboBox^  comboBoxIP;
private: System::Windows::Forms::Label^  label1;
private: System::Windows::Forms::Label^  labelIP;
private: System::Windows::Forms::TextBox^  textPassword;
private: System::Windows::Forms::TabControl^  serverList;
	private: System::ComponentModel::IContainer^  components;
#pragma endregion

#pragma region Windows Form Designer generated code
			 void InitializeComponent(void)
			 {
				 this->components = (gcnew System::ComponentModel::Container());
				 System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(MainForm::typeid));
				 this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
				 this->playerToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->unBanToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->cheatsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->cheatEnable0ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->cheat1ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->cheat2ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->cheat3ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->mapsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->nextMapToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->restartMapToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->changeMapToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->deathMatchToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->brkeenChevapToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->fortressToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->holeToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->jumpOverToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->medievalRageToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->royalPurgatoryToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->sunPalaceToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->theLostTombToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->weGotSkullToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->yodellerToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->chatToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->timedMessageToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->signatureChatToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->killMessageToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->currentMatchToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->detailsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->recentChatToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->helpToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->didYouKnowToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->creditsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->timerRAS = (gcnew System::Windows::Forms::Timer(this->components));
				 this->textBoxStatus = (gcnew System::Windows::Forms::TextBox());
				 this->linkLabel1 = (gcnew System::Windows::Forms::LinkLabel());
				 this->buttonUpdate = (gcnew System::Windows::Forms::Button());
				 this->buttonExit = (gcnew System::Windows::Forms::Button());
				 this->buttonCredits = (gcnew System::Windows::Forms::Button());
				 this->pictureBox2 = (gcnew System::Windows::Forms::PictureBox());
				 this->tabPage2 = (gcnew System::Windows::Forms::TabPage());
				 this->textBoxName = (gcnew System::Windows::Forms::TextBox());
				 this->label4 = (gcnew System::Windows::Forms::Label());
				 this->buttonConfig = (gcnew System::Windows::Forms::Button());
				 this->buttonHost = (gcnew System::Windows::Forms::Button());
				 this->buttonLocal = (gcnew System::Windows::Forms::Button());
				 this->label2 = (gcnew System::Windows::Forms::Label());
				 this->comboBoxPort = (gcnew System::Windows::Forms::ComboBox());
				 this->buttonAdd = (gcnew System::Windows::Forms::Button());
				 this->comboBoxIP = (gcnew System::Windows::Forms::ComboBox());
				 this->label1 = (gcnew System::Windows::Forms::Label());
				 this->labelIP = (gcnew System::Windows::Forms::Label());
				 this->textPassword = (gcnew System::Windows::Forms::TextBox());
				 this->serverList = (gcnew System::Windows::Forms::TabControl());
				 this->menuStrip1->SuspendLayout();
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->BeginInit();
				 this->tabPage2->SuspendLayout();
				 this->serverList->SuspendLayout();
				 this->SuspendLayout();
				 // 
				 // menuStrip1
				 // 
				 this->menuStrip1->Enabled = false;
				 this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(6) {
					 this->playerToolStripMenuItem,
						 this->cheatsToolStripMenuItem, this->mapsToolStripMenuItem, this->chatToolStripMenuItem, this->currentMatchToolStripMenuItem,
						 this->helpToolStripMenuItem
				 });
				 this->menuStrip1->Location = System::Drawing::Point(3, 3);
				 this->menuStrip1->Name = L"menuStrip1";
				 this->menuStrip1->Size = System::Drawing::Size(785, 24);
				 this->menuStrip1->TabIndex = 26;
				 this->menuStrip1->Text = L"menuStrip1";
				 // 
				 // playerToolStripMenuItem
				 // 
				 this->playerToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->unBanToolStripMenuItem });
				 this->playerToolStripMenuItem->Name = L"playerToolStripMenuItem";
				 this->playerToolStripMenuItem->Size = System::Drawing::Size(51, 20);
				 this->playerToolStripMenuItem->Text = L"Player";
				 // 
				 // unBanToolStripMenuItem
				 // 
				 this->unBanToolStripMenuItem->Name = L"unBanToolStripMenuItem";
				 this->unBanToolStripMenuItem->Size = System::Drawing::Size(152, 22);
				 this->unBanToolStripMenuItem->Text = L"UnBan";
				 this->unBanToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::unBanToolStripMenuItem_Click);
				 // 
				 // cheatsToolStripMenuItem
				 // 
				 this->cheatsToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {
					 this->cheatEnable0ToolStripMenuItem,
						 this->cheat1ToolStripMenuItem, this->cheat2ToolStripMenuItem, this->cheat3ToolStripMenuItem
				 });
				 this->cheatsToolStripMenuItem->Name = L"cheatsToolStripMenuItem";
				 this->cheatsToolStripMenuItem->Size = System::Drawing::Size(55, 20);
				 this->cheatsToolStripMenuItem->Text = L"Cheats";
				 // 
				 // cheatEnable0ToolStripMenuItem
				 // 
				 this->cheatEnable0ToolStripMenuItem->Name = L"cheatEnable0ToolStripMenuItem";
				 this->cheatEnable0ToolStripMenuItem->Size = System::Drawing::Size(119, 22);
				 this->cheatEnable0ToolStripMenuItem->Text = L"Cheat=0";
				 this->cheatEnable0ToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::cheatEnable0ToolStripMenuItem_Click);
				 // 
				 // cheat1ToolStripMenuItem
				 // 
				 this->cheat1ToolStripMenuItem->Name = L"cheat1ToolStripMenuItem";
				 this->cheat1ToolStripMenuItem->Size = System::Drawing::Size(119, 22);
				 this->cheat1ToolStripMenuItem->Text = L"Cheat=1";
				 this->cheat1ToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::cheat1ToolStripMenuItem_Click);
				 // 
				 // cheat2ToolStripMenuItem
				 // 
				 this->cheat2ToolStripMenuItem->Name = L"cheat2ToolStripMenuItem";
				 this->cheat2ToolStripMenuItem->Size = System::Drawing::Size(119, 22);
				 this->cheat2ToolStripMenuItem->Text = L"Cheat=2";
				 this->cheat2ToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::cheat2ToolStripMenuItem_Click);
				 // 
				 // cheat3ToolStripMenuItem
				 // 
				 this->cheat3ToolStripMenuItem->Name = L"cheat3ToolStripMenuItem";
				 this->cheat3ToolStripMenuItem->Size = System::Drawing::Size(119, 22);
				 this->cheat3ToolStripMenuItem->Text = L"Cheat=3";
				 this->cheat3ToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::cheat3ToolStripMenuItem_Click);
				 // 
				 // mapsToolStripMenuItem
				 // 
				 this->mapsToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
					 this->nextMapToolStripMenuItem,
						 this->restartMapToolStripMenuItem, this->changeMapToolStripMenuItem
				 });
				 this->mapsToolStripMenuItem->Name = L"mapsToolStripMenuItem";
				 this->mapsToolStripMenuItem->Size = System::Drawing::Size(48, 20);
				 this->mapsToolStripMenuItem->Text = L"Maps";
				 // 
				 // nextMapToolStripMenuItem
				 // 
				 this->nextMapToolStripMenuItem->Name = L"nextMapToolStripMenuItem";
				 this->nextMapToolStripMenuItem->Size = System::Drawing::Size(142, 22);
				 this->nextMapToolStripMenuItem->Text = L"Next Map";
				 this->nextMapToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::nextMapToolStripMenuItem_Click);
				 // 
				 // restartMapToolStripMenuItem
				 // 
				 this->restartMapToolStripMenuItem->Name = L"restartMapToolStripMenuItem";
				 this->restartMapToolStripMenuItem->Size = System::Drawing::Size(142, 22);
				 this->restartMapToolStripMenuItem->Text = L"Restart Map";
				 this->restartMapToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::restartMapToolStripMenuItem_Click);
				 // 
				 // changeMapToolStripMenuItem
				 // 
				 this->changeMapToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->deathMatchToolStripMenuItem });
				 this->changeMapToolStripMenuItem->Name = L"changeMapToolStripMenuItem";
				 this->changeMapToolStripMenuItem->Size = System::Drawing::Size(142, 22);
				 this->changeMapToolStripMenuItem->Text = L"Change Map";
				 // 
				 // deathMatchToolStripMenuItem
				 // 
				 this->deathMatchToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(10) {
					 this->brkeenChevapToolStripMenuItem,
						 this->fortressToolStripMenuItem, this->holeToolStripMenuItem, this->jumpOverToolStripMenuItem, this->medievalRageToolStripMenuItem,
						 this->royalPurgatoryToolStripMenuItem, this->sunPalaceToolStripMenuItem, this->theLostTombToolStripMenuItem, this->weGotSkullToolStripMenuItem,
						 this->yodellerToolStripMenuItem
				 });
				 this->deathMatchToolStripMenuItem->Name = L"deathMatchToolStripMenuItem";
				 this->deathMatchToolStripMenuItem->Size = System::Drawing::Size(139, 22);
				 this->deathMatchToolStripMenuItem->Text = L"DeathMatch";
				 // 
				 // brkeenChevapToolStripMenuItem
				 // 
				 this->brkeenChevapToolStripMenuItem->Name = L"brkeenChevapToolStripMenuItem";
				 this->brkeenChevapToolStripMenuItem->Size = System::Drawing::Size(188, 22);
				 this->brkeenChevapToolStripMenuItem->Text = L"Brkeen Chevap";
				 this->brkeenChevapToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::brkeenChevapToolStripMenuItem_Click);
				 // 
				 // fortressToolStripMenuItem
				 // 
				 this->fortressToolStripMenuItem->Name = L"fortressToolStripMenuItem";
				 this->fortressToolStripMenuItem->Size = System::Drawing::Size(188, 22);
				 this->fortressToolStripMenuItem->Text = L"Fortress";
				 this->fortressToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::fortressToolStripMenuItem_Click);
				 // 
				 // holeToolStripMenuItem
				 // 
				 this->holeToolStripMenuItem->Name = L"holeToolStripMenuItem";
				 this->holeToolStripMenuItem->Size = System::Drawing::Size(188, 22);
				 this->holeToolStripMenuItem->Text = L"Hole";
				 this->holeToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::holeToolStripMenuItem_Click);
				 // 
				 // jumpOverToolStripMenuItem
				 // 
				 this->jumpOverToolStripMenuItem->Name = L"jumpOverToolStripMenuItem";
				 this->jumpOverToolStripMenuItem->Size = System::Drawing::Size(188, 22);
				 this->jumpOverToolStripMenuItem->Text = L"JumpOver";
				 this->jumpOverToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::jumpOverToolStripMenuItem_Click);
				 // 
				 // medievalRageToolStripMenuItem
				 // 
				 this->medievalRageToolStripMenuItem->Name = L"medievalRageToolStripMenuItem";
				 this->medievalRageToolStripMenuItem->Size = System::Drawing::Size(188, 22);
				 this->medievalRageToolStripMenuItem->Text = L"MedievalRage";
				 this->medievalRageToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::medievalRageToolStripMenuItem_Click);
				 // 
				 // royalPurgatoryToolStripMenuItem
				 // 
				 this->royalPurgatoryToolStripMenuItem->Name = L"royalPurgatoryToolStripMenuItem";
				 this->royalPurgatoryToolStripMenuItem->Size = System::Drawing::Size(188, 22);
				 this->royalPurgatoryToolStripMenuItem->Text = L"RoyalPurgatory";
				 this->royalPurgatoryToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::royalPurgatoryToolStripMenuItem_Click);
				 // 
				 // sunPalaceToolStripMenuItem
				 // 
				 this->sunPalaceToolStripMenuItem->Name = L"sunPalaceToolStripMenuItem";
				 this->sunPalaceToolStripMenuItem->Size = System::Drawing::Size(188, 22);
				 this->sunPalaceToolStripMenuItem->Text = L"SunPalace";
				 this->sunPalaceToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::sunPalaceToolStripMenuItem_Click);
				 // 
				 // theLostTombToolStripMenuItem
				 // 
				 this->theLostTombToolStripMenuItem->Name = L"theLostTombToolStripMenuItem";
				 this->theLostTombToolStripMenuItem->Size = System::Drawing::Size(188, 22);
				 this->theLostTombToolStripMenuItem->Text = L"TheLostTomb";
				 this->theLostTombToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::theLostTombToolStripMenuItem_Click);
				 // 
				 // weGotSkullToolStripMenuItem
				 // 
				 this->weGotSkullToolStripMenuItem->Name = L"weGotSkullToolStripMenuItem";
				 this->weGotSkullToolStripMenuItem->Size = System::Drawing::Size(188, 22);
				 this->weGotSkullToolStripMenuItem->Text = L"WeGotSkull&BonesToo";
				 this->weGotSkullToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::weGotSkullToolStripMenuItem_Click);
				 // 
				 // yodellerToolStripMenuItem
				 // 
				 this->yodellerToolStripMenuItem->Name = L"yodellerToolStripMenuItem";
				 this->yodellerToolStripMenuItem->Size = System::Drawing::Size(188, 22);
				 this->yodellerToolStripMenuItem->Text = L"Yodeller";
				 this->yodellerToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::yodellerToolStripMenuItem_Click);
				 // 
				 // chatToolStripMenuItem
				 // 
				 this->chatToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
					 this->timedMessageToolStripMenuItem,
						 this->signatureChatToolStripMenuItem, this->killMessageToolStripMenuItem
				 });
				 this->chatToolStripMenuItem->Name = L"chatToolStripMenuItem";
				 this->chatToolStripMenuItem->Size = System::Drawing::Size(44, 20);
				 this->chatToolStripMenuItem->Text = L"Chat";
				 // 
				 // timedMessageToolStripMenuItem
				 // 
				 this->timedMessageToolStripMenuItem->Name = L"timedMessageToolStripMenuItem";
				 this->timedMessageToolStripMenuItem->Size = System::Drawing::Size(157, 22);
				 this->timedMessageToolStripMenuItem->Text = L"Timed Message";
				 this->timedMessageToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::timedMessageToolStripMenuItem_Click);
				 // 
				 // signatureChatToolStripMenuItem
				 // 
				 this->signatureChatToolStripMenuItem->Name = L"signatureChatToolStripMenuItem";
				 this->signatureChatToolStripMenuItem->Size = System::Drawing::Size(157, 22);
				 this->signatureChatToolStripMenuItem->Text = L"Signature Chat";
				 this->signatureChatToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::signatureChatToolStripMenuItem_Click);
				 // 
				 // killMessageToolStripMenuItem
				 // 
				 this->killMessageToolStripMenuItem->Name = L"killMessageToolStripMenuItem";
				 this->killMessageToolStripMenuItem->Size = System::Drawing::Size(157, 22);
				 this->killMessageToolStripMenuItem->Text = L"Kill Message";
				 this->killMessageToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::killMessageToolStripMenuItem_Click);
				 // 
				 // currentMatchToolStripMenuItem
				 // 
				 this->currentMatchToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
					 this->detailsToolStripMenuItem,
						 this->recentChatToolStripMenuItem
				 });
				 this->currentMatchToolStripMenuItem->Name = L"currentMatchToolStripMenuItem";
				 this->currentMatchToolStripMenuItem->Size = System::Drawing::Size(96, 20);
				 this->currentMatchToolStripMenuItem->Text = L"Current Match";
				 // 
				 // detailsToolStripMenuItem
				 // 
				 this->detailsToolStripMenuItem->Name = L"detailsToolStripMenuItem";
				 this->detailsToolStripMenuItem->Size = System::Drawing::Size(146, 22);
				 this->detailsToolStripMenuItem->Text = L"Details Match";
				 this->detailsToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::detailsToolStripMenuItem_Click);
				 // 
				 // recentChatToolStripMenuItem
				 // 
				 this->recentChatToolStripMenuItem->Name = L"recentChatToolStripMenuItem";
				 this->recentChatToolStripMenuItem->Size = System::Drawing::Size(146, 22);
				 this->recentChatToolStripMenuItem->Text = L"Recent Chat";
				 this->recentChatToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::recentChatToolStripMenuItem_Click);
				 // 
				 // helpToolStripMenuItem
				 // 
				 this->helpToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
					 this->didYouKnowToolStripMenuItem,
						 this->creditsToolStripMenuItem
				 });
				 this->helpToolStripMenuItem->Name = L"helpToolStripMenuItem";
				 this->helpToolStripMenuItem->Size = System::Drawing::Size(44, 20);
				 this->helpToolStripMenuItem->Text = L"Help";
				 // 
				 // didYouKnowToolStripMenuItem
				 // 
				 this->didYouKnowToolStripMenuItem->Name = L"didYouKnowToolStripMenuItem";
				 this->didYouKnowToolStripMenuItem->Size = System::Drawing::Size(152, 22);
				 this->didYouKnowToolStripMenuItem->Text = L"Did you know\?";
				 this->didYouKnowToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::didYouKnowToolStripMenuItem_Click);
				 // 
				 // creditsToolStripMenuItem
				 // 
				 this->creditsToolStripMenuItem->Name = L"creditsToolStripMenuItem";
				 this->creditsToolStripMenuItem->Size = System::Drawing::Size(152, 22);
				 this->creditsToolStripMenuItem->Text = L"Credits";
				 this->creditsToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::creditsToolStripMenuItem_Click);
				 // 
				 // timerRAS
				 // 
				 this->timerRAS->Interval = 5;
				 // 
				 // textBoxStatus
				 // 
				 this->textBoxStatus->ImeMode = System::Windows::Forms::ImeMode::NoControl;
				 this->textBoxStatus->Location = System::Drawing::Point(13, 580);
				 this->textBoxStatus->Name = L"textBoxStatus";
				 this->textBoxStatus->ReadOnly = true;
				 this->textBoxStatus->Size = System::Drawing::Size(766, 20);
				 this->textBoxStatus->TabIndex = 30;
				 // 
				 // linkLabel1
				 // 
				 this->linkLabel1->AutoSize = true;
				 this->linkLabel1->Location = System::Drawing::Point(259, 641);
				 this->linkLabel1->Name = L"linkLabel1";
				 this->linkLabel1->Size = System::Drawing::Size(274, 13);
				 this->linkLabel1->TabIndex = 31;
				 this->linkLabel1->TabStop = true;
				 this->linkLabel1->Text = L"Serious Sam HD MyAdmin by Luca \"Nobel3D\" Gasperini";
				 this->linkLabel1->LinkClicked += gcnew System::Windows::Forms::LinkLabelLinkClickedEventHandler(this, &MainForm::linkLabel1_LinkClicked);
				 // 
				 // buttonUpdate
				 // 
				 this->buttonUpdate->Location = System::Drawing::Point(687, 636);
				 this->buttonUpdate->Name = L"buttonUpdate";
				 this->buttonUpdate->Size = System::Drawing::Size(92, 23);
				 this->buttonUpdate->TabIndex = 32;
				 this->buttonUpdate->Text = L"Check Update";
				 this->buttonUpdate->UseVisualStyleBackColor = true;
				 this->buttonUpdate->Click += gcnew System::EventHandler(this, &MainForm::buttonUpdate_Click);
				 // 
				 // buttonExit
				 // 
				 this->buttonExit->Enabled = false;
				 this->buttonExit->Location = System::Drawing::Point(13, 636);
				 this->buttonExit->Name = L"buttonExit";
				 this->buttonExit->Size = System::Drawing::Size(92, 23);
				 this->buttonExit->TabIndex = 33;
				 this->buttonExit->Text = L"Disconnect";
				 this->buttonExit->UseVisualStyleBackColor = true;
				 this->buttonExit->Click += gcnew System::EventHandler(this, &MainForm::buttonExit_Click);
				 // 
				 // buttonCredits
				 // 
				 this->buttonCredits->Location = System::Drawing::Point(342, 606);
				 this->buttonCredits->Name = L"buttonCredits";
				 this->buttonCredits->Size = System::Drawing::Size(120, 23);
				 this->buttonCredits->TabIndex = 38;
				 this->buttonCredits->Text = L"Credits";
				 this->buttonCredits->UseVisualStyleBackColor = true;
				 this->buttonCredits->Click += gcnew System::EventHandler(this, &MainForm::buttonCredits_Click);
				 // 
				 // pictureBox2
				 // 
				 this->pictureBox2->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox2.Image")));
				 this->pictureBox2->Location = System::Drawing::Point(13, 491);
				 this->pictureBox2->Name = L"pictureBox2";
				 this->pictureBox2->Size = System::Drawing::Size(765, 83);
				 this->pictureBox2->TabIndex = 50;
				 this->pictureBox2->TabStop = false;
				 // 
				 // tabPage2
				 // 
				 this->tabPage2->Controls->Add(this->textBoxName);
				 this->tabPage2->Controls->Add(this->label4);
				 this->tabPage2->Controls->Add(this->buttonConfig);
				 this->tabPage2->Controls->Add(this->buttonHost);
				 this->tabPage2->Controls->Add(this->buttonLocal);
				 this->tabPage2->Controls->Add(this->label2);
				 this->tabPage2->Controls->Add(this->comboBoxPort);
				 this->tabPage2->Controls->Add(this->buttonAdd);
				 this->tabPage2->Controls->Add(this->comboBoxIP);
				 this->tabPage2->Controls->Add(this->label1);
				 this->tabPage2->Controls->Add(this->labelIP);
				 this->tabPage2->Controls->Add(this->textPassword);
				 this->tabPage2->Location = System::Drawing::Point(4, 4);
				 this->tabPage2->Name = L"tabPage2";
				 this->tabPage2->Padding = System::Windows::Forms::Padding(3);
				 this->tabPage2->Size = System::Drawing::Size(759, 432);
				 this->tabPage2->TabIndex = 1;
				 this->tabPage2->Text = L"Add Server";
				 this->tabPage2->UseVisualStyleBackColor = true;
				 // 
				 // textBoxName
				 // 
				 this->textBoxName->Location = System::Drawing::Point(95, 107);
				 this->textBoxName->Name = L"textBoxName";
				 this->textBoxName->Size = System::Drawing::Size(175, 20);
				 this->textBoxName->TabIndex = 27;
				 // 
				 // label4
				 // 
				 this->label4->AutoSize = true;
				 this->label4->Location = System::Drawing::Point(20, 110);
				 this->label4->Name = L"label4";
				 this->label4->Size = System::Drawing::Size(69, 13);
				 this->label4->TabIndex = 26;
				 this->label4->Text = L"Name Server";
				 // 
				 // buttonConfig
				 // 
				 this->buttonConfig->Location = System::Drawing::Point(326, 21);
				 this->buttonConfig->Name = L"buttonConfig";
				 this->buttonConfig->Size = System::Drawing::Size(130, 45);
				 this->buttonConfig->TabIndex = 25;
				 this->buttonConfig->Text = L"Server Configuration";
				 this->buttonConfig->UseVisualStyleBackColor = true;
				 // 
				 // buttonHost
				 // 
				 this->buttonHost->Location = System::Drawing::Point(623, 21);
				 this->buttonHost->Name = L"buttonHost";
				 this->buttonHost->Size = System::Drawing::Size(130, 45);
				 this->buttonHost->TabIndex = 24;
				 this->buttonHost->Text = L"Create Host";
				 this->buttonHost->UseVisualStyleBackColor = true;
				 this->buttonHost->Click += gcnew System::EventHandler(this, &MainForm::buttonHost_Click);
				 // 
				 // buttonLocal
				 // 
				 this->buttonLocal->Location = System::Drawing::Point(23, 21);
				 this->buttonLocal->Name = L"buttonLocal";
				 this->buttonLocal->Size = System::Drawing::Size(130, 45);
				 this->buttonLocal->TabIndex = 23;
				 this->buttonLocal->Text = L"Create Local Server";
				 this->buttonLocal->UseVisualStyleBackColor = true;
				 this->buttonLocal->Click += gcnew System::EventHandler(this, &MainForm::buttonLocal_Click_1);
				 // 
				 // label2
				 // 
				 this->label2->AutoSize = true;
				 this->label2->Location = System::Drawing::Point(20, 181);
				 this->label2->Name = L"label2";
				 this->label2->Size = System::Drawing::Size(26, 13);
				 this->label2->TabIndex = 22;
				 this->label2->Text = L"Port";
				 // 
				 // comboBoxPort
				 // 
				 this->comboBoxPort->FormattingEnabled = true;
				 this->comboBoxPort->Items->AddRange(gcnew cli::array< System::Object^  >(1) { L"27015" });
				 this->comboBoxPort->Location = System::Drawing::Point(95, 178);
				 this->comboBoxPort->Name = L"comboBoxPort";
				 this->comboBoxPort->Size = System::Drawing::Size(175, 21);
				 this->comboBoxPort->TabIndex = 21;
				 // 
				 // buttonAdd
				 // 
				 this->buttonAdd->Location = System::Drawing::Point(326, 143);
				 this->buttonAdd->Name = L"buttonAdd";
				 this->buttonAdd->Size = System::Drawing::Size(96, 56);
				 this->buttonAdd->TabIndex = 20;
				 this->buttonAdd->Text = L"Add";
				 this->buttonAdd->UseVisualStyleBackColor = true;
				 this->buttonAdd->Click += gcnew System::EventHandler(this, &MainForm::buttonAdd_Click);
				 // 
				 // comboBoxIP
				 // 
				 this->comboBoxIP->FormattingEnabled = true;
				 this->comboBoxIP->Location = System::Drawing::Point(95, 143);
				 this->comboBoxIP->Name = L"comboBoxIP";
				 this->comboBoxIP->Size = System::Drawing::Size(175, 21);
				 this->comboBoxIP->TabIndex = 19;
				 // 
				 // label1
				 // 
				 this->label1->AutoSize = true;
				 this->label1->Location = System::Drawing::Point(20, 217);
				 this->label1->Name = L"label1";
				 this->label1->Size = System::Drawing::Size(53, 13);
				 this->label1->TabIndex = 18;
				 this->label1->Text = L"Password";
				 // 
				 // labelIP
				 // 
				 this->labelIP->AutoSize = true;
				 this->labelIP->Location = System::Drawing::Point(20, 146);
				 this->labelIP->Name = L"labelIP";
				 this->labelIP->Size = System::Drawing::Size(51, 13);
				 this->labelIP->TabIndex = 16;
				 this->labelIP->Text = L"IP Server";
				 // 
				 // textPassword
				 // 
				 this->textPassword->Location = System::Drawing::Point(95, 214);
				 this->textPassword->Name = L"textPassword";
				 this->textPassword->Size = System::Drawing::Size(175, 20);
				 this->textPassword->TabIndex = 17;
				 this->textPassword->UseSystemPasswordChar = true;
				 // 
				 // serverList
				 // 
				 this->serverList->Alignment = System::Windows::Forms::TabAlignment::Bottom;
				 this->serverList->Controls->Add(this->tabPage2);
				 this->serverList->Location = System::Drawing::Point(12, 27);
				 this->serverList->Name = L"serverList";
				 this->serverList->SelectedIndex = 0;
				 this->serverList->Size = System::Drawing::Size(767, 458);
				 this->serverList->TabIndex = 39;
				 // 
				 // MainForm
				 // 
				 this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
				 this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
				 this->AutoSize = true;
				 this->ClientSize = System::Drawing::Size(791, 672);
				 this->Controls->Add(this->pictureBox2);
				 this->Controls->Add(this->serverList);
				 this->Controls->Add(this->buttonCredits);
				 this->Controls->Add(this->buttonExit);
				 this->Controls->Add(this->buttonUpdate);
				 this->Controls->Add(this->linkLabel1);
				 this->Controls->Add(this->textBoxStatus);
				 this->Controls->Add(this->menuStrip1);
				 this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
				 this->Location = System::Drawing::Point(4, 4);
				 this->Name = L"MainForm";
				 this->Padding = System::Windows::Forms::Padding(3);
				 this->Text = L"MainForm";
				 this->menuStrip1->ResumeLayout(false);
				 this->menuStrip1->PerformLayout();
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->EndInit();
				 this->tabPage2->ResumeLayout(false);
				 this->tabPage2->PerformLayout();
				 this->serverList->ResumeLayout(false);
				 this->ResumeLayout(false);
				 this->PerformLayout();

			 }
#pragma endregion

	private: System::Void buttonRestart_Click(System::Object^  sender, System::EventArgs^  e) {
				 Connection[netCurrent]->sendData("gamRestartServer()");
	}
	private: System::Void buttonPause_Click(System::Object^  sender, System::EventArgs^  e) {
				 Connection[netCurrent]->sendData("samPauseGame()");
	}
	private: System::Void buttonPass_Click(System::Object^  sender, System::EventArgs^  e) {
				 Connection[netCurrent]->sendData("samVotePass()");
	}
	private: System::Void buttonFail_Click(System::Object^  sender, System::EventArgs^  e) {
				 Connection[netCurrent]->sendData("samVoteFail()");
	}
	private: System::Void buttonKick_Click(System::Object^  sender, System::EventArgs^  e) {
				
	}
	private: System::Void buttonBan_Click(System::Object^  sender, System::EventArgs^  e) {
				
	}
	private: System::Void cheatEnable0ToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
				 Connection[netCurrent]->sendData("cht_bEnableCheats=0");
	}
	private: System::Void cheat1ToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
				 Connection[netCurrent]->sendData("cht_bEnableCheats=1");
	}
	private: System::Void cheat2ToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
				 Connection[netCurrent]->sendData("cht_bEnableCheats=2");
	}
	private: System::Void cheat3ToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
				 Connection[netCurrent]->sendData("cht_bEnableCheats=3");
	}

	private: System::Void nextMapToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
				 Connection[netCurrent]->sendData("samNextMap()");
	}

	private: System::Void restartMapToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {

				 Connection[netCurrent]->sendData("samRestartMap()");
	}

	private: System::Void fortressToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
				 Connection[netCurrent]->sendData("samChangeMap(\"Content/SeriousSamHD/Levels/Z5_Other/Fortress.wld\")");
	}
	private: System::Void brkeenChevapToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
				 Connection[netCurrent]->sendData("samChangeMap(\"Content/SeriousSamHD/Levels/Z5_Other/BrkeenChevap.wld\")");
	}
	private: System::Void weGotSkullToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
				 Connection[netCurrent]->sendData("samChangeMap(\"Content/SeriousSamHD/Levels/Z5_Other/WeGotSkullsNBonesToo.wld\")");
	}
	private: System::Void holeToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
				 Connection[netCurrent]->sendData("samChangeMap(\"Content/SeriousSamHD/Levels/Z5_Other/Hole.wld\")");
	}
	private: System::Void jumpOverToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
				 Connection[netCurrent]->sendData("samChangeMap(\"Content/SeriousSamHD/Levels/Z5_Other/JumpOver.wld\")");
	}
	private: System::Void medievalRageToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
				 Connection[netCurrent]->sendData("samChangeMap(\"Content/SeriousSamHD/Levels/Z5_Other/MedievalRage.wld\")");
	}
	private: System::Void royalPurgatoryToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
				 Connection[netCurrent]->sendData("samChangeMap(\"Content/SeriousSamHD/Levels/Z5_Other/RoyalPurgatory.wld\")");
	}
	private: System::Void sunPalaceToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
				 Connection[netCurrent]->sendData("samChangeMap(\"Content/SeriousSamHD/Levels/Z5_Other/SunPalace.wld\")");
	}
	private: System::Void theLostTombToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
				 Connection[netCurrent]->sendData("samChangeMap(\"Content/SeriousSamHD/Levels/Z5_Other/TheLostTomb.wld\")");
	}
	private: System::Void yodellerToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
				 Connection[netCurrent]->sendData("samChangeMap(\"Content/SeriousSamHD/Levels/Z5_Other/Yodeller.wld\")");
	}
	private: System::Void linkLabel1_LinkClicked(System::Object^  sender, System::Windows::Forms::LinkLabelLinkClickedEventArgs^  e) {
				 System::Diagnostics::Process::Start("http://steamcommunity.com/groups/Nobel3DOfficial");
	}
	private: System::Void buttonUpdate_Click(System::Object^  sender, System::EventArgs^  e) {
				 System::Diagnostics::Process::Start("http://www.seriousteamhd.altervista.org/SeriousSamHDMyAdmin/NeedUpdate.php?version=" + Version);
	}
	private: System::Void groupBox1_Enter(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void menuStrip1_ItemClicked(System::Object^  sender, System::Windows::Forms::ToolStripItemClickedEventArgs^  e) {
	}
	private: System::Void textBoxChat_TextChanged(System::Object^  sender, System::EventArgs^  e) {

	}
	private: System::Void buttonExit_Click(System::Object^  sender, System::EventArgs^  e) {
				 if (MessageBox::Show("Do you want disconnect from " + Connection[netCurrent]->getIPServer() + " : " + Connection[netCurrent]->getPortServer() + " ?",
					 "Change Server?", MessageBoxButtons::YesNo, MessageBoxIcon::Exclamation) == Windows::Forms::DialogResult::Yes)
				 {
					 Connection[netCurrent]->~Rcon();

					 comboBoxIP->Text = "";
					 comboBoxPort->Text = "";
					 textPassword->Text = "";
					 Rcon::addLog2("[SYS] Waiting new Connection");
				 }
	}
	private: System::Void timedMessageToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {

				 form_SupportVoid = gcnew SupportForm();

				 form_SupportVoid->ShowDialog();

				 str_Timer = form_SupportVoid->getMessage();
				 int_Timer = form_SupportVoid->getMinute();
	}
	private: System::Void signatureChatToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {

				 form_SupportInt = gcnew SupportForm(1);

				 form_SupportInt->ShowDialog();

				 str_Message = form_SupportInt->getSignature();


	}
	private: System::Void ThreadHost()
	{
		while (true)
		{
			String^ getData;
			if (getData == "END")
			{

			}
			if (getData == "START")
			{
				if (getData->Contains("+"))
				{

				}
			}
			else
			{

			}
		}
	}
	private: System::Void unBanToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
				 form_SupportUnban = gcnew SupportForm("òpò");
				 form_SupportUnban->ShowDialog();
	}
	private: System::Void detailsToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
				 try{
					 MessageBox::Show("Gamemode: " + array_match[0] + "\nFragLimit: " + array_match[1] + "\nTimeLimit: " + array_match[2] + "\nGoalsLimit: " + array_match[3] +
						 "\nMinPlayers: " + array_match[4] + "\nMaxPlayers: " + array_match[5] + "\nJoinInProgress: " + array_match[6]);
				 }
				 catch (Exception^ w)
				 {
					 textBoxStatus->Text = "Service unavailable, restart a match";
					 Connection[netCurrent]->addLog("[RAS] Service unavailable: MatchDetails");
				 }
	}
	private: System::Void recentChatToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
				 MessageBox::Show("Service unavailable");
	}
	private: System::Void buttonCredits_Click(System::Object^  sender, System::EventArgs^  e) {
				 Credits^ ShowCredits = gcnew Credits();
				 ShowCredits->ShowDialog();
	}
	private: System::Void killMessageToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
				 SupportForm^ KillMessage = gcnew SupportForm(Connection[netCurrent]);
				 KillMessage->ShowDialog();
				 if (KillMessage->getEnabled())
				 {
					 EnabledMessage = true;
					 str_KillMessage = KillMessage->getKill();
					 str_SuicideMessage = KillMessage->getMessage();
				 }
				 else
				 {
					 EnabledMessage = false;
					 str_KillMessage = KillMessage->getKill();
					 str_SuicideMessage = KillMessage->getMessage();
				 }
	}
	private: System::Void didYouKnowToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
				 DidYouKnow();
	}
	private: System::Void creditsToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
				 Credits^ ShowCredits = gcnew Credits();
				 ShowCredits->ShowDialog();
	}
private: System::Void addAdminToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void buttonHost_Click(System::Object^  sender, System::EventArgs^  e) {
	netHost = gcnew Host(13000);
}
private: System::Void buttonLocal_Click_1(System::Object^  sender, System::EventArgs^  e) {
	form_MyDedicated = gcnew MyDedicated(MyDedicatedPath);
	form_MyDedicated->ShowDialog();
	if (!form_MyDedicated->IsExited())
	{
		ServerPage^ netConnect = gcnew ServerPage(gcnew Rcon("127.0.0.1", form_MyDedicated->getPort(), form_MyDedicated->getPassword()), serverList);
		netCount++;
		serverList->Controls->Add(netConnect->getPage(form_MyDedicated->getName(), gcnew System::ComponentModel::ComponentResourceManager(MainForm::typeid)));
	}
}
private: System::Void buttonAdd_Click(System::Object^  sender, System::EventArgs^  e) {
	if (comboBoxIP->Text == "" || comboBoxPort->Text == "" || textPassword->Text == "" || textBoxName->Text == "")
	{
		MessageBox::Show("You forget IP, Password or Name of server, please repeat and retry","ERROR 01", MessageBoxButtons::OK, MessageBoxIcon::Warning);
	}
	else
	{
		bufferIP = comboBoxIP->Text;
		bufferPort = comboBoxPort->Text;
		ServerPage^ newPage = gcnew ServerPage(gcnew Rcon(comboBoxIP->Text, Convert::ToInt32(comboBoxPort->Text), textPassword->Text), serverList);
		netCount++;
		serverList->Controls->Add(newPage->getPage(textBoxName->Text, gcnew System::ComponentModel::ComponentResourceManager(MainForm::typeid)));
	}

}
};
}

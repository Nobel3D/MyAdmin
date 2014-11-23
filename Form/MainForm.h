#pragma once

#include "..\stdafx.h"
#include "..\Class\Rcon.h"
#include "..\Class\Players.h"
#include "MyDedicated.h"
#include "SupportForm.h"
#include "Credits.h"
#include "YouKnow.h"
#include "..\Class\Database.h"

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
			Rcon::addLog("[SYS] System Loading");

			array_Player = gcnew array<Players^>(MAXPLAYERSUPPORT);
			array_match = gcnew array<String^>(7);

			for (int Ini = 0; Ini < MAXPLAYERSUPPORT; Ini++)
				array_Player[Ini] = gcnew Players();

			if (IO::File::Exists("MyAdmin.conf"))
			{
				ConfigFile("MyAdmin.conf");
			}
			else
			{
				Credits^ ShowCredits = gcnew Credits();
				ShowCredits->ShowDialog();
			}
			Rcon::addLog("[SYS] Loaded and Ready");
			settingUpMessage();
			DidYouKnow();
		}

	protected:
		/*Destructor of the main form*/
		~MainForm()
		{
			if (components)
			{


				if (Rcon::getOnline() == true)
				{
					MessageBox::Show("This application will be closed and will disconnects from server",
						"WARNING", MessageBoxButtons::OK, MessageBoxIcon::Warning);
					Timer->Abort();
					RasLog->Close();
					stm_WriteConfig = gcnew IO::StreamWriter("MyAdmin.conf", false);
					Rcon::addLog("[SYS] Saving Configurarion");
					stm_WriteConfig->WriteLine("LastIP=" + Connection->getIPServer());
					stm_WriteConfig->WriteLine("LastPort=" + Connection->getPortServer());
					stm_WriteConfig->WriteLine("Signature=" + str_Message);
					stm_WriteConfig->WriteLine("TimedString=" + str_Timer);
					stm_WriteConfig->WriteLine("TimedTime=" + int_Timer);
					stm_WriteConfig->WriteLine("ServerDedicatedPath=" + MyDedicatedPath);
					stm_WriteConfig->WriteLine("KillMessage=" + str_KillMessage);
					stm_WriteConfig->WriteLine("SuicideMessage=" + str_SuicideMessage);
					stm_WriteConfig->Close();

					textBoxStatus->Text = "Configuration Saved!";
					Connection->sendData("chatSay(\"Log: Closing terminal of MyAdmin!\")");
					Connection->~Rcon();
					Rcon::addLog("[SYS] Closing Application!");
					delete components;
				}
				delete components;
			}
		}
		/*Convenient way to set the buttons in MyAdmin*/
	private: System::Void buttonUsing(bool setting)
	{
				 buttonPause->Enabled = setting;
				 buttonRestart->Enabled = setting;
				 buttonKick->Enabled = setting;
				 buttonBan->Enabled = setting;
				 buttonPass->Enabled = setting;
				 buttonFail->Enabled = setting;
				 comboBoxPlayer->Enabled = setting;
				 menuStrip1->Enabled = setting;
				 buttonChat->Enabled = setting;
				 buttonExit->Enabled = setting;
				 buttonRanked->Enabled = setting;
				 buttonRcon->Enabled = setting;
				 comboBoxPlayer->Enabled = setting;
				 buttonConnect->Enabled = !setting;
				 comboBoxIP->Enabled = !setting;
				 comboBoxPort->Enabled = !setting;
				 textPassword->Enabled = !setting;
				 buttonLocal->Enabled = !setting;
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
			 /*Transform code adapted from markup code to normal text*/
			 String^ markupDecode(String^ strText)
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
			 /*It reads the config file, and set all values (I don't like this method, in future it will be as MyDedicated config)*/
	private: System::Void ConfigFile(String^ Path)
	{
				 stm_ReadConfig = gcnew IO::StreamReader(Path);
				 Rcon::addLog("[SYS] Loading Configuration");
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
						 comboBoxIP->Items->Add(array_Word[c][1]);
					 if (array_Word[c][0] == "LastPort")
					 {
						 if (array_Word[c][1] != "27015")
							 comboBoxPort->Items->Add(array_Word[c][1]);
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

			 /*Threading isn't secure if I don't use this method*/
#pragma region Threading secure
			 delegate void SetTextCallback(String^ text);

			 System::Void addText(String^ AddMe)
			 {
				 if (textBoxReceive->InvokeRequired)
				 {

					 SetTextCallback^ d = gcnew SetTextCallback(this, &MainForm::addText);
					 this->Invoke(d, gcnew array<Object^> { AddMe });
				 }
				 else
				 {
					 textBoxReceive->Text += AddMe;
				 }
			 }

			 System::Void addComboBox(String^ AddMe)
			 {
				 if (comboBoxPlayer->InvokeRequired)
				 {

					 SetTextCallback^ d = gcnew SetTextCallback(this, &MainForm::addComboBox);
					 this->Invoke(d, gcnew array<Object^> { AddMe });
				 }
				 else
				 {
					 comboBoxPlayer->Items->Add(AddMe);
				 }
			 }

			 System::Void addComboBoxRank(String^ AddMe)
			 {
				 if (comboBoxPlayerRank->InvokeRequired)
				 {

					 SetTextCallback^ d = gcnew SetTextCallback(this, &MainForm::addComboBoxRank);
					 this->Invoke(d, gcnew array<Object^> { AddMe });
				 }
				 else
				 {
					 comboBoxPlayerRank->Items->Add(AddMe);
				 }
			 }

			 System::Void delComboBox(String^ AddMe)
			 {
				 if (comboBoxPlayer->InvokeRequired)
				 {
					 SetTextCallback^ d = gcnew SetTextCallback(this, &MainForm::delComboBox);
					 this->Invoke(d, gcnew array<Object^> { AddMe });
				 }
				 else
				 {
					 comboBoxPlayer->Items->Remove(AddMe);
				 }
			 }

			 System::Void delComboBoxRank(String^ AddMe)
			 {
				 if (comboBoxPlayerRank->InvokeRequired)
				 {
					 SetTextCallback^ d = gcnew SetTextCallback(this, &MainForm::delComboBoxRank);
					 this->Invoke(d, gcnew array<Object^> { AddMe });
				 }
				 else
				 {
					 comboBoxPlayerRank->Items->Remove(AddMe);
				 }
			 }
#pragma endregion
			 /*Method of manage the Loading of the players*/
			 System::Void LoadPlayer(array<String^>^ ArrayStream)
			 {
				 try
				 {

					 String^ ID = ArrayStream[3]->Trim();
					 String^ Nick = markupDecode(ArrayStream[1]);

					 if (!Players::AlreadyStarted(array_Player, ID))
					 {
						 if (!Players::IsBanned(ID))
						 {
							 playerJoined = Players::FindIndex(array_Player, ID);
							 if (playerJoined <= -1)
							 {
								 if (StartRank)
								 {
									 Connection->sendData("gamKickByIP(\"" + ID + "\")");
									 Connection->SamChat("Log: Player Unloaded -> " + Nick);
									 Connection->addLog("[RAS] Player: " + Nick + "; ID: " + ID + "; Unload Kicked! ");
								 }
								 else
								 {
									 Connection->addLog("[RAS] Player: " + Nick + "; ID: " + ID + "; Unload Warning! ");
								 }
							 }
							 else
							 {
								 array_Player[playerJoined] = Players::Load(ID, Nick, playerJoined);
								 addComboBox(Nick);
								 addComboBoxRank(Nick);
								 Connection->addLog("[RAS] Player: " + Nick + "; ID: " + ID + "; Index:" + playerJoined + "; Loaded");
							 }
						 }
						 else
						 {
							 Connection->sendData("gamKickByIP(\"" + ID + "\")");
							 Connection->addLog("[NSB] Player: " + Nick + "; ID: " + ID + "; Banned");
							 Connection->SamChat("Ban Machine: " + Nick + " Bye Bye");
						 }
					 }
				 }
				 catch (Exception^ error)
				 {
					 MessageBox::Show(error->ToString());
				 }
			 }

			 //MyClass
	private: Rcon^ Connection;
	private: Database^ dbSam;
	private: array<Players^>^ array_Player;
			 //Main String
	private: static String^ str_KillMessage = "'opo'";
	private: static String^ str_SuicideMessage = "xddd";
	private: static String^ str_Message = "Admin";
	private: static String^ Version = "1.5";
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
	private: SupportForm^ form_SupportBan;
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
	private: Thread^ Timer;
	private: ThreadStart^ StartTimer;
	private: static String^ str_Help = "";
	private: static array<String^>^ Spliter = { ": ", ", " };
	private: static array<String^>^ localSplit = { "\"" };
	private: array<String^>^ array_Stream;
	private: array<String^>^ array_match;
	private: static String^ Buffer = "";
	private: int playerJoined;
	private: bool EnabledMessage;
	private: static IO::StreamWriter^ RasLog = gcnew IO::StreamWriter("RAS.txt", false);

#pragma region Form Pointer

	private: System::Windows::Forms::MenuStrip^  menuStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^  playerToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  banForToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  thisMatchToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  minutesToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  minutesToolStripMenuItem1;
	private: System::Windows::Forms::ToolStripMenuItem^  dayToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  daysToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  mouthToolStripMenuItem;
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
	private: System::Windows::Forms::Timer^  timer;
	private: System::Windows::Forms::Timer^  timerRAS;
	private: System::Windows::Forms::ToolStripMenuItem^  killMessageToolStripMenuItem;
	private: System::Windows::Forms::Button^  buttonKick;
	private: System::Windows::Forms::Button^  buttonBan;
	private: System::Windows::Forms::Button^  buttonPass;
	private: System::Windows::Forms::Button^  buttonFail;
	private: System::Windows::Forms::TextBox^  textPassword;
	private: System::Windows::Forms::Button^  buttonRestart;
	private: System::Windows::Forms::Label^  labelIP;
	private: System::Windows::Forms::Button^  buttonPause;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::ComboBox^  comboBoxIP;
	private: System::Windows::Forms::Button^  buttonConnect;
	private: System::Windows::Forms::ComboBox^  comboBoxPort;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Button^  buttonLocal;
	private: System::Windows::Forms::Button^  buttonRanked;
	private: System::Windows::Forms::TextBox^  textBoxRcon;
	private: System::Windows::Forms::Button^  buttonRcon;
	private: System::Windows::Forms::GroupBox^  groupBox1;
	private: System::Windows::Forms::TextBox^  textBoxChat;
	private: System::Windows::Forms::Button^  buttonChat;
	private: System::Windows::Forms::TextBox^  textBoxStatus;
	private: System::Windows::Forms::LinkLabel^  linkLabel1;
	private: System::Windows::Forms::Button^  buttonUpdate;
	private: System::Windows::Forms::Button^  buttonExit;
	private: System::Windows::Forms::ComboBox^  comboBoxPlayerRank;
	private: System::Windows::Forms::ComboBox^  comboBoxPlayer;
	private: System::Windows::Forms::Button^  buttonCredits;
	private: System::Windows::Forms::ToolStripMenuItem^  helpToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  didYouKnowToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  creditsToolStripMenuItem;
private: System::Windows::Forms::TextBox^  textBoxReceive;
	private: System::Windows::Forms::PictureBox^  pictureBox1;
private: System::Windows::Forms::PictureBox^  pictureBox2;
	private: System::ComponentModel::IContainer^  components;
#pragma endregion

#pragma region Windows Form Designer generated code
			 void InitializeComponent(void)
			 {
				 this->components = (gcnew System::ComponentModel::Container());
				 System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(MainForm::typeid));
				 this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
				 this->playerToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->banForToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->thisMatchToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->minutesToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->minutesToolStripMenuItem1 = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->dayToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->daysToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->mouthToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
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
				 this->timer = (gcnew System::Windows::Forms::Timer(this->components));
				 this->timerRAS = (gcnew System::Windows::Forms::Timer(this->components));
				 this->buttonKick = (gcnew System::Windows::Forms::Button());
				 this->buttonBan = (gcnew System::Windows::Forms::Button());
				 this->buttonPass = (gcnew System::Windows::Forms::Button());
				 this->buttonFail = (gcnew System::Windows::Forms::Button());
				 this->textPassword = (gcnew System::Windows::Forms::TextBox());
				 this->buttonRestart = (gcnew System::Windows::Forms::Button());
				 this->labelIP = (gcnew System::Windows::Forms::Label());
				 this->buttonPause = (gcnew System::Windows::Forms::Button());
				 this->label1 = (gcnew System::Windows::Forms::Label());
				 this->comboBoxIP = (gcnew System::Windows::Forms::ComboBox());
				 this->buttonConnect = (gcnew System::Windows::Forms::Button());
				 this->comboBoxPort = (gcnew System::Windows::Forms::ComboBox());
				 this->label2 = (gcnew System::Windows::Forms::Label());
				 this->buttonLocal = (gcnew System::Windows::Forms::Button());
				 this->buttonRanked = (gcnew System::Windows::Forms::Button());
				 this->textBoxRcon = (gcnew System::Windows::Forms::TextBox());
				 this->buttonRcon = (gcnew System::Windows::Forms::Button());
				 this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
				 this->textBoxReceive = (gcnew System::Windows::Forms::TextBox());
				 this->textBoxChat = (gcnew System::Windows::Forms::TextBox());
				 this->buttonChat = (gcnew System::Windows::Forms::Button());
				 this->textBoxStatus = (gcnew System::Windows::Forms::TextBox());
				 this->linkLabel1 = (gcnew System::Windows::Forms::LinkLabel());
				 this->buttonUpdate = (gcnew System::Windows::Forms::Button());
				 this->buttonExit = (gcnew System::Windows::Forms::Button());
				 this->comboBoxPlayerRank = (gcnew System::Windows::Forms::ComboBox());
				 this->comboBoxPlayer = (gcnew System::Windows::Forms::ComboBox());
				 this->buttonCredits = (gcnew System::Windows::Forms::Button());
				 this->pictureBox2 = (gcnew System::Windows::Forms::PictureBox());
				 this->menuStrip1->SuspendLayout();
				 this->groupBox1->SuspendLayout();
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->BeginInit();
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
				 this->menuStrip1->Location = System::Drawing::Point(0, 0);
				 this->menuStrip1->Name = L"menuStrip1";
				 this->menuStrip1->Size = System::Drawing::Size(791, 24);
				 this->menuStrip1->TabIndex = 26;
				 this->menuStrip1->Text = L"menuStrip1";
				 // 
				 // playerToolStripMenuItem
				 // 
				 this->playerToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
					 this->banForToolStripMenuItem,
						 this->unBanToolStripMenuItem
				 });
				 this->playerToolStripMenuItem->Name = L"playerToolStripMenuItem";
				 this->playerToolStripMenuItem->Size = System::Drawing::Size(51, 20);
				 this->playerToolStripMenuItem->Text = L"Player";
				 // 
				 // banForToolStripMenuItem
				 // 
				 this->banForToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(6) {
					 this->thisMatchToolStripMenuItem,
						 this->minutesToolStripMenuItem, this->minutesToolStripMenuItem1, this->dayToolStripMenuItem, this->daysToolStripMenuItem, this->mouthToolStripMenuItem
				 });
				 this->banForToolStripMenuItem->Name = L"banForToolStripMenuItem";
				 this->banForToolStripMenuItem->Size = System::Drawing::Size(112, 22);
				 this->banForToolStripMenuItem->Text = L"Ban for";
				 // 
				 // thisMatchToolStripMenuItem
				 // 
				 this->thisMatchToolStripMenuItem->Name = L"thisMatchToolStripMenuItem";
				 this->thisMatchToolStripMenuItem->Size = System::Drawing::Size(138, 22);
				 this->thisMatchToolStripMenuItem->Text = L"This Match";
				 this->thisMatchToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::thisMatchToolStripMenuItem_Click);
				 // 
				 // minutesToolStripMenuItem
				 // 
				 this->minutesToolStripMenuItem->Name = L"minutesToolStripMenuItem";
				 this->minutesToolStripMenuItem->Size = System::Drawing::Size(138, 22);
				 this->minutesToolStripMenuItem->Text = L"30 Minutes";
				 this->minutesToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::minutesToolStripMenuItem_Click);
				 // 
				 // minutesToolStripMenuItem1
				 // 
				 this->minutesToolStripMenuItem1->Name = L"minutesToolStripMenuItem1";
				 this->minutesToolStripMenuItem1->Size = System::Drawing::Size(138, 22);
				 this->minutesToolStripMenuItem1->Text = L"120 Minutes";
				 this->minutesToolStripMenuItem1->Click += gcnew System::EventHandler(this, &MainForm::minutesToolStripMenuItem1_Click);
				 // 
				 // dayToolStripMenuItem
				 // 
				 this->dayToolStripMenuItem->Name = L"dayToolStripMenuItem";
				 this->dayToolStripMenuItem->Size = System::Drawing::Size(138, 22);
				 this->dayToolStripMenuItem->Text = L"1 Day";
				 this->dayToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::dayToolStripMenuItem_Click);
				 // 
				 // daysToolStripMenuItem
				 // 
				 this->daysToolStripMenuItem->Name = L"daysToolStripMenuItem";
				 this->daysToolStripMenuItem->Size = System::Drawing::Size(138, 22);
				 this->daysToolStripMenuItem->Text = L"7 Days";
				 this->daysToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::daysToolStripMenuItem_Click);
				 // 
				 // mouthToolStripMenuItem
				 // 
				 this->mouthToolStripMenuItem->Name = L"mouthToolStripMenuItem";
				 this->mouthToolStripMenuItem->Size = System::Drawing::Size(138, 22);
				 this->mouthToolStripMenuItem->Text = L"1 Mouth";
				 this->mouthToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::mouthToolStripMenuItem_Click);
				 // 
				 // unBanToolStripMenuItem
				 // 
				 this->unBanToolStripMenuItem->Name = L"unBanToolStripMenuItem";
				 this->unBanToolStripMenuItem->Size = System::Drawing::Size(112, 22);
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
				 // timer
				 // 
				 this->timer->Enabled = true;
				 this->timer->Interval = 1000;
				 this->timer->Tick += gcnew System::EventHandler(this, &MainForm::timer_Tick);
				 // 
				 // timerRAS
				 // 
				 this->timerRAS->Interval = 5;
				 // 
				 // buttonKick
				 // 
				 this->buttonKick->Enabled = false;
				 this->buttonKick->Location = System::Drawing::Point(43, 327);
				 this->buttonKick->Name = L"buttonKick";
				 this->buttonKick->Size = System::Drawing::Size(163, 23);
				 this->buttonKick->TabIndex = 21;
				 this->buttonKick->Text = L"Kick Player";
				 this->buttonKick->UseVisualStyleBackColor = true;
				 this->buttonKick->Click += gcnew System::EventHandler(this, &MainForm::buttonKick_Click);
				 // 
				 // buttonBan
				 // 
				 this->buttonBan->Enabled = false;
				 this->buttonBan->Location = System::Drawing::Point(43, 373);
				 this->buttonBan->Name = L"buttonBan";
				 this->buttonBan->Size = System::Drawing::Size(163, 23);
				 this->buttonBan->TabIndex = 22;
				 this->buttonBan->Text = L"Ban Player";
				 this->buttonBan->UseVisualStyleBackColor = true;
				 this->buttonBan->Click += gcnew System::EventHandler(this, &MainForm::buttonBan_Click);
				 // 
				 // buttonPass
				 // 
				 this->buttonPass->Enabled = false;
				 this->buttonPass->Location = System::Drawing::Point(590, 327);
				 this->buttonPass->Name = L"buttonPass";
				 this->buttonPass->Size = System::Drawing::Size(163, 23);
				 this->buttonPass->TabIndex = 23;
				 this->buttonPass->Text = L"Vote Pass";
				 this->buttonPass->UseVisualStyleBackColor = true;
				 this->buttonPass->Click += gcnew System::EventHandler(this, &MainForm::buttonPass_Click);
				 // 
				 // buttonFail
				 // 
				 this->buttonFail->Enabled = false;
				 this->buttonFail->Location = System::Drawing::Point(589, 373);
				 this->buttonFail->Name = L"buttonFail";
				 this->buttonFail->Size = System::Drawing::Size(163, 23);
				 this->buttonFail->TabIndex = 24;
				 this->buttonFail->Text = L"Vote Fail";
				 this->buttonFail->UseVisualStyleBackColor = true;
				 this->buttonFail->Click += gcnew System::EventHandler(this, &MainForm::buttonFail_Click);
				 // 
				 // textPassword
				 // 
				 this->textPassword->Location = System::Drawing::Point(291, 73);
				 this->textPassword->Name = L"textPassword";
				 this->textPassword->Size = System::Drawing::Size(192, 20);
				 this->textPassword->TabIndex = 3;
				 this->textPassword->UseSystemPasswordChar = true;
				 // 
				 // buttonRestart
				 // 
				 this->buttonRestart->Enabled = false;
				 this->buttonRestart->Location = System::Drawing::Point(31, 112);
				 this->buttonRestart->Name = L"buttonRestart";
				 this->buttonRestart->Size = System::Drawing::Size(163, 23);
				 this->buttonRestart->TabIndex = 8;
				 this->buttonRestart->Text = L"Restart Server";
				 this->buttonRestart->UseVisualStyleBackColor = true;
				 this->buttonRestart->Click += gcnew System::EventHandler(this, &MainForm::buttonRestart_Click);
				 // 
				 // labelIP
				 // 
				 this->labelIP->AutoSize = true;
				 this->labelIP->Location = System::Drawing::Point(166, 25);
				 this->labelIP->Name = L"labelIP";
				 this->labelIP->Size = System::Drawing::Size(51, 13);
				 this->labelIP->TabIndex = 2;
				 this->labelIP->Text = L"IP Server";
				 // 
				 // buttonPause
				 // 
				 this->buttonPause->Enabled = false;
				 this->buttonPause->Location = System::Drawing::Point(577, 112);
				 this->buttonPause->Name = L"buttonPause";
				 this->buttonPause->Size = System::Drawing::Size(163, 23);
				 this->buttonPause->TabIndex = 9;
				 this->buttonPause->Text = L"Pause Game";
				 this->buttonPause->UseVisualStyleBackColor = true;
				 this->buttonPause->Click += gcnew System::EventHandler(this, &MainForm::buttonPause_Click);
				 // 
				 // label1
				 // 
				 this->label1->AutoSize = true;
				 this->label1->Location = System::Drawing::Point(362, 57);
				 this->label1->Name = L"label1";
				 this->label1->Size = System::Drawing::Size(53, 13);
				 this->label1->TabIndex = 11;
				 this->label1->Text = L"Password";
				 // 
				 // comboBoxIP
				 // 
				 this->comboBoxIP->FormattingEnabled = true;
				 this->comboBoxIP->Location = System::Drawing::Point(223, 22);
				 this->comboBoxIP->Name = L"comboBoxIP";
				 this->comboBoxIP->Size = System::Drawing::Size(144, 21);
				 this->comboBoxIP->TabIndex = 12;
				 // 
				 // buttonConnect
				 // 
				 this->buttonConnect->Location = System::Drawing::Point(291, 112);
				 this->buttonConnect->Name = L"buttonConnect";
				 this->buttonConnect->Size = System::Drawing::Size(194, 23);
				 this->buttonConnect->TabIndex = 13;
				 this->buttonConnect->Text = L"Connect";
				 this->buttonConnect->UseVisualStyleBackColor = true;
				 this->buttonConnect->Click += gcnew System::EventHandler(this, &MainForm::buttonConnect_Click);
				 // 
				 // comboBoxPort
				 // 
				 this->comboBoxPort->FormattingEnabled = true;
				 this->comboBoxPort->Items->AddRange(gcnew cli::array< System::Object^  >(1) { L"27015" });
				 this->comboBoxPort->Location = System::Drawing::Point(456, 25);
				 this->comboBoxPort->Name = L"comboBoxPort";
				 this->comboBoxPort->Size = System::Drawing::Size(144, 21);
				 this->comboBoxPort->TabIndex = 14;
				 // 
				 // label2
				 // 
				 this->label2->AutoSize = true;
				 this->label2->Location = System::Drawing::Point(424, 25);
				 this->label2->Name = L"label2";
				 this->label2->Size = System::Drawing::Size(26, 13);
				 this->label2->TabIndex = 15;
				 this->label2->Text = L"Port";
				 // 
				 // buttonLocal
				 // 
				 this->buttonLocal->Location = System::Drawing::Point(31, 57);
				 this->buttonLocal->Name = L"buttonLocal";
				 this->buttonLocal->Size = System::Drawing::Size(163, 23);
				 this->buttonLocal->TabIndex = 16;
				 this->buttonLocal->Text = L"Create Local Server";
				 this->buttonLocal->UseVisualStyleBackColor = true;
				 this->buttonLocal->Click += gcnew System::EventHandler(this, &MainForm::buttonLocal_Click);
				 // 
				 // buttonRanked
				 // 
				 this->buttonRanked->Enabled = false;
				 this->buttonRanked->Location = System::Drawing::Point(578, 57);
				 this->buttonRanked->Name = L"buttonRanked";
				 this->buttonRanked->Size = System::Drawing::Size(163, 23);
				 this->buttonRanked->TabIndex = 17;
				 this->buttonRanked->Text = L"Start MyRanked";
				 this->buttonRanked->UseVisualStyleBackColor = true;
				 this->buttonRanked->Click += gcnew System::EventHandler(this, &MainForm::button2_Click);
				 // 
				 // textBoxRcon
				 // 
				 this->textBoxRcon->Location = System::Drawing::Point(31, 234);
				 this->textBoxRcon->Name = L"textBoxRcon";
				 this->textBoxRcon->Size = System::Drawing::Size(613, 20);
				 this->textBoxRcon->TabIndex = 35;
				 this->textBoxRcon->Text = L"Send Command";
				 // 
				 // buttonRcon
				 // 
				 this->buttonRcon->Enabled = false;
				 this->buttonRcon->Location = System::Drawing::Point(650, 233);
				 this->buttonRcon->Name = L"buttonRcon";
				 this->buttonRcon->Size = System::Drawing::Size(90, 20);
				 this->buttonRcon->TabIndex = 36;
				 this->buttonRcon->Text = L"Send Rcon";
				 this->buttonRcon->UseVisualStyleBackColor = true;
				 this->buttonRcon->Click += gcnew System::EventHandler(this, &MainForm::buttonRcon_Click);
				 // 
				 // groupBox1
				 // 
				 this->groupBox1->Controls->Add(this->textBoxReceive);
				 this->groupBox1->Controls->Add(this->buttonRcon);
				 this->groupBox1->Controls->Add(this->textBoxRcon);
				 this->groupBox1->Controls->Add(this->buttonRanked);
				 this->groupBox1->Controls->Add(this->buttonLocal);
				 this->groupBox1->Controls->Add(this->label2);
				 this->groupBox1->Controls->Add(this->comboBoxPort);
				 this->groupBox1->Controls->Add(this->buttonConnect);
				 this->groupBox1->Controls->Add(this->comboBoxIP);
				 this->groupBox1->Controls->Add(this->label1);
				 this->groupBox1->Controls->Add(this->buttonPause);
				 this->groupBox1->Controls->Add(this->labelIP);
				 this->groupBox1->Controls->Add(this->buttonRestart);
				 this->groupBox1->Controls->Add(this->textPassword);
				 this->groupBox1->Location = System::Drawing::Point(12, 40);
				 this->groupBox1->Name = L"groupBox1";
				 this->groupBox1->Size = System::Drawing::Size(766, 271);
				 this->groupBox1->TabIndex = 25;
				 this->groupBox1->TabStop = false;
				 // 
				 // textBoxReceive
				 // 
				 this->textBoxReceive->Location = System::Drawing::Point(31, 141);
				 this->textBoxReceive->Multiline = true;
				 this->textBoxReceive->Name = L"textBoxReceive";
				 this->textBoxReceive->ReadOnly = true;
				 this->textBoxReceive->Size = System::Drawing::Size(710, 86);
				 this->textBoxReceive->TabIndex = 37;
				 // 
				 // textBoxChat
				 // 
				 this->textBoxChat->Location = System::Drawing::Point(12, 551);
				 this->textBoxChat->Name = L"textBoxChat";
				 this->textBoxChat->Size = System::Drawing::Size(660, 20);
				 this->textBoxChat->TabIndex = 27;
				 this->textBoxChat->Text = L"Admin Chat";
				 // 
				 // buttonChat
				 // 
				 this->buttonChat->Enabled = false;
				 this->buttonChat->Location = System::Drawing::Point(686, 551);
				 this->buttonChat->Name = L"buttonChat";
				 this->buttonChat->Size = System::Drawing::Size(92, 23);
				 this->buttonChat->TabIndex = 28;
				 this->buttonChat->Text = L"Send Chat";
				 this->buttonChat->UseVisualStyleBackColor = true;
				 this->buttonChat->Click += gcnew System::EventHandler(this, &MainForm::buttonChat_Click);
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
				 // comboBoxPlayerRank
				 // 
				 this->comboBoxPlayerRank->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
				 this->comboBoxPlayerRank->Enabled = false;
				 this->comboBoxPlayerRank->FormattingEnabled = true;
				 this->comboBoxPlayerRank->Location = System::Drawing::Point(303, 350);
				 this->comboBoxPlayerRank->Name = L"comboBoxPlayerRank";
				 this->comboBoxPlayerRank->Size = System::Drawing::Size(194, 21);
				 this->comboBoxPlayerRank->TabIndex = 34;
				 this->comboBoxPlayerRank->SelectedIndexChanged += gcnew System::EventHandler(this, &MainForm::comboBoxPlayerRank_SelectedIndexChanged);
				 // 
				 // comboBoxPlayer
				 // 
				 this->comboBoxPlayer->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
				 this->comboBoxPlayer->Enabled = false;
				 this->comboBoxPlayer->FormattingEnabled = true;
				 this->comboBoxPlayer->Location = System::Drawing::Point(43, 423);
				 this->comboBoxPlayer->Name = L"comboBoxPlayer";
				 this->comboBoxPlayer->Size = System::Drawing::Size(163, 21);
				 this->comboBoxPlayer->TabIndex = 35;
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
				 this->pictureBox2->Location = System::Drawing::Point(13, 450);
				 this->pictureBox2->Name = L"pictureBox2";
				 this->pictureBox2->Size = System::Drawing::Size(765, 95);
				 this->pictureBox2->TabIndex = 39;
				 this->pictureBox2->TabStop = false;
				 // 
				 // MainForm
				 // 
				 this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
				 this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
				 this->AutoSize = true;
				 this->ClientSize = System::Drawing::Size(791, 672);
				 this->Controls->Add(this->pictureBox2);
				 this->Controls->Add(this->buttonCredits);
				 this->Controls->Add(this->comboBoxPlayer);
				 this->Controls->Add(this->comboBoxPlayerRank);
				 this->Controls->Add(this->buttonExit);
				 this->Controls->Add(this->buttonUpdate);
				 this->Controls->Add(this->linkLabel1);
				 this->Controls->Add(this->textBoxStatus);
				 this->Controls->Add(this->buttonChat);
				 this->Controls->Add(this->textBoxChat);
				 this->Controls->Add(this->groupBox1);
				 this->Controls->Add(this->buttonFail);
				 this->Controls->Add(this->buttonPass);
				 this->Controls->Add(this->buttonBan);
				 this->Controls->Add(this->buttonKick);
				 this->Controls->Add(this->menuStrip1);
				 this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
				 this->Name = L"MainForm";
				 this->Text = L"MainForm";
				 this->menuStrip1->ResumeLayout(false);
				 this->menuStrip1->PerformLayout();
				 this->groupBox1->ResumeLayout(false);
				 this->groupBox1->PerformLayout();
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->EndInit();
				 this->ResumeLayout(false);
				 this->PerformLayout();

			 }
#pragma endregion
	private: System::Void buttonConnect_Click(System::Object^  sender, System::EventArgs^  e)
	{
				 if (textPassword->Text == "" || comboBoxIP->Text == "" || comboBoxPort->Text == "")
					 MessageBox::Show("You forget IP or Password! Please Insert and Repeat.", "ERROR 01", MessageBoxButtons::OK, MessageBoxIcon::Warning);
				 else
				 {
					 Connection = gcnew Rcon(comboBoxIP->Text, Convert::ToInt32(comboBoxPort->Text), textPassword->Text);
					 Connection->connectRcon();
					 StartTimer = gcnew ThreadStart(this, &MainForm::ThreadTimer);
					 Timer = gcnew Thread(StartTimer);
					 Timer->Start();
					 Thread::Sleep(1000);
					 if (!Connection->getOnline())
					 {
						 MessageBox::Show("Generic: Error connecting from Rcon.", "ERROR 02", MessageBoxButtons::OK, MessageBoxIcon::Error);
						 textBoxStatus->Text = Connection->getStatus();
					 }
					 else
					 {
						 MessageBox::Show("Connection is started.", "Initialize", MessageBoxButtons::OK, MessageBoxIcon::Information);

						 textPassword->Text = "#PASSWORD#";
						 textBoxStatus->Text = Connection->getStatus();

						 Connection->sendData("chatSay(\"Log: Some Admin has started a GUI MyAdmin by Nobel3D\")");
						 buttonUsing(true);


					 }
				 }
	}
	private: System::Void buttonRestart_Click(System::Object^  sender, System::EventArgs^  e) {
				 Connection->sendData("gamRestartServer()");
	}
	private: System::Void buttonPause_Click(System::Object^  sender, System::EventArgs^  e) {
				 Connection->sendData("samPauseGame()");
	}
	private: System::Void buttonPass_Click(System::Object^  sender, System::EventArgs^  e) {
				 Connection->sendData("samVotePass()");
	}
	private: System::Void buttonFail_Click(System::Object^  sender, System::EventArgs^  e) {
				 Connection->sendData("samVoteFail()");
	}
	private: System::Void buttonKick_Click(System::Object^  sender, System::EventArgs^  e) {
				 if (comboBoxPlayer->Text == "")
				 {
					 MessageBox::Show("Please insert a name player", "ERROR 03", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
				 }
				 else
				 {
					 Connection->sendData("gamKickByName(\"" + comboBoxPlayer->Text + "\")");
					 comboBoxPlayer->Items->Remove(comboBoxPlayer->Text);
				 }
	}
	private: System::Void buttonBan_Click(System::Object^  sender, System::EventArgs^  e) {
				 if (comboBoxPlayer->Text == "")
				 {
					 MessageBox::Show("Please insert a name player", "ERROR 03", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
				 }
				 else
				 {
					 Connection->sendData("gamBanByName(\"" + comboBoxPlayer->Text + "\")");
					 comboBoxPlayer->Items->Remove(comboBoxPlayer->Text);
				 }
	}
	private: System::Void cheatEnable0ToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
				 Connection->sendData("cht_bEnableCheats=0");
	}
	private: System::Void cheat1ToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
				 Connection->sendData("cht_bEnableCheats=1");
	}
	private: System::Void cheat2ToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
				 Connection->sendData("cht_bEnableCheats=2");
	}
	private: System::Void cheat3ToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
				 Connection->sendData("cht_bEnableCheats=3");
	}

	private: System::Void buttonChat_Click(System::Object^  sender, System::EventArgs^  e) {
				 Connection->sendData("chatSay(\"" + str_Message + ": " + textBoxChat->Text + "\")");
				 Connection->addLog("[ASP] Chat Send: " + textBoxChat->Text);
				 textBoxChat->Clear();
				 buttonChat->Enabled = false;
				 ActiveSend = Seconds;
				 Spam = true;
	}
	private: System::Void nextMapToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
				 Connection->sendData("samNextMap()");
	}

	private: System::Void restartMapToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {

				 Connection->sendData("samRestartMap()");
	}

	private: System::Void fortressToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
				 Connection->sendData("samChangeMap(\"Content/SeriousSamHD/Levels/Z5_Other/Fortress.wld\")");
	}
	private: System::Void brkeenChevapToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
				 Connection->sendData("samChangeMap(\"Content/SeriousSamHD/Levels/Z5_Other/BrkeenChevap.wld\")");
	}
	private: System::Void weGotSkullToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
				 Connection->sendData("samChangeMap(\"Content/SeriousSamHD/Levels/Z5_Other/WeGotSkullsNBonesToo.wld\")");
	}
	private: System::Void holeToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
				 Connection->sendData("samChangeMap(\"Content/SeriousSamHD/Levels/Z5_Other/Hole.wld\")");
	}
	private: System::Void jumpOverToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
				 Connection->sendData("samChangeMap(\"Content/SeriousSamHD/Levels/Z5_Other/JumpOver.wld\")");
	}
	private: System::Void medievalRageToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
				 Connection->sendData("samChangeMap(\"Content/SeriousSamHD/Levels/Z5_Other/MedievalRage.wld\")");
	}
	private: System::Void royalPurgatoryToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
				 Connection->sendData("samChangeMap(\"Content/SeriousSamHD/Levels/Z5_Other/RoyalPurgatory.wld\")");
	}
	private: System::Void sunPalaceToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
				 Connection->sendData("samChangeMap(\"Content/SeriousSamHD/Levels/Z5_Other/SunPalace.wld\")");
	}
	private: System::Void theLostTombToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
				 Connection->sendData("samChangeMap(\"Content/SeriousSamHD/Levels/Z5_Other/TheLostTomb.wld\")");
	}
	private: System::Void yodellerToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
				 Connection->sendData("samChangeMap(\"Content/SeriousSamHD/Levels/Z5_Other/Yodeller.wld\")");
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
				 if (MessageBox::Show("Do you want disconnect from " + Connection->getIPServer() + " : " + Connection->getPortServer() + " ?",
					 "Change Server?", MessageBoxButtons::YesNo, MessageBoxIcon::Exclamation) == Windows::Forms::DialogResult::Yes)
				 {
					 Connection->~Rcon();

					 buttonUsing(false);

					 comboBoxIP->Text = "";
					 comboBoxPort->Text = "";
					 textPassword->Text = "";
					 Rcon::addLog("[SYS] Waiting new Connection");
				 }
	}
	private: System::Void timer_Tick(System::Object^  sender, System::EventArgs^  e) {
				 Seconds++;
				 if (Seconds>59)
				 {
					 Seconds = 0;
					 Minute++;
				 }
				 if (Minute == 15 * Multy)
				 {
					 if (Seconds == 30)
					 {
						 Multy++;
						 if (Connection->getOnline())
						 {
							 Connection->sendData("samVoteFail()");
							 if (StartRank)
								 Connection->SamChat("Log: ~ This match will be ranked! ~");
						 }
					 }
				 }
				 if (str_Timer != ""&&int_Timer != 0 && Connection->getOnline() == true)
				 {
					 secTime++;
					 if (secTime>59)
					 {
						 secTime = 0;
						 minTime++;
					 }
					 if (minTime == CstdTime)
					 {
						 CstdTime += int_Timer;
						 Connection->sendData("chatSay(\"" + str_Message + ": " + str_Timer + "\")");
					 }
				 }
				 if (Connection->getOnline() == true && Spam == true)
				 {
					 if ((ActiveSend + 5)>60)
					 {
						 if (ActiveSend>Seconds)
							 buttonChat->Enabled = true;
					 }
					 if (ActiveSend + 5 >= Seconds)
						 buttonChat->Enabled = true;

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
	private: System::Void ThreadTimer()
	{
				 while (Connection->getOnline())
				 {
					 str_Analyze = Connection->getLine();
					 if (str_Analyze != "")
					 {
						 array_Stream = str_Analyze->Split(Spliter, StringSplitOptions::None);

						 if (array_Stream[0]->StartsWith("Server accepted connection from IP"))
						 {
							 array_Stream[3] = array_Stream[3]->Replace(".", "");
							 playerJoined = Convert::ToInt32(array_Stream[3]);
							 array_Player[playerJoined] = gcnew Players(array_Stream[1], Convert::ToInt32(array_Stream[3]));
							 Connection->addLog("Server accepted connection from " + array_Stream[1]);
						 }
						 if (array_Stream[0]->StartsWith("<playerjoined player="))
						 {
							 array_Stream = array_Stream[0]->Split(localSplit, StringSplitOptions::None);
							 if (array_Stream->Length < 3 || Buffer != "")
							 {
								 for (int i = 0; i < array_Stream->Length; i++)
									 Buffer += array_Stream[i];
							 }
							 else
							 {
								 if (Buffer != "")
								 {
									 LoadPlayer(Buffer->Split(localSplit, StringSplitOptions::None));
								 }
								 else
								 {
									 LoadPlayer(array_Stream);
								 }
							 }
						 }

						 if (array_Stream[0]->StartsWith("<playerleft player=") ||
							 array_Stream[0]->StartsWith("Server received a disconnect message from ") ||
							 array_Stream[0]->StartsWith("Server sent a disconnect message to ") ||
							 array_Stream[0]->StartsWith("Server terminating client "))
						 {
							 int Lefter = -1;
							 if (array_Stream[0]->StartsWith("Server received a disconnect message from ") ||
								 array_Stream[0]->StartsWith("Server sent a disconnect message to ") ||
								 array_Stream[0]->StartsWith("Server terminating client "))
							 {
								 array_Stream = array_Stream[0]->Split(gcnew array<String^>{"from ", "to ", "client ", "."}, StringSplitOptions::None);
								 Lefter = Convert::ToInt32(array_Stream[1]);
								 Connection->addLog("[RAS] Player: " + array_Player[Lefter]->getName() + "; ID: " + array_Player[Lefter]->getID() + "; Server disconnect");
							 }
							 else
							 {
								 array_Stream = array_Stream[0]->Split(localSplit, StringSplitOptions::None);
								 Lefter = Players::FindIndex(array_Player, array_Stream[3]);
							 }
							 if (Lefter <= -1)
							 {
								 try
								 {
									 Connection->addLog("[RAS] Player: " + array_Stream[1] + "; ID: " + array_Stream[3] + "; Unload");
								 }
								 catch (Exception^ ex)
								 {
									 Connection->addLog("[RAS] Player Unload + Exception into Stream: " + array_Stream->ToString());
								 }
							 }
							 else
							 {
								 Connection->addLog("[RAS] Player: " + array_Player[Lefter]->getName() + "; ID: " + array_Player[Lefter]->getID() + "; Correct Left");
								 delComboBox(array_Player[Lefter]->getName());
								 delComboBoxRank(array_Player[Lefter]->getName());
								 array_Player[Lefter]->Left();
							 }

						 }
						 if (array_Stream[0]->StartsWith("<chat player="))
						 {
							 //Ignore
						 }
						 if (array_Stream[0]->StartsWith("<roundstart gamemode="))
						 {
							 array_Stream = array_Stream[0]->Split(localSplit, StringSplitOptions::None);

							 int IndexWinner = Players::WinnerIndex(array_Player);
							 if (IndexWinner != -1)
								 array_Player[IndexWinner]->Iwin();

							 Players::Weloser(array_Player);
							 Players::SaveAll(array_Player);

							 array_match[0] = array_Stream[1];
							 array_match[1] = array_Stream[3];
							 array_match[2] = array_Stream[5];
							 array_match[3] = array_Stream[7];
							 array_match[4] = array_Stream[9];
							 array_match[5] = array_Stream[11];
							 array_match[6] = array_Stream[13]; //variable index

							 Players::cleanAll(array_Player);
							 Connection->addLog("[RAS] Match started");
							 Connection->addLog("");
						 }
						 if (StartRank)
						 {
							 if (array_Stream[0]->StartsWith("<playerkilled player="))
							 {
								 array_Stream = array_Stream[0]->Split(localSplit, StringSplitOptions::None);

								 int playerKiller, playerKilled;

								 playerKilled = Players::FindIndex(array_Player, array_Stream[3]);
								 playerKiller = Players::FindIndex(array_Player, array_Stream[13]);

								 if (playerKilled == -1 || playerKiller == -1)
								 {
									 try
									 {
										 Connection->addLog("[NRS] player not found! Killed= " + array_Stream[3] + " ; Killer= " + array_Stream[13] + " ;");
									 }
									 catch (Exception^ ex)
									 {
										 Connection->addLog("[NRS] Player Killer error + Exception into Stream: " + array_Stream->ToString());
									 }
								 }
								 else
								 {
									 if (playerKiller == playerKilled)
									 {
										 array_Player[playerKilled]->Ikillme();
										 if (EnabledMessage)
										 {
											 Connection->SamChat(str_SuicideMessage);
										 }
									 }
									 else
									 {
										 if (EnabledMessage)
										 {
											 Connection->SamChat(str_KillMessage);
										 }
										 array_Player[playerKiller]->Ikill(array_Stream[9]);
										 array_Player[playerKilled]->Idead();
									 }
								 }
							 }
						 }
					 }
				 }
	}

	private: System::Void thisMatchToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
				 try
				 {
					 form_SupportBan = gcnew SupportForm(array_Player, 0, 0, 0, Convert::ToInt32(array_match[1]));
					 form_SupportBan->ShowDialog();
					 Connection->sendData("gamKickByIndex(" + form_SupportBan->getIndexBan() + ")");
				 }
				 catch (Exception^ NotLoadMatch)
				 {
					 textBoxStatus->Text = "This match is NOT LOADED";
				 }

	}
	private: System::Void minutesToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
				 form_SupportBan = gcnew SupportForm(array_Player, 0, 0, 0, 30);
				 form_SupportBan->ShowDialog();
				 Connection->sendData("gamKickByIndex(" + form_SupportBan->getIndexBan() + ")");

	}
	private: System::Void minutesToolStripMenuItem1_Click(System::Object^  sender, System::EventArgs^  e) {
				 form_SupportBan = gcnew SupportForm(array_Player, 0, 0, 2, 0);
				 form_SupportBan->ShowDialog();
				 Connection->sendData("gamKickByIndex(" + form_SupportBan->getIndexBan() + ")");

	}
	private: System::Void dayToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
				 form_SupportBan = gcnew SupportForm(array_Player, 0, 1, 0, 0);
				 form_SupportBan->ShowDialog();
				 Connection->sendData("gamKickByIndex(" + form_SupportBan->getIndexBan() + ")");

	}
	private: System::Void daysToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
				 form_SupportBan = gcnew SupportForm(array_Player, 0, 7, 0, 0);
				 form_SupportBan->ShowDialog();
				 Connection->sendData("gamKickByIndex(" + form_SupportBan->getIndexBan() + ")");

	}
	private: System::Void mouthToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
				 form_SupportBan = gcnew SupportForm(array_Player, 1, 0, 0, 0);
				 form_SupportBan->ShowDialog();
				 Connection->sendData("gamKickByIndex(" + form_SupportBan->getIndexBan() + ")");
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
					 Connection->addLog("[RAS] Service unavailable: MatchDetails");
				 }
	}
	private: System::Void recentChatToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
				 MessageBox::Show("Service unavailable");
	}
	private: System::Void buttonLocal_Click(System::Object^  sender, System::EventArgs^  e) {
				 form_MyDedicated = gcnew MyDedicated(MyDedicatedPath);
				 form_MyDedicated->ShowDialog();
				 if (!form_MyDedicated->IsExited())
				 {
					 Connection = gcnew Rcon("127.0.0.1", form_MyDedicated->getPort(), form_MyDedicated->getPassword());
					 Connection->connectRcon();
					 StartTimer = gcnew ThreadStart(this, &MainForm::ThreadTimer);
					 Timer = gcnew Thread(StartTimer);
					 Timer->Start();
					 Thread::Sleep(1000);
					 if (!Connection->getOnline())
					 {
						 MessageBox::Show("Generic: Error connecting from Rcon.", "ERROR 02", MessageBoxButtons::OK, MessageBoxIcon::Error);
						 textBoxStatus->Text = Connection->getStatus();
					 }
					 else
					 {
						 MessageBox::Show("Connection is started.", "Initialize", MessageBoxButtons::OK, MessageBoxIcon::Information);

						 textPassword->Text = "#PASSWORD#";
						 textBoxStatus->Text = Connection->getStatus();

						 Connection->sendData("chatSay(\"Log: Some Admin has started a GUI MyAdmin by Nobel3D\")");
						 buttonUsing(true);
					 }
				 }
	}
	private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) { //Ranked
				 StartRank = true;
				 buttonRanked->Enabled = false;
				 comboBoxPlayerRank->Enabled = true;
				 Connection->sendData("chatSay(\"[NRS] MyRanked by Nobel3D is started!\")");
				 dbSam = gcnew Database("localhost", "27000", "serioussamhdplayer", "root", "121314", true);
				 Players::dbUsed = dbSam;
				 Connection->sendData("gamRestartServer()");
	}
	private: System::Void buttonRcon_Click(System::Object^  sender, System::EventArgs^  e) {
				 Connection->sendData(textBoxRcon->Text);
				 textBoxRcon->Clear();
	}
	private: System::Void comboBoxPlayerRank_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
				 MessageBox::Show("Kills: " + array_Player[comboBoxPlayerRank->SelectedIndex]->getKill() +
					 " Dead: " + array_Player[comboBoxPlayerRank->SelectedIndex]->getDead() +
					 " Score: " + array_Player[comboBoxPlayerRank->SelectedIndex]->getPoint(),
					 "Score", MessageBoxButtons::OK, MessageBoxIcon::Information);
	}
	private: System::Void buttonCredits_Click(System::Object^  sender, System::EventArgs^  e) {
				 Credits^ ShowCredits = gcnew Credits();
				 ShowCredits->ShowDialog();
	}
	private: System::Void killMessageToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
				 SupportForm^ KillMessage = gcnew SupportForm(Connection);
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
};
}

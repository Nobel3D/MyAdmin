#pragma once

#include "..\stdafx.h"

namespace MyAdmin {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public ref class MyDedicated : public System::Windows::Forms::Form
	{
	public:

		int getPort() { return PortValue; }
		String^ getPassword() { return Password; }
		static String^ getDedicatedPath() { return Exe; }
		String^ getName() { return Name; }
		bool IsExited(){ return exit == Windows::Forms::DialogResult::Cancel; } //Has it been canceled (true = do nothing; false = start server)
		String^ getArgs(){ return Args; }
		String^ getIP(){ return stringIP; }

		/*Change status*/
		System::Void changeClick(Windows::Forms::ToolStripMenuItem^ CLICK)
		{
			if (CLICK->Checked == false)
				CLICK->Checked = true;
			else
				CLICK->Checked = false;
		}
		/*Load levels on the combobox*/
		System::Void setLevels(Windows::Forms::ComboBox^ cmbLevel, int GameMode)
		{
			if (GameMode == 0)
			{
				cmbLevel->Items->Clear();
				cmbLevel->Items->Add("Palenque - Sierra de Chiapas");
				cmbLevel->Items->Add("Palenque - Valley of the Jaguar");
				cmbLevel->Items->Add("Teotihuacan - The City of the Gods");
				cmbLevel->Items->Add("Teotihuacan - Serpent Yards");
				cmbLevel->Items->Add("Teotihuacan - The Pit");
				cmbLevel->Items->Add("Ziggurat");
				cmbLevel->Items->Add("Persepolis - The Elephant Atrium");
				cmbLevel->Items->Add("Persepolis - Courtyards of Gilgamesh");
				cmbLevel->Items->Add("Tower Of Babel");
				cmbLevel->Items->Add("The Citadel");
				cmbLevel->Items->Add("Land of the Damned");
				cmbLevel->Items->Add("The Grand Cathedral");
				cmbLevel->Items->Add("Palenque Demo");
				cmbLevel->Items->Add("TFE DLC: Hatshepsut");
				cmbLevel->Items->Add("TFE DLC: Sand Canyon");
				cmbLevel->Items->Add("TFE DLC: Tomb of Ramses");
				cmbLevel->Items->Add("TFE DLC: Valley of the Kings");
				cmbLevel->Items->Add("TFE DLC: Moon Mountains");
				cmbLevel->Items->Add("TFE DLC: Oasis");
				cmbLevel->Items->Add("TFE DLC: Dunes");
				cmbLevel->Items->Add("TFE DLC: Suburbs");
				cmbLevel->Items->Add("TFE DLC: Sewers");
				cmbLevel->Items->Add("TFE DLC: Metropolis");
				cmbLevel->Items->Add("TFE DLC: Alley of the Sphinxes");
				cmbLevel->Items->Add("TFE DLC: Karnak");
				cmbLevel->Items->Add("TFE DLC: Luxor");
				cmbLevel->Items->Add("TFE DLC: Sacred Yards");
				cmbLevel->Items->Add("TFE DLC: The Great Pryamid");
				cmbLevel->Items->Add("TFE DLC: Karnak Demo");
				cmbLevel->Items->Add("Other...");
				cmbLevel->SelectedIndex = 0;
			}
			if (GameMode == 1)
			{
				cmbLevel->Items->Clear();
				cmbLevel->Items->Add("Brkeen Chevap");
				cmbLevel->Items->Add("Fortress");
				cmbLevel->Items->Add("Hole");
				cmbLevel->Items->Add("Jump Over");
				cmbLevel->Items->Add("Medieval Rage");
				cmbLevel->Items->Add("Royal Purgatory");
				cmbLevel->Items->Add("Sun Palace");
				cmbLevel->Items->Add("The Lost Tomb");
				cmbLevel->Items->Add("We Got Skulls'n'Bones Too");
				cmbLevel->Items->Add("Yodeller");
				cmbLevel->Items->Add("TFE DLC: Desert Temple");
				cmbLevel->Items->Add("TFE DLC: Flood");
				cmbLevel->Items->Add("TFE DLC: Gvide");
				cmbLevel->Items->Add("TFE DLC: Hoodlums Backyard");
				cmbLevel->Items->Add("TFE DLC: Horus Web");
				cmbLevel->Items->Add("TFE DLC: Little Trouble");
				cmbLevel->Items->Add("TFE DLC: Simply One");
				cmbLevel->Items->Add("Other...");
				cmbLevel->SelectedIndex = 0;
			}
			if (GameMode == 2)
			{
				cmbLevel->Items->Clear();
				cmbLevel->Items->Add("Ashes To Ashes");
				cmbLevel->Items->Add("Little Trouble");
				cmbLevel->Items->Add("Flagrante");
				cmbLevel->Items->Add("Fort Wars");
				cmbLevel->Items->Add("Other...");
				cmbLevel->SelectedIndex = 0;
			}
			if (GameMode == 3)
			{
				cmbLevel->Items->Clear();
				cmbLevel->Items->Add("Bear City");
				cmbLevel->Items->Add("Bend On Sand");
				cmbLevel->Items->Add("Death From Above");
				cmbLevel->Items->Add("Deep Hole");
				cmbLevel->Items->Add("Green Field");
				cmbLevel->Items->Add("Icelander");
				cmbLevel->Items->Add("Kleer Base");
				cmbLevel->Items->Add("Other...");
				cmbLevel->SelectedIndex = 0;
			}
		}
		/*Get path of the level*/
		String^ getLevels(int Index)
		{
			String^ Level;

			if (Index == 0)
				Level = "Content/SeriousSamHD/Levels/01_SouthAmerica/1_01_Palenque.wld";
			if (Index == 1)
				Level = "Content/SeriousSamHD/Levels/01_SouthAmerica/1_02_Palenque.wld";
			if (Index == 2)
				Level = "Content/SeriousSamHD/Levels/01_SouthAmerica/1_03_Teotihuacan.wld";
			if (Index == 3)
				Level = "Content/SeriousSamHD/Levels/01_SouthAmerica/1_04_Teotihuacan.wld";
			if (Index == 4)
				Level = "Content/SeriousSamHD/Levels/01_SouthAmerica/1_05_Teotihuacan.wld";
			if (Index == 5)
				Level = "Content/SeriousSamHD/Levels/02_Persia/2_01_Ziggurrat.wld";
			if (Index == 6)
				Level = "Content/SeriousSamHD/Levels/02_Persia/2_02_Persepolis.wld";
			if (Index == 7)
				Level = "Content/SeriousSamHD/Levels/02_Persia/2_03_Persepolis.wld";
			if (Index == 8)
				Level = "Content/SeriousSamHD/Levels/02_Persia/2_04_TowerOfBabylon.wld";
			if (Index == 9)
				Level = "Content/SeriousSamHD/Levels/03_Medieval/3_01_GothicCastle.wld";
			if (Index == 10)
				Level = "Content/SeriousSamHD/Levels/03_Medieval/3_02_LandOfDamned.wld";
			if (Index == 11)
				Level = "Content/SeriousSamHD/Levels/03_Medieval/3_03_CorridorOfDeath.wld";
			if (Index == 12)
				Level = "Content/SeriousSamHD/Levels/Z1_DemoPalenque/PalenqueDemo.wld";
			if (Index == 13)
				Level = "Content/SeriousSamHD/Levels/00_Egypt/0_01_Hatshepsut.wld";
			if (Index == 14)
				Level = "Content/SeriousSamHD/Levels/00_Egypt/0_02_SandCanyon.wld";
			if (Index == 15)
				Level = "Content/SeriousSamHD/Levels/00_Egypt/0_03_TombOfRamses.wld";
			if (Index == 16)
				Level = "Content/SeriousSamHD/Levels/00_Egypt/0_04_ValleyOfTheKings.wld";
			if (Index == 17)
				Level = "Content/SeriousSamHD/Levels/00_Egypt/0_05_MoonMountains.wld";
			if (Index == 18)
				Level = "Content/SeriousSamHD/Levels/00_Egypt/0_06_Oasis.wld";
			if (Index == 19)
				Level = "Content/SeriousSamHD/Levels/00_Egypt/0_07_Dunes.wld";
			if (Index == 20)
				Level = "Content/SeriousSamHD/Levels/00_Egypt/0_08_Suburbs.wld";
			if (Index == 21)
				Level = "Content/SeriousSamHD/Levels/00_Egypt/0_09_Sewers.wld";
			if (Index == 22)
				Level = "Content/SeriousSamHD/Levels/00_Egypt/0_10_Metropolis.wld";
			if (Index == 23)
				Level = "Content/SeriousSamHD/Levels/00_Egypt/0_11_AlleyOfSphinxes.wld";
			if (Index == 24)
				Level = "Content/SeriousSamHD/Levels/00_Egypt/0_12_Karnak.wld";
			if (Index == 25)
				Level = "Content/SeriousSamHD/Levels/00_Egypt/0_13_Luxor.wld";
			if (Index == 26)
				Level = "Content/SeriousSamHD/Levels/00_Egypt/0_14_SacredYards.wld";
			if (Index == 27)
				Level = "Content/SeriousSamHD/Levels/00_Egypt/0_15_TheGreatPyramid.wld";
			if (Index == 28)
				Level = "Content/SeriousSamHD/Levels/Z0_DemoKarnak/KarnakDemo.wld";
			if (Index == 29)
				Level = "";
			if (Index == 30)
				Level = "Content/SeriousSamHD/Levels/Z5_Other/BrkeenChevap.wld";
			if (Index == 31)
				Level = "Content/SeriousSamHD/Levels/Z5_Other/Fortress.wld";
			if (Index == 32)
				Level = "Content/SeriousSamHD/Levels/Z5_Other/Hole.wld";
			if (Index == 33)
				Level = "Content/SeriousSamHD/Levels/Z5_Other/JumpOver.wld";
			if (Index == 34)
				Level = "Content/SeriousSamHD/Levels/Z5_Other/MedievalRage.wld";
			if (Index == 35)
				Level = "Content/SeriousSamHD/Levels/Z5_Other/RoyalPurgatory.wld";
			if (Index == 36)
				Level = "Content/SeriousSamHD/Levels/Z5_Other/SunPalace.wld";
			if (Index == 37)
				Level = "Content/SeriousSamHD/Levels/Z5_Other/TheLostTomb.wld";
			if (Index == 38)
				Level = "Content/SeriousSamHD/Levels/Z5_Other/WeGotSkullsNBonesToo.wld";
			if (Index == 39)
				Level = "Content/SeriousSamHD/Levels/Z5_Other/Yodeller.wld";
			if (Index == 40)
				Level = "Content/SeriousSamHD/Levels/Z3_Other/DesertTemple.wld";
			if (Index == 41)
				Level = "Content/SeriousSamHD/Levels/Z3_Other/Flood.wld";
			if (Index == 42)
				Level = "Content/SeriousSamHD/Levels/Z3_Other/Gvide.wld";
			if (Index == 43)
				Level = "Content/SeriousSamHD/Levels/Z3_Other/HoodlumsBackyard.wld";
			if (Index == 44)
				Level = "Content/SeriousSamHD/Levels/Z3_Other/Horus_Web.wld";
			if (Index == 45)
				Level = "Content/SeriousSamHD/Levels/Z3_Other/LittleTrouble.wld";
			if (Index == 46)
				Level = "Content/SeriousSamHD/Levels/Z3_Other/SimplyOne.wld";
			if (Index == 47)
				Level = "Content/SeriousSamHD/Levels/Z5_Other/AshesToAshes.wld";
			if (Index == 48)
				Level = "Content/SeriousSamHD/Levels/Z5_Other/CTF_LittleTrouble.wld";
			if (Index == 49)
				Level = "Content/SeriousSamHD/Levels/Z5_Other/Flagrante.wld";
			if (Index == 50)
				Level = "Content/SeriousSamHD/Levels/Z5_Other/FortWars.wld";
			if (Index == 51)
				Level = "Content/SeriousSamHD/Levels/Z5_Other/BearCity.wld";
			if (Index == 52)
				Level = "Content/SeriousSamHD/Levels/Z5_Other/SV_BendOnSand.wld";
			if (Index == 53)
				Level = "Content/SeriousSamHD/Levels/Z5_Other/SV_DeathFromAbove.wld";
			if (Index == 54)
				Level = "Content/SeriousSamHD/Levels/Z5_Other/SV_DeepHole.wld";
			if (Index == 55)
				Level = "Content/SeriousSamHD/Levels/Z5_Other/SV_GreenField.wld";
			if (Index == 56)
				Level = "Content/SeriousSamHD/Levels/Z5_Other/SV_Icelander.wld";
			if (Index == 57)
				Level = "Content/SeriousSamHD/Levels/Z5_Other/SV_KleerBase.wld";
			return Level;

		}

		System::Void timeScript()
		{
			if (checkBox1->Checked)
			{
				String^ PathScript = Exe->Replace("Bin\\SamHD_TSE_DedicatedServer.exe", "Content\\SeriousSamHD_TSE\\SGUIHD.lua");
					IO::StreamWriter^ LuaScript = gcnew IO::StreamWriter(PathScript, false);
					LuaScript->Write("Wait(Delay(60));" + "\n" +
						"globals.interChat = function()" + "\n" +
						"    chatSay(\"" + textBoxScript->Text + "\");" + "\n" +
						"    Wait(Delay(" + numScript->Value * 60 + "));" + "\n" +
						"    globals.interChat();" + "\n"
						"end" + "\n"
						"globals.interChat();" + "\n" + "\n");
					LuaScript->Close();
				
				Args += " +exec \"Content/SeriousSamHD_TSE/SGUIHD.lua\"";
			}
		}
		/*constructor of the MyDedicated form*/
		MyDedicated(String^ SamDirectory, bool localHost)
		{
			InitializeComponent();
			comboBoxMode->SelectedIndex = 0;
			comboBoxDifficult->SelectedIndex = 2;
			setLevels(comboBoxLevel, 1);
			textBoxStatus->Text = "Ready!";
			if (SamDirectory != "")
				Exe = SamDirectory;
			else
				Exe = "SamHD_TSE_DedicatedServer.exe";
			if (!localHost)
			{
				label16->Visible = true;
				textBoxIP->Visible = true;
				remoteServer = true;
			}
		}

	protected:
		~MyDedicated()
		{
			delete components;
		}

	private: static bool Modder;
	private: static int CountServer = 1;
	private: int PortValue;
	private: String^ Password;
	private: String^ Name;
	private: bool remoteServer;
	private: static String^ Exe;
	private: String^ Args;
	private: String^ stringIP;
	private: Windows::Forms::DialogResult exit;

#pragma region Form Pointer
	private: System::Windows::Forms::Label^  label12;
	private: System::Windows::Forms::Label^  label11;
	private: System::Windows::Forms::NumericUpDown^  numExtraXplayer;
	private: System::Windows::Forms::NumericUpDown^  numExtra;
	private: System::Windows::Forms::ComboBox^  comboBoxDifficult;
	private: System::Windows::Forms::Label^  label10;
	private: System::Windows::Forms::Label^  label9;
	private: System::Windows::Forms::NumericUpDown^  numFrag;
	private: System::Windows::Forms::NumericUpDown^  numTime;
	private: System::Windows::Forms::GroupBox^  groupBox1;
	private: System::Windows::Forms::Label^  label14;
	private: System::Windows::Forms::Label^  label13;
	private: System::Windows::Forms::NumericUpDown^  numBPS;
	private: System::Windows::Forms::NumericUpDown^  numFPS;
	private: System::Windows::Forms::Label^  label8;
	private: System::Windows::Forms::Label^  label7;
	private: System::Windows::Forms::NumericUpDown^  numPlayerMax;
	private: System::Windows::Forms::NumericUpDown^  numPlayerMin;
	private: System::Windows::Forms::Label^  label6;
	private: System::Windows::Forms::TextBox^  textBoxLevel;
	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::ComboBox^  comboBoxLevel;
	private: System::Windows::Forms::CheckBox^  checkBoxShow;
	private: System::Windows::Forms::TextBox^  textBoxPassword;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::TextBox^  textBoxPort;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::ComboBox^  comboBoxMode;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::TextBox^  textBoxName;
	private: System::Windows::Forms::MenuStrip^  menuStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^  matchOptionsToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  toolStripMenuItem1;
	private: System::Windows::Forms::ToolStripMenuItem^  allowHealthToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  allowArmorToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  heaToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  armorStaysToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  ammoStaysToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  weaponsStayToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  gameOptionsToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  disableVotingToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  clientsMayPauseToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  spawnInvulnerabilityToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  respawnInPlaceToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  coopOptionsToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  extraEnemiesToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  friendlyFireToolStripMenuItem;
	private: System::Windows::Forms::Button^  buttonExit;
	private: System::Windows::Forms::Button^  buttonUpdate;
	private: System::Windows::Forms::Button^  buttonCreate;
	private: System::Windows::Forms::LinkLabel^  linkLabel1;
	private: System::Windows::Forms::TextBox^  textBoxStatus;
	private: System::Windows::Forms::OpenFileDialog^  openFile;
	private: System::Windows::Forms::Button^  buttonSave;
	private: System::Windows::Forms::Button^  buttonLoad;
	private: System::Windows::Forms::OpenFileDialog^  openConfig;
private: System::Windows::Forms::Label^  label15;
private: System::Windows::Forms::TextBox^  textBoxScript;
private: System::Windows::Forms::CheckBox^  checkBox1;
private: System::Windows::Forms::NumericUpDown^  numScript;
private: System::Windows::Forms::Label^  label16;
private: System::Windows::Forms::TextBox^  textBoxIP;





	private: System::ComponentModel::Container ^components;
#pragma endregion
#pragma region Windows Form Designer generated code
			 void InitializeComponent(void)
			 {
				 System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(MyDedicated::typeid));
				 this->label12 = (gcnew System::Windows::Forms::Label());
				 this->label11 = (gcnew System::Windows::Forms::Label());
				 this->numExtraXplayer = (gcnew System::Windows::Forms::NumericUpDown());
				 this->numExtra = (gcnew System::Windows::Forms::NumericUpDown());
				 this->comboBoxDifficult = (gcnew System::Windows::Forms::ComboBox());
				 this->label10 = (gcnew System::Windows::Forms::Label());
				 this->label9 = (gcnew System::Windows::Forms::Label());
				 this->numFrag = (gcnew System::Windows::Forms::NumericUpDown());
				 this->numTime = (gcnew System::Windows::Forms::NumericUpDown());
				 this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
				 this->label14 = (gcnew System::Windows::Forms::Label());
				 this->label13 = (gcnew System::Windows::Forms::Label());
				 this->numBPS = (gcnew System::Windows::Forms::NumericUpDown());
				 this->numFPS = (gcnew System::Windows::Forms::NumericUpDown());
				 this->label8 = (gcnew System::Windows::Forms::Label());
				 this->label7 = (gcnew System::Windows::Forms::Label());
				 this->numPlayerMax = (gcnew System::Windows::Forms::NumericUpDown());
				 this->numPlayerMin = (gcnew System::Windows::Forms::NumericUpDown());
				 this->label6 = (gcnew System::Windows::Forms::Label());
				 this->textBoxLevel = (gcnew System::Windows::Forms::TextBox());
				 this->label5 = (gcnew System::Windows::Forms::Label());
				 this->comboBoxLevel = (gcnew System::Windows::Forms::ComboBox());
				 this->checkBoxShow = (gcnew System::Windows::Forms::CheckBox());
				 this->textBoxPassword = (gcnew System::Windows::Forms::TextBox());
				 this->label4 = (gcnew System::Windows::Forms::Label());
				 this->textBoxPort = (gcnew System::Windows::Forms::TextBox());
				 this->label3 = (gcnew System::Windows::Forms::Label());
				 this->comboBoxMode = (gcnew System::Windows::Forms::ComboBox());
				 this->label2 = (gcnew System::Windows::Forms::Label());
				 this->label1 = (gcnew System::Windows::Forms::Label());
				 this->textBoxName = (gcnew System::Windows::Forms::TextBox());
				 this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
				 this->matchOptionsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->toolStripMenuItem1 = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->allowHealthToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->allowArmorToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->heaToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->armorStaysToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->ammoStaysToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->weaponsStayToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->gameOptionsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->disableVotingToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->clientsMayPauseToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->spawnInvulnerabilityToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->respawnInPlaceToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->coopOptionsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->extraEnemiesToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->friendlyFireToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->buttonExit = (gcnew System::Windows::Forms::Button());
				 this->buttonUpdate = (gcnew System::Windows::Forms::Button());
				 this->buttonCreate = (gcnew System::Windows::Forms::Button());
				 this->linkLabel1 = (gcnew System::Windows::Forms::LinkLabel());
				 this->textBoxStatus = (gcnew System::Windows::Forms::TextBox());
				 this->openFile = (gcnew System::Windows::Forms::OpenFileDialog());
				 this->buttonSave = (gcnew System::Windows::Forms::Button());
				 this->buttonLoad = (gcnew System::Windows::Forms::Button());
				 this->openConfig = (gcnew System::Windows::Forms::OpenFileDialog());
				 this->label15 = (gcnew System::Windows::Forms::Label());
				 this->textBoxScript = (gcnew System::Windows::Forms::TextBox());
				 this->checkBox1 = (gcnew System::Windows::Forms::CheckBox());
				 this->numScript = (gcnew System::Windows::Forms::NumericUpDown());
				 this->textBoxIP = (gcnew System::Windows::Forms::TextBox());
				 this->label16 = (gcnew System::Windows::Forms::Label());
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numExtraXplayer))->BeginInit();
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numExtra))->BeginInit();
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numFrag))->BeginInit();
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numTime))->BeginInit();
				 this->groupBox1->SuspendLayout();
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numBPS))->BeginInit();
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numFPS))->BeginInit();
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numPlayerMax))->BeginInit();
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numPlayerMin))->BeginInit();
				 this->menuStrip1->SuspendLayout();
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numScript))->BeginInit();
				 this->SuspendLayout();
				 // 
				 // label12
				 // 
				 this->label12->AutoSize = true;
				 this->label12->Location = System::Drawing::Point(394, 354);
				 this->label12->Name = L"label12";
				 this->label12->Size = System::Drawing::Size(106, 26);
				 this->label12->TabIndex = 24;
				 this->label12->Text = L"Extra enemy strenght\n(X Player)";
				 // 
				 // label11
				 // 
				 this->label11->AutoSize = true;
				 this->label11->Location = System::Drawing::Point(394, 314);
				 this->label11->Name = L"label11";
				 this->label11->Size = System::Drawing::Size(106, 13);
				 this->label11->TabIndex = 23;
				 this->label11->Text = L"Extra enemy strenght";
				 // 
				 // numExtraXplayer
				 // 
				 this->numExtraXplayer->Location = System::Drawing::Point(506, 354);
				 this->numExtraXplayer->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 400, 0, 0, 0 });
				 this->numExtraXplayer->Name = L"numExtraXplayer";
				 this->numExtraXplayer->Size = System::Drawing::Size(52, 20);
				 this->numExtraXplayer->TabIndex = 22;
				 // 
				 // numExtra
				 // 
				 this->numExtra->Location = System::Drawing::Point(506, 312);
				 this->numExtra->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 400, 0, 0, 0 });
				 this->numExtra->Name = L"numExtra";
				 this->numExtra->Size = System::Drawing::Size(52, 20);
				 this->numExtra->TabIndex = 21;
				 // 
				 // comboBoxDifficult
				 // 
				 this->comboBoxDifficult->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
				 this->comboBoxDifficult->FormattingEnabled = true;
				 this->comboBoxDifficult->Items->AddRange(gcnew cli::array< System::Object^  >(6) {
					 L"Tourist", L"Easy", L"Normal", L"Hard",
						 L"Serious", L"Mental"
				 });
				 this->comboBoxDifficult->Location = System::Drawing::Point(233, 316);
				 this->comboBoxDifficult->Name = L"comboBoxDifficult";
				 this->comboBoxDifficult->Size = System::Drawing::Size(128, 21);
				 this->comboBoxDifficult->TabIndex = 20;
				 // 
				 // label10
				 // 
				 this->label10->AutoSize = true;
				 this->label10->Location = System::Drawing::Point(28, 354);
				 this->label10->Name = L"label10";
				 this->label10->RightToLeft = System::Windows::Forms::RightToLeft::Yes;
				 this->label10->Size = System::Drawing::Size(52, 13);
				 this->label10->TabIndex = 18;
				 this->label10->Text = L"Frag Limit";
				 // 
				 // label9
				 // 
				 this->label9->AutoSize = true;
				 this->label9->Location = System::Drawing::Point(25, 319);
				 this->label9->Name = L"label9";
				 this->label9->Size = System::Drawing::Size(54, 13);
				 this->label9->TabIndex = 17;
				 this->label9->Text = L"Time Limit";
				 // 
				 // numFrag
				 // 
				 this->numFrag->Location = System::Drawing::Point(94, 356);
				 this->numFrag->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
				 this->numFrag->Name = L"numFrag";
				 this->numFrag->Size = System::Drawing::Size(52, 20);
				 this->numFrag->TabIndex = 16;
				 this->numFrag->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 10, 0, 0, 0 });
				 // 
				 // numTime
				 // 
				 this->numTime->Location = System::Drawing::Point(94, 317);
				 this->numTime->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 120, 0, 0, 0 });
				 this->numTime->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
				 this->numTime->Name = L"numTime";
				 this->numTime->Size = System::Drawing::Size(52, 20);
				 this->numTime->TabIndex = 15;
				 this->numTime->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 20, 0, 0, 0 });
				 // 
				 // groupBox1
				 // 
				 this->groupBox1->Controls->Add(this->label16);
				 this->groupBox1->Controls->Add(this->textBoxIP);
				 this->groupBox1->Controls->Add(this->label14);
				 this->groupBox1->Controls->Add(this->label13);
				 this->groupBox1->Controls->Add(this->numBPS);
				 this->groupBox1->Controls->Add(this->numFPS);
				 this->groupBox1->Controls->Add(this->label8);
				 this->groupBox1->Controls->Add(this->label7);
				 this->groupBox1->Controls->Add(this->numPlayerMax);
				 this->groupBox1->Controls->Add(this->numPlayerMin);
				 this->groupBox1->Controls->Add(this->label6);
				 this->groupBox1->Controls->Add(this->textBoxLevel);
				 this->groupBox1->Controls->Add(this->label5);
				 this->groupBox1->Controls->Add(this->comboBoxLevel);
				 this->groupBox1->Controls->Add(this->checkBoxShow);
				 this->groupBox1->Controls->Add(this->textBoxPassword);
				 this->groupBox1->Controls->Add(this->label4);
				 this->groupBox1->Controls->Add(this->textBoxPort);
				 this->groupBox1->Controls->Add(this->label3);
				 this->groupBox1->Controls->Add(this->comboBoxMode);
				 this->groupBox1->Controls->Add(this->label2);
				 this->groupBox1->Controls->Add(this->label1);
				 this->groupBox1->Controls->Add(this->textBoxName);
				 this->groupBox1->Location = System::Drawing::Point(12, 27);
				 this->groupBox1->Name = L"groupBox1";
				 this->groupBox1->Size = System::Drawing::Size(565, 265);
				 this->groupBox1->TabIndex = 14;
				 this->groupBox1->TabStop = false;
				 // 
				 // label14
				 // 
				 this->label14->AutoSize = true;
				 this->label14->Location = System::Drawing::Point(423, 205);
				 this->label14->Name = L"label14";
				 this->label14->Size = System::Drawing::Size(51, 13);
				 this->label14->TabIndex = 23;
				 this->label14->Text = L"Max BPS";
				 // 
				 // label13
				 // 
				 this->label13->AutoSize = true;
				 this->label13->Location = System::Drawing::Point(312, 205);
				 this->label13->Name = L"label13";
				 this->label13->Size = System::Drawing::Size(27, 13);
				 this->label13->TabIndex = 22;
				 this->label13->Text = L"FPS";
				 // 
				 // numBPS
				 // 
				 this->numBPS->Location = System::Drawing::Point(481, 203);
				 this->numBPS->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 15000, 0, 0, 0 });
				 this->numBPS->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 5000, 0, 0, 0 });
				 this->numBPS->Name = L"numBPS";
				 this->numBPS->Size = System::Drawing::Size(65, 20);
				 this->numBPS->TabIndex = 21;
				 this->numBPS->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 11000, 0, 0, 0 });
				 // 
				 // numFPS
				 // 
				 this->numFPS->Location = System::Drawing::Point(345, 203);
				 this->numFPS->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 500, 0, 0, 0 });
				 this->numFPS->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 50, 0, 0, 0 });
				 this->numFPS->Name = L"numFPS";
				 this->numFPS->Size = System::Drawing::Size(65, 20);
				 this->numFPS->TabIndex = 20;
				 this->numFPS->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 200, 0, 0, 0 });
				 // 
				 // label8
				 // 
				 this->label8->AutoSize = true;
				 this->label8->Location = System::Drawing::Point(134, 205);
				 this->label8->Name = L"label8";
				 this->label8->Size = System::Drawing::Size(64, 13);
				 this->label8->TabIndex = 19;
				 this->label8->Text = L"Max Players";
				 // 
				 // label7
				 // 
				 this->label7->AutoSize = true;
				 this->label7->Location = System::Drawing::Point(13, 205);
				 this->label7->Name = L"label7";
				 this->label7->Size = System::Drawing::Size(61, 13);
				 this->label7->TabIndex = 18;
				 this->label7->Text = L"Min Players";
				 // 
				 // numPlayerMax
				 // 
				 this->numPlayerMax->Location = System::Drawing::Point(204, 203);
				 this->numPlayerMax->Name = L"numPlayerMax";
				 this->numPlayerMax->Size = System::Drawing::Size(52, 20);
				 this->numPlayerMax->TabIndex = 17;
				 this->numPlayerMax->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 16, 0, 0, 0 });
				 this->numPlayerMax->ValueChanged += gcnew System::EventHandler(this, &MyDedicated::numPlayerMax_ValueChanged);
				 // 
				 // numPlayerMin
				 // 
				 this->numPlayerMin->Location = System::Drawing::Point(82, 203);
				 this->numPlayerMin->Name = L"numPlayerMin";
				 this->numPlayerMin->Size = System::Drawing::Size(52, 20);
				 this->numPlayerMin->TabIndex = 16;
				 this->numPlayerMin->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 2, 0, 0, 0 });
				 this->numPlayerMin->ValueChanged += gcnew System::EventHandler(this, &MyDedicated::numPlayerMin_ValueChanged);
				 // 
				 // label6
				 // 
				 this->label6->AutoSize = true;
				 this->label6->Location = System::Drawing::Point(286, 154);
				 this->label6->Name = L"label6";
				 this->label6->Size = System::Drawing::Size(42, 13);
				 this->label6->TabIndex = 15;
				 this->label6->Text = L"Other...";
				 // 
				 // textBoxLevel
				 // 
				 this->textBoxLevel->Enabled = false;
				 this->textBoxLevel->Location = System::Drawing::Point(345, 151);
				 this->textBoxLevel->Name = L"textBoxLevel";
				 this->textBoxLevel->Size = System::Drawing::Size(201, 20);
				 this->textBoxLevel->TabIndex = 14;
				 this->textBoxLevel->Text = L"Content/SeriousSamHD/Levels/";
				 // 
				 // label5
				 // 
				 this->label5->AutoSize = true;
				 this->label5->Location = System::Drawing::Point(13, 150);
				 this->label5->Name = L"label5";
				 this->label5->Size = System::Drawing::Size(33, 13);
				 this->label5->TabIndex = 13;
				 this->label5->Text = L"Level";
				 // 
				 // comboBoxLevel
				 // 
				 this->comboBoxLevel->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
				 this->comboBoxLevel->FormattingEnabled = true;
				 this->comboBoxLevel->Location = System::Drawing::Point(82, 150);
				 this->comboBoxLevel->Name = L"comboBoxLevel";
				 this->comboBoxLevel->Size = System::Drawing::Size(174, 21);
				 this->comboBoxLevel->TabIndex = 12;
				 this->comboBoxLevel->SelectedIndexChanged += gcnew System::EventHandler(this, &MyDedicated::comboBoxLevel_SelectedIndexChanged);
				 // 
				 // checkBoxShow
				 // 
				 this->checkBoxShow->AutoSize = true;
				 this->checkBoxShow->Location = System::Drawing::Point(506, 111);
				 this->checkBoxShow->Name = L"checkBoxShow";
				 this->checkBoxShow->Size = System::Drawing::Size(53, 17);
				 this->checkBoxShow->TabIndex = 11;
				 this->checkBoxShow->Text = L"Show";
				 this->checkBoxShow->UseVisualStyleBackColor = true;
				 this->checkBoxShow->CheckedChanged += gcnew System::EventHandler(this, &MyDedicated::checkBoxShow_CheckedChanged);
				 // 
				 // textBoxPassword
				 // 
				 this->textBoxPassword->Location = System::Drawing::Point(345, 109);
				 this->textBoxPassword->Name = L"textBoxPassword";
				 this->textBoxPassword->Size = System::Drawing::Size(155, 20);
				 this->textBoxPassword->TabIndex = 10;
				 this->textBoxPassword->UseSystemPasswordChar = true;
				 // 
				 // label4
				 // 
				 this->label4->AutoSize = true;
				 this->label4->Location = System::Drawing::Point(286, 112);
				 this->label4->Name = L"label4";
				 this->label4->Size = System::Drawing::Size(53, 13);
				 this->label4->TabIndex = 9;
				 this->label4->Text = L"Password";
				 // 
				 // textBoxPort
				 // 
				 this->textBoxPort->Location = System::Drawing::Point(423, 62);
				 this->textBoxPort->Name = L"textBoxPort";
				 this->textBoxPort->Size = System::Drawing::Size(123, 20);
				 this->textBoxPort->TabIndex = 8;
				 this->textBoxPort->Text = L"27015";
				 // 
				 // label3
				 // 
				 this->label3->AutoSize = true;
				 this->label3->Location = System::Drawing::Point(10, 112);
				 this->label3->Name = L"label3";
				 this->label3->Size = System::Drawing::Size(65, 13);
				 this->label3->TabIndex = 7;
				 this->label3->Text = L"Game Mode";
				 // 
				 // comboBoxMode
				 // 
				 this->comboBoxMode->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
				 this->comboBoxMode->FormattingEnabled = true;
				 this->comboBoxMode->Items->AddRange(gcnew cli::array< System::Object^  >(12) {
					 L"Versus: Deathmatch", L"Versus: Instant Kill",
						 L"Versus: Beast Hunt", L"Versus: My Burden", L"Versus: Last Man", L"Team Versus: Deathmatch", L"Team Versus: Beast Hunt", L"Team Versus: Last Team",
						 L"Team Versus: Capture the Flag", L"Cooperative: Classic", L"Cooperative: Coop-op", L"Cooperative: Survival"
				 });
				 this->comboBoxMode->Location = System::Drawing::Point(82, 109);
				 this->comboBoxMode->Name = L"comboBoxMode";
				 this->comboBoxMode->Size = System::Drawing::Size(174, 21);
				 this->comboBoxMode->TabIndex = 6;
				 this->comboBoxMode->SelectedIndexChanged += gcnew System::EventHandler(this, &MyDedicated::comboBoxMode_SelectedIndexChanged);
				 // 
				 // label2
				 // 
				 this->label2->AutoSize = true;
				 this->label2->Location = System::Drawing::Point(357, 65);
				 this->label2->Name = L"label2";
				 this->label2->Size = System::Drawing::Size(60, 13);
				 this->label2->TabIndex = 5;
				 this->label2->Text = L"Server Port";
				 // 
				 // label1
				 // 
				 this->label1->AutoSize = true;
				 this->label1->Location = System::Drawing::Point(7, 65);
				 this->label1->Name = L"label1";
				 this->label1->Size = System::Drawing::Size(69, 13);
				 this->label1->TabIndex = 4;
				 this->label1->Text = L"Server Name";
				 // 
				 // textBoxName
				 // 
				 this->textBoxName->Location = System::Drawing::Point(82, 62);
				 this->textBoxName->Name = L"textBoxName";
				 this->textBoxName->Size = System::Drawing::Size(232, 20);
				 this->textBoxName->TabIndex = 3;
				 this->textBoxName->Text = L"MyServer";
				 // 
				 // menuStrip1
				 // 
				 this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
					 this->matchOptionsToolStripMenuItem,
						 this->gameOptionsToolStripMenuItem, this->coopOptionsToolStripMenuItem
				 });
				 this->menuStrip1->Location = System::Drawing::Point(0, 0);
				 this->menuStrip1->Name = L"menuStrip1";
				 this->menuStrip1->Size = System::Drawing::Size(586, 24);
				 this->menuStrip1->TabIndex = 19;
				 this->menuStrip1->Text = L"menuStrip1";
				 // 
				 // matchOptionsToolStripMenuItem
				 // 
				 this->matchOptionsToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(7) {
					 this->toolStripMenuItem1,
						 this->allowHealthToolStripMenuItem, this->allowArmorToolStripMenuItem, this->heaToolStripMenuItem, this->armorStaysToolStripMenuItem,
						 this->ammoStaysToolStripMenuItem, this->weaponsStayToolStripMenuItem
				 });
				 this->matchOptionsToolStripMenuItem->Name = L"matchOptionsToolStripMenuItem";
				 this->matchOptionsToolStripMenuItem->Size = System::Drawing::Size(98, 20);
				 this->matchOptionsToolStripMenuItem->Text = L"Match Options";
				 // 
				 // toolStripMenuItem1
				 // 
				 this->toolStripMenuItem1->Name = L"toolStripMenuItem1";
				 this->toolStripMenuItem1->Size = System::Drawing::Size(151, 22);
				 this->toolStripMenuItem1->Text = L"Infinite Ammo";
				 this->toolStripMenuItem1->Click += gcnew System::EventHandler(this, &MyDedicated::toolStripMenuItem1_Click);
				 // 
				 // allowHealthToolStripMenuItem
				 // 
				 this->allowHealthToolStripMenuItem->Checked = true;
				 this->allowHealthToolStripMenuItem->CheckState = System::Windows::Forms::CheckState::Checked;
				 this->allowHealthToolStripMenuItem->Name = L"allowHealthToolStripMenuItem";
				 this->allowHealthToolStripMenuItem->Size = System::Drawing::Size(151, 22);
				 this->allowHealthToolStripMenuItem->Text = L"Allow Health";
				 this->allowHealthToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyDedicated::allowHealthToolStripMenuItem_Click);
				 // 
				 // allowArmorToolStripMenuItem
				 // 
				 this->allowArmorToolStripMenuItem->Checked = true;
				 this->allowArmorToolStripMenuItem->CheckState = System::Windows::Forms::CheckState::Checked;
				 this->allowArmorToolStripMenuItem->Name = L"allowArmorToolStripMenuItem";
				 this->allowArmorToolStripMenuItem->Size = System::Drawing::Size(151, 22);
				 this->allowArmorToolStripMenuItem->Text = L"Allow Armor";
				 this->allowArmorToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyDedicated::allowArmorToolStripMenuItem_Click);
				 // 
				 // heaToolStripMenuItem
				 // 
				 this->heaToolStripMenuItem->Checked = true;
				 this->heaToolStripMenuItem->CheckState = System::Windows::Forms::CheckState::Checked;
				 this->heaToolStripMenuItem->Name = L"heaToolStripMenuItem";
				 this->heaToolStripMenuItem->Size = System::Drawing::Size(151, 22);
				 this->heaToolStripMenuItem->Text = L"Health Stays";
				 this->heaToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyDedicated::heaToolStripMenuItem_Click);
				 // 
				 // armorStaysToolStripMenuItem
				 // 
				 this->armorStaysToolStripMenuItem->Checked = true;
				 this->armorStaysToolStripMenuItem->CheckState = System::Windows::Forms::CheckState::Checked;
				 this->armorStaysToolStripMenuItem->Name = L"armorStaysToolStripMenuItem";
				 this->armorStaysToolStripMenuItem->Size = System::Drawing::Size(151, 22);
				 this->armorStaysToolStripMenuItem->Text = L"Armor Stays";
				 this->armorStaysToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyDedicated::armorStaysToolStripMenuItem_Click);
				 // 
				 // ammoStaysToolStripMenuItem
				 // 
				 this->ammoStaysToolStripMenuItem->Checked = true;
				 this->ammoStaysToolStripMenuItem->CheckState = System::Windows::Forms::CheckState::Checked;
				 this->ammoStaysToolStripMenuItem->Name = L"ammoStaysToolStripMenuItem";
				 this->ammoStaysToolStripMenuItem->Size = System::Drawing::Size(151, 22);
				 this->ammoStaysToolStripMenuItem->Text = L"Ammo Stays";
				 this->ammoStaysToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyDedicated::ammoStaysToolStripMenuItem_Click);
				 // 
				 // weaponsStayToolStripMenuItem
				 // 
				 this->weaponsStayToolStripMenuItem->Checked = true;
				 this->weaponsStayToolStripMenuItem->CheckState = System::Windows::Forms::CheckState::Checked;
				 this->weaponsStayToolStripMenuItem->Name = L"weaponsStayToolStripMenuItem";
				 this->weaponsStayToolStripMenuItem->Size = System::Drawing::Size(151, 22);
				 this->weaponsStayToolStripMenuItem->Text = L"Weapons Stay";
				 this->weaponsStayToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyDedicated::weaponsStayToolStripMenuItem_Click);
				 // 
				 // gameOptionsToolStripMenuItem
				 // 
				 this->gameOptionsToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {
					 this->disableVotingToolStripMenuItem,
						 this->clientsMayPauseToolStripMenuItem, this->spawnInvulnerabilityToolStripMenuItem, this->respawnInPlaceToolStripMenuItem
				 });
				 this->gameOptionsToolStripMenuItem->Name = L"gameOptionsToolStripMenuItem";
				 this->gameOptionsToolStripMenuItem->Size = System::Drawing::Size(95, 20);
				 this->gameOptionsToolStripMenuItem->Text = L"Game Options";
				 // 
				 // disableVotingToolStripMenuItem
				 // 
				 this->disableVotingToolStripMenuItem->Name = L"disableVotingToolStripMenuItem";
				 this->disableVotingToolStripMenuItem->Size = System::Drawing::Size(187, 22);
				 this->disableVotingToolStripMenuItem->Text = L"Disable Voting";
				 this->disableVotingToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyDedicated::disableVotingToolStripMenuItem_Click);
				 // 
				 // clientsMayPauseToolStripMenuItem
				 // 
				 this->clientsMayPauseToolStripMenuItem->Name = L"clientsMayPauseToolStripMenuItem";
				 this->clientsMayPauseToolStripMenuItem->Size = System::Drawing::Size(187, 22);
				 this->clientsMayPauseToolStripMenuItem->Text = L"Clients may pause";
				 this->clientsMayPauseToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyDedicated::clientsMayPauseToolStripMenuItem_Click);
				 // 
				 // spawnInvulnerabilityToolStripMenuItem
				 // 
				 this->spawnInvulnerabilityToolStripMenuItem->Checked = true;
				 this->spawnInvulnerabilityToolStripMenuItem->CheckState = System::Windows::Forms::CheckState::Checked;
				 this->spawnInvulnerabilityToolStripMenuItem->Name = L"spawnInvulnerabilityToolStripMenuItem";
				 this->spawnInvulnerabilityToolStripMenuItem->Size = System::Drawing::Size(187, 22);
				 this->spawnInvulnerabilityToolStripMenuItem->Text = L"Spawn Invulnerability";
				 this->spawnInvulnerabilityToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyDedicated::spawnInvulnerabilityToolStripMenuItem_Click);
				 // 
				 // respawnInPlaceToolStripMenuItem
				 // 
				 this->respawnInPlaceToolStripMenuItem->Checked = true;
				 this->respawnInPlaceToolStripMenuItem->CheckState = System::Windows::Forms::CheckState::Checked;
				 this->respawnInPlaceToolStripMenuItem->Name = L"respawnInPlaceToolStripMenuItem";
				 this->respawnInPlaceToolStripMenuItem->Size = System::Drawing::Size(187, 22);
				 this->respawnInPlaceToolStripMenuItem->Text = L"Respawn in place";
				 this->respawnInPlaceToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyDedicated::respawnInPlaceToolStripMenuItem_Click);
				 // 
				 // coopOptionsToolStripMenuItem
				 // 
				 this->coopOptionsToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
					 this->extraEnemiesToolStripMenuItem,
						 this->friendlyFireToolStripMenuItem
				 });
				 this->coopOptionsToolStripMenuItem->Name = L"coopOptionsToolStripMenuItem";
				 this->coopOptionsToolStripMenuItem->Size = System::Drawing::Size(93, 20);
				 this->coopOptionsToolStripMenuItem->Text = L"Coop Options";
				 // 
				 // extraEnemiesToolStripMenuItem
				 // 
				 this->extraEnemiesToolStripMenuItem->Name = L"extraEnemiesToolStripMenuItem";
				 this->extraEnemiesToolStripMenuItem->Size = System::Drawing::Size(146, 22);
				 this->extraEnemiesToolStripMenuItem->Text = L"Extra Enemies";
				 this->extraEnemiesToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyDedicated::extraEnemiesToolStripMenuItem_Click);
				 // 
				 // friendlyFireToolStripMenuItem
				 // 
				 this->friendlyFireToolStripMenuItem->Name = L"friendlyFireToolStripMenuItem";
				 this->friendlyFireToolStripMenuItem->Size = System::Drawing::Size(146, 22);
				 this->friendlyFireToolStripMenuItem->Text = L"Friendly Fire";
				 this->friendlyFireToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyDedicated::friendlyFireToolStripMenuItem_Click);
				 // 
				 // buttonExit
				 // 
				 this->buttonExit->Location = System::Drawing::Point(15, 565);
				 this->buttonExit->Name = L"buttonExit";
				 this->buttonExit->Size = System::Drawing::Size(86, 23);
				 this->buttonExit->TabIndex = 29;
				 this->buttonExit->Text = L"Exit";
				 this->buttonExit->UseVisualStyleBackColor = true;
				 this->buttonExit->Click += gcnew System::EventHandler(this, &MyDedicated::buttonExit_Click);
				 // 
				 // buttonUpdate
				 // 
				 this->buttonUpdate->Location = System::Drawing::Point(475, 565);
				 this->buttonUpdate->Name = L"buttonUpdate";
				 this->buttonUpdate->Size = System::Drawing::Size(86, 23);
				 this->buttonUpdate->TabIndex = 28;
				 this->buttonUpdate->Text = L"Check Update";
				 this->buttonUpdate->UseVisualStyleBackColor = true;
				 this->buttonUpdate->Click += gcnew System::EventHandler(this, &MyDedicated::buttonUpdate_Click);
				 // 
				 // buttonCreate
				 // 
				 this->buttonCreate->Location = System::Drawing::Point(219, 494);
				 this->buttonCreate->Name = L"buttonCreate";
				 this->buttonCreate->Size = System::Drawing::Size(156, 23);
				 this->buttonCreate->TabIndex = 27;
				 this->buttonCreate->Text = L"Create";
				 this->buttonCreate->UseVisualStyleBackColor = true;
				 this->buttonCreate->Click += gcnew System::EventHandler(this, &MyDedicated::buttonCreate_Click);
				 // 
				 // linkLabel1
				 // 
				 this->linkLabel1->AutoSize = true;
				 this->linkLabel1->Location = System::Drawing::Point(149, 575);
				 this->linkLabel1->Name = L"linkLabel1";
				 this->linkLabel1->Size = System::Drawing::Size(294, 13);
				 this->linkLabel1->TabIndex = 26;
				 this->linkLabel1->TabStop = true;
				 this->linkLabel1->Text = L"Serious Sam HD MyDedicated by Luca \"Nobel3D\" Gasperini";
				 this->linkLabel1->LinkClicked += gcnew System::Windows::Forms::LinkLabelLinkClickedEventHandler(this, &MyDedicated::linkLabel1_LinkClicked);
				 // 
				 // textBoxStatus
				 // 
				 this->textBoxStatus->Location = System::Drawing::Point(12, 539);
				 this->textBoxStatus->Name = L"textBoxStatus";
				 this->textBoxStatus->ReadOnly = true;
				 this->textBoxStatus->Size = System::Drawing::Size(565, 20);
				 this->textBoxStatus->TabIndex = 25;
				 // 
				 // openFile
				 // 
				 this->openFile->FileName = L"Give me Serious Sam Dedicated Server";
				 this->openFile->Filter = L"File (*.exe)|*.exe";
				 this->openFile->Title = L"Open Dedicated";
				 // 
				 // buttonSave
				 // 
				 this->buttonSave->Location = System::Drawing::Point(12, 494);
				 this->buttonSave->Name = L"buttonSave";
				 this->buttonSave->Size = System::Drawing::Size(89, 23);
				 this->buttonSave->TabIndex = 30;
				 this->buttonSave->Text = L"Save Config";
				 this->buttonSave->UseVisualStyleBackColor = true;
				 this->buttonSave->Click += gcnew System::EventHandler(this, &MyDedicated::buttonSave_Click);
				 // 
				 // buttonLoad
				 // 
				 this->buttonLoad->Location = System::Drawing::Point(475, 494);
				 this->buttonLoad->Name = L"buttonLoad";
				 this->buttonLoad->Size = System::Drawing::Size(86, 23);
				 this->buttonLoad->TabIndex = 31;
				 this->buttonLoad->Text = L"Load Config";
				 this->buttonLoad->UseVisualStyleBackColor = true;
				 this->buttonLoad->Click += gcnew System::EventHandler(this, &MyDedicated::buttonLoad_Click);
				 // 
				 // openConfig
				 // 
				 this->openConfig->FileName = L"FileName";
				 this->openConfig->Filter = L"File di Configurazione (*.conf)|*.conf";
				 // 
				 // label15
				 // 
				 this->label15->AutoSize = true;
				 this->label15->Location = System::Drawing::Point(239, 384);
				 this->label15->Name = L"label15";
				 this->label15->Size = System::Drawing::Size(112, 13);
				 this->label15->TabIndex = 32;
				 this->label15->Text = L"Timed Message Script";
				 // 
				 // textBoxScript
				 // 
				 this->textBoxScript->Enabled = false;
				 this->textBoxScript->Location = System::Drawing::Point(12, 400);
				 this->textBoxScript->Name = L"textBoxScript";
				 this->textBoxScript->Size = System::Drawing::Size(559, 20);
				 this->textBoxScript->TabIndex = 33;
				 // 
				 // checkBox1
				 // 
				 this->checkBox1->AutoSize = true;
				 this->checkBox1->Location = System::Drawing::Point(319, 443);
				 this->checkBox1->Name = L"checkBox1";
				 this->checkBox1->Size = System::Drawing::Size(56, 17);
				 this->checkBox1->TabIndex = 34;
				 this->checkBox1->Text = L"Active";
				 this->checkBox1->UseVisualStyleBackColor = true;
				 this->checkBox1->CheckedChanged += gcnew System::EventHandler(this, &MyDedicated::checkBox1_CheckedChanged);
				 // 
				 // numScript
				 // 
				 this->numScript->Enabled = false;
				 this->numScript->Location = System::Drawing::Point(219, 442);
				 this->numScript->Name = L"numScript";
				 this->numScript->Size = System::Drawing::Size(72, 20);
				 this->numScript->TabIndex = 35;
				 this->numScript->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 2, 0, 0, 0 });
				 // 
				 // textBoxIP
				 // 
				 this->textBoxIP->Location = System::Drawing::Point(128, 19);
				 this->textBoxIP->Name = L"textBoxIP";
				 this->textBoxIP->Size = System::Drawing::Size(334, 20);
				 this->textBoxIP->TabIndex = 24;
				 this->textBoxIP->Text = L"127.0.0.1";
				 this->textBoxIP->Visible = false;
				 // 
				 // label16
				 // 
				 this->label16->AutoSize = true;
				 this->label16->Location = System::Drawing::Point(41, 22);
				 this->label16->Name = L"label16";
				 this->label16->Size = System::Drawing::Size(51, 13);
				 this->label16->TabIndex = 25;
				 this->label16->Text = L"Server IP";
				 this->label16->Visible = false;
				 // 
				 // MyDedicated
				 // 
				 this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
				 this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
				 this->ClientSize = System::Drawing::Size(586, 596);
				 this->Controls->Add(this->numScript);
				 this->Controls->Add(this->checkBox1);
				 this->Controls->Add(this->textBoxScript);
				 this->Controls->Add(this->label15);
				 this->Controls->Add(this->buttonLoad);
				 this->Controls->Add(this->buttonSave);
				 this->Controls->Add(this->buttonExit);
				 this->Controls->Add(this->buttonUpdate);
				 this->Controls->Add(this->buttonCreate);
				 this->Controls->Add(this->linkLabel1);
				 this->Controls->Add(this->textBoxStatus);
				 this->Controls->Add(this->label12);
				 this->Controls->Add(this->label11);
				 this->Controls->Add(this->numExtraXplayer);
				 this->Controls->Add(this->numExtra);
				 this->Controls->Add(this->comboBoxDifficult);
				 this->Controls->Add(this->label10);
				 this->Controls->Add(this->label9);
				 this->Controls->Add(this->numFrag);
				 this->Controls->Add(this->numTime);
				 this->Controls->Add(this->groupBox1);
				 this->Controls->Add(this->menuStrip1);
				 this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
				 this->Name = L"MyDedicated";
				 this->Text = L"Serious Sam MyDedicated";
				 this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &MyDedicated::MyDedicated_FormClosing);
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numExtraXplayer))->EndInit();
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numExtra))->EndInit();
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numFrag))->EndInit();
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numTime))->EndInit();
				 this->groupBox1->ResumeLayout(false);
				 this->groupBox1->PerformLayout();
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numBPS))->EndInit();
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numFPS))->EndInit();
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numPlayerMax))->EndInit();
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numPlayerMin))->EndInit();
				 this->menuStrip1->ResumeLayout(false);
				 this->menuStrip1->PerformLayout();
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numScript))->EndInit();
				 this->ResumeLayout(false);
				 this->PerformLayout();

			 }
#pragma endregion
	private: System::Void buttonCreate_Click(System::Object^  sender, System::EventArgs^  e) {
		if (textBoxPassword->Text == "")
		{
			MessageBox::Show("Forget Password! Please, set the password and retry!", "ERROR 06", MessageBoxButtons::OK, MessageBoxIcon::Error);
			return;
		}
				 Args += "+port " + textBoxPort->Text;


				 if (textBoxName->Text != "")
					 Args += " +sessionname \"" + textBoxName->Text + "\"";
				 else
				 {
					 textBoxStatus->Text = "No Name Server! Default name setted";
					 Args += "+sessionname \" MyDedicated Server by Nobel3D\"";
				 }
				 Args += " +fps " + Convert::ToString(numFPS->Value);

				 if (comboBoxMode->SelectedIndex == 0 ||
					 comboBoxMode->SelectedIndex == 1 ||
					 comboBoxMode->SelectedIndex == 2 ||
					 comboBoxMode->SelectedIndex == 3 ||
					 comboBoxMode->SelectedIndex == 4 ||
					 comboBoxMode->SelectedIndex == 5 ||
					 comboBoxMode->SelectedIndex == 6 ||
					 comboBoxMode->SelectedIndex == 7)
					 Args += " +level \"" + getLevels(30 + comboBoxLevel->SelectedIndex) + "\"";

				 if (comboBoxMode->SelectedIndex == 8)
					 Args += " +level \"" + getLevels(47 + comboBoxLevel->SelectedIndex) + "\"";

				 if (comboBoxMode->SelectedIndex == 9 || comboBoxMode->SelectedIndex == 10)
					 Args += " +level \"" + getLevels(0 + comboBoxLevel->SelectedIndex) + "\"";

				 if (comboBoxMode->SelectedIndex == 11)
					 Args += " +level \"" + getLevels(51 + comboBoxLevel->SelectedIndex) + "\"";

				 Args += " +gam_bCustomizedDifficulty " + (comboBoxDifficult->SelectedIndex - 1);

				 if (comboBoxMode->SelectedIndex == 0)
					 Args += " +gamemode Deathmatch";
				 if (comboBoxMode->SelectedIndex == 1)
					 Args += " +gamemode InstantKill";
				 if (comboBoxMode->SelectedIndex == 2)
					 Args += " +gamemode BeastHunt";
				 if (comboBoxMode->SelectedIndex == 3)
					 Args += " +gamemode MyBurden";
				 if (comboBoxMode->SelectedIndex == 4)
					 Args += " +gamemode LastManStanding";
				 if (comboBoxMode->SelectedIndex == 5)
					 Args += " +gamemode TeamDeathmatch";
				 if (comboBoxMode->SelectedIndex == 6)
					 Args += " +gamemode TeamBeastHunt";
				 if (comboBoxMode->SelectedIndex == 7)
					 Args += " +gamemode LastTeamStanding";
				 if (comboBoxMode->SelectedIndex == 8)
					 Args += " +gamemode CaptureTheFlag";
				 if (comboBoxMode->SelectedIndex == 9)
					 Args += " +gamemode Cooperative";
				 if (comboBoxMode->SelectedIndex == 10)
					 Args += " +gamemode CooperativeCoinOp";
				 if (comboBoxMode->SelectedIndex == 11)
					 Args += " +gamemode TeamSurvival";

				 Args += " +rcts_strAdminPassword \"" + textBoxPassword->Text + "\"";

				 Args += " +rcts_strWelcomeNote \"MyDedicated Server By Nobel3D\"";

				 Args += " +gam_ctMinPlayers " + numPlayerMin->Value;
				 Args += " +gam_ctMaxPlayers " + numPlayerMax->Value;

				 Args += " +gam_ctPrivateSlots 2";

				 if (toolStripMenuItem1->Checked)
					 Args += " +gam_bInfiniteAmmo 1";
				 else
					 Args += " +gam_bInfiniteAmmo 0";


				 if (allowHealthToolStripMenuItem->Checked)
					 Args += " +gam_bAllowHealth 1";
				 else
					 Args += " +gam_bAllowHealth 0";


				 if (allowArmorToolStripMenuItem->Checked)
					 Args += " +gam_bAllowArmor 1";
				 else
					 Args += " +gam_bAllowArmor 0";


				 if (spawnInvulnerabilityToolStripMenuItem->Checked)
					 Args += " +gam_bInvulnerableAfterSpawning 1";
				 else
					 Args += " +gam_bInvulnerableAfterSpawning 0";


				 if (heaToolStripMenuItem->Checked)
					 Args += " +gam_bHealthStays 1";
				 else
					 Args += " +gam_bHealthStays 0";


				 if (armorStaysToolStripMenuItem->Checked)
					 Args += " +gam_bArmorStays 1";
				 else
					 Args += " +gam_bArmorStays 0";


				 if (ammoStaysToolStripMenuItem->Checked)
					 Args += " +gam_bAmmoStays 1";
				 else
					 Args += " +gam_bAmmoStays 0";


				 if (weaponsStayToolStripMenuItem->Checked)
					 Args += " +gam_bWeaponsStay 1";
				 else
					 Args += " +gam_bWeaponsStay 0";


				 if (friendlyFireToolStripMenuItem->Checked)
					 Args += " +gam_bFriendlyFire 1";
				 else
					 Args += " +gam_bFriendlyFire 0";


				 if (respawnInPlaceToolStripMenuItem->Checked)
					 Args += " +gam_bRespawnInPlace 1";
				 else
					 Args += " +gam_bRespawnInPlace 0";


				 Args += " +gam_gdDifficulty " + (comboBoxDifficult->SelectedIndex + 1);

				 Args += " +gam_iExtraEnemyStrength " + numExtra->Value;
				 Args += " +gam_iExtraEnemyStrengthPerPlayer " + numExtraXplayer->Value;

				 Args += " +gam_ctFragsLimit " + numFrag->Value;
				 Args += " +gam_ctTimeLimit " + numTime->Value;

				 Args += " +ser_iMaxClientBPS " + numBPS->Value;

				 if (disableVotingToolStripMenuItem->Checked)
					 Args += " +prj_strDisabledVoteTypes \"all\"";
				 else
					 Args += " +prj_strDisabledVoteTypes \"\"";

				 stringIP = textBoxIP->Text;

				 if (!remoteServer)
				 {
					 if (IO::File::Exists(Exe))
					 {
						 PortValue = Convert::ToInt32(textBoxPort->Text);
						 Password = textBoxPassword->Text;
						 Name = textBoxName->Text;
						 textBoxStatus->Text = "Started!";
						 timeScript();
						 System::Diagnostics::Process::Start(Exe, Args);
						 MessageBox::Show("Thank you for using MyDedicated -Nobel3D", "This End", MessageBoxButtons::OK, MessageBoxIcon::Information);
						 MyAdmin::MyDedicated::~MyDedicated();
					 }
					 else
					 {
						 exit = openFile->ShowDialog();
						 while (openFile->SafeFileName != "SamHD_TSE_DedicatedServer.exe" || exit == Windows::Forms::DialogResult::Cancel)
						 {
							 MessageBox::Show("Selected file isn't valid! You must select your Serious Sam HD Dedicated Server", "Error File", MessageBoxButtons::OK, MessageBoxIcon::Error);
						 }
						 if (exit != Windows::Forms::DialogResult::Cancel)
						 {

							 Exe = openFile->FileName;
							 Name = textBoxName->Text;
							 PortValue = Convert::ToInt32(textBoxPort->Text);
							 Password = textBoxPassword->Text;
							 textBoxStatus->Text = "Started!";
							 timeScript();
							 System::Diagnostics::Process::Start(Exe, Args);
							 MessageBox::Show("Thank you for using MyDedicated -Nobel3D", "This End", MessageBoxButtons::OK, MessageBoxIcon::Information);
							 MyAdmin::MyDedicated::~MyDedicated();
						 }
						 else
						 {
							 MessageBox::Show("Thank you for using MyDedicated -Nobel3D", "This End", MessageBoxButtons::OK, MessageBoxIcon::Information);
							 MyAdmin::MyDedicated::~MyDedicated();
						 }
					 }
				 }
				 else
				 {
					 MessageBox::Show("Thank you for using MyDedicated -Nobel3D", "This End", MessageBoxButtons::OK, MessageBoxIcon::Information);
					 MyAdmin::MyDedicated::~MyDedicated();
				 }
	}
#pragma region ClickEditor
	private: System::Void toolStripMenuItem1_Click(System::Object^  sender, System::EventArgs^  e) {
				 changeClick(toolStripMenuItem1);
	}
	private: System::Void allowArmorToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
				 changeClick(allowArmorToolStripMenuItem);
	}
	private: System::Void heaToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
				 changeClick(heaToolStripMenuItem);
	}
	private: System::Void armorStaysToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
				 changeClick(armorStaysToolStripMenuItem);
	}
	private: System::Void ammoStaysToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
				 changeClick(ammoStaysToolStripMenuItem);
	}
	private: System::Void weaponsStayToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
				 changeClick(weaponsStayToolStripMenuItem);
	}
	private: System::Void disableVotingToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
				 changeClick(disableVotingToolStripMenuItem);
	}
	private: System::Void clientsMayPauseToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
				 changeClick(clientsMayPauseToolStripMenuItem);
	}
	private: System::Void spawnInvulnerabilityToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
				 changeClick(spawnInvulnerabilityToolStripMenuItem);
	}
	private: System::Void respawnInPlaceToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
				 changeClick(respawnInPlaceToolStripMenuItem);
	}
	private: System::Void extraEnemiesToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
				 changeClick(extraEnemiesToolStripMenuItem);
	}
	private: System::Void friendlyFireToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
				 changeClick(friendlyFireToolStripMenuItem);
	}
	private: System::Void allowHealthToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
				 changeClick(allowHealthToolStripMenuItem);
	}
#pragma endregion
	private: System::Void linkLabel1_LinkClicked(System::Object^  sender, System::Windows::Forms::LinkLabelLinkClickedEventArgs^  e) {
				 System::Diagnostics::Process::Start("https://www.youtube.com/user/nobel3d");
	}
	private: System::Void numPlayerMin_ValueChanged(System::Object^  sender, System::EventArgs^  e) {
				 if (numPlayerMin->Value <= 1 || numPlayerMin->Value >= 8 || numPlayerMin->Value>numPlayerMax->Value)
					 numPlayerMin->Value = 2;
	}
	private: System::Void numPlayerMax_ValueChanged(System::Object^  sender, System::EventArgs^  e) {
				 if (numPlayerMax->Value <= 1 || numPlayerMax->Value >= 17 || numPlayerMax->Value<numPlayerMin->Value)
					 numPlayerMax->Value = 16;
	}
	private: System::Void comboBoxLevel_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
				 if (comboBoxLevel->Text == "Other...")
				 {
					 textBoxLevel->Enabled = true;
					 Modder = true;
				 }
				 else
				 {
					 textBoxLevel->Enabled = false;
					 Modder = false;
				 }
	}
	private: System::Void comboBoxMode_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
				 if (comboBoxMode->SelectedIndex == 0 ||
					 comboBoxMode->SelectedIndex == 1 ||
					 comboBoxMode->SelectedIndex == 2 ||
					 comboBoxMode->SelectedIndex == 3 ||
					 comboBoxMode->SelectedIndex == 4 ||
					 comboBoxMode->SelectedIndex == 5 ||
					 comboBoxMode->SelectedIndex == 6 ||
					 comboBoxMode->SelectedIndex == 7)
				 {
					 setLevels(comboBoxLevel, 1);

					 numFrag->Enabled = true;
					 numTime->Enabled = true;
					 comboBoxDifficult->Enabled = false;
					 numExtra->Enabled = false;
					 numExtraXplayer->Enabled = false;
					 label10->Text = "Frag Limit";
				 }
				 if (comboBoxMode->SelectedIndex == 8)
				 {
					 setLevels(comboBoxLevel, 2);

					 numFrag->Enabled = true;
					 numTime->Enabled = true;
					 comboBoxDifficult->Enabled = false;
					 numExtra->Enabled = false;
					 numExtraXplayer->Enabled = false;
					 label10->Text = "Score Limit";
				 }
				 if (comboBoxMode->SelectedIndex == 9 || comboBoxMode->SelectedIndex == 10)
				 {
					 setLevels(comboBoxLevel, 0);

					 numFrag->Enabled = false;
					 numTime->Enabled = false;
					 comboBoxDifficult->Enabled = true;
					 numExtra->Enabled = true;
					 numExtraXplayer->Enabled = true;
				 }
				 if (comboBoxMode->SelectedIndex == 11)
				 {
					 setLevels(comboBoxLevel, 3);

					 numFrag->Enabled = false;
					 numTime->Enabled = false;
					 comboBoxDifficult->Enabled = true;
					 numExtra->Enabled = true;
					 numExtraXplayer->Enabled = true;
				 }
	}
	private: System::Void checkBoxShow_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
				 if (checkBoxShow->Checked)
					 textBoxPassword->UseSystemPasswordChar = false;
				 else
					 textBoxPassword->UseSystemPasswordChar = true;
	}
	private: System::Void buttonUpdate_Click(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void buttonExit_Click(System::Object^  sender, System::EventArgs^  e) {
		exit = Windows::Forms::DialogResult::Cancel;
		MyAdmin::MyDedicated::~MyDedicated();
	}
	private: System::Void MyDedicated_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e) {
	}
	private: System::Void buttonSave_Click(System::Object^  sender, System::EventArgs^  e) {
				 IO::StreamWriter^ SaveCfg = gcnew IO::StreamWriter("Server.conf", false);
				 SaveCfg->WriteLine("ServerName=" + textBoxName->Text);
				 SaveCfg->WriteLine("ServerPort=" + textBoxPort->Text);
				 SaveCfg->WriteLine("GameMode=" + comboBoxMode->Text);

				 if (comboBoxLevel->Text != "Other...")
					 SaveCfg->WriteLine("GameLevel=" + comboBoxLevel->Text);
				 else
					 SaveCfg->WriteLine("GameLevel=" + textBoxLevel->Text);

				 SaveCfg->WriteLine("MinPlayer=" + numPlayerMin->Text);
				 SaveCfg->WriteLine("MaxPlayer=" + numPlayerMax->Text);
				 SaveCfg->WriteLine("GameTime=" + numTime->Text);
				 SaveCfg->WriteLine("GameFrag=" + numFrag->Text);
				 SaveCfg->Close();

				 MessageBox::Show("Your configuration has been saved!", "Saved", MessageBoxButtons::OK, MessageBoxIcon::Information);
	}
	private: System::Void buttonLoad_Click(System::Object^  sender, System::EventArgs^  e) {
				 openConfig->ShowDialog();
				 IO::StreamReader^ LoadCfg = gcnew IO::StreamReader(openConfig->FileName);
				 System::Collections::Generic::List<String^>^ LoadingCfg = gcnew System::Collections::Generic::List<String^>;
				 array<String^>^ str_Analyze = gcnew array<String^>(2);
				 while (!LoadCfg->EndOfStream)
				 {
					 str_Analyze = LoadCfg->ReadLine()->Split(gcnew array<String^>{"="}, StringSplitOptions::None);
					 LoadingCfg->Add(str_Analyze[1]);
				 }
				 LoadCfg->Close();
				 array<String^>^ Config = LoadingCfg->ToArray();
				 textBoxName->Text = Config[0];
				 textBoxPort->Text = Config[1];
				 comboBoxMode->Text = Config[2];
				 comboBoxLevel->Text = Config[3];
				 numPlayerMin->Text = Config[4];
				 numPlayerMax->Text = Config[5];
				 numTime->Text = Config[6];
				 numFrag->Text = Config[7];

				 MessageBox::Show("Your configuration has been loaded!", "Loaded", MessageBoxButtons::OK, MessageBoxIcon::Information);
	}
	private: System::Void checkBox1_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
				 if (!checkBox1->Checked)
				 {
					 checkBox1->Checked = false;
					 textBoxScript->Enabled = false;
					 numScript->Enabled = false;
				 }
				 else
				 {
					 checkBox1->Checked = true;
					 textBoxScript->Enabled = true;
					 numScript->Enabled = true;
				 }
	}
};
}

#pragma once

#include "..\Class\Players.h"
#include "..\Class\Rcon.h"

namespace MyAdmin {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/*useful class form*/
	public ref class SupportForm : public System::Windows::Forms::Form
	{
	public:
		/*Create a Timer Message*/
		SupportForm(void)
		{
			InitializeComponent();
			this->Text = "Timer Message";
			TypeForm = "TIMER";
			textBoxSuicide->Visible = false;
			label3->Visible = false;
		}
		/*Create your Signature on all admin's message*/
		SupportForm(int Index)
		{
			TypeForm = "SIGNATURE";
			InitializeComponent();
			this->Text = "Signature for message";
			label1->Text = "Insert your signature for all message";
			label2->Visible = false;
			numericMinute->Visible = false;
			textBoxSuicide->Visible = false;
			label3->Visible = false;
		}
		/*Ban anyone player for this time*/
		SupportForm(array<Players^>^ Ban, int AddMonth, int AddDays, int AddHours, int AddMinute)
		{
			InitializeComponent();
			this->Text = "Ban a player";
			Taker = Ban;
			DateTime^ NowTime = DateTime::Now;
			if (NowTime->Minute + AddMinute>59)
			{
				Minutes = (NowTime->Minute + AddMinute) - 60;
				AddHours++;
			}
			else
				Minutes = NowTime->Minute + AddMinute;
			if (NowTime->Hour + AddHours>23)
			{
				Hours = (NowTime->Hour + AddHours) - 24;
				AddDays++;
			}
			else
				Hours = NowTime->Hour + AddHours;
			if (NowTime->Day + AddDays>29) //I know the error, but I will fix D:
			{
				Days = (NowTime->Day + AddDays) - 30;
				AddMonth++;
			}
			else
				Days = NowTime->Day + AddDays;
			if (NowTime->Month + AddMonth>11) //0-11 Months
			{
				Months = (NowTime->Month + AddMonth) - 12;
				Years++;
			}
			else
				Months = NowTime->Month + AddMonth;

			Years += NowTime->Year;



			StringBan = Days + "/" + Months + "/" + Years + " " + Hours + ":" + Minutes + ":00"; //little difference 
			TypeForm = "BAN";
			numericMinute->Visible = false;
			label2->Visible = false;
			label1->Visible = false;
			comboBoxBan->Visible = true;
			textBoxText->Visible = false;
			textBoxSuicide->Visible = false;
			label3->Visible = false;

			for (int i = 0; i<MAXPLAYERSUPPORT; i++)
			{
				if (Ban[i]->getInitialize() == true)
				{
					Rcon::addLog("[NSF] Player: " + Ban[i]->getName() + "; ID: " + Ban[i]->getID() + "; Load on ban list");
					comboBoxBan->Items->Add(Ban[i]->getName() + " : " + Ban[i]->getID());
				}
				else if (Ban[i]->getID() != nullptr)
				{
					comboBoxBan->Items->Add("Spectator Player : " + Ban[i]->getID());
				}
				else
				{
					comboBoxBan->Items->Add("Free Index");
				}
			}

		}
		/*Unban anyone ID*/
		SupportForm(String^ Unban)
		{
			InitializeComponent();
			this->Text = "UnBan a player";
			TypeForm = "UNBAN";
			numericMinute->Visible = false;
			label2->Visible = false;
			label1->Visible = false;
			comboBoxBan->Visible = true;
			textBoxText->Visible = false;
			textBoxSuicide->Visible = false;
			label3->Visible = false;
			if (IO::File::Exists("BanList.ban"))
			{
				IO::StreamReader^ BanList = gcnew IO::StreamReader("BanList.ban");
				array<String^>^ Separator = { "," };

				Line = gcnew array<array<String^>^>(50);
				String^ Part;
				int i = 0;
				while (!BanList->EndOfStream)
				{
					Line[i] = gcnew array<String^>(2);
					Part = BanList->ReadLine();
					Line[i] = Part->Split(Separator, StringSplitOptions::None);
					comboBoxBan->Items->Add(Line[i][0] + " FOR " + Line[i][1]);
					i++;
				}
				BanList->Close();
			}
			else
			{
				MessageBox::Show("None player is banned!", "Not found Banlist", MessageBoxButtons::OK, MessageBoxIcon::Stop);
				MyAdmin::SupportForm::~SupportForm();
			}

		}
		/*Create a kill message*/
		SupportForm(Rcon^ Pointer)
		{
			InitializeComponent();
			this->Text = "Kill Message Editor";
			TypeForm = "KILLMESSAGE";
			comboBoxBan->Visible = false;
			numericMinute->Visible = false;
			label2->Visible = false;

			label1->Text = "Insert your kill message";
		}
	public:
		String^ TypeForm;
		String^ getKill() { return KillMessage; }
		String^ getMessage(){ return MyMessage; }
		String^ getSignature(){ return MySignature; }
		int getMinute(){ return MyMinute; }
		int getIndexBan(){ return IndexBan; }
		bool getEnabled(){ return EnabledMessage; }

	protected:
		~SupportForm()
		{
			if (components)
			{
				delete components;
			}
		}

		//Main Variables
	private: String^ KillMessage;
	private: String^ SuicideMessage;
	private: String^ MyMessage;
	private: String^ MySignature;
	private: int MyMinute;
	private: array<Players^>^ Taker;
	private: String^ StringBan;
	private: String^ ID;
	private: static int IndexBan = -1;
	private: static bool EnabledMessage = true;

			 //Stream
	private: IO::StreamWriter^ stm_confWriter;
	private: IO::StreamReader^ stm_confReader;
	private: String^ str_Analyze;
	private: array<array<String^>^>^ Line;

			 //BanSupport
	private: int Minutes;
	private: int Hours;
	private: int Days;
	private: int Months;
	private: int Years;
	private: bool EqualYear;

	private: System::Windows::Forms::TextBox^  textBoxSuicide;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::ComboBox^  comboBoxBan;
	private: System::Windows::Forms::Button^  buttonExit;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::NumericUpDown^  numericMinute;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::TextBox^  textBoxText;
	private: System::Windows::Forms::Button^  buttonSend;
	private: System::ComponentModel::Container ^components;
	private: System::Windows::Forms::CheckBox^  checkBoxDisable;

#pragma region Windows Form Designer generated code
			 /// <summary>
			 /// Metodo necessario per il supporto della finestra di progettazione. Non modificare
			 /// il contenuto del metodo con l'editor di codice.
			 /// </summary>
			 void InitializeComponent(void)
			 {
				 System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(SupportForm::typeid));
				 this->comboBoxBan = (gcnew System::Windows::Forms::ComboBox());
				 this->buttonExit = (gcnew System::Windows::Forms::Button());
				 this->label2 = (gcnew System::Windows::Forms::Label());
				 this->numericMinute = (gcnew System::Windows::Forms::NumericUpDown());
				 this->label1 = (gcnew System::Windows::Forms::Label());
				 this->textBoxText = (gcnew System::Windows::Forms::TextBox());
				 this->buttonSend = (gcnew System::Windows::Forms::Button());
				 this->textBoxSuicide = (gcnew System::Windows::Forms::TextBox());
				 this->label3 = (gcnew System::Windows::Forms::Label());
				 this->checkBoxDisable = (gcnew System::Windows::Forms::CheckBox());
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericMinute))->BeginInit();
				 this->SuspendLayout();
				 // 
				 // comboBoxBan
				 // 
				 this->comboBoxBan->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
				 this->comboBoxBan->FormattingEnabled = true;
				 this->comboBoxBan->Location = System::Drawing::Point(12, 60);
				 this->comboBoxBan->Name = L"comboBoxBan";
				 this->comboBoxBan->Size = System::Drawing::Size(451, 21);
				 this->comboBoxBan->TabIndex = 13;
				 this->comboBoxBan->Visible = false;
				 // 
				 // buttonExit
				 // 
				 this->buttonExit->Location = System::Drawing::Point(12, 195);
				 this->buttonExit->Name = L"buttonExit";
				 this->buttonExit->Size = System::Drawing::Size(75, 23);
				 this->buttonExit->TabIndex = 12;
				 this->buttonExit->Text = L"Exit";
				 this->buttonExit->UseVisualStyleBackColor = true;
				 this->buttonExit->Click += gcnew System::EventHandler(this, &SupportForm::buttonExit_Click);
				 // 
				 // label2
				 // 
				 this->label2->AutoSize = true;
				 this->label2->Location = System::Drawing::Point(93, 148);
				 this->label2->Name = L"label2";
				 this->label2->Size = System::Drawing::Size(77, 13);
				 this->label2->TabIndex = 11;
				 this->label2->Text = L"Minute of send";
				 // 
				 // numericMinute
				 // 
				 this->numericMinute->Location = System::Drawing::Point(17, 145);
				 this->numericMinute->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 50, 0, 0, 0 });
				 this->numericMinute->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
				 this->numericMinute->Name = L"numericMinute";
				 this->numericMinute->Size = System::Drawing::Size(70, 20);
				 this->numericMinute->TabIndex = 10;
				 this->numericMinute->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 2, 0, 0, 0 });
				 // 
				 // label1
				 // 
				 this->label1->AutoSize = true;
				 this->label1->Location = System::Drawing::Point(168, 32);
				 this->label1->Name = L"label1";
				 this->label1->Size = System::Drawing::Size(129, 13);
				 this->label1->TabIndex = 9;
				 this->label1->Text = L"Insert your timed message";
				 // 
				 // textBoxText
				 // 
				 this->textBoxText->Location = System::Drawing::Point(10, 61);
				 this->textBoxText->Name = L"textBoxText";
				 this->textBoxText->Size = System::Drawing::Size(453, 20);
				 this->textBoxText->TabIndex = 8;
				 // 
				 // buttonSend
				 // 
				 this->buttonSend->Location = System::Drawing::Point(171, 187);
				 this->buttonSend->Name = L"buttonSend";
				 this->buttonSend->Size = System::Drawing::Size(126, 38);
				 this->buttonSend->TabIndex = 7;
				 this->buttonSend->Text = L"Send";
				 this->buttonSend->UseVisualStyleBackColor = true;
				 this->buttonSend->Click += gcnew System::EventHandler(this, &SupportForm::buttonSend_Click);
				 // 
				 // textBoxSuicide
				 // 
				 this->textBoxSuicide->Location = System::Drawing::Point(10, 117);
				 this->textBoxSuicide->Name = L"textBoxSuicide";
				 this->textBoxSuicide->Size = System::Drawing::Size(451, 20);
				 this->textBoxSuicide->TabIndex = 14;
				 // 
				 // label3
				 // 
				 this->label3->AutoSize = true;
				 this->label3->Location = System::Drawing::Point(168, 91);
				 this->label3->Name = L"label3";
				 this->label3->Size = System::Drawing::Size(137, 13);
				 this->label3->TabIndex = 15;
				 this->label3->Text = L"Insert your suicide message";
				 // 
				 // checkBoxDisable
				 // 
				 this->checkBoxDisable->AutoSize = true;
				 this->checkBoxDisable->Location = System::Drawing::Point(381, 146);
				 this->checkBoxDisable->Name = L"checkBoxDisable";
				 this->checkBoxDisable->Size = System::Drawing::Size(61, 17);
				 this->checkBoxDisable->TabIndex = 16;
				 this->checkBoxDisable->Text = L"Disable";
				 this->checkBoxDisable->UseVisualStyleBackColor = true;
				 this->checkBoxDisable->Visible = false;
				 this->checkBoxDisable->CheckedChanged += gcnew System::EventHandler(this, &SupportForm::checkBoxDisable_CheckedChanged);
				 // 
				 // SupportForm
				 // 
				 this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
				 this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
				 this->ClientSize = System::Drawing::Size(479, 237);
				 this->Controls->Add(this->checkBoxDisable);
				 this->Controls->Add(this->label3);
				 this->Controls->Add(this->textBoxSuicide);
				 this->Controls->Add(this->comboBoxBan);
				 this->Controls->Add(this->buttonExit);
				 this->Controls->Add(this->label2);
				 this->Controls->Add(this->numericMinute);
				 this->Controls->Add(this->label1);
				 this->Controls->Add(this->textBoxText);
				 this->Controls->Add(this->buttonSend);
				 this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
				 this->Name = L"SupportForm";
				 this->Text = L"SupportForm";
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericMinute))->EndInit();
				 this->ResumeLayout(false);
				 this->PerformLayout();

			 }
#pragma endregion

	private: System::Void buttonSend_Click(System::Object^  sender, System::EventArgs^  e) {


				 if (TypeForm == "SIGNATURE")
				 {
					 if (textBoxText->Text->Length > 2)
					 {
						 array<wchar_t>^ SafeCheck = textBoxText->Text->ToCharArray();
						 for (int i = 0; i < SafeCheck->Length; i++)
						 if (SafeCheck[i] == ':')
							 SafeCheck[i] = 'ò';

						 MySignature = gcnew String(SafeCheck);
						 MySignature = textBoxText->Text;
						 Rcon::addLog("[NSF] SignatureChanged: " + MySignature);
					 }
					 else
						 MessageBox::Show("Too short", "ERROR 05", MessageBoxButtons::OK, MessageBoxIcon::Error);
				 }
				 if (TypeForm == "TIMER")
				 {
					 MyMessage = textBoxText->Text;
					 MyMinute = Convert::ToInt32(numericMinute->Text);
					 Rcon::addLog("[NSF] TimedMessageChanged: " + MyMessage + "; Time: " + MyMinute);
				 }
				 if (TypeForm == "BAN")
				 {
					 DateTime^ TimeBan = DateTime::Now;
					 IndexBan = comboBoxBan->SelectedIndex;
					 Taker[IndexBan]->Ban(StringBan);
					 Rcon::addLog("[NSB] PlayerBanned: " + Taker[IndexBan]->getName() + "; IDBanned: " + Taker[IndexBan]->getID());

				 }
				 if (TypeForm == "UNBAN")
				 {
					 Players::Unban(Line[comboBoxBan->SelectedIndex][0]);
					 Rcon::addLog("[NSB] IDUnBanned: " + Line[comboBoxBan->SelectedIndex][0]);
				 }
				 if (TypeForm == "KILLMESSAGE")
				 {
					 if (!EnabledMessage)
					 {
						 KillMessage = textBoxText->Text;
						 SuicideMessage = textBoxSuicide->Text;
					 }
				 }
				 SupportForm::Close();

	}
	private: System::Void buttonExit_Click(System::Object^  sender, System::EventArgs^  e) {
				 SupportForm::~SupportForm();
	}
	private: System::Void checkBoxDisable_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
				 EnabledMessage = checkBoxDisable->Checked;
	}
	};
}

#pragma once

namespace MyAdmin {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Riepilogo per Credits
	/// </summary>
	public ref class Credits : public System::Windows::Forms::Form
	{
	public:
		Credits(void)
		{
			InitializeComponent();
		}

	protected:
		~Credits()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::LinkLabel^  linkLabelNobel;
	protected:
	private: System::Windows::Forms::LinkLabel^  linkLabelSgob;
	private: System::Windows::Forms::LinkLabel^  linkLabelScratch;
	private: System::Windows::Forms::LinkLabel^  linkLabelLoller;
	private: System::Windows::Forms::LinkLabel^  linkLabelHexagon;

	private: System::Windows::Forms::Button^  buttonThanks;
	private: System::Windows::Forms::PictureBox^  pictureBox1;

	private:

		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(Credits::typeid));
			this->linkLabelNobel = (gcnew System::Windows::Forms::LinkLabel());
			this->linkLabelSgob = (gcnew System::Windows::Forms::LinkLabel());
			this->linkLabelScratch = (gcnew System::Windows::Forms::LinkLabel());
			this->linkLabelLoller = (gcnew System::Windows::Forms::LinkLabel());
			this->linkLabelHexagon = (gcnew System::Windows::Forms::LinkLabel());
			this->buttonThanks = (gcnew System::Windows::Forms::Button());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			this->SuspendLayout();
			// 
			// linkLabelNobel
			// 
			this->linkLabelNobel->AutoSize = true;
			this->linkLabelNobel->BackColor = System::Drawing::Color::Transparent;
			this->linkLabelNobel->Cursor = System::Windows::Forms::Cursors::IBeam;
			this->linkLabelNobel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10));
			this->linkLabelNobel->LinkColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(128)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)));
			this->linkLabelNobel->Location = System::Drawing::Point(24, 27);
			this->linkLabelNobel->Name = L"linkLabelNobel";
			this->linkLabelNobel->Size = System::Drawing::Size(555, 17);
			this->linkLabelNobel->TabIndex = 0;
			this->linkLabelNobel->TabStop = true;
			this->linkLabelNobel->Text = L"Luca \"Nobel3D\" Gasperini : Programmer and Creator of MyAdmin ~~/ He loves C++ \\~~"
				L"";
			this->linkLabelNobel->LinkClicked += gcnew System::Windows::Forms::LinkLabelLinkClickedEventHandler(this, &Credits::linkLabelNobel_LinkClicked);
			// 
			// linkLabelSgob
			// 
			this->linkLabelSgob->AutoSize = true;
			this->linkLabelSgob->BackColor = System::Drawing::Color::Transparent;
			this->linkLabelSgob->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10));
			this->linkLabelSgob->LinkColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(192)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)));
			this->linkLabelSgob->Location = System::Drawing::Point(24, 66);
			this->linkLabelSgob->Name = L"linkLabelSgob";
			this->linkLabelSgob->Size = System::Drawing::Size(398, 17);
			this->linkLabelSgob->TabIndex = 1;
			this->linkLabelSgob->TabStop = true;
			this->linkLabelSgob->Text = L"Serious Sgob : Ranking method; Good friend and good player";
			this->linkLabelSgob->LinkClicked += gcnew System::Windows::Forms::LinkLabelLinkClickedEventHandler(this, &Credits::linkLabelSgob_LinkClicked);
			// 
			// linkLabelScratch
			// 
			this->linkLabelScratch->AutoSize = true;
			this->linkLabelScratch->BackColor = System::Drawing::Color::Transparent;
			this->linkLabelScratch->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10));
			this->linkLabelScratch->LinkColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(192)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)));
			this->linkLabelScratch->Location = System::Drawing::Point(24, 102);
			this->linkLabelScratch->Name = L"linkLabelScratch";
			this->linkLabelScratch->Size = System::Drawing::Size(545, 17);
			this->linkLabelScratch->TabIndex = 2;
			this->linkLabelScratch->TabStop = true;
			this->linkLabelScratch->Text = L"Angelo Geels : Programmer and first author of managing system and Ranking system";
			this->linkLabelScratch->LinkClicked += gcnew System::Windows::Forms::LinkLabelLinkClickedEventHandler(this, &Credits::linkLabelScratch_LinkClicked);
			// 
			// linkLabelLoller
			// 
			this->linkLabelLoller->AutoSize = true;
			this->linkLabelLoller->BackColor = System::Drawing::Color::Transparent;
			this->linkLabelLoller->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10));
			this->linkLabelLoller->LinkColor = System::Drawing::Color::Red;
			this->linkLabelLoller->Location = System::Drawing::Point(24, 143);
			this->linkLabelLoller->Name = L"linkLabelLoller";
			this->linkLabelLoller->Size = System::Drawing::Size(268, 17);
			this->linkLabelLoller->TabIndex = 3;
			this->linkLabelLoller->TabStop = true;
			this->linkLabelLoller->Text = L"Loller : Beta testing and logistical support";
			this->linkLabelLoller->LinkClicked += gcnew System::Windows::Forms::LinkLabelLinkClickedEventHandler(this, &Credits::linkLabelLoller_LinkClicked);
			// 
			// linkLabelHexagon
			// 
			this->linkLabelHexagon->ActiveLinkColor = System::Drawing::Color::Red;
			this->linkLabelHexagon->AutoSize = true;
			this->linkLabelHexagon->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10));
			this->linkLabelHexagon->LinkColor = System::Drawing::Color::Red;
			this->linkLabelHexagon->Location = System::Drawing::Point(24, 184);
			this->linkLabelHexagon->Name = L"linkLabelHexagon";
			this->linkLabelHexagon->Size = System::Drawing::Size(322, 17);
			this->linkLabelHexagon->TabIndex = 4;
			this->linkLabelHexagon->TabStop = true;
			this->linkLabelHexagon->Text = L"Hexagon : Official translator from English to Italian";
			this->linkLabelHexagon->LinkClicked += gcnew System::Windows::Forms::LinkLabelLinkClickedEventHandler(this, &Credits::linkLabelHexagon_LinkClicked);
			// 
			// buttonThanks
			// 
			this->buttonThanks->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10));
			this->buttonThanks->Location = System::Drawing::Point(217, 221);
			this->buttonThanks->Name = L"buttonThanks";
			this->buttonThanks->Size = System::Drawing::Size(145, 38);
			this->buttonThanks->TabIndex = 6;
			this->buttonThanks->Text = L"Thanks To All!";
			this->buttonThanks->UseVisualStyleBackColor = true;
			this->buttonThanks->Click += gcnew System::EventHandler(this, &Credits::buttonThanks_Click);
			// 
			// pictureBox1
			// 
			this->pictureBox1->BackColor = System::Drawing::Color::Transparent;
			this->pictureBox1->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox1.Image")));
			this->pictureBox1->Location = System::Drawing::Point(93, 12);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(388, 202);
			this->pictureBox1->TabIndex = 7;
			this->pictureBox1->TabStop = false;
			// 
			// Credits
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(591, 271);
			this->Controls->Add(this->buttonThanks);
			this->Controls->Add(this->linkLabelHexagon);
			this->Controls->Add(this->linkLabelLoller);
			this->Controls->Add(this->linkLabelScratch);
			this->Controls->Add(this->linkLabelSgob);
			this->Controls->Add(this->linkLabelNobel);
			this->Controls->Add(this->pictureBox1);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->Name = L"Credits";
			this->Text = L"Credits";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void buttonThanks_Click(System::Object^  sender, System::EventArgs^  e) {
				 Credits::~Credits();
	}
	private: System::Void linkLabelNobel_LinkClicked(System::Object^  sender, System::Windows::Forms::LinkLabelLinkClickedEventArgs^  e) {
				 System::Diagnostics::Process::Start("http://steamcommunity.com/id/Nobel3D/");
	}
	private: System::Void linkLabelSgob_LinkClicked(System::Object^  sender, System::Windows::Forms::LinkLabelLinkClickedEventArgs^  e) {
				 System::Diagnostics::Process::Start("http://steamcommunity.com/id/leeeeeeeeeeeroyjenkins/");
	}
	private: System::Void linkLabelScratch_LinkClicked(System::Object^  sender, System::Windows::Forms::LinkLabelLinkClickedEventArgs^  e) {
				 System::Diagnostics::Process::Start("http://steamcommunity.com/id/ansjh/");
	}
	private: System::Void linkLabelLoller_LinkClicked(System::Object^  sender, System::Windows::Forms::LinkLabelLinkClickedEventArgs^  e) {
				 System::Diagnostics::Process::Start("http://steamcommunity.com/id/SASfffdADdADfdSAD/");
	}
	private: System::Void linkLabelHexagon_LinkClicked(System::Object^  sender, System::Windows::Forms::LinkLabelLinkClickedEventArgs^  e) {
				 System::Diagnostics::Process::Start("http://steamcommunity.com/id/HexagonZzZ/");
	}
	};
}

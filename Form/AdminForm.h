#pragma once

#include "..\Class\Players.h"
#include "..\Class\Admin.h"

namespace MyAdmin {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for AdminForm
	/// </summary>
	public ref class AdminForm : public System::Windows::Forms::Form
	{
	public:
		AdminForm(array<Players^>^ PlayerList)
		{
			InitializeComponent();
			playerList = PlayerList;
			comboBoxType->SelectedIndex = 0;
			for (int i = 0; i < PlayerList->Length; i++)
				comboBoxList->Items->Add(PlayerList[i]->getName() != "" ?
										PlayerList[i]->getName() :
										PlayerList[i]->getID() + " Index: " + PlayerList[i]->getSamIndex());
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~AdminForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: array<Players^>^ playerList;
	private: System::Windows::Forms::ComboBox^  comboBoxList;
	private: System::Windows::Forms::ComboBox^  comboBoxType;
	private: System::Windows::Forms::Button^  buttonExit;
	private: System::Windows::Forms::Button^  buttonAdd;
	private: System::Windows::Forms::Label^  labelPermission;
	private: System::Windows::Forms::Label^  labelList;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(AdminForm::typeid));
			this->comboBoxList = (gcnew System::Windows::Forms::ComboBox());
			this->comboBoxType = (gcnew System::Windows::Forms::ComboBox());
			this->buttonExit = (gcnew System::Windows::Forms::Button());
			this->buttonAdd = (gcnew System::Windows::Forms::Button());
			this->labelPermission = (gcnew System::Windows::Forms::Label());
			this->labelList = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// comboBoxList
			// 
			this->comboBoxList->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->comboBoxList->FormattingEnabled = true;
			this->comboBoxList->Location = System::Drawing::Point(12, 68);
			this->comboBoxList->Name = L"comboBoxList";
			this->comboBoxList->Size = System::Drawing::Size(311, 21);
			this->comboBoxList->TabIndex = 0;
			// 
			// comboBoxType
			// 
			this->comboBoxType->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->comboBoxType->FormattingEnabled = true;
			this->comboBoxType->Items->AddRange(gcnew cli::array< System::Object^  >(4) { L"Standard", L"Middle", L"Full", L"Total" });
			this->comboBoxType->Location = System::Drawing::Point(12, 125);
			this->comboBoxType->Name = L"comboBoxType";
			this->comboBoxType->Size = System::Drawing::Size(132, 21);
			this->comboBoxType->TabIndex = 1;
			// 
			// buttonExit
			// 
			this->buttonExit->Location = System::Drawing::Point(12, 200);
			this->buttonExit->Name = L"buttonExit";
			this->buttonExit->Size = System::Drawing::Size(69, 27);
			this->buttonExit->TabIndex = 2;
			this->buttonExit->Text = L"Exit";
			this->buttonExit->UseVisualStyleBackColor = true;
			this->buttonExit->Click += gcnew System::EventHandler(this, &AdminForm::buttonExit_Click);
			// 
			// buttonAdd
			// 
			this->buttonAdd->Location = System::Drawing::Point(139, 200);
			this->buttonAdd->Name = L"buttonAdd";
			this->buttonAdd->Size = System::Drawing::Size(69, 27);
			this->buttonAdd->TabIndex = 3;
			this->buttonAdd->Text = L"Add Admin";
			this->buttonAdd->UseVisualStyleBackColor = true;
			this->buttonAdd->Click += gcnew System::EventHandler(this, &AdminForm::buttonAdd_Click);
			// 
			// labelPermission
			// 
			this->labelPermission->AutoSize = true;
			this->labelPermission->Location = System::Drawing::Point(156, 128);
			this->labelPermission->Name = L"labelPermission";
			this->labelPermission->Size = System::Drawing::Size(86, 13);
			this->labelPermission->TabIndex = 4;
			this->labelPermission->Text = L"Permission Level";
			// 
			// labelList
			// 
			this->labelList->AutoSize = true;
			this->labelList->Location = System::Drawing::Point(153, 52);
			this->labelList->Name = L"labelList";
			this->labelList->Size = System::Drawing::Size(55, 13);
			this->labelList->TabIndex = 5;
			this->labelList->Text = L"Player List";
			// 
			// AdminForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(335, 239);
			this->Controls->Add(this->labelList);
			this->Controls->Add(this->labelPermission);
			this->Controls->Add(this->buttonAdd);
			this->Controls->Add(this->buttonExit);
			this->Controls->Add(this->comboBoxType);
			this->Controls->Add(this->comboBoxList);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->Name = L"AdminForm";
			this->Text = L"AdminForm";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void buttonAdd_Click(System::Object^  sender, System::EventArgs^  e) {
		Admin::addCredential(playerList[comboBoxList->SelectedIndex]->getID(), Permissions(comboBoxType->SelectedIndex));
		this->Close();
	}
private: System::Void buttonExit_Click(System::Object^  sender, System::EventArgs^  e) {
	this->Close();
}
};
}

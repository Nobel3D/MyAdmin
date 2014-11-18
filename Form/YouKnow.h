#pragma once

namespace MyAdmin {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public ref class YouKnow : public System::Windows::Forms::Form
	{
	public:
		YouKnow(String^ Trick)
		{
			InitializeComponent();
			textBoxTrick->Text = Trick;
		}
	public: bool getNext() { return Next; }
	private: System::Windows::Forms::PictureBox^  pictureBox1;
	public:
	private: static bool Next = false;
	protected:
		~YouKnow()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^  labelKnow;

	private: System::Windows::Forms::TextBox^  textBoxTrick;
	private: System::Windows::Forms::Button^  buttonExit;
	private: System::Windows::Forms::Button^  buttonNext;

	private: System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code

			 void InitializeComponent(void)
			 {
				 System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(YouKnow::typeid));
				 this->labelKnow = (gcnew System::Windows::Forms::Label());
				 this->textBoxTrick = (gcnew System::Windows::Forms::TextBox());
				 this->buttonExit = (gcnew System::Windows::Forms::Button());
				 this->buttonNext = (gcnew System::Windows::Forms::Button());
				 this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
				 this->SuspendLayout();
				 // 
				 // labelKnow
				 // 
				 this->labelKnow->AutoSize = true;
				 this->labelKnow->Font = (gcnew System::Drawing::Font(L"Linux Biolinum G", 20, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->labelKnow->Location = System::Drawing::Point(16, 47);
				 this->labelKnow->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
				 this->labelKnow->Name = L"labelKnow";
				 this->labelKnow->Size = System::Drawing::Size(184, 31);
				 this->labelKnow->TabIndex = 0;
				 this->labelKnow->Text = L"Did You Know\?";
				 // 
				 // textBoxTrick
				 // 
				 this->textBoxTrick->Location = System::Drawing::Point(22, 134);
				 this->textBoxTrick->Multiline = true;
				 this->textBoxTrick->Name = L"textBoxTrick";
				 this->textBoxTrick->ReadOnly = true;
				 this->textBoxTrick->Size = System::Drawing::Size(331, 160);
				 this->textBoxTrick->TabIndex = 2;
				 this->textBoxTrick->Text = L"Text Here!";
				 // 
				 // buttonExit
				 // 
				 this->buttonExit->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9));
				 this->buttonExit->Location = System::Drawing::Point(22, 311);
				 this->buttonExit->Name = L"buttonExit";
				 this->buttonExit->Size = System::Drawing::Size(111, 33);
				 this->buttonExit->TabIndex = 3;
				 this->buttonExit->Text = L"Exit";
				 this->buttonExit->UseVisualStyleBackColor = true;
				 this->buttonExit->Click += gcnew System::EventHandler(this, &YouKnow::buttonExit_Click);
				 // 
				 // buttonNext
				 // 
				 this->buttonNext->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9));
				 this->buttonNext->Location = System::Drawing::Point(242, 311);
				 this->buttonNext->Name = L"buttonNext";
				 this->buttonNext->Size = System::Drawing::Size(111, 33);
				 this->buttonNext->TabIndex = 4;
				 this->buttonNext->Text = L"Next ->";
				 this->buttonNext->UseVisualStyleBackColor = true;
				 this->buttonNext->Click += gcnew System::EventHandler(this, &YouKnow::buttonNext_Click);
				 // 
				 // pictureBox1
				 // 
				 this->pictureBox1->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox1.Image")));
				 this->pictureBox1->Location = System::Drawing::Point(215, 22);
				 this->pictureBox1->Name = L"pictureBox1";
				 this->pictureBox1->Size = System::Drawing::Size(138, 93);
				 this->pictureBox1->TabIndex = 5;
				 this->pictureBox1->TabStop = false;
				 // 
				 // YouKnow
				 // 
				 this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
				 this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
				 this->ClientSize = System::Drawing::Size(388, 356);
				 this->Controls->Add(this->pictureBox1);
				 this->Controls->Add(this->buttonNext);
				 this->Controls->Add(this->buttonExit);
				 this->Controls->Add(this->textBoxTrick);
				 this->Controls->Add(this->labelKnow);
				 this->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
				 this->Margin = System::Windows::Forms::Padding(4);
				 this->Name = L"YouKnow";
				 this->Text = L"Did you know\?";
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
				 this->ResumeLayout(false);
				 this->PerformLayout();

			 }
#pragma endregion
	private: System::Void buttonExit_Click(System::Object^  sender, System::EventArgs^  e) {
				 Next = false;
				 this->~YouKnow();
	}
	private: System::Void buttonNext_Click(System::Object^  sender, System::EventArgs^  e) {
				 Next = true;
				 this->~YouKnow();
	}
	};
}

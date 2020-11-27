#include "Car.h"
#pragma once

namespace Project1 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for GUI
	/// </summary>
	public ref class GUI : public System::Windows::Forms::Form
	{
	public:
		GUI(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~GUI()
		{
			if (components)
			{
				delete components;
			}
		}
	public: System::Windows::Forms::Label^  label1;
	System::Windows::Forms::TextBox^  rho;
	System::Windows::Forms::TextBox^  gravity;
	System::Windows::Forms::TextBox^  wheelRadius;
	System::Windows::Forms::TextBox^  mass;
	System::Windows::Forms::TextBox^  frontarea;
	System::Windows::Forms::TextBox^  cd;
	System::Windows::Forms::TextBox^  cr;
	System::Windows::Forms::TextBox^  cb;
	System::Windows::Forms::TextBox^  l;
	System::Windows::Forms::TextBox^  ca;










	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::Label^  label6;
	private: System::Windows::Forms::Label^  label7;
	private: System::Windows::Forms::Label^  label8;
	private: System::Windows::Forms::Label^  label9;
	private: System::Windows::Forms::Label^  label10;
	private: System::Windows::Forms::Label^  label11;
	private: System::Windows::Forms::Label^  sidearea;
	public: System::Windows::Forms::TextBox^  sidear;
	private:


	private:
	protected:

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
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->rho = (gcnew System::Windows::Forms::TextBox());
			this->gravity = (gcnew System::Windows::Forms::TextBox());
			this->wheelRadius = (gcnew System::Windows::Forms::TextBox());
			this->mass = (gcnew System::Windows::Forms::TextBox());
			this->frontarea = (gcnew System::Windows::Forms::TextBox());
			this->cd = (gcnew System::Windows::Forms::TextBox());
			this->cr = (gcnew System::Windows::Forms::TextBox());
			this->cb = (gcnew System::Windows::Forms::TextBox());
			this->l = (gcnew System::Windows::Forms::TextBox());
			this->ca = (gcnew System::Windows::Forms::TextBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->label11 = (gcnew System::Windows::Forms::Label());
			this->sidearea = (gcnew System::Windows::Forms::Label());
			this->sidear = (gcnew System::Windows::Forms::TextBox());
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(33, 52);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(31, 13);
			this->label1->TabIndex = 0;
			this->label1->Text = L"RHO";
			this->label1->Click += gcnew System::EventHandler(this, &GUI::label1_Click);
			// 
			// rho
			// 
			this->rho->Location = System::Drawing::Point(87, 49);
			this->rho->Name = L"rho";
			this->rho->Size = System::Drawing::Size(100, 20);
			this->rho->TabIndex = 1;
			this->rho->Text = L"1.164";
			this->rho->TextChanged += gcnew System::EventHandler(this, &GUI::textBox1_TextChanged);
			// 
			// gravity
			// 
			this->gravity->Location = System::Drawing::Point(87, 75);
			this->gravity->Name = L"gravity";
			this->gravity->Size = System::Drawing::Size(100, 20);
			this->gravity->TabIndex = 2;
			this->gravity->Text = L"9.8";
			this->gravity->TextChanged += gcnew System::EventHandler(this, &GUI::textBox2_TextChanged);
			// 
			// wheelRadius
			// 
			this->wheelRadius->Location = System::Drawing::Point(87, 101);
			this->wheelRadius->Name = L"wheelRadius";
			this->wheelRadius->Size = System::Drawing::Size(100, 20);
			this->wheelRadius->TabIndex = 3;
			this->wheelRadius->Text = L"19.5";
			this->wheelRadius->TextChanged += gcnew System::EventHandler(this, &GUI::textBox3_TextChanged);
			// 
			// mass
			// 
			this->mass->Location = System::Drawing::Point(87, 127);
			this->mass->Name = L"mass";
			this->mass->Size = System::Drawing::Size(100, 20);
			this->mass->TabIndex = 4;
			this->mass->Text = L"1400";
			this->mass->TextChanged += gcnew System::EventHandler(this, &GUI::textBox4_TextChanged);
			// 
			// frontarea
			// 
			this->frontarea->Location = System::Drawing::Point(87, 153);
			this->frontarea->Name = L"frontarea";
			this->frontarea->Size = System::Drawing::Size(100, 20);
			this->frontarea->TabIndex = 5;
			this->frontarea->Text = L"2.4";
			this->frontarea->TextChanged += gcnew System::EventHandler(this, &GUI::textBox5_TextChanged);
			// 
			// cd
			// 
			this->cd->Location = System::Drawing::Point(329, 49);
			this->cd->Name = L"cd";
			this->cd->Size = System::Drawing::Size(100, 20);
			this->cd->TabIndex = 6;
			this->cd->Text = L"0.25";
			this->cd->TextChanged += gcnew System::EventHandler(this, &GUI::textBox6_TextChanged);
			// 
			// cr
			// 
			this->cr->Location = System::Drawing::Point(329, 75);
			this->cr->Name = L"cr";
			this->cr->Size = System::Drawing::Size(100, 20);
			this->cr->TabIndex = 7;
			this->cr->Text = L"0.1";
			this->cr->TextChanged += gcnew System::EventHandler(this, &GUI::textBox7_TextChanged);
			// 
			// cb
			// 
			this->cb->Location = System::Drawing::Point(329, 101);
			this->cb->Name = L"cb";
			this->cb->Size = System::Drawing::Size(100, 20);
			this->cb->TabIndex = 8;
			this->cb->Text = L"1500";
			this->cb->TextChanged += gcnew System::EventHandler(this, &GUI::textBox8_TextChanged);
			// 
			// l
			// 
			this->l->Location = System::Drawing::Point(329, 127);
			this->l->Name = L"l";
			this->l->Size = System::Drawing::Size(100, 20);
			this->l->TabIndex = 9;
			this->l->Text = L"3.3";
			this->l->TextChanged += gcnew System::EventHandler(this, &GUI::textBox9_TextChanged);
			// 
			// ca
			// 
			this->ca->Location = System::Drawing::Point(329, 153);
			this->ca->Name = L"ca";
			this->ca->Size = System::Drawing::Size(100, 20);
			this->ca->TabIndex = 10;
			this->ca->Text = L"867";
			this->ca->TextChanged += gcnew System::EventHandler(this, &GUI::textBox10_TextChanged);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(12, 78);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(73, 13);
			this->label2->TabIndex = 11;
			this->label2->Text = L"Gravity Const.";
			this->label2->Click += gcnew System::EventHandler(this, &GUI::label2_Click);
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(7, 104);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(74, 13);
			this->label3->TabIndex = 12;
			this->label3->Text = L"Wheel Radius";
			this->label3->Click += gcnew System::EventHandler(this, &GUI::label3_Click);
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(33, 130);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(32, 13);
			this->label4->TabIndex = 13;
			this->label4->Text = L"Mass";
			this->label4->Click += gcnew System::EventHandler(this, &GUI::label4_Click);
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(25, 156);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(56, 13);
			this->label5->TabIndex = 14;
			this->label5->Text = L"Front Area";
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(223, 52);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(100, 13);
			this->label6->TabIndex = 15;
			this->label6->Text = L"Airresistance Const.";
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Location = System::Drawing::Point(212, 75);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(114, 13);
			this->label7->TabIndex = 16;
			this->label7->Text = L"WheelsFraction Const.";
			this->label7->Click += gcnew System::EventHandler(this, &GUI::label7_Click);
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Location = System::Drawing::Point(240, 104);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(73, 13);
			this->label8->TabIndex = 17;
			this->label8->Text = L"Breaks Const.";
			this->label8->Click += gcnew System::EventHandler(this, &GUI::label8_Click);
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->Location = System::Drawing::Point(252, 130);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(40, 13);
			this->label9->TabIndex = 18;
			this->label9->Text = L"Length";
			this->label9->Click += gcnew System::EventHandler(this, &GUI::label9_Click);
			// 
			// label10
			// 
			this->label10->AutoSize = true;
			this->label10->Location = System::Drawing::Point(223, 156);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(85, 13);
			this->label10->TabIndex = 19;
			this->label10->Text = L"Cornering Const.";
			this->label10->Click += gcnew System::EventHandler(this, &GUI::label10_Click);
			// 
			// label11
			// 
			this->label11->AutoSize = true;
			this->label11->Font = (gcnew System::Drawing::Font(L"Modern No. 20", 15.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label11->Location = System::Drawing::Point(24, 22);
			this->label11->Name = L"label11";
			this->label11->Size = System::Drawing::Size(62, 24);
			this->label11->TabIndex = 20;
			this->label11->Text = L"Input";
			// 
			// sidearea
			// 
			this->sidearea->AutoSize = true;
			this->sidearea->Location = System::Drawing::Point(25, 185);
			this->sidearea->Name = L"sidearea";
			this->sidearea->Size = System::Drawing::Size(53, 13);
			this->sidearea->TabIndex = 21;
			this->sidearea->Text = L"Side Area";
			// 
			// sidear
			// 
			this->sidear->Location = System::Drawing::Point(87, 182);
			this->sidear->Name = L"sidear";
			this->sidear->Size = System::Drawing::Size(100, 20);
			this->sidear->TabIndex = 22;
			this->sidear->Text = L"5.0";
			this->sidear->TextChanged += gcnew System::EventHandler(this, &GUI::textBox1_TextChanged_1);
			// 
			// GUI
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::ButtonFace;
			this->ClientSize = System::Drawing::Size(441, 363);
			this->Controls->Add(this->sidear);
			this->Controls->Add(this->sidearea);
			this->Controls->Add(this->label11);
			this->Controls->Add(this->label10);
			this->Controls->Add(this->label9);
			this->Controls->Add(this->label8);
			this->Controls->Add(this->label7);
			this->Controls->Add(this->label6);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->ca);
			this->Controls->Add(this->l);
			this->Controls->Add(this->cb);
			this->Controls->Add(this->cr);
			this->Controls->Add(this->cd);
			this->Controls->Add(this->frontarea);
			this->Controls->Add(this->mass);
			this->Controls->Add(this->wheelRadius);
			this->Controls->Add(this->gravity);
			this->Controls->Add(this->rho);
			this->Controls->Add(this->label1);
			this->Name = L"GUI";
			this->Text = L"GUI";
			this->Load += gcnew System::EventHandler(this, &GUI::GUI_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	public: void show_th(){
				this->ShowDialog();
	}
	private: System::Void GUI_Load(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void label1_Click(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void textBox1_TextChanged(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void label7_Click(System::Object^  sender, System::EventArgs^  e) {
	}
private: System::Void label10_Click(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void label9_Click(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void label8_Click(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void label4_Click(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void label3_Click(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void label2_Click(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void textBox10_TextChanged(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void textBox9_TextChanged(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void textBox8_TextChanged(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void textBox7_TextChanged(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void textBox6_TextChanged(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void textBox5_TextChanged(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void textBox4_TextChanged(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void textBox3_TextChanged(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void textBox2_TextChanged(System::Object^  sender, System::EventArgs^  e) {
}
public: System::Void changeLabel(double c){
			l->Text = L"jm";
}
private: System::Void textBox1_TextChanged_1(System::Object^  sender, System::EventArgs^  e) {
}
};
}

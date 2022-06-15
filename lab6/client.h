#pragma once

#include <Windows.h>

#define PIPE_NAME "\\\\.\\pipe\\Pipe"

namespace os6 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Сводка для Client
	/// </summary>
	public ref class Client : public System::Windows::Forms::Form
	{
	public:
		Client(void)
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~Client()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^ send_btn;
	protected:
	private: System::Windows::Forms::Label^ open_enter;
	private: System::Windows::Forms::TextBox^ a11;
	private: System::Windows::Forms::TextBox^ a21;
	private: System::Windows::Forms::TextBox^ a12;
	private: System::Windows::Forms::TextBox^ a22;
	private: System::Windows::Forms::Label^ close_enter;
	private: System::Windows::Forms::Label^ res_lbl;

	private: System::Windows::Forms::Label^ open_ans;
	private: System::Windows::Forms::Label^ close_ans;
	private: System::Windows::Forms::TextBox^ res11;
	private: System::Windows::Forms::TextBox^ res21;


	private: System::Windows::Forms::TextBox^ res12;
	private: System::Windows::Forms::TextBox^ res22;
	private: System::Windows::Forms::Label^ exit_lbl;







	private:
		/// <summary>
		/// Обязательная переменная конструктора.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Требуемый метод для поддержки конструктора — не изменяйте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->send_btn = (gcnew System::Windows::Forms::Button());
			this->open_enter = (gcnew System::Windows::Forms::Label());
			this->a11 = (gcnew System::Windows::Forms::TextBox());
			this->a21 = (gcnew System::Windows::Forms::TextBox());
			this->a12 = (gcnew System::Windows::Forms::TextBox());
			this->a22 = (gcnew System::Windows::Forms::TextBox());
			this->close_enter = (gcnew System::Windows::Forms::Label());
			this->res_lbl = (gcnew System::Windows::Forms::Label());
			this->open_ans = (gcnew System::Windows::Forms::Label());
			this->close_ans = (gcnew System::Windows::Forms::Label());
			this->res11 = (gcnew System::Windows::Forms::TextBox());
			this->res21 = (gcnew System::Windows::Forms::TextBox());
			this->res12 = (gcnew System::Windows::Forms::TextBox());
			this->res22 = (gcnew System::Windows::Forms::TextBox());
			this->exit_lbl = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// send_btn
			// 
			this->send_btn->Location = System::Drawing::Point(373, 64);
			this->send_btn->Name = L"send_btn";
			this->send_btn->Size = System::Drawing::Size(165, 77);
			this->send_btn->TabIndex = 0;
			this->send_btn->Text = L"Send Matrix";
			this->send_btn->UseVisualStyleBackColor = true;
			this->send_btn->Click += gcnew System::EventHandler(this, &Client::send_btn_Click);
			// 
			// open_enter
			// 
			this->open_enter->AutoSize = true;
			this->open_enter->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 72, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->open_enter->Location = System::Drawing::Point(12, 25);
			this->open_enter->Name = L"open_enter";
			this->open_enter->Size = System::Drawing::Size(98, 135);
			this->open_enter->TabIndex = 1;
			this->open_enter->Text = L"(";
			// 
			// a11
			// 
			this->a11->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 25.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->a11->Location = System::Drawing::Point(85, 42);
			this->a11->Name = L"a11";
			this->a11->Size = System::Drawing::Size(62, 56);
			this->a11->TabIndex = 2;
			this->a11->Text = L"0";
			// 
			// a21
			// 
			this->a21->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 25.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->a21->Location = System::Drawing::Point(85, 104);
			this->a21->Name = L"a21";
			this->a21->Size = System::Drawing::Size(62, 56);
			this->a21->TabIndex = 3;
			this->a21->Text = L"0";
			// 
			// a12
			// 
			this->a12->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 25.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->a12->Location = System::Drawing::Point(195, 42);
			this->a12->Name = L"a12";
			this->a12->Size = System::Drawing::Size(62, 56);
			this->a12->TabIndex = 4;
			this->a12->Text = L"0";
			// 
			// a22
			// 
			this->a22->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 25.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->a22->Location = System::Drawing::Point(195, 104);
			this->a22->Name = L"a22";
			this->a22->Size = System::Drawing::Size(62, 56);
			this->a22->TabIndex = 5;
			this->a22->Text = L"0";
			// 
			// close_enter
			// 
			this->close_enter->AutoSize = true;
			this->close_enter->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 72, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->close_enter->Location = System::Drawing::Point(248, 25);
			this->close_enter->Name = L"close_enter";
			this->close_enter->Size = System::Drawing::Size(98, 135);
			this->close_enter->TabIndex = 6;
			this->close_enter->Text = L")";
			// 
			// res_lbl
			// 
			this->res_lbl->AutoSize = true;
			this->res_lbl->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 13.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->res_lbl->Location = System::Drawing::Point(12, 202);
			this->res_lbl->Name = L"res_lbl";
			this->res_lbl->Size = System::Drawing::Size(261, 29);
			this->res_lbl->TabIndex = 7;
			this->res_lbl->Text = L"Результат сложения:";
			this->res_lbl->Visible = false;
			// 
			// open_ans
			// 
			this->open_ans->AutoSize = true;
			this->open_ans->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 72, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->open_ans->Location = System::Drawing::Point(12, 251);
			this->open_ans->Name = L"open_ans";
			this->open_ans->Size = System::Drawing::Size(98, 135);
			this->open_ans->TabIndex = 8;
			this->open_ans->Text = L"(";
			this->open_ans->Visible = false;
			// 
			// close_ans
			// 
			this->close_ans->AutoSize = true;
			this->close_ans->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 72, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->close_ans->Location = System::Drawing::Point(248, 251);
			this->close_ans->Name = L"close_ans";
			this->close_ans->Size = System::Drawing::Size(98, 135);
			this->close_ans->TabIndex = 9;
			this->close_ans->Text = L")";
			this->close_ans->Visible = false;
			// 
			// res11
			// 
			this->res11->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 25.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->res11->Location = System::Drawing::Point(85, 272);
			this->res11->Name = L"res11";
			this->res11->ReadOnly = true;
			this->res11->Size = System::Drawing::Size(62, 56);
			this->res11->TabIndex = 10;
			this->res11->Text = L"0";
			this->res11->Visible = false;
			// 
			// res21
			// 
			this->res21->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 25.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->res21->Location = System::Drawing::Point(85, 334);
			this->res21->Name = L"res21";
			this->res21->ReadOnly = true;
			this->res21->Size = System::Drawing::Size(62, 56);
			this->res21->TabIndex = 11;
			this->res21->Text = L"0";
			this->res21->Visible = false;
			// 
			// res12
			// 
			this->res12->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 25.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->res12->Location = System::Drawing::Point(195, 272);
			this->res12->Name = L"res12";
			this->res12->ReadOnly = true;
			this->res12->Size = System::Drawing::Size(62, 56);
			this->res12->TabIndex = 12;
			this->res12->Text = L"0";
			this->res12->Visible = false;
			// 
			// res22
			// 
			this->res22->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 25.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->res22->Location = System::Drawing::Point(195, 334);
			this->res22->Name = L"res22";
			this->res22->ReadOnly = true;
			this->res22->Size = System::Drawing::Size(62, 56);
			this->res22->TabIndex = 13;
			this->res22->Text = L"0";
			this->res22->Visible = false;
			// 
			// exit_lbl
			// 
			this->exit_lbl->AutoSize = true;
			this->exit_lbl->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 13.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->exit_lbl->Location = System::Drawing::Point(22, 408);
			this->exit_lbl->Name = L"exit_lbl";
			this->exit_lbl->Size = System::Drawing::Size(388, 29);
			this->exit_lbl->TabIndex = 14;
			this->exit_lbl->Text = L"Для выхода нажмите на крестик";
			// 
			// Client
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(623, 453);
			this->Controls->Add(this->exit_lbl);
			this->Controls->Add(this->res22);
			this->Controls->Add(this->res12);
			this->Controls->Add(this->res21);
			this->Controls->Add(this->res11);
			this->Controls->Add(this->res_lbl);
			this->Controls->Add(this->a22);
			this->Controls->Add(this->a12);
			this->Controls->Add(this->a21);
			this->Controls->Add(this->a11);
			this->Controls->Add(this->open_enter);
			this->Controls->Add(this->send_btn);
			this->Controls->Add(this->close_enter);
			this->Controls->Add(this->close_ans);
			this->Controls->Add(this->open_ans);
			this->Name = L"Client";
			this->Text = L"Client";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void send_btn_Click(System::Object^ sender, System::EventArgs^ e) {
		HANDLE pipe = CreateFile(TEXT(PIPE_NAME),
			GENERIC_READ | GENERIC_WRITE,
			0,
			NULL,
			OPEN_EXISTING,
			0,
			NULL);

		if (pipe == INVALID_HANDLE_VALUE) {
			this->Close();
		}

		int sizeX = 2;
		int sizeY = 2;
		int v;

		WriteFile(pipe, &sizeX, sizeof(int), NULL, NULL);
		WriteFile(pipe, &sizeY, sizeof(int), NULL, NULL);
		v = int::Parse(this->a11->Text);
		WriteFile(pipe, &v, sizeof(int), NULL, NULL);
		v = int::Parse(this->a12->Text);
		WriteFile(pipe, &v, sizeof(int), NULL, NULL);
		v = int::Parse(this->a21->Text);
		WriteFile(pipe, &v, sizeof(int), NULL, NULL);
		v = int::Parse(this->a22->Text);
		WriteFile(pipe, &v, sizeof(int), NULL, NULL);
		
		if (!ReadFile(pipe, &sizeX, sizeof(int), NULL, NULL)) {
		}

		if (!ReadFile(pipe, &sizeY, sizeof(int), NULL, NULL)) {
		}

		for (int i = 0; i < sizeX; i++) {
			for (int j = 0; j < sizeY; j++) {
				if (ReadFile(pipe, &v, sizeof(int), NULL, NULL)) {
					if (i == 0) {
						j == 0 ? res11->Text = Convert::ToString(v) : res12->Text = Convert::ToString(v);
					}
					j == 0 ? res21->Text = Convert::ToString(v) : res22->Text = Convert::ToString(v);
				}
			}
		}

		res_lbl->Visible = true;
		res11->Visible = true;
		res12->Visible = true;
		res21->Visible = true;
		res22->Visible = true;
		open_ans->Visible = true;
		close_ans->Visible = true;
		send_btn->Visible = false;
		Refresh();
	}
};
}
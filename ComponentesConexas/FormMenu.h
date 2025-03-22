#pragma once
#include <string>
#include <vector>
#include <ctime>
#include "FormManual.h"
#include "FormGrafo.h"
#include "FormComponente.h"

namespace ComponentesConexas {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for FormMenu
	/// </summary>
	public ref class FormMenu : public System::Windows::Forms::Form
	{
	public:
		FormMenu(void)
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
		~FormMenu()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^ label1;
	protected:
	private: System::Windows::Forms::TextBox^ textBox1;
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::Button^ button2;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 19.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label1->Location = System::Drawing::Point(24, 34);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(393, 90);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Ingresa el tamaño de la matriz (5-15):";
			// 
			// textBox1
			// 
			this->textBox1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->textBox1->Location = System::Drawing::Point(180, 166);
			this->textBox1->MaxLength = 2;
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(174, 38);
			this->textBox1->TabIndex = 1;
			this->textBox1->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &FormMenu::textBox1_KeyPress);
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(48, 277);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(157, 39);
			this->button1->TabIndex = 2;
			this->button1->Text = L"Manual";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &FormMenu::button1_Click);
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(305, 277);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(157, 39);
			this->button2->TabIndex = 3;
			this->button2->Text = L"Aleatorio";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &FormMenu::button2_Click);
			// 
			// FormMenu
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(537, 369);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->label1);
			this->Name = L"MyForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"MyForm";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e)
	{
		//Comprobar si esta vacio
		bool isEmpty = System::String::IsNullOrEmpty(textBox1->Text);
		if (isEmpty) { MessageBox::Show("Error 404: No se encontro un numero"); return; }
		//Comprobar que este en el intervalo
		int16_t num = Int16::Parse(textBox1->Text);
		if (num < 5 || num > 15) { MessageBox::Show("Error: el numero no esta en el intervalo"); return; }
		//Crear matriz de adyacencia
		srand(time(0));
		std::vector<std::vector<bool>> matriz;
		for (int i = 0; i < num; i++)
		{
			std::vector<bool> vector_fila;
			for (int j = 0; j < num; j++)
			{
				FormManual^ form = gcnew FormManual(i, j);
				form->StartPosition = FormStartPosition::CenterScreen;
				form->ShowDialog();
				bool valor = form->valor;
				vector_fila.push_back(valor);
			}
			matriz.push_back(vector_fila);
		}

		//Abrir la visualizacion
		this->Visible = false;
		FormGrafo^ form = gcnew FormGrafo();
		form->StartPosition = FormStartPosition::CenterScreen;
		form->matriz = new std::vector<std::vector<bool>>(matriz);
		form->ShowDialog();
		//2.0 Proceso de calculo de componentes
		FormComponente^ form2 = gcnew FormComponente();
		form2->matriz = new std::vector<std::vector<bool>>(matriz);
		form2->ShowDialog();
		this->Visible = true;
		return;
	}
	private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e)
	{
		//Comprobar si esta vacio
		bool isEmpty = System::String::IsNullOrEmpty(textBox1->Text);
		if (isEmpty) { MessageBox::Show("Error 404: No se encontro un numero"); return; }
		//Comprobar que este en el intervalo
		int16_t num = Int16::Parse(textBox1->Text);
		if (num < 5 || num > 15) { MessageBox::Show("Error: el numero no esta en el intervalo"); return; }
		//Crear matriz de adyacencia
		srand(time(0));
		std::vector<std::vector<bool>> matriz;
		for (int i = 0; i < num; ++i) {
			std::vector<bool> vector_filas_1;
			for (int j = 0; j < num; ++j) {
				bool aleatorio = rand() % 2;
				vector_filas_1.push_back(aleatorio);
			}
			matriz.push_back(vector_filas_1);
		}
		//Abrir la visualizacion
		this->Visible = false;
		FormGrafo^ form = gcnew FormGrafo();
		form->StartPosition = FormStartPosition::CenterScreen;
		form->matriz = new std::vector<std::vector<bool>>(matriz);
		form->ShowDialog();
		this->Visible = true;

		//2.0 Proceso de calculo de componentes
		FormComponente^ form2 = gcnew FormComponente();
		form2->matriz = new std::vector<std::vector<bool>>(matriz);
		form2->ShowDialog();
		return;
	}
	private: System::Void textBox1_KeyPress(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e)
	{
		if (!(e->KeyChar == 8 || (e->KeyChar >= 48 && e->KeyChar <= 57) || e->KeyChar == 46))
		{
			e->Handled = true;
		}
	}
	};
}

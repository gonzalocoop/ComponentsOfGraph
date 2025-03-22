#pragma once
#include <vector>
#include "VectorNodos.h"
namespace ComponentesConexas {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for FormGrafo
	/// </summary>
	public ref class FormGrafo : public System::Windows::Forms::Form
	{
	private:
		VectorNodos* vector;
		Int16 contador = 0;
	private: System::Windows::Forms::Button^ button1;
	public:
		std::vector<std::vector<bool>>* matriz = new std::vector<std::vector<bool> >();
		String^ buttonText = "Proceso";
	public:
		FormGrafo(void)
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
		~FormGrafo()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Timer^ timer1;
	protected:
	private: System::ComponentModel::IContainer^ components;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// timer1
			// 
			this->timer1->Enabled = true;
			this->timer1->Interval = 500;
			this->timer1->Tick += gcnew System::EventHandler(this, &FormGrafo::timer1_Tick);
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(381, 12);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(173, 53);
			this->button1->TabIndex = 0;
			this->button1->Text = buttonText;
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &FormGrafo::button1_Click);
			// 
			// FormGrafo
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(982, 953);
			this->Controls->Add(this->button1);
			this->Name = L"FormGrafo";
			this->Text = L"MyForm1";
			this->Load += gcnew System::EventHandler(this, &FormGrafo::MyForm1_Load);
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void timer1_Tick(System::Object^ sender, System::EventArgs^ e)
	{
		//Graphics setup
		Graphics^ g = this->CreateGraphics();
		BufferedGraphicsContext^ space = BufferedGraphicsManager::Current;
		BufferedGraphics^ buffer = space->Allocate(g, this->ClientRectangle);

		buffer->Graphics->Clear(Color::White);

		//Dibujar Nodos
		vector->Draw(buffer);
		//Dibujar Lineas
		vector->DrawLines(buffer, matriz, contador);
		//Graphics render
		buffer->Render(g);
		contador++;
		//Deletion
		delete buffer;
		delete space;
		delete g;
	}
	private: System::Void MyForm1_Load(System::Object^ sender, System::EventArgs^ e)
	{
		vector = new VectorNodos(matriz->size());
		Graphics^ g = this->CreateGraphics();
		BufferedGraphicsContext^ space = BufferedGraphicsManager::Current;
		BufferedGraphics^ buffer = space->Allocate(g, this->ClientRectangle);
		vector->AddNodes(buffer);
		button1->Text = buttonText;
	}

	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e)
	{
		Close();
	}


};
};

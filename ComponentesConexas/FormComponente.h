#pragma once
#include "FormGrafo.h"
#include "Calculo.h"
//#include <windows.h>
	namespace ComponentesConexas {

		using namespace System;
		using namespace System::ComponentModel;
		using namespace System::Collections;
		using namespace System::Windows::Forms;
		using namespace System::Data;
		using namespace System::Drawing;

		/// <summary>
		/// Summary for FormComponente
		/// </summary>
		public ref class FormComponente : public System::Windows::Forms::Form
		{
		public:
			std::vector<std::vector<bool>>* matriz = new std::vector<std::vector<bool> >();
		private: 
			System::Windows::Forms::Button^ button1;
			System::Windows::Forms::Button^ button2;
			Int16 contador;
			Int16 num_matriz;

		private:
			Calculo* calculo;
		public:
			FormComponente(void)
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
			~FormComponente()
			{
				if (components)
				{
					delete components;
				}
			}

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
				this->button1 = (gcnew System::Windows::Forms::Button());
				this->button2 = (gcnew System::Windows::Forms::Button());
				this->SuspendLayout();
				// 
				// button1
				// 
				this->button1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
					static_cast<System::Byte>(0)));
				this->button1->Location = System::Drawing::Point(262, 12);
				this->button1->Name = L"button1";
				this->button1->Size = System::Drawing::Size(287, 84);
				this->button1->TabIndex = 0;
				this->button1->Text = L"Empezar";
				this->button1->UseVisualStyleBackColor = true;
				this->button1->Click += gcnew System::EventHandler(this, &FormComponente::button1_Click);
				// 
				// button2
				// 
				this->button2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
					static_cast<System::Byte>(0)));
				this->button2->Location = System::Drawing::Point(728, 12);
				this->button2->Name = L"button2";
				this->button2->Size = System::Drawing::Size(287, 84);
				this->button2->TabIndex = 1;
				this->button2->Text = L"Graficar";
				this->button2->UseVisualStyleBackColor = true;
				this->button2->Click += gcnew System::EventHandler(this, &FormComponente::button2_Click);
				// 
				// FormComponente
				// 
				this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
				this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
				this->ClientSize = System::Drawing::Size(1382, 953);
				this->Controls->Add(this->button2);
				this->Controls->Add(this->button1);
				this->Name = L"FormComponente";
				this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
				this->Text = L"FormComponente";
				this->Load += gcnew System::EventHandler(this, &FormComponente::FormComponente_Load);
				this->ResumeLayout(false);

			}

	#pragma endregion
			private: System::Void FormComponente_Load(System::Object^ sender, System::EventArgs^ e)
			{
				calculo = new Calculo(matriz);
			}


			private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e){
				Graphics^ g = this->CreateGraphics();
				BufferedGraphicsContext^ space = BufferedGraphicsManager::Current;
				BufferedGraphics^ buffer = space->Allocate(g, this->ClientRectangle);

				buffer->Graphics->Clear(Color::White);
				switch (contador)
				{
				case 0:
					num_matriz = 0; //matriz actual
					button1->Text = "Siguiente";
					calculo->DrawMatriz(buffer, (String^)"Matriz de adyacencia");
					contador++;
					break;
				case 1:
					num_matriz = 0; //matriz actual
					calculo->diagonalOnes();
					calculo->DrawMatriz(buffer, (String^)"Diagonal de 1s");
					contador++;
					break;
				case 2:
					num_matriz = 0; //matriz actual
					calculo->pathMatrix();
					calculo->DrawMatriz(buffer, (String^)"Matriz de caminos");
					contador++;
					break;
				case 3:
					calculo->orderRow();
					num_matriz = 1; //matriz caminos
					calculo->DrawMatriz(buffer, (String^)"Se ordenan las filas");
					contador++;
					break;
				case 4:
					calculo->orderColumn();
					num_matriz = 1; //matriz caminos
					calculo->DrawMatriz(buffer, (String^)"Se ordenan las columnas");
					contador++;
					break;
				case 5:
					calculo->DrawComponents(buffer);
					calculo->matrizComponentes();
					num_matriz = 2; //matriz componentes
					button1->Visible = false;
					break;
				}


				buffer->Render(g);
				delete buffer;
				delete space;
				delete g;
			}
		private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e)
		{
			this->Visible = false;
			FormGrafo^ form = gcnew FormGrafo();
			form->StartPosition = FormStartPosition::CenterScreen;
			switch (num_matriz)
			{
			case 0: //matriz actual
				form->matriz = calculo->getMatrix();
				break;
			case 1: //matriz caminos
				form->matriz = calculo->getPathMatrix();
				break;
			case 2: //matriz componentes
				form->matriz = calculo->getComponentMatrix();
				form->buttonText = L"Terminar";
				break;
			}
			
			form->ShowDialog();
			if (num_matriz == 2) this->Close();
			this->Visible = true;
			
		}
};
	}

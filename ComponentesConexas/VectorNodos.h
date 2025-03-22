#pragma once
#include <vector>
#include <cmath>
#include "Nodo.h"
const double PI = 3.14159265;

using namespace System::Drawing;

class VectorNodos
{
private:
	int size;
	int radio;
	int node_size;
	std::vector<Nodo>* nodes = new std::vector<Nodo>();
public:
	VectorNodos(int size = 0) : size(size), node_size(30), radio(175) {}
	~VectorNodos() {}
	void AddNodes(BufferedGraphics^ buffer)
	{
		double angle = 360 / size; //Calcular el angulo entre los nodos

		for (int i = 0; i < size; i++) //Se ejecuta un bucle por la cantidad de nodos
		{
			//Primero se busca el punto medio del ancho (o largo) de la ventana
			//Luego, se tiene 'radio' que sería para tener el tamaño del circulo (valor fijo)
			//Asimismo, el calculo en sí se hace con el coseno para el punto x, y seno para el punto y
			//Éste funcion trigonometrica uti liza el valor del angulo en radianes
			// y aqui se usa el valor de i que depende del nodo
			double x = buffer->Graphics->VisibleClipBounds.Width / 2 + radio * cos(i * angle * PI / 180.0); 
			double y = buffer->Graphics->VisibleClipBounds.Height / 2 + radio * sin(i * angle * PI / 180.0);
			nodes->push_back(Nodo(x, y)); //Se añaden al vector
		}
	}

	void Draw(BufferedGraphics^ buffer)
	{
		Pen^ lapiz = gcnew Pen(Color::Red, 2.0f);
		Font^ font = gcnew Font("Arial", 12);
		for (int i = 0; i < size; i++)
		{
			System::Drawing::Rectangle rectangulo = System::Drawing::Rectangle(nodes->at(i).getX(), nodes->at(i).getY(), node_size, node_size);
			buffer->Graphics->DrawEllipse(lapiz, rectangulo);

			int x = nodes->at(i).getX() + 8;
			int y = nodes->at(i).getY() + 5;
			System::String^ numero = i.ToString();
			buffer->Graphics->DrawString(numero, font, Brushes::Black, x, y);
		}
	}

	void DrawArrow(BufferedGraphics^ buffer, int x1, int y1, int x2, int y2, Color color)
	{
		Pen^ lapiz = gcnew Pen(color, 2.0f);

		// Calcular el angulo entre (x1, y1) y (x2, y2)
		double angle = atan2(y2 - y1, x2 - x1);

		// Longitud de la linea de la flecha
		int arrowLength = 15;

		// Dibujar la linea
		buffer->Graphics->DrawLine(lapiz, x1, y1, x2, y2);

		// Dibujar las partes de la flecha 
		int arrowX1 = x2 - arrowLength * cos(angle - PI / 6);
		int arrowY1 = y2 - arrowLength * sin(angle - PI / 6);
		int arrowX2 = x2 - arrowLength * cos(angle + PI / 6);
		int arrowY2 = y2 - arrowLength * sin(angle + PI / 6);

		buffer->Graphics->DrawLine(lapiz, x2, y2, arrowX1, arrowY1);
		buffer->Graphics->DrawLine(lapiz, x2, y2, arrowX2, arrowY2);
	}


	void DrawLines(BufferedGraphics^ buffer, std::vector<std::vector<bool>>* matriz, int contador)
	{
		cli::array<Color>^ colores = gcnew cli::array<Color>(16); // Cambia el tamano segun tus necesidades
		colores[0] = Color::Blue; colores[1] = Color::Red; colores[2] = Color::Green; colores[3] = Color::Yellow;
		colores[4] = Color::Orange; colores[5] = Color::Purple; colores[6] = Color::Cyan; colores[7] = Color::Magenta;
		colores[8] = Color::Brown; colores[9] = Color::Pink; colores[10] = Color::Lime; colores[11] = Color::Teal;
		colores[12] = Color::Olive; colores[13] = Color::Aqua; colores[14] = Color::Violet; colores[15] = Color::Gray;

		if (contador + 1 > matriz->size()) contador = matriz->size() - 1;
		for (int i = 0; i < contador + 1; i++)
		{
			Pen^ lapiz = gcnew Pen(colores[i], 2.0f);
			for (int j = 0; j < matriz->at(i).size(); j++)
			{
				if (matriz->at(i).at(j) == 1)
				{
					int x1 = nodes->at(i).getX() + node_size / 2;
					int y1 = nodes->at(i).getY() + node_size / 2;
					if (i == j)
					{
						buffer->Graphics->DrawArc(lapiz, x1 - 20, y1 - 20, 20, 20, 0, 360);
					}
					else
					{
						int x2 = nodes->at(j).getX();
						int y2 = nodes->at(j).getY() + node_size / 2;
						DrawArrow(buffer, x1, y1, x2, y2, colores[i]);
					}
				}
			}
		}
	}

};
#pragma once
#include <vector>
#include <algorithm>
#include <string>
#include <Windows.h>
using namespace std;
using namespace System::Drawing;

class Calculo
{
private:
    vector<vector<bool>> matrizAdyacencia;
    vector<vector<bool>> matrizCaminos;
    vector<vector<bool>>* matriz;
    vector<int> rowOrder;
    vector<int> colOrder;
    vector<int> conComponents;
public:
    Calculo(vector<vector<bool>>* matriz)
    {
        this->matriz = matriz;
        for (int i = 0; i < matriz->size(); i++)
        {
            rowOrder.push_back(i);
            colOrder.push_back(i);
        }

        matrizAdyacencia = *matriz;
    }

    void DrawMatriz(BufferedGraphics^ buffer, System::String^ text)
    {
        int numRow = matriz->size();
        int numColm = matriz->at(0).size();

        int cellWidth = 60; // Ancho de cada celda
        int cellHeight = 30; // Alto de cada celda

        Font^ font = gcnew System::Drawing::Font("Arial", 12);
        Pen^ pen = gcnew Pen(Color::Black, 2.0f);

        for (int i = 0; i < numRow; ++i) {
            for (int j = 0; j < numColm; ++j) {
                int x = j * cellWidth + buffer->Graphics->VisibleClipBounds.Width / matriz->size() - 2;
                int y = i * cellHeight + 100;

                // Dibuja el borde de la celda
                buffer->Graphics->DrawRectangle(pen, x, y, cellWidth, cellHeight);

                // Dibuja el número en el centro de la celda
                System::String^ number = System::Convert::ToString((int)matriz->at(i).at(j));
                System::Drawing::SizeF size = buffer->Graphics->MeasureString(number, font);
                float textX = x + (cellWidth - size.Width) / 2;
                float textY = y + (cellHeight - size.Height) / 2;

                buffer->Graphics->DrawString(number, font, Brushes::Black, textX, textY);
                if (j == 0)
                {
                    System::String^ rowNumber = System::Convert::ToString(rowOrder[i]);
                    buffer->Graphics->DrawString(rowNumber, font, Brushes::Black, x - 20, textY);
                }

                if (i == 0)
                {
                    System::String^ colNumber = System::Convert::ToString(colOrder[j]);
                    buffer->Graphics->DrawString(colNumber, font, Brushes::Black, x + cellWidth / 2 - 10, y - 20);
                }
            }


        }

        // Agregar el texto "Hola" debajo de la matriz
        int yTitle = (numRow * cellHeight) + 150; // Ajusta la posición Y según tu diseño
        System::String^ title = text;
        System::Drawing::SizeF holaSize = buffer->Graphics->MeasureString(title, font);
        int xTitle = 500 + (cellWidth - holaSize.Width) / 2;
        buffer->Graphics->DrawString(title, font, Brushes::Black, xTitle, yTitle);
    }

    void diagonalOnes()
    {
        for (int i = 0; i < matriz->size(); ++i) {
            for (int j = 0; j < matriz->size(); ++j) {
                if (i == j) matriz->at(i).at(j) = 1;
            }
        }
    }

    void pathMatrix()
    {
        bool flag = false;
        for (int i = 0; i < matriz->size(); i++) { 

            for (int j = 0; j < matriz->size(); j++) { 

                if (flag) { j = 0; flag = false; } //reset del j y el flag para revisar denuevo
                if (matriz->at(i).at(j) == 1) {
                    for (int k = 0; k < matriz->size(); ++k) {
                        if (!matriz->at(i).at(k) && matriz->at(j).at(k)) {
                            matriz->at(i).at(k) = matriz->at(j).at(k); flag = true;
                        }
                    }
                    if (flag) j = 0; //para que no se detenga el for
                }

            }
        }
        matrizCaminos = *matriz; //se guarda la matriz de caminos
    }

    void orderRow()
    {
        for (int i = 0; i < matriz->size() - 1; ++i) {
            int maxOnes = count(matriz->at(i).begin(), matriz->at(i).end(), 1);
            int maxId = i;
            for (int j = i + 1; j < matriz->size(); ++j) {
                int onesCount = count(matriz->at(j).begin(), matriz->at(j).end(), 1);
                if (onesCount > maxOnes) {
                    maxOnes = onesCount;
                    maxId = j;
                }
            }
            if (maxId != i) {
                // Intercambiar filas
                swap(matriz->at(i), matriz->at(maxId) );
                swap(rowOrder[i], rowOrder[maxId]);
            }
        }
    }

    void orderColumn()
    {
        vector<vector<bool>> matrizCopy = *matriz;
        for (int i = 0; i < matriz->size(); ++i) {
            for (int j = 0; j < matriz->size(); ++j) {
                matriz->at(i).at(j) = matrizCopy.at(i).at(rowOrder[j]);
            }
        }
        colOrder = rowOrder;
    }
    //FUNCIONES DE COMPONENTES CONEXAS
    bool checkSquare(int i, int j, int n)
    {
        bool flag = true;
        int x = i;
        int y = j;
        while (i < n + x)
        {
            j = y;
            while (j < n + y)
            {
                if (!matriz->at(i).at(j))
                {
                    flag = false;
                    return flag;
                }
                j++;
            }
            i++;
        }
        return flag;
    }

    bool finishComponents()
    {
        int suma = 0;
        for (int i = 0; i < conComponents.size(); i++)
        {
            suma += conComponents.at(i);
        }
         if (suma >= matriz->size()) return true;
        else return false;
    }

    void connectedComponents()
    {
        int i = 0;
        int j = 0;
        int k;
        for (i; i < matriz->size(); i++)
        {
            k = 0;
            for (j; j <= matriz->size(); j++)
            {
                if (j < matriz->size())
                {
                    if (matriz->at(i).at(j))
                    {
                        k++;
                    }
                    else
                    {
                        while (!checkSquare(i, i, k)) k--;
                        conComponents.push_back(k);
                        if (finishComponents()) return;
                        else { j = k + i; i = k + i; k = 1; }
                    }
                }
                else
                {
                    while (!checkSquare(i, i, k)) k--;
                    conComponents.push_back(k);
                    if (finishComponents()) return;
                    else { j = k + i; i = k + i; k = 1; }
                }
            }

        }
    }

    void DrawComponents(BufferedGraphics^ buffer)
    {
        connectedComponents(); // Actualiza el vector conComponents
        
        Font^ font = gcnew System::Drawing::Font("Arial", 15);
        //Titulo
        Font^ font_title = gcnew System::Drawing::Font("Arial", 20);
        System::String^ title = "Componentes Conexas";
        System::Drawing::SizeF size = buffer->Graphics->MeasureString(title, font_title);
        buffer->Graphics->DrawString(title, font_title, Brushes::Black, System::Drawing::Rectangle(100, 0, size.Width + 30, size.Height));
        
        int current_index = 0;
        // Construir la cadena con el formato deseado
        for (int i = 0; i < conComponents.size(); i++) //conComponents: 2 1 2 //rowOrder 2 3 0 1 4
        {
            //V[i]= {
            System::String^ component = "V[";
            component += System::Convert::ToString(i+1); 
            component += "] = {";
            //Filas de esa componente
            for (int j = 0; j < conComponents[i]; j++) 
            {
                component += System::Convert::ToString(rowOrder[current_index]); 
                current_index++;
                if (j < conComponents[i] - 1) { component += ",";}
            }
            component += "}";  // Cierra la lista
            System::Drawing::SizeF size = buffer->Graphics->MeasureString(component, font);
            buffer->Graphics->DrawString(component, font, Brushes::Black, System::Drawing::Rectangle(50, 50 + 40 * (i + 1), size.Width + 30, size.Height));
        }
       
    }
    vector<vector<int>> getConnectedComponents()
    {
        vector<vector<int>> componentes;
        int numComponentes = 0;
        int contador = 0;
        int i = 0;
        vector<int> temporal;
        while (contador < conComponents.size())
        {
            numComponentes = conComponents[contador];
            while (numComponentes > 0) {
                temporal.push_back(rowOrder[i++]);
                numComponentes--;
            }
            componentes.push_back(temporal);
            contador++;
            temporal.clear();
        }
        return componentes;
    }

    void matrizComponentes()
    {
        vector<vector<int>> componentes = getConnectedComponents();
        
        for (int i = 0; i < matrizAdyacencia.size(); i++) //va fila por fila
        {
            for (int k = 0; k < componentes.size(); k++)
            {
                int contador = 0;
                bool flag = false;
                while (contador < componentes.at(k).size()) //se busca en que componente conexa esta
                {
                    if (i == componentes.at(k).at(contador)) flag = true;
                    contador++;
                }
                if (flag) //si se encuentra donde esta
                {
                    for (int j = 0; j < matrizAdyacencia.size(); j++) //se cambian los datos
                    {
                        bool filaEnComponente = count(componentes.at(k).begin(), componentes.at(k).end(), j); //cuenta cuantas veces aparece el numero en un vector
                        //si no aparece ninguna vez: devuelve false porque será 0, sino dará 1 o más de una, osea true
                        if (!filaEnComponente) matrizAdyacencia.at(i).at(j) = 0; //si no esta en la componente (false) entonces lo vuelve true y lo cambia a 0 
                    } //modifica todas las filas
                }

            }
        }
    }

    vector<vector<bool>>* getMatrix()
    {
        return matriz;
    }

    vector<vector<bool>>* getPathMatrix()
    {
        return &matrizCaminos;
    }

    vector<vector<bool>>* getComponentMatrix()
    {
        return &matrizAdyacencia;
    }


};
#include <fstream>

#ifndef PISTA_H
#define PISTA_H

/** \brief generarPista
 *          generua una pista guardada desde un archivo de texto
 * \param char direccPista[TAM]
 * \param int colorPista
 * \param char matrizColis[ALTO_PANT][ANCHO_PANT]
 * \param int numFilas
 * \param int numColumnas
 */

void generarPista(char direccPista[TAM],int colorPista,char matrizColis[ALTO_PANT][ANCHO_PANT],int &numFilas,int &numColumnas)
{
    int i = 0,j = 0;
    char car;
    ifstream archPista;
    archPista.open(direccPista);
    while (archPista && archPista.get(car))
    {
        color(colorPista);
        gotoxy(i,j);
        cout << car;
        matrizColis[j][i] = car;
        if(car == '\n')
        {
            j++;
            i = 0;
        }
        else i++;

    }
    archPista.close();
    numFilas = j+1;
    numColumnas = i;
}

#endif // PISTA_H

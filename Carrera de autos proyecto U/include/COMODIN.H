#include <fstream>

#ifndef COMODIN_H
#define COMODIN_H

///Estructura para el comodin
typedef struct
{
    char apariencia;
    int color;
    int posX,posY;
    int duracionComodin;
}tipoComodin;

/** \brief dibujarComodin:
 *         dibuja una estrucutra tipoComodin en la consola
 * \param  estructura tipoComodin
 * \param  char pantallaColisiones[ALTO_PANT][ANCHO_PANT]
 */
 void dibujarComodin(tipoComodin comodin,char pantallaColisiones[ALTO_PANT][ANCHO_PANT])
 {
     color(comodin.color);
     gotoxy(comodin.posX,comodin.posY);
     cout << comodin.apariencia;
     pantallaColisiones[comodin.posY][comodin.posX] = 'C';
 }

/** \brief borrarComodin:
 *         borra una estrucutra tipoObstaculo ya dibujada en la consola
 * \param  estructura tipoObstaculo
 * \param char pantallaColisiones[ALTO_PANT][ANCHO_PANT]
 */
 void borrarComodin(tipoComodin comodin, char pantallaColisiones[ALTO_PANT][ANCHO_PANT])
 {
     gotoxy(comodin.posX,comodin.posY);
     cout << " ";
     pantallaColisiones[comodin.posY][comodin.posX] = ' ';
 }

  /** \brief generarUnComodinAleatorio:
 *         genera UN comodin junto con su matrz colision en una posicion aleatoria en la consola
 * \param  estructura tipoComodin
 * \param  char pantallaColisiones[ANCHO_PANT][ALTO_PANT]
 * \param  int rangoGenerIniX    }
 * \param  int rangoGenerFinX    }Indica una zona donde se desea que se generen los obstaculos
 * \param  int rangoGenerIniY    }
 * \param  int rangoGenerFinY    }
 */
void generarUnComodinAleatorio(tipoComodin &comodin, char pantallaColisiones[ALTO_PANT][ANCHO_PANT],int rangoGenerIniX,int rangoGenerFinX,int rangoGenerIniY,int rangoGenerFinY)
{
    srand(getpid());
    int posAleatObsX,posAleatObsY;
    do
    {
        posAleatObsX = rand () % (rangoGenerFinX - rangoGenerIniX + 1) + rangoGenerIniX;//Genera un numero aleatorio un un rango determinado
        posAleatObsY = rand () % (rangoGenerFinY - rangoGenerIniY + 1) + rangoGenerIniY;

    }while(pantallaColisiones[posAleatObsY][posAleatObsX] != ' ');//Impide que se genere un obstaculo en una posicion ya ocupada
    comodin.posX = posAleatObsX;
    comodin.posY = posAleatObsY;
    dibujarComodin(comodin,pantallaColisiones);
}
#endif // COMODIN_H

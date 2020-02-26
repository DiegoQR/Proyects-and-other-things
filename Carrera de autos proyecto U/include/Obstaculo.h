#ifndef OBSTACULO_H
#define OBSTACULO_H

///Estructura para el obstaculo
typedef struct
{
    char apariencia;
    int color;
    int posX,posY;
}tipoObstaculo;

/** \brief dibujarObstaculo:
 *         dibuja una estrucutra tipoObstaculo en la consola
 * \param  estructura tipoObstaculo
 * \param  char pantallaColisiones[ANCHO_PANT][ALTO_PANT]
 */
 void dibujarObstaculo(tipoObstaculo obstaculo,char pantallaColisiones[ALTO_PANT][ANCHO_PANT])
 {
     color(obstaculo.color);
     gotoxy(obstaculo.posX,obstaculo.posY);
     cout << obstaculo.apariencia;
     pantallaColisiones[obstaculo.posY][obstaculo.posX] = 'O';
 }

 /** \brief generarUnObstaculoAleatorio:
 *         genera UN obstaculo junto con su matrz colision en una posicion aleatoria en la consola
 * \param  estructura tipoAuto
 * \param  char pantallaColisiones[ANCHO_PANT][ALTO_PANT]
 * \param  int rangoGenerIniX    }
 * \param  int rangoGenerFinX    }Indica una zona donde se desea que se generen los obstaculos
 * \param  int rangoGenerIniY    }
 * \param  int rangoGenerFinY    }
 */
void generarUnObstaculoAleatorio(tipoObstaculo &obsPequenio, char pantallaColisiones[ALTO_PANT][ANCHO_PANT],int rangoGenerIniX,int rangoGenerFinX,int rangoGenerIniY,int rangoGenerFinY)
{
    srand(getpid());
    int posAleatObsX,posAleatObsY;
    do
    {
        posAleatObsX = rand () % (rangoGenerFinX - rangoGenerIniX + 1) + rangoGenerIniX;//Genera un numero aleatorio un un rango determinado
        posAleatObsY = rand () % (rangoGenerFinY - rangoGenerIniY + 1) + rangoGenerIniY;

    }while (pantallaColisiones[posAleatObsY][posAleatObsX] != ' ');//Impide que se genere un obstaculo en una posicion ya ocupada
    obsPequenio.posX = posAleatObsX;
    obsPequenio.posY = posAleatObsY;
    dibujarObstaculo(obsPequenio,pantallaColisiones);
}

#endif // OBSTACULO_H

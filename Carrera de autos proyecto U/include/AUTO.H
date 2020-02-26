#include <iostream>
#include <windows.h>

#define TAM 200
#define ANCHO_PANT 115
#define ALTO_PANT 30

#ifndef AUTO_H
#define AUTO_H

using namespace std;

///Estrucutra para el auto
typedef struct
{
    char apariencia;
    int color;
    char direcc;
    int velocidad,posX,posY;
    //Caracteristcas del auto cuando es inmune
    int tiempoInmunAct,tiempoInmunRest,cantComodinesConseg;
    int colorInmun;
}tipoAuto;

///PROCEDIMIENTOS Y FUNCIONES DEL AUTO

void color(WORD col)
{
   SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),col);
}
void gotoxy(short x, short y)
{
   COORD pos = { x, y };
   SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

/** \brief dibujarAuto:
 *         dibuja un auto en la consola
 * \param  estructura tipoAuto
 * \param  char pantallaColisiones[ANCHO_PANT][ALTO_PANT]
 */
void dibujarAuto(tipoAuto Auto,char pantallaColisiones[ALTO_PANT][ANCHO_PANT])
{
    //Dibuja el aspecto del auto en la consola
    color(Auto.color);
    gotoxy(Auto.posX,Auto.posY);
    cout << Auto.apariencia;
    //Dibuja el auto en la pantallaColisiones
    pantallaColisiones[Auto.posY][Auto.posX] = 'A';
}

/** \brief borrarAuto:
 *         borra una estrucutra tipoAuto ya dibujada en la consola
 * \param  estructura tipoAuto
 * \param  char pantallaColisiones[ANCHO_PANT][ALTO_PANT]
 */
void borrarAuto(tipoAuto Auto, char pantallaColisiones[ALTO_PANT][ANCHO_PANT])
{
    //Borra el aspecto del auto en la consola
    gotoxy(Auto.posX,Auto.posY);
    cout << " ";
    //Borra el auto en la pantallaColisiones
    pantallaColisiones[Auto.posY][Auto.posX] = ' ';
}

/** \brief AutoColisionaObstaculo
 *          procedimiento que se ejecuta si solo si el auto a colisonado con un obstaculo
 * \param  estructura tipoAuto
 * \param  int numDeVidasJugador
 * \param  char pantallaColisiones[ANCHO_PANT][ALTO_PANT]
 *
 */

void AutoColisionaObstaculo(tipoAuto Auto,int &numVidasJugador,char pantallaColisiones[ALTO_PANT][ANCHO_PANT])
{
     if(pantallaColisiones[Auto.posY][Auto.posX] == 'O')
     {
         numVidasJugador = numVidasJugador - 1;
     }
}

 /** \brief AutoColisionaComodin
 *          procedimiento que se ejecuta si el auto ha obtenido un comodin
 * \param  estructura tipoAuto
 * \param  char pantallaColisiones[ANCHO_PANT][ALTO_PANT]
 *
 */

void AutoColisionaComodin(tipoAuto &Auto,char pantallaColisiones[ALTO_PANT][ANCHO_PANT])
{
     if(pantallaColisiones[Auto.posY][Auto.posX] == 'C')
     {
         Auto.tiempoInmunAct = Auto.tiempoInmunRest;
         Auto.cantComodinesConseg ++;
     }
     if(Auto.tiempoInmunAct > 0)
     {
         Auto.color = Auto.colorInmun;
         Auto.tiempoInmunAct = Auto.tiempoInmunAct - 1;
     }
}
 /** \brief AutoLlegaAMeta
 *          procedimiento que se ejecuta si el auto ha llegado a la meta
 * \param  estructura tipoAuto
 * \param  char pantallaColisiones[ANCHO_PANT][ALTO_PANT]
 */

bool AutoLlegaAMeta(tipoAuto Auto,char pantallaColisiones[ALTO_PANT][ANCHO_PANT])
{
    bool autoLlegoMeta = false;
    if(pantallaColisiones[Auto.posY][Auto.posX] == '|')
    {
        autoLlegoMeta = true;
    }
    return autoLlegoMeta;
}

/** \brief moverAutoUnaPosicion:
 *         Mueve el auto una posicion segun la direccion que tenga
 * \param  estructura tipoAuto
 * \param int numVidas
 * \param bool autoLlegoMeta
 * \param  char pantallaColisiones[ANCHO_PANT][ALTO_PANT]
 */
void moverAutoUnaPosicion(tipoAuto &Auto,int &numVidas,bool &autoLlegoMeta,char pantallaColisiones[ALTO_PANT][ANCHO_PANT])
{
    dibujarAuto(Auto,pantallaColisiones);
    Sleep(Auto.velocidad);
    borrarAuto(Auto,pantallaColisiones);
    switch(Auto.direcc)
    {
    case 'r':
        if(pantallaColisiones[Auto.posY][Auto.posX+1] != 'x' && pantallaColisiones[Auto.posY][Auto.posX+1] != '/')Auto.posX++;
        break;
    case 'l':
        if(pantallaColisiones[Auto.posY][Auto.posX-1] != 'x')Auto.posX--;
        break;
    case 'u':
        if(pantallaColisiones[Auto.posY-1][Auto.posX] != 'x')Auto.posY--;
        break;
    case 'd':
        if(pantallaColisiones[Auto.posY+1][Auto.posX] != 'x')Auto.posY++;
        break;
    }
    //Detecta si el auto colisona con un objeto
    AutoColisionaComodin(Auto,pantallaColisiones);
    if(Auto.tiempoInmunAct <= 0)AutoColisionaObstaculo(Auto,numVidas,pantallaColisiones);
    autoLlegoMeta = AutoLlegaAMeta(Auto,pantallaColisiones);
    dibujarAuto(Auto,pantallaColisiones);
}
#endif // AUTO_H

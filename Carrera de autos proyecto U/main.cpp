#include <iostream>
#include <fstream>
#include <ctime>
#include <vector>
#include <conio.h>

#include "Auto.h"
#include "Obstaculo.h"
#include "Menu.h"
#include "Pista.h"
#include "COMODIN.H"


using namespace std;

///Estrucutra para el juego
typedef struct
{
    int dificultad,puntos,vidas,tiempo;
    int numObstaculos,numComodines,numSectores;
    bool jugadorPerdio,jugadorGano;
    //Colisiones
    char pantallaColisiones[ALTO_PANT][ANCHO_PANT];
    int numFilsMatCol,numColumnasMatCol;
}tipoJuego;

/** \brief instanteActual
 *          funcion que devuelve en su nombre el instante actual sacado del sistema operativo
 *  \return estructura tipoInstante
*/

tipoInstante regresarInstanteActual()
{
    tipoInstante instAct;
    time_t now = time(0);
    tm * time = localtime(&now);
    instAct.anio = 1900 + time->tm_year;
    instAct.mes = time->tm_mon + 1;
    instAct.dia = time->tm_mday;
    instAct.hora = time->tm_hour;
    instAct.minuto = time->tm_min;
    instAct.segundo = time->tm_sec;
    return instAct;
}

/** \brief mostrarInformacionJuego
 *          muestra la informacion del juego como ser vidas,tiempo,etc
 * \param estructura tipoAuto
 * \param estructura tipoJuego
 * \param int i: posicion X donde se dibuja
 * \param int j: posicion Y donde se dibuja
 */

void mostrarInformacionJuego(tipoAuto Auto,tipoJuego juego,int i,int j)
{
    gotoxy(i,j);color(15);
    cout <<"Vidas: "<< juego.vidas << "\tTiempo Inmunidad: "<< Auto.tiempoInmunAct <<endl;
    cout << "Tiempo: "<< juego.tiempo << "\tPulsa 't' para salir del juego" << "\tPulsa 'g' para guardar tu partida" << endl;
}

/** \brief generarObstaculosEnPista001
 *          procedimiento que genera una cantidad n de obstaculos en la pista
 * \param  estructura tipoObstaculo
 * \param  int numObstaculos
 * \param  int numSectores
 * \param  char pantallaColisiones[ANCHO_PANT][ALTO_PANT]
 */
 void generarObstaculosEnPista001(tipoObstaculo obs,int numObstaculos,int numSectores,char pantallaColisiones[ALTO_PANT][ANCHO_PANT])
 {
    for(int i = numObstaculos/numSectores;i >= 0;i--)
    {
        generarUnObstaculoAleatorio(obs,pantallaColisiones,1,104,19,25);
        generarUnObstaculoAleatorio(obs,pantallaColisiones,11,102,2,7);
        generarUnObstaculoAleatorio(obs,pantallaColisiones,1,29,8,18);
        generarUnObstaculoAleatorio(obs,pantallaColisiones,83,112,8,18);
    }
 }

 /** \brief generarComodinesEnPista001
 *          procedimiento que genera una cantidad n de comodines en la pista
 * \param  estructura tipoObstaculo
 * \param  int numComodines
 * \param  int numSectores
 * \param  char pantallaColisiones[ANCHO_PANT][ALTO_PANT]
 */
 void generarComodinesEnPista001(tipoComodin comod,int numComodines,int numSectores,char pantallaColisiones[ALTO_PANT][ANCHO_PANT])
 {
    for(int i = numComodines/numSectores;i >= 0;i--)
    {
        generarUnComodinAleatorio(comod,pantallaColisiones,1,104,19,25);
        generarUnComodinAleatorio(comod,pantallaColisiones,11,102,2,7);
        generarUnComodinAleatorio(comod,pantallaColisiones,1,29,8,18);
        generarUnComodinAleatorio(comod,pantallaColisiones,83,112,8,18);
    }
 }

 /** \brief calcularCantObsyComod
 *          calcula la cantidad de obstaculos y comodines en base a la dificultad seleccionada
 * \param   int dificultad
 * \return  int cantObstaculos
 * \return  int cantComodines
 *
 */
void calcularCantObsyComod(int dificultad,int &cantObstaculos,int &cantComodines)
{
    cantObstaculos = dificultad * 10;
    cantComodines = 10/dificultad;
}

/** \brief guardarPartida
 *          guerda la partida que actualmente esta jugando el jugador
 * \param   estructura tipoJuego
 */
void guardarPartida(tipoJuego juegoGuardar)
{
    int opcion;
    fstream archPartidasGuardadas;
    gotoxy(35,11);
    cout << "Desea guardar su partida 1.- Si\t2.-No: ";
    gotoxy(35,12);
    cin >> opcion;
    gotoxy(35,11);
    cout << "                                          ";
    gotoxy(35,12);
    cout << "         ";
    if(opcion == 1)
    {
        archPartidasGuardadas.open("saves.dat",ios::binary|ios::app|ios::out);

        tipoInstante instanateActual = regresarInstanteActual();
        archPartidasGuardadas.write((char *)&instanateActual,sizeof(instanateActual));
        archPartidasGuardadas.write((char *)&juegoGuardar,sizeof(juegoGuardar));

        archPartidasGuardadas.close();
    }
}

/** \brief cargarPartida
 *         carga una partida guardada en el archivo de saves.dat
 * \param estructura tipoInstante :instante de la partida que se quiere cargar(es el instante donde la partida se guardo antes)
 * \return estructura tipoJuego: el juego cargado del archivo
 *
 */
 void cargarPartida(tipoInstante instPartidaACargar,tipoJuego &juegoCargado)
 {
     tipoInstante instLeer;
     tipoJuego juegoLeer;
     ifstream archPartidasGuardadas;
     archPartidasGuardadas.open("saves.dat",ios::binary);
     archPartidasGuardadas.read((char *)&instLeer,sizeof(instLeer));
     archPartidasGuardadas.read((char *)&juegoLeer,sizeof(juegoLeer));
     while(!archPartidasGuardadas.eof() && archPartidasGuardadas)
     {
         if(instLeer.anio == instPartidaACargar.anio && instLeer.mes == instPartidaACargar.mes && instLeer.dia == instPartidaACargar.dia &&
            instLeer.hora == instPartidaACargar.hora && instLeer.minuto == instPartidaACargar.minuto && instLeer.segundo == instPartidaACargar.segundo)
         {
             juegoCargado = juegoLeer;
         }
         archPartidasGuardadas.read((char *)&instLeer,sizeof(instLeer));
         archPartidasGuardadas.read((char *)&juegoLeer,sizeof(juegoLeer));
     }
     archPartidasGuardadas.close();
 }

/** \brief cargarJuegoDesdeMatriz
 *          carga la posicion del auto,obstaculos y comodines desde una matriz
 * \param estructura tipoJuego
 * \param estructura tipoObstaculo
 * \param estructura tipoComodin
 * \param estructura tipoAuto
 */

 void cargarJuegoDesdeMatriz(tipoJuego juego,tipoObstaculo obs,tipoComodin comod,tipoAuto &Auto)
 {
     for(int i = 0;i < juego.numFilsMatCol;i++)
     {
         for(int j = 0;j < juego.numColumnasMatCol;j++)
         {
             if(juego.pantallaColisiones[i][j] == 'O')
             {
                 obs.posY = i;
                 obs.posX = j;
                 dibujarObstaculo(obs,juego.pantallaColisiones);
             }
             if(juego.pantallaColisiones[i][j] == 'C')
             {
                 comod.posY = i;
                 comod.posX = j;
                 dibujarComodin(comod,juego.pantallaColisiones);
             }
             if(juego.pantallaColisiones[i][j] == 'A')
             {
                 Auto.posY = i;
                 Auto.posX = j;
                 dibujarAuto(Auto,juego.pantallaColisiones);
             }

         }
     }

 }

/** \brief limpiarPantallaColisiones:
*         limpia la pantalla de colisones para que se reinicie todo
* \param  char pantallaColisiones[ANCHO_PANT][ALTO_PANT]
*/
void limpiarPantallaColisiones(char pantallaColisiones[ALTO_PANT][ANCHO_PANT])
{
    for(int i = 0;i < ALTO_PANT;i++)
    {
        for(int j = 0;j < ANCHO_PANT;j++)
        {
            pantallaColisiones[i][j] = ' ';
        }
    }
}

/** \brief iniciarJuego
 *          inicia el juego de las carreras
 * \param estructura tipoJuego
 * \param estructura tipoObstaculo
 * \param estructura tipoComodin
 * \param bool esJuegoNuevo : indica si e un juego nuevo o se ha cargado otro juego
 * \param estructura tipoInstante instCargar : envia el instante de la partida que se quiere cargar,si se quiere cargar una partida
 */

void iniciarJuego(tipoAuto &Auto, tipoObstaculo obs,tipoJuego &juego,tipoComodin comod,bool esJuegoNuevo,tipoInstante instCargar)
{
    int colorOrignalAuto = Auto.color;

    char tecla;

    system("cls");
    generarPista("G:\\2do Semestre\\Programacion I\\Proyecto Final Versiones\\Proyecto 0.5\\Interfaz\\Pista001.txt",15,juego.pantallaColisiones,juego.numFilsMatCol,juego.numColumnasMatCol);
    if(esJuegoNuevo)
    {
        calcularCantObsyComod(juego.dificultad,juego.numObstaculos,juego.numComodines);
        dibujarAuto(Auto,juego.pantallaColisiones);
        //Genera n obstaculos en toda la pista
        generarObstaculosEnPista001(obs,juego.numObstaculos,juego.numSectores,juego.pantallaColisiones);
        //Genera n comodines en toda la pista
        generarComodinesEnPista001(comod,juego.numComodines,juego.numSectores,juego.pantallaColisiones);
    }
    else
    {
        cargarPartida(instCargar,juego);
        cargarJuegoDesdeMatriz(juego,obs,comod,Auto);
    }

    do
    {
        if(Auto.tiempoInmunAct <= 0)Auto.color = colorOrignalAuto;
        tecla = _getch();
        if(tecla == 'w')Auto.direcc = 'u';
        if(tecla == 'a')Auto.direcc = 'l';
        if(tecla == 's')Auto.direcc = 'd';
        if(tecla == 'd')Auto.direcc = 'r';
        //guardar la partida
        if(tecla == 'g')guardarPartida(juego);
        while(!_kbhit() && !juego.jugadorPerdio && !juego.jugadorGano)
        {
            juego.tiempo++;
            if(juego.vidas <= 0) juego.jugadorPerdio = true;
            moverAutoUnaPosicion(Auto,juego.vidas,juego.jugadorGano,juego.pantallaColisiones);
            mostrarInformacionJuego(Auto,juego,0,ALTO_PANT-3);
        }

    }
    while(tecla !=  't' && !juego.jugadorPerdio && !juego.jugadorGano);
    //Calcula el puntaje en funcion de la dificultad,vidas y tiempo
    juego.puntos = (juego.dificultad * juego.vidas * Auto.cantComodinesConseg *100000)/juego.tiempo;
}



int main()
{
    bool salir,esJuegoNuevo;
    tipoInstante instPartidaCargar;

    tipoAuto Auto = {/*char apariencia = ▀* =*/223,/*int color=*/ 5,/*char direccion=*/ 'd',/*int velocidad=*/ 40,/*int posX=*/54,/*int posY=*/ 22,
    /*int tiempoInmunAct*/0,/*tiempoInmunRest*/100,/*cantComodinesConseg*/1,/*int colorInmun*/9};
    tipoComodin comd = {/*char apariencia = '©' =*/184,/*int color*/9,/*int posX*/0,/*int posY*/0};
    tipoObstaculo obsPequenio = {/*char apariencia*/'@',/*int color*/14,/*int posX*/0,/*posY*/0};
    tipoJuego juego = {/*dificultad*/1,/*puntos*/0,/*vidas*/5,/*tiempo*/0,/*numObstaculos*/0,/*numComodines*/0,/*numSectores*/4,/*jugadorPerdio*/false,/*jugadorGano*/false};
    tipoMenu menuDeVictoria = {/*direccion del archivo del menu*/"G:\\2do Semestre\\Programacion I\\Proyecto Final Versiones\\Proyecto 0.5\\Interfaz\\MenuVictoria.txt",/*color del Menu*/11};
    tipoMenu menuDeDerrota = {/*direccion del archivo del menu*/"G:\\2do Semestre\\Programacion I\\Proyecto Final Versiones\\Proyecto 0.5\\Interfaz\\MenuDerrota.txt",/*color del Menu*/4};
    tipoMenu menuDeInicio = {/*direccion del archivo del menu*/"G:\\2do Semestre\\Programacion I\\Proyecto Final Versiones\\Proyecto 0.5\\Interfaz\\MenuInicio.txt",/*color del Menu*/12};
    tipoMenu menuDeDificultad = {/*direccion del archivo del menu*/"G:\\2do Semestre\\Programacion I\\Proyecto Final Versiones\\Proyecto 0.5\\Interfaz\\MenuDificultad.txt",/*color del Menu*/12};


    limpiarPantallaColisiones(juego.pantallaColisiones);
    iniciarMenuDeInicio(menuDeInicio,menuDeDificultad,juego.dificultad,salir,esJuegoNuevo,instPartidaCargar);
    if(!salir)
    {
        iniciarJuego(Auto,obsPequenio,juego,comd,esJuegoNuevo,instPartidaCargar);

        if(juego.jugadorGano)
        {
            system("cls");
            generarMenu(menuDeVictoria);
            gotoxy(61,18);
            cout << juego.puntos << endl;
            gotoxy(61,19);
            cout << juego.vidas << endl;
            system("PAUSE");
        }
        else if (juego.jugadorPerdio)
        {
            system("cls");
            generarMenu(menuDeDerrota);
            gotoxy(76,14);
            cout << juego.puntos << endl;
            system("PAUSE");
        }
    }
}

#include <fstream>
#define MAX_PARTIDAS_GUARDADAS 50

#ifndef MENU_H
#define MENU_H

///Estructura para el instante
typedef struct
{
    int dia,mes,anio;
    int hora,minuto,segundo;

}tipoInstante;

///Estrucutra para leer el juego
typedef struct
{
    int dificultad,puntos,vidas,tiempo;
    int numObstaculos,numComodines,numSectores;
    bool jugadorPerdio,jugadorGano;
    char pantallaColisiones[ALTO_PANT][ANCHO_PANT];
    int numFilsMatCol,numColumnasMatCol;
}tipoJuegoLeer;

///Estructura para el menu
typedef struct
{
    char direccionArchivo[TAM];
    int color;
}tipoMenu;

/** \brief generarMenu
 *          genera en la consola un menu gardado desde un archivo de texto
 * \param   estructura tipoMenu
 */

void generarMenu(tipoMenu menu)
{
    int i = 0,j = 0;
    char car;
    ifstream archMenu;
    archMenu.open(menu.direccionArchivo);
    while (archMenu && archMenu.get(car))
    {
        gotoxy(i,j);
        color(menu.color);
        cout << car;
        if(car == '\n')
        {
            j++;
            i = 0;
        }
        else i++;
    }
    archMenu.close();

}

/** \brief iniciarMenuDeInicio
 *          inicia el menu de inicio para que el jugador pueda elegir si cargar partida,nueva partida y su dificultad o volver atras y salir
 * \param   estructura tipoMenu menuDeInicio
 * \param   estructura tipoMenu menuDificultad
 * \return  int dificultad seleccionada
 * \return  bool opcion salir del juego
 */
void iniciarMenuDeInicio(tipoMenu menuDeInicio,tipoMenu menuDificultad,int &dificultad,bool &salir,bool &esJuegoNuevo,tipoInstante &instCargarPartida)
{
    system("cls");
    int opcionJugador;
    generarMenu(menuDeInicio);
    cout << endl;
    cout << "Ingrese su opcion: ";
    cin >> opcionJugador;
    switch(opcionJugador)
    {
    case 1:
        {
            ///Inicia el menu de dificultad
            int opcionDificcultad;
            system("cls");
            generarMenu(menuDificultad);
            cout << endl;
            cout << "Ingrese su opcion: ";
            cin >> opcionJugador;
            switch(opcionJugador)
            {
            case 1: dificultad = 1;
                    esJuegoNuevo = true;
                break;
            case 2: dificultad = 5;
                    esJuegoNuevo = true;
                break;
            case 3: dificultad = 10;
                    esJuegoNuevo = true;
                break;
           case 4: iniciarMenuDeInicio(menuDeInicio,menuDificultad,dificultad,salir,esJuegoNuevo,instCargarPartida);
                break;
            default: iniciarMenuDeInicio(menuDeInicio,menuDificultad,dificultad,salir,esJuegoNuevo,instCargarPartida);
                break;
            }
        }
        break;
    case 2:
        {
            ///Inicia el menu de partidas guardadas
             tipoInstante listaInstPartGuardadas[MAX_PARTIDAS_GUARDADAS];
             tipoJuegoLeer leerJuego;
             int ind = 0,opcion;
             system("cls");
             ifstream archPartidasGuardadas;
             archPartidasGuardadas.open("saves.dat",ios::binary);
             cout << "0.-Salir" << endl;
             archPartidasGuardadas.read((char *)&listaInstPartGuardadas[ind],sizeof(listaInstPartGuardadas[ind]));
             archPartidasGuardadas.read((char *)&leerJuego,sizeof(leerJuego));
             while(!archPartidasGuardadas.eof())
             {
                 cout << ind+1 << ".-" << listaInstPartGuardadas[ind].dia << "/" << listaInstPartGuardadas[ind].mes << "/" << listaInstPartGuardadas[ind].anio << "\t"
                      << listaInstPartGuardadas[ind].hora << ":" << listaInstPartGuardadas[ind].minuto << ":" << listaInstPartGuardadas[ind].segundo << endl;
                 ind++;
                 archPartidasGuardadas.read((char *)&listaInstPartGuardadas[ind],sizeof(listaInstPartGuardadas[ind]));
                 archPartidasGuardadas.read((char *)&leerJuego,sizeof(leerJuego));
             }
             archPartidasGuardadas.close();
             cout << "Eliga su opcion: ";
             cin >> opcion;
             if(opcion > 0)
             {
                instCargarPartida = listaInstPartGuardadas[opcion-1];
                esJuegoNuevo = false;
             }
             else iniciarMenuDeInicio(menuDeInicio,menuDificultad,dificultad,salir,esJuegoNuevo,instCargarPartida);
        }
        break;
    case 3: salir = true;
        break;
    default: iniciarMenuDeInicio(menuDeInicio,menuDificultad,dificultad,salir,esJuegoNuevo,instCargarPartida);
        break;
    }
}



#endif // MENU_H

#ifndef COLISIONES_H
#define COLISIONES_H

/** \brief estaAutoChocandoPista
 *          devuelve verdadero si se detecta que el auto esta chocando con los limites de la pista
 * \param  tipo estructura tipoAuto
 * \return boleano true si detecta que ha colisonado con el borde de la pantalla
 */
bool estaAutoChocandoPista(tipoAuto Auto,char pantallaColisiones[ALTO_PANT][ANCHO_PANT])
{
    bool estaColision = false;
    if(pantallaColisiones[Auto.posY][Auto.posX+1] == 'x' ||
       pantallaColisiones[Auto.posY][Auto.posX-1] == 'x' ||
       pantallaColisiones[Auto.posY+1][Auto.posX] == 'x' ||
       pantallaColisiones[Auto.posY-1][Auto.posX] == 'x')
    {
        estaColision = true;
    }
    return estaColision;
}
/** \brief estaAutoChocandoObst
 *          devuelve verdadero si se detecta que el auto esta chocando con los limites de la pistaun obstaculo
 * \return boleano true si detecta que ha colisonado con el borde de la pantalla
 */

#endif // COLISIONES_H

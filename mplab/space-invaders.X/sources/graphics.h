/* 
 * File:   sprites.h
 * Author: mauro
 *
 * Created on June 5, 2021, 8:38 PM
 */

#ifndef SPRITES_H
#define	SPRITES_H

#ifdef	__cplusplus
extern "C" {
#endif

#ifdef	__cplusplus
}
#endif

#include "glcd.h"



#define siInit()    GLCD_Init()

/***************************************************************************************
 SIlanding() es el macro para hacer el landing page en la pantalla 128x64.
 * Se utiliza un macro porque sólo se usa una vez en el programa, para no gastar recursos con una funcion
 * front2 [] es el array que tiene el dibujo inicial
 * names [] es el array que tiene el dibujo con los nombres de los creadores
 ***************************************************************************************/

#define    siLanding(){ \
    GLCD_Clear();\
    GLCD_DisplayLogo(front2);\
    DELAY_sec(5);\
    GLCD_Clear();\
    GLCD_DisplayLogo(names);\
    DELAY_sec(5);\
    }

extern const unsigned char front2 [];
extern const unsigned char names [];





#endif	/* SPRITES_H */


/* 
 * File:   graphics.h
 * Author: mauro
 *
 * Created on June 18, 2021, 7:24 PM
 */

#ifndef GRAPHICS_H
#define	GRAPHICS_H

#include "t6963c.h"

#ifdef	__cplusplus
extern "C" {
#endif

    
enum invader_t{
    CHAR_BLANK_SPACE = 0,
    CHAR_INVADER_TYPE_0,
    CHAR_INVADER_TYPE_1,
    CHAR_INVADER_TYPE_2,
    CHAR_INVADER_TYPE_MAX,
    CHAR_BARRIER_EMPTY,
    CHAR_BARRIER_LOW,
    CHAR_BARRIER_MID,
    CHAR_BARRIER_FULL,
    CHAR_LASER,
    CHAR_SPACESHIP,
};



#define INVADER_RESOLUTION  0x8
#define INVADER_SIZE        0x2 
#define INVADER_FRAMES      0x2

#define INVADER_0_SYM       0x80
#define INVADER_0_ADD       (INVADER_0_SYM * INVADER_RESOLUTION)
#define INVADER_0_RR        11000

#define INVADER_1_SYM       ((INVADER_0_SYM + (INVADER_SIZE * INVADER_FRAMES)))
//#define INVADER_1_ADD       (INVADER_1_SYM * INVADER_RESOLUTION)
#define INVADER_1_RR        12000

#define INVADER_2_SYM       ((INVADER_1_SYM + (INVADER_SIZE * INVADER_FRAMES)))
//#define INVADER_2_ADD       (INVADER_2_SYM * INVADER_RESOLUTION)
#define INVADER_2_RR        13000


/**
 * Set the cursor address
 * @param address
 * @param sprite
 */
void t6963c_spaceInvaders_spriteInit();
void t6963c_spaceInvaders_draw(unsigned char row, unsigned char column, unsigned char character, unsigned short tick);

#ifdef	__cplusplus
}
#endif

#endif	/* GRAPHICS_H */


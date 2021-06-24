/* 
 * File:   graphics.h
 * Author: mauro
 *
 * Created on June 18, 2021, 7:24 PM
 */

#ifndef GRAPHICS_H
#define	GRAPHICS_H

#include "t6963c.h"
#include <stdbool.h>

#ifdef	__cplusplus
extern "C" {
#endif

    
enum character_type_t{
    CHAR_TYPE_BLANK_SPACE = 0,
    CHAR_TYPE_INVADER_0,
    CHAR_TYPE_INVADER_1,
    CHAR_TYPE_INVADER_2,
    CHAR_TYPE_INVADER_MAX,
    CHAR_TYPE_INVADER_LASER,
    CHAR_TYPE_BARRIER,
    CHAR_TYPE_SPACESHIP_LASER,
    CHAR_TYPE_SPACESHIP,
};

enum character_state_t{
    CHAR_STATE_NORMAL = 0,
    CHAR_STATE_HIT_1,
    CHAR_STATE_HIT_2,
    CHAR_STATE_DESTROYED,
    CHAR_STATE_DODGE,

    
};

enum character_movement_t{
    CHAR_MOV_LEFT = 0,
    CHAR_MOV_RIGHT,
    CHAR_MOV_UP,
    CHAR_MOV_DOWN,
};

enum character_speed_t{
    CHAR_SPEED_NORMAL = 0,
    CHAR_SPEED_FAST,
    CHAR_SPEED_ULTRA,
};

struct character_t {
    unsigned char type;
    //unsigned char size;
    //unsigned char frames;
    unsigned char state;
    unsigned char frames;
    
    //unsigned char offset_left;
    //unsigned char offset_right;  
    unsigned char prev_row;
    unsigned char prev_column;
    
    //unsigned char refresh_rate;
    unsigned char hit_counter;
    //bool movement_orientation;
    unsigned char movement_speed;
};


#define CHAR_RESOLUTION     0x8
#define CHAR_NO_DELETE      0x0
#define CHAR_LEFT_DELETE    0x1
#define CHAR_RIGHT_DELETE   0x2

#define INVADER_SIZE        0x2 
#define INVADER_FRAMES      0x2

#define INVADER_0_SYM       0x80
#define INVADER_0_ADD       (INVADER_0_SYM * CHAR_RESOLUTION)
#define INVADER_0_RR        10

#define INVADER_1_SYM       ((INVADER_0_SYM + (INVADER_SIZE * INVADER_FRAMES)))
//#define INVADER_1_ADD       (INVADER_1_SYM * INVADER_RESOLUTION)
#define INVADER_1_RR        20

#define INVADER_2_SYM       ((INVADER_1_SYM + (INVADER_SIZE * INVADER_FRAMES)))
//#define INVADER_2_ADD       (INVADER_2_SYM * INVADER_RESOLUTION)
#define INVADER_2_RR        30


#define SPACESHIP_SIZE      0x2
#define SPACESHIP_FRAMES    0x1

#define SPACESHIP_SYM       ((INVADER_2_SYM + (INVADER_SIZE * INVADER_FRAMES)))
#define SPACESHIP_ADD       (SPACESHIP_SYM * CHAR_RESOLUTION)
#define SPACESHIP_RR        10

#define LASER_SIZE          0x1
#define LASER_FRAMES        0x1

#define LASER_SYM           ((SPACESHIP_SYM + (SPACESHIP_SIZE * SPACESHIP_FRAMES)))
#define LASER_ADD           (LASER_SYM * CHAR_RESOLUTION)
#define LASER_RR            SPACESHIP_RR

#define BARRIER_SIZE        0x2
#define BARRIER_FRAMES      0x3

#define BARRIER_SYM         ((LASER_SYM + (LASER_SIZE * LASER_FRAMES)))
#define BARRIER_ADD         (BARRIER_SYM * CHAR_RESOLUTION)
#define BARRIER_RR          SPACESHIP_RR


/**
 * Set the cursor address
 * @param address
 * @param sprite
 */
void t6963c_spaceInvaders_spriteInit();
void t6963c_spaceInvaders_setCharacter(struct character_t* character, unsigned char type);
void t6963c_spaceInvaders_draw(char row, char column, struct character_t* character, unsigned short tick);

#ifdef	__cplusplus
}
#endif

#endif	/* GRAPHICS_H */


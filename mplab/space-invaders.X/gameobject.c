/*
 * File:   gameobject.c
 * Author: lward
 *
 * Created on 28 de junio de 2021, 08:39 AM
 */

#include "gameobject.h"

void init_game_object(struct gameobject *object, unsigned char x, unsigned char y, unsigned char Vx)
{
    (*object).x = x;
    (*object).y = y;
    (*object).Vx = Vx;
}

void update_game_object(struct gameobject *object, unsigned short tick)
{
    (*object).x = (*object).x + (*object).Vx * tick;
}

void render_spaceship(struct gameobject *object)
{
    t6963c_set_address((*object).y, (*object).x);
    t6963c_writeCmd1(t6963c_CMD_writeData_Increment, SPACESHIP_SYM);
    t6963c_writeCmd1(t6963c_CMD_writeData_Increment, SPACESHIP_SYM + 1);
}

void render_mothership(struct gameobject *object)
{
    t6963c_set_address((*object).y, (*object).x);
    t6963c_writeCmd1(t6963c_CMD_writeData_Increment, MOTHERSHIP_SYM);
    t6963c_writeCmd1(t6963c_CMD_writeData_Increment, MOTHERSHIP_SYM + 1);
}

void render_invader(struct gameobject *object)
{
    t6963c_set_address((*object).y, (*object).x);
    struct animationnode *animation_node = (*object).animation_node;
    t6963c_writeCmd1(t6963c_CMD_writeData_Increment, (*animation_node).symbol[0]);
    t6963c_writeCmd1(t6963c_CMD_writeData_Increment, (*animation_node).symbol[1]);
    (*object).animation_node = (*animation_node).next;
}

void animation_push(struct animationlist *list, struct animationnode *node)
{
    // Create the node
    struct animationnode *head = (*list).head;    
    // Check if the list is empty
    if((*list).size)
    {
        (*head).next = node;
        (*node).next = (*list).head;
    }else
    {
        (*list).head = node;
        (*node).next = node;
        (*list).size += 1;
    }

}
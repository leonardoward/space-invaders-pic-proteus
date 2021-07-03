/*
 * File:   gameobject.c
 * Author: lward
 *
 * Created on 28 de junio de 2021, 08:39 AM
 */

#include "gameobject.h"

void init_game_object(struct gameobject *object, char x, char y, char Vx)
{
    (*object).x = x;
    (*object).y = y;
    (*object).Vx = Vx;
}

void update_game_object(struct gameobject *object, char VxFactor, char dTick)
{
    // Store the previous value for x and y
    (*object).x_prev = (*object).x;
    (*object).y_prev = (*object).y;
    (*object).Vx *= VxFactor;
    // Calculate the new value for x
    (*object).x = (*object).x + (*object).Vx * dTick;
}

void render_spaceship(struct gameobject *object)
{
    t6963c_set_address((*object).y_prev, (*object).x_prev);
    t6963c_writeCmd1(t6963c_CMD_writeData_Increment, DATA_ZERO);
    t6963c_writeCmd1(t6963c_CMD_writeData_Increment, DATA_ZERO);
    t6963c_set_address((*object).y, (*object).x);
    t6963c_writeCmd1(t6963c_CMD_writeData_Increment, SPACESHIP_SYM);
    t6963c_writeCmd1(t6963c_CMD_writeData_Increment, SPACESHIP_SYM + 1);
}

void render_mothership(struct gameobject *object)
{
    t6963c_set_address((*object).y_prev, (*object).x_prev);
    t6963c_writeCmd1(t6963c_CMD_writeData_Increment, DATA_ZERO);
    t6963c_writeCmd1(t6963c_CMD_writeData_Increment, DATA_ZERO);
    t6963c_set_address((*object).y, (*object).x);
    t6963c_writeCmd1(t6963c_CMD_writeData_Increment, MOTHERSHIP_SYM);
    t6963c_writeCmd1(t6963c_CMD_writeData_Increment, MOTHERSHIP_SYM + 1);
}

void update_invader_list(struct alienlist *list, char dTick)
{
    if((*list).head)                           // Check if the list is not empty
    {
        struct aliennode *node = (*list).head;  // Get the head node
        struct gameobject *obj = (*node).alien; // Get the gamebject
        //char Vx = 0; 
        char VxFactor = 1;
        if((*obj).Vx > 0)   //The group is moving from left to right
        {
            // Check if the tail gets out of the screen
            node = (*list).tail;
            obj = (*node).alien;
            if((*obj).x + (*obj).Vx * dTick > XMAX)
            {
                VxFactor = -1;
            }
            node = (*list).head;
        } else if ((*obj).Vx < 0) //The group is moving from right to left
        {
            // Check if the head gets out of the screen
            if((*obj).x + (*obj).Vx * dTick < XMIN)
            {
                VxFactor = -1;
            }
        }
        (*node).update(node, VxFactor, dTick);             // Update the node
        while((*node).next){                    // While there are nodes left
            node = (*node).next;                // Get the node
            (*node).update(node, VxFactor, dTick);         // Update the node
        }
    }
}

void render_invader_list(struct alienlist *list)
{
    if((*list).head)                           // Check if the list is not empty
    {
        struct aliennode *node = (*list).head;  // Get the head node
        // Check if the group is moving to the right (Vx > 0) or to the
        // left (Vx < 0)
        struct gameobject *invader = (*node).alien;
        if((*invader).Vx > 0)   //The group is moving from left to right
        {
            // Start rendering from the Tail to the Head
            node = (*list).tail;
            (*node).render(node);                   // Render the node
            while((*node).prev){                    // While there are nodes left
                node = (*node).prev;                // Get the node
                (*node).render(node);               // Render the node
            }
        } else if ((*invader).Vx < 0) //The group is moving from right to left
        {
            // Start rendering from the Head to the Tail
            (*node).render(node);                   // Render the node
            while((*node).next){                    // While there are nodes left
                node = (*node).next;                // Get the node
                (*node).render(node);               // Render the node
            }
        } 
    }
}

void update_invader_node(struct aliennode *node, char VxFactor, char dTick)
{
    struct gameobject *invader = (*node).alien;
    (*invader).update(invader, VxFactor, dTick);
}

void render_invader_node(struct aliennode *node)
{
    struct gameobject *invader = (*node).alien;
    (*invader).render(invader);
}

void render_invader(struct gameobject *object)
{
    t6963c_set_address((*object).y_prev, (*object).x_prev);
    t6963c_writeCmd1(t6963c_CMD_writeData_Increment, DATA_ZERO);
    t6963c_writeCmd1(t6963c_CMD_writeData_Increment, DATA_ZERO);
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
        // The list not empty
        (*head).next = node;
        (*node).next = (*list).head;
        (*list).size += 1;
    }else
    {
        // The list is empty
        (*list).head = node;
        (*node).next = node;
        (*list).size += 1;
    }

}

void alien_push(struct alienlist *list, struct aliennode *node)
{
    // Create the node
    struct aliennode *tail = (*list).tail;    
    // Check if the list is empty
    if((*list).size)
    {
        // The list not empty
        (*tail).next = node;
        (*node).prev = (*list).tail;        
        (*list).tail = node; 
        (*list).size += 1;
    }else
    {
        // The list is empty
        (*list).head = node;
        (*list).tail = node;
        //(*node).next = node;
        (*list).size += 1;
    }

}
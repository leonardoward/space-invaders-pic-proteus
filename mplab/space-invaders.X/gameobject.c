/*
 * File:   gameobject.c
 * Author: lward
 *
 * Created on 28 de junio de 2021, 08:39 AM
 */

#include "gameobject.h"

/*-------------------------------------------------------------------------------
 ANIMATION LIST
-------------------------------------------------------------------------------*/

void animation_push(struct animationlist *list, struct animationnode *node)
{
    // Check if the list is empty
    if(list->size)
    {
        // The list not empty
        list->head->next = node;
        node->next = list->head;
        list->size += 1;
    }else
    {
        // The list is empty
        list->head = node;
        node->next = node;
        list->size += 1;
    }
}

/*-------------------------------------------------------------------------------
 GAME OBJECT
-------------------------------------------------------------------------------*/

void init_game_object(struct gameobject *object, char x, char y, char Vx, char Vy)
{
    object->x = x;
    object->y = y;
    object->Vx = Vx;
    object->Vy = Vy;
    object->isDead = 0;
}

void update_game_object(struct gameobject *object, char dTick)
{
    // Store the previous value for x and y
    object->x_prev = object->x;
    object->y_prev = object->y;
    // Calculate the new value for x and y
    object->x = object->x + object->Vx * dTick;
    object->y = object->y + object->Vy * dTick;
}

void update_spaceship_bullet(struct gameobject *object, char dTick)
{
    // Store the previous value for x and y
    object->x_prev = object->x;
    object->y_prev = object->y;
    // Calculate the new value for y
    if(object->y >= YMIN) object->y = object->y + object->Vy * dTick;
}

void render_spaceship(struct gameobject *object)
{
    t6963c_set_address(object->y_prev, object->x_prev);
    t6963c_writeCmd1(t6963c_CMD_writeData_Increment, DATA_ZERO);
    t6963c_writeCmd1(t6963c_CMD_writeData_Increment, DATA_ZERO);
    t6963c_set_address(object->y, object->x);
    t6963c_writeCmd1(t6963c_CMD_writeData_Increment, SPACESHIP_SYM);
    t6963c_writeCmd1(t6963c_CMD_writeData_Increment, SPACESHIP_SYM + 1);
}

void render_mothership(struct gameobject *object)
{
    t6963c_set_address(object->y_prev, object->x_prev);
    t6963c_writeCmd1(t6963c_CMD_writeData_Increment, DATA_ZERO);
    t6963c_writeCmd1(t6963c_CMD_writeData_Increment, DATA_ZERO);
    t6963c_set_address(object->y, object->x);
    t6963c_writeCmd1(t6963c_CMD_writeData_Increment, MOTHERSHIP_SYM);
    t6963c_writeCmd1(t6963c_CMD_writeData_Increment, MOTHERSHIP_SYM + 1);
}

void render_barrier(struct gameobject *object)
{
    t6963c_set_address(object->y, object->x);
    t6963c_writeCmd1(t6963c_CMD_writeData_Increment, BARRIER_SYM);
    t6963c_writeCmd1(t6963c_CMD_writeData_Increment, BARRIER_SYM + 1);
}

void render_invader(struct gameobject *object)
{
    t6963c_set_address(object->y_prev, object->x_prev);
    t6963c_writeCmd1(t6963c_CMD_writeData_Increment, DATA_ZERO);
    t6963c_writeCmd1(t6963c_CMD_writeData_Increment, DATA_ZERO);
    t6963c_set_address(object->y, object->x);
    if(!object->isDead)
    {
        t6963c_writeCmd1(t6963c_CMD_writeData_Increment, object->animation_node->symbol[0]);
        t6963c_writeCmd1(t6963c_CMD_writeData_Increment, object->animation_node->symbol[1]);
        object->animation_node = object->animation_node->next;
    }
    if(object->animation_node == object->explosion_node) object->isDead = 1;
}

void render_spaceship_bullet(struct gameobject *object)
{
    if(object->y_prev >= YMIN)
    {
        t6963c_set_address(object->y_prev, object->x_prev);
        t6963c_writeCmd1(t6963c_CMD_writeData_Increment, DATA_ZERO);
        t6963c_writeCmd1(t6963c_CMD_writeData_Increment, DATA_ZERO);
    }
    if((*object).y >= YMIN)
    {
        t6963c_set_address(object->y, object->x);
        struct animationnode *animation_node = object->animation_node;
        t6963c_writeCmd1(t6963c_CMD_writeData_Increment, animation_node->symbol[0]);
        object->animation_node = animation_node->next;
    }
}

void attack_spaceship(struct gameobject *object, struct gameobject *bullet){
    if(bullet->y < YMIN)
    {
        bullet->x = object->x;
        bullet->y = object->y - 1;
        bullet->Vy = -1;
    }
}

/*-------------------------------------------------------------------------------
 Map
-------------------------------------------------------------------------------*/

void mapInit(struct map *gameMap)
{
    int i, j;
    for(i=0; i<t6963c_columns; i++)
    {
        for(j=0; j<t6963c_rows; j++)
        {
            gameMap->pos[i][j].empty = 1;
        }
    }
}

void detectColision(struct map *gameMap, struct gameobject *object)
{
    struct gameobject *colisionObj = gameMap->setSinglePos(gameMap, object);
    if(colisionObj)
    {
        colisionObj->animation_node = colisionObj->explosion_node;
        object->y = -1;
    }
}

struct gameobject * mapSetSinglePos(struct map *gameMap, struct gameobject *object)
{
    struct gameobject *mapObject = gameMap->emptyObject;
    if(object->x_prev && object->y_prev)
    {
        gameMap->pos[(int)object->x_prev][(int)object->y_prev].empty = 1; // Empty
    }
    if(gameMap->pos[(int)object->x][(int)object->y].empty)  // It is empty
    {
        gameMap->pos[(int)object->x][(int)object->y].object = object;
        gameMap->pos[(int)object->x][(int)object->y].empty = 0; // Change to Not empty
    }
    else    // It is not empty
    {
        mapObject = gameMap->pos[(int)object->x][(int)object->y].object;
    }
    
    return mapObject;
}

struct gameobject * mapSetDoublePos(struct map *gameMap, struct gameobject *object)
{
    struct gameobject *mapObject = gameMap->emptyObject;
    if(object->x_prev && object->y_prev)
    {
        gameMap->pos[(int)object->x_prev][(int)object->y_prev].empty = 1; // Empty
        gameMap->pos[(int)object->x_prev + 1][(int)object->y_prev].empty = 1; // Empty
    }
    if(gameMap->pos[(int)object->x][(int)object->y].empty)  // It is empty
    {
        gameMap->pos[(int)object->x][(int)object->y].object = object;
        gameMap->pos[(int)object->x + 1][(int)object->y].object = object;
        gameMap->pos[(int)object->x][(int)object->y].empty = 0;     // Change to Not empty
        gameMap->pos[(int)object->x + 1][(int)object->y].empty = 0; // Change to Not empty
    }
    else    // It is not empty
    {
        mapObject = gameMap->pos[(int)object->x][(int)object->y].object;
    }
    
    return mapObject;
}

/*-------------------------------------------------------------------------------
 ALIEN NODE
-------------------------------------------------------------------------------*/

void update_invader_node(struct aliennode *node, char dTick)
{
    node->alien->update(node->alien, dTick);
}

void render_invader_node(struct aliennode *node)
{
    node->alien->render(node->alien);
}

/*-------------------------------------------------------------------------------
 ALIEN LIST
-------------------------------------------------------------------------------*/

void update_invader_list(struct alienlist *list, struct map *gameMap, char dTick)
{
    struct gameobject *colisionObj;
    if(list->headVertical)        // Check if the list is not empty
    {
        struct aliennode *node = list->headVertical;  // Get the head node
        //char Vx = 0; 
        if(node->alien->Vx > 0)           //The group is moving from left to right
        {
            // Check if the tail gets out of the screen
            node = list->tailVertical;
            if(node->alien->x + node->alien->Vx * dTick > XMAX)
            {
                list->borderColision = 1;
                list->render = list->renderHorizontal;
            }
            node = list->headVertical;
        } else if (node->alien->Vx < 0) //The group is moving from right to left
        {
            // Check if the head gets out of the screen
            if(node->alien->x + node->alien->Vx * dTick < XMIN)
            {
                list->borderColision = 1;
                list->render = list->renderHorizontal;
            }
        }
        
        if(list->borderColision)
        {
            node->alien->Vx *= -1;
            node->alien->Vy = 1;
            node->alien->Vx_prev = node->alien->Vx;
            node->alien->Vx = 0;
        }
        node->update(node, dTick);      // Update the node
        colisionObj = gameMap->setDoublePos(gameMap, node->alien);
        while(node->nextVertical){                // While there are nodes left
            node = node->nextVertical;            // Get the node
            if(list->borderColision)
            {
                node->alien->Vx *= -1;
                node->alien->Vy = 1;
                node->alien->Vx_prev = node->alien->Vx;
                node->alien->Vx = 0;
            }
            node->update(node, dTick);  // Update the node
            colisionObj = gameMap->setDoublePos(gameMap, node->alien);
        }
        list->borderColision = 0;
    }
}

void render_invader_vertical_list(struct alienlist *list)
{
    if(list->headVertical)                           // Check if the list is not empty
    {
        struct aliennode *node = list->headVertical;  // Get the head node
        // Check if the group is moving to the right (Vx > 0) or to the
        // left (Vx < 0)
        if(node->alien->Vx > 0)   //The group is moving from left to right
        {
            // Start rendering from the Tail to the Head
            node = list->tailVertical;
            node->render(node);               // Render the node
            while(node->prevVertical){        // While there are nodes left
                node = node->prevVertical;    // Get the node
                node->render(node);           // Render the node
            }
        } else if (node->alien->Vx <= 0) //The group is moving from right to left
        {
            // Start rendering from the Head to the Tail
            node->render(node);               // Render the node
            while(node->nextVertical){        // While there are nodes left
                node = node->nextVertical;    // Get the node
                node->render(node);               // Render the node
            }
        } 
    }
}

void render_invader_horizontal_list(struct alienlist *list)
{
    if(list->headHorizontal)                           // Check if the list is not empty
    {
        struct aliennode *node = list->headHorizontal;  // Get the head node
        // Check if the group is moving to the right (Vx > 0) or to the
        // left (Vx < 0)
        if(node->alien->Vy > 0)   //The group is moving from left to right
        {
            // Start rendering from the Tail to the Head
            node->render(node);               // Render the node
            node->alien->Vy = 0;
            node->alien->Vx = node->alien->Vx_prev;
            while(node->nextHorizontal){      // While there are nodes left
                node = node->nextHorizontal;  // Get the node
                node->render(node);           // Render the node
                node->alien->Vy = 0;
                node->alien->Vx = node->alien->Vx_prev;
            }
            list->render = list->renderVertical;
        } 
    }
}

void alien_push_vertical(struct alienlist *list, struct aliennode *node)
{
    // Check if the list is empty
    if(list->size)
    {
        // The list not empty
        list->tailVertical->nextVertical = node;
        node->prevVertical = list->tailVertical;        
        list->tailVertical = node; 
        list->size += 1;
    }else
    {
        // The list is empty
        list->headVertical = node;
        list->tailVertical = node;
        //(*node).next = node;
        list->size += 1;
    }
}

void alien_push_horizontal(struct alienlist *list, struct aliennode *node)
{
    // Check if the list is empty
    if(list->headHorizontal)
    {
        // The list not empty
        list->tailHorizontal->nextHorizontal = node;
        node->prevHorizontal = list->tailHorizontal;        
        list->tailHorizontal = node; 
        list->size += 1;
    }else
    {
        // The list is empty
        list->headHorizontal = node;
        list->tailHorizontal = node;
        //(*node).next = node;
        list->size += 1;
    }

}

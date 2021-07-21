/*
 * File:   gameobject.c
 * Author: lward
 *
 * Created on 28 de junio de 2021, 08:39 AM
 */

#include "gameobject.h"

/*-------------------------------------------------------------------------------
 ANIMATION NODE
-------------------------------------------------------------------------------*/
void setSecondaryNode(struct animationnode *nodeMain, struct animationnode *nodeSecondary)
{
    nodeMain->nextSecondary = nodeSecondary;
    nodeSecondary->next = nodeMain;
}

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

void init_game_object(struct gameobject *object, char id, char x, char y, char Vx, char Vy)
{
    object->x = x;
    object->y = y;
    object->Vx = Vx;
    object->Vy = Vy;
    object->state = INVADER_ALIVE;
    object->erasePrev = ERASE;
    object->id = id;
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
    t6963c_writeCmd1(t6963c_CMD_writeData_Increment, object->animation_node->symbol[0]);
    t6963c_writeCmd1(t6963c_CMD_writeData_Increment, object->animation_node->symbol[1]);
    object->animation_node = object->animation_node->next;   
}

void render_spaceship_bullet(struct gameobject *object)
{
    if(object->y_prev >= YMIN && object->erasePrev == ERASE)
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
        bullet->x_prev = object->x;
        bullet->y_prev = object->y;
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

struct mapnode * getMapNode(struct map *gameMap, char x, char y)
{
    struct mapnode *mapNode = NULL;
    if(gameMap->pos[(int)x][(int)y].object)
    {
        mapNode = &gameMap->pos[(int)x][(int)y];
    }
    return mapNode;
}

struct mapnode * mapSetSinglePos(struct map *gameMap, struct gameobject *object)
{
    struct mapnode *mapNode = NULL;
    if(object->x_prev && object->y_prev)
    {
        gameMap->pos[(int)object->x_prev][(int)object->y_prev].object = NULL; // Empty
        gameMap->pos[(int)object->x_prev][(int)object->y_prev].alienNode = NULL;
    }
    if(gameMap->pos[(int)object->x][(int)object->y].object)
    {
        mapNode = &gameMap->pos[(int)object->x][(int)object->y];
    }
    else
    {
        gameMap->pos[(int)object->x][(int)object->y].object = object;
    }
    
    return mapNode;
}

struct mapnode * mapSetDoublePos(struct map *gameMap, struct aliennode *alienNode, struct gameobject *object)
{
    struct mapnode *mapNode = NULL;
    if(object->x_prev && object->y_prev)
    {
        gameMap->pos[(int)object->x_prev][(int)object->y_prev].object = NULL; // Empty
        gameMap->pos[(int)object->x_prev][(int)object->y_prev].alienNode = NULL;
        gameMap->pos[(int)object->x_prev + 1][(int)object->y_prev].object = NULL; // Empty
        gameMap->pos[(int)object->x_prev + 1][(int)object->y_prev].alienNode = NULL;
    }
    if(gameMap->pos[(int)object->x][(int)object->y].object)
    {
        mapNode = &gameMap->pos[(int)object->x][(int)object->y];
    }
    else
    {
        gameMap->pos[(int)object->x][(int)object->y].object = object;
        gameMap->pos[(int)object->x][(int)object->y].alienNode = alienNode;
        gameMap->pos[(int)object->x + 1][(int)object->y].object = object;
        gameMap->pos[(int)object->x + 1][(int)object->y].alienNode = alienNode;
    }
    return mapNode;
}

/*-------------------------------------------------------------------------------
 Score
-------------------------------------------------------------------------------*/
void render_score(struct mapnode *invaderKilled, unsigned int *score){
    if(invaderKilled)
    {
        // Augment score
        switch(invaderKilled->object->id)
        {
            case ID_INVADER_0:
                *score += INVADER_0_POINTS;
                break;
            case ID_INVADER_1:
                *score += INVADER_1_POINTS;
                break;
            case ID_INVADER_2:
                *score += INVADER_2_POINTS;
                break;
            case ID_MOTHERSHIP:
                *score += MOTHERSHIP_POINTS;
                break;
            default:
                break;
        }
        
        // Show score
        t6963c_spaceInvaders_setStats(0, STAT_SCORE, *score);
    }    
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
    switch(node->alien->state)
    {
        case INVADER_ALIVE:
            node->alien->render(node->alien);
            break;
        case INVADER_EXPLOSION:
            node->alien->render(node->alien);
            node->alien->state = INVADER_DEAD;
            break;
        case INVADER_DEAD:
            // Erase alien
            t6963c_set_address(node->alien->y_prev, node->alien->x_prev);
            t6963c_writeCmd1(t6963c_CMD_writeData_Increment, DATA_ZERO);
            t6963c_writeCmd1(t6963c_CMD_writeData_Increment, DATA_ZERO);
            node->alien->state = INVADER_TO_REMOVE;
            break;
        default:
            break;
    } 
}

/*-------------------------------------------------------------------------------
 ALIEN LIST
-------------------------------------------------------------------------------*/

struct mapnode * detectColisionAlienList(struct alienlist *list, struct map *gameMap, struct gameobject *object)
{
    // Front Collision (Destroys invader)
    struct mapnode *directColisionNode = gameMap->getMapNode(gameMap, object->x, object->y);
    if(directColisionNode)
    {
        directColisionNode->object->animation_node = directColisionNode->object->explosion_node;
        directColisionNode->object->state = INVADER_EXPLOSION;
        object->y = -1;
        
    }
    // Side Collision (Change animation of invader)
    struct mapnode *sideColisionNode = gameMap->getMapNode(gameMap, object->x - 1, object->y);
    if(sideColisionNode)
    {
        object->animation_node->nextSecondary->symbol[0] = sideColisionNode->object->animation_node->nextSecondary->symbol[1];
        object->animation_node = object->animation_node->nextSecondary;
    }
    // Bottom Collision
    struct mapnode *bottomColisionNode = gameMap->getMapNode(gameMap, object->x_prev, object->y_prev);
    if(bottomColisionNode)
    {
        object->erasePrev = DO_NOT_ERASE;
    }
    else
    {
        object->erasePrev = ERASE;
    }
    
    return directColisionNode;
}

void update_invader_list(struct alienlist *list, struct map *gameMap, char dTick)
{
    struct mapnode *colisionNode;
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
        colisionNode = gameMap->setDoublePos(gameMap, node, node->alien);
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
            colisionNode = gameMap->setDoublePos(gameMap, node, node->alien);
        }
        list->borderColision = 0;
    }
}

void render_invader_vertical_list(struct alienlist *list, struct map *gameMap)
{
    if(list->headVertical)                           // Check if the list is not empty
    {
        struct aliennode *node = list->headVertical;  // Get the head node
        struct aliennode *nodeToRemove = NULL;  // Get the head node
        // Check if the group is moving to the right (Vx > 0) or to the
        // left (Vx < 0)
        if(node->alien->Vx > 0)   //The group is moving from left to right
        {
            // Start rendering from the Tail to the Head
            node = list->tailVertical;
            node->render(node);               // Render the node
            if(node->alien->state == INVADER_TO_REMOVE) nodeToRemove = node;
            while(node->prevVertical){        // While there are nodes left
                node = node->prevVertical;    // Get the node
                node->render(node);           // Render the node
                if(node->alien->state == INVADER_TO_REMOVE) nodeToRemove = node;
            }
        } else if (node->alien->Vx <= 0) //The group is moving from right to left
        {
            // Start rendering from the Head to the Tail
            node->render(node);               // Render the node
            if(node->alien->state == INVADER_TO_REMOVE) nodeToRemove = node;
            while(node->nextVertical){        // While there are nodes left
                node = node->nextVertical;    // Get the node
                node->render(node);           // Render the node
                if(node->alien->state == INVADER_TO_REMOVE) nodeToRemove = node;
            }
        } 
        if(nodeToRemove) list->pop(list, gameMap, nodeToRemove);
    }
}

void render_invader_horizontal_list(struct alienlist *list, struct map *gameMap)
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
            //if(node->alien->state == INVADER_TO_REMOVE) list->pop(list, gameMap, node);
            node->alien->Vy = 0;
            node->alien->Vx = node->alien->Vx_prev;
            while(node->nextHorizontal){      // While there are nodes left
                node = node->nextHorizontal;  // Get the node
                node->render(node);           // Render the node
                //if(node->alien->state == INVADER_TO_REMOVE) list->pop(list, gameMap, node);
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

void alien_pop(struct alienlist *list, struct map *gameMap, struct aliennode *node)
{
    // Horizontal list
    if(node->prevHorizontal) // If there is a previous node
    {
        // If there is a node that is next in the list
        if(node->nextHorizontal) // CASE : node is in the middle of the list
        {
            // The previous node points to the next node
            node->prevHorizontal->nextHorizontal = node->nextHorizontal;
            // The next node points to the previous node
            node->nextHorizontal->prevHorizontal = node->prevHorizontal;
        }
        else // CASE : node is the last one in the list
        {
            // The previous node becomes the last node in the list
            node->prevHorizontal->nextHorizontal = NULL;
            list->tailHorizontal = node->prevHorizontal;
        }
    }
    else // CASE : Node is the first node on the list
    {
        if(node->nextHorizontal) // CASE The list contains more than one node
        {
            // The next node becomes the first node in the list
            list->headHorizontal = node->nextHorizontal;
            node->nextHorizontal->prevHorizontal = NULL;
        }
        else
        {
            // node is the last one in the list, empty the list
            list->headHorizontal = NULL;
            list->tailHorizontal = NULL;
        }
    }
    // Remove the pointers for the horizontal list
    node->nextHorizontal = NULL;
    node->prevHorizontal = NULL;
    
    // Vertical list
    if(node->prevVertical) // If there is a previous node
    {
        // If there is a node that is next in the list
        if(node->nextVertical) // CASE : node is in the middle of the list
        {
            // The previous node points to the next node
            node->prevVertical->nextVertical = node->nextVertical;
            // The next node points to the previous node
            node->nextVertical->prevVertical = node->prevVertical;
        }
        else // CASE : node is the last one in the list
        {
            // The previous node becomes the last node in the list
            node->prevVertical->nextVertical = NULL;
            list->tailVertical = node->prevVertical;
        }
    }
    else // CASE : Node is the first node on the list
    {
        if(node->nextVertical) // CASE The list contains more than one node
        {
            // The next node becomes the first node in the list
            list->headVertical = node->nextVertical;
            node->nextVertical->prevVertical = NULL;
        }
        else
        {
            // node is the last one in the list, empty the list
            list->headVertical = NULL;
            list->tailVertical = NULL;
        }
    }
    // Remove the pointers for the vertical list
    node->nextVertical = NULL;
    node->prevVertical = NULL;
    
    // Remove alien from gamemap
    gameMap->pos[(int)node->alien->x][(int)node->alien->y].object = NULL;
    gameMap->pos[(int)node->alien->x+1][(int)node->alien->y].object = NULL;
    gameMap->pos[(int)node->alien->x][(int)node->alien->y].alienNode = NULL;
    gameMap->pos[(int)node->alien->x+1][(int)node->alien->y].alienNode = NULL;
    
}
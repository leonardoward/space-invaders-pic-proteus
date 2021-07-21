/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef XC_HEADER_TEMPLATE_H
#define	XC_HEADER_TEMPLATE_H

#include <xc.h> // include processor files - each processor file is guarded.  
// TODO Insert appropriate #include <>
#include "t6963c.h";
#include "graphics.h"
// TODO Insert C++ class definitions if appropriate

// TODO Insert declarations
#define XMAX 28
#define XMIN 0
#define YMIN 1
#define INVADER_ALIVE 0
#define INVADER_EXPLOSION 1
#define INVADER_DEAD 2
#define INVADER_TO_REMOVE 3

struct animationnode
{
   char symbol[2]; 
   struct animationnode *next;
   struct animationnode *nextSecondary;
   // Functions
   void (*setSecondaryNode)(struct animationnode *nodeMain, struct animationnode *nodeSecondary);
};

void setSecondaryNode(struct animationnode *nodeMain, struct animationnode *nodeSecondary);

/*-------------------------------------------------------------------------------
 ANIMATION LIST
-------------------------------------------------------------------------------*/

struct animationlist // Circular list
{
   // Parameters
   unsigned char size;
   struct animationnode *head;
   // Functions
   void (*push)(struct animationlist *list, struct animationnode *node);
};

void animation_push(struct animationlist *list, struct animationnode *node);

/*-------------------------------------------------------------------------------
 GAME OBJECT
-------------------------------------------------------------------------------*/

struct gameobject
{
   // Parameters
   char x; 
   char y;
   char x_prev; 
   char y_prev;
   char Vx;
   char Vy;
   char Vx_prev; 
   char Vy_prev;
   char state;
   struct animationnode *animation_node;
   struct animationnode *explosion_node;
   // Functions
   void (*init)(struct gameobject *object, char x, char y, char Vx, char Vy);
   void (*update)(struct gameobject *object, char dTick);  // Update design pattern
   void (*render)(struct gameobject *object);
   void (*attack)(struct gameobject *object, struct gameobject *bullet);
};

//typedef struct gameobject *GameObject;

void init_game_object(struct gameobject *object, char x, char y, char Vx, char Vy);

void update_game_object(struct gameobject *object, char dTick);

void update_spaceship_bullet(struct gameobject *object, char dTick);

void render_spaceship(struct gameobject *object);

void render_mothership(struct gameobject *object);

void render_barrier(struct gameobject *object);

void render_invader(struct gameobject *object);

void render_spaceship_bullet(struct gameobject *object);

void attack_spaceship(struct gameobject *object, struct gameobject *bullet);


/*-------------------------------------------------------------------------------
 Map
-------------------------------------------------------------------------------*/

struct mapnode
{
   // Parameters
   struct gameobject *object;
   struct aliennode *alienNode;
   unsigned char empty;
};

struct map
{
   // Parameters
   struct mapnode pos[t6963c_columns][t6963c_rows];
   //struct gameobject *emptyObject;
   // Functions
   void (*init) (struct map *gameMap);
   struct mapnode * (*getMapNode)(struct map *gameMap, char x, char y);
   struct mapnode * (*setSinglePos)(struct map *gameMap, struct gameobject *object);
   struct mapnode * (*setDoublePos)(struct map *gameMap, struct aliennode *alienNode, struct gameobject *object);
   
};

void mapInit(struct map *gameMap);
struct mapnode * getMapNode(struct map *gameMap, char x, char y);
struct mapnode * mapSetSinglePos(struct map *gameMap, struct gameobject *object);
struct mapnode * mapSetDoublePos(struct map *gameMap, struct aliennode *alienNode, struct gameobject *object);

/*-------------------------------------------------------------------------------
 ALIEN NODE
-------------------------------------------------------------------------------*/

struct aliennode
{
   struct gameobject *alien; 
   struct aliennode *nextVertical;
   struct aliennode *prevVertical;
   struct aliennode *nextHorizontal;
   struct aliennode *prevHorizontal;
   // Functions
   void (*update)(struct aliennode *node, char dTick);  // Update design pattern
   void (*render)(struct aliennode *node);
};

void update_invader_node(struct aliennode *node, char dTick);

void render_invader_node(struct aliennode *node);


/*-------------------------------------------------------------------------------
 ALIEN LIST
-------------------------------------------------------------------------------*/

struct alienlist // Circular list
{
   // Parameters
   unsigned char size;
   char borderColision;
   struct aliennode *headVertical;  // Vertical list
   struct aliennode *tailVertical;  // Vertical list
   struct aliennode *headHorizontal;  // Horizontal list
   struct aliennode *tailHorizontal;  // Horizontal list
   // Functions
   void (*pushVertical)(struct alienlist *list, struct aliennode *node);
   void (*pushHorizontal)(struct alienlist *list, struct aliennode *node);
   void (*pop)(struct alienlist *list, struct map *gameMap, struct aliennode *node);
   void (*update)(struct alienlist *list, struct map *gameMap, char dTick);  // Update design pattern
   void (*render)(struct alienlist *list, struct map *gameMap);
   void (*renderVertical)(struct alienlist *list, struct map *gameMap);
   void (*renderHorizontal)(struct alienlist *list, struct map *gameMap);
   void (*detectColision)(struct alienlist *list, struct map *gameMap, struct gameobject *object);
};

void alien_push_vertical(struct alienlist *list, struct aliennode *node);

void alien_push_horizontal(struct alienlist *list, struct aliennode *node);

void alien_pop(struct alienlist *list, struct map *gameMap, struct aliennode *node);

void update_invader_list(struct alienlist *list, struct map *gameMap, char dTick);

void render_invader_vertical_list(struct alienlist *list, struct map *gameMap);

void render_invader_horizontal_list(struct alienlist *list, struct map *gameMap);

void detectColisionAlienList(struct alienlist *list, struct map *gameMap, struct gameobject *object);

// Comment a function and leverage automatic documentation with slash star star
/**
    <p><b>Function prototype:</b></p>
  
    <p><b>Summary:</b></p>

    <p><b>Description:</b></p>

    <p><b>Precondition:</b></p>

    <p><b>Parameters:</b></p>

    <p><b>Returns:</b></p>

    <p><b>Example:</b></p>
    <code>
 
    </code>

    <p><b>Remarks:</b></p>
 */
// TODO Insert declarations or function prototypes (right here) to leverage 
// live documentation

#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

    // TODO If C++ is being used, regular C code needs function names to have C 
    // linkage so the functions can be used by the c code. 

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* XC_HEADER_TEMPLATE_H */


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

struct animationnode
{
   char symbol[2]; 
   struct animationnode *next;
};

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
   struct animationnode *animation_node;
   // Functions
   void (*init)(struct gameobject *object, char x, char y, char Vx, char Vy);
   void (*update)(struct gameobject *object, char VxFactor, char dTick);  // Update design pattern
   void (*render)(struct gameobject *object);
};

//typedef struct gameobject *GameObject;

void init_game_object(struct gameobject *object, char x, char y, char Vx, char Vy);

void update_game_object(struct gameobject *object, char VxFactor, char dTick);

void render_spaceship(struct gameobject *object);

void render_mothership(struct gameobject *object);

void render_invader(struct gameobject *object);

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
   void (*update)(struct aliennode *node, char VxFactor, char dTick);  // Update design pattern
   void (*render)(struct aliennode *node);
};

void update_invader_node(struct aliennode *node, char VxFactor, char dTick);

void render_invader_node(struct aliennode *node);

/*-------------------------------------------------------------------------------
 ALIEN LIST
-------------------------------------------------------------------------------*/

struct alienlist // Circular list
{
   // Parameters
   unsigned char size;
   struct aliennode *headVertical;  // Vertical list
   struct aliennode *tailVertical;  // Vertical list
   struct aliennode *headHorizontal;  // Horizontal list
   struct aliennode *tailHorizontal;  // Horizontal list
   // Functions
   void (*pushVertical)(struct alienlist *list, struct aliennode *node);
   void (*pushHorizontal)(struct alienlist *list, struct aliennode *node);
   void (*pop)(struct alienlist *list, struct aliennode *node);
   void (*update)(struct alienlist *list, char dTick);  // Update design pattern
   void (*renderVertical)(struct alienlist *list);
   void (*renderHorizontal)(struct alienlist *list);
};

void alien_push_vertical(struct alienlist *list, struct aliennode *node);

void alien_push_horizontal(struct alienlist *list, struct aliennode *node);

void alien_pop(struct alienlist *list, struct aliennode *node);

void update_invader_list(struct alienlist *list, char dTick);

void render_invader_vertical_list(struct alienlist *list);

void render_invader_horizontal_list(struct alienlist *list);

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


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

struct animationnode
{
   char symbol[2]; 
   struct animationnode *next;
};

struct animationlist // Circular list
{
   // Parameters
   unsigned char size;
   struct animationnode *head;
   // Functions
   void (*push)(struct animationlist *list, struct animationnode *node);
};

void animation_push(struct animationlist *list, struct animationnode *node);

struct gameobject
{
   // Parameters
   unsigned char x; 
   unsigned char y;
   unsigned char Vx;
   struct animationnode *animation_node;
   // Functions
   void (*init)(struct gameobject *object, unsigned char x, unsigned char y, unsigned char Vx);
   void (*update)(struct gameobject *object, unsigned short tick);  // Update design pattern
   void (*render)(struct gameobject *object);
};

//typedef struct gameobject *GameObject;

void init_game_object(struct gameobject *object, unsigned char x, unsigned char y, unsigned char Vx);

void update_game_object(struct gameobject *object, unsigned short tick);

void render_spaceship(struct gameobject *object);

void render_mothership(struct gameobject *object);

void render_invader(struct gameobject *object);



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


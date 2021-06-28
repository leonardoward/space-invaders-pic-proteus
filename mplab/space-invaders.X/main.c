/*-------------------------------------------------------------------------------
  HEADER FILES
  NOTE: The processor specific header file is not required since we will not
  be using any processor specific features - this is all generic C code
-------------------------------------------------------------------------------*/
#include <xc.h>             // Processor specific header file
#include "mcc_generated_files/system.h"
//#include "LCD.h"          // include LCD driver source file
#include "t6963c.h"         // include LCD driver source file
#include "graphics.h"    
#include "gameobject.h"  
/*-------------------------------------------------------------------------------
  VARIABLE DECLARATIONS
-------------------------------------------------------------------------------*/
#define ALIENS_PER_ROW 11
/*-------------------------------------------------------------------------------
  FUNCTION PROTOTYPES
-------------------------------------------------------------------------------*/

/*===============================================================================
  FUNCTION:     main()
  DESCRIPTION:  
  PARAMETERS:   none
  RETURNS:      nothing
  REQUIREMENTS: none  
===============================================================================*/
int main(void)
{
    // Initialize the device
    SYSTEM_Initialize();
    
    // Initialice the t6963 library
    t6963c_init();
    t6963c_spaceInvaders_spriteInit();  
    //t6963c_spaceInvaders_setLanding();
    t6963c_spaceInvaders_setStats(1, STAT_SCORE, 0);
    t6963c_spaceInvaders_setStats(1, STAT_LIVES, 3);
    //t6963c_spaceInvaders_setStats(1, STAT_GAMEOVER, 0);
    /*--------------------------------------------------------------------------
     Component Declarations
	--------------------------------------------------------------------------*/
    // Animation Nodes
    struct animationnode invader0_node0;
    struct animationnode invader0_node1;
    struct animationnode invader1_node0;
    struct animationnode invader1_node1;
    struct animationnode invader2_node0;
    struct animationnode invader2_node1;
    
    // Animation Lists
    struct animationlist invader0_animation;
    struct animationlist invader1_animation;
    struct animationlist invader2_animation;
    
    //Game Objects
    struct gameobject spaceship;
    struct gameobject mothership;
    struct gameobject invader0[ALIENS_PER_ROW*2];
    struct gameobject invader1[ALIENS_PER_ROW*2];
    struct gameobject invader2[ALIENS_PER_ROW*2];
    
    unsigned char i=0;
    
    /*--------------------------------------------------------------------------
     Component Initialization
	--------------------------------------------------------------------------*/
    
    // Animation Nodes
    invader0_node0.symbol[0] = INVADER_0_SYM;
    invader0_node0.symbol[1] = INVADER_0_SYM + 1;
    invader0_node1.symbol[0] = INVADER_0_SYM + 4;
    invader0_node1.symbol[1] = INVADER_0_SYM + 5;
    
    invader1_node0.symbol[0] = INVADER_1_SYM;
    invader1_node0.symbol[1] = INVADER_1_SYM + 1;
    invader1_node1.symbol[0] = INVADER_1_SYM + 4;
    invader1_node1.symbol[1] = INVADER_1_SYM + 5;
    
    invader2_node0.symbol[0] = INVADER_2_SYM;
    invader2_node0.symbol[1] = INVADER_2_SYM + 1;
    invader2_node1.symbol[0] = INVADER_2_SYM + 4;
    invader2_node1.symbol[1] = INVADER_2_SYM + 5;
    
    // Animation Lists  
    invader0_animation.size = 0;
    invader0_animation.push = animation_push;
    invader0_animation.push(&invader0_animation, &invader0_node0);
    invader0_animation.push(&invader0_animation, &invader0_node1);
       
    invader1_animation.size = 0;
    invader1_animation.push = animation_push;
    invader1_animation.push(&invader1_animation, &invader1_node0);
    invader1_animation.push(&invader1_animation, &invader1_node1);

    invader2_animation.size = 0;
    invader2_animation.push = animation_push;
    invader2_animation.push(&invader2_animation, &invader2_node0);
    invader2_animation.push(&invader2_animation, &invader2_node1);

    //Game Objects
    
    // Spaceship (Player)
    spaceship.init = init_game_object;   
    spaceship.update = update_game_object;
    spaceship.render = render_spaceship;  
    spaceship.init(&spaceship, 14, 14, 0);
    
    mothership.init = init_game_object;   
    mothership.update = update_game_object;
    mothership.render = render_mothership;  
    mothership.init(&mothership, 7, 2, 0);
    
    for(i=0; i<ALIENS_PER_ROW; i++){
        // Invader 0
        invader0[i].init = init_game_object;   
        invader0[i].update = update_game_object;
        invader0[i].render = render_invader;      
        invader0[ALIENS_PER_ROW+i].init = init_game_object;   
        invader0[ALIENS_PER_ROW+i].update = update_game_object;
        invader0[ALIENS_PER_ROW+i].render = render_invader;
        
        invader0[i].init(&invader0[i], i*2, 8, 0);
        invader0[i].animation_node = invader0_animation.head;
        invader0[ALIENS_PER_ROW+i].init(&invader0[ALIENS_PER_ROW+i], i*2, 9, 0);
        invader0[ALIENS_PER_ROW+i].animation_node = invader0_animation.head;
        
        // Invader 1
        invader1[i].init = init_game_object;   
        invader1[i].update = update_game_object;
        invader1[i].render = render_invader;       
        invader1[ALIENS_PER_ROW+i].init = init_game_object;   
        invader1[ALIENS_PER_ROW+i].update = update_game_object;
        invader1[ALIENS_PER_ROW+i].render = render_invader;
        
        invader1[i].init(&invader1[i], i*2, 6, 0);
        invader1[i].animation_node = invader1_animation.head;
        invader1[ALIENS_PER_ROW+i].init(&invader1[ALIENS_PER_ROW+i], i*2, 7, 0);
        invader1[ALIENS_PER_ROW+i].animation_node = invader1_animation.head;
        
        // Invader 2
        invader2[i].init = init_game_object;   
        invader2[i].update = update_game_object;
        invader2[i].render = render_invader;      
        invader2[ALIENS_PER_ROW+i].init = init_game_object;   
        invader2[ALIENS_PER_ROW+i].update = update_game_object;
        invader2[ALIENS_PER_ROW+i].render = render_invader;   
        
        invader2[i].init(&invader2[i], i*2, 4, 0);
        invader2[i].animation_node = invader2_animation.head;
        invader2[ALIENS_PER_ROW+i].init(&invader2[ALIENS_PER_ROW+i], i*2, 5, 0);
        invader2[ALIENS_PER_ROW+i].animation_node = invader2_animation.head;
    }
    
    
    /*--------------------------------------------------------------------------
     Game Loop - Design Pattern
     * 
     * A game loop runs continuously during gameplay. Each turn of the loop, it
     * processes user input without blocking, updates the game state, and 
     * renders the game. 
     * It tracks the passage of time to control the rate of gameplay.
	--------------------------------------------------------------------------*/
    unsigned short tick = 0;
    
    //unsigned short previous = tick;                // Get the current time
    //unsigned short current = 0;                  // Get the current time
    //unsigned short elapsed = 0;                  // Get the current time
    //unsigned short lag = 0;
    
    while (1)
    {
        //current = tick;
        //elapsed = current - previous; 
        //previous = current;
        //lag += elapsed;
        
        /*----------------------------------------------------------------------
         Inputs
        ----------------------------------------------------------------------*/
        
        
        /*----------------------------------------------------------------------
         Updates
        ----------------------------------------------------------------------*/
        spaceship.update(&spaceship, tick);
        mothership.update(&mothership, tick);
        for(i=0; i<ALIENS_PER_ROW*2; i++){
            invader0[i].update(&invader0[i], tick);
            invader1[i].update(&invader1[i], tick);
            invader2[i].update(&invader2[i], tick);
        }
        
        /*----------------------------------------------------------------------
         Render
        ----------------------------------------------------------------------*/    
        if((tick % 1) == 0){ 
            //t6963c_spaceInvaders_draw( 8 , 20, &invader); //lateral % 15
            spaceship.render(&spaceship);
            mothership.render(&mothership);
            for(i=0; i<ALIENS_PER_ROW; i++){
                invader2[i].render(&invader2[i]);
                invader2[ALIENS_PER_ROW+i].render(&invader2[ALIENS_PER_ROW+i]);
                invader1[i].render(&invader1[i]);
                invader1[ALIENS_PER_ROW+i].render(&invader1[ALIENS_PER_ROW+i]);
                invader0[i].render(&invader0[i]);
                invader0[ALIENS_PER_ROW+i].render(&invader0[ALIENS_PER_ROW+i]); 
            }
        }
        tick++;
    }

    return 1;
}
/**
 End of File
*/


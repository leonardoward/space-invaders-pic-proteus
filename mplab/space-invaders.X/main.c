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
#define INVADER_VX_INIT 1
#define INVADER_ROW_START 4
#define SPACESHIP_X_INIT 14
#define SPACESHIP_Y_INIT 14
#define SPACESHIP_VX_INIT 1
#define MOTHERSHIP_X_INIT 7
#define MOTHERSHIP_Y_INIT 2
#define MOTHERSHIP_VX_INIT 0

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
    struct animationnode invader0_animation_node0;
    struct animationnode invader0_animation_node1;
    struct animationnode invader1_animation_node0;
    struct animationnode invader1_animation_node1;
    struct animationnode invader2_animation_node0;
    struct animationnode invader2_animation_node1;
    
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
    
    // Invader list
    struct alienlist invaders_alive;
    
    struct aliennode invader0_node[ALIENS_PER_ROW*2];
    struct aliennode invader1_node[ALIENS_PER_ROW*2];
    struct aliennode invader2_node[ALIENS_PER_ROW*2];
    
    unsigned char i=0;
    
    /*--------------------------------------------------------------------------
     Component Initialization
	--------------------------------------------------------------------------*/
    
    // Invaders alive list
    invaders_alive.size = 0;
    invaders_alive.push = alien_push;
    invaders_alive.update = update_invader_list;
    invaders_alive.render = render_invader_list;
    
    // Animation Nodes
    invader0_animation_node0.symbol[0] = INVADER_0_SYM;
    invader0_animation_node0.symbol[1] = INVADER_0_SYM + 1;
    invader0_animation_node1.symbol[0] = INVADER_0_SYM + 4;
    invader0_animation_node1.symbol[1] = INVADER_0_SYM + 5;
    
    invader1_animation_node0.symbol[0] = INVADER_1_SYM;
    invader1_animation_node0.symbol[1] = INVADER_1_SYM + 1;
    invader1_animation_node1.symbol[0] = INVADER_1_SYM + 4;
    invader1_animation_node1.symbol[1] = INVADER_1_SYM + 5;
    
    invader2_animation_node0.symbol[0] = INVADER_2_SYM;
    invader2_animation_node0.symbol[1] = INVADER_2_SYM + 1;
    invader2_animation_node1.symbol[0] = INVADER_2_SYM + 4;
    invader2_animation_node1.symbol[1] = INVADER_2_SYM + 5;
    
    // Animation Lists  
    invader0_animation.size = 0;
    invader0_animation.push = animation_push;
    invader0_animation.push(&invader0_animation, &invader0_animation_node0);
    invader0_animation.push(&invader0_animation, &invader0_animation_node1);
       
    invader1_animation.size = 0;
    invader1_animation.push = animation_push;
    invader1_animation.push(&invader1_animation, &invader1_animation_node0);
    invader1_animation.push(&invader1_animation, &invader1_animation_node1);

    invader2_animation.size = 0;
    invader2_animation.push = animation_push;
    invader2_animation.push(&invader2_animation, &invader2_animation_node0);
    invader2_animation.push(&invader2_animation, &invader2_animation_node1);

    //Game Objects
    
    // Spaceship (Player)
    spaceship.init = init_game_object;   
    spaceship.update = update_game_object;
    spaceship.render = render_spaceship;  
    spaceship.init(&spaceship, SPACESHIP_X_INIT, SPACESHIP_Y_INIT, SPACESHIP_VX_INIT);
    
    // Mothership
    mothership.init = init_game_object;   
    mothership.update = update_game_object;
    mothership.render = render_mothership;  
    mothership.init(&mothership, MOTHERSHIP_X_INIT, MOTHERSHIP_Y_INIT, MOTHERSHIP_VX_INIT);
    
    
    for(i=0; i<ALIENS_PER_ROW; i++){
        // Invader 0 First Row
        invader0[i].init = init_game_object;   
        invader0[i].update = update_game_object;
        invader0[i].render = render_invader;      
        invader0[i].init(&invader0[i], i*2, INVADER_ROW_START+5, INVADER_VX_INIT);
        invader0[i].animation_node = invader0_animation.head;    
        invader0_node[i].alien = &invader0[i];
        invader0_node[i].update = update_invader_node;
        invader0_node[i].render = render_invader_node;
        invaders_alive.push(&invaders_alive, &invader0_node[i]);
         
        // Invader 0 Second Row
        invader0[ALIENS_PER_ROW+i].init = init_game_object;   
        invader0[ALIENS_PER_ROW+i].update = update_game_object;
        invader0[ALIENS_PER_ROW+i].render = render_invader;
        invader0[ALIENS_PER_ROW+i].init(&invader0[ALIENS_PER_ROW+i], i*2, INVADER_ROW_START+4, INVADER_VX_INIT);
        invader0[ALIENS_PER_ROW+i].animation_node = invader0_animation.head;
        invader0_node[ALIENS_PER_ROW + i].alien = &invader0[ALIENS_PER_ROW+i];
        invader0_node[ALIENS_PER_ROW + i].update = update_invader_node;
        invader0_node[ALIENS_PER_ROW + i].render = render_invader_node;
        invaders_alive.push(&invaders_alive, &invader0_node[ALIENS_PER_ROW + i]);
        
        // Invader 1 Third Row
        invader1[i].init = init_game_object;   
        invader1[i].update = update_game_object;
        invader1[i].render = render_invader;
        invader1[i].init(&invader1[i], i*2, INVADER_ROW_START+3, INVADER_VX_INIT);
        invader1[i].animation_node = invader1_animation.head;
        invader1_node[i].alien = &invader1[i]; 
        invader1_node[i].update = update_invader_node;
        invader1_node[i].render = render_invader_node;
        invaders_alive.push(&invaders_alive, &invader1_node[i]);
        
        // Invader 1 Fourth Row
        invader1[ALIENS_PER_ROW+i].init = init_game_object;   
        invader1[ALIENS_PER_ROW+i].update = update_game_object;
        invader1[ALIENS_PER_ROW+i].render = render_invader;
        invader1[ALIENS_PER_ROW+i].init(&invader1[ALIENS_PER_ROW+i], i*2, INVADER_ROW_START+2, INVADER_VX_INIT);
        invader1[ALIENS_PER_ROW+i].animation_node = invader1_animation.head;
        invader1_node[ALIENS_PER_ROW + i].alien = &invader1[ALIENS_PER_ROW+i]; 
        invader1_node[ALIENS_PER_ROW + i].update = update_invader_node;
        invader1_node[ALIENS_PER_ROW + i].render = render_invader_node;
        invaders_alive.push(&invaders_alive, &invader1_node[ALIENS_PER_ROW + i]);
        
        // Invader 2 Fifth Row
        invader2[i].init = init_game_object;   
        invader2[i].update = update_game_object;
        invader2[i].render = render_invader;      
        invader2[i].init(&invader2[i], i*2, INVADER_ROW_START+1, INVADER_VX_INIT);
        invader2[i].animation_node = invader2_animation.head;
        invader2_node[i].alien = &invader2[i];  
        invader2_node[i].update = update_invader_node;
        invader2_node[i].render = render_invader_node;
        invaders_alive.push(&invaders_alive, &invader2_node[i]);  
        
        // Invader 2 Sixth Row
        invader2[ALIENS_PER_ROW+i].init = init_game_object;   
        invader2[ALIENS_PER_ROW+i].update = update_game_object;
        invader2[ALIENS_PER_ROW+i].render = render_invader;   
        invader2[ALIENS_PER_ROW+i].init(&invader2[ALIENS_PER_ROW+i], i*2, INVADER_ROW_START, INVADER_VX_INIT);
        invader2[ALIENS_PER_ROW+i].animation_node = invader2_animation.head;
        invader2_node[ALIENS_PER_ROW + i].alien = &invader2[ALIENS_PER_ROW+i];
        invader2_node[ALIENS_PER_ROW + i].update = update_invader_node;
        invader2_node[ALIENS_PER_ROW + i].render = render_invader_node;
        invaders_alive.push(&invaders_alive, &invader2_node[ALIENS_PER_ROW + i]);
    }
    
    
    /*--------------------------------------------------------------------------
     Game Loop - Design Pattern
     * 
     * A game loop runs continuously during gameplay. Each turn of the loop, it
     * processes user input without blocking, updates the game state, and 
     * renders the game. 
     * It tracks the passage of time to control the rate of gameplay.
	--------------------------------------------------------------------------*/
    int previousTick = 0;           // Get the previous tick
    int currentTick = 0;            // Get the current tick
    char elapsed = 0;               // Get the time difference
    //unsigned short lag = 0;
    
    while (1)
    {
        elapsed = (char)(currentTick - previousTick); 
        previousTick = currentTick;
        //lag += elapsed;
        
        /*----------------------------------------------------------------------
         Inputs
        ----------------------------------------------------------------------*/
        
        
        /*----------------------------------------------------------------------
         Updates
        ----------------------------------------------------------------------*/
        spaceship.update(&spaceship, 1, elapsed);
        mothership.update(&mothership, 1, elapsed);
        invaders_alive.update(&invaders_alive, elapsed);
        /*----------------------------------------------------------------------
         Render
        ----------------------------------------------------------------------*/    
        if((currentTick % 1) == 0){ 
            //t6963c_spaceInvaders_draw( 8 , 20, &invader); //lateral % 15
            spaceship.render(&spaceship);
            mothership.render(&mothership);
            invaders_alive.render(&invaders_alive);
        }
        currentTick++;
    }

    return 1;
}
/**
 End of File
*/


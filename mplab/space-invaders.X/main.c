/*-------------------------------------------------------------------------------
  HEADER FILES
  NOTE: The processor specific header file is not required since we will not
  be using any processor specific features - this is all generic C code
-------------------------------------------------------------------------------*/
#include <xc.h>             // Processor specific header file
#include "mcc_generated_files/system.h"
#include "mcc_generated_files/pin_manager.h"
#include "mcc_generated_files/ext_int.h"
#include "mcc_generated_files/mcc.h"


//#include "LCD.h"          // include LCD driver source file
#include "t6963c.h"         // include LCD driver source file
#include "graphics.h" 
#include "button.h"
#include "gameobject.h"  

/*-------------------------------------------------------------------------------
  VARIABLE DECLARATIONS
-------------------------------------------------------------------------------*/
#define ALIENS_PER_ROW 11
#define INVADER_VX_INIT 1 //1
#define INVADER_VY_INIT 0
#define INVADER_ROW_START 4
#define SPACESHIP_X_INIT 14
#define SPACESHIP_Y_INIT 14
#define SPACESHIP_VX_INIT 0
#define SPACESHIP_VY_INIT 0
#define MOTHERSHIP_X_INIT 7
#define MOTHERSHIP_Y_INIT 2
#define MOTHERSHIP_VX_INIT 0
#define MOTHERSHIP_VY_INIT 0
#define BARRIER0_X_INIT 5
#define BARRIER1_X_INIT 11
#define BARRIER2_X_INIT 17
#define BARRIER3_X_INIT 23
#define BARRIER_Y_INIT 13
#define BARRIER_VX_INIT 0
#define BARRIER_VY_INIT 0
#define SPACESHIP_BULLET_X_INIT -1
#define SPACESHIP_BULLET_Y_INIT -1
#define SPACESHIP_BULLET_VX_INIT 0
#define SPACESHIP_BULLET_VY_INIT 0
#define INVADER_BULLET_X_INIT -1
#define INVADER_BULLET_Y_INIT -1
#define INVADER_BULLET_VX_INIT 0
#define INVADER_BULLET_VY_INIT 0
#define INIT_SCORE 0
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
    t6963c_spaceInvaders_setStats(1, STAT_SCORE, INIT_SCORE);
    t6963c_spaceInvaders_setStats(1, STAT_LIVES, 3);
    //t6963c_spaceInvaders_setStats(1, STAT_GAMEOVER, 0);
    INTERRUPT_GlobalEnable();
    
    // Initialization of the buttons 
    BUT_Initialize();

    /*--------------------------------------------------------------------------
     Component Declarations
	--------------------------------------------------------------------------*/
    unsigned int score = INIT_SCORE;
    
    // Game Map
    struct map gameMap;
    
    // Animation Nodes
    struct animationnode invader0_animation_node0;
    struct animationnode invader0_animation_node0_side_attack;
    struct animationnode invader0_animation_node1;
    struct animationnode invader0_animation_node1_side_attack;
    struct animationnode invader1_animation_node0;
    struct animationnode invader1_animation_node0_side_attack;
    struct animationnode invader1_animation_node1;
    struct animationnode invader1_animation_node1_side_attack;
    struct animationnode invader2_animation_node0;
    struct animationnode invader2_animation_node0_side_attack;
    struct animationnode invader2_animation_node1;
    struct animationnode invader2_animation_node1_side_attack;
    struct animationnode laser_animation_node;
    struct animationnode laser_animation_node_side_attack;
    struct animationnode explosion_animation_node;
    struct animationnode barrierHit0;
    struct animationnode barrierHit1;
    struct animationnode barrierHit2;
    
    // Animation Lists
    struct animationlist invader0_animation;
    struct animationlist invader1_animation;
    struct animationlist invader2_animation;
    struct animationlist laser_animation;
    struct animationlist explosion_animation;
    
    //Game Objects
    struct gameobject spaceship;
    struct gameobject spaceship_bullet;
    struct gameobject invader_bullet;
    struct gameobject mothership;
    struct gameobject invader0[ALIENS_PER_ROW*2];
    struct gameobject invader1[ALIENS_PER_ROW*2];
    struct gameobject invader2[ALIENS_PER_ROW*2];
    
    // Barriers 
    struct barrierArray barriers;
    
    // Invader list
    struct alienlist invaders_alive;
    
    struct aliennode invader0_node[ALIENS_PER_ROW*2];
    struct aliennode invader1_node[ALIENS_PER_ROW*2];
    struct aliennode invader2_node[ALIENS_PER_ROW*2];
    
    unsigned char i=0;
    
    struct mapnode *invaderKilled;
    
    /*--------------------------------------------------------------------------
     Component Initialization
	--------------------------------------------------------------------------*/
    // Game Map
    gameMap.init = mapInit;
    gameMap.getMapNode = getMapNode;
    gameMap.setSinglePos = mapSetSinglePos;
    gameMap.setDoublePos = mapSetDoublePos;
    gameMap.init(&gameMap);
            
    // Invaders alive list
    invaders_alive.size = 0;
    invaders_alive.borderColision = 0;
    invaders_alive.pushVertical = alien_push_vertical;
    invaders_alive.pushHorizontal = alien_push_horizontal;
    invaders_alive.update = update_invader_list; 
    invaders_alive.pop = alien_pop;
    invaders_alive.renderVertical = render_invader_vertical_list;
    invaders_alive.renderHorizontal = render_invader_horizontal_list;
    invaders_alive.render = invaders_alive.renderVertical;
    invaders_alive.detectColision = detectColisionAlienList;
    
    // Animation Nodes 
    invader0_animation_node0_side_attack.symbol[0] = INVADER_0_SYM + 2;
    invader0_animation_node0_side_attack.symbol[1] = INVADER_0_SYM + 3;
    invader0_animation_node0_side_attack.setSecondaryNode = setSecondaryNode;
    
    invader0_animation_node0.symbol[0] = INVADER_0_SYM;
    invader0_animation_node0.symbol[1] = INVADER_0_SYM + 1;
    invader0_animation_node0.setSecondaryNode = setSecondaryNode;
    invader0_animation_node0.setSecondaryNode(&invader0_animation_node0, &invader0_animation_node0_side_attack);
    
    invader0_animation_node1_side_attack.symbol[0] = INVADER_0_SYM + 6;
    invader0_animation_node1_side_attack.symbol[1] = INVADER_0_SYM + 7;
    invader0_animation_node1_side_attack.setSecondaryNode = setSecondaryNode;
             
    invader0_animation_node1.symbol[0] = INVADER_0_SYM + 4;
    invader0_animation_node1.symbol[1] = INVADER_0_SYM + 5;
    invader0_animation_node1.setSecondaryNode = setSecondaryNode;
    invader0_animation_node1.setSecondaryNode(&invader0_animation_node1, &invader0_animation_node1_side_attack);
    
    invader1_animation_node0_side_attack.symbol[0] = INVADER_1_SYM + 2;
    invader1_animation_node0_side_attack.symbol[1] = INVADER_1_SYM + 3;
    invader1_animation_node0_side_attack.setSecondaryNode = setSecondaryNode;
            
    invader1_animation_node0.symbol[0] = INVADER_1_SYM;
    invader1_animation_node0.symbol[1] = INVADER_1_SYM + 1;
    invader1_animation_node0.setSecondaryNode = setSecondaryNode;
    invader1_animation_node0.setSecondaryNode(&invader1_animation_node0, &invader1_animation_node0_side_attack);
    
    invader1_animation_node1_side_attack.symbol[0] = INVADER_1_SYM + 6;
    invader1_animation_node1_side_attack.symbol[1] = INVADER_1_SYM + 7;
    invader1_animation_node1_side_attack.setSecondaryNode = setSecondaryNode;
            
    invader1_animation_node1.symbol[0] = INVADER_1_SYM + 4;
    invader1_animation_node1.symbol[1] = INVADER_1_SYM + 5;
    invader1_animation_node1.setSecondaryNode = setSecondaryNode;
    invader1_animation_node1.setSecondaryNode(&invader1_animation_node1, &invader1_animation_node1_side_attack);
    
    invader2_animation_node0_side_attack.symbol[0] = INVADER_2_SYM + 2;
    invader2_animation_node0_side_attack.symbol[1] = INVADER_2_SYM + 3;
    invader2_animation_node0_side_attack.setSecondaryNode = setSecondaryNode;
            
    invader2_animation_node0.symbol[0] = INVADER_2_SYM;
    invader2_animation_node0.symbol[1] = INVADER_2_SYM + 1;
    invader2_animation_node0.setSecondaryNode = setSecondaryNode;
    invader2_animation_node0.setSecondaryNode(&invader2_animation_node0, &invader2_animation_node0_side_attack);
    
    invader2_animation_node1_side_attack.symbol[0] = INVADER_2_SYM + 6;
    invader2_animation_node1_side_attack.symbol[1] = INVADER_2_SYM + 7;
    invader2_animation_node1_side_attack.setSecondaryNode = setSecondaryNode;
            
    invader2_animation_node1.symbol[0] = INVADER_2_SYM + 4;
    invader2_animation_node1.symbol[1] = INVADER_2_SYM + 5;
    invader2_animation_node1.setSecondaryNode = setSecondaryNode;
    invader2_animation_node1.setSecondaryNode(&invader2_animation_node1, &invader2_animation_node1_side_attack);
    
    laser_animation_node.symbol[0] = LASER_SYM;
    laser_animation_node.setSecondaryNode = setSecondaryNode;
    laser_animation_node.setSecondaryNode(&laser_animation_node, &laser_animation_node_side_attack);
    
    explosion_animation_node.symbol[0] = EXPLOSION_SYM;
    explosion_animation_node.symbol[1] = EXPLOSION_SYM + 1;
    explosion_animation_node.setSecondaryNode = setSecondaryNode;
    
    barrierHit0.symbol[0] = BARRIER_SYM;
    barrierHit0.symbol[1] = BARRIER_SYM + 1;
    barrierHit0.setSecondaryNode = setSecondaryNode;
    
    barrierHit1.symbol[0] = BARRIER_SYM + 2;
    barrierHit1.symbol[1] = BARRIER_SYM + 3;
    barrierHit1.setSecondaryNode = setSecondaryNode;
    
    barrierHit2.symbol[0] = BARRIER_SYM + 4;
    barrierHit2.symbol[1] = BARRIER_SYM + 5;
    barrierHit2.setSecondaryNode = setSecondaryNode;
    
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
    
    laser_animation.size = 0;
    laser_animation.push = animation_push;
    laser_animation.push(&laser_animation, &laser_animation_node);
    
    explosion_animation.size = 0;
    explosion_animation.push = animation_push;
    explosion_animation.push(&explosion_animation, &explosion_animation_node);
    
    //Game Objects
    
    // Spaceship (Player)
    spaceship.init = init_game_object;   
    spaceship.update = update_spaceship;
    spaceship.render = render_spaceship; 
    spaceship.attack = attack_spaceship;
    spaceship.init(&spaceship, ID_SPACESHIP, SPACESHIP_X_INIT, SPACESHIP_Y_INIT, SPACESHIP_VX_INIT, SPACESHIP_VY_INIT);
    spaceship.explosion_node = &explosion_animation_node;
    
    // Spaceship Bullet (Player)
    spaceship_bullet.init = init_game_object;   
    spaceship_bullet.update = update_bullet;
    spaceship_bullet.render = render_bullet;  
    spaceship_bullet.init(&spaceship_bullet, ID_BULLET, SPACESHIP_BULLET_X_INIT, SPACESHIP_BULLET_Y_INIT, SPACESHIP_BULLET_VX_INIT, SPACESHIP_BULLET_VY_INIT);
    spaceship_bullet.animation_node = laser_animation.head;
    spaceship_bullet.explosion_node = &explosion_animation_node;
    
    // Spaceship Bullet (Player)
    invader_bullet.init = init_game_object;   
    invader_bullet.update = update_bullet;
    invader_bullet.render = render_bullet;  
    invader_bullet.init(&invader_bullet, ID_BULLET, INVADER_BULLET_X_INIT, INVADER_BULLET_Y_INIT, INVADER_BULLET_VX_INIT, INVADER_BULLET_VY_INIT);
    invader_bullet.animation_node = laser_animation.head;
    invader_bullet.explosion_node = &explosion_animation_node;
    
    // Mothership
    mothership.init = init_game_object;   
    mothership.update = update_game_object;
    mothership.render = render_mothership;  
    mothership.init(&mothership, ID_MOTHERSHIP, MOTHERSHIP_X_INIT, MOTHERSHIP_Y_INIT, MOTHERSHIP_VX_INIT, MOTHERSHIP_VY_INIT);
    mothership.explosion_node = &explosion_animation_node;
    
    // Barriers
    barriers.init = initBarrierArray;
    barriers.initBarrier = initBarrier;
    barriers.render = renderBarrierArray;
    barriers.detectColisionBullet = detectColisionBulletBarrierArray;
    barriers.init(&barriers, &barrierHit0, &barrierHit1, &barrierHit2);
    for(i=0; i<BARRIERS_QUANTITY; i++)
    {
        barriers.barrier[i].init = init_game_object;   
        barriers.barrier[i].update = update_game_object;
        barriers.barrier[i].render = render_barrier;
        barriers.barrier[i].explosion_node = &explosion_animation_node;
    } 
    barriers.initBarrier(&barriers, &gameMap, 0, ID_BARRIER, BARRIER0_X_INIT, BARRIER_Y_INIT, BARRIER_VX_INIT, BARRIER_VY_INIT); 
    barriers.initBarrier(&barriers, &gameMap, 1, ID_BARRIER, BARRIER1_X_INIT, BARRIER_Y_INIT, BARRIER_VX_INIT, BARRIER_VY_INIT); 
    barriers.initBarrier(&barriers, &gameMap, 2, ID_BARRIER, BARRIER2_X_INIT, BARRIER_Y_INIT, BARRIER_VX_INIT, BARRIER_VY_INIT);
    barriers.initBarrier(&barriers, &gameMap, 3, ID_BARRIER, BARRIER3_X_INIT, BARRIER_Y_INIT, BARRIER_VX_INIT, BARRIER_VY_INIT);
    
    // Invader Object Functions
    for(i=0; i<ALIENS_PER_ROW*2; i++)
    {
        invader0[i].init = init_game_object;
        invader0[i].update = update_game_object;
        invader0[i].render = render_invader;
        invader0[i].animation_node = invader0_animation.head;
        invader0[i].explosion_node = &explosion_animation_node;
        invader0[i].attack = attack_alien;
        invader1[i].init = init_game_object;   
        invader1[i].update = update_game_object;
        invader1[i].render = render_invader;
        invader1[i].animation_node = invader1_animation.head;
        invader1[i].explosion_node = &explosion_animation_node;
        invader1[i].attack = attack_alien;
        invader2[i].init = init_game_object;   
        invader2[i].update = update_game_object;
        invader2[i].render = render_invader;
        invader2[i].animation_node = invader2_animation.head;
        invader2[i].explosion_node = &explosion_animation_node;
        invader2[i].attack = attack_alien;
    }
    
    // Invader Nodes Functions
    for(i=0; i<ALIENS_PER_ROW*2; i++)
    {
        invader0_node[i].update = update_invader_node;
        invader0_node[i].render = render_invader_node;
        invader0_node[i].alien = &invader0[i];
        invader1_node[i].update = update_invader_node;
        invader1_node[i].render = render_invader_node;
        invader1_node[i].alien = &invader1[i]; 
        invader2_node[i].update = update_invader_node;
        invader2_node[i].render = render_invader_node;
        invader2_node[i].alien = &invader2[i];
    }
    
    // Invader Object Position Parameters
    for(i=0; i<ALIENS_PER_ROW; i++){
        invader0[i].init(&invader0[i], ID_INVADER_0, i*2, INVADER_ROW_START+5, INVADER_VX_INIT, INVADER_VY_INIT);  
        invader0[ALIENS_PER_ROW+i].init(&invader0[ALIENS_PER_ROW+i], ID_INVADER_0, i*2, INVADER_ROW_START+4, INVADER_VX_INIT, INVADER_VY_INIT);
        invader1[i].init(&invader1[i], ID_INVADER_1, i*2, INVADER_ROW_START+3, INVADER_VX_INIT, INVADER_VY_INIT);
        invader1[ALIENS_PER_ROW+i].init(&invader1[ALIENS_PER_ROW+i], ID_INVADER_1, i*2, INVADER_ROW_START+2, INVADER_VX_INIT, INVADER_VY_INIT); 
        invader2[i].init(&invader2[i], ID_INVADER_2, i*2, INVADER_ROW_START+1, INVADER_VX_INIT, INVADER_VY_INIT);  
        invader2[ALIENS_PER_ROW+i].init(&invader2[ALIENS_PER_ROW+i], ID_INVADER_2, i*2, INVADER_ROW_START, INVADER_VX_INIT, INVADER_VY_INIT);
    }
    
    // Invaders Alive Vertical List
    for(i=0; i<ALIENS_PER_ROW; i++){
        invaders_alive.pushVertical(&invaders_alive, &invader0_node[i]);
        invaders_alive.pushVertical(&invaders_alive, &invader0_node[ALIENS_PER_ROW + i]);
        invaders_alive.pushVertical(&invaders_alive, &invader1_node[i]);
        invaders_alive.pushVertical(&invaders_alive, &invader1_node[ALIENS_PER_ROW + i]);
        invaders_alive.pushVertical(&invaders_alive, &invader2_node[i]);  
        invaders_alive.pushVertical(&invaders_alive, &invader2_node[ALIENS_PER_ROW + i]);
    }
    
    // Invaders Alive Horizontal List
    for(i=0; i<ALIENS_PER_ROW; i++){
        invaders_alive.pushHorizontal(&invaders_alive, &invader0_node[i]);
    }
    for(i=0; i<ALIENS_PER_ROW; i++){
        invaders_alive.pushHorizontal(&invaders_alive, &invader0_node[ALIENS_PER_ROW + i]);
    }
    for(i=0; i<ALIENS_PER_ROW; i++){
        invaders_alive.pushHorizontal(&invaders_alive, &invader1_node[i]);
    }
    for(i=0; i<ALIENS_PER_ROW; i++){
        invaders_alive.pushHorizontal(&invaders_alive, &invader1_node[ALIENS_PER_ROW + i]);
    }
    for(i=0; i<ALIENS_PER_ROW; i++){
        invaders_alive.pushHorizontal(&invaders_alive, &invader2_node[i]);  
    }
    for(i=0; i<ALIENS_PER_ROW; i++){    
        invaders_alive.pushHorizontal(&invaders_alive, &invader2_node[ALIENS_PER_ROW + i]);
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
        inputHandler(BUT_get(), &spaceship, &spaceship_bullet);
        //spaceship.attack(&spaceship, &spaceship_bullet);
        invader0[0].attack(&invader0[0], &invader_bullet);
        
        /*----------------------------------------------------------------------
         Updates
        ----------------------------------------------------------------------*/
        spaceship.update(&spaceship, elapsed);
        mothership.update(&mothership, elapsed);
        invaders_alive.update(&invaders_alive, &gameMap, elapsed);
        spaceship_bullet.update(&spaceship_bullet, elapsed);
        invader_bullet.update(&invader_bullet, elapsed);
        invaderKilled = invaders_alive.detectColision(&invaders_alive, &gameMap, &spaceship_bullet);
        barriers.detectColisionBullet(&barriers, &gameMap, &invader_bullet);
        barriers.detectColisionBullet(&barriers, &gameMap, &spaceship_bullet);
        
        /*----------------------------------------------------------------------
         Render
        ----------------------------------------------------------------------*/    
        if((currentTick % 1) == 0){ 
            //t6963c_spaceInvaders_draw( 8 , 20, &invader); //lateral % 15
            barriers.render(&barriers);
            spaceship.render(&spaceship);
            mothership.render(&mothership);
            invaders_alive.render(&invaders_alive, &gameMap);
            spaceship_bullet.render(&spaceship_bullet);

            //IO_LED_Toggle();
            

            invader_bullet.render(&invader_bullet);
            render_score(invaderKilled, &score);
            invaderKilled = NULL;

        }
        
        currentTick++;
    }

    return 1;
}
/**
 End of File
*/


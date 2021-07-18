/*-------------------------------------------------------------------------------
  HEADER FILES
  NOTE: The processor specific header file is not required since we will not
  be using any processor specific features - this is all generic C code
-------------------------------------------------------------------------------*/
#include <xc.h>             // Processor specific header file
#include "mcc_generated_files/system.h"
#include "mcc_generated_files/oc1.h"
  
/*-------------------------------------------------------------------------------
  VARIABLE DECLARATIONS
-------------------------------------------------------------------------------*/

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
    OC1_Initialize();
    OC1_Start();
    /*--------------------------------------------------------------------------
     Component Declarations
	--------------------------------------------------------------------------*/
    
    
    /*--------------------------------------------------------------------------
     Component Initialization
	--------------------------------------------------------------------------*/
    
    
    /*--------------------------------------------------------------------------
     Game Loop - Design Pattern
     * 
     * A game loop runs continuously during gameplay. Each turn of the loop, it
     * processes user input without blocking, updates the game state, and 
     * renders the game. 
     * It tracks the passage of time to control the rate of gameplay.
	--------------------------------------------------------------------------*/
    
    
    while (1)
    {
        //elapsed = (char)(currentTick - previousTick); 
        //previousTick = currentTick;
        //lag += elapsed;
        
        /*----------------------------------------------------------------------
         Inputs
        ----------------------------------------------------------------------*/
        
        //spaceship.attack(&spaceship, &spaceship_bullet);
        
        /*----------------------------------------------------------------------
         Updates
        ----------------------------------------------------------------------*/
        //spaceship.update(&spaceship, elapsed);
        //mothership.update(&mothership, elapsed);
        //invaders_alive.update(&invaders_alive, &gameMap, elapsed);
        //spaceship_bullet.update(&spaceship_bullet, elapsed);
        //gameMap.detectColision(&gameMap, &spaceship_bullet);

        /*----------------------------------------------------------------------
         Render
        ----------------------------------------------------------------------*/    

        
        //currentTick++;
    }

    return 1;
}
/**
 End of File
*/


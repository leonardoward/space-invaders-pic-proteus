/*-------------------------------------------------------------------------------
  HEADER FILES
  NOTE: The processor specific header file is not required since we will not
  be using any processor specific features - this is all generic C code
-------------------------------------------------------------------------------*/
#include <xc.h>             // Processor specific header file
#include "mcc_generated_files/system.h"
#include "mcc_generated_files/oc1.h"
#include "mcc_generated_files/interrupt_manager.h"
//#include "fastinvader1.h" 
//#include "ufo_lowpitch.h" 



/*-------------------------------------------------------------------------------
  VARIABLE DECLARATIONS
-------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------
  FUNCTION PROTOTYPES
-------------------------------------------------------------------------------*/
/*
void mio(){
        //unsigned short index = 0;
        unsigned short frame;
        frame = index++ % (PR2);
        OC1_SecondaryValueSet(frame);
};*/
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
    OC1_Start();
    //TMR2_Start();
    INTERRUPT_GlobalEnable();
    //TMR2_SetInterruptHandler( &mio);
    /*--------------------------------------------------------------------------
     Component Declarations
	--------------------------------------------------------------------------*/
    
    
    /*--------------------------------------------------------------------------
     Component Initialization
	--------------------------------------------------------------------------*/
    //bool completeCycle;
    //unsigned short index = 0;
    long int frame;
    long int ufito;
    unsigned short index = 0;
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
        //index += 1000;
        //OC1_Tasks();
       // frame = PR2;
        //ufito = UFO[index++ % (NUM_ELEMENTS_UFO)];
        //frame *= ufito;
        //frame /= 255;
        //frame = index++ % (PR2);
        //OC1_SecondaryValueSet(frame);
        
    }

    return 1;
}
/**
 End of File
*/


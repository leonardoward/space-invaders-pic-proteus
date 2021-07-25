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
    INTERRUPT_GlobalEnable();


    /*--------------------------------------------------------------------------
     Component Initialization
	--------------------------------------------------------------------------*/
    //bool completeCycle;
    //unsigned short index = 0;
    //long int frame;


    
    while (1)
    {

        //frame = PR2;
        //frame *= UFO[index++ % (NUM_ELEMENTS_UFO)];
        //frame /= 255;
        //OC1_SecondaryValueSet(frame);
        
    }

    return 1;
}
/**
 End of File
*/


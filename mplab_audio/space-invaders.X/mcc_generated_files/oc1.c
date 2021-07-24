
/**
  OC1 Generated Driver API Source File

  @Company
    Microchip Technology Inc.

  @File Name
    oc1.c

  @Summary
    This is the generated source file for the OC1 driver using PIC24 / dsPIC33 / PIC32MM MCUs

  @Description
    This source file provides APIs for driver for OC1.
    Generation Information :
        Product Revision  :  PIC24 / dsPIC33 / PIC32MM MCUs - 1.170.0
        Device            :  PIC24FJ128GA010
    The generated drivers are tested against the following:
        Compiler          :  XC16 v1.61
        MPLAB 	          :  MPLAB X v5.45
*/

/*
    (c) 2020 Microchip Technology Inc. and its subsidiaries. You may use this
    software and any derivatives exclusively with Microchip products.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION
    WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.

    MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE
    TERMS.
*/

/**
  Section: Included Files
*/

#include "oc1.h"
#include "../ufo_lowpitch.h" 
#include "../fastinvader1.h" 

/** OC Mode.

  @Summary
    Defines the OC Mode.

  @Description
    This data type defines the OC Mode of operation.

*/

static uint16_t         gOC1Mode;

/**
  Section: Driver Interface
*/


void OC1_Initialize (void)
{
    // OC1RS 1440; 
    OC1RS = 0x5A0;
    // OC1R 720; 
    OC1R = 0x2D0;
    // OCSIDL disabled; OCM Double Compare Continuous Pulse mode; OCTSEL TMR2; 
    OC1CON = 0x05;
	
    gOC1Mode = OC1CONbits.OCM;
    
    IFS0bits.OC1IF = false;
    IEC0bits.OC1IE = true;
}


 unsigned short index = 0;

void __attribute__ ((weak)) OC1_CallBack(void)
{
    // Add your custom callback code here
    //OC1_SecondaryValueSet(720/2);
    //OC1_PrimaryValueSet(720/2);
    
   
   long int frame = 0;
   
    frame = PR2;
    frame *= inv_step_1[index++ % (NUM_ELEMENTS_INV_1 + NUM_ELEMENTS_INV_2)];

    frame /= 255;

   //frame = (PR2 * UFO[index++ % (NUM_ELEMENTS_UFO)])/255;
   //frame = index++ % (PR2);
   OC1_SecondaryValueSet(frame);
   OC1_PrimaryValueSet(0);
}

void __attribute__ ( ( interrupt, no_auto_psv ) ) _ISR _OC1Interrupt( void )
{	
    if(IFS0bits.OC1IF)
    {
		// OC1 callback function 
		OC1_CallBack();
        IFS0bits.OC1IF = 0;
    }
}


void OC1_Start( void )
{
    OC1CONbits.OCM = gOC1Mode;
}


void OC1_Stop( void )
{
    OC1CONbits.OCM = 0;
}

void OC1_SecondaryValueSet( uint16_t secVal )
{
   
    OC1RS = secVal;
}


void OC1_PrimaryValueSet( uint16_t priVal )
{
   
    OC1R = priVal;
}

bool OC1_IsCompareCycleComplete( void )
{
    return(IFS0bits.OC1IF);
}


bool OC1_FaultStatusGet( OC1_FAULTS faultNum )
{
    bool status;
    /* Return the status of the fault condition */
   
    switch(faultNum)
    { 
        case OC1_FAULT0:
			status = OC1CONbits.OCFLT;
            break;
        default :
            break;

    }
    return(status);
}



/**
 End of File
*/

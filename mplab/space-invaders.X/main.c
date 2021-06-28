/**
  Generated main.c file from MPLAB Code Configurator

  @Company
    Microchip Technology Inc.

  @File Name
    main.c

  @Summary
    This is the generated main.c using PIC24 / dsPIC33 / PIC32MM MCUs.

  @Description
    This source file provides main entry point for system initialization and application code development.
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
#include <xc.h>
#include "mcc_generated_files/system.h"
//#include "LCD.h"          // include LCD driver source file
#include "t6963c.h"          // include LCD driver source file
#include "graphics.h"          

/*
                         Main application
 */
int main(void)
{
    // initialize the device
    SYSTEM_Initialize();
    t6963c_init();
    
    t6963c_spaceInvaders_spriteInit();
    
    //t6963c_spaceInvaders_setLanding();
    t6963c_spaceInvaders_setStats(1, STAT_SCORE, 0);
    t6963c_spaceInvaders_setStats(1, STAT_LIVES, 3);
    t6963c_spaceInvaders_setStats(0, STAT_GAMEOVER, 1);
    
    
    

    unsigned short tick = 0;
    unsigned short lateral = 0;

    
    struct character_t invader;
    
    t6963c_spaceInvaders_setCharacter(&invader, CHAR_TYPE_INVADER_0);
    
    invader.state = CHAR_STATE_DODGE_LEFT;
    //t6963c_spaceInvaders_setStats(1, STAT_GAMEOVER, 0);
    while (1)
    {
        
/*
        t6963c_spaceInvaders_draw(1, 5, CHAR_TYPE_INVADER_1, tick, CHAR_NO_DELETE);
        t6963c_spaceInvaders_draw(2, 5, CHAR_TYPE_INVADER_2, tick, CHAR_NO_DELETE);
        t6963c_spaceInvaders_draw(8, ( lateral % 29), CHAR_TYPE_LASER, tick, CHAR_NO_DELETE); //( lateral % 28)
        t6963c_spaceInvaders_draw(9, ( lateral % 29), CHAR_TYPE_SPACESHIP, tick, CHAR_NO_DELETE);
 * 
 * */
        tick++;
        if((tick % 100000) == 0){ 
            t6963c_spaceInvaders_draw( 8 , 5, &invader, (tick)); //
            lateral++;
        }
    }

    return 1;
}
/**
 End of File
*/


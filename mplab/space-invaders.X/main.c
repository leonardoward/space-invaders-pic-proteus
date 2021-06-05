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
#include "mcc_generated_files/system.h"
#include "glcd.h"
#include "front2.c"
#include "names.c"

/*
                         Main application
 */
int main(void)
{
    // initialize the device
    SYSTEM_Initialize();

    int num = 1234;
    GLCD_Init();
    
    //GLCD_Printf("Dec:%d \nHex:%x \nBin:%b \nFloat:%f", num, num, num, 4567.89);


    while (1) 
    {
        GLCD_Clear();
        GLCD_DisplayLogo(front2);
        DELAY_sec(5);
        
        GLCD_Clear();
        GLCD_DisplayLogo(names);
        DELAY_sec(5);

        //GLCD_Clear();
        //GLCD_Printf("Dec:%d \nHex:%x \nBin:%b \nFloat:%f", num, num, num, 4567.0);
        //DELAY_sec(1);

        //GLCD_Clear();
       // GLCD_HorizontalGraph(0, 45);
        //GLCD_HorizontalGraph(1, 50);
        //GLCD_HorizontalGraph(2, 82);
        //GLCD_HorizontalGraph(3, 74);
        
        //GLCD_SetCursor(5, 5);
        //        GLCD_Printf("Hola");

        //DELAY_sec(1);
/*
        GLCD_Clear();
        GLCD_VerticalGraph(0, 45);
        GLCD_VerticalGraph(1, 50);
        GLCD_VerticalGraph(2, 82);
        GLCD_VerticalGraph(3, 74);
        DELAY_sec(1);*/
    }
    return 1;
}
/**
 End of File
*/


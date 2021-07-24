/* Microchip Technology Inc. and its subsidiaries.  You may use this software 
 * and any derivatives exclusively with Microchip products. 
 * 
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES, WHETHER 
 * EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED 
 * WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A 
 * PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION 
 * WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION. 
 *
 * IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
 * INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
 * WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS 
 * BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE 
 * FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS 
 * IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF 
 * ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE 
 * TERMS. 
 */

/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef BUTTONS_H
#define	BUTTONS_H

#include <xc.h> // include processor files - each processor file is guarded. 


// TODO Insert appropriate #include <>

// TODO Insert C++ class definitions if appropriate

// TODO Insert declarations


// Utilizado para diferenciar las instrucciones que ejecuta cada boton
enum button_instructions_t{
    BUT_EMPTY = 0,
    BUT_INS_OK, 
    BUT_INS_LEFT,
    BUT_INS_RIGHT
};

// El tamano maximo del arreglo que mantiene la cantidad instrucciones a procesar
#define MAX_LIST_SIZE 10

// Estructura del boton, este contiene la instruccion que debe ejecutarse al ser presionado
struct button_t {
    enum button_instructions_t instruction;
    //struct button_t *next;
};

// Estructura del arreglo que mantiene las instrucciones en cola FIFO hasta ser procesados
struct buttonlist_t // array
{
   // Parameters
   unsigned char bufferSize; //cantidad de elementos ocupados
   
   struct button_t bufferIndex[MAX_LIST_SIZE]; // arreglo, buffer o lista de instrucciones
   
   //void (*insert)(struct button_t but);
   //void (*pop)(struct button_t *but);  
};



// Inicializa el arreglo de los botones
void BUT_Initialize(void);

// Solicita una instruccion del arreglo
enum button_instructions_t BUT_get();

// Verifica si hay una instruccion sin procesar
char BUT_buffer_elements();

// Inserta una nueva instruccion al arreglo
void BUT_insert(enum button_instructions_t in);

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


/*
 * File:   button.c
 * Author: mauro
 *
 * Created on July 23, 2021, 1:01 PM
 */


#include "button.h"




struct buttonlist_t BUTTONS;


void BUT_Initialize(void){
    
    unsigned char index;
    
    //BUTTONS.insert = BUT_insert;
    //BUTTONS.pop = BUT_pop;
    
    // Se inicializa el contador de elementos en cero y se vacia el array de cualquier valor extrano
    BUTTONS.bufferSize = 0;
    
    for(index = 0; index < MAX_LIST_SIZE; index++ ){
        BUTTONS.bufferIndex[index].instruction = BUT_EMPTY;
    };

};



void BUT_insert(enum button_instructions_t ins){
    
    unsigned char index;
    
    // Busca el primer elemento del arreglo vacio para insertar la nueva instruccion
    // Si el arreglo esta ful, la instruccion es desechada
    for(index = 0; index < MAX_LIST_SIZE; index++ ){
        if( BUTTONS.bufferIndex[index].instruction == BUT_EMPTY ){
            BUTTONS.bufferIndex[index].instruction = ins;
            BUTTONS.bufferSize++;
            break;
        }
    }
    
};


enum button_instructions_t BUT_get(){
    
    unsigned char index;
    
    //Devuelve la primera instruccion 
    enum button_instructions_t temp = BUTTONS.bufferIndex[0].instruction;
    
    //Si el arreglo tenia alguna instruccion entonces corre cada elemento hacia el principio del arreglo)
    if(BUTTONS.bufferSize){ 
        
        BUTTONS.bufferSize--;
        
        for(index = 0; index < MAX_LIST_SIZE-1; index++ ){
           BUTTONS.bufferIndex[index].instruction = BUTTONS.bufferIndex[index+1].instruction;
        }
        
        // Pone el ultimo elemento del arreglo vacio
        BUTTONS.bufferIndex[MAX_LIST_SIZE-1].instruction = BUT_EMPTY;
        
    }
    
    return temp;
}; 


char BUT_buffer_elements(){
    
    // Entrega la cantidad de instrucciones a ser procesadas que ocupan el arreglo
    return BUTTONS.bufferSize;
};
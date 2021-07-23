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
    BUTTONS.bufferSize = 0;
    
    for(index = 0; index < MAX_LIST_SIZE; index++ ){
        BUTTONS.bufferIndex[index].instruction = BUT_EMPTY;
    };

};



void BUT_insert(enum button_instructions_t ins){
    
    unsigned char index;
    
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
    enum button_instructions_t temp = BUTTONS.bufferIndex[0].instruction;
    
    if(BUTTONS.bufferSize){ 
        
        BUTTONS.bufferSize--;
        
        for(index = 0; index < MAX_LIST_SIZE-1; index++ ){
           BUTTONS.bufferIndex[index].instruction = BUTTONS.bufferIndex[index+1].instruction;
        }
        
        BUTTONS.bufferIndex[MAX_LIST_SIZE-1].instruction = BUT_EMPTY;
        
    }
    
    return temp;
}; 

char BUT_buffer_size(){
    return BUTTONS.bufferSize;
};
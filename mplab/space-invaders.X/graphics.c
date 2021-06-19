

#include "graphics.h"

#include "invaders.h"



void t6963c_spaceInvaders_spriteInit(){
    unsigned char index_type, index_byte;
    

   //Load the invaders sprites in t6963c ram memory
    unsigned short address = INVADER_0_ADD;
    t6963c_writeCmd2(t6963c_CMD_set_addressPointer, address & 0xff, ((address >> 8) & 0xff));
    
  
    for( index_type = 0; index_type < (CHAR_INVADER_TYPE_MAX - CHAR_INVADER_TYPE_0) ; index_type++){ 
        for( index_byte = 0; index_byte < INVADER_RESOLUTION * INVADER_SIZE * INVADER_FRAMES; index_byte++){
                t6963c_writeCmd1(t6963c_CMD_writeData_Increment, invaders[index_type][index_byte]);
        }
    }  
    
    /*
        t6963c_set_address(2, 15);
        t6963c_startAutoWrite();
        unsigned char index;
        for( index = 0; index < INVADER_SIZE; index++){
            t6963c_autoWrite(INVADER_1_SYM+index);
        }
        t6963c_stopAutoWrite();
     */
    
    //t6963c_writeByte(CMD, t6963c_CMD_MASK_set_externalCGROM);    //  internal ROM
    //t6963c_writeCmd2(t6963c_CMD_set_offsetRegister, 0x03, DATA_ZERO);    // set offset register in certain address
    
    
    /*
    address = INVADER_1_ADD;
    t6963c_writeCmd2(t6963c_CMD_set_addressPointer, address & 0xff, ((address >> 8) & 0xff));

    for( i = 0; i<8; i++){ 
    //t6963c_writeCmd2(t6963c_CMD_set_addressPointer, i, 0x4);
    t6963c_writeCmd1(t6963c_CMD_writeData_Increment, inv_right_0[i]);
    //delay_ns(2);
    //t6963c_writeByte( CMD, t6963c_CMD_MASK_bit_set + (i) );
    //t6963c_writeByte(DATA, pound[i]);
    } 
     * 
    */
    
    
    //t6963c_writeCmd2(t6963c_CMD_set_offsetRegister, 0x01, DATA_ZERO);    // set offset register in certain address

    //t6963c_writeByte(CMD, t6963c_CMD_MASK_set_internalCGROM);

    
        //t6963c_writeByte(DATA, 0x80);
    
    //t6963c_autoWrite(0x80);
    
    //t6963c_set_address(DATA_ZERO, DATA_ZERO);
}


void t6963c_spaceInvaders_draw(unsigned char row, unsigned char column, unsigned char character, unsigned short tick){
    
    unsigned char symbol;
    unsigned short counter = 1;
    unsigned char max_size = 1;
    
    switch(character){
        case CHAR_BLANK_SPACE:
            break;
            
        case CHAR_INVADER_TYPE_0:
            symbol = INVADER_0_SYM;
            counter = INVADER_0_RR;
            max_size = INVADER_SIZE;
            break;
            
        case CHAR_INVADER_TYPE_1:
            symbol = INVADER_1_SYM;
            counter = INVADER_1_RR;
            max_size = INVADER_SIZE;
            break;
            
        case CHAR_INVADER_TYPE_2:
            symbol = INVADER_2_SYM;
            counter = INVADER_2_RR;
            max_size = INVADER_SIZE;
            break;
            
        case CHAR_BARRIER_EMPTY:
            break;
            
        case CHAR_BARRIER_LOW:
            break;
            
        case CHAR_BARRIER_MID:
            break;
            
        case CHAR_BARRIER_FULL:
            break;
            
        case CHAR_LASER:
            break;
            
        case CHAR_SPACESHIP:
            break;
            
        default:
            break;       
    }
    
    if(tick % counter == 0){
        
        unsigned char frame = ((tick / counter)% 2 == 0) ?  0:2;
        t6963c_set_address(row, column);
        
        t6963c_startAutoWrite();
        
        unsigned char index;
        for( index = 0; index < max_size; index++){
            t6963c_autoWrite(symbol + frame + index);
        }
        
        t6963c_stopAutoWrite();
    }
    
}


#include "graphics.h"

#include "invaders.h"
#include "spaceship.h"



void t6963c_spaceInvaders_spriteInit(){
    unsigned char index_type, index_byte;
    

   //Load the invaders sprites in t6963c ram memory
    unsigned short address = INVADER_0_ADD;
    t6963c_writeCmd2(t6963c_CMD_set_addressPointer, address & 0xff, ((address >> 8) & 0xff));
    
    for( index_type = 0; index_type < (CHAR_TYPE_INVADER_MAX - CHAR_TYPE_INVADER_0) ; index_type++){ 
        for( index_byte = 0; index_byte < CHAR_RESOLUTION * INVADER_SIZE * INVADER_FRAMES; index_byte++){
            t6963c_writeCmd1(t6963c_CMD_writeData_Increment, invaders[index_type][index_byte]);
        }
    }  
    
    
    address = SPACESHIP_ADD;
    t6963c_writeCmd2(t6963c_CMD_set_addressPointer, address & 0xff, ((address >> 8) & 0xff));
    
    for( index_byte = 0; index_byte < CHAR_RESOLUTION * SPACESHIP_SIZE ; index_byte++){
        t6963c_writeCmd1(t6963c_CMD_writeData_Increment, spaceship[index_byte]);
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


void t6963c_spaceInvaders_draw(unsigned char row, unsigned char column, unsigned char character, unsigned short tick, unsigned char delete){
    
    unsigned char symbol;
    unsigned short counter = 1;
    unsigned char max_size = 1;
    unsigned char flag_multiple_frames = 0;
    
    switch(character){
        case CHAR_TYPE_BLANK_SPACE:
            break;
            
        case CHAR_TYPE_INVADER_0:
            symbol = INVADER_0_SYM;
            counter = INVADER_0_RR;
            max_size = INVADER_SIZE;
            flag_multiple_frames = 1;
            break;
            
        case CHAR_TYPE_INVADER_1:
            symbol = INVADER_1_SYM;
            counter = INVADER_1_RR;
            max_size = INVADER_SIZE;
            flag_multiple_frames = 1;
            break;
            
        case CHAR_TYPE_INVADER_2:
            symbol = INVADER_2_SYM;
            counter = INVADER_2_RR;
            max_size = INVADER_SIZE;
            flag_multiple_frames = 1;
            break;
            
        case CHAR_TYPE_BARRIER:
            break;         
            
        case CHAR_TYPE_LASER:
            break;
            
        case CHAR_TYPE_SPACESHIP:
            symbol = SPACESHIP_SYM;
            max_size = SPACESHIP_SIZE;
            counter = SPACESHIP_RR;
            break;
            
        default:
            break;       
    }
    
    if(tick % counter == 0){
        
        unsigned char frame = ((tick / counter)% 2 == 0) ?  0:(2*flag_multiple_frames);
        
        if(delete != CHAR_LEFT_DELETE) t6963c_set_address(row, column);
        else{t6963c_set_address(row-1, column);}
        
        t6963c_startAutoWrite();
        
        if(delete == CHAR_LEFT_DELETE){ 
            t6963c_autoWrite(DATA_ZERO);
        }
          
        unsigned char index;
        for( index = 0; index < max_size; index++){
            t6963c_autoWrite(symbol + frame + index);
        }
        
        if(delete == CHAR_RIGHT_DELETE) t6963c_autoWrite(DATA_ZERO);
        
        t6963c_stopAutoWrite();
    }
    
}
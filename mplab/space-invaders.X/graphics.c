

#include "graphics.h"

#include "invaders.h"



void t6963c_set_sprite(unsigned char character, unsigned char* sprite){
    unsigned char index_type, index_byte;
    
    //t6963c_writeByte(CMD, t6963c_CMD_MASK_set_externalCGROM);    //  internal ROM
    //t6963c_writeCmd2(t6963c_CMD_set_offsetRegister, 0x03, DATA_ZERO);    // set offset register in certain address
    
   
    unsigned short address = INVADER_0_ADD;
    t6963c_writeCmd2(t6963c_CMD_set_addressPointer, address & 0xff, ((address >> 8) & 0xff));
    
  
    for( index_type = CHAR_INVADER_TYPE_0; index_type< CHAR_INVADER_TYPE_MAX ; index_type++){ 
        for( index_byte = 0; index_byte < INVADER_RESOLUTION * INVADER_SIZE * INVADER_FRAMES; index_byte++){
                t6963c_writeCmd1(t6963c_CMD_writeData_Increment, invaders[index_type][index_byte]);
        }
    }  
    
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
    unsigned char j, i;
    for(j=1;j<16;j++){
        for(i=0;i<=t6963c_columns;i+=4){
            t6963c_set_address(j, i);
            t6963c_startAutoWrite();
            t6963c_autoWrite(INVADER_1_SYM);
            t6963c_autoWrite(INVADER_1_SYM+1);
            t6963c_autoWrite(INVADER_1_SYM+2);
            t6963c_autoWrite(INVADER_1_SYM+3);
            t6963c_stopAutoWrite();
        }
    }
    
        //t6963c_writeByte(DATA, 0x80);
    
    //t6963c_autoWrite(0x80);
    
    //t6963c_set_address(DATA_ZERO, DATA_ZERO);
}
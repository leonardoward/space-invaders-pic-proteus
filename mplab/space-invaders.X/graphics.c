

#include "graphics.h"

#include "invaders.h"
#include "spaceship.h"
#include <string.h>



void t6963c_spaceInvaders_spriteInit(){
    unsigned char index_type, index_byte;
    
    //t6963c_writeByte(CMD, t6963c_CMD_MASK_set_externalCGROM);    //  internal ROM
    //t6963c_writeCmd2(t6963c_CMD_set_offsetRegister, 0x01, DATA_ZERO);    // set offset register in certain address
    
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
    
    address = LASER_ADD;
    t6963c_writeCmd2(t6963c_CMD_set_addressPointer, address & 0xff, ((address >> 8) & 0xff));
    
    for( index_byte = 0; index_byte < CHAR_RESOLUTION * LASER_SIZE ; index_byte++){
        t6963c_writeCmd1(t6963c_CMD_writeData_Increment, laser[index_byte]);
    }
    
    address = BARRIER_ADD;
    t6963c_writeCmd2(t6963c_CMD_set_addressPointer, address & 0xff, ((address >> 8) & 0xff));
    
    for( index_byte = 0; index_byte < CHAR_RESOLUTION * BARRIER_SIZE * BARRIER_FRAMES; index_byte++){
        t6963c_writeCmd1(t6963c_CMD_writeData_Increment, barrier[index_byte]);
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

void t6963c_spaceInvaders_setLanding(){
    
    unsigned short index;
    
    unsigned int address = t6963c_graph_address;
    
          
        //t6963c_set_address(0, 0);
        //Dibuja el titulo del juego
    
        t6963c_writeCmd2(t6963c_CMD_set_addressPointer, address & 0xff, ((address >> 8) & 0xff));
        for( index = 0; index < 3840; index++){
            t6963c_writeCmd1(t6963c_CMD_writeData_Increment, landing[index]);
        } 
        
        t6963c_set_address(0, 0);     
        //Dibuja el nombres de los programadores
        t6963c_writeCmd2(t6963c_CMD_set_addressPointer, address & 0xff, ((address >> 8) & 0xff));
        for( index = 0; index < 3840; index++){
            t6963c_writeCmd1(t6963c_CMD_writeData_Increment, names[index]);
        }  
        
        t6963c_set_address(0, 0);
        //Dibuja el nombres de los programadores
        t6963c_writeCmd2(t6963c_CMD_set_addressPointer, address & 0xff, ((address >> 8) & 0xff));
        for( index = 0; index < 3840; index++){
            t6963c_writeCmd1(t6963c_CMD_writeData_Increment, DATA_ZERO );
        }  
        
        /*
        //t6963c_set_cursor_address(0,0);
        t6963c_set_address(0, 0);
        t6963c_writeCmd2(t6963c_CMD_set_addressPointer, address & 0xff, ((address >> 8) & 0xff));
        t6963c_startAutoWrite();

        for( index = 0; index < 3840; index++){
            
            t6963c_autoWrite(0);
           //t6963c_writeCmd1(t6963c_CMD_writeData_Increment,0x00);
        }   
                
        t6963c_stopAutoWrite();
*/
        
       // t6963c_clear();
        

   
};


void t6963c_spaceInvaders_setCharacter(struct character_t* character, unsigned char type){
    
    character->type = type;
    character->prev_column = 0;
    character->prev_row = 0;
    character->frames = 0;
    character->state = CHAR_STATE_NORMAL;
};



void t6963c_spaceInvaders_setStats(bool first_time,unsigned char stat, unsigned int num){
    
        char snum[10];
        sprintf(snum, "%.3d", num);
        
        // Si es la primera vez, se tiene que pintar la palabra "Score" y "Lives"
        if(first_time){
            switch(stat){
                case STAT_CORE:
                    t6963c_set_address(0, 0); 
                    t6963c_startAutoWrite();
                    t6963c_writeString("Score:");
                    t6963c_stopAutoWrite();
                    break;
                case STAT_LIVES:
                    t6963c_set_address(0, 10); 
                    t6963c_startAutoWrite();
                    t6963c_writeString("Lives:");
                    t6963c_stopAutoWrite();
                    break;                   
            }
        }

        switch(stat){
           case STAT_CORE: // Si se quiere escribir el score, se pone esta direccion
               t6963c_set_address(0, 6);         
               break;
           case STAT_LIVES:// Si se quiere escribir la cantidad de vidas, se pone esta direccion
               t6963c_set_address(0, 16);  
               break;                   
       }

       t6963c_startAutoWrite();
       t6963c_writeString(snum);  
       t6963c_stopAutoWrite();
        
            

};


void t6963c_spaceInvaders_draw(char row, char column, struct character_t* character, unsigned short tick){
    
    unsigned char symbol;
    unsigned char max_size = 1;
    unsigned char frame = 0;//((tick / counter)% 2 == 0) ?  0:(2*flag_multiple_frames);
    
    switch(character->type){
        case CHAR_TYPE_BLANK_SPACE:
            break;
            
        case CHAR_TYPE_INVADER_0:
            
            if (tick % INVADER_0_RR == 0)frame  =  (++character->frames % INVADER_FRAMES)*INVADER_SIZE;
            symbol   = INVADER_0_SYM;
            max_size = INVADER_SIZE;
           
            break;
            
        case CHAR_TYPE_INVADER_1:
            
            if (tick % INVADER_1_RR == 0) frame  =  (++character->frames % INVADER_FRAMES)*INVADER_SIZE;
            symbol   = INVADER_1_SYM;
            max_size = INVADER_SIZE;
            break;
            
        case CHAR_TYPE_INVADER_2:
            
            if (tick % INVADER_2_RR == 0) frame  =  (++character->frames % INVADER_FRAMES)*INVADER_SIZE;
            symbol   = INVADER_2_SYM;
            max_size = INVADER_SIZE;
            break;
            
        case CHAR_TYPE_BARRIER:
            
            switch(character->state){
                case CHAR_STATE_NORMAL:
                    symbol   = BARRIER_SYM;
                break;
                case CHAR_STATE_HIT_1:
                    symbol   = BARRIER_SYM +   BARRIER_SIZE;
                break;
                case CHAR_STATE_HIT_2:
                    symbol   = BARRIER_SYM + 2*BARRIER_SIZE;
                break;
                case CHAR_STATE_DESTROYED:
                    symbol   = BARRIER_SYM + 3*BARRIER_SIZE;
                break;
            }
            
            max_size = BARRIER_SIZE;
            break;         
            
        case CHAR_TYPE_SPACESHIP_LASER:
            
            symbol   = LASER_SYM;
            max_size = LASER_SIZE;
            break;
            
        case CHAR_TYPE_SPACESHIP:
            
            if (tick % SPACESHIP_RR == 0) frame  =  (++character->frames % SPACESHIP_FRAMES)*SPACESHIP_SIZE;
            symbol   = SPACESHIP_SYM;
            max_size = SPACESHIP_SIZE;           
            break;
            
        default:
            break;       
    }
    
        unsigned char index;
        
        // Código para borrar la sombra que queda al mover el sprite verticalmente
        if(character->prev_row != row){ 
            t6963c_set_address(character->prev_row, column);
            for( index = 0; index < max_size; index++){
                t6963c_writeCmd1(t6963c_CMD_writeData_Increment, DATA_ZERO);
            }       
        }
        
        // Código para borrar la sombra que queda al mover el sprite horizontalmente
        if(character->prev_column != column){
            t6963c_set_address(row, character->prev_column);
            t6963c_writeCmd1(t6963c_CMD_writeData_Nonvariable, DATA_ZERO);
        }
        
        // Código para impedir de el sprite se salga de los limites hotizontales de la pantalla
        if( column > (t6963c_columns - max_size) ){
            column =  t6963c_columns - max_size;
        }else if(column < 0){
            column =  0;
        }
        
        // Pone las coordenadas en pantalla para dibujar el sprite
        t6963c_set_address(row, column);
        //t6963c_startAutoWrite();
        
        //Dibuja el sprite de izquierda a derecha
        for( index = 0; index < max_size; index++){
            //t6963c_autoWrite(symbol + frame + index);
            t6963c_writeCmd1(t6963c_CMD_writeData_Increment,(symbol + frame + index));
        }
                
        //t6963c_stopAutoWrite();
        
        character->prev_column = column;
        character->prev_row = row;
    
    
}
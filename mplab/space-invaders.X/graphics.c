

#include "graphics.h"

#include "invaders.h"
#include <string.h>


void t6963c_spaceInvaders_setLanding(){
    
    unsigned short index;
    
    unsigned int address = t6963c_graph_address;
    
          
        t6963c_set_address(0, 0);
  
        //Dibuja el titulo del juego
        t6963c_writeCmd2(t6963c_CMD_set_addressPointer, address & 0xff, ((address >> 8) & 0xff));
        for( index = 0; index < t6963c_rows*t6963c_columns*CHAR_RESOLUTION; index++){
            t6963c_writeCmd1(t6963c_CMD_writeData_Increment, landing[index]);
        } 
        
        t6963c_set_address(0, 0);    
        
        //Dibuja el nombres de los programadores
        t6963c_writeCmd2(t6963c_CMD_set_addressPointer, address & 0xff, ((address >> 8) & 0xff));
        for( index = 0; index < t6963c_rows*t6963c_columns*CHAR_RESOLUTION; index++){
            t6963c_writeCmd1(t6963c_CMD_writeData_Increment, names[index]);
        }  
        
        t6963c_set_address(0, 0);
        
        //Borra la pantalla
        t6963c_writeCmd2(t6963c_CMD_set_addressPointer, address & 0xff, ((address >> 8) & 0xff));
        for( index = 0; index < t6963c_rows*t6963c_columns*CHAR_RESOLUTION; index++){
            t6963c_writeCmd1(t6963c_CMD_writeData_Increment, 0xff );
        }  
        
 
   
   
};

void t6963c_spaceInvaders_spriteInit(){
    unsigned char index_type, index_frame, index_byte;
    unsigned laser_side;
   //Load the invaders sprites in t6963c ram memory
    unsigned short address = INVADER_0_ADD;
    
    t6963c_writeCmd2(t6963c_CMD_set_addressPointer, address & 0xff, ((address >> 8) & 0xff));
    
    for( index_type = 0; index_type < (CHAR_TYPE_INVADER_MAX - CHAR_TYPE_INVADER_0) ; index_type++){ 
        for( index_frame = 0; index_frame < INVADER_FRAMES; index_frame++){
            for( index_byte = 0; index_byte < CHAR_RESOLUTION * INVADER_SIZE; index_byte++){
                t6963c_writeCmd1(t6963c_CMD_writeData_Increment, invaders[index_type][index_byte + (index_frame* CHAR_RESOLUTION * INVADER_SIZE)]);
            }
            
            for( index_byte = 0; index_byte < CHAR_RESOLUTION * INVADER_SIZE; index_byte++){
                laser_side = (index_byte < CHAR_RESOLUTION) ?  0x80 : 0x01;
                t6963c_writeCmd1(t6963c_CMD_writeData_Increment, invaders[index_type][index_byte + (index_frame* CHAR_RESOLUTION * INVADER_SIZE)] | laser_side);  ;
            }
        }
    }  
    
    address = MOTHERSHIP_ADD;
    t6963c_writeCmd2(t6963c_CMD_set_addressPointer, address & 0xff, ((address >> 8) & 0xff));
    
    for( index_byte = 0; index_byte < CHAR_RESOLUTION * SHIP_SIZE * (CHAR_TYPE_SHIP_MAX - CHAR_TYPE_MOTHERSHIP) ; index_byte++){
        t6963c_writeCmd1(t6963c_CMD_writeData_Increment, ships[index_byte]);
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
    
    address = EXPLOSION_ADD;
    t6963c_writeCmd2(t6963c_CMD_set_addressPointer, address & 0xff, ((address >> 8) & 0xff));
    
    for( index_byte = 0; index_byte < CHAR_RESOLUTION * EXPLOSION_SIZE * EXPLOSION_FRAMES; index_byte++){
        t6963c_writeCmd1(t6963c_CMD_writeData_Increment, explosion[index_byte]);
    }
    
}


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
                case STAT_SCORE:
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
           case STAT_SCORE: // Si se quiere escribir el score, se pone esta direccion
               t6963c_set_address(0, 6);         
               break;
           case STAT_LIVES:// Si se quiere escribir la cantidad de vidas, se pone esta direccion
               t6963c_set_address(0, 16);  
               break;
           case STAT_GAMEOVER:// Si se quiere escribir la palabra gameover
               t6963c_set_address(7, 10);
               if(num){sprintf(snum, "GAMEOVER");}
               else    sprintf(snum, "        ");
               break;     
       }

       t6963c_startAutoWrite();
       t6963c_writeString(snum);  
       t6963c_stopAutoWrite();
        
            

};


void t6963c_spaceInvaders_draw_tick(char row, char column, struct character_t* character, unsigned short tick){
    
    unsigned char dodge_left  = (character->state == CHAR_STATE_DODGE_LEFT)  ? INVADER_SIZE : 0 ;
    unsigned char dodge_right = (character->state == CHAR_STATE_DODGE_RIGHT) ? INVADER_SIZE : 0 ;
    
    unsigned char symbol[2];
    unsigned char max_size = 1;
    unsigned char frame;
    
    
    switch(character->type){
         
        case CHAR_TYPE_INVADER_0:
            
            switch(character->state){
            
                case CHAR_STATE_HIT_1:
                    symbol[0]  =  EXPLOSION_SYM;
                    symbol[1]  = (EXPLOSION_SYM + 1);
                    character->state = CHAR_STATE_DESTROYED;
                    break;
                case CHAR_STATE_DESTROYED:
                    symbol[0]  =  DATA_ZERO;
                    symbol[1]  =  DATA_ZERO; 
                    break;         
                default:
                    frame = (tick % INVADER_0_RR == 0)? (++character->frames % INVADER_FRAMES)*INVADER_SIZE*2 : 0;          
                    symbol[0]  =  INVADER_0_SYM      + frame + dodge_left;
                    symbol[1]  = (INVADER_0_SYM + 1) + frame + dodge_right;
                    character->state = CHAR_STATE_NORMAL;
                    break;
            }
                
            max_size   =  INVADER_SIZE;
           
            break;
            
        case CHAR_TYPE_INVADER_1:
            
            switch(character->state){
            
                case CHAR_STATE_HIT_1:
                    symbol[0]  =  EXPLOSION_SYM;
                    symbol[1]  = (EXPLOSION_SYM + 1);
                    character->state = CHAR_STATE_DESTROYED;
                    break;
                case CHAR_STATE_DESTROYED:
                    symbol[0]  =  DATA_ZERO;
                    symbol[1]  =  DATA_ZERO; 
                    break;         
                default:
                    frame = (tick % INVADER_1_RR == 0)? (++character->frames % INVADER_FRAMES)*INVADER_SIZE*2 : 0;          
                    symbol[0]  =  INVADER_1_SYM      + frame + dodge_left;
                    symbol[1]  = (INVADER_1_SYM + 1) + frame + dodge_right;
                    character->state = CHAR_STATE_NORMAL;
                    break;
            }
            max_size = INVADER_SIZE;
            break;
            
        case CHAR_TYPE_INVADER_2:
            
            switch(character->state){
            
                case CHAR_STATE_HIT_1:
                    symbol[0]  =  EXPLOSION_SYM;
                    symbol[1]  = (EXPLOSION_SYM + 1);
                    character->state = CHAR_STATE_DESTROYED;
                    break;
                case CHAR_STATE_DESTROYED:
                    symbol[0]  =  DATA_ZERO;
                    symbol[1]  =  DATA_ZERO; 
                    break;         
                default:
                    frame = (tick % INVADER_2_RR == 0)? (++character->frames % INVADER_FRAMES)*INVADER_SIZE*2 : 0;          
                    symbol[0]  =  INVADER_2_SYM      + frame + dodge_left;
                    symbol[1]  = (INVADER_2_SYM + 1) + frame + dodge_right;
                    character->state = CHAR_STATE_NORMAL;
                    break;
            }
            max_size = INVADER_SIZE;
            break;
            
        case CHAR_TYPE_BARRIER:
            
            switch(character->state){           
                case CHAR_STATE_HIT_1:
                    symbol[0]  =  BARRIER_SYM +   BARRIER_SIZE;
                    symbol[1]  = (BARRIER_SYM +   BARRIER_SIZE + 1);
                    break;
                case CHAR_STATE_HIT_2:
                    symbol[0]  =  BARRIER_SYM +   2*BARRIER_SIZE;
                    symbol[1]  = (BARRIER_SYM +   2*BARRIER_SIZE + 1);
                    break;
                case CHAR_STATE_DESTROYED:
                    symbol[0]  =  DATA_ZERO;
                    symbol[1]  =  DATA_ZERO; 
                    break;         
                default:                         
                    symbol[0]  =  BARRIER_SYM;
                    symbol[1]  = (BARRIER_SYM + 1);    
                    break;
            }          
            
            max_size = BARRIER_SIZE;
            break;         
            
        case CHAR_TYPE_SPACESHIP_LASER:
            
            symbol[0]  = LASER_SYM;
            max_size   = LASER_SIZE;
            break;
            
        case CHAR_TYPE_SPACESHIP:
            symbol[0]  =  SPACESHIP_SYM;
            symbol[1]  = (SPACESHIP_SYM + 1);             
            max_size   = SHIP_SIZE;           
            break;
            
        case CHAR_TYPE_MOTHERSHIP:
            symbol[0]  =  MOTHERSHIP_SYM;
            symbol[1]  = (MOTHERSHIP_SYM + 1);     
            max_size   = SHIP_SIZE;           
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
            t6963c_writeCmd1(t6963c_CMD_writeData_Increment,symbol[index]);
        }
                
        //t6963c_stopAutoWrite();
        
        character->prev_column = column;
        character->prev_row = row;
    
    
}

void t6963c_spaceInvaders_draw(char row, char column, struct character_t* character){
    
    unsigned char dodge_left  = (character->state == CHAR_STATE_DODGE_LEFT)  ? INVADER_SIZE : 0 ;
    unsigned char dodge_right = (character->state == CHAR_STATE_DODGE_RIGHT) ? INVADER_SIZE : 0 ; 
    
    unsigned char symbol[2];
    unsigned char max_size = 1;
    unsigned char frame = character->frames; 
    
    
    switch(character->type){
         
        case CHAR_TYPE_INVADER_0:
            
            switch(character->state){
            
                case CHAR_STATE_HIT_1:
                    symbol[0]  =  EXPLOSION_SYM;
                    symbol[1]  = (EXPLOSION_SYM + 1);
                    //character->state = CHAR_STATE_DESTROYED;
                    break;
                case CHAR_STATE_DESTROYED:
                    symbol[0]  =  DATA_ZERO;
                    symbol[1]  =  DATA_ZERO; 
                    break;         
                default:  
                    symbol[0]  =  INVADER_0_SYM      + frame + dodge_left;
                    symbol[1]  = (INVADER_0_SYM + 1) + frame + dodge_right;
                    //character->state = CHAR_STATE_NORMAL;
                    break;
            }
                
            max_size   =  INVADER_SIZE;
           
            break;
            
        case CHAR_TYPE_INVADER_1:
            
            switch(character->state){
            
                case CHAR_STATE_HIT_1:
                    symbol[0]  =  EXPLOSION_SYM;
                    symbol[1]  = (EXPLOSION_SYM + 1);
                    //character->state = CHAR_STATE_DESTROYED;
                    break;
                case CHAR_STATE_DESTROYED:
                    symbol[0]  =  DATA_ZERO;
                    symbol[1]  =  DATA_ZERO; 
                    break;         
                default:
                                
                    symbol[0]  =  INVADER_1_SYM      + frame + dodge_left;
                    symbol[1]  = (INVADER_1_SYM + 1) + frame + dodge_right;
                    //character->state = CHAR_STATE_NORMAL;
                    break;
            }
            max_size = INVADER_SIZE;
            break;
            
        case CHAR_TYPE_INVADER_2:
            
            switch(character->state){
            
                case CHAR_STATE_HIT_1:
                    symbol[0]  =  EXPLOSION_SYM;
                    symbol[1]  = (EXPLOSION_SYM + 1);
                    //character->state = CHAR_STATE_DESTROYED;
                    break;
                case CHAR_STATE_DESTROYED:
                    symbol[0]  =  DATA_ZERO;
                    symbol[1]  =  DATA_ZERO; 
                    break;         
                default:            
                    symbol[0]  =  INVADER_2_SYM      + frame + dodge_left;
                    symbol[1]  = (INVADER_2_SYM + 1) + frame + dodge_right;
                    //character->state = CHAR_STATE_NORMAL;
                    break;
            }
            max_size = INVADER_SIZE;
            break;
            
        case CHAR_TYPE_BARRIER:
            
            switch(character->state){           
                case CHAR_STATE_HIT_1:
                    symbol[0]  =  BARRIER_SYM +   BARRIER_SIZE;
                    symbol[1]  = (BARRIER_SYM +   BARRIER_SIZE + 1);
                    break;
                case CHAR_STATE_HIT_2:
                    symbol[0]  =  BARRIER_SYM +   2*BARRIER_SIZE;
                    symbol[1]  = (BARRIER_SYM +   2*BARRIER_SIZE + 1);
                   // character->state = CHAR_STATE_DESTROYED;
                    break;
                case CHAR_STATE_DESTROYED:
                    symbol[0]  =  DATA_ZERO;
                    symbol[1]  =  DATA_ZERO; 
                    break;         
                default:                         
                    symbol[0]  =  BARRIER_SYM;
                    symbol[1]  = (BARRIER_SYM + 1);    
                    break;
            }          
            
            max_size = BARRIER_SIZE;
            break;         
            
        case CHAR_TYPE_SPACESHIP_LASER:
            
            symbol[0]  = LASER_SYM;
            max_size   = LASER_SIZE;
            break;
            
        case CHAR_TYPE_SPACESHIP:
            symbol[0]  =  SPACESHIP_SYM;
            symbol[1]  = (SPACESHIP_SYM + 1);             
            max_size   = SHIP_SIZE;           
            break;
            
        case CHAR_TYPE_MOTHERSHIP:
            symbol[0]  =  MOTHERSHIP_SYM;
            symbol[1]  = (MOTHERSHIP_SYM + 1);     
            max_size   = SHIP_SIZE;           
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
             
        // Pone las coordenadas en pantalla para dibujar el sprite
        t6963c_set_address(row, column);
        //t6963c_startAutoWrite();
        
        //Dibuja el sprite de izquierda a derecha
        for( index = 0; index < max_size; index++){
            //t6963c_autoWrite(symbol + frame + index);
            t6963c_writeCmd1(t6963c_CMD_writeData_Increment,symbol[index]);
        }
                
        //t6963c_stopAutoWrite();
        
        character->prev_column = column;
        character->prev_row = row;
    
    
}
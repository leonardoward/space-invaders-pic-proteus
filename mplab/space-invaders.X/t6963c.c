/**
 * C library for interfacing a T6963C display with a PIC microcontroller
 * Copyright (C) 2015 Camil Staps <info@camilstaps.nl>

 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#include "t6963c.h"

inline void delay_ns(unsigned short ns) {
    //t6963c_startTimer();
    //while (t6963c_getTimeNs() < ns);
    //t6963c_stopTimer();
    __delay32( (unsigned long) (((unsigned long long) ns)*(FCY)/1000000000ULL));
}

void t6963c_writeByte(unsigned cd, char byte) {
    t6963c_cd(cd);
    t6963c_wr(LOW);
	t6963c_data(byte);
    t6963c_ce(LOW);
    delay_ns(1); //delay_ns(200) //Reduced to improve Proteus performance
    t6963c_ce(HIGH);
    t6963c_wr(HIGH);
    delay_ns(1); //delay_ns(200) //Reduced to improve Proteus performance
    
}

void t6963c_writeCmd1(char cmd, char data) {
    t6963c_writeByte(DATA, data);
    t6963c_writeByte(CMD, cmd);
    delay_ns(1); //delay_ns(60000) //Reduced to improve Proteus performance
}

void t6963c_writeCmd2(char cmd, char data1, char data2) {
    t6963c_writeByte(DATA, data1);
    t6963c_writeByte(DATA, data2);
    t6963c_writeByte(CMD, cmd);
    delay_ns(1); //delay_ns(60000) //Reduced to improve Proteus performance
}

void t6963c_startAutoWrite(void) {
    t6963c_writeByte(CMD, t6963c_CMD_set_dataAutoWrite);
    delay_ns(1); //delay_ns(60000) //Reduced to improve Proteus performance
    // delay_ns(60000); //Commented to improve Proteus performance
}

void t6963c_stopAutoWrite(void) {
    t6963c_writeByte(CMD, t6963c_CMD_autoReset);
    delay_ns(1); //delay_ns(60000) //Reduced to improve Proteus performance
    // delay_ns(60000); //Commented to improve Proteus performance
}

void t6963c_autoWrite(char byte) {
    t6963c_cd(DATA);
    t6963c_wr(LOW);
    t6963c_data(byte);
    t6963c_ce(LOW);
    delay_ns(1); //delay_ns(200) //Reduced to improve Proteus performance
    t6963c_ce(HIGH);
    t6963c_wr(HIGH);
    delay_ns(1); //delay_ns(200) //Reduced to improve Proteus performance
}

inline void t6963c_autoWriteChar(char byte) {
    t6963c_autoWrite(byte - ASCCI_2_T6963C_OFFSET);
}

void t6963c_writeString(char* string) {
    t6963c_startAutoWrite();
    for (;*string;string++)
        t6963c_autoWriteChar(*string);
    t6963c_stopAutoWrite();
}

void t6963c_clear(void) {
    unsigned short i;
    t6963c_set_address(DATA_ZERO, DATA_ZERO);
    t6963c_startAutoWrite();
    for (i = 0; i < t6963c_rows * t6963c_columns; i++) {
        t6963c_autoWrite(DATA_ZERO);
    }
    t6963c_writeCmd2(0x24, DATA_ZERO, t6963c_CMD_set_addressPointer);
    for (i = 0; i < t6963c_rows * t6963c_columns; i++) {
        t6963c_autoWrite(t6963c_attr_normal);
    }
    t6963c_stopAutoWrite();
    t6963c_set_cursor_address(0, 0);
}

void t6963c_init(void) {
    unsigned short i;
    
    t6963c_t_rst(LOW);
    t6963c_t_cd(DATA);
    t6963c_t_ce(LOW);
    t6963c_t_rd(LOW);
    t6963c_t_wr(LOW);
    t6963c_t_data(DATA_ZERO);
    
    t6963c_wr(HIGH);
    t6963c_rd(HIGH);
    t6963c_cd(CMD);
    t6963c_ce(HIGH);
    
    t6963c_rst(LOW);
   /*for (i = 0; i < 10; i++) //Commented to improve Proteus performance
        delay_ns(60000);*/
    t6963c_rst(HIGH);
    
    t6963c_writeCmd2(t6963c_CMD_set_textHomeAddress, DATA_ZERO, DATA_ZERO);             // text home address
    t6963c_writeCmd2(t6963c_CMD_set_textArea, t6963c_columns, DATA_ZERO);               // text area set
    t6963c_writeCmd2(t6963c_CMD_set_graphicHomeAddress, DATA_ZERO, 0x03);             // graphic home address
    t6963c_writeCmd2(t6963c_CMD_set_graphicArea, t6963c_columns, DATA_ZERO);   // graphic area set
    
    t6963c_writeByte(CMD, t6963c_CMD_set_textAttributeMode);    // text attribute, internal ROM
    t6963c_writeByte(CMD, (t6963c_CMD_MASK_display_textON_grapON | t6963c_CMD_MASK_display_cursorON_blinkON));    // graphic, text, cursor, blink
    t6963c_writeByte(CMD, t6963c_CMD_set_oneLineCursor);          // 8-line cursor
    
    t6963c_clear();
    
    t6963c_set_address(DATA_ZERO, DATA_ZERO);
    t6963c_set_cursor_address(DATA_ZERO, DATA_ZERO);
    
    //t6963c_initTimer(); 
}

void t6963c_set_address(unsigned char row, unsigned char column) {
    unsigned short address = ((unsigned short) row) * ((unsigned short) t6963c_columns) + column;
    t6963c_writeCmd2(t6963c_CMD_set_addressPointer, address & 0xff, ((address >> 8) & 0xff));
}

void t6963c_set_cursor_address(unsigned char row, unsigned char column) {
    t6963c_writeCmd2(t6963c_CMD_set_cursorPointer, column, row);
}

/*
void t6963c_update_terminal(Terminal* term) {
    unsigned int i;
    unsigned char row, column;
    
    while (terminal.lines_needed(term->content, t6963c_columns) > t6963c_rows)
        terminal.discard_first_line(term->content, t6963c_columns);
    
    row = 0;
    column = 0;
    t6963c_set_address(0, 0);
    t6963c_startAutoWrite();
    for (i=0; term->content[i]; i++) {
        if (term->content[i] == '\n') {
            t6963c_autoWriteChar(' ');
            while ((column = (column + 1) % t6963c_columns))
                t6963c_autoWriteChar(' ');
            row++;
        } else {
            t6963c_autoWriteChar(term->content[i]);
            column = (column + 1) % t6963c_columns;
            if (column == 0)
                row++;
        }
    }
    t6963c_stopAutoWrite();
    t6963c_set_cursor_address(row, column);
    t6963c_startAutoWrite();
    while (row != t6963c_rows) {
        t6963c_autoWriteChar(' ');
        column = (column + 1) % t6963c_columns;
        if (column == 0)
            row++;
    }
    t6963c_stopAutoWrite();
}
*/

/*
 * lcd.c
 *
 *  Created on: Jun 20, 2025
 *      Author: Administrator
 */

#include "lcd.h"

#define lcd4_bit

void lcd_init(){
#ifdef lcd4_bit

	delay_ms(10); send_cmd_lcd (0x2);  // 4bit mode
	delay_ms(1000); send_cmd_lcd (0x28); // Function set --> DL=0 (4 bit mode), N = 1 (2 line display) F = 0 (5x8 characters)
	delay_ms(1);
#else
	send_cmd_lcd (0x38); // Function set --> DL=0 (4 bit mode), N = 1 (2 line display) F = 0 (5x8 characters)
	delay_ms(1);
#endif

	send_cmd_lcd(0x0C); delay_ms(1);
	send_cmd_lcd(0x01); delay_ms(2);
	send_cmd_lcd(0x06); delay_ms(1);

	delay_ms(200);
	lcd_put_cur(0,0);
	send_string_lcd("Init LCD successfull"); // Test
//	lcd_put_cur(1,0);
//	send_string_lcd("Init LCD successfull"); // Test
//	lcd_put_cur(2,0);
//	send_string_lcd("Init LCD successfull"); // Test
//	lcd_put_cur(3,0);
//	send_string_lcd("Init LCD successfull"); // Test
	delay_ms(500);
	lcd_clear();
}

void write_data_lcd(char data){
	Write_data((uint8_t)data, DS3, LSB);
}

void send_cmd_lcd(char data){

#ifdef lcd4_bit
	char tmp;
	tmp = ((data >> 4) | 0x20) & 0x3F;
	write_data_lcd(tmp);

	tmp = data & 0x0F;
	write_data_lcd(tmp);
#else
	write_data_lcd(data);
#endif	// LCD_4bit
}

void send_data_lcd(char data){

#ifdef lcd4_bit
    char tmp;
	tmp = ((data >> 4) | (1<<4)) & 0x1F;
	write_data_lcd(tmp);

	tmp = (data | (1<<4)) & 0x1F;
	write_data_lcd(tmp);
#else
	write_data_lcd(data);
#endif	// lcd4_bit

}

void send_string_lcd(char *data){
	while (*data){
		send_data_lcd(*data++);
	}
}

void lcd_clear(){
	send_cmd_lcd(0x01); delay_ms(2);
}

void lcd_put_cur(int row, int col){
    switch (row){
        case 0:
            col |= 0x80;
            break;
        case 1:
            col |= 0xC0;
            break;
        case 2:
            col |= 0x94;
            break;
        case 3:
            col |= 0xD4;
            break;
    }

    send_cmd_lcd (col);
}


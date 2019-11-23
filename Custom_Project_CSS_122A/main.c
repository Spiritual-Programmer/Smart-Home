/*
 * Custom_Project_CSS_122A.c
 *
 * Created: 11/20/2019 3:18:39 PM
 * Author : Kamaljot Singh
 */ 

#include <avr/io.h>
#include <lcd.h>
#include <timer.h>
#include <util/delay.h>

//Global Variables
unsigned char LRBtn = 0x00;
unsigned char BRBtn = 0x00;

//State Machines
enum LivingRoomLights_States {Start1,LRbtn_unpressed, LRbtn_pressed, LRafter_pressed} livingRoomLights_state;
unsigned char livingRoomlights;
unsigned char LRlightsisOn = 1;
void livingRoomLights() {
	LRBtn = ~PINA& 0x01;
	switch (livingRoomLights_state) { //Transitions
		case Start1:
		livingRoomLights_state= LRbtn_unpressed;
		break;
		case LRbtn_unpressed:
		if (LRBtn)
		{
			livingRoomLights_state = LRbtn_pressed;
		}
		else
		livingRoomLights_state= LRbtn_unpressed;
		break;
		case LRbtn_pressed:
		livingRoomLights_state = LRafter_pressed;
		break;
		case LRafter_pressed:
		if (!LRBtn)
		{
			livingRoomLights_state = LRbtn_unpressed;
		}
		else
		livingRoomLights_state = LRafter_pressed;
		break;

		default:
		break;
	}
	
	switch (livingRoomLights_state) { //Actions
		case Start1:
		break;
		case LRbtn_unpressed:
		break;
		case LRbtn_pressed:
		LRlightsisOn = !LRlightsisOn;
		break;
		case LRafter_pressed:
		break;
		
		default:
		break;
		
	}
PORTB = LRlightsisOn;
}

enum BedRoomLights_States {Start2,BRbtn_unpressed, BRbtn_pressed, BRafter_pressed} bedRoomLights_state;
unsigned char bedRoomlights;
unsigned char BRlightsisOn = 2;
void bedRoomLights() {
	BRBtn = ~PINA& 0x02;
	switch (bedRoomLights_state) { //Transitions
		case Start2:
		bedRoomLights_state= BRbtn_unpressed;
		break;
		case BRbtn_unpressed:
		if (BRBtn== 0x02)
		{
			bedRoomLights_state = BRbtn_pressed;
		}
		else
		bedRoomLights_state= BRbtn_unpressed;
		break;
		case BRbtn_pressed:
		bedRoomLights_state = BRafter_pressed;
		break;
		case BRafter_pressed:
		if (BRBtn!=0x02)
		{
			bedRoomLights_state = BRbtn_unpressed;
		}
		else
		bedRoomLights_state = BRafter_pressed;
		break;

		default:
		break;
	}
	
	switch (bedRoomLights_state) { //Actions
		case Start2:
		break;
		case BRbtn_unpressed:
		break;
		case BRbtn_pressed:
		if (BRlightsisOn == 2) {
			BRlightsisOn = 0;
		}
		else if (BRlightsisOn == 0)
		{
			BRlightsisOn = 2;
		}
		break;
		case BRafter_pressed:
		break;
		
		default:
		break;
		
	}
	PORTB = BRlightsisOn;
}

int main(void)
{
    DDRA = 0x00; PORTA = 0xFF; //input from port A
    DDRB = 0xFF; PORTB = 0x00; //output of led
	
	LCD_init();
	
	PORTB = 0x04;
	PORTB = 0x08;
	PORTB = 0x16;
	PORTB = 0x32;
	
	//State Machines
	livingRoomLights_state = Start1;
	bedRoomLights_state = Start2;
    while (1) 
    {
		livingRoomLights();
		bedRoomLights();
    }
}


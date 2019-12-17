/*
 * Custom_Project_CSS_122A.c
 *
 * Created: 11/20/2019 3:18:39 PM
 * Author : Kamaljot Singh
 */ 

#include <avr/io.h>
#include "usart_ATmega1284.h"
#include "lcd.h"
//#include "io.c"
#include <timer.h>
#include <util/delay.h>

//Global Variables
unsigned char LRBtn = 0x00;
unsigned char BRBtn = 0x00;
unsigned char BathRBtn = 0x00;
unsigned char KRBtn = 0x00;
unsigned char GBtn = 0x00;
unsigned char DBtn = 0x00;
unsigned char data_value = 0;
unsigned char data_value2 = 0;
unsigned char data_value3 = 0;

unsigned char LRlightsisOn =1;
unsigned char BRlightsisOn = 2;
unsigned char BathRlightsisOn = 4;
unsigned char KRlightsisOn = 8;
unsigned char GateisLocked = 1;
unsigned char isDoorLocked = 4;



void usart_fcn (unsigned char tempOutput) {
	if ( USART_HasReceived(0)) {
		//...receive data...
		data_value = USART_Receive(0);
		USART_Send(0xFF,0);
		if (data_value == '1')
		{
			PORTB = tempOutput;
		}
		
		else if (data_value == '2')
		
		{
			PORTB = 0;
			USART_Send(0,0);
		}
		
	}
}
enum UsartReceive2_States {Wait3, HasRecieved2} usartReceive2_state;
void usartReceive2() {
	
	switch (usartReceive2_state) // Transitions
	{
		case Wait3:
		usartReceive2_state = HasRecieved2;
		break;
		case HasRecieved2:
		usartReceive2_state = Wait3;
		break;
		default:
		break;
		
	}
	
	switch (usartReceive2_state) // Actions
	{
		case Wait3:
		break;
		case HasRecieved2:
				
		if ( USART_HasReceived(1)) {
			//...receive data...
			data_value3 = USART_Receive(1);
			
			if (data_value3 == '1')
			
			{
				PORTB =1;
				if (GateisLocked == 0)
				{
					
					GateisLocked = 1;
				}
				else if (GateisLocked == 1)
				{
					
					GateisLocked = 0;
				}

			
			}
			
			
		}
		break;
		default:
		break;
		
	}
}


enum UsartReceive_States {Wait, HasRecieved} usartReceive_state;
	
void usartReceive() {
	
	switch (usartReceive_state) // Transitions
	{
		case Wait:
		usartReceive_state = HasRecieved;
		break;
		case HasRecieved:
		usartReceive_state = Wait;
		break;
		default:
		break;
		
	}
	
	switch (usartReceive_state) // Actions
	{
		case Wait:
		break;
		case HasRecieved:
		
		//if (GateisLocked == 16)
		//{
			//USART_Send(0x02,1);
			//LCD_Cursor(23);
			//LCD_WriteData( 0 + '0');
		//}
		//else if (GateisLocked == 0)
		//{
			//USART_Send(0x01,1);
			//LCD_Cursor(23);
			//LCD_WriteData( 1 + '0');
		//}
			
			
		if ( USART_HasReceived(0)) {
			//...receive data...
			data_value = USART_Receive(0);
			if (data_value == '1')
			{
				if (LRlightsisOn == 0)
				{
					LRlightsisOn = !LRlightsisOn ;
					LCD_Cursor(4);
					LCD_WriteData( 1 + '0');
				}
	
				else if (LRlightsisOn==1)
				{
					LRlightsisOn = !LRlightsisOn ;
					LCD_Cursor(4);
					LCD_WriteData( 0 + '0');
				}
				
			}
			
			else if (data_value == '2')
			
			{
				if (BRlightsisOn == 0)
				{
					BRlightsisOn = 2;
					LCD_Cursor(9);
					LCD_WriteData( 1 + '0');
				}
				else
				{
					BRlightsisOn = 0;
					LCD_Cursor(9);
					LCD_WriteData( 0 + '0');
				}
			}
			
			else if (data_value == '3')
			
			{
				if (BathRlightsisOn == 0)
				{
					BathRlightsisOn = 4;
					LCD_Cursor(15);
					LCD_WriteData( 1 + '0');
				}
				else
				{
					BathRlightsisOn = 0;
					LCD_Cursor(15);
					LCD_WriteData( 0 + '0');
				}
			}
			
			else if (data_value == '4')
			
			{
				if (KRlightsisOn == 0)
				{
					KRlightsisOn = 8;
					LCD_Cursor(19);
					LCD_WriteData( 1 + '0');
				}
				else
				{
					KRlightsisOn = 0;
					LCD_Cursor(19);
					LCD_WriteData( 0 + '0');
				}
			}
			else if (data_value == '5')
			{
				if (isDoorLocked == 4)
				{
					TCCR1A|= 0x00;        //NON Inverted PWM
					TCCR1B|=(1<<WGM13)|(1<<WGM12)|(1<<CS11)|(1<<CS10); //PRESCALER=64 MODE 14(FAST PWM)
					
					ICR1 = 4999;

					OCR1A = 135; //18000
					_delay_ms(100);
					OCR1A = 425; //18000
					_delay_ms(100);
					OCR1A=535;  //180 degree
					_delay_ms(100);

					
					isDoorLocked = 8;
					LCD_Cursor(27);
					LCD_WriteData( 1 + '0');
				}
				else if (isDoorLocked == 8)
			
				{
					 TCCR1A|=(1<<COM1A1)|(1<<COM1B1)|(1<<WGM11);        //NON Inverted PWM
					 TCCR1B|=(1<<WGM13)|(1<<WGM12)|(1<<CS11)|(1<<CS10); //PRESCALER=64 MODE 14(FAST PWM)
					 
					 ICR1 = 4999;
					 
					 OCR1A=535;  //180 degree
					 _delay_ms(100);
					 OCR1A = 425; //18000
					 _delay_ms(100);
					 OCR1A = 135; //18000
					 _delay_ms(100);
					 
					 
					 
					 isDoorLocked = 4;
					 LCD_Cursor(27);
					 LCD_WriteData( 0 + '0');
				}
				
			}
			else if (data_value == '6')
			{
				if (USART_IsSendReady(1))
				{
				
					if (GateisLocked == 1)
					{
						USART_Send(0x01,1);
						GateisLocked =0;
						LCD_Cursor(23);
						LCD_WriteData( 0 + '0');
					}
					else if (GateisLocked == 0)
					{
						USART_Send(0x01,1);
						GateisLocked = 1;
						LCD_Cursor(23);
						LCD_WriteData( 1 + '0');
					}
				}
			}
				
			
			
		}
		break;
		default:
		break;
			
	}
}

//State Machines
enum LivingRoomLights_States {Start1,LRbtn_unpressed, LRbtn_pressed, LRafter_pressed} livingRoomLights_state;
unsigned char livingRoomlights;
//unsigned char LRlightsisOn =1 ;

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
		if (LRlightsisOn ==1)
		{
				LCD_Cursor(4);
				LCD_WriteData( 1 + '0');	
		}
		else
		{
				LCD_Cursor(4);
				LCD_WriteData( 0 + '0');
		}
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
			LCD_Cursor(9);
			LCD_WriteData( 0 + '0');
		}
		else if (BRlightsisOn == 0)
		{
			BRlightsisOn = 2;
			LCD_Cursor(9);
			LCD_WriteData( 1 + '0');
		}
		break;
		case BRafter_pressed:
		break;
		
		default:
		break;
		
	}
	PORTB = BRlightsisOn;
}


enum BathRoomLights_States {Start3,BathRbtn_unpressed, BathRbtn_pressed, BathRafter_pressed} bathRoomLights_state;
unsigned char bathRoomlights;

void bathRoomLights() {
	BathRBtn = ~PINA& 0x04;
	switch (bathRoomLights_state) { //Transitions
		case Start3:
		bathRoomLights_state= BathRbtn_unpressed;
		break;
		case BathRbtn_unpressed:
		if (BathRBtn== 0x04)
		{
			bathRoomLights_state = BathRbtn_pressed;
		}
		else
		bathRoomLights_state= BathRbtn_unpressed;
		break;
		case BathRbtn_pressed:
		bathRoomLights_state = BathRafter_pressed;
		break;
		case BathRafter_pressed:
		if (BathRBtn!=0x04)
		{
			bathRoomLights_state = BathRbtn_unpressed;
		}
		else
		bathRoomLights_state = BathRafter_pressed;
		break;

		default:
		break;
	}
	
	switch (bathRoomLights_state) { //Actions
		case Start3:
		break;
		case BathRbtn_unpressed:
		break;
		case BathRbtn_pressed:
		if (BathRlightsisOn == 4) {
			BathRlightsisOn = 0;
			LCD_Cursor(15);
			LCD_WriteData( 0 + '0');
		}
		else if (BathRlightsisOn == 0)
		{
			BathRlightsisOn = 4;
			LCD_Cursor(15);
			LCD_WriteData( 1 + '0');
		}
		break;
		case BathRafter_pressed:
		break;
		
		default:
		break;
		
	}
	PORTB = BathRlightsisOn;
}


enum KitchenRoomLights_States {Start4,KRbtn_unpressed, KRbtn_pressed, KRafter_pressed} kitchenRoomLights_state;
unsigned char kitchenRoomlights;

void kitchenRoomLights() {
	KRBtn = ~PINA& 0x08;
	switch (kitchenRoomLights_state) { //Transitions
		case Start4:
		kitchenRoomLights_state= KRbtn_unpressed;
		break;
		case KRbtn_unpressed:
		if (KRBtn== 0x08)
		{
			kitchenRoomLights_state = KRbtn_pressed;
		}
		else
		kitchenRoomLights_state= KRbtn_unpressed;
		break;
		case KRbtn_pressed:
		kitchenRoomLights_state = KRafter_pressed;
		break;
		case KRafter_pressed:
		if (KRBtn!=0x08)
		{
			kitchenRoomLights_state = KRbtn_unpressed;
		}
		else
		kitchenRoomLights_state = KRafter_pressed;
		break;

		default:
		break;
	}
	
	switch (kitchenRoomLights_state) { //Actions
		case Start4:
		break;
		case KRbtn_unpressed:
		break;
		case KRbtn_pressed:
		if (KRlightsisOn == 8) {
			KRlightsisOn = 0;
			LCD_Cursor(19);
			LCD_WriteData( 0 + '0');
		}
		else if (KRlightsisOn == 0)
		{
			KRlightsisOn = 8;
			LCD_Cursor(19);
			LCD_WriteData( 1 + '0');
		}
		break;
		case KRafter_pressed:
		break;
		
		default:
		break;
		
	}
	PORTB = KRlightsisOn;
}

enum Motor_States {Start5, A, AB, B, BC, C, CD, D, DA} motor_state;
unsigned char motorValue = 0x00;
void motorStates() {
	switch (motor_state) { //Transitions
		case Start5:
		motor_state = A;
		_delay_ms(3);
		break;
		case A:
		motor_state = AB;
		_delay_ms(3);
		break;
		case AB:
		motor_state = B;
		_delay_ms(3);
		break;
		case B:
		motor_state = BC;
		_delay_ms(3);
		break;
		case BC:
		motor_state = C;
		_delay_ms(3);
		break;
		case C:
		motor_state = CD;
		_delay_ms(3);
		break;
		case CD:
		motor_state = D;
		_delay_ms(3);
		break;
		case D:
		motor_state = DA;
		_delay_ms(3);
		break;
		case DA:
		motor_state = A;
		_delay_ms(3);
		break;
		default:
		motor_state = A;
		_delay_ms(3);
		break;

	}
	
	switch (motor_state) { //Actions
		case Start5:
		break;
		case A:
		motorValue = 16;
		break;
		case AB:
		motorValue = 48;
		break;
		case B:
		motorValue = 32;
		break;
		case BC:
		motorValue = 96;
		break;
		case C:
		motorValue = 64;
		break;
		case CD:
		motorValue = 192;
		break;
		case D:
		motorValue = 128;
		break;
		case DA:
		motorValue = 144;
		break;
		default:
		motorValue = 0;
		break;

	}
	PORTB = motorValue;
}

enum Motor_StatesReverse {Start7, RA, RAB, RB, RBC, RC, RCD, RD, RDA} motor_statereverse;
//unsigned char motorValue = 0x00;
unsigned char count = 7;
void motorStatesreverse() {
	switch (motor_statereverse) { //Transitions
		case Start7:
		motor_statereverse = RDA;
		_delay_ms(3);

		break;
		case RDA:
		motor_statereverse = RD;
		_delay_ms(3);
		break;
		case RD:
		motor_statereverse = RCD;
		_delay_ms(3);
		break;
		case RCD:
		motor_statereverse = RC;
		_delay_ms(3);
		break;
		case RC:
		motor_statereverse = RBC;
		_delay_ms(3);
		break;
		case RBC:
		motor_statereverse = RB;
		_delay_ms(3);
		break;
		case RB:
		motor_statereverse = RAB;
		_delay_ms(3);
		break;
		case RAB:
		motor_statereverse = RA;
		_delay_ms(3);
		break;
		case RA:
		motor_statereverse = RDA;
		_delay_ms(3);
		break;
		default:
		motor_statereverse = RDA;
		_delay_ms(3);
		break;

	}
	
	switch (motor_statereverse) { //Actions
		case Start7:
		break;
		case RA:
		motorValue = 16;
		break;
		case RAB:
		motorValue = 48;
		break;
		case RB:
		motorValue = 32;
		break;
		case RBC:
		motorValue = 96;
		break;
		case RC:
		motorValue = 64;
		break;
		case RCD:
		motorValue = 192;
		break;
		case RD:
		motorValue = 128;
		break;
		case RDA:
		motorValue = 144;
		break;
		default:
		motorValue = 0;
		break;

	}
	PORTB = motorValue;
}

enum Gate_States {Start8,Gbtn_unpressed, Gbtn_pressed, Gafter_pressed} gate_state;

void gate() {
	GBtn = ~PINA& 0x10;
	switch (gate_state) { //Transitions
		case Start8:
		gate_state= Gbtn_unpressed;
		break;
		case Gbtn_unpressed:
		if (GBtn== 0x10)
		{
			gate_state = Gbtn_pressed;
		}
		else
		gate_state= Gbtn_unpressed;
		break;
		case Gbtn_pressed:
		gate_state = Gafter_pressed;
		break;
		case Gafter_pressed:
		if (GBtn!=0x10)
		{
			gate_state = Gbtn_unpressed;
		}
		else
		gate_state = Gafter_pressed;
		break;

		default:
		break;
	}
	
	switch (gate_state) { //Actions
		case Start8:
		break;
		case Gbtn_unpressed:
		break;
		case Gbtn_pressed:
		if (GateisLocked == 1) {
			GateisLocked = 0;
			LCD_Cursor(23);
			LCD_WriteData( 0 + '0');
		}
		else if (GateisLocked == 0)
		{
			GateisLocked = 1;
			LCD_Cursor(23);
			LCD_WriteData( 1 + '0');
		}
		break;
		case Gafter_pressed:
		break;
		
		default:
		break;
		
	}
	//PORTB = GateisLocked;
}

enum DoorLock_States {Start6, Dbtn_unpressed, Dbtn_pressed, Dafter_pressed} doorLock_State;

void doorLock() {
	DBtn = ~PINA& 0x32;
	switch (doorLock_State) { //Transitions
		case Start6:
		doorLock_State= Dbtn_unpressed;
		break;
		case Dbtn_unpressed:
		if (DBtn == 32)
		{
			doorLock_State = Dbtn_pressed;
		}
		else
		doorLock_State= Dbtn_unpressed;
		break;
		case Dbtn_pressed:
		doorLock_State = Dafter_pressed;
		break;
		case Dafter_pressed:
	
		if (DBtn!=32)
		{
			doorLock_State = Dbtn_unpressed;
		}
		else
		doorLock_State = Dafter_pressed;
		break;

		default:
		break;
	}

	switch (doorLock_State) { //Actions
		case Start6:
		break;
		case Dbtn_unpressed:
		break;
		case Dbtn_pressed:
		if (isDoorLocked == 4) {
			//TCCR1A |= 1<<WGM11 | 1<<COM1A1 | 1<<COM1A0;
			//TCCR1B |= 1<<WGM12 | 1<<WGM13 | 1<<CS10;
			//ICR1 = 4999;
//
			//OCR1A = ICR1 -800; //18000
			//_delay_ms(300);
			//OCR1A = ICR1 -2000; //18000
			//_delay_ms(300);
			
			TCCR1A|= 0x00;        //NON Inverted PWM
			TCCR1B|=(1<<WGM13)|(1<<WGM12)|(1<<CS11)|(1<<CS10); //PRESCALER=64 MODE 14(FAST PWM)
			
			ICR1 = 4999;

			OCR1A = 135; //18000
			_delay_ms(100);
			OCR1A = 425; //18000
			_delay_ms(100);
			OCR1A=535;  //180 degree
			_delay_ms(100);

			
			isDoorLocked = 8;
			LCD_Cursor(27);
			LCD_WriteData( 1 + '0');
		}
		else if (isDoorLocked == 8)
		{
			//TCCR1A |= 1<<WGM11 | 1<<COM1A1 | 1<<COM1A0;
			//TCCR1B |= 1<<WGM12 | 1<<WGM13 | 1<<CS10;
			
			 TCCR1A|=(1<<COM1A1)|(1<<COM1B1)|(1<<WGM11);        //NON Inverted PWM
			 TCCR1B|=(1<<WGM13)|(1<<WGM12)|(1<<CS11)|(1<<CS10); //PRESCALER=64 MODE 14(FAST PWM)
			 
			ICR1 = 4999;
			
			OCR1A=535;  //180 degree
			_delay_ms(100);
			OCR1A = 425; //18000
			_delay_ms(100);
			OCR1A = 135; //18000
			_delay_ms(100);
		
			

			
			isDoorLocked = 4;
			LCD_Cursor(27);
			LCD_WriteData( 0 + '0');
		}
		break;
		case Dafter_pressed:
		break;
	
		default:
		break;
	
	}
	PORTD = isDoorLocked;
	}


void doorLocktest() {
	TCCR1A |= 1<<WGM11 | 1<<COM1A1 | 1<<COM1A0;
	TCCR1B |= 1<<WGM12 | 1<<WGM13 | 1<<CS10;
	ICR1 = 1999;

	//OCR1A = ICR1 -800; //18000
	//_delay_ms(100);
	//OCR1A = ICR1 -2000; //18000
	//_delay_ms(100);

}



void lcdInfo () {
		//LR
		LCD_Cursor(4);
		LCD_WriteData( 1 + '0');
		//BedRoom
		LCD_Cursor(9);
		LCD_WriteData( 1 + '0');
		//Bathroom
		LCD_Cursor(15);
		LCD_WriteData( 1 + '0');
		//Kitchen
		LCD_Cursor(19);
		LCD_WriteData( 1 + '0');
		//Gate
		LCD_Cursor(23);
		LCD_WriteData( 0 + '0');
		//Door Lock
		LCD_Cursor(27);
		LCD_WriteData( 0 + '0');
	}

int main(void)
{
    DDRA = 0x00; PORTA = 0xFF; //input from port A
    DDRB = 0xFF; PORTB = 0x00; //output of led
	DDRC = 0xFF; PORTC = 0x00; //output
	DDRD = 0xFF; PORTD = 0x00; //output
	

	initUSART(0);	// initialize USART 0
	initUSART(1);
	unsigned char score = 1;
	char display_score[10];
	LCD_init();
	sprintf(display_score, "%d", score);
	LCD_DisplayString(1, "LR:  BR:  BTR:  K:  G:  D:");
	
	lcdInfo();
	//State Machines
	//livingRoomLights_state = Start1;
	//bedRoomLights_state = Start2;
	//bathRoomLights_state = Start3;
	//kitchenRoomLights_state = Start4;
	
	gate_state = Start8;
	motor_state = Start5;
	motor_statereverse = Start7;
	usartReceive2_state = Wait3;
	
	//usartReceive_state = Wait;
	//doorLock_State = Start6;
	//doorLocktest();




	//DDRD|=(1<<PD4)|(1<<PD5);   //PWM Pins as Out

    while (1) 
    {	

		if (GateisLocked == 1)
		{
			motorStates();
		}
		
		else if (GateisLocked == 0)
		{
			motorStatesreverse();
		}

		
		//usartReceive();
		//livingRoomLights();
		//bedRoomLights();
		//bathRoomLights();
		//kitchenRoomLights();
		//doorLock();
	/////doorLocktest();
		usartReceive2();
		gate();

	
		if ( USART_HasReceived(1)) {
			//...receive data...
			data_value3 = USART_Receive(1);
			
			if (data_value3 == '1')
			
			{
				PORTB =1;
			}
		}
    }
}


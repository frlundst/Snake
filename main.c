/*Written by Fredrik Lundström and Michell Dib 2021 (c)*/

#include <stdint.h>
#include <pic32mx.h>
#include "snake.h" 

void user_isr(){
	return;
}

int main(void){
	/*
	  This will set the peripheral bus clock to the same frequency
	  as the sysclock. That means 80 MHz, when the microcontroller
	  is running at 80 MHz. Changed 2017, as recommended by Axel.
	*/
	SYSKEY = 0xAA996655;  /* Unlock OSCCON, step 1 */
	SYSKEY = 0x556699AA;  /* Unlock OSCCON, step 2 */
	while(OSCCON & (1 << 21)); /* Wait until PBDIV ready */
	OSCCONCLR = 0x180000; /* clear PBDIV bit <0,1> */
	while(OSCCON & (1 << 21));  /* Wait until PBDIV ready */
	SYSKEY = 0x0;  /* Lock OSCCON */
	
	/* Set up output pins */
	AD1PCFG = 0xFFFF;
	ODCE = 0x0;
	TRISECLR = 0xFF;
	PORTE = 0x0;
	
	/* Output pins for display signals */
	PORTF = 0xFFFF;
	PORTG = (1 << 9);
	ODCF = 0x0;
	ODCG = 0x0;
	TRISFCLR = 0x70;
	TRISGCLR = 0x200;
	
	/* Set up input pins */
	TRISDSET = (1 << 8);
	TRISFSET = (1 << 1);
	
	/* Set up SPI as master */
	SPI2CON = 0;
	SPI2BRG = 4;
	/* SPI2STAT bit SPIROV = 0; */
	SPI2STATCLR = 0x40;
	/* SPI2CON bit CKP = 1; */
        SPI2CONSET = 0x40;
	/* SPI2CON bit MSTEN = 1; */
	SPI2CONSET = 0x20;
	/* SPI2CON bit ON = 1; */
	SPI2CONSET = 0x8000;

	display_init(); //Initialize OLED display 

	score = 0; //Set score to one

	snake.y = snakeY; //Set y to array
	snake.x = snakeX; //Set x to array

	snake.y[0] = 16; //Initialize snake
	snake.x[0] = 64; //We make the snake big at first for demonstration purposes only
	snake.y[1] = 16;
	snake.x[1] = 65;
	snake.y[2] = 16;
	snake.x[2] = 66;
	snake.y[3] = 16;
	snake.x[3] = 67;
	snake.y[4] = 16;
	snake.x[4] = 68;
	snake.y[5] = 16;
	snake.x[5] = 69;
	snake.y[6] = 16;
	snake.x[6] = 70;
	snake.y[7] = 16;
	snake.x[7] = 71;
	snake.y[8] = 16;
	snake.x[8] = 72;
	snake.y[9] = 16;
	snake.x[9] = 73;

	
	snake.length = 10;
	snake.dir = 'L'; 

	while(1){
		display_start(); //Start display
	}

	return;
}




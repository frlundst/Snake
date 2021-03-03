/*Written by Fredrik Lundström and Michell Dib 2021 (c)*/

#include <stdint.h>
#include <pic32mx.h> 
#include "snake.h" //Project header file

void *stdin, *stdout, *stderr;

#define DISPLAY_CHANGE_TO_COMMAND_MODE (PORTFCLR = 0x10)
#define DISPLAY_CHANGE_TO_DATA_MODE (PORTFSET = 0x10)

#define DISPLAY_ACTIVATE_RESET (PORTGCLR = 0x200)
#define DISPLAY_DO_NOT_RESET (PORTGSET = 0x200)

#define DISPLAY_ACTIVATE_VDD (PORTFCLR = 0x40)
#define DISPLAY_ACTIVATE_VBAT (PORTFCLR = 0x20)

#define DISPLAY_TURN_OFF_VDD (PORTFSET = 0x40)
#define DISPLAY_TURN_OFF_VBAT (PORTFSET = 0x20)

/*If any point in the array is set to one the pixel att the same position be lit*/
uint8_t display[32][128]; //Human readable pixel position and activation
uint8_t oled_display[512]; //Computer readable pixel position and activation

/*(TAKEN FROM LAB) Quick sleep timer*/
void quicksleep(int cyc) {
	int i;
	for(i = cyc; i > 0; i--);
}

/*(TAKEN FROM LAB) Send data to the OLED display*/
uint8_t spi_send_recv(uint8_t data) { //LAB
	while(!(SPI2STAT & 0x08));
	SPI2BUF = data;
	while(!(SPI2STAT & 1));
	return SPI2BUF;
}

/*(TAKEN FROM LAB) Initialize OLED display*/
void display_init(void){
	DISPLAY_CHANGE_TO_COMMAND_MODE;
	quicksleep(10);
	DISPLAY_ACTIVATE_VDD;
	quicksleep(1000000);
	
	spi_send_recv(0xAE);
	DISPLAY_ACTIVATE_RESET;
	quicksleep(10);
	DISPLAY_DO_NOT_RESET;
	quicksleep(10);
	
	spi_send_recv(0x8D);
	spi_send_recv(0x14);
	
	spi_send_recv(0xD9);
	spi_send_recv(0xF1);
	
	DISPLAY_ACTIVATE_VBAT;
	quicksleep(10000000);
	
	spi_send_recv(0xA1);
	spi_send_recv(0xC8);
	
	spi_send_recv(0xDA);
	spi_send_recv(0x20);
	
	spi_send_recv(0xAF);
}

void display_string(int line, char *s) { //LAB
	int i;
	if(line < 0 || line >= 4)
		return;
	if(!s)
		return;
	for(i = 0; i < 16; i++)
		if(*s) {
			textbuffer[line][i] = *s;
			s++;
		} else
			textbuffer[line][i] = ' ';
}

void display_update(void) { //LAB
	int i, j, k;
	int c;
	for(i = 0; i < 4; i++) {
		DISPLAY_CHANGE_TO_COMMAND_MODE;
		spi_send_recv(0x22);
		spi_send_recv(i);
		
		spi_send_recv(0x0);
		spi_send_recv(0x10);
		
		DISPLAY_CHANGE_TO_DATA_MODE;
		
		for(j = 0; j < 16; j++) {
			c = textbuffer[i][j];
			if(c & 0x80)
				continue;
			
			for(k = 0; k < 8; k++)
				spi_send_recv(font[c*8 + k]);
		}
	}
}

/*(TAKEN FROM LAB) This will print any image on the display with the help of an array containing the map of the active and inactive pixels*/
void display_image(int x, const uint8_t *data) { //LAB
	int i, j;
	
	for(i = 0; i < 4; i++) {
		DISPLAY_CHANGE_TO_COMMAND_MODE;

		spi_send_recv(0x22);
		spi_send_recv(i);
		
		spi_send_recv(x & 0xF);
		spi_send_recv(0x10 | ((x >> 4) & 0xF));
		
		DISPLAY_CHANGE_TO_DATA_MODE;
		
		for(j = 0; j < 128; j++)
			spi_send_recv(data[i*128 + j]);
	}
}

void translateToImage() {
  int page, column, row, c, k;
  uint8_t powerOfTwo = 1;
  uint8_t oledNumber = 0;
  int survivalMode = 0;

  for(page = 0; page < 4; page++) {
    for(column = 0; column < 128; column++) {
      powerOfTwo = 1;
      oledNumber = 0;

      for(row = 0; row < 8; row++) {
        if(display[8 * page + row][column]) {
          oledNumber |= powerOfTwo;
        }
        powerOfTwo <<= 1;
      }
      oled_display[column + page * 128] = oledNumber;
    }
  }
}

void create_object(int xPos, int yPos, int width, int height) {
  int row, column;

  for (row = 0; row < 32; row++) {
    for (column = 0; column < 128; column++) {
      if (row >= yPos && row <= (yPos + height) && column >= xPos && column <= (xPos + width)) {
        display[row][column] = 1;
      }
    }
  }
}

void clear_display() {
  int row, column, i;

  for(row = 0; row < 32; row++) {
    for(column = 0; column < 128; column++) {
      display[row][column] = 0;
    }
  }

  for (i = 0; i < 512; i++) {
    oled_display[i] = 0;
  }
}

void display_start(){
	clear_display();
	snake();
	//create_object(64,16,1,1);
	translateToImage();
	display_image(0, oled_display);
}




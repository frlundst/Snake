#include <stdint.h>
#include <pic32mx.h>
#include "snake.h" 

uint8_t spi_send_recv(uint8_t data);
extern char textbuffer[4][16];

int main(void);
void quicksleep(int cyc);
void display_init(void);
void display_string(int line, char *s);
void display_update(void);


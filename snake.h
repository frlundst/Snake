/*Written by Fredrik Lundström and Michell Dib 2021 (c)*/

void display_image(int x, const uint8_t *data);
void display_init(void);
void display_string(int line, char *s);
void display_update(void);
uint8_t spi_send_recv(uint8_t data);

void quicksleep(int cyc);

void display_debug( volatile int * const addr );

extern const uint8_t const font[128*8];
extern const uint8_t const icon[128];
extern char textbuffer[4][16];

void delay(int);
void enable_interrupt(void);

//Egna
uint8_t display[32][128]; //Human readable pixel position and activation
uint8_t oled_display[512]; //Computer readable pixel position and activation

void display_start();
void clear_display();
void translateToImage();
void create_object(int xPos, int yPos, int width, int height);
void snake();

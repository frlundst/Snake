/*Written by Fredrik Lundström and Michell Dib 2021 (c)*/

#include <stdint.h>
#include <pic32mx.h> 
#include "snake.h" //Project header file

int score = 0;
int speed = 20;


int snake_length;
int snake_width = 1;
int snake_x = 64;
int snake_y = 16;

int apple_x;
int apple_y;

void snake(){
    snake_create();
    apple_create();

    if(snake_x == apple_x && snake_y == apple_y){
        apple_eat();
    }
    delay(speed);
    snake_move();
}

void snake_create(){
    snake_length = 5;
    create_object(snake_x, snake_y, snake_length, snake_width);
}

void snake_move(){
    if(snake_x > 128){
        snake_x = 0;
    }else{
        snake_x++;  
    }
}

void apple_create(){
    //Randomize 
    create_object(apple_x, apple_y, 1, 1);
}

void apple_eat(){
    display[apple_x][apple_y] = 0; //Clear apple pixel
    apple_x = 5;
    apple_y = 5;
    apple_create();
    score++;
}

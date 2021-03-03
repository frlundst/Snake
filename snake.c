/*
void snake(){

    this.length = 0;

    this.y = 0;
    this.x = 0;

    this.xspeed = 1;
    this.yspeed = 0;

    this.direction = "right";
}

void update(){
    
    this.x = this.x + this.xspeed;
    this.y = this.y + this.yspeed;
    if(getbtns == 0xf0f0 | 0xf00f | 0x0ff0 | 0x0f0f){
       keyPress(getbtns());
    }
    delay(1000);
}

void getbtns(void){
    int btn = (PORTD >> 5) & 0x0007;
    return btn;
}

void keyPress(int buttons){
    // 0 0 0 0 = UP DOWN LEFT RIGHT

    //Svänga upp
    if(buttons & 0xf000){
        if(this.direction == "down")
            break;
        this.xspeed = 0;
        this.yspeed = 1;
        this.direction = "up";
    }

    //Svänga ner
    if(buttons & 0x0f00){
        if(this.direction == "up")
            break;
        this.xspeed = 0;
        this.yspeed = -1;
        this.direction = "down";
    }

    //Svänga vänster
    if(buttons & 0x00f0){
        if(this.direction == "right")
            break;
        this.xpseed = -1;
        this.yspeed = 0;
        this.direction = "left";
    }

    //Svänga höger
    if(buttons & 0x000f){
        if(this.direction == "left")
            break;
        this.xpseed = 1;
        this.yspeed = 0;
        this.direction = "right";
    }

}

void draw(){
    Snake.update();
}
*/
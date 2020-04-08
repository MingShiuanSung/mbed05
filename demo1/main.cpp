#include "mbed.h"


Ticker time_up;

DigitalOut yellowLED(LED2);
DigitalOut greenLED(LED3);


void blink(){

    yellowLED = !yellowLED;
    greenLED = !greenLED;

}


int main(){

    time_up.attach( &blink, 0.5 );

    while(1);

}
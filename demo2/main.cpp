#include "mbed.h"

#include "mbed_events.h"


DigitalOut led1(LED1);
DigitalOut led2(LED2);



EventQueue printfQueue;

EventQueue eventQueue;


void blink_led2() {

  // this runs in the normal priority thread

  led2 = !led2;

}

void blink_led1() {

  // this runs in the low priority thread

  led1 = !led1;

}




int main() {

  // low priority thread for calling printf()

  Thread printfThread(osPriorityLow);

  printfThread.start(callback(&printfQueue, &EventQueue::dispatch_forever));


  // normal priority thread for other events

  Thread eventThread(osPriorityNormal);

  eventThread.start(callback(&eventQueue, &EventQueue::dispatch_forever));


  // call blink_led2 every second, automatically defering to the eventThread

  Ticker ledTicker;

  ledTicker.attach(eventQueue.event(&blink_led2), 1.0f);

  // call blink_led1 every two second, automatically defering to the eventThread

  Ticker printfTicker;

  printfTicker.attach(eventQueue.event(&blink_led1), 2.0f);

  while (1) {wait(1);}

}
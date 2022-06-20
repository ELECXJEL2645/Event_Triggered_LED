/*  Event interrupt example
*   Operate an Red LED using an event interrupt. 
*
*   Board: NUCLEO L476RG
*   Author: Dr Craig Evans
*	Editied: Andrew Knowles 2022
*	MBED OS: 6.14
*/
 
#include "mbed.h"
 
// Create objects for button A and LED1
InterruptIn buttonA(PC_12);
DigitalOut red_led(PA_15);
 
// flag - must be volatile as changes within ISR
// g_ prefix makes it easier to distinguish it as global
volatile int g_buttonA_flag = 0;
 
// function prototypes
void buttonA_isr();
int state = 0;
 
int main(){
    // Button A has a pull-down resistor, so the pin will be at 0 V by default
    // and rise to 3.3 V when pressed. We therefore need to look for a rising edge
    // on the pin to fire the interrupt
    buttonA.rise(&buttonA_isr);
	
    // since Button A has an external pull-down, we should disable to internal pull-down
    // resistor that is enabled by default using InterruptIn
    buttonA.mode(PullNone);
	
	red_led = state;
 
    while (1) {
 
        // check if flag i.e. interrupt has occured
        if (g_buttonA_flag) {
            g_buttonA_flag = 0;  // if it has, clear the flag
			
			state = !state;
			red_led = state;
        }
 
        // put the MCU to sleep until an interrupt wakes it up
        sleep();
    }
}
 
// Button A event-triggered interrupt
void buttonA_isr(){
    g_buttonA_flag = 1;   // set flag in ISR
}

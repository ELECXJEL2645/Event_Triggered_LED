/*	Event_Triggered_LED
*	====================
*
*	Function:               Preform an ISR upon the detection of an event (a button press)
*	Circuit Schematic No.:  2 : https://github.com/ELECXJEL2645/Circuit_Schematics
*	Required Libraries:     
*
*	Authored by:            Dr Craig Evans
*	Date:                   
*	Collaberators:          Andrew Knowles
*				Dr Tim Amsdon
*	Version:                1.0
*	Revision Date:          06/2022 
*	MBED Studio Version:    1.4.1
*	MBED OS Version:        6.12.0
*	Board:	                NUCLEO L476RG	*/
 
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

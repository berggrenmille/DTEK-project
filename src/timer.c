#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "mipslab.h"  /* Declatations for these labs */
#include <math.h>

int globaltime = 0;

volatile unsigned* portE = (volatile unsigned*)0xbf886110;
volatile unsigned* trisE = (volatile unsigned*)0xbf886100;
/* Interrupt Service Routine */
void user_isr( void )
{
    IFS(0) &= ~(0x100); //Reset flag
    ++globaltime;
}


void init_timer( void )
{
    __asm__("ei"); //Enable interupts


  *trisE &= ~0xff; //Set bit index 7 - 0 to output
  *portE = 0;      //Initialize PortE to 0

  TRISD  |= 0xFE0; //Set bit index 5 - 11 to output

  //Timer Setup

  //Init Timer interrupt 
  IPC(2) |= 0x1f; //HIGEST PRIORITY
  IEC(0) |= 0x100; //Enable timer 2 interrupts

  T2CON = 0x0; //stop the timer and clear control register
  TMR2 = 0x0; //Reset the timer value

  T2CON |= 0x70; //Sets bit 6 - 4 to 111, aka prescaling 1:256
  PR2 = 313; //80*10^6 / 256 / 10 (prescaling 1:256)

  T2CON |= 0x8000; //Start the timer

  return;
}


#include "watchdog.h"
/*
 * The watchdog interrupt is configured for 8s Interrupt. 
 * At the starting of the user program loop, the wdtCounter = 0. 
 * when program stucks at the middle of loop it trigger WDT interrupt 
 * at the interval of 8s and increase wdtCounter. 
 * when Counter exceeds user defined WDT_MAX_COUNT value the system will resets.
 * So system will resets after = 8*WDT_MAX_COUNT seconds
 */
#include <avr/io.h>
#include <avr/wdt.h>
#include <avr/interrupt.h>

#define WDT_MAX_COUNT 5 //10*6 = 60

uint8_t wdtCounter = 0;

ISR(WDT_vect)
{
  wdtCounter++;
  if(wdtCounter<WDT_MAX_COUNT)
  {
    //Start WDT Timer again
    wdt_reset();
  }
  else
  {
    //if counter exceeds reset system 
    MCUSR = 0;  //reset MCU status register
    WDTCSR |= (1<<WDCE)|(1<<WDE);   // Enter config mode.
    WDTCSR  = (1<<WDE)|0b000000;    //Reset Enable
  }
  
}

void watchdogSetup()
{
  char oldReg = SREG;
  cli();                                    //Disable all interrupt to avoid interrupt during register change
  MCUSR = 0;                                //reset mcu status register
  WDTCSR |= (1<<WDCE)|(1<<WDE);             //Enter config mode.
  WDTCSR = (1<<WDIE)|(1<<WDP3) | (1<<WDP0); //WDT Interrupt enable with 8S
  SREG = oldReg;
  sei();                                    //Enable Interrupt
}


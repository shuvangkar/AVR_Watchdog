#ifndef _WATCHDOG_H_
#define _WATCHDOG_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <Arduino.h>
#include <avr/wdt.h>

void watchdogSetup();
extern uint8_t wdtCounter;

#ifdef __cplusplus
}
#endif //end __cplusplus

#endif //End _WATCHDOG_H_

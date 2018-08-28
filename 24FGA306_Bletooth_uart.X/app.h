/* 
 * File:   app.h
 * Author: pierre
 *
 * Created on February 8, 2018, 1:21 PM
 */



#include <xc.h>
#include <stdint.h>
#include <stdbool.h>
#define _XTAL_FREQ  20000000UL
#define FCY 10000000UL
#include <libpic30.h> // requis pour __delay_ms & __delay_us
#include "uart4_bluetooth.h"

//def structure 






void SYSTEM_Initialize(void);
void OSCILLATOR_Initialize(void);
void PIN_MANAGER_Initialize(void);
void ISR_init(void);






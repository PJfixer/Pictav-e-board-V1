/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using PIC24 / dsPIC33 / PIC32MM MCUs

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC24 / dsPIC33 / PIC32MM MCUs - pic24-dspic-pic32mm : 1.55
        Device            :  PIC24FJ64GA306
    The generated drivers are tested against the following:
        Compiler          :  XC16 v1.34
        MPLAB             :  MPLAB X v4.15
*/

/*
    (c) 2016 Microchip Technology Inc. and its subsidiaries. You may use this
    software and any derivatives exclusively with Microchip products.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION
    WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.

    MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE
    TERMS.
*/

#include "mcc_generated_files/mcc.h"
#include "pwm.h"
#define _XTAL_FREQ  20000000UL
#define FCY 10000000UL
#include <libpic30.h>
#include <p24FJ64GA306.h> // requis pour __delay_ms & __delay_us
/*
                         Main application
 */
int main(void)
{
    // initialize the device
    SYSTEM_Initialize();
   /*  RPOR10bits.RP21R = 18 ; // REMAP on RP21
     RPOR13bits.RP26R = 19;
     RPOR13bits.RP27R = 21;
     RPOR9bits.RP19R = 20 ;
     out_PWM(2,1,1206.0,99.0);
     out_PWM(2,2,1206.0,35.0);
     out_PWM(2,3,1206.0,62.0);
     out_PWM(2,4,1206.0,88.0); */
     
     T1CONbits.TON = 0 ;
     T2CONbits.TON = 0 ;
     T3CONbits.TON = 0 ;
     T4CONbits.TON = 0 ;
     T5CONbits.TON = 0 ;

 // configure T4
 T4CONbits.TON = 0 ;
 TMR4 = 0x0000;
 T4CON = 0x0000;
 T4CON = 0x2000;  
 PR4 = 39062; //period value
 //IEC0bits.T2IE = 1;
 IFS1bits.T4IF= 0;
 
 RPOR10bits.RP21R = 18 ; // REMAP on RP21
 
 
/* Reset PWM */
OC1CON1 = 0x0000;
OC1CON2 = 0x0000;

/* set PWM duty cycle to 50% */
OC1R    = 19500 ;
OC1RS   = 19500 ;

/* configure PWM */
OC1CON2 = 0x001f;   /* 0x001F = Sync with This OC module                               */
OC1CON1 = 0x0800; /* src=Timer4 */  /* 0x1C08 = Clock source Fcyc, trigger mode 1, Mode 0 (disable OC1) */

/* enable the PWM */
OC1CON1 |= 0x0006;   /* Mode 6, Edge-aligned PWM Mode */
 
 
 T4CONbits.TON = 1 ;
     
    while (1)
    {
        LATFbits.LATF0 = 1 ; 
        __delay_ms(1000);
       LATFbits.LATF0 = 0 ; 
        __delay_ms(1000);
     
    
        // Add your application code
    }

    return -1;
}
/**
 End of File
*/

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
    
    /****************************************************************************
     * Setting the Output Latch SFR(s)
     ***************************************************************************/
    LATB = 0x0000;
    LATC = 0x0000;
    LATD = 0x0000;
    LATE = 0x0000;
    LATF = 0x0000;
    LATG = 0x0000;

    /****************************************************************************
     * Setting the GPIO Direction SFR(s)
     ***************************************************************************/
    TRISB = 0x0000;
    TRISC = 0x0000;
    TRISD = 0x0000;
    TRISE = 0x0000;
    TRISF = 0x0000;
    TRISG = 0x0000;

    /****************************************************************************
     * Setting the Weak Pull Up and Weak Pull Down SFR(s)
     ***************************************************************************/
    CNPD1 = 0x0000;
    CNPD2 = 0x0000;
    CNPD3 = 0x0000;
    CNPD4 = 0x0000;
    CNPD5 = 0x0000;
    CNPD6 = 0x0000;
    CNPU1 = 0x0000;
    CNPU2 = 0x0000;
    CNPU3 = 0x0000;
    CNPU4 = 0x0000;
    CNPU5 = 0x0000;
    CNPU6 = 0x0000;

    /****************************************************************************
     * Setting the Open Drain SFR(s)
     ***************************************************************************/
    ODCB = 0x0000;
    ODCC = 0x0000;
    ODCD = 0x0000;
    ODCE = 0x0000;
    ODCF = 0x0000;
    ODCG = 0x0000;

    /****************************************************************************
     * Setting the Analog/Digital Configuration SFR(s)
     ***************************************************************************/
    ANSB = 0x0000;
    ANSD = 0x0000;
    ANSE = 0x0000;
    ANSG = 0x0000;
    
     RPOR10bits.RP21R = 18 ; // REMAP OC1 on RP21 --> page 175
     RPOR13bits.RP26R = 19;
     RPOR13bits.RP27R = 21;
     RPOR9bits.RP19R = 20 ;

     
     T1CONbits.TON = 0 ;
     T2CONbits.TON = 0 ;
     T3CONbits.TON = 0 ;
     T4CONbits.TON = 0 ;
     T5CONbits.TON = 0 ;

 
 
// configure T4
 T4CONbits.TON = 0 ;
 TMR4 = 0x0000;
 T4CON = 0x0000; // reset T4CON
 T4CON = 0x2000;   //Disable on idle
 T4CONbits.TCKPS = 3 ; // Presacle 256
 PR4 = 1000; // set 1s delay

 IEC1bits.T4IE = 1; //enable T4 interupt
 IFS1bits.T4IF= 0; //disable flag...
 
 
 
//Reset Output compare register --> P213 section 15.3 Pulse-Width Modulation (PWM) Mode
OC1CON1 = 0x0000;
OC1CON2 = 0x0000;

//set PWM duty cycle to 50% 
OC1R    = 19532 ;
OC1RS   = 39063 ;
//select sync source as explain in datasheet --> page    (not really understand what is it use for )
OC1CON2bits.SYNCSEL = 0x1F ;
OC1CON2bits.OCTRIG = 0 ; 

//select T4 as source
OC1CON1bits.OCTSEL = 0b010 ; // --> page 

//configure PWM 
OC1CON1bits.OCM = 0b110; // edge PWM mode                           




 

 
T4CONbits.TON = 1 ; // enable T4
     
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


void __attribute__((__interrupt__, no_auto_psv)) _T4Interrupt( void )
{
    IFS1bits.T4IF = 0; // reset T4 interupt flag

    LATFbits.LATF1 =~  LATFbits.LATF1; //Toggle led to check T4 is working


} 
/**
 End of File
*/
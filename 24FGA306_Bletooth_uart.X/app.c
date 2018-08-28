#include "app.h"

#pragma config DSWDTPS = DSWDTPS1F    // Deep Sleep Watchdog Timer Postscale Select bits->1:68719476736 (25.7 Days)
#pragma config DSWDTOSC = LPRC    // DSWDT Reference Clock Select->DSWDT uses LPRC as reference clock
#pragma config DSBOREN = ON    // Deep Sleep BOR Enable bit->DSBOR Enabled
#pragma config DSWDTEN = ON    // Deep Sleep Watchdog Timer Enable->DSWDT Enabled
#pragma config DSSWEN = ON    // DSEN Bit Enable->Deep Sleep is controlled by the register bit DSEN

// CONFIG3
#pragma config WPFP = WPFP63    // Write Protection Flash Page Segment Boundary->Page 52 (0xFC00)
#pragma config VBTBOR = ON    // VBAT BOR enable bit->VBAT BOR enabled
#pragma config SOSCSEL = OFF    // SOSC Selection bits->Digital (SCLKI) mode
#pragma config WDTWIN = PS25_0    // Watch Dog Timer Window Width->Watch Dog Timer Window Width is 25 percent
#pragma config BOREN = ON    // Brown-out Reset Enable->Brown-out Reset Enable
#pragma config WPDIS = WPDIS    // Segment Write Protection Disable->Disabled
#pragma config WPCFG = WPCFGDIS    // Write Protect Configuration Page Select->Disabled
#pragma config WPEND = WPENDMEM    // Segment Write Protection End Page Select->Write Protect from WPFP to the last page of memory

// CONFIG2
#pragma config POSCMD = HS    // Primary Oscillator Select->HS Oscillator Enabled
#pragma config BOREN1 = EN    // BOR Override bit->BOR Enabled [When BOREN=1]
#pragma config IOL1WAY = ON    // IOLOCK One-Way Set Enable bit->Once set, the IOLOCK bit cannot be cleared
#pragma config OSCIOFCN = OFF    // OSCO Pin Configuration->OSCO/CLKO/RC15 functions as CLKO (FOSC/2)
#pragma config FCKSM = CSDCMD    // Clock Switching and Fail-Safe Clock Monitor Configuration bits->Clock switching and Fail-Safe Clock Monitor are disabled
#pragma config FNOSC = PRI    // Initial Oscillator Select->Primary Oscillator (XT, HS, EC)
#pragma config ALTVREF = ALT_AV_ALT_CV    // Alternate VREF/CVREF Pins Selection bit->Voltage reference input, ADC =RB0/RB1   Comparator =RB0/RB1
#pragma config IESO = ON    // Internal External Switchover->Enabled

// CONFIG1
#pragma config WDTPS = PS32768    // Watchdog Timer Postscaler Select->1:32768
#pragma config FWPSA = PR128    // WDT Prescaler Ratio Select->1:128
#pragma config FWDTEN = WDT_DIS    // Watchdog Timer Enable->WDT disabled in hardware; SWDTEN bit disabled
#pragma config WINDIS = OFF    // Windowed WDT Disable->Standard Watchdog Timer
#pragma config ICS = PGx3    // Emulator Pin Placement Select bits->Emulator functions are shared with PGEC3/PGED3
#pragma config LPCFG = OFF    // Low power regulator control->Disabled
#pragma config GWRP = OFF    // General Segment Write Protect->Disabled
#pragma config GCP = OFF    // General Segment Code Protect->Code protection is disabled
#pragma config JTAGEN = OFF    // JTAG Port Enable->Disabled

#include "app.h"

//


void SYSTEM_Initialize(void)
{
    
    OSCILLATOR_Initialize();
    usart4_init();
    PIN_MANAGER_Initialize();
    ISR_init();

}

void OSCILLATOR_Initialize(void)
{
      // CF no clock failure; NOSC PRI; SOSCEN disabled; POSCEN disabled; CLKLOCK unlocked; OSWEN Switch is Complete; IOLOCK not-active; 
    __builtin_write_OSCCONL((uint8_t) (0x0200 & 0x00FF));
    // RCDIV FRC/2; DOZE 1:8; DOZEN disabled; ROI disabled; 
    CLKDIV = 0x3100;
    // TUN Center frequency; 
    OSCTUN = 0x0000;
    // ROEN disabled; ROSEL disabled; RODIV Base clock value; ROSSLP disabled; 
    REFOCON = 0x0000;
}

void PIN_MANAGER_Initialize(void)
{
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
    TRISB = 0xBEFF;
    TRISC = 0x9000;
    TRISD = 0x0FFF;
    TRISE = 0x00FF;
    TRISF = 0x007F;
    TRISG = 0x038C;
    TRISFbits.TRISF0 = 0;
  
    
    
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
    ANSB = 0xBCCF;
    ANSD = 0x0CC0;
    ANSE = 0x00F0;
    ANSG = 0x0300;
    


    /****************************************************************************
     * Set the PPS
     ***************************************************************************/
    
    __builtin_write_OSCCONL(OSCCON & 0xbf); // unlock PPS

  //  RPOR4bits.RP8R = 0x0008;   //RB8->SPI1:SCK1OUT;
    RPOR10bits.RP21R = 0x0005;   //RG6->UART2:U2TX;
  //  RPOR7bits.RP14R = 0x0007;   //RB14->SPI1:SDO1;
   // RPINR20bits.SDI1R = 0x0009;   //RB9->SPI1:SDI1;
   RPINR19bits.U2RXR = 0x001A;   //RG7->UART2:U2RX;

    __builtin_write_OSCCONL(OSCCON | 0x40); // lock   PPS
    
   

}

void ISR_init(void)
{
    IEC5bits.U4RXIE = 1 ; // activation des interution sur U4RX
    IFS5bits.U4RXIF = 0  ; // reset flag U4RX
}





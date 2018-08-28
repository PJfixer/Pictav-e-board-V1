
#include "pwm.h"


double Fcy = 10000000;
double tcy ;

int16_t round1 (double x)
 {
  return (int16_t)(x + 0.5f);
 }

void Calc_PWM(int16_t *range,uint8_t *index,double Freq)
{
    uint8_t i ;
    int16_t max = 0;
    uint8_t indexmax ;
    int16_t tab[4];
    double S ;
    S = 1.0/Freq;
    if( (S/tcy) > 65536)  // 1:1
    {
        tab[0] = 0 ;
        //printf("trop grand 1:1 : %.10g\n",(S/tcy));
    }
    else
    {
        tab[0] =  (int16_t)round1(S/tcy);
    }
     if( (S/(tcy*8.0)) > 65536) //1:8
    {
        tab[1] = 0 ;
         //printf("trop grand 1:8 : %.10g\n",(S/(tcy*8.0)));
    }
    else
    {
        tab[1] = (int16_t)round1((S/(tcy*8.0)));
    }
     if( (S/(tcy*64.0)) > 65536) // 1:64
    {
        tab[2] = 0 ;
        //printf("trop grand 1:64: %.10g \n",(S/(tcy*64.0)));
    }
    else
    {
        tab[2] =  (int16_t)round1((S/(tcy*64.0)));
    }
     if( (S/(tcy*256.0)) > 65536) // 1:256
    {
        tab[3] = 0 ;
        //printf("trop grand  1:256 : %.10g \n",(S/(tcy*256.0)));
    }
    else
    {
        tab[3] =  (int16_t)round1((S/(tcy*256.0)));
    }
    for(i=0;i<4;i++)
    {
        //printf("tab de %u = %d \n",i,tab[i]);
        if(tab[i] > max)
        {
            max = tab[i];
            indexmax = i ;
        }
    }
    *range = max ;
    *index = indexmax;
}

int16_t map(float x, float in_min, float in_max, int16_t out_min, int16_t out_max)
{
  return round1((x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min);
}


void out_PWM(uint8_t timer,uint8_t channel,double frequency,float duty_cycle)
{
    
    int16_t range;
    uint8_t index;
    tcy = (1.0/Fcy) ;
    switch(timer)
    {
    case 1:
        Calc_PWM(&range,&index,frequency); //calculating the frequency & deducting which prescaler is better to use
         T1CONbits.TON = 0 ;
         TMR1 = 0x0000;
         T1CON = 0x2000;
         switch(index)
         {
         case 0:
             T1CONbits.TCKPS = 0b00; //  1:1
         break;
         case 1:
             T1CONbits.TCKPS = 0b01; //  1:8
         break;
         case 2:
             T1CONbits.TCKPS = 0b10; // 1:64
         break;
         case 3:
             T1CONbits.TCKPS = 0b11; // 1:256
         break;
         }
         PR1 = range; //period value

        switch(channel)
        {
        case 1: //attach 0C1 on TMR1
             OC1R = map(duty_cycle,0.0,100.0,0,range); // initial duty cycle 50%
             OC1RS = map(duty_cycle,0.0,100.0,0,range); // initial duty cycle 50%
             OC1CON1bits.OCM = 0b000; // Clear whatever values are in
             OC1CON1bits.OCM = 0b110; // edge PWM mode
             OC1CON1bits.OCTSEL = 0b100; // Timer1 source
        break;
        case 2://attach 0C2 on TMR1
             OC2R = map(duty_cycle,0.0,100.0,0,range); // initial duty cycle 50%
             OC2RS = map(duty_cycle,0.0,100.0,0,range); // initial duty cycle 50%
             OC2CON1bits.OCM = 0b000; // Clear whatever values are in
             OC2CON1bits.OCM = 0b110; // edge PWM mode
             OC2CON1bits.OCTSEL = 0b100; // Timer1 source

        break;
        case 3://attach 0C3 on TMR1
             OC3R = map(duty_cycle,0.0,100.0,0,range); // initial duty cycle 50%
             OC3RS = map(duty_cycle,0.0,100.0,0,range); // initial duty cycle 50%
             OC3CON1bits.OCM = 0b000; // Clear whatever values are in
             OC3CON1bits.OCM = 0b110; // edge PWM mode
             OC3CON1bits.OCTSEL = 0b100; // Timer1 source

        break;
        case 4://attach 0C4 on TMR1
             OC4R = map(duty_cycle,0.0,100.0,0,range); // initial duty cycle 50%
             OC4RS = map(duty_cycle,0.0,100.0,0,range); // initial duty cycle 50%
             OC4CON1bits.OCM = 0b000; // Clear whatever values are in
             OC4CON1bits.OCM = 0b110; // edge PWM mode
             OC4CON1bits.OCTSEL = 0b100; // Timer1 source

        break;
        }
    T1CONbits.TON = 1 ;
    break;
    case 2:
        Calc_PWM(&range,&index,frequency); //calculating the frequency & deducting which prescaler is better to use
         T2CONbits.TON = 0 ;
         TMR2 = 0x0000;
         T2CON = 0x2000;
         switch(index)
         {
         case 0:
             T2CONbits.TCKPS = 0b00; //  1:1
         break;
         case 1:
             T2CONbits.TCKPS = 0b01; //  1:8
         break;
         case 2:
             T2CONbits.TCKPS = 0b10; // 1:64
         break;
         case 3:
             T2CONbits.TCKPS = 0b11; // 1:256
         break;
         }
         PR2 = range; //period value

        switch(channel)
        {
        case 1: //attach 0C1 on TMR1
             OC1R = map(duty_cycle,0.0,100.0,0,range); // initial duty cycle 50%
             OC1RS = map(duty_cycle,0.0,100.0,0,range); // initial duty cycle 50%
             OC1CON1bits.OCM = 0b000; // Clear whatever values are in
             OC1CON1bits.OCM = 0b110; // edge PWM mode
             OC1CON1bits.OCTSEL = 0b000; // Timer2 source
        break;
        case 2://attach 0C2 on TMR1
             OC2R = map(duty_cycle,0.0,100.0,0,range); // initial duty cycle 50%
             OC2RS = map(duty_cycle,0.0,100.0,0,range); // initial duty cycle 50%
             OC2CON1bits.OCM = 0b000; // Clear whatever values are in
             OC2CON1bits.OCM = 0b110; // edge PWM mode
             OC2CON1bits.OCTSEL = 0b000; // Timer2 source

        break;
        case 3://attach 0C3 on TMR1
             OC3R = map(duty_cycle,0.0,100.0,0,range); // initial duty cycle 50%
             OC3RS = map(duty_cycle,0.0,100.0,0,range); // initial duty cycle 50%
             OC3CON1bits.OCM = 0b000; // Clear whatever values are in
             OC3CON1bits.OCM = 0b110; // edge PWM mode
             OC3CON1bits.OCTSEL = 0b000; // Timer2 source

        break;
        case 4://attach 0C4 on TMR1
             OC4R = map(duty_cycle,0.0,100.0,0,range); // initial duty cycle 50%
             OC4RS = map(duty_cycle,0.0,100.0,0,range); // initial duty cycle 50%
             OC4CON1bits.OCM = 0b000; // Clear whatever values are in
             OC4CON1bits.OCM = 0b110; // edge PWM mode
             OC4CON1bits.OCTSEL = 0b000; // Timer2 source

        break;
        }
    T2CONbits.TON = 1 ;

    break;
    case 3:
        
        Calc_PWM(&range,&index,frequency); //calculating the frequency & deducting which prescaler is better to use
         T3CONbits.TON = 0 ;
         TMR3 = 0x0000;
         T3CON = 0x2000;
         switch(index)
         {
         case 0:
             T3CONbits.TCKPS = 0b00; //  1:1
         break;
         case 1:
             T3CONbits.TCKPS = 0b01; //  1:8
         break;
         case 2:
             T3CONbits.TCKPS = 0b10; // 1:64
         break;
         case 3:
             T3CONbits.TCKPS = 0b11; // 1:256
         break;
         }
         PR3 = range; //period value
         
        switch(channel)
        {
        case 1: //attach 0C1 on TMR1
             OC1R = map(duty_cycle,0.0,100.0,0,range); // initial duty cycle 50%
             OC1RS = map(duty_cycle,0.0,100.0,0,range); // initial duty cycle 50%
             OC1CON1bits.OCM = 0b000; // Clear whatever values are in
             OC1CON1bits.OCM = 0b110; // edge PWM mode
             OC1CON1bits.OCTSEL = 0b001; // Timer3 source
             LATFbits.LATF1 = 1 ;
            
        break;
        case 2://attach 0C2 on TMR1
             OC2R = map(duty_cycle,0.0,100.0,0,range); // initial duty cycle 50%
             OC2RS = map(duty_cycle,0.0,100.0,0,range); // initial duty cycle 50%
             OC2CON1bits.OCM = 0b000; // Clear whatever values are in
             OC2CON1bits.OCM = 0b110; // edge PWM mode
             OC2CON1bits.OCTSEL = 0b001; // Timer3 source

        break;
        case 3://attach 0C3 on TMR1
             OC3R = map(duty_cycle,0.0,100.0,0,range); // initial duty cycle 50%
             OC3RS = map(duty_cycle,0.0,100.0,0,range); // initial duty cycle 50%
             OC3CON1bits.OCM = 0b000; // Clear whatever values are in
             OC3CON1bits.OCM = 0b110; // edge PWM mode
             OC3CON1bits.OCTSEL = 0b001; // Timer3 source

        break;
        case 4://attach 0C4 on TMR1
             OC4R = map(duty_cycle,0.0,100.0,0,range); // initial duty cycle 50%
             OC4RS = map(duty_cycle,0.0,100.0,0,range); // initial duty cycle 50%
             OC4CON1bits.OCM = 0b000; // Clear whatever values are in
             OC4CON1bits.OCM = 0b110; // edge PWM mode
             OC4CON1bits.OCTSEL = 0b001; // Timer3 source

        break;
        }
    T3CONbits.TON = 1 ;

    break;
    case 4:
        Calc_PWM(&range,&index,frequency); //calculating the frequency & deducting which prescaler is better to use
         T4CONbits.TON = 0 ;
         TMR4 = 0x0000;
         T4CON = 0x2000;
         switch(index)
         {
         case 0:
             T4CONbits.TCKPS = 0b00 ;//  1:1
         break;
         case 1:
             T4CONbits.TCKPS = 0b01; //  1:8
         break;
         case 2:
             T4CONbits.TCKPS = 0b10 ;// 1:64
         break;
         case 3:
             T4CONbits.TCKPS = 0b11; // 1:256
         break;
         }
         PR4 = range; //period value

        switch(channel)
        {
        case 1: //attach 0C1 on TMR1
             OC1R = map(duty_cycle,0.0,100.0,0,range); // initial duty cycle 50%
             OC1RS = map(duty_cycle,0.0,100.0,0,range); // initial duty cycle 50%
             OC1CON1bits.OCM = 0b000; // Clear whatever values are in
             OC1CON1bits.OCM = 0b110; // edge PWM mode
             OC1CON1bits.OCTSEL = 0b010; // Timer4 source
        break;
        case 2://attach 0C2 on TMR1
             OC2R = map(duty_cycle,0.0,100.0,0,range); // initial duty cycle 50%
             OC2RS = map(duty_cycle,0.0,100.0,0,range); // initial duty cycle 50%
             OC2CON1bits.OCM = 0b000; // Clear whatever values are in
             OC2CON1bits.OCM = 0b110; // edge PWM mode
             OC2CON1bits.OCTSEL = 0b010; // Timer4 source

        break;
        case 3://attach 0C3 on TMR1
             OC3R = map(duty_cycle,0.0,100.0,0,range); // initial duty cycle 50%
             OC3RS = map(duty_cycle,0.0,100.0,0,range); // initial duty cycle 50%
             OC3CON1bits.OCM = 0b000; // Clear whatever values are in
             OC3CON1bits.OCM = 0b110; // edge PWM mode
             OC3CON1bits.OCTSEL = 0b010; // Timer4 source

        break;
        case 4://attach 0C4 on TMR1
             OC4R = map(duty_cycle,0.0,100.0,0,range); // initial duty cycle 50%
             OC4RS = map(duty_cycle,0.0,100.0,0,range); // initial duty cycle 50%
             OC4CON1bits.OCM = 0b000; // Clear whatever values are in
             OC4CON1bits.OCM = 0b110; // edge PWM mode
             OC4CON1bits.OCTSEL = 0b010; // Timer4 source

        break;
        }
    T4CONbits.TON = 1 ;

    break;
    case 5:
        Calc_PWM(&range,&index,frequency); //calculating the frequency & deducting which prescaler is better to use
         T5CONbits.TON = 0 ;
         TMR5 = 0x0000;
         T5CON = 0x2000;
         switch(index)
         {
         case 0:
             T5CONbits.TCKPS = 0b00 ;//  1:1
         break;
         case 1:
             T5CONbits.TCKPS = 0b01; //  1:8
         break;
         case 2:
             T5CONbits.TCKPS = 0b10 ;// 1:64
         break;
         case 3:
             T5CONbits.TCKPS = 0b11; // 1:256
         break;
         }
         PR5 = range; //period value

        switch(channel)
        {
        case 1: //attach 0C1 on TMR1
             OC1R = map(duty_cycle,0.0,100.0,0,range); // initial duty cycle 50%
             OC1RS = map(duty_cycle,0.0,100.0,0,range); // initial duty cycle 50%
             OC1CON1bits.OCM = 0b000; // Clear whatever values are in
             OC1CON1bits.OCM = 0b110; // edge PWM mode
             OC1CON1bits.OCTSEL = 0b011; // Timer5 source
        break;
        case 2://attach 0C2 on TMR1
             OC2R = map(duty_cycle,0.0,100.0,0,range); // initial duty cycle 50%
             OC2RS = map(duty_cycle,0.0,100.0,0,range); // initial duty cycle 50%
             OC2CON1bits.OCM = 0b000; // Clear whatever values are in
             OC2CON1bits.OCM = 0b110; // edge PWM mode
             OC2CON1bits.OCTSEL = 0b011; // Timer5 source

        break;
        case 3://attach 0C3 on TMR1
             OC3R = map(duty_cycle,0.0,100.0,0,range); // initial duty cycle 50%
             OC3RS = map(duty_cycle,0.0,100.0,0,range); // initial duty cycle 50%
             OC3CON1bits.OCM = 0b000; // Clear whatever values are in
             OC3CON1bits.OCM = 0b110; // edge PWM mode
             OC3CON1bits.OCTSEL = 0b011; // Timer5 source

        break;
        case 4://attach 0C4 on TMR1
             OC4R = map(duty_cycle,0.0,100.0,0,range); // initial duty cycle 50%
             OC4RS = map(duty_cycle,0.0,100.0,0,range); // initial duty cycle 50%
             OC4CON1bits.OCM = 0b000; // Clear whatever values are in
             OC4CON1bits.OCM = 0b110; // edge PWM mode
             OC4CON1bits.OCTSEL = 0b011; // Timer5 source

        break;
        }
    T5CONbits.TON = 1 ;

    break;
    }
}

/*void InitializeTimer2For_PWM(void)
{
 
 //initTimer2
 T2CONbits.TON = 0 ;
 TMR2 = 0x0000;
 T2CON = 0x2000;  //prescale 1:256
 PR2 = 39062; //period value
 //IEC0bits.T2IE = 1;
 IFS0bits.T2IF= 0;
 RPOR10bits.RP21R = 18 ; // REMAP on RP21
 OC1R = 1000; // initial duty cycle 50%
 OC1RS = 1000; //duty cycle 50%
 OC1CON1bits.OCM = 0b000; // Clear whatever values are in
 OC1CON1bits.OCTSEL = 0b000; // Timer2 source 
 
 IPC0bits.OC1IP = 0x01;  // Set Output Compare 1 Interrupt Priority Level
 IFS0bits.OC1IF = 0;     // Clear Output Compare 1 Interrupt Flag
// IEC0bits.OC1IE = 1;     // Enable Output Compare 1 interrupt
 
 
 OC1CON1bits.OCM = 0b110; // edge PWM mode 
 T2CONbits.TON = 1 ;
 
}*/


/*void __attribute__((__interrupt__, no_auto_psv)) _OC1Interrupt( void )
{
//Interrupt Service Routine code goes here
IFS0bits.OC1IF = 0;     // Clear OC1 interrupt flag
//LATFbits.LATF1 =~  LATFbits.LATF1;
 
 

}

void __attribute__((__interrupt__, no_auto_psv)) _T2Interrupt( void )
{
    IFS0bits.T2IF = 0; 
//Interrupt Service Routine code goes here
    // Clear OC1 interrupt flag
//LATFbits.LATF1 =~  LATFbits.LATF1;


} */







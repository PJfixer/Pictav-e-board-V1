/*
 * File:   main.c
 * Author: pierre
 *
 * Created on 11 juin 2018, 18:30
 */


#include <xc.h>
#include "app.h"

int main(void) {
    SYSTEM_Initialize();
    while(1)
    {
       
        LATFbits.LATF0 = 1 ;
        __delay_ms(2000);
         LATFbits.LATF0 = 0 ;
        __delay_ms(2000);
        

         
        
    }
    
return 1 ;
}

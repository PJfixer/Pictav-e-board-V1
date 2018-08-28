
#include <p24FJ64GA306.h>
#include "app.h"

#include <stddef.h>
/**************************************************************************************************/
// library carte PICtaV -e pour utilsation bluetooth rs232 avec buffer automatique via interuption 

typedef struct { 
    char data[RX_BUFFER_SIZE];
    uint8_t len ;
} buffer;

/************************************************************/
//BUFFER RX 
 buffer monBuffer;
void usart4_init(void)
{
    //TRIS
    TRISFbits.TRISF2 = 1 ; // entrée pour RX 
    TRISFbits.TRISF3 = 0 ; // sortie por TX
    LATFbits.LATF3 = 1 ; //TX a 1 avant d'init le module !!!! 
  
  
    U4MODE = (0x8008 & ~(1<<15));  // disabling UARTEN bit   
   
    U4STA = 0x0000;
    // BaudRate = 9600; Frequency = 10000000 Hz; BRG 259; 
    U4BRG = 0x0103;
    
   
    //reglage PPS map 
    __builtin_write_OSCCONL(OSCCON & 0xbf); // unlock PPS
 
     RPINR27bits.U4RXR = 0x001E;   //RF2->UART4:U4RX;
    RPOR8bits.RP16R = 0x001E;   //RF3->UART4:U4TX;
    //CONFIG UART
   
    
    U4MODEbits.UARTEN = 1;  // enabling UARTEN bit
    U4STAbits.UTXEN = 1; 
  
    
   
}

/*bool UART4_is_tx_ready(void)
{
    return (IFS5bits.U4TXIF && U4STAbits.UTXEN);
}

bool UART4_is_rx_ready(void)
{
    return IFS5bits.U4RXIF;
}

bool UART4_is_tx_done(void)
{
    return U4STAbits.TRMT;
}  */

uint8_t UART4_Read(void)
{
    while(!(U4STAbits.URXDA == 1))
    {
        
    }

    if ((U4STAbits.OERR == 1))
    {
        U4STAbits.OERR = 0;
    }

    

    return U4RXREG;
}

void SendUART4(uint8_t txData)
{
    while(U4STAbits.UTXBF == 1)
    {
        
    }

    U4TXREG = txData;    // Write the data byte to the USART.
}


    

void UART4_SendStr(const char * s)
{
    while(*s)
            SendUART4(*s++);
}

void UART4_SendDec(unsigned int data) // 
{
    unsigned char temp;
    temp=data/1000;
    SendUART4(temp+'0');
    data=data-temp*1000;
    temp=data/100;
    SendUART4(temp+'0');
    data=data-temp*100;
    temp=data/10;
    SendUART4(temp+'0');
    data=data-temp*10;
    SendUART4(data+'0');
}

void UART4_SendHex(unsigned int data) // 
{
    unsigned char temp;
     SendUART4('0');
     SendUART4('x');
    temp = data>>4;
    SendUART4(setHEX(temp));
    temp = data&0x0F;
    SendUART4(setHEX(temp));
    
    
}

unsigned char setHEX(unsigned char ch)
{
    if(ch >= 0 && ch <= 9)
    {
        return (ch+'0');
    }
    else
    {
        switch(ch)
        {
            case 10:
                return 'A';
            break; 
            case 11:
                return 'B';
            break; 
            case 12:
                return 'C';
            break; 
            case 13:
                return 'D';
            break; 
            case 14:
                return 'E';
            break; 
            case 15:
                return 'F';
            break; 
            default:
                return 'F';
            
        }
    }
}


void printTable(uint8_t * table,uint8_t size)
{
    uint8_t i ;
    for(i = 0; i<size;i++)
    {
        if (table[i] != NULL)
        {
            UART4_SendHex(table[i]);
            UART4_SendStr(" ");
        }
    }
}

void __attribute__((interrupt,no_auto_psv))_U4RXInterrupt() //routine d'interruption 
{   
    uint8_t RX_byte = U4RXREG ; // on copie le contenu du registre de reception 
     if(RX_byte == '\r') // si le caractere est "entrée"
       {
          
          interpretation(); // on appelle la fonction d'interpretation des commandes
       }
       else // sinon on le stock
       {
           //printf("stock");
           monBuffer.data[monBuffer.len] = RX_byte; //on stock
           monBuffer.len++; //on incremente la position du buffer
            if(monBuffer.len > (RX_BUFFER_SIZE+1)) // si le buffer est plein les caractere suivant ecraserons les autres 
            {
                monBuffer.len = 0 ;
            }
       }
    IFS5bits.U4RXIF = 0; // reset du flag d'interuption 
     
    
}

void  interpretation(void) // fonction d'interpretation cette fonction n'est appelé que si l'utilisateur fait un CR ( Carriage return = touche entrée)
{                          //ici l'utilisateur peut lire le buffer et interpreter ( dans l'exemple on se contente de renvoyer le contenu du buffer RX)
    uint8_t i ; 
    for(i=0;i<monBuffer.len;i++)
    {
        SendUART4(monBuffer.data[i]);
        
    }
    monBuffer.len = 0 ; 
    SendUART4('\n');
}
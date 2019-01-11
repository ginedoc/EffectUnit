/* 
 * File:   led.c
 * Author: popo
 *
 * Created on 01 January 2019, 20:50
 */

#include <stdio.h>
#include <stdlib.h>
#include "led.h"

void init_LED(){
  TRISD = 0;
  
  TRISCbits.RC4 = 0;
  TRISCbits.RC5 = 0;
  TRISCbits.RC6 = 0;
  TRISCbits.RC7 = 0;
  TRISCbits.RC3 = 0;
  TRISBbits.RB1 = 0;
  TRISBbits.RB4 = 0;
  TRISBbits.RB5 = 0;
  TRISBbits.RB6 = 0;
  TRISBbits.RB7 = 0;
  
  ADCON1bits.PCFG = 7;
}

void set_10(int val){
  switch(val){
    case 1:{
      LATCbits.LATC4 = 1;
      LATCbits.LATC5 = 0;
      LATCbits.LATC6 = 0;
      LATCbits.LATC7 = 0;
      LATCbits.LATC3 = 0;
      LATBbits.LATB1 = 0;
      LATBbits.LATB4 = 0;
      LATBbits.LATB5 = 0;
      LATBbits.LATB6 = 0;
      LATBbits.LATB7 = 0;      
    }break;
    case 2:{
      LATCbits.LATC4 = 1;
      LATCbits.LATC5 = 1;
      LATCbits.LATC6 = 0;
      LATCbits.LATC7 = 0;
      LATCbits.LATC3 = 0;
      LATBbits.LATB1 = 0;
      LATBbits.LATB4 = 0;
      LATBbits.LATB5 = 0;
      LATBbits.LATB6 = 0;
      LATBbits.LATB7 = 0;
    }break;
    case 3:{
      LATCbits.LATC4 = 1;
      LATCbits.LATC5 = 1;
      LATCbits.LATC6 = 1;
      LATCbits.LATC7 = 0;
      LATCbits.LATC3 = 0;
      LATBbits.LATB1 = 0;
      LATBbits.LATB4 = 0;
      LATBbits.LATB5 = 0;
      LATBbits.LATB6 = 0;
      LATBbits.LATB7 = 0;
    }break;
    case 4:{
      LATCbits.LATC4 = 1;
      LATCbits.LATC5 = 1;
      LATCbits.LATC6 = 1;
      LATCbits.LATC7 = 1;
      LATCbits.LATC3 = 0;
      LATBbits.LATB1 = 0;
      LATBbits.LATB4 = 0;
      LATBbits.LATB5 = 0;
      LATBbits.LATB6 = 0;
      LATBbits.LATB7 = 0;

    }break;
    case 5:{  
      LATCbits.LATC4 = 1;
      LATCbits.LATC5 = 1;
      LATCbits.LATC6 = 1;
      LATCbits.LATC7 = 1;
      LATCbits.LATC3 = 1;
      LATBbits.LATB1 = 0;
      LATBbits.LATB4 = 0;
      LATBbits.LATB5 = 0;
      LATBbits.LATB6 = 0;
      LATBbits.LATB7 = 0;
    }break;
    case 6:{ 
      LATCbits.LATC4 = 1;
      LATCbits.LATC5 = 1;
      LATCbits.LATC6 = 1;
      LATCbits.LATC7 = 1;
      LATCbits.LATC3 = 1;
      LATBbits.LATB1 = 1;
      LATBbits.LATB4 = 0;
      LATBbits.LATB5 = 0;
      LATBbits.LATB6 = 0;
      LATBbits.LATB7 = 0;

    }break;
    case 7:{  
      LATCbits.LATC4 = 1;
      LATCbits.LATC5 = 1;
      LATCbits.LATC6 = 1;
      LATCbits.LATC7 = 1;
      LATCbits.LATC3 = 1;
      LATBbits.LATB1 = 1;
      LATBbits.LATB4 = 1;
      LATBbits.LATB5 = 0;
      LATBbits.LATB6 = 0;
      LATBbits.LATB7 = 0;
    
    }break;
    case 8:{   
      LATCbits.LATC4 = 1;
      LATCbits.LATC5 = 1;
      LATCbits.LATC6 = 1;
      LATCbits.LATC7 = 1;
      LATCbits.LATC3 = 1;
      LATBbits.LATB1 = 1;
      LATBbits.LATB4 = 1;
      LATBbits.LATB5 = 1;
      LATBbits.LATB6 = 0;
      LATBbits.LATB7 = 0;
    
    }break;
    case 9:{   
      LATCbits.LATC4 = 1;
      LATCbits.LATC5 = 1;
      LATCbits.LATC6 = 1;
      LATCbits.LATC7 = 1;
      LATCbits.LATC3 = 1;
      LATBbits.LATB1 = 1;
      LATBbits.LATB4 = 1;
      LATBbits.LATB5 = 1;
      LATBbits.LATB6 = 1;
      LATBbits.LATB7 = 0;
    
    }break;
    case 10:{   
      LATCbits.LATC4 = 1;
      LATCbits.LATC5 = 1;
      LATCbits.LATC6 = 1;
      LATCbits.LATC7 = 1;
      LATCbits.LATC3 = 1;
      LATBbits.LATB1 = 1;
      LATBbits.LATB4 = 1;
      LATBbits.LATB5 = 1;
      LATBbits.LATB6 = 1;
      LATBbits.LATB7 = 1;
    
    }break;
    default:{ 
      LATCbits.LATC4 = 0;
      LATCbits.LATC5 = 0;
      LATCbits.LATC6 = 0;
      LATCbits.LATC7 = 0;
      LATCbits.LATC3 = 0;
      LATBbits.LATB1 = 0;
      LATBbits.LATB4 = 0;
      LATBbits.LATB5 = 0;
      LATBbits.LATB6 = 0;
      LATBbits.LATB7 = 0;   }
    }
}

void set_LED(int num, int value){
  switch(num){
    case 0:
      if(value<10){
        LATDbits.LATD0 = (value&1);
        LATDbits.LATD1 = (value&2)>>1;
        LATDbits.LATD2 = (value&4)>>2;
        LATDbits.LATD3 = (value&8)>>3;
        }           
      break;
      
    case 1:
      if(value<10){
        LATDbits.LATD4 = (value&1);
        LATDbits.LATD5 = (value&2)>>1;
        LATDbits.LATD6 = (value&4)>>2;
        LATDbits.LATD7 = (value&8)>>3;
        }      
      break;
      
    case 2: 
      break;
      
    case 3:
      break;
    default:
    {
      LATD = 0;
    }
    }
}
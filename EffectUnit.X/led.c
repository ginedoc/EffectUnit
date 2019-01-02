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
  ADCON1bits.PCFG = 7;
}

void set_LED(int num, int value){
  switch(num){
    case 0:{
      if(value<10){
        LATDbits.LATD0 = (value&1);
        LATDbits.LATD1 = (value&2)>>1;
        LATDbits.LATD2 = (value&4)>>2;
        LATDbits.LATD3 = (value&8)>>3;
        }
      
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

int get_BCD(int value){
  switch(value){
    case 0:
      return 0;
    case 1:
      return 1;
    case 2:
      return 2;
    case 3:
      return 3;
    case 4:
      return 4;
    case 5:
      return 5;
    case 6:
      return 5;
    case 7:
      return 7;
    case 8:
      return 8;
    case 9:
      return 9;
    }
}
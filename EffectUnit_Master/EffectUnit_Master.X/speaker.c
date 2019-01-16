/*
 * File:   speaker.c
 * Author: popo
 *
 * Created on 18 December 2018, 21:43
 */


#include <xc.h>
#include "speaker.h"


void init_PWM()
{
  // CCP1CON
  CCP1CONbits.CCP1M3 = 1;
  CCP1CONbits.CCP1M2 = 1;
  CCP1CONbits.CCP1M1 = 0;
  CCP1CONbits.CCP1M0 = 0;
  // Timer2
  T2CONbits.TMR2ON = 1;
  T2CONbits.T2CKPS = 0;
  // PWM(RC2) output
  TRISCbits.RC2 = 0;
}


void set_Period()
{
   // PR2 = 127;  // 64us
   //PR2 = 63;  // 32us
   //PR2 = 31;  // 16us 
   PR2 = 159;  // 8us 
   //PR2 = 15;   //  8us
    //PR2 = 7;    // 4us
}

void set_Duty(int level){
  CCPR1L = level>>2;
  
  CCP1CONbits.DC1B1 = (level>>1)%2;
  CCP1CONbits.DC1B0 = (level%2); 
}

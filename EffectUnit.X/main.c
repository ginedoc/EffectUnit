/*
 * File:   main.c
 * Author: popo
 *
 * Created on 2018年12月12日, 下午 3:08
 */
#include <xc.h>
#include "effect.h"

#pragma config OSC  = INTIO67,WDT=OFF,LVP=OFF
#pragma PBADEN = 1 //set AN0~AN12 as analog input

unsigned int samplerate = 31250; // Hz
unsigned int i=1;
//-------------------------------------------------------------------------//
void setting_sound_input(void);
void ccp2_init(void);
void timer3_init(void);
void init_PWM();
void set_Period();
void set_Duty(int level);
void call_effect();
void interrupt high_priority HiISR(void){
    if(PIR1bits.ADIF){
//        buffer[index] = ADRES;

        call_effect();
        
        TMR3 = 0;
        T3CONbits.TMR3ON=1;
        
        ADCON0bits.GO = 0;
        PIR1bits.ADIF = 0;
      }
    if(PIR2bits.CCP2IF){
        T3CONbits.TMR3ON=0;
        ADCON0bits.GO=1;
        PIR2bits.CCP2IF=0;
      }
}


void main(void) {
    OSCCONbits.IRCF = 7; // OSC 8 Mhz
    setting_sound_input();
    ccp2_init();
    timer3_init();
    init_PWM();
    set_Period();

    while(1);
    return;
}

void call_effect(){
  int level = (ADRES/4);
  
  if(level>256)
    level = 256;
  else if(level==0)
    level = 1;
  
  set_Duty(level);
  
  return;
}

void setting_sound_input(void){
  // ADC input
    ADCON0bits.CHS = 7;  // analog channel - AN7
    TRISEbits.RE2 = 1;
    ADCON0bits.ADON = 1;
    
    ADCON1bits.VCFG = 0; //set refer voltage 
    ADCON2bits.ADCS = 1; // 001 // AD Conversion Clock
    ADCON2bits.ACQT = 2;   //Acquisition Time // 4 Tad 
    
    ADCON2bits.ADFM = 1;  //left or right justified
  //Configure A/D interrupt(optional)
  //enable Interrupt Priority mode
    PIR1bits.ADIF = 0;
    PIE1bits.ADIE = 1;
    RCONbits.IPEN = 1;
    INTCONbits.GIE = 1;
}

void ccp2_init(void){
    //Configure CCP2
    CCP2CONbits.CCP2M = 10;
    //configure CCP1 interrupt
    PIR2bits.CCP2IF = 0;
    IPR2bits.CCP2IP = 1;
    PIE2bits.CCP2IE = 1;
    //configure CCP2 comparator value
    CCPR2 = 8;
 }

void timer3_init(void){
    //set up timer3
    T3CONbits.T3CCP2 = 0;
    T3CONbits.T3CCP1 = 1;
    // prescaler
    T3CONbits.T3CKPS1 = 0;
    T3CONbits.T3CKPS0 = 0;
    T3CONbits.TMR3ON = 1;
}

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
   PR2 = 63;  // 32us
   // PR2 = 16;  // 128us
}

void set_Duty(int level){
  CCPR1L = level>>2;
  
  CCP1CONbits.DC1B1 = (level>>1)%2;
  CCP1CONbits.DC1B0 = (level%2); 
}
/*
 * File:   sound.c
 * Author: popo
 *
 * Created on 18 December 2018, 12:42
 */

#include "sound.h"

void setting_sound_input(void){
  // ADC input
    ADCON0bits.CHS = 7;  // analog channel - AN7
    TRISEbits.RE2 = 1;
    ADCON0bits.ADON = 1;
    
    
    ADCON1bits.VCFG = 0; //set refer voltage 
    ADCON2bits.ADCS = 1; // 001 // AD Conversion Clock
    //ADCON2bits.ACQT = 2;   //Acquisition Time // 4 Tad 
    ADCON2bits.ACQT = 7;   //Acquisition Time // 20 Tad  //7
    
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
    //CCPR2=16;
    //CCPR2 = 8;  // 16us
    //CCPR2 = 4;  //8us
    CCPR2 = 320;  // 16us
 }

void timer3_init(void){
    //set up timer3
    T3CONbits.T3CCP2 = 0;
    T3CONbits.T3CCP1 = 1;
    // prescaler
    T3CONbits.T3CKPS1 = 0;
    T3CONbits.T3CKPS0 = 1;
    T3CONbits.TMR3ON = 1;
}

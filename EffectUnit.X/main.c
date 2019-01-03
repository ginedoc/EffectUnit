   /*
 * File:   main.c
 * Author: popo
 *
 * Created on 2018年12月12日, 下午 3:08
 */
#include "setting.h"
#include "debug.h"
#include <stdlib.h>
#include <stdio.h>
#include "string.h"


#pragma config OSC  = INTIO67,WDT=OFF,LVP=OFF
#pragma PBADEN = 1 //set AN0~AN12 as analog input

#define samplerate 62500 // Hz


extern unsigned short buffer[2][128];
extern unsigned short effect_buffer[3][128];
extern char buffer_ptr;
extern char effect_index;
extern char effect_ptr;
long ANASrc;
extern int Mode[4];
int cnt = 0;
//-------------------------------------------------------------------------//

void interrupt high_priority HiISR(void){
    if(PIR1bits.ADIF){
        
        if(ANASrc==15625 || ANASrc==31250 || ANASrc==46875 || ANASrc==65000){
            Mode[ANASrc/15625-1] = (int) ADRES/100;
//            if(ANASrc==-4)
                set_LED(ANASrc/15625-1, (int) ADRES/100);
          }
        
        
        if(buffer_ptr<128){
            buffer[buffer_index][buffer_ptr] = ADRES/8;
            play_sample();

            buffer_ptr++;
        }
        if(buffer_ptr==128){
            /*
            if(buffer_index<2) buffer_index++;
            else buffer_index = 0;
            */
            buffer_index = (buffer_index+1)%2;
            audio_index = (audio_index+1)%2;
            
            buffer_ptr = 0;
            effect_ptr = 0;
            
        }
        
         //////////////////////////////////////////////
        TMR3 = 0;
        T3CONbits.TMR3ON=1;
        
        ADCON0bits.GO = 0;
        PIR1bits.ADIF = 0;
        ANASrc++;
        
        //if(ANASrc==65001) ANASrc=0;
      }
    
    // start convert
    if(PIR2bits.CCP2IF){
 
        if(ANASrc==15624)   ADCON0bits.CHS = 0;
        else if(ANASrc==31249) ADCON0bits.CHS = 1;
        else if(ANASrc==46874) ADCON0bits.CHS = 5;
        else if(ANASrc==64999) ADCON0bits.CHS = 6;
        else ADCON0bits.CHS = 7;
 
        T3CONbits.TMR3ON=0;
        ADCON0bits.GO=1;
        PIR2bits.CCP2IF=0;
      }
}

void main(void) {
    // initial
    ANASrc = 0;
    for(int i = 0; i < 128 ; i++){
        buffer[0][i] = 0;
        buffer[1][i] = 0;
        buffer[2][i] = 0;
      }
  
    OSCCONbits.IRCF = 7; // OSC 8 Mhz
    setting_sound_input();
    ccp2_init();
    timer3_init();
    init_PWM();
    set_Period();
    init_LED();
    
    set_LED(-1,0);
    
    while(1){
               
        if(effect_ptr<128)  call_effect();       
    }
    return;
}

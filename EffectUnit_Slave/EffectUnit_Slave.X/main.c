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


#pragma config OSC  = HSPLL,WDT=OFF,LVP=OFF
#pragma PBADEN = 1 //set AN0~AN12 as analog input

#define samplerate 62500 // Hz
#define bufferSize 128
#define PWMRange 320

//---------------------------------------//
extern unsigned short buffer[3][bufferSize];
extern unsigned short buffer_ptr;
extern unsigned short effect_index;
extern unsigned short effect_ptr;
int ANAFlag;
int ANASrc;
extern int bitC_index;
extern int Mode[4];
int LED_Flag=0;
const short Mul = 16;
//-------------------------------------------------------------------------//

void ResistValue(int i){
    if(ANASrc==0)   ADCON0bits.CHS = 6;
    else if(ANASrc==1) ADCON0bits.CHS = 5;
    else if(ANASrc==2) ADCON0bits.CHS = 1;
    else if(ANASrc==3) ADCON0bits.CHS = 0;
    
    ADCON0bits.GO=1;
    ADCON0bits.ADON = 1;

    while(ADCON0bits.GO_nDONE==1);

    ADRES = (ADRES<1000)? ADRES:999;
    
    Mode[i] = (int) ADRES/100;
    set_LED(i, Mode[i]);
    
    ADCON0bits.GO = 0;
    ADCON0bits.CHS = 7;
    
    if(ANASrc==3) ANAFlag=0;
}

void interrupt high_priority HiISR(void){
    if(PIR1bits.ADIF){
       
        if(buffer_ptr<bufferSize){
            buffer[buffer_index][buffer_ptr] = (short) ADRES/4+32;
            play_sample();

            buffer_ptr++;
        }
        if(buffer_ptr==bufferSize){
            buffer_index = (buffer_index+1)%3;
            effect_index = (effect_index+1)%3;
            audio_index = (audio_index+1)%3;
            
            buffer_ptr = 0;
            effect_ptr = 0;
            
        }
        
         //////////////////////////////////////////////
        
        ADCON0bits.GO = 0;
        
        ANAFlag++;
        if(ANAFlag>2000){
            ANASrc++;
            ANASrc %= 4;
        
            ResistValue(ANASrc);
          }      

        
        TMR3 = 0;
        T3CONbits.TMR3ON=1;
        
        PIR1bits.ADIF = 0;
      }
    
    // start convert
    if(PIR2bits.CCP2IF){        
        T3CONbits.TMR3ON=0;
        ADCON0bits.GO=1;
        PIR2bits.CCP2IF=0;
      }
}

void main(void) {
    // initial
    ANASrc = 0;
    ANAFlag = 0;
    for(int i = 0; i < bufferSize ; i++){
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
        if(effect_ptr<bufferSize)
        {
            short currentSample = buffer[effect_index][effect_ptr];
            if(Mode[3]==0){
                if(Mode[0]>0 || Mode[1]>0){ 
                    if(currentSample>PWMRange-Mode[0]*Mul) currentSample = (PWMRange-Mode[0]*Mul)+Mode[1]/10*(currentSample+PWMRange-Mode[0]*Mul);
                    else if(currentSample<Mode[0]*Mul) currentSample = (Mode[0]*Mul)+(Mode[1]/10)*(currentSample-Mode[0]*Mul);                  
                  }          
                
                buffer[effect_index][effect_ptr] = currentSample;
                // bitcrusher
                if(Mode[2]>0){
                    currentSample = buffer[effect_index][effect_ptr-effect_ptr%(2*Mode[2])];
                  }
            }
            else if(Mode[3]>0){
                char freq = Mode[3];
                currentSample = (square_wave[freq][buffer_ptr]*Mode[0]+triangle_wave[freq][buffer_ptr]*Mode[1]+sine_wave[freq][effect_ptr]*Mode[2])*4.5;
              }
             
            buffer[effect_index][effect_ptr++] = currentSample;
        }
        
        int volLev = (buffer[buffer_index][buffer_ptr])/30;
        if(Mode[0]>0 || Mode[1]>0 || Mode[2]>0 || Mode[3] >0){
            set_10(volLev);
          }
        else{
            if(LED_Flag<100){ 
                LED_Flag++;
              }
            else if(LED_Flag==100) {
                set_10(volLev);
                LED_Flag=0;
            }
          }
      }

    return;
}

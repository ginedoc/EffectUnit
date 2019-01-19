/*
 * File:   effect.c
 * Author: popo
 *
 * Created on 19 December 2018, 03:00
 */

#include <xc.h>
#include "effect.h"

#define bufferSize 128
#define PWMRange 320
const int Mul = 16;

void distortion_soft_effect(int dis){

  if(buffer[effect_index][effect_ptr] > 128-dis) 
    {
      buffer[effect_index][effect_ptr] = 128-dis;
    }
  else if(buffer[effect_index][effect_ptr] < dis){
      buffer[effect_index][effect_ptr] = dis;
    }
}

void distortion_hard_effect(int dis, float portion){
  buffer[effect_index][effect_ptr] = 0;
  return;
  if(buffer[effect_index][effect_ptr] > 128-dis) 
    //buffer[effect_index][effect_ptr] *= portion;
     buffer[effect_index][effect_ptr] = 0;
  else if(buffer[effect_index][effect_ptr] < dis) 
    buffer[effect_index][effect_ptr] = 0;
    //buffer[effect_index][effect_ptr] *= portion;
}

void play_sample(){
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
    set_Duty(buffer[audio_index][buffer_ptr]);
}
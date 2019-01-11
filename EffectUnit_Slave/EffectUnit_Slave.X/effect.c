/*
 * File:   effect.c
 * Author: popo
 *
 * Created on 19 December 2018, 03:00
 */

#include <xc.h>
#include "effect.h"

#define bufferSize 128

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

int bitC_index;
void play_sample(){
    if(effect_ptr<bufferSize)
    {
        short currentSample = buffer[effect_index][effect_ptr];
        if(Mode[3]==0){
            // soft_clipping
            if(Mode[1]>0){
                if(currentSample>128-Mode[0]*5) currentSample = (128-Mode[0]*5)+Mode[0]/10*(currentSample+128-Mode[0]*5);
                else if(currentSample<Mode[0]*5) currentSample += (Mode[0]*5)+(Mode[0]/10)*(currentSample-Mode[0]*5);
              }  
            // hard_clipping
            else if(Mode[0]>0){
                if (currentSample>128-Mode[0]*5) currentSample = 128-Mode[0]*5;
                else if(currentSample<Mode[0]*5) currentSample = Mode[0]*5;
              }
            // bitcrasher
            if(Mode[2]>0){
                bitC_index++;
                bitC_index %= Mode[2];

                if(bitC_index>0 && buffer_ptr>Mode[2]) currentSample = (currentSample+buffer[effect_index][effect_ptr-bitC_index])/2;
              }
        }
        else if(Mode[3]>0){
            char freq = Mode[3];
                currentSample = (square_wave[freq][buffer_ptr]*Mode[0]+triangle_wave[freq][buffer_ptr]*Mode[1]+sine_wave[freq][effect_ptr]*Mode[2])*4.5;
          }
        buffer[effect_index][effect_ptr++] = currentSample;
    }
    set_Duty(buffer[audio_index][buffer_ptr]);
  //set_Duty(currentSample);
}
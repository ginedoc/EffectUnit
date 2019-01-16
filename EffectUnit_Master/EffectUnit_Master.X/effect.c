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

    set_Duty(buffer[audio_index][buffer_ptr]);
}
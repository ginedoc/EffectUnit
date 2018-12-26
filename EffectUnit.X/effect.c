/*
 * File:   effect.c
 * Author: popo
 *
 * Created on 19 December 2018, 03:00
 */

#include <xc.h>
#include "effect.h"
#include "speaker.h"
void call_effect(){
  //128
  
  distortion_effect(20);
   
  effect_ptr++;
  return;
}
void distortion_effect(int dis){
  if(buffer[effect_index][effect_ptr] > 128-dis) buffer[effect_index][effect_ptr] = 128-dis;
  else if(buffer[effect_index][effect_ptr] < dis) buffer[effect_index][effect_ptr] = dis;
}

void reverb_effect(int rev){

}

void play_sample(){
  set_Duty(buffer[audio_index][buffer_ptr]);
}
/* 
 * File:   effect.h
 * Author: popo
 *
 * Created on 19 December 2018, 03:00
 */

#ifndef EFFECT_H
#define	EFFECT_H

#include <xc.h>
#include <pic18f4520.h>
#include "speaker.h"
#include "synthtable.h"

#define true 1
#define false 0


unsigned short buffer_ptr = 0;
unsigned short effect_ptr = 0;
unsigned short buffer_index = 0;
unsigned short effect_index = 1;
unsigned short audio_index = 2;
unsigned short buffer[3][128];
int Mode[4];

void call_effect();
void distortion_soft_effect(int);
void distortion_hard_effect(int, float);
void play_sample();

#endif	/* EFFECT_H */


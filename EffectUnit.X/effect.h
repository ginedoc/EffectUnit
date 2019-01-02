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

#define true 1
#define false 0

char buffer_index = 0;
char buffer_ptr = 0;
char effect_ptr = 0;
char effect_index = 1;
char audio_index = 2;
unsigned short buffer[2][128];
unsigned short effect_buffer[3][128];

void call_effect();
void distortion_soft_effect(int);
void distortion_hard_effect(int, float);
void play_sample();

#endif	/* EFFECT_H */


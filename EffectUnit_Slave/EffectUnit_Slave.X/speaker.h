/* 
 * File:   speaker.h
 * Author: popo
 *
 * Created on 18 December 2018, 12:57
 */

#ifndef SPEAKER_H
#define	SPEAKER_H

#include <xc.h>
#include <pic18f4520.h>

void init_PWM();
void set_Period();
void set_Duty(int level);

#endif	/* SPEAKER_H */


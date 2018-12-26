/* 
 * File:   sound.h
 * Author: popo
 *
 * Created on 18 December 2018, 12:39
 */

#ifndef SOUND_H
#define	SOUND_H

#include <xc.h>
#include <pic18f4520.h>

void setting_sound_input(void);
void ccp2_init(void);
void timer3_init(void);

#endif	/* SOUND_H */


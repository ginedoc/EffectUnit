/* 
 * File:   led.h
 * Author: popo
 *
 * Created on 01 January 2019, 20:38
 */

#ifndef LED_H
#define	LED_H

#include <xc.h>
#include <pic18f4520.h>
#include "effect.h"



void init_LED();
void set_10(int);
void set_LED(int, int);
#endif	/* LED_H */


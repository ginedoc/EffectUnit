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

int Mode[4];

void init_LED();
void set_LED(int, int);
int get_BCD(int value);
#endif	/* LED_H */


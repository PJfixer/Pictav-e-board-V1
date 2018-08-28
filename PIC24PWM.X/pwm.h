/* 
 * File:   pwm.h
 * Author: pierre
 *
 * Created on 25 août 2018, 21:51
 */

#include <xc.h>

//void InitializeTimer2For_PWM(void);
void Init_PWM(void);
void Calc_PWM(int16_t *range,uint8_t *index,double Freq);
int16_t map(float x, float in_min, float in_max, int16_t out_min, int16_t out_max);
void out_PWM(uint8_t timer,uint8_t channel,double frequency,float duty_cycle);
 int16_t round1 (double x);
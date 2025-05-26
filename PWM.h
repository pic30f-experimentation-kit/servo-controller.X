/* 
 * File:   PWM.h
 * Author: cristinamidorifukuda
 *
 * Created on May 25, 2025, 4:54 PM
 */

#ifndef PWM_H
#define	PWM_H

#define SCALE 1
#define PWM_PERIOD 4594/SCALE
#define PWM_MIDDLE_POSITION 1459/SCALE

#define PULSE_MAX 1000
#define PULSE_MIN 0

/**
 * 
 */
void __attribute__((interrupt)) _T2Interrupt(void);

/**
 * 
 */
void initializationPWM();  

/**
 * 
 * @param position
 * @return 
 */
void servoSetPositionFromADCBuffer (int position);

#endif	/* PWM_H */


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
#define PWM_MIDDLE_POSITION 344/SCALE

#define PULSE_MAX 460  //For +90º with 256 prescale
#define PULSE_CERO 344 //For 0º   with 256 prescale
#define PULSE_MIN 230  //For -90º with 256 prescale

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
void servoSetPositionFromADC (int ADC);

#endif	/* PWM_H */


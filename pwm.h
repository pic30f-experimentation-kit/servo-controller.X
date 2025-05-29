/* 
 * File:   PWM.h
 * Author: cristinamidorifukuda
 *
 * Created on May 25, 2025, 4:54 PM
 */

#ifndef PWM_H
#define	PWM_H

// In real conditions it should be 1. 
// Set the scale to 50 or 100 to use MPLABX simulator's logic analyzer
#define SCALE 100

// At selected pre-scaler and Fosc...
#define PWM_PERIOD               14739/SCALE  // ... this is 4.0ms
#define PWM_RIGHTMOST_POSITION    7370/SCALE  // ... this is 2.0ms
#define PWM_LEFTMOST_POSITION     3685/SCALE  // ... this is 1.0ms
#define PWM_RANGE (PWM_RIGHTMOST_POSITION - PWM_LEFTMOST_POSITION)
#define PWM_MIDDLE_POSITION       5528/SCALE  // ... this is 1.5ms

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


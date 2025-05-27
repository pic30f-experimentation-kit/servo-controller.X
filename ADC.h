/* 
 * File:   ADC.h
 * Author: cristinamidorifukuda
 *
 * Created on May 25, 2025, 4:49 PM
 */

#ifndef ADC_H
#define	ADC_H

#define ADC_MAX 4095
#define ADC_MIN 0
#define VREF 5

#define MAXVOLTAGE = 5;
#define MINVOLTAGE = 0;

/**
 * 
 */
void initializationADC();

/**
 * 
 */
void __attribute__((interrupt, no_auto_psv)) _ADCInterrupt(void);

/**
 * 
 */


#endif	/* ADC_H */


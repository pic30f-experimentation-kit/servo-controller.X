/* 
 * File:   ADC.h
 * Author: cristinamidorifukuda
 *
 * Created on May 25, 2025, 4:49 PM
 */

#ifndef ADC_H
#define	ADC_H

#define ADC_MAX 1023
#define ADC_MIN 0
#define VREF 5

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


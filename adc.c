#ifndef TEST

#include <xc.h>
#include "adc.h"
#include "shared.h"

int captureADC = 0;

void __attribute__((interrupt, no_auto_psv)) _ADCInterrupt(void) {
    // Reset the interruption flag:
    IFS0bits.ADIF = 0;

    // Averages all available input captures, to remove noise:
    unsigned int average = 0;
    volatile unsigned int *adcptr = &ADCBUF0;
    for (int n = 0; n < 16; n++) {
        average += *adcptr;
        adcptr++;
    }
    average >>= 4; //Divide by 16
    
    // Place a breakpoint inside the conditional section to stop
    // the program every time the stimulus changes.
    if (average != captureADC) {
        captureADC = average;
        bufferWrite (&capturesBuffer, average);
    }
}

void initializationADC() {
    // Configure the A/D module
    // -> Select voltage reference source to match expected range 
    //    on analog inputs:
    ADCON2bits.VCFG = 0; // Use VRef+ = AVdd and VRef- = AVss
    
    // -> Select the analog conversion clock to match desired data rate with
    //    processor clock: FRC = 7.32MHz, PLL=x16 -> Fosc = 117.92MHz -> Tcy = 33.92ns
    ADCON3bits.ADCS = 63; // TAD = Tcy * (ADCS + 1) / 2 = 1102µs
    
    // -> Determine how sampling will occur
    ADCON1bits.ASAM = 1;  // Enable automating sampling.
    ADCON1bits.SSRC = 7;  // Use internal timer.
    
    // -> Determine how inputs will be allocated to the S/H channel
    TRISBbits.TRISB6 = 1; // AN6/RB6 is configured as input.
    ADPCFGbits.PCFG6 = 0; // AN6/RB6 is configured as analog.
    ADCHSbits.CH0NA = 0;  // Negative input is VRef-
    ADCHSbits.CH0SA = 6;  // Sample analog data from AN6.
    
    // -> Select how conversion results are presented in the buffer
    ADCON1bits.FORM = 0;  // Positive integer.
    ADCON2bits.SMPI = 15; // 16 samples per interrupt.

    // -> Select interrupt rate
    ADCON3bits.SAMC = 31; // Configure internal timer to allow 32TAD for sampling time.
    
    // -> Turn on A/D module
    ADCON1bits.ADON = 1;
    
    // Configure A/D interrupt (if required)
    // -> Clear ADIF bit
    IFS0bits.ADIF = 0;
    
    // -> Select A/D interrupt priority
    IPC2bits.ADIP = 1; // Lowest possible interrupt level
    IEC0bits.ADIE = 1; // Enable interrupts for A/D module
}

#endif
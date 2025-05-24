/* 
 * File:   main.c
 * Author: cristinamidorifukuda
 *
 * Created on May 4, 2025, 6:21 PM
 */
#include <xc.h>
#include "buffer.h"
#include "test.h"

#pragma config FOSC_FOSFPR = FRC_PLL16     // FRC w/PLL 16x 
#pragma config FOSC_FCKSMEN = CSW_FSCM_OFF // Sw Disabled, Mon Disabled 
#pragma config FICD_ICS = ICS_PGD         // Use PGC/EMUC and PGD/EMUD
#pragma config FWDT_WDT = WDT_OFF         // Disable watchdog

#define SCALE 1
#define PWM_PERIOD 4594/SCALE
#define PWM_MIDDLE_POSITION 1459/SCALE


#ifndef TEST
int capture = 0;

void __attribute__((interrupt, no_auto_psv)) _ADCInterrupt(void) {
    // Reset the interruption flag:
    IFS0bits.ADIF = 0;

    // Averages all available input captures, to remove noise:
    unsigned int average = 0;
    volatile unsigned int *adcptr = &ADCBUF0;
    for(int n = 0; n < 16; n++) {
        average += *adcptr;
        adcptr++;
    }
    average >>= 4;
    
    // Place a breakpoint inside the conditional section to stop
    // the program every time the stimulus changes.
    if (average != capture) {
        bufferWrite(average);
    }
}

void __attribute__((interrupt)) _T2Interrupt(void) {
    IFS0bits.T2IF = 0; //Clear interrupt flag
    OC2R = capture;
}

void initializationPWM() {    
    //vamos a usar OC1
    TRISBbits.TRISB9 = 0; // Asegura que RB9 (OC2) sea salida
    ADPCFGbits.PCFG9 = 1; // AN9/RB9 is configured as digital.
    
    //Period 20ms. 1ms = -90ª. 1.5ms = 0ª. 2ms = 90ª
    
    //110 Without Fault mode. 111 With Fault mode
    OC2CONbits.OCM = 6;
    
    //vamos a usar timer2
    OC2CONbits.OCTSEL = 0;
    
    //Set PWM period. PWMT = (Pry+1)*Tcy*Prescale
    //Tcy = 17ns. No prescale. --> PRY = 1176469 --> necesito un prescaler
    //prescaler 1:256 (cada 256 ciclos de reloj, timer cuenta 1 vez) --> PRY = 4594
    T2CONbits.TCKPS = 3; //prescaler 256
        
    //TMRY
    PR2 = PWM_PERIOD; //Period register2 4594
    
    //Set PWM Duty Cycle -> to 90º DC = 10%
    OC2RS = PWM_MIDDLE_POSITION;
    
    //Write initial duty cycle
    OC2R = PWM_MIDDLE_POSITION; 
    
    //Enable interrupts -> interrupt when timer for period is reached
    IPC0bits.T1IP = 1; //priority 1 for time interrupts
    IFS0bits.T2IF = 0; //clear interrupt flag for timer 2
    IEC0bits.T2IE = 1; //Enable interrupts for timer 2
    T2CONbits.TON = 1; //Start Timer 2           
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

/*
 * 
 */
int main(void) {
    int c = 0;
    
   initializationPWM();
   initializationADC();
    
    for(;;) {
        while(bufferIsEmpty());
        int capture = bufferRead();
        servoSetPosition(capture);
    }
}
#else
int main(void) {
    testInitialize();
    testBuffer();
    testReport();
    while(1);
}
#endif

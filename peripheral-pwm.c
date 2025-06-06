#include <xc.h>
#include "peripheral-pwm.h"
#include "servo.h"

void __attribute__((interrupt, no_auto_psv)) _T2Interrupt(void) {
    IFS0bits.T2IF = 0; //Clear interrupt flag    
    OC2RS = servoGetPWMDutyCycle(); //Store into DC buffer register
}

void initializationPWM() {    
    //we will use OC2
    TRISBbits.TRISB9 = 0; // OC2 is output
    ADPCFGbits.PCFG9 = 1; // AN9/RB9 is configured as digital
    
    //110 Without Fault mode. 111 With Fault mode
    OC2CONbits.OCM = 6;
    
    //We will use Timer2
    OC2CONbits.OCTSEL = 0;
    
    //Set PWM period. PWMT = (Pry+1)* Tcy * Prescale
    //Tcy = 17ns. No prescale. --> PRY = 1176469 --> necesito un prescaler
    //prescaler 1:8 (cada 8 ciclos de reloj, timer cuenta 1 vez) --> PRY = 14739
    T2CONbits.TCKPS = 1; //prescaler 8
        
    //Period 20ms - 50Hz. 1ms = -90ª. 1.5ms = 0ª. 2ms = 90ª
    //Values to configure the Timer2
    PR2 = PWM_PERIOD; //Period register
    
    //Set PWM Duty Cycle -> to 90º DC = 10% (2ms)
    OC2RS = PWM_MIDDLE_POSITION; //DC buffer register
    
    //Write initial duty cycle
    OC2R = PWM_MIDDLE_POSITION;  //Read Only DC register
    
    //Enable interrupts -> interrupt when timer for period is reached
    IPC0bits.T1IP = 1; //priority 1 for time interrupts
    IFS0bits.T2IF = 0; //clear interrupt flag for timer 2
    IEC0bits.T2IE = 1; //Enable interrupts for timer 2
    T2CONbits.TON = 1; //Start Timer 2           
}

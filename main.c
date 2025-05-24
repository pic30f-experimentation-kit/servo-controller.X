/* 
 * File:   main.c
 * Author: cristinamidorifukuda
 *
 * Created on May 4, 2025, 6:21 PM
 */
#include <xc.h>
#pragma config FOSC_FOSFPR = FRC_PLL16     // FRC w/PLL 16x 
#pragma config FOSC_FCKSMEN = CSW_FSCM_OFF // Sw Disabled, Mon Disabled 
#pragma config FICD_ICS = ICS_PGD         // Use PGC/EMUC and PGD/EMUD
#pragma config FWDT_WDT = WDT_OFF         // Disable watchdog

#define SCALE 1
#define PWM_PERIOD 4594/SCALE
#define PWM_MIDDLE_POSITION 1459/SCALE

int inter = 0;

void __attribute__((interrupt)) _T2Interrupt(void) {
    IFS0bits.T2IF = 0; //Clear interrupt flag
    inter++;
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

/*
 * 
 */
int main(void) {
    int c = 0;
    
   initializationPWM();
    
    while(1) {   
        c++;
    }
}

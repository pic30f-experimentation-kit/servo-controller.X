/* 
 * File:   main.c
 * Author: cristinamidorifukuda
 *
 * Created on May 4, 2025, 6:21 PM
 */
#include <xc.h>
#include "buffer.h"
#include "servo.h"
#include "test.h"
#include "adc.h"
#include "pwm.h"

#pragma config FOSC_FOSFPR = FRC_PLL16     // FRC w/PLL 16x 
#pragma config FOSC_FCKSMEN = CSW_FSCM_OFF // Sw Disabled, Mon Disabled 
#pragma config FICD_ICS = ICS_PGD         // Use PGC/EMUC and PGD/EMUD
#pragma config FWDT_WDT = WDT_OFF         // Disable watchdog

#ifndef TEST

Buffer capturesBuffer; //Buffer that stores output values of ADC converter

/*
 * 
 */
int main(void) {
    
    
   //Initialization of modules
   initializationPWM();
   initializationADC();
    
   //Initialization of variables
   bufferInitialize(&capturesBuffer);
   
   int capture = 0;

   for(;;) {
        
       //ADC module is capturing data and writing it in the buffer
       //While the last data that was written in the buffer has not been read,
       //read it and set servo position accordingly
       //
        while(!bufferIsEmpty(&capturesBuffer)) {
            capture = bufferRead (&capturesBuffer);
            servoSetPositionFromADC(capture);
        }
    }
}

#else

int main(void) {
    testInitialize();
    testBuffer();
    testServo();
    testReport();
    while(1);
}

#endif

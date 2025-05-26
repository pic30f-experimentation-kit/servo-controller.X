/* 
 * File:   main.c
 * Author: cristinamidorifukuda
 *
 * Created on May 4, 2025, 6:21 PM
 */
#include <xc.h>
#include "buffer.h"
#include "test.h"
#include "ADC.h"
#include "PWM.h"

#pragma config FOSC_FOSFPR = FRC_PLL16     // FRC w/PLL 16x 
#pragma config FOSC_FCKSMEN = CSW_FSCM_OFF // Sw Disabled, Mon Disabled 
#pragma config FICD_ICS = ICS_PGD         // Use PGC/EMUC and PGD/EMUD
#pragma config FWDT_WDT = WDT_OFF         // Disable watchdog




#ifndef TEST


Buffer CapturesBuffer; //Buffer that stores output values of ADC converter

/*
 * 
 */
int main(void) {
    
    
   //Initialization of modules
   initializationPWM();
   initializationADC();
    
   //Initialization of variables
   bufferInitialize(&CapturesBuffer);
   
   int capture = 0;

   for(;;) {
        
       //ADC module is capturing data and writing it in the buffer
       //While we have not read the last data that was written in the buffer
       //
        while(!bufferIsEmpty(&CapturesBuffer))
        {
            capture = bufferRead (&CapturesBuffer);
            servoSetPositionFromADCBuffer (capture);
        }
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

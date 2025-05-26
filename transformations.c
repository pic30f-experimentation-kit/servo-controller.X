#include "ADC.h"
#include "PWM.h"

//DeltaPulse / DeltaADC
float ratio = (float)(PULSE_MAX - PULSE_MIN) / (ADC_MAX - ADC_MIN);

/*
int PositiontoPulseWidth (int Position) {
}

int DutyCycletoPulseWidth (int DutyCycle) {
}

int PositionToDutyCycle (int position) {
}

int ADCtoPosition (int ADCValue) {

}
*/

/*
 * 
 */
int ADCtoPulseWidth (int ADCValue) {
    
    int PulseWidth = PULSE_MIN + ratio * (ADCValue - ADC_MIN);
            
    return PulseWidth;
}

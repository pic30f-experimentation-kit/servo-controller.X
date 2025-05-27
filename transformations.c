#include "ADC.h"
#include "PWM.h"

//DeltaPulse / DeltaADC
const float ratio = (float)(PULSE_MAX - PULSE_MIN) / (ADC_MAX - ADC_MIN);

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

/**
 * 
 * @param ADCValue - output value from ADC module
 * @return integer representing the pulse Width for a PWM module
 */
int ADCtoPulseWidth (int ADCValue) {
    
    int PulseWidth = PULSE_MIN + ratio * (ADCValue - ADC_MIN);
            
    return PulseWidth;
}

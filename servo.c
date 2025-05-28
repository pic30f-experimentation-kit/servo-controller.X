#include "pwm.h"
#include "servo.h"
#include "test.h"

static int pwmSegment = 0;
static int servoPosition = PWM_MIDDLE_POSITION;

void servoInitialize() {
    pwmSegment = 0;
    servoPosition = PWM_MIDDLE_POSITION;
}

void servoSetPositionFromADC(int position) {
    float p = (float) position;
    p *= PWM_RANGE;
    p /= 4096;
    p += PWM_LEFTMOST_POSITION;
    servoPosition = (int)p;
}

int servoGetPWMDutyCycle() {
    if (pwmSegment++ == 0) {
        return servoPosition;
    }
    if (pwmSegment > 4) {
        pwmSegment = 0;
    }
    return 0;
}

#ifdef TEST
void servo_can_position_itself() {
    servoSetPositionFromADC(0);
    assertWithinBounds("SERVO_POS_01", servoPosition, PWM_LEFTMOST_POSITION - 1, PWM_LEFTMOST_POSITION + 1);
    servoSetPositionFromADC(4095);
    assertWithinBounds("SERVO_POS_02", servoPosition, PWM_RIGHTMOST_POSITION - 1, PWM_RIGHTMOST_POSITION + 1);
    servoSetPositionFromADC(2048);
    assertWithinBounds("SERVO_POS_03", servoPosition, PWM_MIDDLE_POSITION - 1, PWM_MIDDLE_POSITION + 1);
}

void servo_can_produce_duty_cycle() {
    servoInitialize();
    
    assertNotZero("SERVO_DC_0", servoGetPWMDutyCycle());
    assertZero("SERVO_DC_1", servoGetPWMDutyCycle());
    assertZero("SERVO_DC_2", servoGetPWMDutyCycle());
    assertZero("SERVO_DC_3", servoGetPWMDutyCycle());
    assertZero("SERVO_DC_4", servoGetPWMDutyCycle());

    assertNotZero("SERVO_DC_5", servoGetPWMDutyCycle());
    assertZero("SERVO_DC_6", servoGetPWMDutyCycle());
    assertZero("SERVO_DC_7", servoGetPWMDutyCycle());
    assertZero("SERVO_DC_8", servoGetPWMDutyCycle());
    assertZero("SERVO_DC_9", servoGetPWMDutyCycle());

    assertNotZero("SERVO_DC_10", servoGetPWMDutyCycle());
}

void testServo() {
    servo_can_position_itself();
    servo_can_produce_duty_cycle();
}
#endif

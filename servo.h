#ifndef SERVO_H
#define	SERVO_H

/**
 * Sets the servo position.
 * The position is a positive integer of 12 bits.
 * Middle position is 2048.
 * @param position The position.
 */
void servoSetPositionFromADC(int position);

/**
 * Obtains the duty cycle for the servo.
 * @return The duty cycle.
 */
int servoGetPWMDutyCycle();


#ifdef TEST
/**
 * Tests the servo functionalities.
 */
void testServo();
#endif

#endif	/* SERVO_H */


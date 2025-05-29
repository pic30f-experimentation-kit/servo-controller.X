/* 
 * File:   test.h
 * Author: jmgonet
 *
 * Created on May 24, 2025, 8:32 AM
 */

#ifndef TEST_H
#define	TEST_H

#ifdef TEST

/** Initializes test bench. */
void testInitialize();

/**
 * Asserts that actual and expected values are equal.
 * @param testId Test identifier.
 * @param actual Actual value.
 * @param expected Expected value.
 */
void assertEquals(const char *testId, int expected, int actual);

/**
 * Asserts that actual value is within the defined limits.
 * @param testId Test identifier.
 * @param actual Actual value.
 * @param min Actual value must be greater or equal min value.
 * @param max Actual value must be lesser or equal max value.
 */
void assertWithinBounds(const char *testId, int actual, int min, int max);

/**
 * Asserts that actual value is not zero.
 * @param testId Test identifier.
 * @param actual Actual value.
 */
void assertNotZero(const char *testId, int actual);

/**
 * Asserts that actual value is zero.
 * @param testId Test identifier.
 * @param actual Actual value.
 */
void assertZero(const char *testId, int actual);

/** Ends test and reports errors. */
void testReport();

#endif

#endif	/* TEST_H */


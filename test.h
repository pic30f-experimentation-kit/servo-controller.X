/* 
 * File:   test.h
 * Author: jmgonet
 *
 * Created on May 24, 2025, 8:32 AM
 */

#ifndef TEST_H
#define	TEST_H

#ifdef TEST

void testInitialize();
void assertEquals(const char *testId, int expected, int actual);
void testReport();

#endif

#endif	/* TEST_H */


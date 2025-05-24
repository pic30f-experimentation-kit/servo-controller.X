#ifdef TEST
#include <stdio.h>
#include <xc.h>
#include "test.h"

int testsPassed;
int testsFailed;

void putch(char data) {
   while( ! U1STAbits.UTXBF);
   U1TXREG = data; 
}

void initializationUART() {
    // Initialize the UxBRG register for the appropriate baud rate.
    U1BRG = 95;

    // Set the number of data bits, number of Stop bits, and parity selection.
    // The most common data format is 8 bits, no parity and one Stop
    // bit (denoted as 8, N, 1), which is the default (POR) setting.
    U1MODEbits.PDSEL = 0;   // 8 Bits, no parity
    U1MODEbits.STSEL = 0;   // 1 Stop bit.

    // Simulator UART is connected to the regular pins
    U1MODEbits.ALTIO = 0;   // Use regular pins - U1TX / U1RX

    // Enable UART1:
    U1MODEbits.UARTEN = 1;  // Enable UART1
    U1STAbits.UTXEN = 1;    // Enable UART1 transmitter (after enabling UART).
}

void testInitialize() {
    initializationUART();
    testsFailed = 0;
    testsPassed = 0;
    printf("Starting tests:\r\n");
}

void assertEquals(const char *testId, int expected, int actual) {
    if (actual != expected) {
        printf("Test %s: expected is %d, but actual is %d", 
                testId, expected, actual);
        testsFailed++;
    } else {
        testsPassed++;
    }
}

void testReport() {
    printf("Finished tests:\r\n");
    printf("- Tests passed: %d\r\n", testsPassed);
    printf("- Tests failed: %d\r\n", testsFailed);
}

#endif

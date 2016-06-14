#include "PROCESSOR_PARKUEST.h"
#include <delays.h>
#include "COLOR_PARKUEST.h"
#include "SoftwareUART_PARKUEST.h"

static void DelayTXBitUART(void) {
    Delay10KTCYx(1);
}

unsigned char ReadUART2_SoftwareSync(void) {
    unsigned long contador = 0;
    unsigned char bitcount = 0;
    unsigned char UartDATA = 0;

    if (PORTBbits.RB2 == 0) {
        do {
            while (PORTBbits.RB2 == 0 && contador < (unsigned long)200000)contador++;
            if (PORTBbits.RB3 == 1) {
                UartDATA |= 0x01;
            } else {
                UartDATA |= 0x00;
            }
            contador = 0;
            while (PORTBbits.RB2 == 1 && contador < (unsigned long)200000)contador++;
            if (bitcount < 7)UartDATA = UartDATA << 1;
            bitcount++;
        } while (bitcount < 8);
        contador = 0;
        while (PORTBbits.RB2 == 0 && contador < (unsigned long)200000)contador++;
    }
    return (UartDATA);
}

void WriteUART1_SoftwareSync(unsigned char uartdata) {
    unsigned char i = 0;

    LATBbits.LATB3 = 0;
    LATBbits.LATB2 = 0;
    for (i = 0; i < 8; i++) {
        LATBbits.LATB2 = 0;
        if (i == 0) {
            LATBbits.LATB3 = (uartdata >> 0x07)&0x01;
        } else {
            LATBbits.LATB3 = ((uartdata >> 7 - i) & 0x01);
        }
        DelayTXBitUART();
        LATBbits.LATB2 = 1;
        DelayTXBitUART();
    }
    LATBbits.LATB2 = 0;
    DelayTXBitUART();
    LATBbits.LATB2 = 1;
    LATBbits.LATB3 = 0;
}

#warning "UART2 by Software"




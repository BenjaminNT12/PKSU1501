#include <p18cxxx.h>
#include "PROCESSOR_PARKUEST.h"
#include "EEPROM_PARKUEST.h"

#if defined __18F25K22_H || defined __18F24K22_H
    BOOL WriteEEPROM(unsigned char _EEADR,unsigned char _EEDATA){
        EEADR  = _EEADR;
        EEDATA = _EEDATA;
        EECON1bits.EEPGD = 0;
        EECON1bits.CFGS = 0;
        EECON1bits.WREN = 1;
        INTCONbits.GIE = 0;
        EECON2 = 0x55;
        EECON2 = 0xAA;
        EECON1bits.WR = 1;
        while(!PIR2bits.EEIF);
        PIR2bits.EEIF=0;
        EECON1bits.WREN = 0;
        INTCONbits.GIE = 1;
        return(1);
    }

    unsigned char ReadEEPROM(unsigned char _EEADR){
        unsigned char _temp=0;
        INTCONbits.GIE = 0;
        EEADR = _EEADR;
        EECON1bits.EEPGD = 0;
        EECON1bits.CFGS = 0;
        EECON1bits.RD = 1; // Read Control bit
        _temp=EEDATA;
        INTCONbits.GIE = 1;
        return(_temp);
    }
#endif



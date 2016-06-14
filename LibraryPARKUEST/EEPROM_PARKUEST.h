/* 
 * File:   EEPROM_PARKUEST.h
 * Author: Nicolas
 *
 * Created on 2 de abril de 2014, 06:43 PM
 */

#ifndef EEPROM_PARKUEST_H
#define	EEPROM_PARKUEST_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <GenericTypeDefs.h>

BOOL WriteEEPROM            (unsigned char _EEADR,unsigned char _EEDATA);
unsigned char ReadEEPROM    (unsigned char _EEADR);

#ifdef	__cplusplus
}
#endif

#endif	/* EEPROM_PARKUEST_H */


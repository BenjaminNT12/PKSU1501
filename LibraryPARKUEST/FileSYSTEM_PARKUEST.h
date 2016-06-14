/* 
 * File:   FileSYSTEM_PARKUEST.h
 * Author: Nicolas
 *
 * Created on 10 de junio de 2015, 11:44 AM
 */

#ifndef FILESYSTEM_PARKUEST_H
#define	FILESYSTEM_PARKUEST_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "../LibraryPARKUEST/SONAR_PARKUEST.h"
// Directory
#define AddressColorsEEPROM             0x00 /*6 Bytes*/
#define AddressDistanceEEPROM           0x06 /*1 Bytes*/
#define AddressIdEEPROM                 0x07 /*1 Bytes*/
#define AddressHardwareIdEEPROM         0x08 /*1 Bytes*/
#define AddressIndicatoOnOFF            0x09 /*1 Bytes*/
#define AddressOnlyOneIndicatorIDs      0x0A /*16 Bytes*/


    BOOL ReadColorsPARKUEST         (COLOR *Color_1);
    BOOL ReadIdPARKUEST             (unsigned char *IdSensorSLAVE_3);
    BOOL ReadHardwareIdPARKUEST     (unsigned char *IdSensorSLAVE_9);
    BOOL WriteIdHardwarePARKUEST    (unsigned char *IdSensorSLAVE_10);
    BOOL WriteColorsPARKUEST        (COLOR *Color_4);
    BOOL WriteDistancePARKUEST      (SONAR1 *SensingDistance_5);
    BOOL WriteIdPARKUEST            (unsigned char *IdSensorSLAVE_6);
    BOOL FileCOLORS                 (COLOR *color_7);
    BOOL FileDISTANCE               (SONAR1 *SensingDistance_8);
    BOOL FileID                     (unsigned char *IdSensorSLAVE_9);
    BOOL ReadIndicatorOnOff         (void);
    BOOL FileINDICATOR_OnOff        (void);
    BOOL WriteIndicatorOnOff        (BOOL _OnOff);
    BOOL ReadOnlyOneIndicatorIDs    (unsigned char *Storage);
    BOOL WriteOnlyOneIndicatorIDs   (unsigned char *Storage);
    BOOL ReadDistancePARKUEST       (SONAR1 *SensingDistance_2);
    
#ifdef	__cplusplus
}
#endif

#endif	/* FILESYSTEM_PARKUEST_H */


#include "PROCESSOR_PARKUEST.h"
#include "EEPROM_PARKUEST.h"
#include "COLOR_PARKUEST.h"
#include "COMMUNICATION_PARKUEST.h"
#include <GenericTypeDefs.h>
#include "SONAR_PARKUEST.h"
#include "FileSYSTEM_PARKUEST.h"

BOOL ReadColorsPARKUEST(COLOR *Color_1) {
    unsigned char ColorPARKUEST[6] = {0};
    unsigned char i = 0;

    for (i = 0; i < 6; i++) {
        ColorPARKUEST[i] = ReadEEPROM(AddressColorsEEPROM + i);
    }
    if (ColorPARKUEST[0] == 0xFF && ColorPARKUEST[1] == 0xFF && ColorPARKUEST[2] == 0xFF && ColorPARKUEST[3] == 0xFF && ColorPARKUEST[4] == 0xFF && ColorPARKUEST[5] == 0xFF) {
        return (0);
    }
    if (ColorPARKUEST[0] != 0 || ColorPARKUEST[1] != 0 || ColorPARKUEST[2] != 0 || ColorPARKUEST[3] != 0 || ColorPARKUEST[4] != 0 || ColorPARKUEST[5] != 0) {
        Color_1->RED_A = ColorPARKUEST[0];
        Color_1->GREEN_A = ColorPARKUEST[1];
        Color_1->BLUE_A = ColorPARKUEST[2];
        Color_1->RED_D = ColorPARKUEST[3];
        Color_1->GREEN_D = ColorPARKUEST[4];
        Color_1->BLUE_D = ColorPARKUEST[5];
        return (1);
    }
    return (0);
}

BOOL ReadDistancePARKUEST(SONAR1 *SensingDistance_2) {
    unsigned char _temp = 0;

    _temp = ReadEEPROM(AddressDistanceEEPROM);
    if (_temp == 0xFF) {
        return (0);
    }
    if (_temp != 0) {
        SensingDistance_2->SensingDistance = _temp;
        return (1);
    }
    return (0);
}

BOOL ReadIndicatorOnOff(void) {
    unsigned char _temp = 0;

    _temp = ReadEEPROM(AddressIndicatoOnOFF);
    if (_temp == 0xFF) {
        return (1);
    }
    if (_temp != 0) {
        if(_temp == 1){
            return (1);
        }
    }
    return (0);
}

BOOL WriteIndicatorOnOff(BOOL _OnOff) {

    if(_OnOff == 1){
        WriteEEPROM(AddressIndicatoOnOFF,1);
        return(1);
    }else{
        WriteEEPROM(AddressIndicatoOnOFF,0);
        return(1);
    }
    return (0);
}

BOOL WriteOnlyOneIndicatorIDs(unsigned char *Storage) {
    unsigned char i = 0;

    for (i = 0; i < 16; i++) {
        WriteEEPROM(AddressOnlyOneIndicatorIDs + i, Storage[i]);
    }
}

BOOL ReadOnlyOneIndicatorIDs(unsigned char *Storage) {
    unsigned char i = 0;
    unsigned char _temp = 0;
    BOOL fLA46456 = 0;

    for (i = 0; i < 16; i++) {
        _temp = ReadEEPROM(AddressOnlyOneIndicatorIDs + i);
        if(_temp != 0xFF && _temp != 0){
            Storage[i] = _temp;
            fLA46456 = 1;
        }else{
            Storage[i] = 0;
        }
    }
    return (fLA46456);
}

BOOL ReadIdPARKUEST(unsigned char *IdSensorSLAVE_3) {
    unsigned char _tempID = 0;

    _tempID = ReadEEPROM(AddressIdEEPROM);
    if (_tempID == 0xFF) {
        return (0);
    }
    if (_tempID != 0) {
        *IdSensorSLAVE_3 = _tempID;
        return (1);
    }
    return (0);
}

BOOL ReadHardwareIdPARKUEST(unsigned char *IdSensorSLAVE_10) {
    unsigned char _tempID = 0;

    _tempID = ReadEEPROM(AddressHardwareIdEEPROM);
    if (_tempID == 0xFF) {
        return (0);
    }
    if (_tempID != 0) {
        *IdSensorSLAVE_10 = _tempID;
        return (1);
    }
    return (0);
}

BOOL WriteColorsPARKUEST(COLOR *Color_4) {
    if (WriteEEPROM((AddressColorsEEPROM), Color_4->RED_A) == 1) {
        if (WriteEEPROM((AddressColorsEEPROM + 1), Color_4->GREEN_A) == 1) {
            if (WriteEEPROM((AddressColorsEEPROM + 2), Color_4->BLUE_A) == 1) {
                if (WriteEEPROM((AddressColorsEEPROM + 3), Color_4->RED_D) == 1) {
                    if (WriteEEPROM((AddressColorsEEPROM + 4), Color_4->GREEN_D) == 1) {
                        if (WriteEEPROM((AddressColorsEEPROM + 5), Color_4->BLUE_D) == 1) {
                            return (1);
                        }
                    }
                }
            }
        }

    }
    return (0);
}

BOOL WriteDistancePARKUEST(SONAR1 *SensingDistance_5) {
    if (WriteEEPROM(AddressDistanceEEPROM, SensingDistance_5->SensingDistance) == 1) {
        return (1);
    }
    return (0);
}

BOOL WriteIdPARKUEST(unsigned char *IdSensorSLAVE_6) {
    if (WriteEEPROM(AddressIdEEPROM, *IdSensorSLAVE_6) == 1) {
        return (1);
    }
    return (0);
}

BOOL WriteIdHardwarePARKUEST(unsigned char *IdSensorSLAVE_11) {
    if (WriteEEPROM(AddressHardwareIdEEPROM, *IdSensorSLAVE_11) == 1) {
        return (1);
    }
    return (0);
}

BOOL FileCOLORS(COLOR *color_7) {
    if (ReadColorsPARKUEST(color_7) == 1) {
        return (1);
    } else {
        WriteColorsPARKUEST(color_7);
    }
    return (0);
}

BOOL FileDISTANCE(SONAR1 *SensingDistance_8) {
    if (ReadDistancePARKUEST(SensingDistance_8) == 1) {
        return (1);
    } else {
        WriteDistancePARKUEST(SensingDistance_8);
    }
    return (0);
}

BOOL FileINDICATOR_OnOff(void) {
    if (ReadIndicatorOnOff() == 1) {
        return (1);
    }
    return (0);
}

BOOL FileID(unsigned char *IdSensorSLAVE_9) {
    unsigned char _tempID = 0;

    if (ReadHardwareIdPARKUEST(&_tempID) == 0) { // leee el id de hardware grabado por ultima vez
        WriteIdHardwarePARKUEST(IdSensorSLAVE_9); // si no lo encuentra escribe por primera vez el id de hardware
    } else {
        if (_tempID == *IdSensorSLAVE_9) {// si encontro in id de hardware anterio y coincide con el actual debe retornar el id que fue configurado por ultima vez
            if (ReadIdPARKUEST(IdSensorSLAVE_9) == 1) { // devuelve el utlimo id por software
                return (1);
            }else{
                WriteIdPARKUEST(IdSensorSLAVE_9); // si no existe un id por software asignar uno
                return(0);
            }
        }else{
            WriteIdHardwarePARKUEST(IdSensorSLAVE_9); // si el id por hardware cambio escribir el utlimo id por hardware
            WriteIdPARKUEST(IdSensorSLAVE_9); // si el id por hardware cambio escribir el utlimo id por software
            return (1);
        }
    }

    return (0);
}


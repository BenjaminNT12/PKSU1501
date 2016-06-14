/* 
 * File:   ComINDICADOR_PARKUEST.h
 * Author: Nicolas
 *
 * Created on 26 de febrero de 2014, 05:59 PM
 */

#ifndef COMINDICADOR_PARKUEST_H
#define	COMINDICADOR_PARKUEST_H

#ifdef	__cplusplus
extern "C" {
#endif

    #define IND_RED_SIMPLE      1
    #define IND_GREN_ROUTINE    2
    #define IND_BLUE_ROUTINE    3
    #define IND_RED_ROUTINE     4

    #define ChangeColorSOFTWARE_A       0x41
    #define ChangeColorSOFTWARE_D       0x42
    #define ChangeStatusSOFTWARE_A      0x43
    #define ChangeStatusSOFTWARE_D      0x44
    #define ChangeOnSOFTWARE_D          0x45
    #define ChangeOffSOFTWARE_D         0x46
    #define OffINDICATOR                0x47
    #define OnINDICATOR                 0x48


    #if defined PIC18F_INDICADOR || defined PIC18F_MasterSLAVE
        void RemapINPUT_IND                 (void);
        void RemapOUTPUT_IND                (void);
        unsigned char ComBASIC_IndicadorIN  (void);
        void ComBASIC_IndicadorOUT          (unsigned char _option);

        BOOL ReceiveCommand2_UartSOFTWARE   (unsigned char *DATA, unsigned char lenght);
        void COMMUNICATION_INDICATOR        (unsigned char *CMD_DATA);

        void SmartOnlyOneIndicator          (unsigned char NumerOfSensor, unsigned char State,unsigned char SendCommand) ;
        void SendCommand1_UartSOFTWARE      (unsigned char *data, unsigned char lenght);
        void IndicatorSensorDEACTIVE        (void);
        void IndicatorSensorACTIVE          (void);
        void IndicatorColorDEACTIVE         (unsigned char _RED, unsigned char _GREEN, unsigned char _BLUE);
        void IndicatorColorACTIVE           (unsigned char _RED, unsigned char _GREEN, unsigned char _BLUE);
        void IndicatorOFF                   (void);
        void IndicatorON                    (void);
    #endif

#ifdef	__cplusplus
}
#endif

#endif	/* COMINDICADOR_PARKUEST_H */


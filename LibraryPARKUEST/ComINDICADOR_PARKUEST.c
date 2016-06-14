
#include <delays.h>
#include <GenericTypeDefs.h>
#include "PROCESSOR_PARKUEST.h"
#include <p18cxxx.h>
#include "PWM_PARKUEST.h"
#include "TIMER_PARKUEST.h"
#include "COLOR_PARKUEST.h"
#include "COMMUNICATION_PARKUEST.h"
#include "SoftwareUART_PARKUEST.h"
#include "EEPROM_PARKUEST.h"
#include "FileSYSTEM_PARKUEST.h"
#include "ComINDICADOR_PARKUEST.h"

#if defined __18F25K22_H || defined __18F24K22_H
    #if defined PIC18F_INDICADOR || defined PIC18F_MasterSLAVE
        extern FLAGs FLAG;
        extern COLOR COLORS;

        void RemapINPUT_IND(void) {
            INPUT_IN1 = 1;
            INPUT_IN2 = 1;
        }

        void RemapOUTPUT_IND(void) {
            INPUT_IN1 = 0;
            INPUT_IN2 = 0;
        }

        void ComBASIC_IndicadorOUT(unsigned char _option){
            switch (_option) {
                case 1:{
                    COM1_IND_O = 0;
                    COM2_IND_O = 0;
                }break;
                case 2:{
                    COM1_IND_O = 1;
                    COM2_IND_O = 0;
                }break;
                case 3:{
                    COM1_IND_O = 0;
                    COM2_IND_O = 1;
                }break;
                case 4:{
                    COM1_IND_O = 1;
                    COM2_IND_O = 1;
                }break;
            }
        }

        unsigned char ComBASIC_IndicadorIN(void) {
            if (COM1_IND_I == 0 && COM2_IND_I == 0) {
                if (FLAG.ChangeSTATE == 1) {
                    FLAG.ChangeSTATE = 0;
                    ChangeFadeCOLOR_FAST(green(), red4());
                    RGB_8bit(red4());
                }
                return (1);
            }

            if (COM1_IND_I == 0 && COM2_IND_I == 1) {
                if (FLAG.ChangeSTATE == 0) {
                    FLAG.ChangeSTATE = 1;
                    ChangeFadeCOLOR_FAST(red4(), blue());
                    RGB_8bit(blue());
                }
                return (2);
            }

            if (COM1_IND_I == 1 && COM2_IND_I == 0) {
                if (FLAG.ChangeSTATE == 0) {
                    FLAG.ChangeSTATE = 1;
                    ChangeFadeCOLOR_FAST(red4(), green());
                    RGB_8bit(green());
                }
                return (3);
            }

            if (COM1_IND_I == 1 && COM2_IND_I == 1) {
                if (FLAG.ChangeSTATE == 1) {
                    FLAG.ChangeSTATE = 0;
                    ChangeFadeCOLOR_FAST(blue(), red4());
                    RGB_8bit(red4());
                }
                return (4);
            }
        }

        void SendCommand1_UartSOFTWARE(unsigned char *data, unsigned char lenght) {
            unsigned char i = 0;

            for (i = 0; i < lenght; i++) {
                WriteUART1_SoftwareSync(*data);
                *data++;
            }
        }
        
        void SmartOnlyOneIndicator(unsigned char NumerOfSensor, unsigned char State,unsigned char SendCommand) {
            unsigned char _temp[4] = {0};
            static unsigned char Flag615 = 0;
            static BOOL OneSend = 0;
            
            if(FLAG.OnlyOneIndicatorActive == 1) {                
                Flag615 = OnlyOneIndicator(NumerOfSensor, State);
                _temp[1] = 0;
                _temp[2] = 0;
                _temp[3] = 0;
                if(Flag615 == 1 && OneSend == 0) {
                    OneSend = 1;
                    _temp[0] = ChangeStatusSOFTWARE_A;
                    SendCommand1_UartSOFTWARE(&_temp[0], 4);
                }else if(Flag615 == 0 && OneSend == 1) {
                    OneSend = 0;
                    _temp[0] = ChangeStatusSOFTWARE_D;
                    SendCommand1_UartSOFTWARE(&_temp[0], 4);
                }
            }else{
                _temp[0] = SendCommand;
                _temp[1] = 0;
                _temp[2] = 0;
                _temp[3] = 0;
                SendCommand1_UartSOFTWARE(&_temp[0], 4);
            }
        }

        BOOL ReceiveCommand2_UartSOFTWARE(unsigned char *DATA, unsigned char lenght) {
            unsigned char i = 0;
            unsigned long contador2 = 0;

            if (PORTBbits.RB2 == 0) {
                for (i = 0; i < lenght; i++) {
                    *DATA = ReadUART2_SoftwareSync();
                    *DATA++;
                    if (i < lenght - 1) while (PORTBbits.RB2 == 1 && contador2 < (unsigned long) 200000)contador2++;
                    contador2 = 0;
                }
                return (1);
            }
            return (0);
        }

        void COMMUNICATION_INDICATOR(unsigned char *CMD_DATA){
            static BOOL StatusINDICATOR = 0;
            
            switch(CMD_DATA[0]){
                case ChangeColorSOFTWARE_A:{
                    COLORS.RED_A = CMD_DATA[1];
                    COLORS.GREEN_A = CMD_DATA[2];
                    COLORS.BLUE_A = CMD_DATA[3];
                    WriteColorsPARKUEST(&COLORS);
                    if(StatusINDICATOR == 1){
                        RGB_8bit(COLORS.RED_A, COLORS.GREEN_A, COLORS.BLUE_A);
                    }
                }break;
                case ChangeColorSOFTWARE_D:{
                    COLORS.RED_D = CMD_DATA[1];
                    COLORS.GREEN_D = CMD_DATA[2];
                    COLORS.BLUE_D = CMD_DATA[3];
                    WriteColorsPARKUEST(&COLORS);
                    if(StatusINDICATOR == 0){
                        RGB_8bit(COLORS.RED_D, COLORS.GREEN_D, COLORS.BLUE_D);
                    }
                }break;
                case ChangeStatusSOFTWARE_A:{
                    StatusINDICATOR = 1;
                    ChangeFadeCOLOR(COLORS.RED_D, COLORS.GREEN_D, COLORS.BLUE_D, COLORS.RED_A, COLORS.GREEN_A, COLORS.BLUE_A);
                    RGB_8bit(COLORS.RED_A, COLORS.GREEN_A, COLORS.BLUE_A);
                }break;
                case ChangeStatusSOFTWARE_D:{
                    StatusINDICATOR = 0;
                    ChangeFadeCOLOR(COLORS.RED_A, COLORS.GREEN_A, COLORS.BLUE_A, COLORS.RED_D, COLORS.GREEN_D, COLORS.BLUE_D);
                    RGB_8bit(COLORS.RED_D, COLORS.GREEN_D, COLORS.BLUE_D);
                }break;
                case ChangeOnSOFTWARE_D:{
                    FileCOLORS(&COLORS);
                    ChangeFadeCOLOR_FAST(blue(), COLORS.RED_D, COLORS.GREEN_D, COLORS.BLUE_D);
                }break;
                case ChangeOffSOFTWARE_D:{
                    COLORS.RED_D = 0;
                    COLORS.GREEN_D = 0;
                    COLORS.BLUE_D = 0;
                    
                    COLORS.RED_A = 0;
                    COLORS.GREEN_A = 0;
                    COLORS.BLUE_A = 0;
                }break;
                case OffINDICATOR:{
                    if (StatusINDICATOR == 1) {
                        ChangeFadeCOLOR(COLORS.RED_A, COLORS.GREEN_A, COLORS.BLUE_A, 0, 0, 0);
                        PWM1_OFF();
                        PWM2_OFF();
                        PWM4_OFF();
                        TIMER0_OFF();
                        FLAG.IndicatorINTEGRATED_OnOff = 0;
                    } else {
                        ChangeFadeCOLOR(COLORS.RED_D, COLORS.GREEN_D, COLORS.BLUE_D, 0, 0, 0);
                        PWM1_OFF();
                        PWM2_OFF();
                        PWM4_OFF();
                        TIMER0_OFF();
                        FLAG.IndicatorINTEGRATED_OnOff = 0;
                    }
                    LED_AZUL = 0;
                    LED_ROJO = 0;
                    LED_VERDE = 0;
                }break;
                case OnINDICATOR:{
                    PWM1_ON();
                    PWM2_ON();
                    PWM4_ON();
                    TIMER0_ON();
                    ChangeFadeCOLOR(0,0,0,COLORS.RED_D, COLORS.GREEN_D, COLORS.BLUE_D);
                    LED_AZUL = 0;
                    LED_ROJO = 0;
                    LED_VERDE = 0;
                }break;
            }
            CMD_DATA[0] = 0;
            CMD_DATA[1] = 0;
            CMD_DATA[2] = 0;
            CMD_DATA[3] = 0;
        }

    #endif
#endif


        void IndicatorON(void) {
            unsigned char _Buffer1[4] = {0};

            _Buffer1[0] = ChangeOnSOFTWARE_D;
            _Buffer1[1] = 0;
            _Buffer1[2] = 0;
            _Buffer1[3] = 0;
            SendCommand1_UartSOFTWARE(&_Buffer1[0], 4);
        }

        void IndicatorOFF(void) {
            unsigned char _Buffer2[4] = {0};

            _Buffer2[0] = ChangeOffSOFTWARE_D;
            _Buffer2[1] = 0;
            _Buffer2[2] = 0;
            _Buffer2[3] = 0;
            SendCommand1_UartSOFTWARE(&_Buffer2[0], 4);
        }

        void IndicatorColorACTIVE(unsigned char _RED, unsigned char _GREEN, unsigned char _BLUE) {
            unsigned char _Buffer3[4] = {0};

            _Buffer3[0] = ChangeColorSOFTWARE_A;
            _Buffer3[1] = _RED;
            _Buffer3[2] = _GREEN;
            _Buffer3[3] = _BLUE;
            SendCommand1_UartSOFTWARE(&_Buffer3[0], 4);
        }

        void IndicatorColorDEACTIVE(unsigned char _RED, unsigned char _GREEN, unsigned char _BLUE) {
            unsigned char _Buffer4[4] = {0};

            _Buffer4[0] = ChangeColorSOFTWARE_D;
            _Buffer4[1] = _RED;
            _Buffer4[2] = _GREEN;
            _Buffer4[3] = _BLUE;
            SendCommand1_UartSOFTWARE(&_Buffer4[0], 4);
        }

        void IndicatorSensorACTIVE(void) {
            unsigned char _Buffer5[4] = {0};

            _Buffer5[0] = ChangeStatusSOFTWARE_A;
            _Buffer5[1] = 0;
            _Buffer5[2] = 0;
            _Buffer5[3] = 0;
            SendCommand1_UartSOFTWARE(&_Buffer5[0], 4);
        }

        void IndicatorSensorDEACTIVE(void) {
            unsigned char _Buffer6[4] = {0};

            _Buffer6[0] = ChangeStatusSOFTWARE_D;
            _Buffer6[1] = 0;
            _Buffer6[2] = 0;
            _Buffer6[3] = 0;
            SendCommand1_UartSOFTWARE(&_Buffer6[0], 4);
        }



        
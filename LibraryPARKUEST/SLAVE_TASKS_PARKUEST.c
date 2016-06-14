#include <p18cxxx.h>
#include <delays.h>
#include <GenericTypeDefs.h>
#include "PROCESSOR_PARKUEST.h"
#include "TIMER_PARKUEST.h"
#include "SONAR_PARKUEST.h"
#include "COLOR_PARKUEST.h"
#include "ComINDICADOR_PARKUEST.h"
#include "COMMUNICATION_PARKUEST.h"
#include "PWM_PARKUEST.h"
#include "SLAVE_TASKS_PARKUEST.h"

extern FLAGs FLAG;
extern Bus_Data BusSLAVE_T;
extern Bus_Data BusMASTER_T;
extern Bus_Data BusSLAVE_R;
extern Bus_Data BusMASTER_R;
extern COLOR COLORS;
extern ID_PARKUEST IDSlave;
extern ID_PARKUEST IDMaster;
extern BOOL FLAG_TIMER_HIGH;
extern BOOL FLAG_TIMER;
extern unsigned char BufferIndicatorUART[4];

void SLAVE_TASKS(void) {
    ClearWDT();
    if (FLAG.IndicatorINTEGRATED_OnOff == 0) {
        if (FLAG.FlagTimerRemaining3 == 0) {
            FLAG.FlagTimerRemaining3 = TIMER_SEC_Remaining3(10);
            if (FLAG.FlagTimerRemaining3 == 1) {
                if(FLAG.SensorACTIVE == 1){
                    ChangeFadeCOLOR(COLORS.RED_A, COLORS.GREEN_A, COLORS.BLUE_A, 0, 0, 0);
                    PWM1_OFF();
                    PWM2_OFF();
                    PWM4_OFF();
                    TIMER0_OFF();
                    FLAG.IndicatorINTEGRATED_OnOff = 0;
                }else{
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
            }
        }
    }

    Task_UART_Slave(&BusSLAVE_R);
    if (FLAG.NOT_SENSE == 0) {
        PRESENCE_SONAR_4_0(&FLAG.StateSONAR);
        if (FLAG_TIMER_HIGH == 1) {
            FLAG_TIMER_HIGH = 0;
            if (FLAG.FlagTimerRemaining2 == 0) {
                FLAG.FlagTimerRemaining2 = TIMER_SEC_Remaining1(65 + (IDSlave.VAL));
                if (FLAG.FlagTimerRemaining2 == 1) {
                    FLAG.StartCommSLAVE = 1;
                    BusSLAVE_T.IDR = IDMaster.VAL;
                    BusSLAVE_T.IDT1 = IDSlave.VAL;
                    BusSLAVE_T.IDT2 = 0;
                    BusSLAVE_T.CMD = CMD1_PARKUEST;
                    BusSLAVE_T.Data[0].val = (unsigned char)FLAG.SensorACTIVE;
                    BusSLAVE_T.Data[1].val = STOP_COMMUNICATION;
                    BusSLAVE_T.Data[2].val = STOP_COMMUNICATION2;
                    SendDATA1(&BusSLAVE_T);                    
                }
            }
        }
        
        if (FLAG.StateSONAR == 3) {
            if (FLAG.ChangeSTATE == 1 && FLAG.INDICATOR_ACTIVE == 0) {
                FLAG.SensorACTIVE = 1;
                BusSLAVE_T.IDR = IDMaster.VAL;
                BusSLAVE_T.IDT1 = IDSlave.VAL;
                BusSLAVE_T.IDT2 = 0;
                BusSLAVE_T.CMD = CMD1_PARKUEST;
                BusSLAVE_T.Data[0].val = (unsigned char)FLAG.SensorACTIVE;
                BusSLAVE_T.Data[1].val = STOP_COMMUNICATION;
                BusSLAVE_T.Data[2].val = STOP_COMMUNICATION2;
                if(FLAG.StartCommSLAVE == 1) SendDATA1(&BusSLAVE_T);
                SmartOnlyOneIndicator(IDSlave.VAL, (unsigned char) FLAG.SensorACTIVE, ChangeStatusSOFTWARE_A);
                if (FLAG.ChangeSTATE == 1)ChangeFadeCOLOR(COLORS.RED_D, COLORS.GREEN_D, COLORS.BLUE_D, COLORS.RED_A, COLORS.GREEN_A, COLORS.BLUE_A);
                RGB_8bit(COLORS.RED_A, COLORS.GREEN_A, COLORS.BLUE_A);
            }
            FLAG.ChangeSTATE = 0;
            BusSLAVE_R.TimeOut2 = 0;
        } else {
            if (FLAG.ChangeSTATE == 0 && FLAG.INDICATOR_ACTIVE == 0) {
                FLAG.SensorACTIVE = 0;
                BusSLAVE_T.IDR = IDMaster.VAL;
                BusSLAVE_T.IDT1 = IDSlave.VAL;
                BusSLAVE_T.IDT2 = 0;
                BusSLAVE_T.CMD = CMD1_PARKUEST;
                BusSLAVE_T.Data[0].val = (unsigned char)FLAG.SensorACTIVE;
                BusSLAVE_T.Data[1].val = STOP_COMMUNICATION;
                BusSLAVE_T.Data[2].val = STOP_COMMUNICATION2;
                if(FLAG.StartCommSLAVE == 1) SendDATA1(&BusSLAVE_T);
                SmartOnlyOneIndicator(IDSlave.VAL, (unsigned char) FLAG.SensorACTIVE, ChangeStatusSOFTWARE_D);
                if (FLAG.ChangeSTATE == 0)ChangeFadeCOLOR(COLORS.RED_A, COLORS.GREEN_A, COLORS.BLUE_A, COLORS.RED_D, COLORS.GREEN_D, COLORS.BLUE_D);
                RGB_8bit(COLORS.RED_D, COLORS.GREEN_D, COLORS.BLUE_D);
            }
            FLAG.ChangeSTATE = 1;
            BusSLAVE_R.TimeOut1 = 0;
        }
    }
}


































/*******************************************************************************/
//unsigned int Buffer234 = 0;
//
//void SLAVE_TASKS(void) {
//    ClearWDT();
//    Buffer234 = SenseSONAR_3_0();
//    RGB_10bit(Buffer234,0,0);
//}

/******************************************************************************/
//void SLAVE_TASKS(void) {
//    ClearWDT();
//
////    FLAG.StateSONAR = PRESENCE_SONAR_3_0(200);
////    PRESENCE_SONAR1(&FLAG.StateSONAR);
//    PRESENCE_SONAR_4_0(&FLAG.StateSONAR);
//    if (FLAG.StateSONAR == 3) {
//        if (FLAG.ChangeSTATE == 1 && FLAG.INDICATOR_ACTIVE == 0) {
//            FLAG.SensorACTIVE = 1;
//            BusSLAVE_T.IDR = IDMaster.VAL;
//            BusSLAVE_T.IDT1 = IDSlave.VAL;
//            BusSLAVE_T.IDT2 = 0;
//            BusSLAVE_T.CMD = CMD1_PARKUEST;
//            BusSLAVE_T.Data[0].val = (unsigned char)FLAG.SensorACTIVE;
//            BusSLAVE_T.Data[1].val = STOP_COMMUNICATION;
//            BusSLAVE_T.Data[2].val = STOP_COMMUNICATION2;
//            if(FLAG.StartCommSLAVE == 1) SendDATA1(&BusSLAVE_T);
//            SmartOnlyOneIndicator(IDSlave.VAL, (unsigned char) FLAG.SensorACTIVE, ChangeStatusSOFTWARE_A);
//            if (FLAG.ChangeSTATE == 1)ChangeFadeCOLOR(COLORS.RED_D, COLORS.GREEN_D, COLORS.BLUE_D, COLORS.RED_A, COLORS.GREEN_A, COLORS.BLUE_A);
//            RGB_8bit(COLORS.RED_A, COLORS.GREEN_A, COLORS.BLUE_A);
//        }
//        FLAG.ChangeSTATE = 0;
//        BusSLAVE_R.TimeOut2 = 0;
//    } else {
//        if (FLAG.ChangeSTATE == 0 && FLAG.INDICATOR_ACTIVE == 0) {
//            FLAG.SensorACTIVE = 0;
//            BusSLAVE_T.IDR = IDMaster.VAL;
//            BusSLAVE_T.IDT1 = IDSlave.VAL;
//            BusSLAVE_T.IDT2 = 0;
//            BusSLAVE_T.CMD = CMD1_PARKUEST;
//            BusSLAVE_T.Data[0].val = (unsigned char)FLAG.SensorACTIVE;
//            BusSLAVE_T.Data[1].val = STOP_COMMUNICATION;
//            BusSLAVE_T.Data[2].val = STOP_COMMUNICATION2;
//            if(FLAG.StartCommSLAVE == 1) SendDATA1(&BusSLAVE_T);
//            SmartOnlyOneIndicator(IDSlave.VAL, (unsigned char) FLAG.SensorACTIVE, ChangeStatusSOFTWARE_D);
//            if (FLAG.ChangeSTATE == 0)ChangeFadeCOLOR(COLORS.RED_A, COLORS.GREEN_A, COLORS.BLUE_A, COLORS.RED_D, COLORS.GREEN_D, COLORS.BLUE_D);
//            RGB_8bit(COLORS.RED_D, COLORS.GREEN_D, COLORS.BLUE_D);
//        }
//        FLAG.ChangeSTATE = 1;
//        BusSLAVE_R.TimeOut1 = 0;
//    }
//}


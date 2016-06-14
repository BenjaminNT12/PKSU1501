//    HNJ - 98 10
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
#include "MASTER_SLAVE_TASKS_PARKUEST.h"

extern FLAGs FLAG;
extern Bus_Data BusSLAVE_T;
extern Bus_Data BusMASTER_T;
extern Bus_Data BusSLAVE_R;
extern Bus_Data BusMASTER_R;
extern COLOR COLORS;
extern ID_PARKUEST IDSlave;
extern ID_PARKUEST IDMaster;
extern BOOL    FLAG_TIMER_HIGH;
extern unsigned char BufferIndicatorUART[4];

void MASTER_SLAVE_TASKS(void){
    ClearWDT();
    if(FLAG.IndicatorINTEGRATED_OnOff == 0){
        if (FLAG.FlagTimerRemaining3 == 0) {
            FLAG.FlagTimerRemaining3 = TIMER_SEC_Remaining3(10);
            if (FLAG.FlagTimerRemaining3 == 1) {
                if(FLAG.SensorACTIVE == 1){
                    ChangeFadeCOLOR(COLORS.RED_A, COLORS.GREEN_A, COLORS.BLUE_A, 0, 0, 0);
                    PWM1_OFF();
                    PWM2_OFF();
                    PWM4_OFF();
                    FLAG.IndicatorINTEGRATED_OnOff = 0;
                }else{
                    ChangeFadeCOLOR(COLORS.RED_D, COLORS.GREEN_D, COLORS.BLUE_D, 0, 0, 0);
                    PWM1_OFF();
                    PWM2_OFF();
                    PWM4_OFF();
                    FLAG.IndicatorINTEGRATED_OnOff = 0;
                }
                LED_AZUL = 0;
                LED_ROJO = 0;
                LED_VERDE = 0;
            }
        }
    }
    Task_UART_MasterSLAVE(&BusMASTER_R);
    Task_UART_Slave(&BusSLAVE_R);
    if (FLAG.NOT_SENSE == 0) {
        PRESENCE_SONAR_4_0(&FLAG.StateSONAR);
        if (FLAG_TIMER_HIGH == 1) {
            FLAG_TIMER_HIGH = 0;
            if (FLAG.FlagTimerRemaining2 == 0) {
                FLAG.FlagTimerRemaining2 = TIMER_SEC_Remaining1(128 + (2 * IDSlave.VAL));
                if (FLAG.FlagTimerRemaining2 == 1) {
                    FLAG.StartCommMASTER = 1;
                    SLAVEs_INITIALIZATION();
                    FLAG.NumberSLAVEs_REGISTER = CONT_SLAVES_REGISTERED();
                    FLAG.NumberSLAVEs_DISPLAY = (FLAG.NumberSLAVEs_REGISTER - FLAG.NumberSLAVEs_ACTIVES);
                    UsingDisplay(ID_MAIN_SCREEN_1, FLAG.NumberSLAVEs_DISPLAY);
                    Delay10KTCYx(1);
                    Response_Initialization();
                    Delay10KTCYx(40); 
                    FLAG.ContSendPending = 0;
                    FLAG.SENSOR = 0;
                    Send_TABLE();                    
                }
            }
            if (FLAG.SENSOR == 1 && FLAG.StartCommMASTER == 1) {
                if (TIMER_SEC_Remaining2(5) == 1) {
                    FLAG.ContSendPending = 0;
                    FLAG.SENSOR = 0;
                    Send_TABLE();
                }
            }
        }
        if (FLAG.StateSONAR == 3) {
            if (FLAG.ChangeSTATE == 1) {
                FLAG.SensorACTIVE = 1;
                BusSLAVE_R.IDT1 = 1;
                BusSLAVE_R.Data[0].val = 1;
                STATE_OF_SLAVEs();
                FLAG.NumberSLAVEs_ACTIVES = CONT_SLAVE_ACTIVE();
                FLAG.NumberSLAVEs_DISPLAY = (FLAG.NumberSLAVEs_REGISTER - FLAG.NumberSLAVEs_ACTIVES);
                FLAG.SENSOR = 1;
                FLAG.ContSendPending++;
                if (FLAG.ContSendPending == 5 && FLAG.StartCommMASTER == 1) {
                    FLAG.SENSOR = 0;
                    FLAG.ContSendPending = 0;
                    Send_TABLE();
                }
                BusSLAVE_T.IDR = MASTER_ID;
                BusSLAVE_T.IDT1 = 1;
                BusSLAVE_T.IDT2 = 0;
                BusSLAVE_T.CMD = CMD1_PARKUEST;
                BusSLAVE_T.Data[0].val = (unsigned char)FLAG.SensorACTIVE;
                BusSLAVE_T.Data[1].val = STOP_COMMUNICATION;
                BusSLAVE_T.Data[2].val = STOP_COMMUNICATION2;
                SendDATA1(&BusSLAVE_T);
                SmartOnlyOneIndicator(BusSLAVE_T.IDT1, (unsigned char) FLAG.SensorACTIVE, ChangeStatusSOFTWARE_A);
                UsingDisplay(ID_MAIN_SCREEN_1, FLAG.NumberSLAVEs_DISPLAY);
                RGB_8bit(COLORS.RED_A, COLORS.GREEN_A, COLORS.BLUE_A);
            }
            FLAG.ChangeSTATE = 0;
            BusMASTER_R.TimeOut2 = 0;
        } else {
            if (FLAG.ChangeSTATE == 0) {
                FLAG.SensorACTIVE = 0;
                BusSLAVE_R.IDT1 = 1;
                BusSLAVE_R.Data[0].val = 0;
                STATE_OF_SLAVEs();
                FLAG.NumberSLAVEs_ACTIVES = CONT_SLAVE_ACTIVE();
                FLAG.NumberSLAVEs_DISPLAY = (FLAG.NumberSLAVEs_REGISTER - FLAG.NumberSLAVEs_ACTIVES);
                FLAG.SENSOR = 1;
                FLAG.ContSendPending++;
                if (FLAG.ContSendPending == 5 && FLAG.StartCommMASTER == 1) {
                    FLAG.SENSOR = 0;
                    FLAG.ContSendPending = 0;
                    Send_TABLE();
                }
                BusSLAVE_T.IDR = MASTER_ID;
                BusSLAVE_T.IDT1 = 1;
                BusSLAVE_T.IDT2 = 0;
                BusSLAVE_T.CMD = CMD1_PARKUEST;
                BusSLAVE_T.Data[0].val = (unsigned char)FLAG.SensorACTIVE;
                BusSLAVE_T.Data[1].val = STOP_COMMUNICATION;
                BusSLAVE_T.Data[2].val = STOP_COMMUNICATION2;
                SendDATA1(&BusSLAVE_T);
                SmartOnlyOneIndicator(BusSLAVE_T.IDT1, (unsigned char) FLAG.SensorACTIVE, ChangeStatusSOFTWARE_D);
                UsingDisplay(ID_MAIN_SCREEN_1, FLAG.NumberSLAVEs_DISPLAY);
                RGB_8bit(COLORS.RED_D, COLORS.GREEN_D, COLORS.BLUE_D);
            }
            FLAG.ChangeSTATE = 1;
            BusMASTER_R.TimeOut1 = 0;
        }
    }
}
















#include <GenericTypeDefs.h>
#include <p18cxxx.h>
#include <delays.h>
#include <stdarg.h>
#include "PROCESSOR_PARKUEST.h"
#include "UART_PARKUEST.h"
#include "COLOR_PARKUEST.h"
#include "SONAR_PARKUEST.h"
#include "PWM_PARKUEST.h"
#include "TIMER_PARKUEST.h"
#include "COMMUNICATION_PARKUEST.h"
#include "FileSYSTEM_PARKUEST.h"
#include "ComINDICADOR_PARKUEST.h"



#if defined __18F25K22_H || defined __18F24K22_H
extern ID_PARKUEST IDSlave;
extern ID_PARKUEST IDMaster;
extern ID_PARKUEST ID_RECEPCION;
extern FLAGs FLAG;
extern Bus_Data BusSLAVE_R;
extern Bus_Data BusSLAVE_T;
extern COLOR COLORS;
extern SONAR1 SONAR;

extern Val_Data StateSLAVE[SensorNUMBER/8];
extern Val_Data SLAVE_INIT[SensorNUMBER/8];
extern Val_Data DISPLAY_INIT[SensorNUMBER/8];

extern unsigned char BufferIndicatorUART[4];

#if defined PIC18F_MasterSLAVE
    extern Bus_Data BusMASTER_R;
    extern Bus_Data BusMASTER_T;
#endif

#if defined PIC18F_MasterSLAVE || defined PIC18F_SUI
        #if defined ISRHIGH
            void ISRhigh(void);
        #endif
        #ifndef ISRLOW
            void ISRlow (void);
        #endif

        #if defined ISRHIGH
            #pragma code ISR_HIGH_VECTOR = REMAPPED_HIGH_INTERRUPT_VECTOR_ADDRESS
            void ISR_AT_HIGH_VECTOR(void){
                _asm goto ISRhigh _endasm
            }
            #pragma code

            #pragma interrupt ISRhigh
                void ISRhigh(void){
                    unsigned char i = 0;

                    INTCONbits.GIE = 0;

                  #if defined BUS_SLAVE
                    if (PIR1bits.RC1IF) {  // Bus Slave Recepcion
                    #if defined UART1_9bit
                        if(FLAG.MASTERSLAVE_ACTIVE == 1){
                            BusSLAVE_R.IDR = RCREG1;
                            if((BusSLAVE_R.IDR == IDMaster.VAL || BusSLAVE_R.IDR == BROADCAST )){
                                RCSTA1bits.ADDEN1 = 0 ;
                                if( !wait_1(10000) ){RCSTA1bits.ADDEN1 = 1 ;INTCONbits.GIE = 1; return;}
                                BusSLAVE_R.IDT1 = RCREG1;
                                if( !wait_1(10000) ){RCSTA1bits.ADDEN1 = 1 ;INTCONbits.GIE = 1; return;}
                                BusSLAVE_R.IDT2 = RCREG1;
                                if( !wait_1(10000) ){RCSTA1bits.ADDEN1 = 1 ;INTCONbits.GIE = 1; return;}
                                BusSLAVE_R.CMD  = RCREG1;
                                do{
                                    if( !wait_1(10000) ){RCSTA1bits.ADDEN1 = 1 ;INTCONbits.GIE = 1; return;}
                                    BusSLAVE_R.Data[i].val = RCREG1;
                                    i++;
                                    if (BusSLAVE_R.Data[i - 2].val == STOP_COMMUNICATION && BusSLAVE_R.Data[i - 1].val == STOP_COMMUNICATION2) {
                                        break;
                                    }
                                } while (i < 64);
                                if( !wait_1(10000) ){RCSTA1bits.ADDEN1 = 1 ;INTCONbits.GIE = 1; return;}
                                BusSLAVE_R.ChS = RCREG1;
                                BusSLAVE_R.DataReceived = 1;
                                RCSTA1bits.ADDEN1 = 1 ;
                            #if defined PIC18F_MasterSLAVE
    //                            if(FLAG.MASTERSLAVE_ACTIVE==1 && BusSLAVE_R.CMD != CMD2_PARKUEST){Transmission_ConfirmationBUSslave(&BusSLAVE_R,&BusSLAVE_T);}
                            #endif
                            }else{
                                BusSLAVE_R.IDR = 0;
                            }
                        } else if (FLAG.OnlyOneIndicatorActive == 1) {
                            BusSLAVE_R.IDR = RCREG1;
                            if ((BusSLAVE_R.IDR == ID_RECEPCION.VAL || BusSLAVE_R.IDR == BROADCAST || BusSLAVE_R.IDR == IDMaster.VAL)) {
                                RCSTA1bits.ADDEN1 = 0 ;
                                if( !wait_1(10000) ){RCSTA1bits.ADDEN1 = 1 ;INTCONbits.GIE = 1; return;}
                                BusSLAVE_R.IDT1 = RCREG1;
                                if( !wait_1(10000) ){RCSTA1bits.ADDEN1 = 1 ;INTCONbits.GIE = 1; return;}
                                BusSLAVE_R.IDT2 = RCREG1;
                                if( !wait_1(10000) ){RCSTA1bits.ADDEN1 = 1 ;INTCONbits.GIE = 1; return;}
                                BusSLAVE_R.CMD  = RCREG1;
                                do{
                                    if( !wait_1(10000) ){RCSTA1bits.ADDEN1 = 1 ;INTCONbits.GIE = 1; return;}
                                    BusSLAVE_R.Data[i].val = RCREG1;
                                    i++;
                                    if (BusSLAVE_R.Data[i - 2].val == STOP_COMMUNICATION && BusSLAVE_R.Data[i - 1].val == STOP_COMMUNICATION2) {
                                        break;
                                    }
                                } while (i < 64);
                                if( !wait_1(10000) ){RCSTA1bits.ADDEN1 = 1 ;INTCONbits.GIE = 1; return;}
                                BusSLAVE_R.ChS = RCREG1;
                                BusSLAVE_R.DataReceived = 1;
                                RCSTA1bits.ADDEN1 = 1 ;
                            #if defined PIC18F_MasterSLAVE
    //                            if(FLAG.MASTERSLAVE_ACTIVE==1 && BusSLAVE_R.CMD != CMD2_PARKUEST){Transmission_ConfirmationBUSslave(&BusSLAVE_R,&BusSLAVE_T);}
                            #endif
                            }else{
                                BusSLAVE_R.IDR = 0;
                            }
                        }else{
                            BusSLAVE_R.IDR = RCREG1;
                            if (BusSLAVE_R.IDR == ID_RECEPCION.VAL || BusSLAVE_R.IDR == BROADCAST) {
                                RCSTA1bits.ADDEN1 = 0 ;
                                if( !wait_1(10000) ){RCSTA1bits.ADDEN1 = 1 ;INTCONbits.GIE = 1; return;}
                                BusSLAVE_R.IDT1 = RCREG1;
                                if( !wait_1(10000) ){RCSTA1bits.ADDEN1 = 1 ;INTCONbits.GIE = 1; return;}
                                BusSLAVE_R.IDT2 = RCREG1;
                                if( !wait_1(10000) ){RCSTA1bits.ADDEN1 = 1 ;INTCONbits.GIE = 1; return;}
                                BusSLAVE_R.CMD  = RCREG1;
                                do{
                                    if( !wait_1(10000) ){RCSTA1bits.ADDEN1 = 1 ;INTCONbits.GIE = 1; return;}
                                    BusSLAVE_R.Data[i].val = RCREG1;
                                    i++;
                                    if (BusSLAVE_R.Data[i - 2].val == STOP_COMMUNICATION && BusSLAVE_R.Data[i - 1].val == STOP_COMMUNICATION2) {
                                        break;
                                    }
                                } while (i < 64);
                                if( !wait_1(10000) ){RCSTA1bits.ADDEN1 = 1 ;INTCONbits.GIE = 1; return;}
                                BusSLAVE_R.ChS = RCREG1;
                                BusSLAVE_R.DataReceived = 1;
                                RCSTA1bits.ADDEN1 = 1 ;
                            #if defined PIC18F_MasterSLAVE
    //                            if(FLAG.MASTERSLAVE_ACTIVE==1 && BusSLAVE_R.CMD != CMD2_PARKUEST){Transmission_ConfirmationBUSslave(&BusSLAVE_R,&BusSLAVE_T);}
                            #endif
                            }else{
                                BusSLAVE_R.IDR = 0;
                            }                            
                        }
                    #elif defined UART1_8bit
                        BusSLAVE.IDR = RCREG1;
                        if( !wait_1(10) ) return;
                        BusSLAVE.IDT1 = RCREG1;
                        if( !wait_1(10) ) return;
                        BusSLAVE.IDT2 = RCREG1;
                        if( !wait_1(10) ) return;
                        BusSLAVE.CMD = RCREG1;
                        if( !wait_1(10) ) return;
                        BusSLAVE.Data[0].val = RCREG1;
                        if( !wait_1(10) ) return;
                        BusSLAVE.ChS = RCREG1;
                        if( BusSLAVE.IDR == ID.VAL ){ BusSLAVE.DataReceived = 1; }
                    #endif
                    #warning "COMUNICACION PARKUEST V2"
                    }
                #endif

                #if defined BUS_MASTER                
                    if (PIR3bits.RC2IF) { // Bus Master Recepcion
                    #if defined UART2_9bit
                        BusMASTER_R.IDR = RCREG2;
                        if( BusMASTER_R.IDR == ID_RECEPCION.VAL || BusMASTER_R.IDR == BROADCAST){
                            RCSTA2bits.ADDEN2 = 0 ;
                            if( !wait_2(1000) ) {RCSTA2bits.ADDEN2 = 1 ;INTCONbits.GIE = 1; return;}
                            BusMASTER_R.IDT1 = RCREG2;
                            if( !wait_2(1000) ) {RCSTA2bits.ADDEN2 = 1 ;INTCONbits.GIE = 1; return;}
                            BusMASTER_R.IDT2 = RCREG2;
                            if( !wait_2(1000) ) {RCSTA2bits.ADDEN2 = 1 ;INTCONbits.GIE = 1; return;}
                            BusMASTER_R.CMD = RCREG2;
                            i = 0;
                            do{
                                if( !wait_2(1000) ) {RCSTA2bits.ADDEN2 = 1 ;INTCONbits.GIE = 1; return;}
                                BusMASTER_R.Data[i].val = RCREG2;
                                i++;
                                if (BusMASTER_R.Data[i - 2].val == STOP_COMMUNICATION && BusMASTER_R.Data[i - 1].val == STOP_COMMUNICATION2) {
                                    break;
                                }
                            } while (i < 64);
                            if( !wait_2(1000) ) {RCSTA2bits.ADDEN2 = 1 ;INTCONbits.GIE = 1; return;}
                            BusMASTER_R.ChS = RCREG2;
                            BusMASTER_R.DataReceived = 1;
                            RCSTA2bits.ADDEN2 = 1;
                        }else{
                            BusMASTER_R.IDR = 0;
                        }
                    }
                    #elif defined UART2_8bit
                        i=0;
                        BusMASTER_R.IDR = RCREG2;
                        if( BusMASTER_R9.IDR == ID_RECEPCION.VAL || BusMASTER_R.IDR == BROADCAST){
                            RCSTA2bits.ADDEN = 0;
                            if( !wait_2(10) ) return;
                            BusMASTER_R.IDT1 = RCREG2;
                            if( !wait_2(10) ) return;
                            BusMASTER_R.IDT2 = RCREG2;
                            if( !wait_2(10) ) return;
                            BusMASTER_R.CMD = RCREG2;
                            do{
                                if( !wait_2(10) ) return;
                                BusMASTER_R.Data[i].val = RCREG2;
                                i++;
                                if (BusMASTER_R.Data[i - 2].val == STOP_COMMUNICATION && BusMASTER_R.Data[i - 1].val == STOP_COMMUNICATION2) {
                                    break;
                                }
                            } while (i < 64);
                            if( !wait_2(10) ) return;
                            BusMASTER_R.ChS = RCREG2;
                            BusMASTER_R.DataReceived = 1;
                        }else{
                            BusMASTER_R.IDR = 0;
                        }
    //                    if( BusMASTER_R.IDR == ID_RECEPCION.VAL || BusMASTER_R.IDR == BROADCAST ){BusMASTER_R.DataReceived = 1;}
                    #endif
                #endif
                    INTCONbits.GIE = 1;
                    return;
            #warning "Interrupt Service Routine HIGH";
                }
        #endif

        #ifndef ISRLOW
            #pragma code ISR_LOW_VECTOR  = REMAPPED_LOW_INTERRUPT_VECTOR_ADDRESS
            void ISR_AT_LOW_VECTOR (void){
                _asm goto ISRlow _endasm
            }
            #pragma code

            #pragma interruptlow LowPriorityISRCode
            void ISRlow(void){

            }
            #pragma code
        #warning "Interrupt Service Routine LOW";
        #endif

#if defined PIC18F_SUI || defined PIC18F_MasterSLAVE
#if defined COMMUNICATION_V2 || defined COMMUNICATION_V1
        #if defined UART1_9bit
             void SendDATA1(Bus_Data *num_bus){
                 unsigned char i = 0;

                 FLAG.busSLAVE = 1;
                #if defined COMMUNICATION_V1
                    RCSTA1bits.CREN1   = 0;
                    num_bus->ChS=0;
                    TXRX_EN1 = 1;
                        TXSTA1bits.TX9D1 = 1;
                    if(BUS1_free())TXREG1 = num_bus->IDR;
                        while(BUS1_busy());
                        TXSTA1bits.TX9D1 = 0;
                    if(BUS1_free())TXREG1 = num_bus->IDT1;
                        while(BUS1_busy());
                    if(BUS1_free())TXREG1 = num_bus->IDT2;
                        while(BUS1_busy());
                    if(BUS1_free())TXREG1 = num_bus->CMD;
                        while(BUS1_busy());
                    if(BUS1_free())TXREG1 = num_bus->Data->val[0];
                        while(BUS1_busy());
                    if(BUS1_free())TXREG1 = num_bus->Data->val[1];
                        while(BUS1_busy());
                    if(BUS1_free())TXREG1 = num_bus->Data->val[2];
                        while(BUS1_busy());
                    if(BUS1_free())TXREG1 = num_bus->Data->val[3];
                        while(BUS1_busy());
                    if(BUS1_free())TXREG1 = num_bus->Data->val[4];
                        while(BUS1_busy());
                    if(BUS1_free())TXREG1 = num_bus->Data->val[5];
                        while(BUS1_busy());
                    if(BUS1_free())TXREG1 = num_bus->Data->val[6];
                        while(BUS1_busy());
                    if(BUS1_free())TXREG1 = num_bus->Data->val[7];
                        while(BUS1_busy());
                    num_bus->ChS=CALCULATE_ChS(num_bus);
                    if(BUS1_free())TXREG1  = num_bus->ChS;
                        while(BUS1_busy());
                    TXRX_EN1 = 0;
                #elif defined COMMUNICATION_V2
                    num_bus->ChS = 0;
                    num_bus->ChS = CALCULATE_ChS(num_bus);
                    while(!BAUD1CONbits.RCIDL);
                    RCSTA1bits.CREN1 = 0;
                    TXRX_EN1 = 1;
                    if(BUS1_free()){
                            TXSTA1bits.TX9D1 = 1;
                        TXREG1 = num_bus->IDR;
                            while(BUS1_busy());
                        TXSTA1bits.TX9D1 = 0;///// esta linea
                    }
                    if(BUS1_free()){
                        TXREG1 = num_bus->IDT1;
                            while(BUS1_busy());
                    }
                    if(BUS1_free()){
                        TXREG1 = num_bus->IDT2;
                            while(BUS1_busy());
                    }
                    if(BUS1_free()){
                        TXREG1 = num_bus->CMD;
                            while(BUS1_busy());
                    }
                        do{
                            if(BUS1_free()){
                                TXREG1 = num_bus->Data[i].val;
                                    while(BUS1_busy());
                            }
                            i++;
                            if(num_bus->Data[i - 2].val == STOP_COMMUNICATION && num_bus->Data[i - 1].val == STOP_COMMUNICATION2 ){
                                break;
                            }
                        } while ( i < 64);
                    if(BUS1_free()){
                        TXREG1  = num_bus->ChS;
                            while(BUS1_busy());
                    }
                    TXRX_EN1 = 0;
                    FLAG.busSLAVE = 0;
                    RCSTA1bits.CREN1 = 1;
                #endif
            }
            #warning "COMMUNICATION BUS SLAVE";
        #elif defined UART1_8bit
             void SendDATA1(Bus_Data *num_bus){
                #if defined COMMUNICATION_V1
                    INTCONbits.GIE = 0;
                    num_bus->ChS=0;
                    num_bus->ChS=CALCULATE_ChS(num_bus);
                    TXRX_EN1 = 1;
                    if(BUS1_free()){TXREG1 = num_bus->IDR;}
                        while(BUS1_busy());
                    if(BUS1_free()){TXREG1 = num_bus->IDT1;}
                        while(BUS1_busy());
                    if(BUS1_free()){TXREG1 = num_bus->IDT2;}
                        while(BUS1_busy());
                    if(BUS1_free()){TXREG1 = num_bus->CMD;}
                        while(BUS1_busy());
                    if(BUS1_free()){TXREG1 = num_bus->Data[0].val;}
                        while(BUS1_busy());
                    if(BUS1_free()){TXREG1 = num_bus->Data[1].val;}
                        while(BUS1_busy());
                    if(BUS1_free()){TXREG1 = num_bus->Data[2].val;}
                        while(BUS1_busy());
                    if(BUS1_free()){TXREG1 = num_bus->Data[3].val;}
                        while(BUS1_busy());
                    if(BUS1_free()){TXREG1 = num_bus->Data[4].val;}
                        while(BUS1_busy());
                    if(BUS1_free()){TXREG1 = num_bus->Data[5].val;}
                        while(BUS1_busy());
                    if(BUS1_free()){TXREG1 = num_bus->Data[6].val;}
                        while(BUS1_busy());
                    if(BUS1_free()){TXREG1 = num_bus->Data[7].val;}
                        while(BUS1_busy());
                    if(BUS1_free()){TXREG1  = num_bus->ChS;}
                        while(BUS1_busy());
                    TXRX_EN1 = 0;
                    INTCONbits.GIE = 1;
                #elif defined COMMUNICATION_V2
                    num_bus->ChS=0;
                    TXRX_EN1 = 1;
                    if(BUS1_free())TXREG1 = num_bus->IDR;
                        while(BUS1_busy());
                    if(BUS1_free())TXREG1 = num_bus->IDT1;
                        while(BUS1_busy());
                    if(BUS1_free())TXREG1 = num_bus->IDT2;
                        while(BUS1_busy());
                    if(BUS1_free())TXREG1 = num_bus->CMD;
                        while(BUS1_busy());
                    if(BUS1_free())TXREG1 = num_bus->Data[0].val;
                        while(BUS1_busy());
                    num_bus->ChS=CALCULATE_ChS(num_bus);
                    if(BUS1_free())TXREG1  = num_bus->ChS;
                        while(BUS1_busy());
                    TXRX_EN1 = 0;
                #endif
            }
             #warning "COMMUNICATION BUS SLAVE";
        #endif

        #if defined UART2_9bit
            void SendDATA2(Bus_Data *num_bus){
                unsigned char i = 0;

                if(FLAG.StartCommMASTER == 1){
                    FLAG.busMASTER = 1;
                    num_bus->ChS = 0;
                    num_bus->ChS = CALCULATE_ChS(num_bus);
                    while(!BAUD2CONbits.RCIDL);
                    RCSTA2bits.CREN2 = 0;
                    TXRX_EN2 = 1;
                    if (BUS2_free()) {
                            TXSTA2bits.TX9D2 = 1;
                        TXREG2 = num_bus->IDR;
                            while(BUS2_busy());
                            TXSTA2bits.TX9D2 = 0;
                    }
                    if (BUS2_free()) {                            
                        TXREG2 = num_bus->IDT1;
                            while(BUS2_busy());
                    }
                    if (BUS2_free()) {
                        TXREG2 = num_bus->IDT2;
                            while(BUS2_busy());
                    }
                    if (BUS2_free()) {
                        TXREG2 = num_bus->CMD;
                            while(BUS2_busy());
                    }
                    do{
                        if (BUS2_free()) {
                            TXREG2 = num_bus->Data[i].val;
                                while(BUS2_busy());
                        }
                        i++;
                        if(num_bus->Data[i - 2].val == STOP_COMMUNICATION && num_bus->Data[i - 1].val == STOP_COMMUNICATION2 && i < 64){
                            break;
                        }
                    } while ( i < 64);
                    if (BUS2_free()) {
                        TXREG2 = num_bus->ChS;
                        while(BUS2_busy());
                    }
                    TXRX_EN2 = 0;
                    FLAG.busMASTER = 0;
                    RCSTA2bits.CREN2 = 1;
                }
            }

        #elif defined UART2_8bit
            void SendDATA2(Bus_Data *num_bus){

                num_bus->ChS=0;
                TXRX_EN2 = 1;
                    TXSTA2bits.TX9D2 = 1;
                if(BUS2_free())TXREG2 = num_bus->IDR;
                    while(BUS2_busy());
                if(BUS2_free())TXREG2 = num_bus->IDT1;
                    while(BUS2_busy());
                    TXSTA2bits.TX9D2 = 0;
                if(BUS2_free())TXREG2 = num_bus->IDT2;
                    while(BUS2_busy());
                if(BUS2_free())TXREG2 = num_bus->CMD;
                    while(BUS2_busy());
                if(BUS2_free())TXREG2 = num_bus->Data[0].val;
                    while(BUS2_busy());
                num_bus->ChS=CALCULATE_ChS(num_bus);
                if BUS2_free()TXREG2  = num_bus->ChS;
                    while(BUS2_busy());
                TXRX_EN2 = 0;
            }

            #endif
            #warning "COMMUNICATION BUS MASTER";

        unsigned char CALCULATE_ChS(Bus_Data *num_bus){
            unsigned char i=0;
            unsigned char CS=0;

            #if defined PIC18F_SUI
                #if defined COMMUNICATION_V2
                    return (0xFF^(num_bus->IDR+num_bus->IDT1+num_bus->IDT2+num_bus->CMD+num_bus->Data[0].val));
                #elif defined COMMUNICATION_V1
                    return (0xFF^(num_bus->IDR+num_bus->IDT1+num_bus->IDT2+num_bus->CMD+num_bus->Data[0].val
                            +num_bus->Data[1].val+num_bus->Data[2].val+num_bus->Data[3].val+num_bus->Data[4].val
                            +num_bus->Data[5].val+num_bus->Data[6].val+num_bus->Data[7].val));
                #endif
            #elif defined PIC18F_MasterSLAVE
                CS += num_bus->IDR;
                CS += num_bus->IDT1;
                CS += num_bus->IDT2;
                CS += num_bus->CMD;
                for (i = 0; i < 64; i++) {
                    CS += num_bus->Data[i].val;
                    if(num_bus->Data[ i - 1 ].val == STOP_COMMUNICATION && num_bus->Data[i].val == STOP_COMMUNICATION2){
                        break;
                    }
                }
                CS ^= 0xFF;
                return(CS);
            #endif
        }

        BOOL CheckSUM_CORRECT(Bus_Data *num_bus) {
            unsigned char SumDATA = 0;
            unsigned char i = 0;

            num_bus->ChecksumCORRECT = 0;
            SumDATA = num_bus->IDR;
            SumDATA += num_bus->IDT1;
            SumDATA += num_bus->IDT2;
            SumDATA += num_bus->CMD;
            for (i = 0; i < 64; i++) {
                SumDATA += num_bus->Data[i].val;
                if (num_bus->Data[ i - 1 ].val == STOP_COMMUNICATION && num_bus->Data[i].val == STOP_COMMUNICATION2) {
                    break;
                }
            }
            SumDATA += num_bus->ChS;
            if (SumDATA == 0xFF) {
                num_bus->ChecksumCORRECT = 1;
                return (1);
            }
            return (0);
        }

        BOOL CLEAR_BUFFER(unsigned char *_buffer,unsigned char _val,unsigned char _lengh){
            unsigned char i=0;
            for (i = 0; i < _lengh; i++) {
                *_buffer = _val;
                *_buffer++;
            }
        }

//        BOOL Delay_to_SEND(void){
//            while(FLAG.Delay_to_SEND>1){
//                FLAG.Delay_to_SEND--;
//                Delay10TCYx(2*IDSlave.VAL);
//            }
//            FLAG.Ready_to_SEND=1;
//            return(1);
//        }
        
        unsigned char CALCULATE_ID_7bit(void) {
            IDSlave.VAL = 0;
            IDMaster.VAL = MASTER_ID;
            ID_RECEPCION.VAL = 0;
            FLAG.MASTERSLAVE_ACTIVE = 0;
            FLAG.INDICATOR_ACTIVE = 0;
            FLAG.SLAVE_ACTIVE = 0;

            if(DIP_1 == 1)IDSlave.BIT_0 = 1; else IDSlave.BIT_0 = 0;
            if(DIP_2 == 1)IDSlave.BIT_1 = 1; else IDSlave.BIT_1 = 0;
            if(DIP_3 == 1)IDSlave.BIT_2 = 1; else IDSlave.BIT_2 = 0;
            if(DIP_4 == 1)IDSlave.BIT_3 = 1; else IDSlave.BIT_3 = 0;
            if(DIP_5 == 1)IDSlave.BIT_4 = 1; else IDSlave.BIT_4 = 0;
            if(DIP_6 == 1)IDSlave.BIT_5 = 1; else IDSlave.BIT_5 = 0;
            if(DIP_7 == 1)IDSlave.BIT_6 = 1; else IDSlave.BIT_6 = 0;

            IDSlave.VAL &= 0x7F;
            ID_RECEPCION.VAL = IDSlave.VAL ;
            FLAG.SLAVE_ACTIVE = 1;
            FLAG.MASTERSLAVE_ACTIVE = 0;
            FLAG.INDICATOR_ACTIVE = 0;

            if (IDSlave.VAL > 64) {
                if (IDSlave.VAL > 96) {
                    FLAG.SLAVE_ACTIVE = 0;
                    FLAG.MASTERSLAVE_ACTIVE = 0;
                    FLAG.INDICATOR_ACTIVE = 1;
                }else {
                    IDMaster.VAL = 0;
                    IDSlave.VAL &= 0x3F;
                    FLAG.SLAVE_ACTIVE = 0;
                    FLAG.MASTERSLAVE_ACTIVE = 1;
                    FLAG.INDICATOR_ACTIVE = 0;
                    IDMaster.VAL = MASTER_ID;
                    ID_RECEPCION.VAL = IDSlave.VAL;
                }
            }
            return( IDSlave.VAL );
            #warning "ID HARDWARE"
        }
        
        /**
         * unsigned char CALCULATE_ID_SOFTWARE_7bit(unsigned char Master_Slave, unsigned char _ID) 
         * funcion para calcular direcciones de 7 bits
         * 
         * @param Master_Slave tipo de funcion
         * @param _ID id por software
         * @return 
         */
        unsigned char CALCULATE_ID_SOFTWARE_7bit(unsigned char Master_Slave, unsigned char _ID) {
            IDSlave.VAL = 0;
            IDMaster.VAL = MASTER_ID;
            ID_RECEPCION.VAL = 0;
            FLAG.MASTERSLAVE_ACTIVE = 0;
            FLAG.INDICATOR_ACTIVE = 0;
            FLAG.SLAVE_ACTIVE = 0;
            
            IDSlave.VAL = _ID;
            switch(Master_Slave){
                case 56:{
                    FLAG.SLAVE_ACTIVE = 0;
                    FLAG.MASTERSLAVE_ACTIVE = 1;
                    FLAG.INDICATOR_ACTIVE = 0;
                    IDMaster.VAL = 0;
                    IDMaster.VAL = MASTER_ID;
                    ID_RECEPCION.VAL = IDSlave.VAL;
                }break;
                case 57:{
                    IDSlave.VAL &= 0x7F;
                    ID_RECEPCION.VAL = IDSlave.VAL ;
                    FLAG.SLAVE_ACTIVE = 1;
                    FLAG.MASTERSLAVE_ACTIVE = 0;
                    FLAG.INDICATOR_ACTIVE = 0;
                }break;
                case 58:{
                    FLAG.SLAVE_ACTIVE = 0;
                    FLAG.MASTERSLAVE_ACTIVE = 0;
                    FLAG.INDICATOR_ACTIVE = 1;
                }break;
                case 59:{
                    IDSlave.VAL = CALCULATE_ID_7bit();
                }break;
                default:{
                    COLOR_ROUTINE1(blue());
                }break;
            }
            return( IDSlave.VAL );
            #warning "ID SOFTWARE"
        }
        
        
#if defined Address8BIT        
        /**
         * unsigned char CALCULATE_ID_8bit(void) 
         * calcula la direccion por hardware del dispositivo
         * 
         * @return direccion por hardware asignada
         */        
        unsigned char CALCULATE_ID_8bit(void) {
            IDSlave.VAL = 0;
            IDMaster.VAL = MASTER_ID;
            ID_RECEPCION.VAL = 0;
            FLAG.MASTERSLAVE_ACTIVE = 0;
            FLAG.INDICATOR_ACTIVE = 0;
            FLAG.SLAVE_ACTIVE = 0;

            if(DIP_1 == 0)IDSlave.BIT_7 = 1; else IDSlave.BIT_7 = 0;
            if(DIP_2 == 0)IDSlave.BIT_6 = 1; else IDSlave.BIT_6 = 0;
            if(DIP_3 == 0)IDSlave.BIT_5 = 1; else IDSlave.BIT_5 = 0;
            if(DIP_4 == 0)IDSlave.BIT_4 = 1; else IDSlave.BIT_4 = 0;
            if(DIP_5 == 0)IDSlave.BIT_3 = 1; else IDSlave.BIT_3 = 0;
            if(DIP_6 == 0)IDSlave.BIT_2 = 1; else IDSlave.BIT_2 = 0;
            if(DIP_7 == 0)IDSlave.BIT_1 = 1; else IDSlave.BIT_1 = 0;
/** FUNCION PARA DETERMINAR EL FUNCIONAMIENTO DEL DISPOSITIVO**/
            if(DIP_8 == 0)IDSlave.BIT_0 = 1; else IDSlave.BIT_0 = 0;
/** FUNCION PARA DETERMINAR EL FUNCIONAMIENTO DEL DISPOSITIVO**/

            if (IDSlave.VAL == 0) {
                FLAG.INDICATOR_ACTIVE = 1;
                ID_RECEPCION.VAL = 0 ;
                IDMaster.VAL = 0x00;
                IDSlave.VAL &= 0x00;
            } else if (DIP_1 == 0) {
                FLAG.MASTERSLAVE_ACTIVE = 1;
                IDSlave.VAL &= 0x7F;
                ID_RECEPCION.VAL = IDSlave.VAL;
            } else {
                FLAG.SLAVE_ACTIVE = 1;
                IDSlave.VAL &= 0x7F;
                ID_RECEPCION.VAL = IDSlave.VAL;
            }
            
            return( IDSlave.VAL );
            #warning "ID HARDWARE"
        }

        /**
         * unsigned char CALCULATE_ID_SOFTWARE_8bit(unsigned char Master_Slave, unsigned char _ID) 
         * Funcion para asignar direcciones por hardware o software
         * 
         * @param Master_Slave FuncionTYPE
         * @param _ID ID POR SOFTWARE
         * @return 
         */
        unsigned char CALCULATE_ID_SOFTWARE_8bit(unsigned char Master_Slave_TYPE, unsigned char _ID) {
            IDSlave.VAL = 0;
            IDMaster.VAL = MASTER_ID;
            ID_RECEPCION.VAL = 0;
            FLAG.MASTERSLAVE_ACTIVE = 0;
            FLAG.INDICATOR_ACTIVE = 0;
            FLAG.SLAVE_ACTIVE = 0;
            
            IDSlave.VAL = _ID;
            switch (Master_Slave_TYPE) {
                case 56:{
                    FLAG.SLAVE_ACTIVE = 0;
                    FLAG.MASTERSLAVE_ACTIVE = 1;
                    FLAG.INDICATOR_ACTIVE = 0;
                    IDMaster.VAL = 0;
                    IDMaster.VAL = MASTER_ID;
                    ID_RECEPCION.VAL = IDSlave.VAL;
                }break;
                case 57:{
                    IDSlave.VAL &= 0x7F;
                    ID_RECEPCION.VAL = IDSlave.VAL ;
                    FLAG.SLAVE_ACTIVE = 1;
                    FLAG.MASTERSLAVE_ACTIVE = 0;
                    FLAG.INDICATOR_ACTIVE = 0;
                }break;
                case 58:{
                    FLAG.SLAVE_ACTIVE = 0;
                    FLAG.MASTERSLAVE_ACTIVE = 0;
                    FLAG.INDICATOR_ACTIVE = 1;
                }break;
                case 59:{
                    IDSlave.VAL = CALCULATE_ID_8bit();
                }break;
                default:{
                    COLOR_ROUTINE1(blue());
                }break;
            }
            return( IDSlave.VAL );
            #warning "ID SOFTWARE"
        }
#endif 
        #if defined BUS_SLAVE
            unsigned char wait_1(unsigned int wait1){
                unsigned int waiting = 0;

                while( !PIR1bits.RCIF ){
                    if( waiting < wait1 ) waiting++;
                    else {
                        waiting = RCREG1;
                        return 0;
                    }
                }
                return 1;
            }
        #endif
        #if defined BUS_MASTER

            unsigned char wait_2(unsigned int wait2) {
                unsigned int waiting = 0;

                while( !PIR3bits.RC2IF ){
                    if( waiting < wait2 ) waiting++;
                    else {
                        waiting = RCREG2;
                        return 0;
                    }
                }
                return 1;
            }
        #endif

            BOOL Waiting_Initialization(Bus_Data *num_bus) {
                BOOL FlagINIT = 0;
                unsigned int C1 = 0;
                unsigned char C2 = 0;

                do{
                    ClrWdt();
                    if (num_bus->DataReceived == 1) {
                        num_bus->DataReceived = 0;
                        if ((num_bus->IDR == ID_RECEPCION.VAL || num_bus->IDR == BROADCAST) && num_bus->CMD == CMD2_PARKUEST) {
                            num_bus->ChecksumCORRECT = CheckSUM_CORRECT(num_bus);
                            if(num_bus->ChecksumCORRECT == 1){
                                num_bus->ChecksumCORRECT = 0;
                                FlagINIT = 1;
                            }
                        }
                    }
                    C1++;
                    if (C1 == 50000) {
                        C1 = 0;
                        C2++;
                        if(FLAG.MASTERSLAVE_ACTIVE == 1){
                            if (C2 == ID_RECEPCION.VAL + 5) {
                               C2 = 0;
                               Request_Initialization_SLAVE(FLAG.MASTERSLAVE_ACTIVE);
                            }
                        }else {
                            if (C2 == IDSlave.VAL + 11) {
                               C2 = 0;
                               Request_Initialization_SLAVE(FLAG.MASTERSLAVE_ACTIVE);
                            }
                        }
                    }
                }while(FlagINIT == 0);
                return(1);
            }
            
        #if defined PIC18F_MasterSLAVE

            BOOL Waiting_Initialization_PARKUEST(void) {
                if (FLAG.MASTERSLAVE_ACTIVE == 1) {
                    Waiting_Initialization(&BusMASTER_R);
                    return(1);
                }
                else if (FLAG.SLAVE_ACTIVE == 1) {
                    Waiting_Initialization(&BusSLAVE_R);
                    return(1);
                }
                return(0);
            }

        #endif

//            BOOL Waiting_Response(struct Bus_Data *num_bus){
//                unsigned int ContResponse=0;
//                static unsigned char Rcont=0;
//
//                num_bus->StateConfirmation = 0;
//                num_bus->TimeOut1=0;
//                num_bus->TimeOut2=0;
//                 do{
//                    ContResponse++;
//                        if( num_bus->DataReceived == 1 ){
//                            num_bus->DataReceived = 0;
//                            num_bus->ChecksumCORRECT = CheckSUM_CORRECT(num_bus);
//                            if( num_bus->ChecksumCORRECT ==1 ){
//                                if( num_bus->CMD == CMD6_PARKUEST ){
//                                    num_bus->CMD = 0;
//                                    num_bus->StateConfirmation = 1;
//                                    Rcont=0;
//                                    return(1);
//                                }
//                            }
//                        }
//                    }while( num_bus->StateConfirmation!=1 && ContResponse<50000);
//                    Rcont++;
//                    if(Rcont==TIEMPO_ESPERA_RESPUESTA){
//                        Rcont=0;
//                        num_bus->TimeOut1=1;
//                        num_bus->TimeOut2=1;
//                    }
//                return(0);
//            }

        #if defined PIC18F_MasterSLAVE

            BOOL Check_List(Bus_Data *num_bus) { // envia a cada esclavo peticion de estado programado para ser enviada cada 5 minutos
                static unsigned char Slave_num = 0;
                static unsigned int contLIST = 0;

                contLIST++;
                if(contLIST == 2500){
                    contLIST=0;
                    Slave_num++;
                    if(Slave_num <= FLAG.NumberSLAVEs_REGISTER){
                        num_bus->IDR  = Slave_num;
                        num_bus->IDT1 = IDMaster.VAL;
                        num_bus->IDT2 = 0;
                        num_bus->CMD  = CMD3_PARKUEST;
                        num_bus->Data[0].val = 0;
                        num_bus->Data[1].val = STOP_COMMUNICATION;
                        num_bus->Data[2].val = STOP_COMMUNICATION2;
                        SendDATA1(num_bus);
                    }
                }
                if(Slave_num == FLAG.NumberSLAVEs_REGISTER){
                    contLIST = 0;
                    Slave_num = 0;
                    return(0);
                }
                return(1);
            }

            BOOL Check_HEALTH(Bus_Data *num_bus){
                unsigned char i = 0;

                for (i = 0; i < (SensorNUMBER/8); i++) {SLAVE_INIT[i].val = 0;}
                num_bus->IDR  = BROADCAST;
                num_bus->IDT1 = IDMaster.VAL;
                num_bus->IDT2 = 0;
                num_bus->CMD  = CMD2_PARKUEST;
                num_bus->Data[0].val = 0;
                num_bus->Data[1].val = STOP_COMMUNICATION;
                num_bus->Data[2].val = STOP_COMMUNICATION2;
                SendDATA1(num_bus);
                return(0);
            }
            
            void STATE_OF_SLAVEs(void) { // almacenal el estado del sensor en la variable StateSLAVE[x].val
                unsigned char i = 0;
                unsigned char C1 = 0;

                for (i = 0, C1 = 0; i < SensorNUMBER; i = i + 8) {
                    if (BusSLAVE_R.IDT1 > i && BusSLAVE_R.IDT1 <= (i + 8)) {
                        if (BusSLAVE_R.Data[0].val == 1){
                            StateSLAVE[C1].val |= (0x01 << ((BusSLAVE_R.IDT1 - i) - 1));
                        }else {
                            StateSLAVE[C1].val &= (0xFF^(0x01 << ((BusSLAVE_R.IDT1 - i) - 1)));
                        }
                    }
                    C1++;
                }
            }

            void SLAVEs_INITIALIZATION(void) { // almacena los sensores que se inicializan
                unsigned char i = 0;
                unsigned char C1 = 0;

                SLAVE_INIT[0].D1 = 1;
                for (i = 0, C1 = 0; i < SensorNUMBER; i = i + 8, C1++) {
                    if (BusSLAVE_R.IDT1 > i && BusSLAVE_R.IDT1 <= (i + 8)) {
                        SLAVE_INIT[C1].val |= (0x01 << ((BusSLAVE_R.IDT1 - i) - 1));/*************************************/
                    }
                }
            }
//
//            static void DISPLAY_INITIALIZATION(struct Bus_Data *num_bus){ // almacena las pantallas que se inicializan
//                unsigned char i = 0, C1 = 0;
//
//                for (i = 0, C1 = 0; i < SensorNUMBER; i = i + 8, C1++) {
//                    if(num_bus->IDT1>i  && num_bus->IDT1<=(i+8) ){ DISPLAY_INIT[C1].val |= (0x01<<((num_bus->IDT1 - i)-1)); }
//                }
//            }

            unsigned char STATE_SLAVE(unsigned char NUM_slave){ // regresa el estado del numero de esclavo
                unsigned char temp = 0;
                unsigned char C1 = 0;
                unsigned char i = 0;

                for (i = 0, C1 = 0; i < SensorNUMBER; i = i + 8, C1++) {
                    if (NUM_slave > i && NUM_slave <= (i + 8)) {temp = StateSLAVE[C1].val;temp = temp >> ((NUM_slave - i) - 1);temp &= 0x01;}
                }
                return(temp);
            }

            void Data_Migration(Bus_Data *num_bus){ // migra los datos de la variable global al buffer de envio
                unsigned char i = 0;
                
                for (i = 0; i < (SensorNUMBER/8); i++) {
                    num_bus->Data[i].val = StateSLAVE[i].val;
                }
                num_bus->Data[(SensorNUMBER/8)].val = FLAG.NumberSLAVEs_REGISTER;
                num_bus->Data[(SensorNUMBER/8)+1].val = STOP_COMMUNICATION;
                num_bus->Data[(SensorNUMBER/8)+2].val = STOP_COMMUNICATION2;
            }

            void Transmission_ConfirmationBUSslave(Bus_Data *num_bus_R,Bus_Data *num_bus_T){ // envia confiramacion de recepcion

                num_bus_T->IDR  = num_bus_R->IDT1;
                num_bus_T->IDT1 = num_bus_R->IDR;
                num_bus_T->IDT2 = 0;
                num_bus_T->CMD  = CMD6_PARKUEST;
                num_bus_T->Data[0].D1  = 1;
                num_bus_T->Data[1].val = STOP_COMMUNICATION;
                num_bus_T->Data[2].val = STOP_COMMUNICATION2;
                SendDATA1(num_bus_T);
            }

            void Send_TABLE(void){ // envia la tabla de estados de los sensores esclavos del master slave correspondiente
                BusMASTER_T.IDR  = MASTER_ID;          // 0x59 SE ENVIA HACIA EL MASTER_2
                BusMASTER_T.IDT1 = IDSlave.VAL;           // ID CALCULADA
                BusMASTER_T.IDT2 = 0;
                BusMASTER_T.CMD  = CMD1_PARKUEST;
                Data_Migration(&BusMASTER_T);
                SendDATA2(&BusMASTER_T);
            }

            void Send_Initialization(void){ // envia inicializacion

                BusSLAVE_T.IDR  = BROADCAST;  // ENVIA INICIALIZACION A TODOS BROADCAST
                BusSLAVE_T.IDT1 = MASTER_ID;  // ENVIA 0X59 ID MASTER-SLAVE
                BusSLAVE_T.IDT2 = 0;
                BusSLAVE_T.CMD  = CMD2_PARKUEST;
                BusSLAVE_T.Data[0].val = 1;
                BusSLAVE_T.Data[1].val = STOP_COMMUNICATION;
                BusSLAVE_T.Data[2].val = STOP_COMMUNICATION2;
                SendDATA1(&BusSLAVE_T);
                Delay1KTCYx(2);
            }

            void Send_Initialization_Master(void){ // envia inicializacion

                BusMASTER_T.IDR  = BROADCAST;  // ENVIA INICIALIZACION A TODOS BROADCAST
                BusMASTER_T.IDT1 = MASTER_ID;  // ENVIA 0X59 ID MASTER-SLAVE
                BusMASTER_T.IDT2 = 0;
                BusMASTER_T.CMD  = CMD2_PARKUEST;
                BusMASTER_T.Data[0].val = 1;
                BusMASTER_T.Data[1].val = STOP_COMMUNICATION;
                BusMASTER_T.Data[2].val = STOP_COMMUNICATION2;
                SendDATA2(&BusMASTER_T);
                Delay1KTCYx(2);
            }

            void Request_Initialization_SLAVE(BOOL _BUS){
                ChangeFadeCOLOR_FAST(OFF_INDICATOR(),blue());
                ChangeFadeCOLOR_FAST(blue(),OFF_INDICATOR());
                switch(_BUS){
                    case 0:{ // esclavo pide inicializacion
                        BusSLAVE_T.IDR  = MASTER_ID;        // 0x59
                        BusSLAVE_T.IDT1 = IDSlave.VAL;      // ID CALCULADA
                        BusSLAVE_T.IDT2 = 0;
                        BusSLAVE_T.CMD  = CMD7_PARKUEST;
                        BusSLAVE_T.Data[0].val = (unsigned char) FLAG.SensorACTIVE;
                        BusSLAVE_T.Data[1].val = STOP_COMMUNICATION;
                        BusSLAVE_T.Data[2].val = STOP_COMMUNICATION2;
                        SendDATA1(&BusSLAVE_T);
                    }break;
                    case 1:{ // master-slave pide inicializacion
                        BusMASTER_T.IDR  = MASTER_ID;       // 0X59
                        BusMASTER_T.IDT1 = IDSlave.VAL;     // ID CALCULADA
                        BusMASTER_T.IDT2 = 0;
                        BusMASTER_T.CMD  = CMD7_PARKUEST;
                        BusMASTER_T.Data[0].val = (unsigned char) FLAG.SensorACTIVE;
                        BusMASTER_T.Data[1].val = STOP_COMMUNICATION;
                        BusMASTER_T.Data[2].val = STOP_COMMUNICATION2;
                        SendDATA2(&BusMASTER_T);
                    }break;
                }
            }

            void Response_Initialization(void) {
                unsigned char i = 0;
                if (FLAG.SLAVE_ACTIVE == 1) {
                    BusSLAVE_T.IDR = MASTER_ID;
                    BusSLAVE_T.IDT1 = IDSlave.VAL;
                    BusSLAVE_T.IDT2 = 0;
                    BusSLAVE_T.CMD = CMD14_PARKUEST;
                    BusSLAVE_T.Data[0].val = 1;
                    BusSLAVE_T.Data[1].val = STOP_COMMUNICATION;
                    BusSLAVE_T.Data[2].val = STOP_COMMUNICATION2;
                    SendDATA1(&BusSLAVE_T);
                } else if (FLAG.MASTERSLAVE_ACTIVE == 1) {
                    FLAG.NumberSLAVEs_REGISTER = CONT_SLAVES_REGISTERED();
                    BusMASTER_T.IDR = MASTER_ID;
                    BusMASTER_T.IDT1 = IDSlave.VAL;
                    BusMASTER_T.IDT2 = 0;
                    BusMASTER_T.CMD = CMD16_PARKUEST;
                    BusMASTER_T.Data[0].val = 1;
                    BusMASTER_T.Data[1].val = FLAG.NumberSLAVEs_REGISTER;
                    for (i = 0; i < 16; i++) {BusMASTER_T.Data[i + 2].val = SLAVE_INIT[i].val;}
                    BusMASTER_T.Data[i+3].val = STOP_COMMUNICATION;
                    BusMASTER_T.Data[i+4].val = STOP_COMMUNICATION2;
                    SendDATA2(&BusMASTER_T);
                }
            }

            unsigned char BitCont2(unsigned char buffer) {
                unsigned char i = 0;
                unsigned char k = 0;

                k = 0;
                for (i = 0; i < 8; i++) {
                    if ((buffer & 0x01) == 0x01) k++;
                    buffer = buffer >> 1;
                }
                return(k);
            }

            unsigned char CONT_SLAVES_REGISTERED(void){
                unsigned char i = 0;
                unsigned char TempCont = 0;

                for (i = 0; i < (SensorNUMBER / 8); i++) {TempCont += BitCont2(SLAVE_INIT[i].val);}
                return(TempCont);
            }

            unsigned char CONT_SLAVE_ACTIVE(void){
                unsigned char i = 0;
                unsigned char TempCont = 0;

                for (i = 0; i < (SensorNUMBER/8); i++) {TempCont += BitCont2(StateSLAVE[i].val);}
                return(TempCont);
            }

            BOOL DelayedStartMaster(unsigned char _Delayed){
                unsigned char i = 0;

                for (i = 0; i < _Delayed; i++) Delay10KTCYx(50);
                return (1);
            }

            BOOL DelayedStart(unsigned char _Delayed){
                unsigned char i = 0;

                for (i = 0; i < _Delayed; i++) Delay10KTCYx(200);
                return (1);
            }

            void Task_UART_MasterSLAVE(Bus_Data *num_bus){           // tareas del bus master-slave
                if(num_bus->DataReceived == 1){
                    num_bus->DataReceived = 0;
                    num_bus->ChecksumCORRECT = CheckSUM_CORRECT(num_bus);
                    if(num_bus->ChecksumCORRECT == 1){
                        num_bus->ChecksumCORRECT = 0;
                        switch(num_bus->CMD){
                            case CMD2_PARKUEST:{                            // comando para inicializar verificar la salud y disponibilidad de cada dispositivo
                                Response_Initialization();
                            }break;
                            case CMD3_PARKUEST:{ // el master principal pide el estado del algun sensor y este lo devuelve
                                BusMASTER_T.IDR  = MASTER_ID; // id de master principal
                                BusMASTER_T.IDT1 = IDSlave.VAL; // envia el ID del master-slave
                                BusMASTER_T.IDT2 = BusMASTER_R.IDT2; // id del numero de sensor que se desea obtener el estado
                                BusMASTER_T.CMD  = CMD1_PARKUEST; // se envia con el comando princiapal de actualizacion de estado
                                BusMASTER_T.Data[0].val = STATE_SLAVE(BusMASTER_R.IDT2);  // regresa el estado del sensor que se desea
                                BusMASTER_T.Data[1].val = STOP_COMMUNICATION; // stop de comunicacion
                                BusMASTER_T.Data[2].val = STOP_COMMUNICATION2; // stop de comunicacion
                                SendDATA2(&BusMASTER_T);  // lo envia hacia el bus del master pricnipal
//                                Waiting_Response(&BusMASTER_R); // espera respuesta
                            }break;
                            case CMD4_PARKUEST:{ // comando de bus MASTER el master ´principal debe enviar este comando para que el master-slave le envie la tabla de estado de todos los sensores
                                Send_TABLE();   // envia la tabla de estados
                            }break;
                            case CMD8_PARKUEST:{ // comando de bus MASTER comando para actualizar los colores del sensor cuando esta ACTIVO
                                BusSLAVE_T.IDR  = BusMASTER_R.IDT2;
                                BusSLAVE_T.IDT1 = MASTER_ID;
                                BusSLAVE_T.IDT2 = 0;
                                BusSLAVE_T.CMD  = CMD8_PARKUEST;
                                BusSLAVE_T.Data[0].val = BusMASTER_R.Data[0].val;
                                BusSLAVE_T.Data[1].val = BusMASTER_R.Data[1].val;
                                BusSLAVE_T.Data[2].val = BusMASTER_R.Data[2].val;
                                BusSLAVE_T.Data[3].val = STOP_COMMUNICATION;
                                BusSLAVE_T.Data[4].val = STOP_COMMUNICATION2;
                                if(BusMASTER_R.IDT2 != 0x01){
                                    if(BusMASTER_R.IDT2 == BROADCAST){
                                        COLORS.RED_A   = BusMASTER_R.Data[0].val; // actualiza el color rojo
                                        COLORS.GREEN_A = BusMASTER_R.Data[1].val; // actualiza el color verde
                                        COLORS.BLUE_A  = BusMASTER_R.Data[2].val; // actualiza el color azul
                                        if (FLAG.StateSONAR == 3) {
                                            RGB_8bit(COLORS.RED_A, COLORS.GREEN_A, COLORS.BLUE_A);
                                        }
//                                        IndicatorColorACTIVE(BusMASTER_R.Data[0].val,BusMASTER_R.Data[1].val,BusMASTER_R.Data[2].val);
                                        BufferIndicatorUART[0] = ChangeColorSOFTWARE_A;
                                        BufferIndicatorUART[1] = BusMASTER_R.Data[0].val;
                                        BufferIndicatorUART[2] = BusMASTER_R.Data[1].val;
                                        BufferIndicatorUART[3] = BusMASTER_R.Data[2].val;
                                        SendCommand1_UartSOFTWARE(&BufferIndicatorUART[0],4);
                                    }
                                    SendDATA1(&BusSLAVE_T);
                                }
                                else{
                                    COLORS.RED_A   = BusMASTER_R.Data[0].val; // actualiza el color rojo
                                    COLORS.GREEN_A = BusMASTER_R.Data[1].val; // actualiza el color verde
                                    COLORS.BLUE_A  = BusMASTER_R.Data[2].val; // actualiza el colo azul
                                    if (FLAG.StateSONAR == 3) {
                                        RGB_8bit(COLORS.RED_A, COLORS.GREEN_A, COLORS.BLUE_A);
                                    }
//                                    IndicatorColorACTIVE(BusMASTER_R.Data[0].val,BusMASTER_R.Data[1].val,BusMASTER_R.Data[2].val);
                                    BufferIndicatorUART[0] = ChangeColorSOFTWARE_A;
                                    BufferIndicatorUART[1] = BusMASTER_R.Data[0].val;
                                    BufferIndicatorUART[2] = BusMASTER_R.Data[1].val;
                                    BufferIndicatorUART[3] = BusMASTER_R.Data[2].val;
                                    SendCommand1_UartSOFTWARE(&BufferIndicatorUART[0],4);
                                    BusMASTER_R.CMD = 0;
                                }
                                WriteColorsPARKUEST(&COLORS);
                            }break;
                            case CMD9_PARKUEST:{ // comando de bus MASTER comando para actualizar los colores del sensor cuando esta DESACTIVADO
                                BusSLAVE_T.IDR  = BusMASTER_R.IDT2;
                                BusSLAVE_T.IDT1 = MASTER_ID;
                                BusSLAVE_T.IDT2 = 0;
                                BusSLAVE_T.CMD  = CMD9_PARKUEST;
                                BusSLAVE_T.Data[0].val = BusMASTER_R.Data[0].val;
                                BusSLAVE_T.Data[1].val = BusMASTER_R.Data[1].val;
                                BusSLAVE_T.Data[2].val = BusMASTER_R.Data[2].val;
                                BusSLAVE_T.Data[3].val = STOP_COMMUNICATION;
                                BusSLAVE_T.Data[4].val = STOP_COMMUNICATION2;
                                if(BusMASTER_R.IDT2 != 0x01 ){
                                    if(BusMASTER_R.IDT2 == BROADCAST){
                                        COLORS.RED_D   = BusMASTER_R.Data[0].val; // actualiza el color rojo
                                        COLORS.GREEN_D = BusMASTER_R.Data[1].val; // actualiza el color verde
                                        COLORS.BLUE_D  = BusMASTER_R.Data[2].val; // actualiza el color azul
                                        if (FLAG.StateSONAR != 3) {
                                            RGB_8bit(COLORS.RED_D, COLORS.GREEN_D, COLORS.BLUE_D);
                                        }
//                                        IndicatorColorDEACTIVE(BusMASTER_R.Data[0].val,BusMASTER_R.Data[1].val,BusMASTER_R.Data[2].val);
                                        BufferIndicatorUART[0] = ChangeColorSOFTWARE_D;
                                        BufferIndicatorUART[1] = BusMASTER_R.Data[0].val;
                                        BufferIndicatorUART[2] = BusMASTER_R.Data[1].val;
                                        BufferIndicatorUART[3] = BusMASTER_R.Data[2].val;
                                        SendCommand1_UartSOFTWARE(&BufferIndicatorUART[0],4);
                                    }
                                    SendDATA1(&BusSLAVE_T);
                                }
                                else{
                                    COLORS.RED_D   = BusMASTER_R.Data[0].val; // actualiza el color rojo
                                    COLORS.GREEN_D = BusMASTER_R.Data[1].val; // actualiza el color verde
                                    COLORS.BLUE_D  = BusMASTER_R.Data[2].val; // actualiza el color azul
                                    BusMASTER_R.CMD = 0;
                                    if (FLAG.StateSONAR != 3) {
                                        RGB_8bit(COLORS.RED_D, COLORS.GREEN_D, COLORS.BLUE_D);
                                    }
//                                    IndicatorColorDEACTIVE(BusMASTER_R.Data[0].val,BusMASTER_R.Data[1].val,BusMASTER_R.Data[2].val);
                                    BufferIndicatorUART[0] = ChangeColorSOFTWARE_D;
                                    BufferIndicatorUART[1] = BusMASTER_R.Data[0].val;
                                    BufferIndicatorUART[2] = BusMASTER_R.Data[1].val;
                                    BufferIndicatorUART[3] = BusMASTER_R.Data[2].val;
                                    SendCommand1_UartSOFTWARE(&BufferIndicatorUART[0],4);
                                }
                                WriteColorsPARKUEST(&COLORS);
                            }break;
                            case CMD10_PARKUEST:{ // comando de bus MASTER tipo de secuencia para el sensor cuando esta activo
                                ;
                            }break;
                            case CMD11_PARKUEST:{ // comando de bus MASTER tipo de secuencia cuando esta desactivado
                                ;
                            }break;
                            case CMD12_PARKUEST:{ // actuliza la distancia de sensado minimo despues del autoajuste
                                BusSLAVE_T.IDR  = BusMASTER_R.IDT2;
                                BusSLAVE_T.IDT1 = MASTER_ID;
                                BusSLAVE_T.IDT2 = 0;
                                BusSLAVE_T.CMD  = CMD12_PARKUEST;
                                BusSLAVE_T.Data[0].val = BusMASTER_R.Data[0].val;
                                BusSLAVE_T.Data[1].val = BusMASTER_R.Data[1].val;
                                BusSLAVE_T.Data[2].val = STOP_COMMUNICATION;
                                BusSLAVE_T.Data[3].val = STOP_COMMUNICATION2;
                                if(BusMASTER_R.IDT2 != 0x01 ){
                                    if(BusMASTER_R.IDT2 == BROADCAST){
                                        SONAR.SensingDistance = DISTANCE(BusMASTER_R.Data[0].val,BusMASTER_R.Data[1].val);
                                    }
                                    SendDATA1(&BusSLAVE_T);
                                }
                                else{
                                    SONAR.SensingDistance = DISTANCE(BusMASTER_R.Data[0].val,BusMASTER_R.Data[1].val);
                                    BusMASTER_R.CMD = 0;
                                }
                                WriteDistancePARKUEST(&SONAR);
                            }break;
                            case CMD13_PARKUEST:{ // manda la instruccion para que haga el autoajuste de sensado
                                BusSLAVE_T.IDR  = BusMASTER_R.IDT2;
                                BusSLAVE_T.IDT1 = MASTER_ID;
                                BusSLAVE_T.IDT2 = 0;
                                BusSLAVE_T.CMD  = CMD13_PARKUEST;
                                BusSLAVE_T.Data[0].val = 0;
                                BusSLAVE_T.Data[1].val = STOP_COMMUNICATION;
                                BusSLAVE_T.Data[2].val = STOP_COMMUNICATION2;
                                if(BusMASTER_R.IDT2 != 0x01 ){
                                    if(BusMASTER_R.IDT2 == BROADCAST){
                                        SONAR.SensingDistance = AutoSetting();
                                    }
                                    SendDATA1(&BusSLAVE_T);
                                }
                                else{
                                    SONAR.SensingDistance = AutoSetting();
                                    BusMASTER_R.CMD = 0;
                                }
                                WriteDistancePARKUEST(&SONAR);
                            }break;
                            case CMD15_PARKUEST:{ // modificar la velocidad de la rutina
                                BusSLAVE_T.IDR  = BusMASTER_R.IDT2;
                                BusSLAVE_T.IDT1 = BusMASTER_R.IDT1;
                                BusSLAVE_T.IDT2 = 0;
                                BusSLAVE_T.CMD  = CMD15_PARKUEST;
                                BusSLAVE_T.Data[0].val = BusMASTER_R.Data[0].val;
                                BusSLAVE_T.Data[1].val = STOP_COMMUNICATION;
                                BusSLAVE_T.Data[2].val = STOP_COMMUNICATION2;
                                if(BusMASTER_R.IDT2 != 0x01){
                                    SendDATA1(&BusSLAVE_T);
                                }else{
                                    COLORS.SPEED = BusMASTER_R.Data[0].val;
                                }
                            }break;
                            case CMD17_PARKUEST:{ // inicializacion de la pantalla
                                FLAG.Number_DISPLAY = ID_MAIN_SCREEN_1;
                            }break;
                            case CMD18_PARKUEST:{ // verifica la salud de los esclavos
                                Check_HEALTH(&BusSLAVE_T);
                            }break;
                            case CMD20_PARKUEST:{ // cambio de id de esclavo
                                BusSLAVE_T.IDR  = BusMASTER_R.IDT2;
                                BusSLAVE_T.IDT1 = MASTER_ID;
                                BusSLAVE_T.IDT2 = 0;
                                BusSLAVE_T.CMD  = CMD20_PARKUEST;
                                BusSLAVE_T.Data[0].val = BusMASTER_R.Data[0].val;
                                BusSLAVE_T.Data[1].val = STOP_COMMUNICATION;
                                BusSLAVE_T.Data[2].val = STOP_COMMUNICATION2;
                                if(BusMASTER_R.IDT2 != 0x01 ){
                                    if(BusMASTER_R.IDT2 == BROADCAST){
                                        IDSlave.VAL = BusMASTER_R.Data[0].val;
                                    }
                                    SendDATA1(&BusSLAVE_T);
                                }
                                else{
                                    IDSlave.VAL = BusMASTER_R.Data[0].val;
                                }
                                WriteIdPARKUEST(&IDSlave.VAL);
                                BusMASTER_R.CMD = 0;
                            }break;
                            case CMD21_PARKUEST:{ // Reset Id Hardware
                                BusSLAVE_T.IDR  = BusMASTER_R.IDT2;
                                BusSLAVE_T.IDT1 = MASTER_ID;
                                BusSLAVE_T.IDT2 = 0;
                                BusSLAVE_T.CMD  = CMD21_PARKUEST;
                                BusSLAVE_T.Data[0].val = BusMASTER_R.Data[0].val;
                                BusSLAVE_T.Data[1].val = STOP_COMMUNICATION;
                                BusSLAVE_T.Data[2].val = STOP_COMMUNICATION2;
                                if(BusMASTER_R.IDT2 != 0x01 ){
                                    if(BusMASTER_R.IDT2 == BROADCAST){
                                        IDSlave.VAL = CALCULATE_ID_SOFTWARE_7bit(HardwareFUNCTION,5);
                                        WriteIdHardwarePARKUEST(&IDSlave.VAL); // si el id por hardware cambio escribir el utlimo id por hardware
                                        WriteIdPARKUEST(&IDSlave.VAL); // si el id por hardware cambio escribir el utlimo id por software
                                    }
                                    SendDATA1(&BusSLAVE_T);
                                }
                                else{
                                    IDSlave.VAL = CALCULATE_ID_SOFTWARE_7bit(HardwareFUNCTION,5);
                                    WriteIdHardwarePARKUEST(&IDSlave.VAL); // si el id por hardware cambio escribir el utlimo id por hardware
                                    WriteIdPARKUEST(&IDSlave.VAL); // si el id por hardware cambio escribir el utlimo id por software
                                }
                                BusMASTER_R.CMD = 0;
                            }break;
                            case CMD22_PARKUEST:{ // APAGA EL INDICADOR INTEGRADO
                                BusSLAVE_T.IDR  = BusMASTER_R.IDT2;
                                BusSLAVE_T.IDT1 = MASTER_ID;
                                BusSLAVE_T.IDT2 = 0;
                                BusSLAVE_T.CMD  = CMD22_PARKUEST;
                                BusSLAVE_T.Data[0].val = BusMASTER_R.Data[0].val;
                                BusSLAVE_T.Data[1].val = STOP_COMMUNICATION;
                                BusSLAVE_T.Data[2].val = STOP_COMMUNICATION2;
                                if(BusMASTER_R.IDT2 != 0x01 ){
                                    if(BusMASTER_R.IDT2 == BROADCAST) {
                                        if(FLAG.StateSONAR != 3){
                                            ChangeFadeCOLOR(COLORS.RED_D, COLORS.GREEN_D, COLORS.BLUE_D, OFF_INDICATOR());
                                        }else{
                                            ChangeFadeCOLOR(COLORS.RED_A, COLORS.GREEN_A, COLORS.BLUE_A, OFF_INDICATOR());
                                        }
                                        PWM1_OFF();
                                        PWM2_OFF();
                                        PWM4_OFF();
                                        FLAG.IndicatorINTEGRATED_OnOff = 0;
                                        WriteIndicatorOnOff(FLAG.IndicatorINTEGRATED_OnOff);
                                    }
                                    SendDATA1(&BusSLAVE_T);
                                }
                                else {
                                    if(FLAG.StateSONAR != 3){
                                        ChangeFadeCOLOR(COLORS.RED_D, COLORS.GREEN_D, COLORS.BLUE_D, OFF_INDICATOR());
                                    }else{
                                        ChangeFadeCOLOR(COLORS.RED_A, COLORS.GREEN_A, COLORS.BLUE_A, OFF_INDICATOR());
                                    }
                                    PWM1_OFF();
                                    PWM2_OFF();
                                    PWM4_OFF();
                                    FLAG.IndicatorINTEGRATED_OnOff = 0;
                                    WriteIndicatorOnOff(FLAG.IndicatorINTEGRATED_OnOff);
                                }
                                BusMASTER_R.CMD = 0;
                            }break;
                            case CMD23_PARKUEST:{ // ENCIENDE EL INDICADOR INTEGRADO
                                BusSLAVE_T.IDR  = BusMASTER_R.IDT2;
                                BusSLAVE_T.IDT1 = MASTER_ID;
                                BusSLAVE_T.IDT2 = 0;
                                BusSLAVE_T.CMD  = CMD23_PARKUEST;
                                BusSLAVE_T.Data[0].val = BusMASTER_R.Data[0].val;
                                BusSLAVE_T.Data[1].val = STOP_COMMUNICATION;
                                BusSLAVE_T.Data[2].val = STOP_COMMUNICATION2;
                                if(BusMASTER_R.IDT2 != 0x01 ){
                                    if(BusMASTER_R.IDT2 == BROADCAST){
                                        PWM1_ON();
                                        PWM2_ON();
                                        PWM4_ON();
                                        TIMER0_ON();
                                        if(FLAG.StateSONAR != 3){
                                            ChangeFadeCOLOR(OFF_INDICATOR(), COLORS.RED_D, COLORS.GREEN_D, COLORS.BLUE_D);
                                        }else{
                                            ChangeFadeCOLOR(OFF_INDICATOR(), COLORS.RED_A, COLORS.GREEN_A, COLORS.BLUE_A);
                                        }
                                        FLAG.IndicatorINTEGRATED_OnOff = 1;
                                        WriteIndicatorOnOff(FLAG.IndicatorINTEGRATED_OnOff);
                                    }
                                    SendDATA1(&BusSLAVE_T);
                                }
                                else{
                                    PWM1_ON();
                                    PWM2_ON();
                                    PWM4_ON();
                                    TIMER0_ON();
                                    if(FLAG.StateSONAR != 3){
                                        ChangeFadeCOLOR(OFF_INDICATOR(), COLORS.RED_D, COLORS.GREEN_D, COLORS.BLUE_D);
                                    }else{
                                        ChangeFadeCOLOR(OFF_INDICATOR(), COLORS.RED_A, COLORS.GREEN_A, COLORS.BLUE_A);
                                    }
                                    FLAG.IndicatorINTEGRATED_OnOff = 1;
                                    WriteIndicatorOnOff(FLAG.IndicatorINTEGRATED_OnOff);
                                }
                                BusMASTER_R.CMD = 0;
                            }break;
                            case CMD24_PARKUEST:{
                                unsigned char i346534 = 0;
                                unsigned char C1761 = 0;
                                
                                BusSLAVE_T.IDR  = BusMASTER_R.IDT2;
                                BusSLAVE_T.IDT1 = MASTER_ID;
                                BusSLAVE_T.IDT2 = 0;
                                BusSLAVE_T.CMD  = CMD24_PARKUEST;
                                do{
                                    BusSLAVE_T.Data[i346534].val = BusMASTER_R.Data[i346534].val;
                                    i346534++;
                                    if (BusMASTER_R.Data[i346534 - 2].val == STOP_COMMUNICATION && BusMASTER_R.Data[i346534 - 1].val == STOP_COMMUNICATION2) break;
                                } while (i346534 < 64);
                                
                                if(BusMASTER_R.IDT2 != 0x01 ){
                                    SendDATA1(&BusSLAVE_T);
                                }else{
                                    for (C1761 = 0; C1761 < 64; C1761++) {
                                        if (BusMASTER_R.Data[C1761].val == STOP_COMMUNICATION && BusMASTER_R.Data[C1761 + 1].val == STOP_COMMUNICATION2) {
                                            break;
                                        }else if(BusMASTER_R.Data[C1761].val != 0){
                                            FLAG.OnlyOneIndicatorActive = 1;
                                            SaveInBits(&FLAG.OnlyOneIndicatorSENSORES[0],BusMASTER_R.Data[C1761].val, 0x01);
                                        }
                                    }
                                    SaveInBits(&FLAG.OnlyOneIndicatorSENSORES[0],1, 0x01);
                                    WriteOnlyOneIndicatorIDs(&FLAG.OnlyOneIndicatorSENSORES[0]);
                                }
                            }break;
                            case CMD25_PARKUEST:{
                                unsigned char i346534 = 0;
                                unsigned char C17346 = 0;
                                unsigned  char C3546 = 0;
                                unsigned int Sum4564 = 0;
                                
                                BusSLAVE_T.IDR  = BusMASTER_R.IDT2;
                                BusSLAVE_T.IDT1 = MASTER_ID;
                                BusSLAVE_T.IDT2 = 0;
                                BusSLAVE_T.CMD  = CMD25_PARKUEST;
                                do{
                                    BusSLAVE_T.Data[i346534].val = BusMASTER_R.Data[i346534].val;
                                    i346534++;
                                    if (BusMASTER_R.Data[i346534 - 2].val == STOP_COMMUNICATION && BusMASTER_R.Data[i346534 - 1].val == STOP_COMMUNICATION2) break;
                                } while (i346534 < 64);
                                
                                if(BusMASTER_R.IDT2 != 0x01 ){
                                    SendDATA1(&BusSLAVE_T);
                                }else{
                                    for (C17346 = 0; C17346 < 64; C17346++) {
                                        if (BusMASTER_R.Data[C17346].val == STOP_COMMUNICATION && BusMASTER_R.Data[C17346 + 1].val == STOP_COMMUNICATION2) {
                                            break;
                                        }else if(BusMASTER_R.Data[C17346].val != 0){
                                            SaveInBits(&FLAG.OnlyOneIndicatorDATA[0],BusMASTER_R.Data[C17346].val, 0);
                                            SaveInBits(&FLAG.OnlyOneIndicatorSENSORES[0],BusMASTER_R.Data[C17346].val, 0);
                                        }
                                    }
                                    for (C3546 = 0; C3546 < 16; C3546++) Sum4564 += FLAG.OnlyOneIndicatorSENSORES[C3546];
                                    if (Sum4564 == 0 || Sum4564 == 1) FLAG.OnlyOneIndicatorActive = 0;
                                    WriteOnlyOneIndicatorIDs(&FLAG.OnlyOneIndicatorSENSORES[0]);
                                }
                            }break;
                            case CMD_REESTART_SYSTEM_PARKUEST:{
                                BusSLAVE_T.IDR  = BusMASTER_R.IDT2;
                                BusSLAVE_T.IDT1 = MASTER_ID;
                                BusSLAVE_T.IDT2 = 0;
                                BusSLAVE_T.CMD  = CMD_REESTART_SYSTEM_PARKUEST;
                                BusSLAVE_T.Data[0].val = BusMASTER_R.Data[0].val;
                                BusSLAVE_T.Data[1].val = STOP_COMMUNICATION;
                                BusSLAVE_T.Data[2].val = STOP_COMMUNICATION2;
                                if(BusMASTER_R.IDT2 != 0x01 ){
                                    SendDATA1(&BusSLAVE_T);
                                    if(BusMASTER_R.IDT2 == BROADCAST){
                                        BLUE_DUTY(1020);
                                        Delay10KTCYx(200);
                                        BLUE_DUTY(0);
                                        RESET_PROCESSOR();
                                    }
                                }
                                else{
                                    BLUE_DUTY(1020);
                                    Delay10KTCYx(200);
                                    BLUE_DUTY(0);
                                    RESET_PROCESSOR();
                                }
                            }break;
                            case CMD_ONLY_ROUTINE_PARKUEST:{
                                BusSLAVE_T.IDR  = BusMASTER_R.IDT2;
                                BusSLAVE_T.IDT1 = MASTER_ID;
                                BusSLAVE_T.IDT2 = 0;
                                BusSLAVE_T.CMD  = CMD_ONLY_ROUTINE_PARKUEST;
                                BusSLAVE_T.Data[0].val = BusMASTER_R.Data[0].val;
                                BusSLAVE_T.Data[1].val = STOP_COMMUNICATION;
                                BusSLAVE_T.Data[2].val = STOP_COMMUNICATION2;
                                if(BusMASTER_R.IDT2 != 0x01 ){
                                    SendDATA1(&BusSLAVE_T);
                                    if(BusMASTER_R.IDT2 == BROADCAST){
                                        while(BusMASTER_R.CMD == CMD_ONLY_ROUTINE_PARKUEST)COLOR_ROUTINE3(COLORS.RED_D,COLORS.GREEN_D,COLORS.BLUE_D);
                                    }
                                }
                                else{
                                    while(BusMASTER_R.CMD == CMD_ONLY_ROUTINE_PARKUEST)COLOR_ROUTINE3(COLORS.RED_D,COLORS.GREEN_D,COLORS.BLUE_D);
                                }
                            }break;
                            case CMD_ONLY_SENSE_PARKUEST:{
                                BusSLAVE_T.IDR  = BusMASTER_R.IDT2;
                                BusSLAVE_T.IDT1 = MASTER_ID;
                                BusSLAVE_T.IDT2 = 0;
                                BusSLAVE_T.CMD  = CMD_ONLY_SENSE_PARKUEST;
                                BusSLAVE_T.Data[0].val = BusMASTER_R.Data[0].val;
                                BusSLAVE_T.Data[1].val = STOP_COMMUNICATION;
                                BusSLAVE_T.Data[2].val = STOP_COMMUNICATION2;
                                if(BusMASTER_R.IDT2 != 0x01 ){
                                    SendDATA1(&BusSLAVE_T);
                                    if(BusMASTER_R.IDT2 == BROADCAST){
                                        BLUE_DUTY(0);
                                        RED_DUTY(0);
                                        GREEN_DUTY(0);
                                        PWM1_OFF();
                                        PWM2_OFF();
                                        PWM4_OFF();
                                        LED_AZUL = 0;
                                        LED_ROJO = 0;
                                        LED_VERDE = 0;
                                    }
                                }
                                else{
                                    BLUE_DUTY(0);
                                    RED_DUTY(0);
                                    GREEN_DUTY(0);
                                    PWM1_OFF();
                                    PWM2_OFF();
                                    PWM4_OFF();
                                    LED_AZUL = 0;
                                    LED_ROJO = 0;
                                    LED_VERDE = 0;
                                }
                            }break;
                            case CMD_STOP_SYSTEM_PARKUEST:{
                                BusSLAVE_T.IDR  = BusMASTER_R.IDT2;
                                BusSLAVE_T.IDT1 = MASTER_ID;
                                BusSLAVE_T.IDT2 = 0;
                                BusSLAVE_T.CMD  = CMD_STOP_SYSTEM_PARKUEST;
                                BusSLAVE_T.Data[0].val = BusMASTER_R.Data[0].val;
                                BusSLAVE_T.Data[1].val = STOP_COMMUNICATION;
                                BusSLAVE_T.Data[2].val = STOP_COMMUNICATION2;
                                if(BusMASTER_R.IDT2 != 0x01 ){
                                    SendDATA1(&BusSLAVE_T);
                                    if(BusMASTER_R.IDT2 == BROADCAST){
                                        BLUE_DUTY(0);
                                        GREEN_DUTY(0);
                                        RED_DUTY(0);
                                        SLEEP_PROCESSOR();
                                    }
                                }
                                else{
                                    BLUE_DUTY(0);
                                    GREEN_DUTY(0);
                                    RED_DUTY(0);
                                    SLEEP_PROCESSOR();
                                }
                            }break;
                            case CMD_TEMPORARY_STOP_SYSTEM_PARKUEST:{
                                BusSLAVE_T.IDR  = BusMASTER_R.IDT2;
                                BusSLAVE_T.IDT1 = MASTER_ID;
                                BusSLAVE_T.IDT2 = 0;
                                BusSLAVE_T.CMD  = CMD_TEMPORARY_STOP_SYSTEM_PARKUEST;
                                BusSLAVE_T.Data[0].val = BusMASTER_R.Data[0].val;
                                BusSLAVE_T.Data[1].val = STOP_COMMUNICATION;
                                BusSLAVE_T.Data[2].val = STOP_COMMUNICATION2;
                                if(BusMASTER_R.IDT2 != 0x01 ){
                                    SendDATA1(&BusSLAVE_T);
                                    if(BusMASTER_R.IDT2 == BROADCAST){
                                        BufferIndicatorUART[0] = OffINDICATOR;
                                        BufferIndicatorUART[1] = 0;
                                        BufferIndicatorUART[2] = 0;
                                        BufferIndicatorUART[3] = 0;
                                        SendCommand1_UartSOFTWARE(&BufferIndicatorUART[0],4);
                                        if(FLAG.StateSONAR != 3){
                                            ChangeFadeCOLOR(COLORS.RED_D, COLORS.GREEN_D, COLORS.BLUE_D, OFF_INDICATOR());
                                        }else{
                                            ChangeFadeCOLOR(COLORS.RED_A, COLORS.GREEN_A, COLORS.BLUE_A, OFF_INDICATOR());
                                        }
                                        PWM1_OFF();
                                        PWM2_OFF();
                                        PWM4_OFF();
                                        TIMER0_OFF();
                                        FLAG.NOT_SENSE = 1;
                                    }
                                }
                                else{
                                    BufferIndicatorUART[0] = OffINDICATOR;
                                    BufferIndicatorUART[1] = 0;
                                    BufferIndicatorUART[2] = 0;
                                    BufferIndicatorUART[3] = 0;
                                    SendCommand1_UartSOFTWARE(&BufferIndicatorUART[0], 4);
                                    if (FLAG.StateSONAR != 3) {
                                        ChangeFadeCOLOR(COLORS.RED_D, COLORS.GREEN_D, COLORS.BLUE_D, OFF_INDICATOR());
                                    }else{
                                        ChangeFadeCOLOR(COLORS.RED_A, COLORS.GREEN_A, COLORS.BLUE_A, OFF_INDICATOR());
                                    }
                                    PWM1_OFF();
                                    PWM2_OFF();
                                    PWM4_OFF();
                                    TIMER0_OFF();
                                    FLAG.NOT_SENSE = 1;
                                }
                            }break;
                            case CMD_ReSTART:{
                                BusSLAVE_T.IDR  = BusMASTER_R.IDT2;
                                BusSLAVE_T.IDT1 = MASTER_ID;
                                BusSLAVE_T.IDT2 = 0;
                                BusSLAVE_T.CMD  = CMD_ReSTART;
                                BusSLAVE_T.Data[0].val = BusMASTER_R.Data[0].val;
                                BusSLAVE_T.Data[1].val = STOP_COMMUNICATION;
                                BusSLAVE_T.Data[2].val = STOP_COMMUNICATION2;
                                if(BusMASTER_R.IDT2 != 0x01 ){
                                    SendDATA1(&BusSLAVE_T);
                                    if(BusMASTER_R.IDT2 == BROADCAST){
                                        BufferIndicatorUART[0] = OnINDICATOR;
                                        BufferIndicatorUART[1] = 0;
                                        BufferIndicatorUART[2] = 0;
                                        BufferIndicatorUART[3] = 0;
                                        SendCommand1_UartSOFTWARE(&BufferIndicatorUART[0],4);
                                        PWM1_ON();
                                        PWM2_ON();
                                        PWM4_ON();
                                        TIMER0_ON();
                                        ChangeFadeCOLOR(0, 0, 0, COLORS.RED_D, COLORS.GREEN_D, COLORS.BLUE_D);
                                        FLAG.NOT_SENSE = 0;
                                        FLAG.ChangeSTATE = 1;
                                        FLAG.StateSONAR = 0;
                                        FLAG.FlagTimerRemaining3 = 0;
                                    }
                                }
                                else{
                                    BufferIndicatorUART[0] = OnINDICATOR;
                                    BufferIndicatorUART[1] = 0;
                                    BufferIndicatorUART[2] = 0;
                                    BufferIndicatorUART[3] = 0;
                                    SendCommand1_UartSOFTWARE(&BufferIndicatorUART[0],4);
                                    PWM1_ON();
                                    PWM2_ON();
                                    PWM4_ON();
                                    TIMER0_ON();
                                    ChangeFadeCOLOR(OFF_INDICATOR(), COLORS.RED_D, COLORS.GREEN_D, COLORS.BLUE_D);
                                    FLAG.NOT_SENSE = 0;
                                    FLAG.ChangeSTATE = 1;
                                    FLAG.StateSONAR = 0;
                                    FLAG.FlagTimerRemaining3 = 0;
                                }
                            }break;
                        }
                    }
                    num_bus->IDR  = 0;
                    num_bus->IDT1 = 0;
                    num_bus->IDT1 = 0;
                    num_bus->CMD  = 0;
                    CLEAR_BUFFER(&num_bus->Data[0].val,0,64);
                    num_bus->ChS  = 0;
                }
            }

            void Send_DISPLAY_BusSlave(unsigned char address,unsigned int buffer){
                UINT16_VAL tem_ = 0;
                
                tem_.Val = buffer;
                
                BusSLAVE_T.IDR  = address;
                BusSLAVE_T.IDT1 = MASTER_ID;
                BusSLAVE_T.IDT2 = 0;
                BusSLAVE_T.CMD  = CMD5_PARKUEST;
                BusSLAVE_T.Data[0].val = tem_.v[1];
                BusSLAVE_T.Data[1].val = tem_.v[0];
                BusSLAVE_T.Data[2].val = STOP_COMMUNICATION;
                BusSLAVE_T.Data[3].val = STOP_COMMUNICATION2;
                SendDATA1(&BusSLAVE_T);
            }

            void Send_DISPLAY_BusMaster(unsigned char address,unsigned int buffer){
                UINT16_VAL tem_ = 0;
                
                tem_.Val = buffer;
                
                BusMASTER_T.IDR  = address;
                BusMASTER_T.IDT1 = MASTER_ID;
                BusMASTER_T.IDT2 = 0;
                BusMASTER_T.CMD  = CMD5_PARKUEST;
                BusMASTER_T.Data[0].val = tem_.v[1];
                BusMASTER_T.Data[1].val = tem_.v[0];
                BusMASTER_T.Data[2].val = STOP_COMMUNICATION;
                BusMASTER_T.Data[3].val = STOP_COMMUNICATION2;
                SendDATA2(&BusMASTER_T);
            }

            void Task_UART_Slave(Bus_Data *num_bus){
 
                if(num_bus->DataReceived == 1){
                    num_bus->DataReceived = 0;
                    num_bus->ChecksumCORRECT = CheckSUM_CORRECT(num_bus);
                    if(num_bus->ChecksumCORRECT == 1){
                        num_bus->ChecksumCORRECT = 0;
                        switch(num_bus->CMD){
                            case CMD1_PARKUEST:{ // actualiza la matriz de estados del sensor y lo envia hacia el master principal
                                if (FLAG.MASTERSLAVE_ACTIVE == 1) {
                                    if (FLAG.OnlyOneIndicatorActive == 1)SmartOnlyOneIndicator(BusSLAVE_R.IDT1, BusSLAVE_R.Data[0].val, 0);
                                    FLAG.ContSendPending++;
                                    STATE_OF_SLAVEs();
                                    FLAG.NumberSLAVEs_ACTIVES = CONT_SLAVE_ACTIVE();
                                    FLAG.SENSOR = 1;
                                    if(FLAG.ContSendPending == 5){
                                        FLAG.SENSOR = 0;
                                        FLAG.ContSendPending = 0;
                                        Send_TABLE();
                                    }
                                    FLAG.NumberSLAVEs_DISPLAY = (FLAG.NumberSLAVEs_REGISTER - FLAG.NumberSLAVEs_ACTIVES);
                                    UsingDisplay(ID_MAIN_SCREEN_1,FLAG.NumberSLAVEs_DISPLAY); //"ATENCION" SE DEBE ESPECIFICAR SOBRE QUE BUS ESTA TRABAJANDO LA PANTALLA /**// PANTALLA LOCAL
                                }else if(FLAG.SLAVE_ACTIVE == 1 && FLAG.OnlyOneIndicatorActive == 1){                                
                                    SmartOnlyOneIndicator(BusSLAVE_R.IDT1, BusSLAVE_R.Data[0].val, 0);
                                }
                            }break;
                            case CMD2_PARKUEST:{ // comando para inicializar verificar la salud y disponibilidad de cada dispositivo
                                DelayedStart(IDSlave.VAL);
                                Response_Initialization();
                            }break;
                            case CMD7_PARKUEST:{ // peticion de inicializacion por parte de un esclavo
                                
                                if (FLAG.MASTERSLAVE_ACTIVE == 1) {
                                    BusSLAVE_T.IDR  = BusSLAVE_R.IDT1;  // ENVIA INICIALIZACION A TODOS BROADCAST
                                    BusSLAVE_T.IDT1 = MASTER_ID;  // ENVIA 0X59 ID MASTER-SLAVE
                                    BusSLAVE_T.IDT2 = 0;
                                    BusSLAVE_T.CMD  = CMD2_PARKUEST;
                                    BusSLAVE_T.Data[0].val = 1;
                                    BusSLAVE_T.Data[1].val = STOP_COMMUNICATION;
                                    BusSLAVE_T.Data[2].val = STOP_COMMUNICATION2;
                                    SendDATA1(&BusSLAVE_T);
                                }
                            }break;
                            case CMD8_PARKUEST:{ // ACTUALIZACION DE COLORES PARA SENSOR ACTIVO
                                COLORS.RED_A   = BusSLAVE_R.Data[0].val; // actualizacion del color rojo para el esclavo ACTIVO
                                COLORS.GREEN_A = BusSLAVE_R.Data[1].val; // actualizacion del color verde para el esclavo ACTIVO
                                COLORS.BLUE_A  = BusSLAVE_R.Data[2].val; // actualizacion del color azul para el esclavo ACTIVO
                                if(FLAG.StateSONAR == 3){
                                    RGB_8bit(COLORS.RED_A,COLORS.GREEN_A,COLORS.BLUE_A);
                                }
                                WriteColorsPARKUEST(&COLORS);
//                                IndicatorColorACTIVE(BusSLAVE_R.Data[0].val,BusSLAVE_R.Data[1].val,BusSLAVE_R.Data[2].val);
                                BufferIndicatorUART[0] = ChangeColorSOFTWARE_A;
                                BufferIndicatorUART[1] = BusSLAVE_R.Data[0].val;
                                BufferIndicatorUART[2] = BusSLAVE_R.Data[1].val;
                                BufferIndicatorUART[3] = BusSLAVE_R.Data[2].val;
                                SendCommand1_UartSOFTWARE(&BufferIndicatorUART[0],4);
                            }break;
                            case CMD9_PARKUEST:{ // ACTUALIZACION DE COLORES PARA SENSOR DESACTIVADO
                                COLORS.RED_D   = BusSLAVE_R.Data[0].val; // actualizacion del color rojo para el esclavo DESACTIVADO
                                COLORS.GREEN_D = BusSLAVE_R.Data[1].val; // actualizacion del color verde para el esclavo DESACTIVADO
                                COLORS.BLUE_D  = BusSLAVE_R.Data[2].val; // actualizacion del color azul para el esclavo DESACTIVADO
                                if(FLAG.StateSONAR != 3){
                                    RGB_8bit(COLORS.RED_D,COLORS.GREEN_D,COLORS.BLUE_D);
                                }
                                WriteColorsPARKUEST(&COLORS);
//                                IndicatorColorDEACTIVE(BusSLAVE_R.Data[0].val,BusSLAVE_R.Data[1].val,BusSLAVE_R.Data[2].val);
                                BufferIndicatorUART[0] = ChangeColorSOFTWARE_D;
                                BufferIndicatorUART[1] = BusSLAVE_R.Data[0].val;
                                BufferIndicatorUART[2] = BusSLAVE_R.Data[1].val;
                                BufferIndicatorUART[3] = BusSLAVE_R.Data[2].val;
                                SendCommand1_UartSOFTWARE(&BufferIndicatorUART[0],4);
                            }break;
                            case CMD10_PARKUEST:{ // tipo de secuncia para sensor ACTIVO
                                ;
                            }break;
                            case CMD11_PARKUEST:{ // tipo de secuncia para sensor DESACTIVADO
                                ;
                            }break;
                            case CMD12_PARKUEST:{ // actuliza la distancia de sensado minimo despues del autoajuste
                                SONAR.SensingDistance = DISTANCE(BusSLAVE_R.Data[0].val,BusSLAVE_R.Data[1].val);
                                WriteDistancePARKUEST(&SONAR);
                            }break;
                            case CMD13_PARKUEST:{ // manda la instruccion para que haga el autoajuste de sensado
                                SONAR.SensingDistance = AutoSetting();
                                WriteDistancePARKUEST(&SONAR);
                            }break;
                            case CMD14_PARKUEST:{ //el master-slave recibe este comando para actualizar el numero de esclavos para ser mostrados en la pantalla
                                
                                if (FLAG.MASTERSLAVE_ACTIVE == 1) {
                                    SLAVEs_INITIALIZATION(); // almacena el numero de esclavos inicializados
                                    FLAG.NumberSLAVEs_REGISTER = CONT_SLAVES_REGISTERED();  // devuelve el numero de esclavos inicializados
                                }
                            }break;
                            case CMD15_PARKUEST:{ // modificar la velocidad de la rutina
                                COLORS.SPEED = BusSLAVE_R.Data[0].val;
                            }break;
                            case CMD17_PARKUEST:{ // inicializacion de la pantalla
                                FLAG.Number_DISPLAY = ID_MAIN_SCREEN_1;
                            }break;
                            case CMD20_PARKUEST:{ // CAMBIO DE ID DE SLAVE
                                IDSlave.VAL = BusSLAVE_R.Data[0].val;
                                WriteIdPARKUEST(&IDSlave.VAL);
                            }break;
                            case CMD21_PARKUEST:{ // RESET DE ID HARDWARE
                                IDSlave.VAL = CALCULATE_ID_SOFTWARE_7bit(HardwareFUNCTION,5);
                                WriteIdHardwarePARKUEST(&IDSlave.VAL); // si el id por hardware cambio escribir el utlimo id por hardware
                                WriteIdPARKUEST(&IDSlave.VAL); // si el id por hardware cambio escribir el utlimo id por software
                            }break;
                            case CMD22_PARKUEST:{ // APAGA EL INDICADOR INTEGRADO
                                if(FLAG.StateSONAR != 3){
                                    ChangeFadeCOLOR(COLORS.RED_D, COLORS.GREEN_D, COLORS.BLUE_D, OFF_INDICATOR());
                                }else{
                                    ChangeFadeCOLOR(COLORS.RED_A, COLORS.GREEN_A, COLORS.BLUE_A, OFF_INDICATOR());
                                }
                                PWM1_OFF();
                                PWM2_OFF();
                                PWM4_OFF();
                                TIMER0_OFF();
                                LED_AZUL = 0;
                                LED_ROJO = 0;
                                LED_VERDE = 0;
                                FLAG.IndicatorINTEGRATED_OnOff = 0;
                                WriteIndicatorOnOff(FLAG.IndicatorINTEGRATED_OnOff);
                                BusMASTER_R.CMD = 0;
                            }break;
                            case CMD23_PARKUEST:{ // ENCIENDE EL INDICADOR INTEGRADO
                                PWM1_ON();
                                PWM2_ON();
                                PWM4_ON();
                                TIMER0_ON();
                                if(FLAG.StateSONAR != 3){
                                    ChangeFadeCOLOR(OFF_INDICATOR(), COLORS.RED_D, COLORS.GREEN_D, COLORS.BLUE_D);
                                }else{
                                    ChangeFadeCOLOR(OFF_INDICATOR(), COLORS.RED_A, COLORS.GREEN_A, COLORS.BLUE_A);
                                }
                                FLAG.IndicatorINTEGRATED_OnOff = 1;
                                WriteIndicatorOnOff(FLAG.IndicatorINTEGRATED_OnOff);
                                BusMASTER_R.CMD = 0;
                            }break;
                            case CMD24_PARKUEST:{
                                unsigned char I45646 = 0;
                                
                                for (I45646 = 0; I45646 < 64; I45646++) {
                                    if (BusSLAVE_R.Data[I45646].val == STOP_COMMUNICATION && BusSLAVE_R.Data[I45646 + 1].val == STOP_COMMUNICATION2) {
                                        break;
                                    }else if(BusSLAVE_R.Data[I45646].val != 0){
                                        FLAG.OnlyOneIndicatorActive = 1;
                                        SaveInBits(&FLAG.OnlyOneIndicatorSENSORES[0],BusSLAVE_R.Data[I45646].val, 0x01);
                                    }
                                }
                                SaveInBits(&FLAG.OnlyOneIndicatorSENSORES[0],IDSlave.VAL, 0x01);
                                WriteOnlyOneIndicatorIDs(&FLAG.OnlyOneIndicatorSENSORES[0]);                                
                            }break;
                            case CMD25_PARKUEST:{
                                unsigned char i57657 = 0;
                                unsigned char SUM4564 = 0;
                                 
                                for (i57657 = 0; i57657 < 64; i57657++) {
                                    if (BusSLAVE_R.Data[i57657].val == STOP_COMMUNICATION && BusSLAVE_R.Data[i57657 + 1].val == STOP_COMMUNICATION2) {
                                        break;
                                    }else if(BusSLAVE_R.Data[i57657].val != 0){
                                        SaveInBits(&FLAG.OnlyOneIndicatorDATA[0], BusSLAVE_R.Data[i57657].val, 0);
                                        SaveInBits(&FLAG.OnlyOneIndicatorSENSORES[0], BusSLAVE_R.Data[i57657].val, 0);
                                    }
                                }
                                
                                for (i57657 = 0; i57657 < 16; i57657++) {SUM4564 += BitCont2(FLAG.OnlyOneIndicatorSENSORES[i57657]);}
                                if(SUM4564 == 1){
                                    FLAG.OnlyOneIndicatorActive = 0;
                                    SaveInBits(&FLAG.OnlyOneIndicatorDATA[0], IDSlave.VAL, 0);
                                    SaveInBits(&FLAG.OnlyOneIndicatorSENSORES[0], IDSlave.VAL, 0);
                                }
                                WriteOnlyOneIndicatorIDs(&FLAG.OnlyOneIndicatorSENSORES[0]);                                
                            }break;
                            case CMD_REESTART_SYSTEM_PARKUEST:{ // reinicia el procesador
                                RESET_PROCESSOR();
                            }break;
                            case CMD_ONLY_ROUTINE_PARKUEST:{ // deja solo la rutina del indicador
                                while (BusSLAVE_R.CMD == CMD_ONLY_ROUTINE_PARKUEST) {
                                    COLOR_ROUTINE3(COLORS.RED_D,COLORS.GREEN_D,COLORS.BLUE_D);
                                }
                            }break;
                            case CMD_ONLY_SENSE_PARKUEST:{ // unicamente se permite el sensador
                                BLUE_DUTY(0);
                                RED_DUTY(0);
                                GREEN_DUTY(0);
                                PWM1_OFF();
                                PWM2_OFF();
                                PWM4_OFF();
                                LED_AZUL = 0;
                                LED_ROJO = 0;
                                LED_VERDE = 0;
                            }break;
                            case CMD_STOP_SYSTEM_PARKUEST:{ // dtiene todo el sistema
                                BLUE_DUTY(0);
                                GREEN_DUTY(0);
                                RED_DUTY(0);
                                SLEEP_PROCESSOR();
                            }break;
                            case CMD_TEMPORARY_STOP_SYSTEM_PARKUEST:{ // detiene todo el sitema pemporalmente
                                if(FLAG.StateSONAR != 3){
                                    ChangeFadeCOLOR(COLORS.RED_D, COLORS.GREEN_D, COLORS.BLUE_D, OFF_INDICATOR());
                                }else{
                                    ChangeFadeCOLOR(COLORS.RED_A, COLORS.GREEN_A, COLORS.BLUE_A, OFF_INDICATOR());
                                }
                                PWM1_OFF();
                                PWM2_OFF();
                                PWM4_OFF();
                                TIMER0_OFF();
                                BufferIndicatorUART[0] = OffINDICATOR;
                                BufferIndicatorUART[1] = 0;
                                BufferIndicatorUART[2] = 0;
                                BufferIndicatorUART[3] = 0;
                                SendCommand1_UartSOFTWARE(&BufferIndicatorUART[0],4);
                                FLAG.NOT_SENSE = 1;
                                LED_AZUL = 0;
                                LED_ROJO = 0;
                                LED_VERDE = 0;
                            }break;
                            case CMD_ReSTART:{ // REINICIA EL SISTEMA NO EL PROCESADOR
                                PWM1_ON();
                                PWM2_ON();
                                PWM4_ON();
                                TIMER0_ON();
                                BufferIndicatorUART[0] = OnINDICATOR;
                                BufferIndicatorUART[1] = 0;
                                BufferIndicatorUART[2] = 0;
                                BufferIndicatorUART[3] = 0;
                                SendCommand1_UartSOFTWARE(&BufferIndicatorUART[0],4);
                                ChangeFadeCOLOR(OFF_INDICATOR(), COLORS.RED_D, COLORS.GREEN_D, COLORS.BLUE_D);
                                FLAG.NOT_SENSE = 0;
                                FLAG.ChangeSTATE = 1;
                                FLAG.StateSONAR = 0;
                                FLAG.FlagTimerRemaining3 = 0;
                            }break;
                        }
                    }
                    num_bus->IDR  = 0;
                    num_bus->IDT1 = 0;
                    num_bus->IDT1 = 0;
                    num_bus->CMD  = 0;
                    CLEAR_BUFFER(&num_bus->Data[0].val,0,64);
                    num_bus->ChS  = 0;
                }
            }

            void TEST_COMUNICACION (void){
                BusSLAVE_T.IDR  = IDMaster.VAL;
                BusSLAVE_T.IDT1 = IDSlave.VAL;
                BusSLAVE_T.IDT2 = 0;
                BusSLAVE_T.CMD  = CMD1_PARKUEST;
                BusSLAVE_T.Data[0].val = FLAG.SensorACTIVE;
                BusSLAVE_T.Data[1].val = STOP_COMMUNICATION;
                BusSLAVE_T.Data[2].val = STOP_COMMUNICATION2;
                SendDATA1(&BusSLAVE_T);
            }

            void test_reception(void) {
                unsigned char i = 0;
                if (BusMASTER_R.DataReceived == 1) {
                    BusMASTER_R.DataReceived = 0;
                    BusMASTER_R.ChecksumCORRECT = CheckSUM_CORRECT(&BusMASTER_R);
                    if (BusMASTER_R.ChecksumCORRECT == 1) {
                        BusMASTER_R.ChecksumCORRECT = 0;
                        for (i = 0; i < BusMASTER_R.IDT1; i++) {
                            RED_DUTY(1020);
                            Delay1KTCYx(50);
                            RED_DUTY(0);
                            Delay1KTCYx(50);
                        }
                    }
                }
            }

            void SaveInBits(unsigned char *Storage, unsigned char Position, unsigned char StateBit) {
                unsigned char i = 0;
                unsigned char C1 = 0;
                unsigned char _temp = 0;

                _temp = Position;
                for (i = 0; i < SensorNUMBER; i = i + 8) {
                    if (Position > i && Position <= (i + 8)) {
                        if (StateBit == 1) {
                            Storage[C1] |= ((unsigned char)0x01 << ((_temp - i) - 1));
                        } else {
                            Storage[C1]  &= (0xFF^((unsigned char)0x01 << ((_temp - i) - 1)));
                        }
                        return;
                    }
                    C1++;
                }
                return;
            }

            unsigned char LoadState(unsigned char *Storage, unsigned char Position) {
                unsigned char temp = 0;
                unsigned char i = 0;
                unsigned char C1 = 0;

                for (i = 0, C1 = 0; i < SensorNUMBER; i = i + 8) {
                    if (Position > i && Position <= (i + 8)) {
                        temp = Storage[C1];
                        temp = temp >> ((Position - i) - 1);
                        temp &= 0x01;
                        break;
                    }
                     C1++;
                }
                return (temp);
            }

            void OnlyOneIndicatorIdSensors(unsigned char NumberOfArg, ...) {
                unsigned char temp1 = 0;
                BOOL F98 = 0;
                va_list PointerPos;
                
                if(NumberOfArg != 0){
                    va_start(PointerPos,NumberOfArg); // numero de argumentos
                        while (NumberOfArg--){ // hace un while para el numero de argumentos que tiene la funcion while 
                            temp1 = va_arg(PointerPos, unsigned char); // almacena el valor del argumento
                            if (temp1 != 0) {
                                SaveInBits(&FLAG.OnlyOneIndicatorSENSORES[0], temp1, 0x01); // almacena en bits los sensores que se van a evaluar
                                if(F98 == 0){
                                    F98 = 1;
                                    SaveInBits(&FLAG.OnlyOneIndicatorSENSORES[0], IDSlave.VAL, 0x01); // almacena en bits los sensores que se van a evaluar 
                                }
                                temp1 = 0;  // resetea la variable
                                FLAG.OnlyOneIndicatorActive = 1;
                            }
                        } 
                    va_end(PointerPos);
                }else{
                    FLAG.OnlyOneIndicatorActive = 0;
                }
            }
            
            unsigned char OnlyOneIndicator(unsigned char NumberOfSensor, unsigned char State) {
                unsigned char i = 0;
                unsigned char contador = 0;
                BOOL FLAG917 = 1;
                
                if (LoadState(&FLAG.OnlyOneIndicatorSENSORES[0], NumberOfSensor) == 1 && FLAG.OnlyOneIndicatorActive == 1) {
                    SaveInBits(&FLAG.OnlyOneIndicatorDATA[0], NumberOfSensor, State);
                    for (i = 0; i < 16; i++) {
                        if (FLAG.OnlyOneIndicatorSENSORES[i] != 0) {
                            if (FLAG.OnlyOneIndicatorSENSORES[i] == FLAG.OnlyOneIndicatorDATA[i]) {
                                if(FLAG917 == 1){
                                    FLAG917 = 1;
                                }
                            }else{
                                FLAG917 = 0;
                            }
                            contador++;
                        }
                    }
                    if (FLAG917 == 1){
                        return(1);
                    }else{
                        return(0);
                    }
                }else{
                    return(0);
                }
            }

            void ResetVariables(void) {
                unsigned char i = 0;

                FLAG.OnlyOneIndicatorActive = 0;
                FLAG.SLAVE_ACTIVE = 0;
                FLAG.MASTERSLAVE_ACTIVE = 0;
                FLAG.INDICATOR_ACTIVE = 0;
                FLAG.busMASTER = 0;
                FLAG.StartCommMASTER = 0;
                FLAG.StartCommSLAVE = 0;
                FLAG.busSLAVE = 0;
                FLAG.ChangeSTATE = 0;
                FLAG.SensorACTIVE = 0;
                FLAG.FlagTimerRemaining1 = 0;
                FLAG.FlagTimerRemaining2 = 0;
                FLAG.FlagTimerRemaining3 = 0;
                FLAG.FlagTimerRemaining4 = 0;
                FLAG.SENSOR = 0;
                FLAG.NOT_SENSE = 0;
                FLAG.IndicatorINTEGRATED_OnOff = 0;
                FLAG.StateSONAR = 0;
                FLAG.ContSendPending = 0;
                FLAG.NumberSLAVEs_REGISTER = 1; /*las especificaciones requieren 1 sensor registrado como minimo*/
                FLAG.NumberSLAVEs_ACTIVES = 0;
                FLAG.NumberSLAVEs_DISPLAY = 0;
                FLAG.Number_DISPLAY = 0;
                for (i = 0; i < 16; i++) {
                    FLAG.OnlyOneIndicatorDATA[i] = 0;
                    FLAG.OnlyOneIndicatorSENSORES[i] = 0;
                }
                COLORS.BLUE_A = 0;
                COLORS.BLUE_D = 0;
                COLORS.GREEN_A = 0;
                COLORS.GREEN_D = 0;
                COLORS.RED_A = 0;
                COLORS.RED_D = 0;
                COLORS.SPEED = 0;
                IDMaster.VAL = 0;
                IDSlave.VAL = 0;
                ID_RECEPCION.VAL = 0;
                SONAR.SensingDistance = 0;
                for (i = 0; i < 2; i++) SONAR.sensado_minimo[i] = 0;
                for (i = 0; i < (SensorNUMBER / 8); i++) StateSLAVE[i].val = 0;
                for (i = 0; i < (SensorNUMBER / 8); i++) SLAVE_INIT[i].val = 0;
                for (i = 0; i < (SensorNUMBER / 8); i++) DISPLAY_INIT[i].val = 0;
                for (i = 0; i < 4; i++) BufferIndicatorUART[i] = 0;
                return;
            }
        #endif
    #endif
#endif
#endif

                
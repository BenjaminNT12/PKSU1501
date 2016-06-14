/* 
 * File:   PROCESSOR_PARKUEST.h
 * Author: Nicolas
 *
 * Created on 20 de febrero de 2014, 08:51 PM
 * 
 * modificacion de puertos de oscilador para Transductor ultrasonico
 * modificacion A2 y A3
 */

#ifndef PROCESSOR_PARKUEST_H
#define	PROCESSOR_PARKUEST_H

#ifdef	__cplusplus
extern "C" {
#endif

//#define PIC18F_SENSOR
//#define PIC18F_SUI
//#define PIC18F_INDICADOR
#define PIC18F_MasterSLAVE

//#define COMMUNICATION_V1
#define COMMUNICATION_V2

#define MasterFUNCTION      56
#define SlaveFUNCTION       57
#define IndicatorFUNCTION   58
#define HardwareFUNCTION    59

#define SensorWithoutINDICCATOR
#define MasterWithoutINDICATOR

#define Address8BIT // Comentar linea para direcciones de 7 bits
    
/*definir macros para uart*/
#if defined PIC18F_SUI
    #if defined COMMUNICATION_V1
        #define UART1_9bit
    #elif defined COMMUNICATION_V2
        #define UART1_9bit
    #endif
#elif defined PIC18F_MasterSLAVE
    #define UART1_9bit
    #define UART2_9bit
#endif

/*definir macros para pwm*/
#if defined PIC18F_SENSOR
    #define PWM_1_CONFIG
    #define PWM_2_CONFIG
    //#define PWM_3_CONFIG
    //#define PWM_4_CONFIG
    //#define PWM_5_CONFIG
#elif defined PIC18F_SUI
    #define PWM_1_CONFIG
    #define PWM_2_CONFIG
    #define PWM_4_CONFIG
#elif defined PIC18F_MasterSLAVE
    #define PWM_1_CONFIG
    #define PWM_2_CONFIG
    #define PWM_4_CONFIG
#elif defined PIC18F_INDICADOR
    #define PWM_1_CONFIG
    #define PWM_2_CONFIG
    #define PWM_4_CONFIG
#endif


#define REMAPPED_HIGH_INTERRUPT_VECTOR_ADDRESS  0x0008
#define REMAPPED_LOW_INTERRUPT_VECTOR_ADDRESS   0x0018

//#define ISRHIGH
//#define ISRLOW

#if defined PIC18F_SENSOR
    #define OSC1_P      TRISAbits.TRISA2
    #define OSC1_N      TRISAbits.TRISA3
    #define OSC2_P      TRISAbits.TRISA4
    #define OSC2_N      TRISAbits.TRISA5

    #define COM1_IND    LATBbits.LATB2
    #define COM2_IND    LATBbits.LATB3

    #define TXRX_EN1    LATCbits.LATC5

    #define LED1        LATBbits.LATB0
    #define LED2        LATCbits.LATC1
    #define LED3        LATCbits.LATC2

    #define DIP_1       PORTAbits.RA7
    #define DIP_2       PORTAbits.RA6
    #define DIP_3       PORTCbits.RC0
    #define DIP_4       PORTCbits.RC3
    #define DIP_5       PORTCbits.RC4
    #define DIP_6       PORTBbits.RB1
    #define DIP_7       PORTBbits.RB4

#elif defined PIC18F_SUI
    #define OSC1_P      TRISAbits.TRISA2
    #define OSC1_N      TRISAbits.TRISA3
    #define OSC2_P      TRISAbits.TRISA4
    #define OSC2_N      TRISAbits.TRISA5

    #define LED1        LATBbits.LATB0
    #define LED2        LATCbits.LATC1
    #define LED3        LATCbits.LATC2

    #define TXRX_EN1    LATCbits.LATC5
    #define TXRX_EN2    LATBbits.LATB5

    #define COM1_IND    LATBbits.LATB2
    #define COM2_IND    LATBbits.LATB3

    #define DIP_7       PORTAbits.RA7
    #define DIP_6       PORTAbits.RA6
    #define DIP_5       PORTCbits.RC0
    #define DIP_4       PORTCbits.RC3
    #define DIP_3       PORTCbits.RC4
    #define DIP_2       PORTBbits.RB1
    #define DIP_1       PORTBbits.RB4
#elif defined PIC18F_MasterSLAVE
//    #define OSC1_P      TRISAbits.TRISA2 
//    #define OSC1_N      TRISAbits.TRISA3 
    #define OSC1_N      TRISAbits.TRISA2 
    #define OSC1_P      TRISAbits.TRISA3 
    #define OSC2_P      TRISAbits.TRISA4
    #define OSC2_N      TRISAbits.TRISA5

    #define LED1        LATBbits.LATB0
    #define LED2        LATCbits.LATC1
    #define LED3        LATCbits.LATC2

    #define LED_ROJO    LED1   
    #define LED_VERDE   LED2   
    #define LED_AZUL    LED3   

    #define TXRX_EN1    LATCbits.LATC5
    #define TXRX_EN2    LATBbits.LATB5

    #define COM1_IND_O  LATBbits.LATB2
    #define COM2_IND_O  LATBbits.LATB3

    #define COM1_IND_I  PORTBbits.RB2
    #define COM2_IND_I  PORTBbits.RB3

    #define INPUT_IN1   TRISBbits.TRISB2 // TRANSIMISION
    #define INPUT_IN2   TRISBbits.TRISB3 // RECEPCION

    #define DIP_1       PORTAbits.RA7
    #define DIP_2       PORTAbits.RA6
    #define DIP_3       PORTCbits.RC0
    #define DIP_4       PORTCbits.RC3
    #define DIP_5       PORTCbits.RC4
    #define DIP_6       PORTBbits.RB1
    #define DIP_7       PORTBbits.RB4
#if defined Address8BIT
    #define DIP_8       PORTEbits.RE3 /********REVISION*********/
#endif


#elif defined PIC18F_INDICADOR
    #define LED1        LATBbits.LATB0
    #define LED2        LATCbits.LATC1
    #define LED3        LATCbits.LATC2

    #define COM1_IND    PORTBbits.RB2
    #define COM2_IND    PORTBbits.RB3
#endif


void CONF_PROCESSOR         (void);
void OSC_CONF               (void);
void IO_CONF                (void);
void INTERRRUPT_ON          (void);
void INTERRRUPT_OFF         (void);
void RESET_PROCESSOR        (void);
void SLEEP_PROCESSOR        (void);
void ClearWDT               (void);

#ifdef	__cplusplus
}
#endif

#endif	/* PROCESSOR_PARKUEST_H */


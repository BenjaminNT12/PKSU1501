/* 
 * File:   PWM_PARKUEST.h
 * Author: Nicolas
 *
 * Created on 20 de febrero de 2014, 07:41 PM
 */

#ifndef PWM_PARKUEST_H
#define	PWM_PARKUEST_H

#ifdef	__cplusplus
extern "C" {
#endif


//#define PWM_1_CONFIG
//#define PWM_2_CONFIG
//#define PWM_3_CONFIG
//#define PWM_4_CONFIG
//#define PWM_5_CONFIG

#define PWM_1_ON()    {CCP1CONbits.CCP1M3 = 1; CCP1CONbits.CCP1M2 = 1; CCP1CONbits.CCP1M1 = 0; CCP1CONbits.CCP1M0 = 0;}
#define PWM_2_ON()    {CCP2CONbits.CCP2M3 = 1; CCP2CONbits.CCP2M2 = 1; CCP2CONbits.CCP2M1 = 0; CCP2CONbits.CCP2M0 = 0;}
#define PWM_3_ON()    {CCP3CONbits.CCP3M3 = 1; CCP3CONbits.CCP3M2 = 1; CCP3CONbits.CCP3M1 = 0; CCP3CONbits.CCP3M0 = 0;}
#define PWM_4_ON()    {CCP4CONbits.CCP4M3 = 1; CCP4CONbits.CCP4M2 = 1; CCP4CONbits.CCP4M1 = 0; CCP4CONbits.CCP4M0 = 0;}
#define PWM_5_ON()    {CCP5CONbits.CCP5M3 = 1; CCP5CONbits.CCP5M2 = 1; CCP5CONbits.CCP5M1 = 0; CCP5CONbits.CCP5M0 = 0;}

#define PWM_1_OFF()   {CCP1CONbits.CCP1M3 = 0; CCP1CONbits.CCP1M2 = 0; CCP1CONbits.CCP1M1 = 0; CCP1CONbits.CCP1M0 = 0;}
#define PWM_2_OFF()   {CCP2CONbits.CCP2M3 = 0; CCP2CONbits.CCP2M2 = 0; CCP2CONbits.CCP2M1 = 0; CCP2CONbits.CCP2M0 = 0;}
#define PWM_3_OFF()   {CCP3CONbits.CCP3M3 = 0; CCP3CONbits.CCP3M2 = 0; CCP3CONbits.CCP3M1 = 0; CCP3CONbits.CCP3M0 = 0;}
#define PWM_4_OFF()   {CCP4CONbits.CCP4M3 = 0; CCP4CONbits.CCP4M2 = 0; CCP4CONbits.CCP4M1 = 0; CCP4CONbits.CCP4M0 = 0;}
#define PWM_5_OFF()   {CCP5CONbits.CCP5M3 = 0; CCP5CONbits.CCP5M2 = 0; CCP5CONbits.CCP5M1 = 0; CCP5CONbits.CCP5M0 = 0;}

#if defined PWM_1_CONFIG
    #define PWM1 LATCbits.LATC2
    void PWM1_CONF              (unsigned int DUTY);
    void PWM1_DUTY              (unsigned int DUTY);
    void PWM1_ON                (void);
    void PWM1_OFF               (void);
#endif
#if defined PWM_2_CONFIG
    #define PWM2 LATCbits.LATC1
    void PWM2_CONF              (unsigned int DUTY);
    void PWM2_DUTY              (unsigned int DUTY);
    void PWM2_ON                (void);
    void PWM2_OFF               (void);
#endif
#if defined PWM_3_CONFIG
    #define PWM3 LATBbits.LATB5
    void PWM3_CONF              (unsigned int DUTY);
    void PWM3_DUTY              (unsigned int DUTY);
    void PWM3_ON                (void);
    void PWM3_OFF               (void);
#endif
#if defined PWM_4_CONFIG
    #define PWM4 LATBbits.LATB0
    void PWM4_CONF              (unsigned int DUTY);
    void PWM4_DUTY              (unsigned int DUTY);
    void PWM4_ON                (void);
    void PWM4_OFF               (void);
#endif
#if defined PWM_5_CONFIG
    #define PWM5 LATAbits.LATA4
    void PWM5_CONF              (unsigned int DUTY);
    void PWM5_DUTY              (unsigned int DUTY);
    void PWM5_ON                (void);
    void PWM5_OFF               (void);
#endif

#ifdef	__cplusplus
}
#endif

#endif	/* PWM_PARKUEST_H */



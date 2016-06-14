/* 
 * File:   TIMER_PARKUEST.h
 * Author: Nicolas
 *
 * Created on 25 de febrero de 2014, 02:19 PM
 */

#ifndef TIMER_PARKUEST_H
#define	TIMER_PARKUEST_H

#ifdef	__cplusplus
extern "C" {
#endif

#define TIMER0_
//#define ISRHIGH
#define ISRLOW
#define TIMER0_FLAG INTCONbits.TMR0IF

#define REMAPPED_HIGH_INTERRUPT_VECTOR_ADDRESS  0x0008
#define REMAPPED_LOW_INTERRUPT_VECTOR_ADDRESS   0x0018

#define mSeconds5   65458
#define mSeconds10  65380
#define mSeconds50  64755
#define mSeconds100 63974
#define mSeconds200 62411
#define mSeconds500 57724
#define Seconds1    49911
#define Seconds2    34286
#define Seconds3    18661
#define Seconds4    3036

#if defined  TIMER0_
    BOOL TIMER_SEC_Remaining1   (unsigned int _Alarm);
    void TIMER0_CONF            (void);
    void WriteTimer0            (unsigned int timer0);
    void TIMER0_ON              (void);
    void TIMER0_OFF             (void);
    BOOL TIMER_MIN_Remaining1   (unsigned char _Alarm);
    BOOL TIMER_MIN_Remaining2   (unsigned char _Alarm);
    BOOL TIMER_SEC_Remaining2   (unsigned char _Alarm);
    BOOL TIMER_SEC_Remaining3   (unsigned char _Alarm);
#endif

#ifdef	__cplusplus
}
#endif

#endif	/* TIMER_PARKUEST_H */


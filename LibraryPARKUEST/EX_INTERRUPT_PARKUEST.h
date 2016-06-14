/* 
 * File:   EX_INTERRUPT_PARKUEST.h
 * Author: Nicolas
 *
 * Created on 20 de febrero de 2014, 09:30 PM
 */

#ifndef EX_INTERRUPT_PARKUEST_H
#define	EX_INTERRUPT_PARKUEST_H

#ifdef	__cplusplus
extern "C" {
#endif

//#define INT_0
//#define INT_1
//#define INT_2

#define INTERRUPT_0     INTCONbits.INT0IF
#define INTERRUPT_1     INTCON3bits.INT1IF
#define INTERRUPT_2     INTCON3bits.INT2IF

    #if defined INT_0
        void INTERRUPT_EXTERNAL0(void);
    #endif

    #if defined INT_1
        void INTERRUPT_EXTERNAL1(void);
    #endif

    #if defined INT_2
        void INTERRUPT_EXTERNAL2(void);
    #endif

#ifdef	__cplusplus
}
#endif

#endif	/* EX_INTERRUPT_PARKUEST_H */


#include <p18cxxx.h>
#include <GenericTypeDefs.h>
#include "PROCESSOR_PARKUEST.h"
#include "TIMER_PARKUEST.h"


#if defined __18F25K22_H || defined __18F24K22_H

    extern BOOL FLAG_TIMER_HIGH;
    BOOL FLAG_TIMER1;
    BOOL FLAG_TIMER2;
    BOOL FLAG_TIMER3;
    BOOL FLAG_TIMER4;
    BOOL FLAG_TIMER5;

    #if defined ISRHIGH
        void ISRhigh(void);
    #endif
    #if defined ISRLOW
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

        }
        #pragma code
        #warning "Interrupt Service Routine HIGH";
    #endif

    #if defined ISRLOW
        #pragma code ISR_LOW_VECTOR  = REMAPPED_LOW_INTERRUPT_VECTOR_ADDRESS
        void ISR_AT_LOW_VECTOR (void){
            _asm goto ISRlow _endasm
        }
        #pragma code

        #pragma interrupt ISRlow
        void ISRlow(void) {
            INTCONbits.GIE = 0;
            if (TIMER0_FLAG) {
                TIMER0_FLAG = 0;
                FLAG_TIMER_HIGH = 1;
                FLAG_TIMER1 = 1;
                FLAG_TIMER2 = 1;
                FLAG_TIMER3 = 1;
                FLAG_TIMER4 = 1;
                FLAG_TIMER5 = 1;
            }
            WriteTimer0(Seconds1);
            INTCONbits.GIE = 1;
            return;
        }
        #pragma code
        #warning "Interrupt Service Routine LOW";
    #endif

    #if defined TIMER0_
        void TIMER0_CONF(void){
            T0CONbits.TMR0ON    = 0;    // ACTIVA TIMER 0
            T0CONbits.T08BIT    = 0;    // ACTIVA TIMER 16 BITS
            T0CONbits.T0CS      = 0;    // FUENTE DE RELOG DEL TIMER
            T0CONbits.T0SE      = 1;    // low to high
            T0CONbits.PSA       = 0;    // ACTIVA PRESCALER PARA TIMER

            T0CONbits.T0PS2     = 1;    // PRESCALER DE 1:256
            T0CONbits.T0PS1     = 1;    // PRESCALER DE 1:256
            T0CONbits.T0PS0     = 1;    // PRESCALER DE 1:256

            INTCONbits.TMR0IF   = 0;
            INTCONbits.TMR0IE   = 1;    // interrupciones activadas
            INTCON2bits.TMR0IP  = 0;
            TMR0L               = 0;
            TMR0H               = 0;
            T0CONbits.TMR0ON    = 1;    // ACTIVA TIMER 0
            INTCONbits.PEIE     = 1;
            INTCONbits.GIE      = 1;
        #warning "TIMER0 ACTIVATED"
        }

    void TIMER0_ON(void){
        T0CONbits.TMR0ON    = 1;    // ACTIVA TIMER 0
    }

    void TIMER0_OFF(void){
        T0CONbits.TMR0ON    = 0;    // ACTIVA TIMER 0
    }

    void WriteTimer0(unsigned int timer0) {
        UINT16_VAL timer = 0;

        timer.Val = timer0;
        TMR0H = timer.v[1]; // Write high byte to Timer0
        TMR0L = timer.v[0]; // Write low byte to Timer0
    }

    BOOL TIMER_MIN_Remaining1(unsigned char _Alarm) {
        static unsigned char SEC_1 = 0;
        static unsigned char MIN_1 = 0;

        if (FLAG_TIMER1 == 1) {
            FLAG_TIMER1 = 0;
            SEC_1++;
            if (SEC_1 == 60) {
                SEC_1 = 0;
                MIN_1++;
                if (MIN_1 == _Alarm) {
                    MIN_1 = 0;
                    return (1);
                }
            }
        }
        return (0);
    }

    BOOL TIMER_MIN_Remaining2(unsigned char _Alarm) {
        static unsigned char SEC_2 = 0;
        static unsigned char MIN_2 = 0;

        if (FLAG_TIMER2 == 1) {
            FLAG_TIMER2 = 0;
            SEC_2++;
            if (SEC_2 == 60) {
                SEC_2 = 0;
                MIN_2++;
                if (MIN_2 == _Alarm) {
                    MIN_2 = 0;
                    return (1);
                }
            }
        }
        return (0);
    }

    BOOL TIMER_SEC_Remaining1(unsigned int _Alarm) {
        static unsigned int SEC_3 = 0;

        if (FLAG_TIMER3 == 1) {
            FLAG_TIMER3 = 0;
            SEC_3++;
            if (SEC_3 == _Alarm) {
                SEC_3 = 0;
                return (1);
            }
        }
        return (0);
    }

    BOOL TIMER_SEC_Remaining2(unsigned char _Alarm) {
        static unsigned char SEC_4 = 0;

        if (FLAG_TIMER4 == 1) {
            FLAG_TIMER4 = 0;
            SEC_4++;
            if (SEC_4 == _Alarm) {
                SEC_4 = 0;
                return (1);
            }
        }
        return (0);
    }

    BOOL TIMER_SEC_Remaining3(unsigned char _Alarm) {
        static unsigned char SEC_5 = 0;

        if (FLAG_TIMER5 == 1) {
            FLAG_TIMER5 = 0;
            SEC_5++;
            if (SEC_5 == _Alarm) {
                SEC_5 = 0;
                return (1);
            }
        }
        return (0);
    }

    #endif
#endif


/*formula para el timer*/

/*
 *overflow=(2^n-TMR0)*(prescaler/(Fosc/4))
 *
 * n=numero de bits del timer (16 ú 8)
 * TMR0= valor inicial del timer
 * prescaler=valor del prescaler
 * Fosc=frecuencia del oscilador del microcontrolador
 *
 * formula para calcular el valor de TMRO
 * Vtmr0=2^n-((overflow*(Fosc/4)/prescaler))
 *
 *
 */
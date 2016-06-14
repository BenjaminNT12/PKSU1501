/*
 * EJEMPLO PARA RUTINA DE INTERRUPCION, PARA EL USO DE
 * INTERRUPCIONES EXTERNAS
 *
 *  volatile BOOL flag_sens1;
 *  volatile BOOL flag_sens2;
 *  volatile BOOL flag_sens3;
 *
 *  void ISRhigh(void); /////////////////////////////////////// definicion de la ISR
 *  #pragma code ISR_HIGH_VECTOR = 0x0008
 *  void ISR_AT_HIGH_VECTOR(void){
 *        _asm goto ISRhigh _endasm
 *  }
 *  #pragma code
 *
 *  #pragma interrupt ISRhigh
 *  void ISRhigh(void){
 *       INTCONbits.GIE = 0;
 *           if(INTERRUPT_0==1){
 *               INTERRUPT_0=0;
 *               flag_sens1=1;
 *           }
 *
 *           if(INTERRUPT_1==1){
 *               INTERRUPT_1=0;
 *               flag_sens2=1;
 *           }
 *
 *           if(INTERRUPT_2==1){
 *               INTERRUPT_2=0;
 *               flag_sens2=1;
 *           }
 *       INTCONbits.GIE = 1;
 *       return;
 *   }
 *
 */

#include <p18cxxx.h>
#include "PROCESSOR_PARKUEST.h"
#include "EX_INTERRUPT_PARKUEST.h"

#if defined __18F25K22_H || defined __18F24K22_H
    #if defined INT_0
        void INTERRUPT_EXTERNAL0(void){
            INTCONbits.INT0IE   = 1;    // interrupcion externa
            INTCONbits.INT0IF   = 0;    // bandera de interrupcion
            INTCON2bits.INTEDG0 = 1;    // interrupcion por flanco de subida
            INTCONbits.PEIE     = 1;    // activa interrupciones de perifericos
            #warning "INTERRRUPT EXT 0";
        }
    #endif

    #if defined INT_1
        void INTERRUPT_EXTERNAL1(void){
            INTCON3bits.INT1IE   = 1;   // interrupcion externa
            INTCON3bits.INT1IF   = 0;   // bandera de interrupcion
            INTCON2bits.INTEDG1  = 1;   // interrupcion por flanco de subida
            INTCONbits.PEIE      = 1;   // activa interrupciones de perifericos
            #warning "INTERRRUPT EXT 1";
        }
    #endif

    #if defined INT_2
        void INTERRUPT_EXTERNAL2(void){
            INTCON3bits.INT2IE   = 1;   // interrupcion externa
            INTCON3bits.INT2IF   = 0;   // bandera de interrupcion
            INTCON2bits.INTEDG2 = 1;    // interrupcion por flanco de subida
            INTCONbits.PEIE     = 1;    // activa interrupciones de perifericos
            #warning "INTERRRUPT EXT 2";
        }
    #endif
#endif


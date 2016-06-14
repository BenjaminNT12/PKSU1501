#include "PROCESSOR_PARKUEST.h"
#include <p18cxxx.h>
#include "ADC_PARKUEST.h"

#if defined __18F25K22_H || defined __18F24K22_H
    void ADC_INPUT_CONFIG(void){
        ANSELAbits.ANSA0    = 1;    /* ACTIVA EL CANAL ANALOGICO (1) */
        ANSELAbits.ANSA1    = 1;
        ANSELAbits.ANSA2    = 0;
        ANSELAbits.ANSA3    = 0;
        ANSELAbits.ANSA5    = 0;

        ANSELBbits.ANSB0    = 0;
        ANSELBbits.ANSB1    = 0;
        ANSELBbits.ANSB2    = 0;
        ANSELBbits.ANSB3    = 0;
        ANSELBbits.ANSB4    = 0;
        ANSELBbits.ANSB5    = 0;

        ANSELCbits.ANSC2    = 0;
        ANSELCbits.ANSC3    = 0;
        ANSELCbits.ANSC4    = 0;
        ANSELCbits.ANSC5    = 0;
        ANSELCbits.ANSC6    = 0;
        ANSELCbits.ANSC7    = 0;
    }

    void AN_CONF(void){
        ADC_INPUT_CONFIG();
        ADCON0              = 0;
        ADCON1              = 0;
        ADCON2              = 0;
        ADCON0bits.ADON     = 0;    // APAGA EL CONVERSOR ANALOGICO
        ADCON1bits.PVCFG1   = 1;    // valor de referencia positivo 1       /*VOLTAJES DE REFERENCIA*/
        ADCON1bits.PVCFG0   = 1;    // valor de referencia positivo 0
        ADCON1bits.NVCFG1   = 1;    // valor de referencia negativo 1
        ADCON1bits.NVCFG0   = 1;    // valor de referencia negativo 0
        ADCON2bits.ADCS2    = 1;    // frecuencia del oscilador  FOSC/32    /*SELECTOR DE RELOG DE ENTRADA PARA CONVERSION*/
        ADCON2bits.ADCS1    = 0;    // frecuencia del oscilador  FOSC/32
        ADCON2bits.ADCS0    = 1;    // frecuencia del oscilador  FOSC/32
        ADCON2bits.ADFM     = 1;    // justificador a la derecha            /*FORMATO DE RESULTADO*/
        ADCON2bits.ACQT2    = 1;    // tiempor de adquisicion 12Tad         /*TIEMPO DE ADQUISICION*/
        ADCON2bits.ACQT1    = 0;    // tiempor de adquisicion 12Tad
        ADCON2bits.ACQT0    = 1;    // tiempor de adquisicion 12Tad
        PMD2bits.ADCMD      = 0;    /*activa el modulo*/
        #warning "ADC_ACTIVATED";
    }

    unsigned int StartAN(unsigned char _AN){
        unsigned int _temp;

        ADCON0bits.ADON     = 0;    // apaga elconvertidor analogico digital
        ADCON0bits.CHS      = _AN;  // activa el canal del convertidor
        ADCON0bits.ADON     = 1;    // enciende el convertidor
        ADCON0bits.GO       = 1;    // empieza la conversion
        while(ADCON0bits.GO);       // espera a que termine la conversion
        if(PIR1bits.ADIF){          // verifica y la conversion a terminado
            _temp=(((unsigned int)ADRESH)<<8)|(ADRESL); // devuelve el valor del convertidor
            PIR1bits.ADIF=0;        // resetea la bandera de intrrupcion
        }
        ADCON0bits.ADON     = 0;    // apaga elconvertidor analogico digital

        return _temp;               // devuelve el resultado concatenado con el registro bajo y el alto
    }
#endif


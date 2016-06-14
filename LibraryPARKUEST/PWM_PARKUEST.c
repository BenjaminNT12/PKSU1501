#include <p18cxxx.h>
#include "PROCESSOR_PARKUEST.h"
#include "PWM_PARKUEST.h"

#if defined __18F25K22_H || defined __18F24K22_H
    #if defined PWM_1_CONFIG
        void PWM1_CONF(unsigned int DUTY){
            CCP1CONbits.CCP1M3   = 1;       /*PWM  ESTANDAR*/
            CCP1CONbits.CCP1M2   = 1;
            CCP1CONbits.CCP1M1   = 0;
            CCP1CONbits.CCP1M0   = 0;
            TRISCbits.TRISC2     = 0;       // SALIDA PWM 
            CCPTMRS0bits.C1TSEL1 = 0;       // TIMER 2 PARA PWM 
            CCPTMRS0bits.C1TSEL0 = 0;       // seleccion del timer 2
            T2CONbits.TMR2ON     = 0;       // ACTIVA TIMER2 
            PR2                  = 0xFF;    // PERIODO DE PWM
            T2CONbits.TMR2ON     = 1;       // ACTIVA TIMER2 
            PMD1bits.CCP1MD      = 0;       // modulo activado, clock source connected, module draw digital power/*ACTIVACION DEL MODULO*/
            CCP1CONbits.DC1B1    = DUTY;    // CICLO DE TRABAJO
            CCP1CONbits.DC1B0    = DUTY>>1;
            CCPR1L               = DUTY>>2;
            T2CONbits.T2OUTPS3   = 0;       // postcale 1:1 /*postcaler para timer 2*/
            T2CONbits.T2OUTPS2   = 1;       // postcale 1:1
            T2CONbits.T2OUTPS1   = 1;       // postcale 1:1
            T2CONbits.T2OUTPS0   = 0;       // postcale 1:1
            
            T2CONbits.T2CKPS1    = 0;       // prescaler 16/*prescaler para timer 2*/
            #warning "PWM1_ACTIVATED";
        }

        void PWM1_DUTY(unsigned int DUTY){
            CCP1CONbits.DC1B1    = DUTY;    // escribe el valor del ciclo de trabajo en el bit mas bajo
            CCP1CONbits.DC1B0    = DUTY>>1; // escribe el valor del ciclo de trabajo en el bit 1
            CCPR1L               = DUTY>>2; // escribe el valor del ciclo de trabajo en el bit 2 - al 9
        }

        void PWM1_ON(void){
            CCP1CONbits.CCP1M3   = 1;       // PWM  ESTANDAR
            CCP1CONbits.CCP1M2   = 1;
            CCP1CONbits.CCP1M1   = 0;
            CCP1CONbits.CCP1M0   = 0;
        }

        void PWM1_OFF(void){
            CCP1CONbits.CCP1M3   = 0;       // PWM  ESTANDAR
            CCP1CONbits.CCP1M2   = 0;
            CCP1CONbits.CCP1M1   = 0;
            CCP1CONbits.CCP1M0   = 0;
            LED_AZUL = 0;
        }

    #endif

    #if defined PWM_2_CONFIG
        void PWM2_CONF(unsigned int DUTY){
            
            CCP2CONbits.CCP2M3   = 1;       // PWM ESTANDAR
            CCP2CONbits.CCP2M2   = 1;
            CCP2CONbits.CCP2M1   = 0;
            CCP2CONbits.CCP2M0   = 0;
            TRISCbits.TRISC1     = 0;       // SALIDA PWM 
            CCPTMRS0bits.C2TSEL1 = 0;       // TIMER 4 PARA PWM
            CCPTMRS0bits.C2TSEL0 = 1;       // seleccion del timer 4
            T4CONbits.TMR4ON     = 0;       // ACTIVA TIMER4
            PR4                  = 0xFF;    // PERIODO DE PWM
            T4CONbits.TMR4ON     = 1;       // ACTIVA TIMER4
            PMD1bits.CCP2MD      = 0;       // modulo activado, clock source connected, module draw digital power/*ACTIVACION DEL MODULO*/
            CCP2CONbits.DC2B1    = DUTY;    // CICLO DE TRABAJO
            CCP2CONbits.DC2B0    = DUTY>>1;
            CCPR2L               = DUTY>>2;
            T4CONbits.T4OUTPS3   = 0;       // postcale 1:1// postcaler para timer 4
            T4CONbits.T4OUTPS2   = 0;       // postcale 1:1
            T4CONbits.T4OUTPS1   = 0;       // postcale 1:1
            T4CONbits.T4OUTPS0   = 0;       // postcale 1:1
            T4CONbits.T4CKPS1    = 0;       // prescaler 16// prescaler para timer 4
            #warning "PWM2_ACTIVATED";
        }

        void PWM2_DUTY(unsigned int DUTY){
            CCP2CONbits.DC2B1    = DUTY;    // escribe el valor del ciclo de trabajo en el bit mas bajo
            CCP2CONbits.DC2B0    = DUTY>>1; // escribe el valor del ciclo de trabajo en el bit 1
            CCPR2L               = DUTY>>2; // escribe el valor del ciclo de trabajo en el bit 2 - al 9
        }

        void PWM2_ON(void){
            CCP2CONbits.CCP2M3   = 1;       /*PWM  ESTANDAR*/
            CCP2CONbits.CCP2M2   = 1;
            CCP2CONbits.CCP2M1   = 0;
            CCP2CONbits.CCP2M0   = 0;
        }

        void PWM2_OFF(void){
            CCP2CONbits.CCP2M3   = 0;       /*PWM  ESTANDAR*/
            CCP2CONbits.CCP2M2   = 0;
            CCP2CONbits.CCP2M1   = 0;
            CCP2CONbits.CCP2M0   = 0;
            LED_VERDE = 0;
        }


    #endif

    #if defined PWM_3_CONFIG
        void PWM3_CONF(unsigned int DUTY){
            
            CCP3CONbits.CCP3M3   = 1;   // PWM ESTANDAR
            CCP3CONbits.CCP3M2   = 1;
            CCP3CONbits.CCP3M1   = 0;
            CCP3CONbits.CCP3M0   = 0;
            TRISBbits.TRISB5     = 0;   // SALIDA PWM
            CCPTMRS0bits.C3TSEL1 = 0;   // TIMER 4 PARA PWM 
            CCPTMRS0bits.C3TSEL0 = 1;   // seleccion del timer 4
            T4CONbits.TMR4ON     = 0;   // ACTIVA TIMER4
            PR4                  = 0xFF;// PERIODO DE PWM
            T4CONbits.TMR4ON     = 1;   // ACTIVA TIMER4
            PMD1bits.CCP3MD      =0;    // modulo activado, clock source connected, module draw digital power
            CCP3CONbits.DC3B1    = DUTY;// CICLO DE TRABAJO
            CCP3CONbits.DC3B0    = DUTY>>1;
            CCPR3L               = DUTY>>2;
            T4CONbits.T4OUTPS3   = 0;   //postcale 1:1/*postcaler para timer 4*/
            T4CONbits.T4OUTPS2   = 0;   //postcale 1:1
            T4CONbits.T4OUTPS1   = 0;   //postcale 1:1
            T4CONbits.T4OUTPS0   = 0;   //postcale 1:1
            T4CONbits.T4CKPS1    = 0;   //prescaler 16/*prescaler para timer 4*/
            #warning "PWM3_ACTIVATED";
        }


        void PWM3_DUTY(unsigned int DUTY){
            CCP3CONbits.DC3B1    = DUTY;
            CCP3CONbits.DC3B0    = DUTY>>1;
            CCPR3L               = DUTY>>2;
        }

        void PWM3_ON(void){
            CCP3CONbits.CCP3M3   = 1;
            CCP3CONbits.CCP3M2   = 1;
            CCP3CONbits.CCP3M1   = 0;
            CCP3CONbits.CCP3M0   = 0;
        }

        void PWM3_OFF(void){
            CCP3CONbits.CCP3M3   = 0;
            CCP3CONbits.CCP3M2   = 0;
            CCP3CONbits.CCP3M1   = 0;
            CCP3CONbits.CCP3M0   = 0;
        }

    #endif

    #if defined PWM_4_CONFIG
        void PWM4_CONF(unsigned int DUTY){

            CCP4CONbits.CCP4M3   = 1;   // PWM  ESTANDAR
            CCP4CONbits.CCP4M2   = 1;
            CCP4CONbits.CCP4M1   = 0;
            CCP4CONbits.CCP4M0   = 0;
            TRISBbits.TRISB0     = 0;   // SALIDA PWM
            CCPTMRS1bits.C4TSEL1 = 0;   // TIMER 4 PARA PWM 
            CCPTMRS1bits.C4TSEL0 = 1;   // seleccion del timer 4
            T4CONbits.TMR4ON     = 0;   // ACTIVA TIMER4
            PR4                  = 0xFF;// PERIODO DE PWM
            T4CONbits.TMR4ON     = 1;   // ACTIVA TIMER4
            PMD1bits.CCP4MD      = 0;   // modulo activado, clock source connected, module draw digital power
            CCP4CONbits.DC4B1    = DUTY;// CICLO DE TRABAJO
            CCP4CONbits.DC4B0    = DUTY>>1;
            CCPR4L               = DUTY>>2;
            T4CONbits.T4OUTPS3   = 0;   // postcale 1:1/* postcaler para timer 4*/
            T4CONbits.T4OUTPS2   = 0;   // postcale 1:1
            T4CONbits.T4OUTPS1   = 0;   // postcale 1:1
            T4CONbits.T4OUTPS0   = 0;   // postcale 1:1
            T4CONbits.T4CKPS1    = 0;   // prescaler 16/*prescaler para timer 4*/
            #warning "PWM4_ACTIVATED";
        }

        void PWM4_DUTY(unsigned int DUTY){
            CCP4CONbits.DC4B1    = DUTY;
            CCP4CONbits.DC4B0    = DUTY>>1;
            CCPR4L               = DUTY>>2;
        }

        void PWM4_ON(void){
            CCP4CONbits.CCP4M3   = 1;
            CCP4CONbits.CCP4M2   = 1;
            CCP4CONbits.CCP4M1   = 0;
            CCP4CONbits.CCP4M0   = 0;
        }

        void PWM4_OFF(void){
            CCP4CONbits.CCP4M3   = 0;
            CCP4CONbits.CCP4M2   = 0;
            CCP4CONbits.CCP4M1   = 0;
            CCP4CONbits.CCP4M0   = 0;
            LED_ROJO = 0;
        }


    #endif

    #if defined PWM_5_CONFIG
        void PWM5_CONF(unsigned int DUTY){
            
            CCP5CONbits.CCP5M3   = 1;   // PWM  ESTANDAR
            CCP5CONbits.CCP5M2   = 1;
            CCP5CONbits.CCP5M1   = 0;
            CCP5CONbits.CCP5M0   = 0;
            TRISAbits.TRISA4     = 0;   // SALIDA PWM
            CCPTMRS1bits.C4TSEL1 = 0;   // TIMER 4 PARA PWM
            CCPTMRS1bits.C4TSEL0 = 1;   // seleccion del timer 4
            T4CONbits.TMR4ON     = 0;   // ACTIVA TIMER4
            PR4                  = 0xFF;// PERIODO DE PWM
            T4CONbits.TMR4ON     = 1;   // ACTIVA TIMER4
            PMD1bits.CCP5MD      =0;    // modulo activado, clock source connected, module draw digital power
            CCP5CONbits.DC5B1    = DUTY;// CICLO DE TRABAJO
            CCP5CONbits.DC5B0    = DUTY>>1;
            CCPR5L               = DUTY>>2;
            T4CONbits.T4OUTPS3   = 0;   // postcale 1:1/*postcaler para timer 4   */
            T4CONbits.T4OUTPS2   = 0;   // postcale 1:1
            T4CONbits.T4OUTPS1   = 0;   // postcale 1:1
            T4CONbits.T4OUTPS0   = 0;   // postcale 1:1            
            T4CONbits.T4CKPS1    = 0;   // prescaler 16/*prescaler para timer 4*/
            #warning "PWM5_ACTIVATED";
        }

        void PWM5_DUTY(unsigned int DUTY){
            CCP5CONbits.DC5B1    = DUTY;
            CCP5CONbits.DC5B0    = DUTY>>1;
            CCPR5L               = DUTY>>2;
        }

        void PWM5_ON(void){
            CCP5CONbits.CCP5M3   = 1;
            CCP5CONbits.CCP5M2   = 1;
            CCP5CONbits.CCP5M1   = 0;
            CCP5CONbits.CCP5M0   = 0;
        }

        void PWM5_OFF(void){
            CCP5CONbits.CCP5M3   = 0;
            CCP5CONbits.CCP5M2   = 0;
            CCP5CONbits.CCP5M1   = 0;
            CCP5CONbits.CCP5M0   = 0;
        }

    #endif
#endif


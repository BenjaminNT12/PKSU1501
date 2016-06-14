#include <p18cxxx.h>
#include <delays.h>
#include <GenericTypeDefs.h>
#include "PROCESSOR_PARKUEST.h"


#if defined __18F25K22_H || defined __18F24K22_H
// CONFIG1H
#pragma config FOSC         = INTIO67       // Oscillator Selection bits (Internal oscillator block)
#pragma config PLLCFG       = OFF           // 4X PLL Enable (Oscillator used directly)
#pragma config PRICLKEN     = OFF           // Primary clock enable bit (Primary clock can be disabled by software)
#pragma config FCMEN        = OFF           // Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor disabled)
#pragma config IESO         = OFF           // Internal/External Oscillator Switchover bit (Oscillator Switchover mode disabled)
// CONFIG2L
#pragma config PWRTEN       = ON            // Power-up Timer Enable bit (Power up timer enabled)
#pragma config BOREN        = ON            // Brown-out Reset Enable bits (Brown-out Reset enabled and controlled by software (SBOREN is enabled))
#pragma config BORV         = 190           // Brown Out Reset Voltage bits (VBOR set to 1.90 V nominal)
// CONFIG2H
#pragma config WDTEN        = ON            // Watchdog Timer Enable bits (WDT is always enabled. SWDTEN bit has no effect)
#pragma config WDTPS        = 8192          // Watchdog Timer Postscale Select bits (1:8192)
// CONFIG3H
#pragma config CCP2MX       = PORTC1        // CCP2 MUX bit (CCP2 input/output is multiplexed with RC1)
#pragma config PBADEN       = OFF           // PORTB A/D Enable bit (PORTB<5:0> pins are configured as digital I/O on Reset)
#pragma config CCP3MX       = PORTB5        // P3A/CCP3 Mux bit (P3A/CCP3 input/output is multiplexed with RB5)
#pragma config HFOFST       = ON            // HFINTOSC Fast Start-up (HFINTOSC output and ready status are not delayed by the oscillator stable status)
#pragma config T3CMX        = PORTB5        // Timer3 Clock input mux bit (T3CKI is on RB5)
#pragma config P2BMX        = PORTB5        // ECCP2 B output mux bit (P2B is on RB5)
#if defined Address8BIT
    #pragma config MCLRE        = INTMCLR       // MCLR Pin Enable bit (RE3 input pin enabled; MCLR disabled) CONFIGURACION NECESARIA PARA ACTIVAR RE3
#else
    #pragma config MCLRE        = EXTMCLR       // MCLR Pin Enable bit (RE3 input pin enabled; MCLR disabled)
#endif
// CONFIG4L
#pragma config STVREN       = ON            // Stack Full/Underflow Reset Enable bit (Stack full/underflow will cause Reset)
#if defined Address8BIT
    #pragma config LVP          = OFF            // Single-Supply ICSP Enable bit (Single-Supply ICSP enabled if MCLRE is also 1) CONFIGURACION NECESARIA PARA ACTIVAR RE3
#else
    #pragma config LVP          = ON            // Single-Supply ICSP Enable bit (Single-Supply ICSP enabled if MCLRE is also 1)
#endif
#pragma config XINST        = OFF           // Extended Instruction Set Enable bit (Instruction set extension and Indexed Addressing mode disabled (Legacy mode))
#pragma config DEBUG        = OFF
// CONFIG5L
#pragma config CP0          = ON            // Code Protection Block 0 (Block 0 (000800-001FFFh) code-protected)
#pragma config CP1          = ON            // Code Protection Block 1 (Block 1 (002000-003FFFh) code-protected)
#pragma config CP2          = ON            // Code Protection Block 2 (Block 2 (004000-005FFFh) code-protected)
#pragma config CP3          = ON            // Code Protection Block 3 (Block 3 (006000-007FFFh) code-protected)
// CONFIG5H
#pragma config CPB          = OFF           // Boot Block Code Protection bit (Boot block (000000-0007FFh) not code-protected)
#pragma config CPD          = OFF           // Data EEPROM Code Protection bit (Data EEPROM not code-protected)
// CONFIG6L
#pragma config WRT0         = OFF           // Write Protection Block 0 (Block 0 (000800-001FFFh) not write-protected)
#pragma config WRT1         = OFF           // Write Protection Block 1 (Block 1 (002000-003FFFh) not write-protected)
#pragma config WRT2         = OFF           // Write Protection Block 2 (Block 2 (004000-005FFFh) not write-protected)
#pragma config WRT3         = OFF           // Write Protection Block 3 (Block 3 (006000-007FFFh) not write-protected)
// CONFIG6H
#pragma config WRTC         = OFF           // Configuration Register Write Protection bit (Configuration registers (300000-3000FFh) not write-protected)
#pragma config WRTB         = OFF           // Boot Block Write Protection bit (Boot Block (000000-0007FFh) not write-protected)
#pragma config WRTD         = OFF           // Data EEPROM Write Protection bit (Data EEPROM not write-protected)
// CONFIG7L
#pragma config EBTR0        = OFF           // Table Read Protection Block 0 (Block 0 (000800-001FFFh) not protected from table reads executed in other blocks)
#pragma config EBTR1        = OFF           // Table Read Protection Block 1 (Block 1 (002000-003FFFh) not protected from table reads executed in other blocks)
#pragma config EBTR2        = OFF           // Table Read Protection Block 2 (Block 2 (004000-005FFFh) not protected from table reads executed in other blocks)
#pragma config EBTR3        = OFF           // Table Read Protection Block 3 (Block 3 (006000-007FFFh) not protected from table reads executed in other blocks)
// CONFIG7H
#pragma config EBTRB        = OFF           // Boot Block Table Read Protection bit (Boot Block (000000-0007FFh) not protected from table reads executed in other blocks)

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
        void ISRlow(void){
            
        }
        #pragma code
        #warning "Interrupt Service Routine LOW";
    #endif

    void OSC_CONF(void){
        
        OSCCONbits.IRCF2    = 1;    // 16Mhz VELOCIDAD PROCESSOR (OSC INTERNO)
        OSCCONbits.IRCF1    = 1;
        OSCCONbits.IRCF0    = 1;
        
        OSCCONbits.OSTS     = 0;
        OSCCONbits.SCS      = 0;    // deternima el origen del oscilador 
//        OSCTUNEbits.PLLEN   = 1;    // activa el PLL x 4
        #warning "RC_OSCILLATOR";
    }

    void CONF_PROCESSOR(void){
        OSC_CONF();
        INTERRRUPT_ON();
    }

    
    void INTERRRUPT_ON(void){
        INTCONbits.GIE      = 1;
        INTCONbits.PEIE     = 1;
        RCONbits.IPEN       = 1;
    }

    void INTERRRUPT_OFF(void){
        INTCONbits.GIE      = 0;
        INTCONbits.PEIE     = 0;
        RCONbits.IPEN       = 0;
    }

    void RESET_PROCESSOR(void){
        _asm RESET _endasm
    }

    void SLEEP_PROCESSOR(void){
        _asm SLEEP _endasm
    }
    
    void ClearWDT(void) {
        _asm CLRWDT _endasm
    }

    void IO_CONF(void){
        #if defined PIC18F_SENSOR
            ANSELA              = 0x00; // ACTIVA TODO EL PUERTO A COMO I/O DIGITALES
            ANSELB              = 0x00; // ACTIVA TODO EL PUERTO B COMO I/O DIGITALES
            ANSELC              = 0x00; // ACTIVA TODO EL PUERTO C COMO I/O DIGITALES

            TRISAbits.TRISA2    = 0;    // OSC1
            TRISAbits.TRISA3    = 0;    // SALIDA NEGATIVA
            TRISAbits.TRISA4    = 0;    // OSC2
            TRISAbits.TRISA5    = 0;    // SALIDA NEGATIVA

            TRISBbits.TRISB0    = 0;    // LED1
            TRISCbits.TRISC1    = 0;    // LED2
            TRISCbits.TRISC2    = 0;    // LED3

            TRISBbits.TRISB5    = 0;    // TXRX_EN2
            TRISCbits.TRISC5    = 0;    // TXRX_EN1

            TRISBbits.TRISB2    = 0;    // COMUNICACION1 INDICADOR
            TRISBbits.TRISB3    = 0;    // COMUNICACION2 INDICADOR

            TRISAbits.TRISA7    = 1;    // DIP_1 ENTRADA
            TRISAbits.TRISA6    = 1;    // DIP_2 ENTRADA
            TRISCbits.TRISC0    = 1;    // DIP_3 ENTRADA
            TRISCbits.TRISC3    = 1;    // DIP_4 ENTRADA
            TRISCbits.TRISC4    = 1;    // DIP_5 ENTRADA
            TRISBbits.TRISB1    = 1;    // DIP_6 ENTRADA
            TRISBbits.TRISB4    = 1;    // DIP_7 ENTRADA

            ADCON0              = 0x00; // RESETEA TODAS LAS CONFIGURACIONES ANALOGICAS
            ADCON1              = 0x00; // RESETEA TODAS LAS CONFIGURACIONES ANALOGICAS
            ADCON2              = 0x00; // RESETEA TODAS LAS CONFIGURACIONES ANALOGICAS
        #elif defined PIC18F_SUI

            ANSELA              = 0x00; // ACTIVA TODO EL PUERTO A COMO I/O DIGITALES
            ANSELB              = 0x00; // ACTIVA TODO EL PUERTO B COMO I/O DIGITALES
            ANSELC              = 0x00; // ACTIVA TODO EL PUERTO C COMO I/O DIGITALES

            TRISAbits.TRISA2    = 0;    // OSC1
            TRISAbits.TRISA3    = 0;    // SALIDA NEGATIVA
            TRISAbits.TRISA4    = 0;    // OSC2
            TRISAbits.TRISA5    = 0;    // SALIDA NEGATIVA

            TRISBbits.TRISB0    = 0;    // LED1
            TRISCbits.TRISC1    = 0;    // LED2
            TRISCbits.TRISC2    = 0;    // LED3

            TRISBbits.TRISB5    = 0;    // TXRX_EN2
            TRISCbits.TRISC5    = 0;    // TXRX_EN1

            TRISCbits.TRISC6    = 0;    // TX
            TRISCbits.TRISC7    = 0;    // RX

            TRISBbits.TRISB2    = 0;    // COMUNICACION1 INDICADOR
            TRISBbits.TRISB3    = 0;    // COMUNICACION2 INDICADOR

            TRISAbits.TRISA7    = 1;    // DIP_1 ENTRADA
            TRISAbits.TRISA6    = 1;    // DIP_2 ENTRADA
            TRISCbits.TRISC0    = 1;    // DIP_3 ENTRADA
            TRISCbits.TRISC3    = 1;    // DIP_4 ENTRADA
            TRISCbits.TRISC4    = 1;    // DIP_5 ENTRADA
            TRISBbits.TRISB1    = 1;    // DIP_6 ENTRADA
            TRISBbits.TRISB4    = 1;    // DIP_7 ENTRADA

            ADCON0              = 0x00; // RESETEA TODAS LAS CONFIGURACIONES ANALOGICAS
            ADCON1              = 0x00; // RESETEA TODAS LAS CONFIGURACIONES ANALOGICAS
            ADCON2              = 0x00; // RESETEA TODAS LAS CONFIGURACIONES ANALOGICAS
        #elif defined PIC18F_MasterSLAVE

            ANSELA              = 0x00; // ACTIVA TODO EL PUERTO A COMO I/O DIGITALES
            ANSELB              = 0x00; // ACTIVA TODO EL PUERTO B COMO I/O DIGITALES
            ANSELC              = 0x00; // ACTIVA TODO EL PUERTO C COMO I/O DIGITALES

            TRISAbits.TRISA2    = 0;    // OSC1
            TRISAbits.TRISA3    = 0;    // SALIDA NEGATIVA
            TRISAbits.TRISA4    = 0;    // OSC2
            TRISAbits.TRISA5    = 0;    // SALIDA NEGATIVA

            TRISBbits.TRISB0    = 0;    // LED1 color rojo
            TRISCbits.TRISC1    = 0;    // LED2 color verde
            TRISCbits.TRISC2    = 0;    // LED3 color azul

            TRISBbits.TRISB5    = 0;    // TXRX_EN2
            TRISCbits.TRISC5    = 0;    // TXRX_EN1

            TRISCbits.TRISC6    = 0;    // TX
            TRISCbits.TRISC7    = 0;    // RX

            TRISBbits.TRISB2    = 0;    // COMUNICACION1 INDICADOR
            TRISBbits.TRISB3    = 0;    // COMUNICACION2 INDICADOR

            TRISAbits.TRISA7    = 1;    // DIP_1 ENTRADA
            TRISAbits.TRISA6    = 1;    // DIP_2 ENTRADA
            TRISCbits.TRISC0    = 1;    // DIP_3 ENTRADA
            TRISCbits.TRISC3    = 1;    // DIP_4 ENTRADA
            TRISCbits.TRISC4    = 1;    // DIP_5 ENTRADA
            TRISBbits.TRISB1    = 1;    // DIP_6 ENTRADA
            TRISBbits.TRISB4    = 1;    // DIP_7 ENTRADA

            ADCON0              = 0x00; // RESETEA TODAS LAS CONFIGURACIONES ANALOGICAS
            ADCON1              = 0x00; // RESETEA TODAS LAS CONFIGURACIONES ANALOGICAS
            ADCON2              = 0x00; // RESETEA TODAS LAS CONFIGURACIONES ANALOGICAS

        #elif defined PIC18F_INDICADOR
            ANSELA              = 0x00; // ACTIVA TODO EL PUERTO A COMO I/O DIGITALES
            ANSELB              = 0x00; // ACTIVA TODO EL PUERTO B COMO I/O DIGITALES
            ANSELC              = 0x00; // ACTIVA TODO EL PUERTO C COMO I/O DIGITALES

            TRISBbits.TRISB0    = 0;    // LED1
            TRISCbits.TRISC1    = 0;    // LED2
            TRISCbits.TRISC2    = 0;    // LED3

            TRISBbits.TRISB2    = 1;    // COMUNICACION1 INDICADOR
            TRISBbits.TRISB3    = 1;    // COMUNICACION2 INDICADOR

            ADCON0              = 0x00; // RESETEA TODAS LAS CONFIGURACIONES ANALOGICAS
            ADCON1              = 0x00; // RESETEA TODAS LAS CONFIGURACIONES ANALOGICAS
            ADCON2              = 0x00; // RESETEA TODAS LAS CONFIGURACIONES ANALOGICAS
        #endif
    }

#endif

    

    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
//    #pragma config CP0          = ON        // Code Protection Block 0 (Block 0 (000800-001FFFh) code-protected)
//    #pragma config CP1          = ON        // Code Protection Block 1 (Block 1 (002000-003FFFh) code-protected)
//    #pragma config CP2          = ON        // Code Protection Block 2 (Block 2 (004000-005FFFh) code-protected)
//    #pragma config CP3          = ON        // Code Protection Block 3 (Block 3 (006000-007FFFh) code-protected)
//    #pragma config CPB          = ON        // Boot Block Code Protection bit (Boot block (000000-0007FFh) code-protected)
//    #pragma config CPD          = ON        // Data EEPROM Code Protection bit (Data EEPROM code-protected
//    #pragma config WRT0         = ON       // Write Protection Block 0 (Block 0 (000800-001FFFh) not write-protected)
//    #pragma config WRT1         = ON       // Write Protection Block 1 (Block 1 (002000-003FFFh) not write-protected)
//    #pragma config WRT2         = ON       // Write Protection Block 2 (Block 2 (004000-005FFFh) not write-protected)
//    #pragma config WRT3         = ON       // Write Protection Block 3 (Block 3 (006000-007FFFh) not write-protected)
//    #pragma config WRTC         = ON       // Configuration Register Write Protection bit (Configuration registers (300000-3000FFh) not write-protected)
//    #pragma config WRTB         = ON       // Boot Block Write Protection bit (Boot Block (000000-0007FFh) not write-protected)
//    #pragma config WRTD         = ON       // Data EEPROM Write Protection bit (Data EEPROM not write-protected)
//    #pragma config EBTR0        = ON        // Table Read Protection Block 0 (Block 0 (000800-001FFFh) protected from table reads executed in other blocks)
//    #pragma config EBTR1        = ON        // Table Read Protection Block 1 (Block 1 (002000-003FFFh) protected from table reads executed in other blocks)
//    #pragma config EBTR2        = ON        // Table Read Protection Block 2 (Block 2 (004000-005FFFh) protected from table reads executed in other blocks)
//    #pragma config EBTR3        = ON        // Table Read Protection Block 3 (Block 3 (006000-007FFFh) protected from table reads executed in other blocks)
//    #pragma config EBTRB        = ON        // Boot Block Table Read Protection bit (Boot Block (000000-0007FFh) protected from table reads executed in other blocks)
    
    
    
    
    
    
// **************************ORIGINAL*************************************
//    #pragma config IESO         = OFF
//    #pragma config FCMEN        = OFF
//    #pragma config PRICLKEN     = OFF
//    #pragma config PLLCFG       = OFF
//    #pragma config FOSC         = INTIO67
//    #pragma config BORV         = 190
//    #pragma config BOREN        = ON
//    #pragma config PWRTEN       = ON
//    #pragma config WDTPS        = 1
//    #pragma config WDTEN        = OFF
//    #pragma config MCLRE        = INTMCLR
//    #pragma config P2BMX        = PORTB5
//    #pragma config T3CMX        = PORTB5
//    #pragma config PBADEN       = OFF
//    #pragma config HFOFST       = ON//
//    #pragma config CCP2MX       = PORTC1
//    #pragma config CCP3MX       = PORTB5
//    #pragma config DEBUG        = OFF
//    #pragma config XINST        = OFF
//    #pragma config LVP          = ON
//    #pragma config STVREN       = ON
//    #pragma config CP1          = OFF
//    #pragma config CP0          = OFF
//    #pragma config CPD          = OFF
//    #pragma config CPB          = OFF
//    #pragma config WRT1         = OFF
//    #pragma config WRT0         = OFF
//    #pragma config WRTD         = OFF
//    #pragma config WRTB         = OFF
//    #pragma config WRTC         = OFF
//    #pragma config EBTR1        = OFF
//    #pragma config EBTR0        = OFF
//    #pragma config EBTRB        = OFF
// **************************ORIGINAL*************************************
    
    
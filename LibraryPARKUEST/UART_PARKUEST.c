#include <p18cxxx.h>
#include "PROCESSOR_PARKUEST.h"
#include "UART_PARKUEST.h"

#if defined __18F25K22_H || defined __18F24K22_H
    #if defined UART1_9bit
        void UART1_CONF_9bit(unsigned char _SPBRG1){
            SPBRG1             = _SPBRG1;
            TXSTA1bits.TX91    = 1;
            TXSTA1bits.TXEN1   = 1;
            TXSTA1bits.SYNC1   = 0;
            TXSTA1bits.BRGH1   = 1;/**************/
            RCSTA1bits.RX91    = 1;
            RCSTA1bits.CREN1   = 1;
            RCSTA1bits.ADDEN1  = 1;
            RCSTA1bits.RX9D1   = 0;
            BAUDCON1bits.BRG16 = 1;///********
            BAUDCON1bits.CKTXP = 0;
            BAUDCON1bits.DTRXP = 0;
            PIE1bits.RC1IE     = 1;
            PIE1bits.TX1IE     = 0;
            IPR1bits.RC1IP     = 1;
            TXSTA1bits.TX9D    = 1;
            TRISCbits.TRISC6   = 1;
            TRISCbits.TRISC7   = 1;
            RCONbits.IPEN      = 1;
            PMD0bits.UART1MD   = 0;
            RCSTA1bits.SPEN1   = 1;
            #warning "UART1 ACTIVATED 9bit";
        }
    #elif defined UART1_8bit
        void UART1_CONF_8bit(unsigned char _SPBRG1){
            SPBRG1             = _SPBRG1;
            TXSTA1bits.TX91    = 0;
            TXSTA1bits.TXEN1   = 1;
            TXSTA1bits.SYNC1   = 0;
            TXSTA1bits.BRGH1   = 1;/**************/
            RCSTA1bits.SPEN1   = 1;
            RCSTA1bits.RX91    = 0;
            RCSTA1bits.CREN1   = 1;
            RCSTA1bits.RX9D1   = 0;
            BAUDCON1bits.BRG16 = 1;///********
            BAUDCON1bits.CKTXP = 0;
            BAUDCON1bits.DTRXP = 0;
//            BAUDCON1bits.WUE   = 1;
            PIE1bits.RC1IE     = 1;
            PIE1bits.TX1IE     = 0;
            IPR1bits.RC1IP     = 1;
            TXSTA1bits.TX9D    = 0;
            TRISCbits.TRISC6   = 1;
            TRISCbits.TRISC7   = 1;
            RCONbits.IPEN      = 1;
            PMD0bits.UART1MD   = 0;
            #warning "UART1 ACTIVATED 8bit";
        }
    #endif
    #if defined UART2_9bit
        void UART2_CONF_9bit(unsigned char _SPBRG2){
            SPBRG2             = _SPBRG2;
            TXSTA2bits.TX92    = 1;
            TXSTA2bits.TXEN2   = 1;
            TXSTA2bits.SYNC2   = 0;
            TXSTA2bits.BRGH2   = 1;/*************/
            RCSTA2bits.RX92    = 1;
            RCSTA2bits.CREN2   = 1;
            RCSTA2bits.ADDEN2  = 1;
            RCSTA2bits.RX9D2   = 0;
            BAUDCON2bits.BRG16 = 1;/*************/
            BAUDCON2bits.CKTXP = 0;
            BAUDCON2bits.DTRXP = 0;
            PIE3bits.RC2IE     = 1;
            PIE3bits.TX2IE     = 0;
            IPR3bits.RC2IP     = 1;
            TXSTA2bits.TX9D    = 1;
            TRISBbits.TRISB6   = 1;
            TRISBbits.TRISB7   = 1;
            RCONbits.IPEN      = 1;
            PMD0bits.UART2MD   = 0;
            RCSTA2bits.SPEN2   = 1;
            #warning "UART2 ACTIVATED 9bit";
        }
    #elif defined UART2_8bit
        void UART2_CONF_8bit(unsigned char _SPBRG2){
            SPBRG2             = _SPBRG2;
            TXSTA2bits.TX92    = 1;
            TXSTA2bits.TXEN2   = 1;
            TXSTA2bits.SYNC2   = 0;
            TXSTA2bits.BRGH2   = 1;/*************/
            RCSTA2bits.RX92    = 1;
            RCSTA2bits.CREN2   = 1;
            RCSTA2bits.RX9D2   = 0;
            BAUDCON2bits.BRG16 = 1;/*************/
            BAUDCON2bits.CKTXP = 0;
            BAUDCON2bits.DTRXP = 0;
            PIE3bits.RC2IE     = 1;
            PIE3bits.TX2IE     = 0;
            IPR3bits.RC2IP     = 1;
            TXSTA2bits.TX9D    = 0;
            TRISBbits.TRISB6   = 1;
            TRISBbits.TRISB7   = 1;
            RCONbits.IPEN      = 1;
            PMD0bits.UART2MD   = 0;
            PIR3bits.RC2IF     = 0;
            RCSTA2bits.SPEN2   = 1;
            #warning "UART2 ACTIVATED 8bit";
        }

    #endif

        void UART1_OFF(void){
            RCSTA1bits.CREN1 = 0;
        }

        void UART1_ON(void){
            RCSTA1bits.CREN1 = 1;
        }

        void UART2_OFF(void){
            RCSTA2bits.CREN2 = 0;
        }

        void UART2_ON(void){
            RCSTA2bits.CREN2 = 1;
        }
#endif

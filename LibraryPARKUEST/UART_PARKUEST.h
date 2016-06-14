/* 
 * File:   UART_PARKUEST.h
 * Author: Nicolas
 *
 * Created on 20 de febrero de 2014, 08:40 PM
 */

#ifndef UART_PARKUEST_H
#define	UART_PARKUEST_H

#ifdef	__cplusplus
extern "C" {
#endif

    
//#define UART1_9bit
//#define UART1_8bit
//#define UART2_9bit
//#define UART2_8bit

#if defined UART1_9bit
    void UART1_CONF_9bit(unsigned char _SPBRG1);
#elif defined UART1_8bit
    void UART1_CONF_8bit(unsigned char _SPBRG1);
#endif
#if defined UART2_9bit
    void UART2_CONF_9bit(unsigned char _SPBRG2);
#elif defined UART2_8bit
    void UART2_CONF_8bit(unsigned char _SPBRG2);
#endif
    void UART1_OFF(void);
    void UART1_ON(void);
    void UART2_OFF(void);
    void UART2_ON(void);
#ifdef	__cplusplus
}
#endif

#endif	/* UART_PARKUEST_H */


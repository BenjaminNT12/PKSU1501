/* 
 * File:   SoftwareUART_PARKUEST.h
 * Author: Nicolas
 *
 * Created on 10 de junio de 2015, 03:45 PM
 */

#ifndef SOFTWAREUART_PARKUEST_H
#define	SOFTWAREUART_PARKUEST_H

#ifdef	__cplusplus
extern "C" {
#endif

unsigned char ReadUART2_SoftwareSync(void);
void WriteUART1_SoftwareSync(unsigned char uartdata);

#ifdef	__cplusplus
}
#endif

#endif	/* SOFTWAREUART_PARKUEST_H */


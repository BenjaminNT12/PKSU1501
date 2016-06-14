/* 
 * File:   ADC_PARKUEST.h
 * Author: Nicolas
 *
 * Created on 20 de febrero de 2014, 07:56 PM
 */

#ifndef ADC_PARKUEST_H
#define	ADC_PARKUEST_H

#ifdef	__cplusplus
extern "C" {
#endif

#define CH_AN_0     0
#define CH_AN_1     1
#define CH_AN_2     2
#define CH_AN_3     3
#define CH_AN_4     4

#define CH_AN_8     8
#define CH_AN_9     9
#define CH_AN_10    10
#define CH_AN_11    11
#define CH_AN_12    12
#define CH_AN_13    13

#define CH_AN_13    13
#define CH_AN_14    14
#define CH_AN_15    15
#define CH_AN_16    16
#define CH_AN_17    17
#define CH_AN_18    18
#define CH_AN_19    19

void AN_CONF            (void);
unsigned int StartAN    (unsigned char _AN);
void ADC_INPUT_CONFIG   (void);

#ifdef	__cplusplus
}
#endif

#endif	/* ADC_PARKUEST_H */


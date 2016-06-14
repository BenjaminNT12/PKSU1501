/* 
 * File:   SONAR_PARKUEST.h
 * Author: Nicolas
 *
 * Created on 20 de febrero de 2014, 09:28 PM
 */

#ifndef SONAR_PARKUEST_H
#define	SONAR_PARKUEST_H

#ifdef	__cplusplus
extern "C" {
#endif

#define OSC2_1              LATAbits.LATA2
#define OSC1_1              LATAbits.LATA3
#define OSC1_2              LATAbits.LATA4
#define OSC2_2              LATAbits.LATA5

#define SAMP_FREQ           2000
#define SAMP_FREQ1()        (unsigned int) SAMP_FREQ
#define SAMP_FREQ2()        (unsigned int)(SAMP_FREQ*2)

#define SAMP_NUM            32  // numero de muestras totales 128
#define SAMP_CORRECT        58 // numero minimo de muestras correctas

#define Sampling            1

#define OneSensing          1   // solo un transuctor esta sensando
#define TwoSensing          2   // ambos transductores estan sensand0
#define CorrectSensing      3   // todas las muestras fueron superadas
  
//#define METERS(x)           (((unsigned int)x*(unsigned int)700)-35)
#define METERS(x)           (((unsigned int)x*135)-35)
#define CENTIMETRES(x)      (x-35)
//#define DISTANCE(X,Y)       ((((unsigned int)(X)*(unsigned int)700)+Y)-35)
#define DISTANCE(X,Y)       ((((unsigned int)(X)*135)+Y)-35)
#define DISTANCIA           DISTANCE(1,0)
#define DISTANCIA_FREQ      100  // numero de adquisiciones del convertidor analogico digital
#define OscillationNumber   20
#define SensingSensitivity  200 // sensibilidad de sensado

typedef struct {
    unsigned char sensado_minimo[2];
    unsigned int SensingDistance;
}SONAR1;

void GEN_FREQ1                  (unsigned char _num_osc);
void GEN_FREQ2                  (unsigned char _num_osc);
BOOL SENSE_SONAR1               (void);
BOOL SENSE_SONAR2               (void);
//BOOL SENSE_SONAR1               (unsigned char _RET);
//BOOL SENSE_SONAR2               (unsigned char _RET);

unsigned char PRESENCE_SONAR1   (unsigned char *RETORNO);
unsigned char BitCont           (unsigned char buffer);
unsigned char Sensing           (void);
unsigned int AutoSetting        (void);
void SetupDISTANCE_MIN          (unsigned char meters,unsigned char centimeters);
unsigned int SenseSONAR_3_0     (void);
unsigned char PRESENCE_SONAR_3_0(unsigned int Distance);
BOOL SENSE_SONAR1_4_0           (void);
BOOL SENSE_SONAR2_4_0           (void);
unsigned char PRESENCE_SONAR_4_0(unsigned char *RETORNO);

#ifdef	__cplusplus
}
#endif

#endif	/* SONAR_PARKUEST_H */


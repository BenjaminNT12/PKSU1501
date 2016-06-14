#include <p18cxxx.h>
#include <delays.h>
#include <flash.h>
#include <GenericTypeDefs.h>
#include "PROCESSOR_PARKUEST.h"
#include "ADC_PARKUEST.h"
#include "PWM_PARKUEST.h"
#include "COLOR_PARKUEST.h"
#include "SONAR_PARKUEST.h"

#if defined __18F25K22_H || defined __18F24K22_H
#if defined PIC18F_SENSOR || defined PIC18F_SUI || defined PIC18F_MasterSLAVE
    extern SONAR1 SONAR;

    void SetupDISTANCE_MIN(unsigned char meters,unsigned char centimeters){
        SONAR.sensado_minimo[0] = meters;
        SONAR.sensado_minimo[1] = centimeters;
    }

    void GEN_FREQ1(unsigned char _num_osc) {
        unsigned char i = 0;

        _num_osc = (_num_osc * 2);
        OSC1_1 = 0;
        for (i = 0; i < _num_osc; i++) {
            Delay10TCYx(4);
            Delay1TCY();
            Delay1TCY();
            OSC1_1 = !OSC1_1;
        }
        OSC1_1 = 0;
    }

    void GEN_FREQ2(unsigned char _num_osc){
        unsigned char i = 0;

        _num_osc = (_num_osc * 2);
        OSC1_2 = 0;
        for (i = 0; i < _num_osc; i++) {
            Delay10TCYx(4);
            Delay1TCY();
            Delay1TCY();
            OSC1_2 = !OSC1_2;
        }
        OSC1_2 = 0;
    }

    BOOL SENSE_SONAR1(void) {
        unsigned int Return_AN = 0;
        unsigned int temp = 0;
        unsigned int cont1 = 0;

        Delay10TCYx(1);
        OSC1_P = 0; OSC1_N = 0; OSC2_P = 0; OSC2_N = 1;
        OSC1_1 = 0; OSC2_1 = 0; OSC1_2 = 0; OSC2_2 = 0;
        GEN_FREQ1(OscillationNumber);
        Delay1KTCYx(7);
        do {
            cont1++;
            Return_AN = StartAN(CH_AN_1);
            if (Return_AN > temp) temp = Return_AN;
        } while (cont1 < SONAR.SensingDistance);
        OSC2_N = 0;
        OSC1_1 = 0;
        OSC2_1 = 0;
        OSC1_2 = 0;
        OSC2_2 = 0;
        if (temp > SensingSensitivity) return (1);
        return(0);
        #warning "SONAR 1 ACTIVE";
    }

    BOOL SENSE_SONAR2(void) {
        unsigned int Return_AN = 0;
        unsigned int temp = 0;
        unsigned int cont1 = 0;
        
        Delay10TCYx(1);
        OSC1_P = 0; OSC1_N = 1; OSC2_P = 0; OSC2_N = 0;
        OSC1_1 = 0; OSC2_1 = 0; OSC1_2 = 0; OSC2_2 = 0;
        GEN_FREQ2(OscillationNumber);
        Delay1KTCYx(7);
        do {
            cont1++;
            Return_AN = StartAN(CH_AN_0);
            if (Return_AN > temp)temp = Return_AN;
        } while (cont1 < SONAR.SensingDistance);
        OSC1_N = 0;
        OSC1_1 = 0;
        OSC2_1 = 0;
        OSC1_2 = 0;
        OSC2_2 = 0;
        if (temp > SensingSensitivity) return (1);
        return(0);
        #warning "SONAR 2 ACTIVE";
    }
    
    unsigned char PRESENCE_SONAR1(unsigned char *RETORNO) {
        static unsigned char i = 0;
        static unsigned int k = 0;
        static UINT32_VAL SAMP32_1 = 0,SAMP32_2 = 0;
        static unsigned char SAMPLES = 0;
        BOOL FLAG1 = 0;
    
        k++;
        if(k == SAMP_FREQ1()){
            SAMP32_1.Val |= SENSE_SONAR1();
            SAMP32_1.Val = (SAMP32_1.Val << 1);
        }
    
        if(k == SAMP_FREQ2()){
            i++;
            k=0;
            SAMP32_2.Val |= SENSE_SONAR2();
            SAMP32_2.Val = (SAMP32_2.Val << 1);
        }
        
        if(i == SAMP_NUM){
    
            i = 0;
            SAMPLES = 0;
            SAMPLES += BitCont(SAMP32_1.v[0]);
            SAMPLES += BitCont(SAMP32_1.v[1]);
            SAMPLES += BitCont(SAMP32_1.v[2]);
            SAMPLES += BitCont(SAMP32_1.v[3]);
    
            SAMPLES += BitCont(SAMP32_2.v[0]);
            SAMPLES += BitCont(SAMP32_2.v[1]);
            SAMPLES += BitCont(SAMP32_2.v[2]);
            SAMPLES += BitCont(SAMP32_2.v[3]);
            FLAG1 = 1;
            if (SAMPLES >= SAMP_CORRECT){
                *RETORNO = 3;
            }
            else{
                *RETORNO = 0;
            }
        }
        if(FLAG1 == 1) {
            FLAG1 = 0;
            SAMP32_1.Val = 0;
            SAMP32_2.Val = 0;
            return(1);
        }
        return(0);
    }
    
    unsigned char Sensing(void){
        static unsigned int temporizador1 = 0;
        static unsigned int temporizador2 = 0;
        static unsigned int contadorMuestras1 = 0;
        static unsigned char RET1 = 0;
        static unsigned char RetornoSENSOR = 0;
        static BOOL flag = 0;
    
        if(flag == 0){
            temporizador1++;
            if (temporizador1 == 65000) {
                temporizador1 = 0;
                temporizador2++;
            }
        }
        if(temporizador2 == Sampling){
            flag = 1;
            temporizador2 = 0;
        }
        if(flag == 1 && RET1 != 1){
            RET1 = PRESENCE_SONAR1(&RetornoSENSOR);
            contadorMuestras1++;
        }
        if (RET1 == 1) {
            RET1 = 0;
            flag = 0;
        }
        return (RetornoSENSOR);
        #warning "Sensing SYSTEM";
    }
    
    unsigned char BitCont(unsigned char buffer) {
        unsigned char i = 0;
        unsigned char k = 0;
    
        k = 0;
        for (i = 0; i < 8; i++) {
            if ((buffer & 0x01) == 0x01) k++;
            buffer = buffer >> 1;
        }
        return (k);
    }
    
    unsigned int AutoSetting(void) {
        unsigned int Return_AN = 0;
        unsigned int ContLength = 0;
        unsigned int HIGH = 0;
        unsigned int Setting = 0;
        unsigned int temp = 0;
        unsigned char ContSamples = 0;
    
        temp = DISTANCE(SONAR.sensado_minimo[0], SONAR.sensado_minimo[1]);
        OSC1_P = 0; OSC1_N = 0; OSC2_P = 0; OSC2_N = 1;
        OSC1_1 = 0; OSC2_1 = 0; OSC1_2 = 0; OSC2_2 = 0;
        
        for (ContSamples = 0; ContSamples < 15; ContSamples++) {
            Delay10KTCYx(20);
            GEN_FREQ1(OscillationNumber);
            Delay1KTCYx(7);
            ContLength = 0;
            do {
                Return_AN = 0;
                Return_AN = StartAN(CH_AN_1);
                ContLength++;
            } while (Return_AN < 150 && ContLength < 500);
            if (ContLength > HIGH) {
                HIGH = ContLength;
            }
        }
        Setting = (HIGH - 50);
        if(Setting > temp){
            return(Setting);
        }else{
            return(temp);
        }
        #warning "AutoSentting ACTIVATED";
    }
    
    static double CalcDistance(double _Speed,double _Time) {
        double D = 0;
        
        D = _Speed * _Time;
        
        return(D);
    }
    
    static double SensePresenceDISTANCE(void) {
        static double BufferFILTER[20] = {0};
        unsigned int Return_AN = 0;
        unsigned int cont1 = 0;
        double SpeedOfSound = 332.01;
        double TimeOfProcess = 0.000035;
        double _Time = 0;
        double Sum = 0;
        double R = 0;
        
        Delay10TCYx(1);
        OSC1_P = 0; OSC1_N = 1; OSC2_P = 0; OSC2_N = 0;
        OSC1_1 = 0; OSC2_1 = 0; OSC1_2 = 0; OSC2_2 = 0;
        GEN_FREQ2(OscillationNumber); 
        Delay1KTCYx(7);
        do {
            cont1++;
            _Time += TimeOfProcess;
            Return_AN = StartAN(CH_AN_0);
        } while (cont1 < SONAR.SensingDistance && Return_AN < SensingSensitivity);
        BufferFILTER[19] = _Time;
        for (cont1 = 0; cont1 < 20; cont1++) Sum += BufferFILTER[cont1];
        for (cont1 = 0; cont1 < 19; cont1++) BufferFILTER[cont1] = BufferFILTER[cont1 + 1];
        Sum /= 20;
        R = CalcDistance(SpeedOfSound,Sum);
        return(R);
    }

    unsigned int SenseSONAR_3_0(void) {
        double SenseSONAR_3 = 0;
        double SenseSONAR_4 = 0;
        unsigned int R_1 = 0;
        
        SenseSONAR_3 = SensePresenceDISTANCE();
        SenseSONAR_4 = (double)100 * SenseSONAR_3;
        
        R_1 = (unsigned int )SenseSONAR_4;
        if (R_1 > 1024)R_1 = 1023;
        return(R_1);
    }

    unsigned char PRESENCE_SONAR_3_0(unsigned int Distance) {
        static unsigned int Distance_3_0[20] = {0};
        static unsigned int Count2 = 0;
        static unsigned char Count3 = 0;
        unsigned int Sum_3_0 = 0;
        unsigned char i_3_0 = 0;

        if(Count2 == 100){
            if (Count3 < 3) {
                Distance_3_0[19] = SenseSONAR_3_0();
                for (i_3_0 = 0; i_3_0 < 20; i_3_0++) Sum_3_0 += Distance_3_0[i_3_0];
                for (i_3_0 = 0; i_3_0 < 19; i_3_0++) Distance_3_0[i_3_0] = Distance_3_0[i_3_0 + 1];
                Sum_3_0 /= 20;
                if (Distance > Sum_3_0) {return (3);} 
                else {return (0);}
            }
            Count3++;
            if(Count3 == 3){
                Count2 = 0;
                Count3 = 0;
            }
        }else{
            Count2++;
        }    
    }
    
    BOOL SENSE_SONAR1_4_0(void) {
        unsigned int Return_AN = 0;
        unsigned int temp = 0;
        unsigned int cont1 = 0;
        unsigned char cont2 = 0;
        static unsigned int BufferRET[20] = {0};
        static unsigned int SumBR = 0;

        Delay10TCYx(1);
        OSC1_P = 0; OSC1_N = 0; OSC2_P = 0; OSC2_N = 1;
        OSC1_1 = 0; OSC2_1 = 0; OSC1_2 = 0; OSC2_2 = 0;
        GEN_FREQ1(OscillationNumber);
        Delay1KTCYx(7);
        do {
            cont1++;
            Return_AN = StartAN(CH_AN_1);
            if (Return_AN > temp) temp = Return_AN;
        } while (cont1 < SONAR.SensingDistance);
        OSC2_N = 0;
        OSC1_1 = 0;
        OSC2_1 = 0;
        OSC1_2 = 0;
        OSC2_2 = 0;
        BufferRET[19] = temp;
        for (cont2 = 0; cont2 < 20; cont2++)SumBR += BufferRET[cont2];
        for (cont2 = 0; cont2 < 19; cont2++)BufferRET[cont2] = BufferRET[cont2 + 1];
        SumBR /= 20;
        if (SumBR < (SensingSensitivity - 20)) SumBR += 20;
        if (SumBR > SensingSensitivity) return (1);
        return(0);
        #warning "SONAR 1 ACTIVE";
    }
    
    BOOL SENSE_SONAR2_4_0(void) {
        unsigned int Return_AN = 0;
        unsigned int temp = 0;
        unsigned int cont1 = 0;
        unsigned char cont2 = 0;
        static unsigned int BufferRET2[20] = {0};
        static unsigned int SumBR2 = 0;        
        
        Delay10TCYx(1);
        OSC1_P = 0; OSC1_N = 1; OSC2_P = 0; OSC2_N = 0;
        OSC1_1 = 0; OSC2_1 = 0; OSC1_2 = 0; OSC2_2 = 0;
        GEN_FREQ2(OscillationNumber);
        Delay1KTCYx(7);
        do {
            cont1++;
            Return_AN = StartAN(CH_AN_0);
            if (Return_AN > temp)temp = Return_AN;
        } while (cont1 < SONAR.SensingDistance);
        OSC1_N = 0;
        OSC1_1 = 0;
        OSC2_1 = 0;
        OSC1_2 = 0;
        OSC2_2 = 0;
        BufferRET2[19] = temp;
        for (cont2 = 0; cont2 < 20; cont2++)SumBR2 += BufferRET2[cont2];
        for (cont2 = 0; cont2 < 19; cont2++)BufferRET2[cont2] = BufferRET2[cont2 + 1];
        SumBR2 /= 20;
        if (SumBR2 < (SensingSensitivity - 20)) SumBR2 += 20;
        if (SumBR2 > SensingSensitivity) return (1);        
        return(0);
        #warning "SONAR 2 ACTIVE";
    }
    
    unsigned char PRESENCE_SONAR_4_0(unsigned char *RETORNO) {
        static unsigned char i = 0;
        static unsigned int k = 0;
        static UINT32_VAL SAMP32_1 = 0,SAMP32_2 = 0;
        static unsigned char SAMPLES = 0;
        BOOL FLAG1 = 0;
        
        k++;
        if(k == SAMP_FREQ1()){
            SAMP32_1.Val |= SENSE_SONAR1_4_0();
            SAMP32_1.Val = (SAMP32_1.Val << 1);
        }
        
        if(k == SAMP_FREQ2()){
            i++;
            k = 0;
            SAMP32_2.Val |= SENSE_SONAR2_4_0();
            SAMP32_2.Val = (SAMP32_2.Val << 1);
        }
        
        if(i == SAMP_NUM){
        
            i = 0;
            SAMPLES = 0;
            SAMPLES += BitCont(SAMP32_1.v[0]);
            SAMPLES += BitCont(SAMP32_1.v[1]);
            SAMPLES += BitCont(SAMP32_1.v[2]);
            SAMPLES += BitCont(SAMP32_1.v[3]);
            
            SAMPLES += BitCont(SAMP32_2.v[0]);
            SAMPLES += BitCont(SAMP32_2.v[1]);
            SAMPLES += BitCont(SAMP32_2.v[2]);
            SAMPLES += BitCont(SAMP32_2.v[3]);
            FLAG1 = 1;
            if (SAMPLES >= SAMP_CORRECT){
                *RETORNO = 3;
            }
            else{
                *RETORNO = 0;
            }
        }
        if(FLAG1 == 1) {
            FLAG1 = 0;
            SAMP32_1.Val = 0;
            SAMP32_2.Val = 0;
            return(1);
        }
        return(0);
    }    
    
    #endif
#endif


    
    
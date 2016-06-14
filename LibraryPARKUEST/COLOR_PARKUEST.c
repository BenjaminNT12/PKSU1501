#include <p18cxxx.h>
#include <delays.h>
#include "PROCESSOR_PARKUEST.h"
#include "PWM_PARKUEST.h"
#include <GenericTypeDefs.h>
#include "COLOR_PARKUEST.h"

#if defined __18F25K22_H || defined __18F24K22_H
    #if defined PIC18F_INDICADOR || defined PIC18F_SUI || defined PIC18F_MasterSLAVE
        extern COLOR COLORS;

            void RGB_8bit(unsigned char _RED,unsigned char _GREEN,unsigned char _BLUE){
                RED_DUTY((unsigned int)_RED*4);
                GREEN_DUTY((unsigned int)_GREEN*4);
                BLUE_DUTY((unsigned int)_BLUE*4);
                #warning"RGB 8 BITS";
            }

            void RGB_10bit(unsigned int _RED,unsigned int _GREEN,unsigned int _BLUE){
                RED_DUTY(_RED);
                GREEN_DUTY(_GREEN);
                BLUE_DUTY(_BLUE);
                #warning"RGB 10 BITS";
            }

            void ChangeFadeCOLOR(unsigned char _RED0,unsigned char _GREEN0,unsigned char _BLUE0,unsigned char _RED1,unsigned char _GREEN1,unsigned char _BLUE1) {
                unsigned char RED_C = 0;
                unsigned char GREEN_C = 0;
                unsigned char BLUE_C = 0;
                unsigned char i = 0;

                RED_C   = _RED0;
                GREEN_C = _GREEN0;
                BLUE_C  = _BLUE0;

                for (i = 0; i < 255; i++) {
                    if(RED_C < _RED1) RED_C++;
                    else if(RED_C > _RED1) RED_C--;
                    if(GREEN_C < _GREEN1) GREEN_C++;
                    else if(GREEN_C > _GREEN1) GREEN_C--;
                    if(BLUE_C < _BLUE1) BLUE_C++;
                    else if(BLUE_C > _BLUE1) BLUE_C--;
                    Delay1KTCYx(30);
                    RGB_8bit(RED_C,GREEN_C,BLUE_C);
                }
                #warning "RGB COLOR";
            }

            void ChangeFadeCOLOR_FAST(unsigned char _RED0,unsigned char _GREEN0,unsigned char _BLUE0,unsigned char _RED1,unsigned char _GREEN1,unsigned char _BLUE1){
                unsigned char RED_C = 0;
                unsigned char GREEN_C = 0;
                unsigned char BLUE_C = 0;
                unsigned char i = 0;

                RED_C   = _RED0;
                GREEN_C = _GREEN0;
                BLUE_C  = _BLUE0;

                for (i = 0; i < 255; i++) {
                    if(RED_C < _RED1) {RED_C++;}
                    else if(RED_C > _RED1) {RED_C--;}
                    if(GREEN_C < _GREEN1) {GREEN_C++;}
                    else if(GREEN_C > _GREEN1) {GREEN_C--;}
                    if(BLUE_C < _BLUE1) {BLUE_C++;}
                    else if(BLUE_C > _BLUE1) {BLUE_C--;}
                    Delay1KTCYx(10);
                    RGB_8bit(RED_C,GREEN_C,BLUE_C);
                }
            }

            BOOL ChangeFadeCOLOR1(unsigned char _RED0,unsigned char _GREEN0,unsigned char _BLUE0,unsigned char _RED1,unsigned char _GREEN1,unsigned char _BLUE1){
                static unsigned int i = 0;
                static unsigned char RED_C = 0;
                static unsigned char GREEN_C = 0;
                static unsigned char BLUE_C = 0;
                static BOOL FLAG = 0;

                if(i==0 && FLAG == 0){
                    RED_C   = _RED0;
                    GREEN_C = _GREEN0;
                    BLUE_C  = _BLUE0;
                    FLAG=1;
                }

                if (i == 500) {
                    i = 0;
                    if(_RED0 < _RED1){RED_C++;}
                    else if(_RED0 > _RED1){RED_C--;}
                    if(_GREEN0 < _GREEN1){GREEN_C++;}
                    else if(_GREEN0 > _GREEN1){GREEN_C--;}
                    if(_BLUE0 < _BLUE1){BLUE_C++;}
                    else if(_BLUE0 > _BLUE1) {BLUE_C--;}
                    RGB_8bit(RED_C,GREEN_C,BLUE_C);
                }
                i++;
                if(RED_C == _RED1 && GREEN_C == _GREEN1 && RED_C == _RED1){
                    FLAG=0;
                    return(1);
                }
                return(0);
            }

            BOOL COLOR_ROUTINE1(unsigned char _RED,unsigned char _GREEN,unsigned char _BLUE){
                static unsigned int i = 0;
                static unsigned char R = 0;
                static unsigned char G = 0;
                static unsigned char B = 0;

                if (i == 0) {
                    R = 0;
                    B = 0;
                    G = 0;
                }
                if (i == 500) {
                    i=0;
                    if(_RED > 0){R++;}
                    if(_GREEN > 0){G++;}
                    if(_BLUE > 0){B++;}
                    RGB_8bit(R,G,B);
                }
                i++;
                if (R == _RED && G == _GREEN && B == _BLUE){return(1);}
                return(0);
            }

            void COLOR_ROUTINE2(unsigned char _RED,unsigned char _GREEN,unsigned char _BLUE) {
                static unsigned char cont2 = 0;
                static unsigned char R = 0;
                static unsigned char G = 0;
                static unsigned char B = 0;

                if (cont2 == 200)cont2 = 0;

                if (cont2 < 100) {
                    if(_RED > 0){R++;}
                    if(_GREEN > 0){G++;}
                    if(_BLUE > 0){B++;}
                    RGB_8bit(R,G,B);
                }
                else{
                    if(_RED>0){R--;}
                    if(_GREEN>0){G--;}
                    if(_BLUE >0){B--;}
                    RGB_8bit(R,G,B);
                }
                cont2++;
            }

            void COLOR_ROUTINE3(unsigned char _RED,unsigned char _GREEN,unsigned char _BLUE) {
                static unsigned int cont3 = 0;
                static unsigned char R = 0;
                static unsigned char G = 0;
                static unsigned char B = 0;

                if(R == 0 && G == 0 && B == 0){
                    R=_RED;
                    G=_GREEN;
                    B=_BLUE;
                }
                if (cont3 == COLORS.SPEED) {
                    cont3=0;
                    if(R > 0){R--;}
                    if(G > 0){G--;}
                    if(B > 0){B--;}
                    RGB_8bit(R,G,B);
                }
                cont3++;
            }

            void COLOR_ROUTINE4(unsigned char _RED,unsigned char _GREEN,unsigned char _BLUE){
                unsigned char i = 0;
                static unsigned char R = 0;
                static unsigned char G = 0;
                static unsigned char B = 0;

                for (i = 0; i < 255; i++) {
                    if(_RED > 0){R++;}
                    if(_GREEN > 0){G++;}
                    if(_BLUE > 0){B++;}
                    RGB_8bit(R, G, B);
                    Delay1KTCYx(20);
                }
                for (i = 0; i < 255; i++) {
                    if(_RED>0){R--;}
                    if(_GREEN>0){G--;}
                    if(_BLUE >0){B--;}
                    RGB_8bit(R,G,B);
                    Delay1KTCYx(20);
                }
            }

            void COLOR_ROUTINE5(unsigned char _RED,unsigned char _GREEN,unsigned char _BLUE){
                static unsigned int cont3=0;
                static unsigned char R=0;
                static unsigned char G=0;
                static unsigned char B=0;

                if (cont3 == 0) {
                    R = _RED;
                    G = _GREEN;
                    B = _BLUE;
                }
                if (cont3 == 70) {
                    cont3 = 0;
                    if(_RED > 0)    {R--;}
                    if(_GREEN > 0)  {G--;}
                    if(_BLUE > 0)   {B--;}
                    RGB_8bit(R,G,B);
                }
                cont3++;
            }

            void SetupCOLOR_ACTIVE(unsigned char _R, unsigned char _G, unsigned char _B){
                COLORS.RED_A    = _R;
                COLORS.GREEN_A  = _G;
                COLORS.BLUE_A   = _B;
            }

            void SetupCOLOR_N_ACTIVE(unsigned char _R, unsigned char _G, unsigned char _B){
                COLORS.RED_D    = _R;
                COLORS.GREEN_D  = _G;
                COLORS.BLUE_D   = _B;
            }

        #endif
#endif

    
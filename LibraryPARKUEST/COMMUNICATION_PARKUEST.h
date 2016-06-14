/* 
 * File:   COMMUNICATION_PARKUEST.h
 * Author: Nicolas
 *
 * Created on 1 de marzo de 2014, 10:59 AM
 */

#ifndef COMMUNICATION_PARKUEST_H
#define	COMMUNICATION_PARKUEST_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <GenericTypeDefs.h>

//#define COMMUNICATION_V1
//#define COMMUNICATION_V2
#define ISRHIGH
//#define ISRLOW


#define REMAPPED_HIGH_INTERRUPT_VECTOR_ADDRESS  0x0008
#define REMAPPED_LOW_INTERRUPT_VECTOR_ADDRESS   0x0018
    
#define BUS1_free()         (PIR1bits.TXIF && !PIR1bits.RCIF && BAUD1CONbits.RCIDL)
#define BUS1_busy()         (!TXSTA1bits.TRMT)

#define BUS2_free()         (PIR3bits.TX2IF && !PIR3bits.RC2IF && BAUD2CONbits.RCIDL)
#define BUS2_busy()         (!TXSTA2bits.TRMT)

#if defined UART1_9bit || defined UART1_8bit
    #define BUS_SLAVE
#endif
#if defined UART2_9bit || defined UART2_8bit
    #define BUS_MASTER
#endif



#if defined COMMUNICATION_V1
    #define MASTER_ID    0x40
    #define SLAVE_ID     0x01

    #define CMD1_PARKUEST       0x02   // ESCLAVO ENVIA ESTADO
    #define CMD2_PARKUEST       0x07   // MASTER Y/O MASTER_SLAVE INICIALIZA ESCLAVO
    #define CMD3_PARKUEST       3   // MASTER_SLAVE PIDE ESTADO
    #define CMD4_PARKUEST       4   // MASTER_SLAVE ENVIA TABLA DE ESTADO
    #define CMD5_PARKUEST       5   // MASTER_SLAVE/MASTER ACTUALIZA PANTALLA
    #define CMD6_PARKUEST       0x03// RESPUESTA DE CONFIRMACION
    #define CMD7_PARKUEST       7   // 
    #define CMD8_PARKUEST       8   //
    #define CMD9_PARKUEST       9   //
    #define CMD10_PARKUEST      10  //
#elif defined COMMUNICATION_V2

    #define CMD1_PARKUEST                       1     // ESCLAVO ENVIA ESTADO comando que contiene el estado del sensor que envia
    #define CMD2_PARKUEST                       2     // MASTER Y/O MASTER_SLAVE INICIALIZA ESCLAVO comando de inicializacion
    #define CMD3_PARKUEST                       3     // MASTER_SLAVE PIDE ESTADO comando de bus MASTER el master principal debe enviar este comando para que el master-slave se los envia a los demas sensores
    #define CMD4_PARKUEST                       4     // MASTER_SLAVE ENVIA TABLA DE ESTADO comando de bus MASTER el master ´principal debe enviar este comando para que el master-slave le envie la tabla de estado de todos los sensores
    #define CMD5_PARKUEST                       5     // MASTER_SLAVE/MASTER ACTUALIZA PANTALLA comando para actualizar pantalla
    #define CMD6_PARKUEST                       6     // RESPUESTA DE CONFIRMACION
    #define CMD7_PARKUEST                       7     // REQUEST Initialization PARKUEST
    #define CMD8_PARKUEST                       8     // ACTUALIZACION DE COLORES PARA SENSOR/INDICADOR ACTIVO comando para actualizar los colores del sensor cuando esta ACTIVO
    #define CMD9_PARKUEST                       9     // ACTUALIZACION DE COLORES PARA SENSOR/INDICADOR DESACTIVADO // comando de bus MASTER comando para actualizar los colores del sensor cuando esta DESACTIVADO
    #define CMD10_PARKUEST                      10    // TIPO DE SECUENCIA ACTIVO
    #define CMD11_PARKUEST                      11    // TIPO DE SECUENCIA DESACTIVADO
    #define CMD12_PARKUEST                      12    // DISTANCIA MINIMA DE SENSADO
    #define CMD13_PARKUEST                      13    // AUTOAJUSTE
    #define CMD14_PARKUEST                      14    // RESPUESTA DE INICIALIZACION SENSOR
    #define CMD15_PARKUEST                      15    // ACTUALIZA LA VELOCIDAD DE LA RUTINA
    #define CMD16_PARKUEST                      16    // RESPUESTA DE INICIALIZACION MS2
    #define CMD17_PARKUEST                      17    // RESPUESTA DE INICIALIZACION PANTALLA
    #define CMD18_PARKUEST                      18    // VERIFICA SALUD DE SENSORES
    #define CMD19_PARKUEST                      19    // ENVIO DE CUALQUIER COMANDO, A NIVELES INFERIORES
    #define CMD20_PARKUEST                      20    // CAMBIO DE ID DE SLAVE
    #define CMD21_PARKUEST                      21    // RESET ID HARDWARE
    #define CMD22_PARKUEST                      22    // APAGAR EL INDICADOR INTEGRADO
    #define CMD23_PARKUEST                      23    // ENCENDER EL INDICADOR INTEGRADO
    #define CMD24_PARKUEST                      24    // AGREGAR SENSORES AL INDICADOR COMPARTIDOR
    #define CMD25_PARKUEST                      25    // ELIMINAR SENSORES A LA CONFIGURACION DE INDICADOR COMPARTIDO

    #define CMD_STOP_SYSTEM_PARKUEST            255   // COMANDO PARA DETENER EL FUNCIONAMIENTO DEL SYSTEMA PARKUEST
    #define CMD_TEMPORARY_STOP_SYSTEM_PARKUEST  254   // COMANDO PARA DETENER TEMPORALMETE EL SYSTEMA PARKUEST
    #define CMD_REESTART_SYSTEM_PARKUEST        253   // COMANDO PARA REINICIAR EL SYSTEMA PARKUEST
    #define CMD_ONLY_ROUTINE_PARKUEST           252   // COMANDO PARA QUE EXISTA SOLO LA RUTINA SIN SENSAR
    #define CMD_ONLY_SENSE_PARKUEST             251   // COMANDO PARA SOLO SENSAR SIN RUTINA
    #define CMD_ReSTART                         250   // COMANDO PARA SOLO SENSAR SIN RUTINA

    #define ID_MAIN_SCREEN_1                    0xBB
    #define ID_MAIN_SCREEN_2                    0xCC
    #define ID_MAIN_SCREEN_BROADCAST            0xDD

    #define MASTER_BUS                          0
    #define SLAVE_BUS                           1

    #define STOP_COMMUNICATION                  0x8A  // BYTE PARA RECONOCIENTO DE PARO DE COMUNICAION
    #define STOP_COMMUNICATION2                 0x44  // BYTE2 PARA RECONOCIENTO DE PARO DE COMUNICAION
    #define TIEMPO_ESPERA_RESPUESTA             5

    #define MASTER_ID                           0xE1  // BYTE PARA EL ID DEL BUS MASTER
//    #define MASTER_ID                           0x59  // BYTE PARA EL ID DEL BUS MASTER
    #define MasterS_SLAVE_ID                    0x01  // ID POR SOFTWARE
    #define BROADCAST                           0xAA  // ID PARA HACER BROADCAST

    #define SensorNUMBER                        128   //-->255

//    #define UsingDisplay(x,y)   Send_DISPLAY_BusMaster(x,y)
    #define UsingDisplay(x,y)   Send_DISPLAY_BusSlave(x,y)

#endif

#if defined COMMUNICATION_V2 || defined COMMUNICATION_V1
    typedef union {
        struct{
            unsigned char val;
        };
        struct{
            unsigned D1:1;
            unsigned D2:1;
            unsigned D3:1;
            unsigned D4:1;
            unsigned D5:1;
            unsigned D6:1;
            unsigned D7:1;
            unsigned D8:1;
        };
    }Val_Data;

    typedef struct {
       unsigned char IDR;
       unsigned char IDT1;
       unsigned char IDT2;
       unsigned char CMD;
       Val_Data Data[65];
       unsigned char STOP;
       unsigned char ChS;
       unsigned DataReceived:1;
       unsigned ChecksumCORRECT:1;
//       unsigned StateConfirmation:1;
       unsigned TimeOut1:1;
       unsigned TimeOut2:1;
    }Bus_Data;

   typedef union {
        struct{
            unsigned char VAL;
        };
        struct{
            unsigned BIT_0:1;
            unsigned BIT_1:1;
            unsigned BIT_2:1;
            unsigned BIT_3:1;
            unsigned BIT_4:1;
            unsigned BIT_5:1;
            unsigned BIT_6:1;
            unsigned BIT_7:1;
        };
    }ID_PARKUEST;
 
    typedef struct {
        unsigned OnlyOneIndicatorActive:1;
        unsigned SLAVE_ACTIVE:1;
        unsigned MASTERSLAVE_ACTIVE:1;
        unsigned INDICATOR_ACTIVE:1;
        unsigned busMASTER:1;
        unsigned StartCommMASTER:1;
        unsigned StartCommSLAVE:1;
        unsigned busSLAVE:1;
        unsigned ChangeSTATE:1;
        unsigned SensorACTIVE:1;
        unsigned FlagTimerRemaining1:1;
        unsigned FlagTimerRemaining2:1;
        unsigned FlagTimerRemaining3:1;
        unsigned FlagTimerRemaining4:1;
        unsigned SENSOR:1;
        unsigned NOT_SENSE:1;
        unsigned IndicatorINTEGRATED_OnOff:1;
//        unsigned Ready_to_SEND;
        unsigned char StateSONAR;
        unsigned char ContSendPending;
        unsigned char NumberSLAVEs_REGISTER;
        unsigned char NumberSLAVEs_ACTIVES;
        unsigned int NumberSLAVEs_DISPLAY;
        unsigned char Number_DISPLAY;
        unsigned char OnlyOneIndicatorDATA[16];
        unsigned char OnlyOneIndicatorSENSORES[16];
//        unsigned int Delay_to_SEND;
    }FLAGs;

#endif

#if defined COMMUNICATION_V2 || defined COMMUNICATION_V1
    #if defined BUS_SLAVE
        void SendDATA1              (Bus_Data *num_bus); 
        unsigned char wait_1        (unsigned int wait1); 
    #endif
    #if defined BUS_MASTER
        void SendDATA2              (Bus_Data *num_bus); 
        unsigned char wait_2        (unsigned int wait2); 
    #endif
    unsigned char CALCULATE_ChS     (Bus_Data *num_bus);
    BOOL CheckSUM_CORRECT           (Bus_Data *num_bus);
    unsigned char CALCULATE_ID_7bit (void); 
    unsigned char CALCULATE_ID_8bit (void);
#endif
    BOOL Waiting_Initialization     (Bus_Data *num_bus); 
#if defined PIC18F_MasterSLAVE
    BOOL Check_List                 (Bus_Data *num_bus);
    void STATE_OF_SLAVEs            (void); 
    unsigned char STATE_SLAVE       (unsigned char NUM_slave); 
    void Transmission_ConfirmationBUSslave(Bus_Data *num_bus_R,Bus_Data *num_bus_T); 
    void Send_Initialization        (void); 
    void Send_Initialization_Master (void); 
    BOOL Waiting_Initialization_PARKUEST(void); 
    void Request_Initialization_SLAVE(BOOL _BUS); 
    void Task_UART_MasterSLAVE      (Bus_Data *num_bus); 
    void Task_UART_Slave            (Bus_Data *num_bus); 
    void Data_Migration             (Bus_Data *num_bus); 
    void Send_TABLE                 (void); 
    BOOL CLEAR_BUFFER               (unsigned char *_buffer,unsigned char _val,unsigned char _lengh);
    BOOL DelayedStart               (unsigned char _Delayed);
    void State_INDICATOR            (void);
    void SLAVEs_INITIALIZATION      (void);
    unsigned char BitCont2          (unsigned char buffer);
    void Response_Initialization    (void);
    unsigned char CONT_SLAVES_REGISTERED(void);
    unsigned char CONT_SLAVE_ACTIVE (void);
    void SLAVE_TASKS                (void);
    void MASTER_SLAVE_TASKS         (void);
    void INDICATOR_TASKS            (void);
    void TEST_COMUNICACION          (void);
    BOOL Check_HEALTH               (Bus_Data *num_bus);
//    BOOL Delay_to_SEND              (void);
    void test_reception             (void);
    void Send_DISPLAY_BusSlave      (unsigned char address,unsigned int buffer);
    void Send_DISPLAY_BusMaster     (unsigned char address,unsigned int buffer);
    BOOL DelayedStartMaster         (unsigned char _Delayed);
    unsigned char CALCULATE_ID_SOFTWARE_7bit(unsigned char Master_Slave, unsigned char _ID);
    unsigned char CALCULATE_ID_SOFTWARE_8bit(unsigned char Master_Slave_TYPE, unsigned char _ID);
    unsigned char LoadState         (unsigned char *Storage, unsigned char Position);
    void SaveInBits                 (unsigned char *Storage, unsigned char Position, unsigned char StateBit);
    void OnlyOneIndicatorIdSensors  (unsigned char NumberOfArg, ...);
    unsigned char OnlyOneIndicator  (unsigned char NumberOfSensor, unsigned char State);
    void ResetVariables             (void);
#endif
#ifdef	__cplusplus
}
#endif

#endif	/* COMMUNICATION_PARKUEST_H */


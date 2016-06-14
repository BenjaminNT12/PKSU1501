/*******************************************************************************
 *  NO BORRAR ESTA CABECERA, ESTE SOFTWARE PERTENECE A "PARKUEST SAPI DE CV."
 * TODO CAMBIO DEBE SER REGISTRADO EN ESTA, ADEMAS DEL AUTOR, FECHA Y DESCRIPCION
 * DE LA ACTUALIZACION.
 * LA DISTRIBUCION DE ESTE SOFTWARE ES BAJO RESPONSABILIDAD DE PARKUEST SAPI DE CV.
 * 
 * File:   PIC18F_SIM_2_0_4.c
 *
 * PARKUEST.COM 
 * Descripcion: Sensor Ultrasonico, Indicador integrado, controlador de indicador
 * independiente y MaestroSensor.
 * Autor: Nicolas
 * Firmware: PKSIM2.0.2022016
 * Tipo de procesador: PIC18F25K22 Microchip Technology Inc.
 * Velocidad de procesador: 16MHz
 * 
 * Colores Estadar
 * RED6();
 * GREEN();
 * BLUE();
 *
 * BITACORA DE ACTUALIZACIONES.
 * Created on 10 de mayo de 2014
 * - modificaciones 
 * Revision 10 de junio de 2014
 * - modificaciones 
 * -->se diseño el sistema de deteccion 
 * Revision 15 de junio de 2014
 * - modificaciones 
 * -->se activan los PWM
 * Revision 19 de junio de 2014
 * - modificaciones 
 * -->se agregan macros para colores
 * Revision 4 de agosto de 2014
 * - modificaciones 
 * -->se termina el sistema de comunicaciones
 * Revision 5 de septiembre de 2014
 * - modificaciones 
 * -->se reparan errores en la comunicacion 
 * Revision 23 de septiembre de 2014
 * - modificaciones 
 * -->se agregan el sistema para ajuste automatico
 * Revision 17 de octubre de 2014
 * - modificaciones 
 * -->se agregan funciones para ajuste remoto
 * Revision 15 de noviembre de 2014
 * - modificaciones 
 * -->se prueban y se activan reset por software
 * -->se prueban y se activan sleep por software
 * Revision 3 de diciembre de 2014
 * - modificaciones 
 * --> se reparan errores aleatorios
 * Revision 22 de enero de 2015
 * - modificaciones 
 * --> se mejora el sistema de deteccion 
 * Revision 25 de enero de 2015
 * - modificaciones 
 * --> se detecta el color prohibido 
 * Revision 1 de febrero de 2015
 * - modificaciones 
 * --> se reduce el numero de colores y se modifica la cantidad de bits
 * Revision 12 de febrero de 2015
 * - modificaciones 
 * --> se activa y prueba la configuracion de colores remota
 * Revision 23 de febrero de 2015
 * - modificaciones 
 * --> se activa el sensor indicador independiente
 * Revision 17 de Marzo de 2015
 * - modificaciones 
 * --> Se programa el sistema de encendido remoto
 * Revision 24 de Marzo de 2015
 * - modificaciones 
 * --> No se registraba el MasterSlave como sensor
 * Revision 5 de Abril de 2015
 * - modificaciones 
 * --> se prueba el inicio por medio de Master
 * Revision 16 de Abril de 2015
 * - modificaciones 
 * --> se modifican el tamaño de los buffers para un mayor numero de sensores
 * --> se reduce el numero memoria utilizada
 * --> se aumenta la velocidad del procesador
 * Revision 2 de Mayo de 2015
 * - modificaciones 
 * El procesador se queda en "pausa" solucionado
 * Revision 11 de Junio de 2015
 * - modificaciones
 * --> Cambio de colores por uart por software
 * --> El sensor sin indicador, no se apagaba
 * Revision 02 de septiembre de 2015
 * - modificaciones
 * --> ninguna
 * Revision 03 de septiembre de 2015
 * - modificaciones
 * --> El indicador integrado guarda su configuracion pero a la hora de ejecutarlo de nuevo las
 * salidas se mantienen en un estado aleatorio
 *  Revision 12 de Septiembre de 2015 
 * -modificaciones
 * --> las salidas de los pwm se apagan correctamente.
 *  Revision 15 de Septiembre de 2015 
 * -modificaciones
 * --> Las salidas del sonar se ponen en estado cero para evitar el drenado de corriente 
 *  Revision 18 de Septiembre de 2015 
 * -modificaciones
 * --> se modifico el sistema de muestreo para la deteccion 
 *  Revision 13 de Octubre de 2015 
 * -modificaciones
 * --> Se agrego sistema para compartir un solo indicador
 *  Revision 16 de Octubre de 2015 
 * -modificaciones
 * --> Se agrego configuracion remota de indicador compartido
 * --> Se agregaron medidas de seguridad en comunicacion RS485
 * --> se agrego almacenamiento de configuracion de indicador compartido
 * --> Se logro aumentar el nivel de procesamiento del Core del procesador(retirada)
 *  Revision 23 de Noviembre de 2015 
 * -modificaciones
 * --> Se modifico la direccion de la pantalla por default
 *  Revision 23 de Noviembre de 2015 
 * -modificaciones
 * --> Se cambiaron estructuras por datos definidos
 *  Revision 26 de Noviembre de 2015 
 * -modificaciones
 * --> Se cambio a entero la varible para envio de la pantalla* 
 *  Revision 30 de Diciembre de 2015 
 * -modificaciones
 * --> Se hizo la revision del sistema para calcular direcciones
 * --> Se cambio a direcciones de 8 bits (FUTURA ACTUALIZACION DE HARDWARE no 
 *     disponible en version PKSU1501)
 *  Revision 21 de Enero de 2016 
 * -modificaciones
 * --> cuando se hace la peticion de inicializacion se hace un flasheo de 200 mS en color Azul 
 *  Revision 1 de Febrero de 2016 
 * -modificaciones
 * --> Cuando el indicador se apagaba en modo masterSlave apagaba el timer0 y eso impedia el envio de los datos
 *  Revision 2 de Febrero de 2016 
 * -modificaciones
 * --> Problema de Stop en la comunicacion Stop_communication
 *  Revision 6 de Febrero de 2016 
 * -modificaciones
 * --> se agrego la funcion de indicador compartido para el masterSlave
 * --> se modifico el envio de parametros desde masterSlave a sensores para el 
 *     indicador compartido
 * --> se agregaron los comandos 24 y 25 y se modificaron los comandos en la 
 *     seccion masterSlave
 * --> se agrego la bandera que activa el indicador compartido para todo 
 *     el sistema y discrimina funciones de indicador compartido y de 
 *     masterslave
 * --> se modificaron los tiempos de inicio 
 * --> se mejoro la administracion de los tiempos del sistema
 *  Revision 8 de Febrero de 2016 
 * - modificaciones
 * --> Se soluciono un error que no permitia la configuracion via remota del indicador compartido
 *  Revision 16 de Febrero de 2016 
 * - modificaciones
 * --> Se diseño un filtro para el buffer del canal analogico pueda resistir las
 *     corrientes de aire.
 * --> Se modificaron el algoritmo de deteccion para evitar falsos positivos.
 * --> Se modifico el tiempo en que el transductor envia los pulsos de Ultrasonido
 * --> Se mejoro la fiabilidad del sistema de deteccion.
 *  Revision 16 de Febrero de 2016 
 * --> se modificaron los pines de deteccion 
 * del oscilador 1 por el oscilador 2 
 * NOTA: siempre registrar ultima entrada/******************************
 * Ultima entrada 20/Abril /2016
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <GenericTypeDefs.h>
#include <p18f25k22.h>
#include <delays.h>
#include <reset.h>
#include "../LibraryPARKUEST/PROCESSOR_PARKUEST.h" 
#include "../LibraryPARKUEST/PWM_PARKUEST.h"
#include "../LibraryPARKUEST/ADC_PARKUEST.h"
#include "../LibraryPARKUEST/UART_PARKUEST.h"
#include "../LibraryPARKUEST/EX_INTERRUPT_PARKUEST.h"
#include "../LibraryPARKUEST/TIMER_PARKUEST.h"
#include "../LibraryPARKUEST/SONAR_PARKUEST.h"
#include "../LibraryPARKUEST/COLOR_PARKUEST.h"
#include "../LibraryPARKUEST/ComINDICADOR_PARKUEST.h"
#include "../LibraryPARKUEST/COMMUNICATION_PARKUEST.h"
#include "../LibraryPARKUEST/EEPROM_PARKUEST.h"
#include "../LibraryPARKUEST/MASTER_SLAVE_TASKS_PARKUEST.h"
#include "../LibraryPARKUEST/SLAVE_TASKS_PARKUEST.h"
#include "../LibraryPARKUEST/INDICATOR_TASKS_PARKUEST.h"
#include "../LibraryPARKUEST/FileSYSTEM_PARKUEST.h"
#include "../LibraryPARKUEST/SoftwareUART_PARKUEST.h"

/*
 *
 */

#pragma udata COMUNICATION_VAR1 = 0x200
    Bus_Data BusSLAVE_T;
    Bus_Data BusMASTER_T;
#pragma udata
#pragma udata COMUNICATION_VAR2 = 0x300
    Bus_Data BusSLAVE_R;
    Bus_Data BusMASTER_R;
#pragma udata
    
FLAGs FLAG;
COLOR COLORS;
ID_PARKUEST IDSlave;
ID_PARKUEST IDMaster;
ID_PARKUEST ID_RECEPCION;
SONAR1 SONAR;
Val_Data StateSLAVE[(SensorNUMBER / 8)] = {0};
Val_Data SLAVE_INIT[(SensorNUMBER / 8)] = {0};
Val_Data DISPLAY_INIT[(SensorNUMBER / 8)] = {0};
BOOL FLAG_TIMER_HIGH;
unsigned char BufferIndicatorUART[4] = {0};

void main(void) {
    
    CONF_PROCESSOR();
    IO_CONF();
    UART1_CONF_9bit(219);
    UART2_CONF_9bit(219);
    AN_CONF();
    TIMER0_CONF();
    R_PWM_CONFIG(0);
    G_PWM_CONFIG(0);
    B_PWM_CONFIG(0);
    TXRX_EN1 = 0;
    TXRX_EN2 = 0;
    ResetVariables();
#if defined Address8BIT
    IDSlave.VAL = CALCULATE_ID_SOFTWARE_8bit(HardwareFUNCTION,5); /*Funcionamiento definido por HARDWARE*/
#else
    IDSlave.VAL = CALCULATE_ID_SOFTWARE_7bit(HardwareFUNCTION,5); /*Funcionamiento definido por HARDWARE*/
#endif 
    FLAG.ChangeSTATE = 1;
    FLAG.NOT_SENSE = 0;
    COLORS.SPEED = SPEED_R3;

    SetupDISTANCE_MIN(1, 0);
    SetupCOLOR_ACTIVE(red6()); 
    SetupCOLOR_N_ACTIVE(green());
    
    FileCOLORS(&COLORS);
    FileID(&IDSlave.VAL);
    FLAG.IndicatorINTEGRATED_OnOff = FileINDICATOR_OnOff();
    FLAG.OnlyOneIndicatorActive = ReadOnlyOneIndicatorIDs(&FLAG.OnlyOneIndicatorSENSORES[0]);
/* ES NECESARIO ESPECIFICAR EL NUMERO DE ARGUMENTOS QUE CONTIENE LA FUNCION******
 * Ejemplo:
 * Numero de argumentos:
 * arg1
 * arg2
 * arg3
 * OnlyOneIndicatorIdSensors(3,arg1,arg2,arg3);
 *******************************************************************************/
    if (FLAG.MASTERSLAVE_ACTIVE == 1) {
        FLAG.StartCommMASTER = 1;
        COM1_IND_O = 1;
        COM2_IND_O = 0;
        Waiting_Initialization_PARKUEST();
        ChangeFadeCOLOR(magenta(), COLORS.RED_D, COLORS.GREEN_D, COLORS.BLUE_D);
        SONAR.SensingDistance = AutoSetting();
        SONAR.SensingDistance = DISTANCE(1,80);
        FileDISTANCE(&SONAR);
        RGB_8bit(COLORS.RED_D, COLORS.GREEN_D, COLORS.BLUE_D);
        Send_Initialization();
        FLAG.NumberSLAVEs_REGISTER = 1;
        FLAG.NumberSLAVEs_ACTIVES = 0;
        FLAG.StartCommMASTER = 0;
        FLAG.FlagTimerRemaining2 = 0;
        FLAG.FlagTimerRemaining3 = 0;
        BufferIndicatorUART[0] = ChangeOnSOFTWARE_D;
        BufferIndicatorUART[1] = 0;
        BufferIndicatorUART[2] = 0;
        BufferIndicatorUART[3] = 0;
        SendCommand1_UartSOFTWARE(&BufferIndicatorUART[0],4);
        while (1) MASTER_SLAVE_TASKS();
    } else if (FLAG.SLAVE_ACTIVE == 1) {
        COM1_IND_O = 1;
        COM2_IND_O = 0;
        Waiting_Initialization_PARKUEST();
        DelayedStart(IDSlave.VAL);
        Response_Initialization();
        ChangeFadeCOLOR_FAST(OrangeRed(), COLORS.RED_D, COLORS.GREEN_D, COLORS.BLUE_D);
        SONAR.SensingDistance = AutoSetting();
        RGB_8bit(COLORS.RED_D, COLORS.GREEN_D, COLORS.BLUE_D);
        SONAR.SensingDistance = DISTANCE(1,80);
        FileDISTANCE(&SONAR);
        FLAG.FlagTimerRemaining2 = 0;
        FLAG.FlagTimerRemaining3 = 0;
        BufferIndicatorUART[0] = ChangeOnSOFTWARE_D;
        BufferIndicatorUART[1] = 0;
        BufferIndicatorUART[2] = 0;
        BufferIndicatorUART[3] = 0;
        SendCommand1_UartSOFTWARE(&BufferIndicatorUART[0],4);         
        while (1) SLAVE_TASKS();
    } else if (FLAG.INDICATOR_ACTIVE == 1) {
        RemapINPUT_IND();
        while(!COM1_IND_I);
        UART1_OFF();
        UART2_OFF();
        TIMER0_OFF();
        RGB_8bit(OFF_INDICATOR());
        while (1) INDICATOR_TASK();
    }
}








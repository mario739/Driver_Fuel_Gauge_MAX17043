/**
 * @file MAX17043.h
 * @author Mario Aguilar (fernandoaguilar731010@gmail.com)
 * @brief 
 * @version v1
 * @date 2022-02-18
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef MAX17043_H
#define MAX17043_H

// velocidad de I2C 400kHZ
//NOTA:Formatos de operacion 
// 1:Escribir el bit de inicio,direcccion de dispositivo,R/W,Luego monitorear el bit de reconocimiento para detectar la precencia del MAX17043
// 2:Escribir datos y leer datos  
// 3:Lectura de datos y ejecución de operaciones específicas del dispositivo

//Write: S. SAddr W. A. MAddr. A. Data0. A. Data1. A. P
//Para la lectura se tiene que escribir primero de donde va empezar a leer 
//Read: S. SAddr W. A. MAddr. A. Sr. SAddr R. A. Data0. A. Data1. N. P

#include <stdint.h>

#define MAX17043_ADDRESS        0x36    /*!<Direccion del esclavo 7 bits        */
#define CMD_QUICK_START         0x4000  /*!<Comando para inicio rapido Registro MODE     */
#define CMD_RESET               0x0054  /*!<Comando para resetear el divice en el registro COMMAND     */




#define REG_ONE_VCELL           0x02    /*!< (R) 12 bits medicion del nivel de voltaje   */
#define REG_TWO_VCELL           0x03     
#define REG_ONE_SOC             0x04    /*!< (R)16 bits Calculo del algoritmo de ModelGauge  */
#define REG_TWO_SOC             0x05
#define REG_ONE_MODE            0x06    /*!< (W)Registro numero uno para el modo de operacion*/    
#define REG_TWO_MODE            0x07    /*!< Registro numero dos para el modo de operacion */
#define REG_ONE_VERSION         0x08    /*!< (R)Retorna la version del IC */
#define REG_TWO_VERSION         0x09  
#define REG_ONE_CONFIG          0x0C    /*!< (R/W)(971C)Registro para la configuracion del DC tiene el bit de sleep y alert */
#define REG_TWO_CONFIG          0x0D   
#define REG_ONE_COMMAND         0xFE   /*!< (W)Comandos especiales para el IC  */
#define REG_TWO_COMMAND         0xFF     


#define DELAY_500MS             500
#define DELAY_MEDICION          125
//maximo direccion 4Fh de escritura
//maxima direccion FFhde lectura 

//NOTA: Flanco ascendente al pin QSTR o escribiendo al 4000h al mode registro 


typedef void (*func_write)(uint8_t,uint8_t *,uint8_t);
typedef void (*func_read) (uint8_t,uint8_t *,uint8_t);
typedef void (*delay1ms)(uint8_t);

typedef struct 
{
    func_write writeI2C;
    func_read readI2C;
    delay1ms  delayms_I2C;
    /* data */
}max17043_data;


void max17043Init(max17043_data *obj,func_write func_write_port,func_read func_read_port,delay1ms delay_port );
void max17043SoftReset(max17043_data *obj);
uint16_t max17043GetVoltage(max17043_data *obj);
uint16_t max17043GetBatteryChargePercentage(max17043_data *obj);
uint16_t max17043GetVersion(max17043_data *obj);
void max17043OpenSleepMode(max17043_data *obj);
void max17043CloseSleepMode(max17043_data *obj);
void max17043SetAlertThreshold(max17043_data*obj ,uint8_t percentage);
void max17043SetAlert(max17043_data*obj);
void max17043ClearAlert(max17043_data*obj);
uint16_t max17043_get_config(max17043_data *obj);










#endif
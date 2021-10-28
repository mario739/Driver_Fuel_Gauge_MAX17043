#include "MAX17043.h"

void max17043Init(max17043_data *obj,func_write func_write_port,func_read func_read_port,delay1ms delay_port )
{
    obj->writeI2C=func_write_port;
    obj->readI2C=func_read_port;
    obj->delayms_I2C=delay_port;

}


static void max17043Write16(max17043_data *obj,uint16_t data )
{
    uint8_t msb,lsb;
    msb=(data & 0xFF00)>>8;
    lsb=(data & 0x00FF);
    uint8_t bufferWrite[2]={msb,lsb};
    obj->writeI2C(MAX17043_ADDRESS,bufferWrite,2);
} 
static uint16_t max17043Read16(max17043_data *obj,uint8_t reg )
{
    uint8_t bufferRead[2]={0,0};
    obj->writeI2C(MAX17043_ADDRESS,reg,1);
    obj->readI2C(MAX17043_ADDRESS,bufferRead,2);
    uint16_t data=(uint16_t)bufferRead[0] <<8  | (uint16_t)bufferRead[1] ; 
    return data;

}


void max17043SoftReset(max17043_data *obj)
{
    max17043Write16(obj,CMD_RESET);
}
uint16_t max17043GetVersion(max17043_data *obj)
{
  return  max17043Read16(obj,REG_ONE_VERSION);
 
}   
uint16_t max17043GetVoltage(max17043_data *obj)
{
    uint16_t Voltage=max17043Read16(obj,REG_ONE_VCELL)>>4;

    return Voltage;

}

uint16_t max17043GetBatteryChargePercentage(max17043_data *obj)
{
        uint8_t Porcentaje=0;
        obj->writeI2C(MAX17043_ADDRESS,REG_ONE_SOC,1);
        obj->readI2C(MAX17043_ADDRESS,&Porcentaje,1);

    return Porcentaje;
}

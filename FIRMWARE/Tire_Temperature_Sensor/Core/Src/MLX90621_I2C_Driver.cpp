/**
 * @copyright (C) 2017 Melexis N.V.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */
#include "i2c.h"
#include "MLX90621_I2C_Driver.h"


void MLX90621_I2CInit()
{
	//initialization generated by the .ioc
	//MX_I2C2_Init();
}

int MLX90621_I2CReadEEPROM(uint8_t slaveAddr, uint8_t startAddress, uint16_t nMemAddressRead, uint8_t *data)
{

    uint8_t sa;                           
    int ack = 0;                               
    int cnt = 0;
    uint8_t cmd = 0;
    uint8_t i2cData[256] = {0};
    uint8_t *p;
    
    p = data;
    sa = (slaveAddr << 1);
    cmd = startAddress;
    
    if(HAL_I2C_Mem_Read(&hi2c2, sa, cmd, 1, i2cData, nMemAddressRead, 100) != HAL_OK)
    {
    	return -1;
    }

    /*

    i2c.stop();

    wait_us(5);

    // i2c.write(slave_Address + 0, pointer_to_read_from, lenght_of_data(bytes) , true-do_not_send_stop_at_end);

    ack = i2c.write(sa, &cmd, 1, 1);
    
    if (ack != 0x00)
    {
        return -1;
    }
             
    sa = sa | 0x01;

    // i2c.read(slave_Address + 1, pointer_to_read_to, lenght_of_data(bytes), true-do_not_send_stop_at_end);

    ack = i2c.read(sa, i2cData, nMemAddressRead, 0);
    
    if (ack != 0x00)
    {
        return -1; 
    }          

    i2c.stop();   
    */
    
    for(cnt=0; cnt < nMemAddressRead; cnt++)
    {
        *p++ = i2cData[cnt];
    }
    

    return 0;
} 

int MLX90621_I2CRead(uint8_t slaveAddr,uint8_t command, uint8_t startAddress, uint8_t addressStep, uint8_t nMemAddressRead, uint16_t *data)
{
    uint8_t sa;                           
    int ack = 0;                               
    int cnt = 0;
    int i = 0;
    uint8_t cmd[4] = {0,0,0,0};
    uint8_t i2cData[132] = {0};
    uint16_t *p;
    
    p = data;
    sa = (slaveAddr << 1);
    cmd[0] = command;
    cmd[1] = startAddress;
    cmd[2] = addressStep;
    cmd[3] = nMemAddressRead;
    

    if(Custom_HAL_I2C_Mem_Read(&hi2c2, sa, command, startAddress, addressStep, nMemAddressRead, i2cData, 2*nMemAddressRead, 100) != HAL_OK)
    {
    	return -1;
    }


//    if(HAL_I2C_Mem_Read_MltCmd(&hi2c, sa, cmd, 4, i2cData, 2*nMemAddressRead, 100) != HAL_OK)
//    {
//    	return -1;
//    }
//
//    if(HAL_I2C_Master_Transmit(&hi2c2, sa, cmd, 4, 100) != HAL_OK)
//    {
//        return -1;
//    }
//    if(HAL_I2C_Master_Receive(&hi2c2, sa, i2cData, 2*nMemAddressRead, 100) != HAL_OK)
//    {
//        return -1;
//    }

    /*
    i2c.stop();
    wait_us(5);
    ack = i2c.write(sa, cmd, 4, 1);
    
    if (ack != 0x00)
    {
        return -1;
    }
             
    sa = sa | 0x01;
    ack = i2c.read(sa, i2cData, 2*nMemAddressRead, 0);
    
    if (ack != 0x00)
    {
        return -1; 
    }          
    i2c.stop();
    */
    
    for(cnt=0; cnt < nMemAddressRead; cnt++)
    {
        i = cnt << 1;
        *p++ = (uint16_t)i2cData[i+1]*256 + (uint16_t)i2cData[i];
    }
    



    return 0;   
} 

void MLX90621_I2CFreqSet(int freq)
{
	//set via the .ioc
    //i2c.frequency(1000*freq);
}

int MLX90621_I2CWrite(uint8_t slaveAddr, uint8_t command, uint8_t checkValue, uint16_t data)
{
    uint8_t sa;
    int ack = 0;
    uint8_t cmd[5] = {0,0,0,0,0};
    static uint16_t dataCheck;
    

    sa = (slaveAddr << 1);
    cmd[0] = command;
    cmd[2] = data & 0x00FF;
    cmd[1] = cmd[2] - checkValue;
    cmd[4] = data >> 8;
    cmd[3] = cmd[4] - checkValue;

    if(HAL_I2C_Master_Transmit(&hi2c2, sa, cmd, 5, 100) != HAL_OK)
    {
        return -1;
    }

    /*

    i2c.stop();
    wait_us(5);    
    ack = i2c.write(sa, cmd, 5, 0);
    
    if (ack != 0x00)
    {
        return -1;
    }         
    i2c.stop();   
    
    */

    MLX90621_I2CRead(slaveAddr, 0x02, 0x8F+command, 0, 1, &dataCheck);
    
    if ( dataCheck != data)
    {
        return -2;
    }    
    
    return 0;
}





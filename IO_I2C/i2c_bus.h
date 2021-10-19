/********************************************************************************************************
* @file     i2c_bus.h 
* 
* @brief    i2c_bus header file IO模拟IIC
* 
* @author   404zen
* 
* @date     2021-10-14 14:03:36 
* 
* @attention 
* 
* None.
* 
*******************************************************************************************************/
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __I2C_BUS_H__
#define __I2C_BUS_H__

/* Includes ------------------------------------------------------------------*/
#ifdef	USE_HAL_DRIVER	            /* USE ST HAL Lib */
#include "stm32f1xx_hal.h"
#endif

#include "delay.h"
#include <stdio.h>

/* Private includes ----------------------------------------------------------*/

/* Exported defines ----------------------------------------------------------*/
#define IIC_SCL_Port                    GPIOA
#define IIC_SCL_Pin                     GPIO_PIN_1
#define IIC_SDA_Port                    GPIOA
#define IIC_SDA_Pin                     GPIO_PIN_2

#ifdef	USE_HAL_DRIVER	                /* USE ST HAL Lib */
#define IIC_SDA(n)                      (n == 0 ? HAL_GPIO_WritePin(IIC_SDA_Port, IIC_SDA_Pin, GPIO_PIN_RESET) : HAL_GPIO_WritePin(IIC_SDA_Port, IIC_SDA_Pin, GPIO_PIN_SET))
#define IIC_SCL(n)                      (n == 0 ? HAL_GPIO_WritePin(IIC_SCL_Port, IIC_SCL_Pin, GPIO_PIN_RESET) : HAL_GPIO_WritePin(IIC_SCL_Port, IIC_SCL_Pin, GPIO_PIN_SET))

#define READ_SDA()                      HAL_GPIO_ReadPin(IIC_SDA_Port, IIC_SDA_Pin)
#endif

#if 1
#define IIC_DEBUG(...)                  printf(__VA_ARGS__)
#else
#define IIC_DEBUG(...)                  (void*)0
#endif

/* Exported types ------------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/

/* Exported macro ------------------------------------------------------------*/

/* Private defines -----------------------------------------------------------*/

/* Exported functions prototypes ---------------------------------------------*/
void IICBusInit(void);

uint8_t IICReadOneByte(uint8_t slave_addr, uint8_t reg_addr);
void IICWriteOneByte(uint8_t slave_addr, uint8_t reg_addr, uint8_t data);
void IICReadBuf(uint8_t slave_addr, uint8_t reg_addr, uint8_t *r_buf, uint8_t r_len);
void IICWriteBuf(uint8_t slave_addr, uint8_t reg_addr, uint8_t *w_buf, uint8_t w_len);







#endif /* __MY_I2C_H__ */
/*********************************END OF FILE**********************************/

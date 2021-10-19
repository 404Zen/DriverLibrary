/**
******************************************************************************
 * @file             : spi_bus.h 
 * @brief            : program header 
 * @author           : 404Zen 
 * @date             : 2021-10-18, 21:38:49 
******************************************************************************
* @attention
*    None.
******************************************************************************
*/
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __SPI_BUS_H__
#define __SPI_BUS_H__

/* Includes ------------------------------------------------------------------*/
#ifdef USE_HAL_DRIVER
#include "main.h"
#endif

#include "delay.h"

/* Exported types ------------------------------------------------------------*/
typedef enum
{
    SPI_MODE0 = 0,
    SPI_MODE1,
    SPI_MODE2,
    SPI_MODE3,
}SPIMode_t;

/* Exported constants --------------------------------------------------------*/

/* Exported defines -----------------------------------------------------------*/

#define SPI_CS_ENABLE                                       1
#define SPI_MODE                                            SPI_MODE0

#ifdef USE_HAL_DRIVER                   /* ST HAL库 */
#define GPIO_WRITE_PIN(port, pin, level)                    HAL_GPIO_WritePin(port, pin, level)                      
#define GPIO_READ_PIN(port, pin)                            HAL_GPIO_ReadPin(port, pin)

#if SPI_CS_ENABLE
#define SPI_CS(n)                       (n ? (GPIO_WRITE_PIN(SPI_CS_GPIO_Port, SPI_CS_Pin, GPIO_PIN_SET)) : (GPIO_WRITE_PIN(SPI_CS_GPIO_Port, SPI_CS_Pin, GPIO_PIN_RESET)))
#else
#define SPI_CS(n)                       (void*)0
#endif
#define SPI_CLK(n)                      (n ? (GPIO_WRITE_PIN(SPI_SCK_GPIO_Port, SPI_SCK_Pin, GPIO_PIN_SET)) : (GPIO_WRITE_PIN(SPI_SCK_GPIO_Port, SPI_SCK_Pin, GPIO_PIN_RESET)))
#define SPI_MOSI(n)                     (n ? (GPIO_WRITE_PIN(SPI_MOSI_GPIO_Port, SPI_MOSI_Pin, GPIO_PIN_SET)) : (GPIO_WRITE_PIN(SPI_MOSI_GPIO_Port, SPI_MOSI_Pin, GPIO_PIN_RESET)))
#define SPI_MISO_READ()                 GPIO_READ_PIN(SPI_MISO_GPIO_Port, SPI_MISO_Pin)

#define SPI_DELAY(n)                    DelayUS(n)
// #define SPI_DELAY(n)                    (void*)0
#endif

/* Private macros ------------------------------------------------------------*/

/* Exported functions --------------------------------------------------------*/
void SPIBusInit(void);
void SPIBusWriteByte(uint8_t data);
uint8_t SPIBusReadByte(void);
void SPIBusWriteBuf(uint8_t *buf, uint16_t len);


/* Private functions ---------------------------------------------------------*/


#endif /* __SPI_BUS_H__ */
/**********************************END OF FILE*********************************/


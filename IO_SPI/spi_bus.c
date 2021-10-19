/**
******************************************************************************
 * @file             : spi_bus.c 
 * @brief            : program body 
 * @author           : 404Zen 
 * @date             : 2021-10-18, 21:38:25 
******************************************************************************
* @attention
*    None.
******************************************************************************
*/
/* Includes ------------------------------------------------------------------*/
#include "spi_bus.h"

/* Private includes ----------------------------------------------------------*/

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
static SPIMode_t spi_work_mode;

static uint8_t SPIBusReadWriteByte(uint8_t w_data);
/* Private function prototypes -----------------------------------------------*/

/* Private user code ---------------------------------------------------------*/
/**
 * @brief  SPIBusInit.spi io init.
 * @param  None.
 * @note   None. 
 * @retval None
 */
void SPIBusInit(void)
{
    uint8_t temp[10] = {1,2,3,4,5,6,7,8,9,10};
    
    spi_work_mode = SPI_MODE;
    
    if(spi_work_mode == SPI_MODE3 || spi_work_mode == SPI_MODE1)
    {
        SPI_CS(1);
        SPI_CLK(1);
        SPI_MOSI(1);
    }
    else if(spi_work_mode == SPI_MODE2 || spi_work_mode == SPI_MODE0)
    {
        SPI_CS(1);
        SPI_CLK(0);
        SPI_MOSI(1);
    }
    
    SPIBusWriteByte(0x55);              /* test ok */
    SPIBusReadByte();                   /* test ok */
    SPIBusWriteBuf(temp, 10);           /* test ok */
}

/**
 * @brief  SPIBusReadWriteByte.
 * @param  None.
 * @note   w_data:将要写入的数据
 * @retval 读到的数据
 */
uint8_t SPIBusReadWriteByte(uint8_t w_data)
{
    uint8_t r_data = 0, i = 0;

    #if SPI_CS_ENABLE
    SPI_CS(0);
    #endif
    SPI_DELAY(1);

    if(spi_work_mode == SPI_MODE3)
    {
        for (i = 0; i < 8; i++)
        {
            SPI_CLK(0);

            if(w_data & 0x80)
                SPI_MOSI(1);
            else
                SPI_MOSI(0);

            SPI_DELAY(1);

            SPI_CLK(1);

            w_data <<= 1;
            r_data <<= 1;
            if(SPI_MISO_READ())
                r_data &= 0x01;
            
            SPI_DELAY(1);
        }
        SPI_DELAY(1);
        SPI_CLK(1);
    }
    else if(spi_work_mode == SPI_MODE2)
    {
        for (i = 0; i < 8; i++)
        {
            SPI_CLK(1);
            
            if(w_data & 0x80)
                SPI_MOSI(1);
            else
                SPI_MOSI(0);

            SPI_DELAY(1);

            SPI_CLK(0);

            w_data <<= 1;
            r_data <<= 1;
            if(SPI_MISO_READ())
                r_data &= 0x01;
            
            SPI_DELAY(1);
        }
        SPI_DELAY(1);
        SPI_CLK(0);
    }
    else if(spi_work_mode == SPI_MODE1)
    {
        for (i = 0; i < 8; i++)
        {
            if(w_data & 0x80)
                SPI_MOSI(1);
            else
                SPI_MOSI(0);

            SPI_DELAY(1);
            SPI_CLK(0);
            
            w_data <<= 1;
            r_data <<= 1;
            if(SPI_MISO_READ())
                r_data &= 0x01;
            
            SPI_CLK(1);
        }
        SPI_DELAY(1);
        SPI_CLK(1);
    }
    else if(spi_work_mode == SPI_MODE0)
    {
        for (i = 0; i < 8; i++)
        {
            if(w_data & 0x80)
                SPI_MOSI(1);
            else
                SPI_MOSI(0);

            SPI_DELAY(1);
            SPI_CLK(1);
            
            w_data <<= 1;
            r_data <<= 1;
            if(SPI_MISO_READ())
                r_data &= 0x01;
            
            SPI_CLK(0);
        }
        SPI_DELAY(1);
        SPI_CLK(0);
    }

    #if SPI_CS_ENABLE
    SPI_CS(1);
    #endif

    return r_data;
}

/**
 * @brief  SPIBusWriteByte.
 * @param  None.
 * @note   w_data:将要写入的数据
 * @retval None.
 */
void SPIBusWriteByte(uint8_t data)
{
    SPIBusReadWriteByte(data);
}

/**
 * @brief  SPIBusReadByte.
 * @param  None.
 * @note   None.
 * @retval 读到的数据
 */
uint8_t SPIBusReadByte(void)
{
    return SPIBusReadWriteByte(0xFF);
}

/**
 * @brief  SPIBusWriteBuf.
 * @param  *buf:将要写入的数据指针.
 * @param   len:要写入的数据长度
 * @note   None.
 * @retval None.
 */
void SPIBusWriteBuf(uint8_t *buf, uint16_t len)
{
    uint16_t i = 0;

    for (i = 0; i < len; i++)
    {
        SPIBusReadWriteByte(*buf);
        buf++;
    }
}

/**********************************END OF FILE*********************************/


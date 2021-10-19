/********************************************************************************************************
* @file     i2c_bus.c 
* 
* @brief    i2c_bus c file
* 
* @author   404zen
* 
* @date     2021-10-14 14:02:28 
* 
* @attention 
* 
* None.
* 
*******************************************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "i2c_bus.h"


/* Private includes ----------------------------------------------------------*/

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/
void SDAConfigOut(void);
void SDAConfigIn(void);

void IICStart(void);
void IICStop(void);
uint8_t IICWaitAck(void);
void IICAck(void);
void IICNoAck(void);
void IICSendByte(uint8_t data);
uint8_t IICReadByte(uint8_t ack);

/* Private user code ---------------------------------------------------------*/

/* External variables --------------------------------------------------------*/

/* Private user code ---------------------------------------------------------*/
 /**
  * @brief  MyIICInit
  * @note   None.
  * @param  None.
  * @retval None.
  */
void IICBusInit(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    /* GPIO Ports Clock Enable */
    __HAL_RCC_GPIOA_CLK_ENABLE();

    /*Configure GPIO pin Output Level */
    HAL_GPIO_WritePin(IIC_SCL_Port, IIC_SCL_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(IIC_SDA_Port, IIC_SDA_Pin, GPIO_PIN_SET);

    /*Configure GPIO pin : ---- */
    GPIO_InitStruct.Pin = IIC_SCL_Pin | IIC_SDA_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
    HAL_GPIO_Init(IIC_SCL_Port, &GPIO_InitStruct);
}

 /**
  * @brief  MySDAConfigOut
  * @note   None.
  * @param  None.
  * @retval None.
  */
void SDAConfigOut(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    /*Configure GPIO pin : ---- */
    GPIO_InitStruct.Pin = IIC_SDA_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
    HAL_GPIO_Init(IIC_SDA_Port, &GPIO_InitStruct);
}

 /**
  * @brief  MySDAConfigIn
  * @note   None.
  * @param  None.
  * @retval None.
  */
void SDAConfigIn(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    /*Configure GPIO pin : ---- */
    GPIO_InitStruct.Pin = IIC_SDA_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
    HAL_GPIO_Init(IIC_SDA_Port, &GPIO_InitStruct);
}

 /**
  * @brief  IICStart
  * @note   None.
  * @param  None.
  * @retval None.
  */
void IICStart(void)
{
    SDAConfigOut();

    IIC_SCL(1);
    IIC_SDA(1);
    DelayUS(1);

    IIC_SDA(0);
    DelayUS(5);
    IIC_SCL(0);
}

 /**
  * @brief  IICStop
  * @note   None.
  * @param  None.
  * @retval None.
  */
void IICStop(void)
{
    SDAConfigOut();
    IIC_SCL(0);
    IIC_SDA(0);
    DelayUS(4);

    IIC_SCL(1);
    DelayUS(4);
    IIC_SDA(1);
}

 /**
  * @brief  IICWaitAck
  * @note   None.
  * @param  None.
  * @retval 1-OK, 0-fail.
  */
uint8_t IICWaitAck(void)
{
    uint8_t timeout = 0;

    SDAConfigIn();
    IIC_SDA(1);
    DelayUS(1);
    IIC_SCL(1);
    DelayUS(1);
    while (READ_SDA())
    {
        timeout++;

        if(timeout >= 250)
        {
            IICStop();
            return 0;
        }
    }

    IIC_SCL(0);
    return 1;
}

 /**
  * @brief  IICAck
  * @note   None.
  * @param  None.
  * @retval None.
  */
void IICAck(void)
{
    IIC_SCL(0);
    SDAConfigOut();
    IIC_SDA(0);
    DelayUS(2);
    IIC_SCL(1);
    DelayUS(2);
    IIC_SCL(0);
}

 /**
  * @brief  IICNoAck
  * @note   None.
  * @param  None.
  * @retval None.
  */
void IICNoAck(void)
{
    IIC_SCL(0);
    SDAConfigOut();
    IIC_SDA(1);
    DelayUS(2);
    IIC_SCL(1);
    DelayUS(2);
    IIC_SCL(0);
}

 /**
  * @brief  IICSendByte
  * @note   None.
  * @param  data: data need to send
  * @retval None.
  */
void IICSendByte(uint8_t data)
{
    uint8_t i = 0;

    SDAConfigOut();

    IIC_SCL(0);

    for (i = 0; i < 8; i++)
    {
        IIC_SDA((data&0x80) >> 7);
        data <<= 1;

        DelayUS(1);
        IIC_SCL(1);
        DelayUS(2);
        IIC_SCL(0);
        DelayUS(2);
    }
}

 /**
  * @brief  IICReadByte
  * @note   None.
  * @param  ack: 1: send ack 0: send no ack
  * @retval data read out.
  */
uint8_t IICReadByte(uint8_t ack)
{
    uint8_t i = 0, data = 0;

    SDAConfigIn();

    for (i = 0; i < 8; i++)
    {
        IIC_SCL(0);
        DelayUS(2);
        IIC_SCL(1);
        data <<= 1;

        if(READ_SDA())
            data |= 1;
        
        DelayUS(1);
    }

    if(ack)
        IICAck();
    else
        IICNoAck();
    
    return data;
}

 /**
  * @brief  IICReadOneByte
  * @note   None.
  * @param  slave_addr: 从机地址
  * @param  reg_addr: 寄存器地址
  * @retval data read out.
  */
uint8_t IICReadOneByte(uint8_t slave_addr, uint8_t reg_addr)
{
    uint8_t data = 0;

    IICStart();                         /* 起始帧 */
    IICSendByte(slave_addr);            /* 器件地址，写命令 */
    if(IICWaitAck() == 0)               /* 等待从机应答 */
        IIC_DEBUG("IIC send write slave addr no ack!\r\n");
    IICSendByte(reg_addr);              /* 寄存器地址 */
    if(IICWaitAck() == 0)               /* 等待从机应答 */
        IIC_DEBUG("IIC write reg addr no ack!\r\n");

    IICStart();                         /* Start Repeat */
    IICSendByte(slave_addr|0x01);       /* 器件地址，读命令 */
    if(IICWaitAck() == 0)               /* 等待从机应答 */
        IIC_DEBUG("IIC send read slave addr no ack!\r\n");
    
    data = IICReadByte(0);              /* Read Byte without ack */
    IICStop();                          /* Stop */

    return data;
}

 /**
  * @brief  IICWriteOneByte
  * @note   None.
  * @param  slave_addr: 从机地址
  * @param  reg_addr: 寄存器地址
  * @param  data: 要写入的数据
  * @retval data read out.
  */
void IICWriteOneByte(uint8_t slave_addr, uint8_t reg_addr, uint8_t data)
{
    IICStart();                         /* 起始帧 */
    IICSendByte(slave_addr);            /* 器件地址，写命令 */
    if(IICWaitAck() == 0)               /* 等待从机应答 */
        IIC_DEBUG("IIC send write slave addr no ack!\r\n");
    IICSendByte(reg_addr);              /* 寄存器地址 */
    if(IICWaitAck() == 0)               /* 等待从机应答 */
        IIC_DEBUG("IIC write reg addr no ack!\r\n");

    IICSendByte(data);
    if(IICWaitAck() == 0)               /* 等待从机应答 */
        IIC_DEBUG("IIC write data no ack!\r\n");

    IICStop();
}

 /**
  * @brief  IICReadBuf
  * @note   None.
  * @param  slave_addr: 从机地址
  * @param  reg_addr: 寄存器地址
  * @param  *r_buf: 数据指针
  * @param  r_len： 读出数据长度
  * @retval None.
  */
void IICReadBuf(uint8_t slave_addr, uint8_t reg_addr, uint8_t *r_buf, uint8_t r_len)
{
    IICStart();                         /* 起始帧 */
    IICSendByte(slave_addr);            /* 器件地址，写命令 */
    if(IICWaitAck() == 0)               /* 等待从机应答 */
    {
        IIC_DEBUG("IIC send write slave addr no ack!\r\n");
        return ;
    }
    IICSendByte(reg_addr);              /* 寄存器地址 */
    if(IICWaitAck() == 0)               /* 等待从机应答 */
    {
        IIC_DEBUG("IIC write reg addr no ack!\r\n");
        return ;
    }

    IICStart();                         /* Start Repeat */
    IICSendByte(slave_addr|0x01);       /* 器件地址，读命令 */
    if(IICWaitAck() == 0)               /* 等待从机应答 */
    {
        IIC_DEBUG("IIC send read slave addr no ack!\r\n");
        return ;
    }

    while (r_len)
    {
        
        if(r_len == 1)
            *r_buf = IICReadByte(0);
        else
            *r_buf = IICReadByte(1);
        
        r_buf++;
        r_len--;
    }

    IICStop();
}

 /**
  * @brief  IICReadBuf
  * @note   None.
  * @param  slave_addr: 从机地址
  * @param  reg_addr: 寄存器地址
  * @param  *w_buf: 数据指针
  * @param  w_len 写入数据长度
  * @retval None.
  */
void IICWriteBuf(uint8_t slave_addr, uint8_t reg_addr, uint8_t *w_buf, uint8_t w_len)
{
    uint8_t i = 0;

    IICStart();                         /* 起始帧 */
    IICSendByte(slave_addr);            /* 器件地址，写命令 */
    if(IICWaitAck() == 0)               /* 等待从机应答 */
    {
        IIC_DEBUG("IIC send write slave addr no ack!\r\n");
        return ;
    }
    IICSendByte(reg_addr);              /* 寄存器地址 */
    if(IICWaitAck() == 0)               /* 等待从机应答 */
    {
        IIC_DEBUG("IIC write reg addr no ack!\r\n");
        return ;
    }

    for (i = 0; i < w_len; i++)
    {
        IICSendByte(w_buf[i]);
        if(IICWaitAck() == 0)               /* 等待从机应答 */
        {
            IIC_DEBUG("IIC write data no ack! count = %d.\r\n", i);

            IICStop();
            return ;
        }
    }
    IICStop();
}



/*********************************END OF FILE**********************************/

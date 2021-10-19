#include "my_uart.h"
#include "stm32f1xx_hal.h"
#include <stdio.h>
#include <stdint.h>
#include <stdarg.h>
#include <string.h>

extern UART_HandleTypeDef huart1;
extern DMA_HandleTypeDef hdma_usart1_tx;

#define UART_TX_SIZE        256
uint8_t uart_send_buffer[256];
uint8_t uart_tx_dma_flag = 0;

int fputc(int ch, FILE *f)
{
    while(__HAL_UART_GET_FLAG(&huart1, UART_FLAG_TC) == RESET);
    HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 1, 0xFFFF);
    // HAL_UART_Transmit_DMA(&huart1, (uint8_t *)&ch, 1);
    return ch;
}

// int fgetc(FILE *f)
// {
//     uint8_t ch = 0;
//     HAL_UART_Receive(&huart1, &ch, 1, 0xFFFF);
//     return ch;
// }

void my_printf(const char *fmt, ...)
{
    va_list ap;

    va_start(ap, fmt);
    vprintf(fmt, ap);
    va_end(ap);

    return ;
}

void my_printf_array(unsigned char *array, unsigned int len)
{
    while (len--)
    {
        printf("0x%02X ", *array);
        array++;
    }

    printf("\r\n");
}

void my_log(LOG_LEVEL_e level, const char *fmt, ...)
{
    va_list ap;
    
    va_start(ap, fmt);

    switch (level)
    {
        case LOG_INFORMATION:
            printf("\r\nInformation: ");
            vprintf(fmt, ap);
            break;

        case LOG_WARNING:
            printf("\r\nWarning: ");
            vprintf(fmt, ap);
            break;

        case LOG_ERROR:
            printf("\r\nError: ");
            vprintf(fmt, ap);
            break;

        case LOG_VL53L0X:
            printf("\r\nVL53L0X: ");
            vprintf(fmt, ap);
            break;
        
        default:
            break;
    }

    va_end(ap);
}


//void debug_printf(const char *fmt, ...)
//{
//    uint16_t len;
//    va_list args;

//    va_start(args, fmt);
//    len = vsnprintf((char*)uart_send_buffer, (sizeof(uart_send_buffer)+1), (char*)fmt, args);
//    va_end(args);

//    HAL_UART_Transmit_DMA(&huart1, uart_send_buffer, len);
//}

void my_dma_log(LOG_LEVEL_e level, const char *fmt, ...)
{
    char Info[] = "Information: ";
    char Warning[] = "Warnin: ";
    char Error[] = "Error: ";
    uint16_t len;
    va_list args;

    va_start(args, fmt);

    switch (level)
    {
    case LOG_INFORMATION:
        len = strlen(Info);
        strcat((char *)uart_send_buffer, Info);
        len += vsnprintf((char*)(uart_send_buffer+len), sizeof(uart_send_buffer)+1, (char*)fmt, args);
        break;

    case LOG_WARNING:
        len = strlen(Warning);
        strcat((char *)uart_send_buffer, Warning);
        len += vsnprintf((char*)(uart_send_buffer+len), sizeof(uart_send_buffer)+1, (char*)fmt, args);
        break;

    case LOG_ERROR:
        len = strlen(Error);
        strcat((char *)uart_send_buffer, Error);
        len += vsnprintf((char*)(uart_send_buffer+len), sizeof(uart_send_buffer)+1, (char*)fmt, args);
        break;

        
    default:
        break;
    }
    va_end(args);
        
    HAL_UART_Transmit_DMA(&huart1, uart_send_buffer, len);
}





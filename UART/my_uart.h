#ifndef __MY_UART_H__
#define __MY_UART_H__


typedef enum
{
    LOG_INFORMATION = 1,
    LOG_WARNING,
    LOG_ERROR,
    LOG_VL53L0X,
}LOG_LEVEL_e;


#define UART_DEBUG_ENABLE               1

#if UART_DEBUG_ENABLE
    #define MY_PRINT(...)               my_printf(__VA_ARGS__)
    #define MY_PRINT_ARRAY(array, len)	my_printf_array(array, len)
//    #define LOGI(...)                   my_dma_log(LOG_INFORMATION, __VA_ARGS__)
//    #define LOGW(...)                   my_dma_log(LOG_WARNING, __VA_ARGS__)
//    #define LOGE(...)                   my_dma_log(LOG_ERROR, __VA_ARGS__)
    #define LOGI(...)                   my_log(LOG_INFORMATION, __VA_ARGS__)
    #define LOGW(...)                   my_log(LOG_WARNING, __VA_ARGS__)
    #define LOGE(...)                   my_log(LOG_ERROR, __VA_ARGS__)
    #define LOG_VL53L0X(...)            my_log(LOG_VL53L0X, __VA_ARGS__)
#else   
    #define MY_PRINT(...)               (void)0
    #define LOGI(...)                   (void)0
    #define LOGW(...)                   (void)0
    #define LOGE(...)                   (void)0
#endif

void my_printf(const char *fmt, ...);
void my_printf_array(unsigned char *array, unsigned int len);
void my_log(LOG_LEVEL_e level, const char *fmt, ...);
void debug_printf(const char *fmt, ...);
void my_dma_log(LOG_LEVEL_e level, const char *fmt, ...);

#endif

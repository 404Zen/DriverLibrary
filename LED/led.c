/**
******************************************************************************
 * @file             : led.c 
 * @brief            : program body 
 * @author           : 404Zen 
 * @date             : 2021-10-10, 21:52:08 
******************************************************************************
* @attention
*   None.
******************************************************************************
*/

/* Includes ------------------------------------------------------------------*/
#include "led.h"

/* Private includes ----------------------------------------------------------*/

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

#if 0               
LEDDeviceStrcut LedRed;
LEDDeviceStrcut LedGreen;
LEDDeviceStrcut LedBlue;
#endif

#ifdef FK103M5
LEDDeviceStrcut led;
#endif

/* Private function prototypes -----------------------------------------------*/


/* Private user code ---------------------------------------------------------*/
/**	
 * @brief  LEDInit.
 * @param  None.
 * @note   None. 
 * @retval None
 */
void LEDInit(void)
{
#if 0
    LedRed.Port     = LED_R_GPIO_Port;
    LedRed.Pin      = LED_R_Pin;
    LedRed.Level    = LED_LOW_LEVEL;

    LedGreen.Port   = LED_G_GPIO_Port;
    LedGreen.Pin    = LED_G_Pin;
    LedGreen.Level  = LED_LOW_LEVEL;

    LedBlue.Port    = LED_B_GPIO_Port;
    LedBlue.Pin     = LED_B_Pin;
    LedBlue.Level   = LED_LOW_LEVEL;
#endif

#ifdef FK103M5
    led.Port        = LED_GPIO_Port;
    led.Pin         = LED_Pin;
    led.Level       = LED_LOW_LEVEL;
#endif
}

/**	
 * @brief  LEDOn.
 * @param  None.
 * @note   None. 
 * @retval None
 */
void LEDOn(LEDDeviceStrcut led)
{
    if (LED_LOW_LEVEL == led.Level)
    {
        GPIO_WRITE_PIN(led.Port, led.Pin, (GPIO_PinState)LED_LOW_LEVEL);
    }
    else
    {
        GPIO_WRITE_PIN(led.Port, led.Pin, (GPIO_PinState)LED_HIGH_LEVEL);
    }
}

/**
 * @brief  LEDOn.
 * @param  None.
 * @note   None. 
 * @retval None
 */
void LEDOff(LEDDeviceStrcut led)
{
    if (LED_LOW_LEVEL == led.Level)
    {
        GPIO_WRITE_PIN(led.Port, led.Pin, (GPIO_PinState)LED_HIGH_LEVEL);
    }
    else
    {
        GPIO_WRITE_PIN(led.Port, led.Pin, (GPIO_PinState)LED_LOW_LEVEL);
    }
}

/**
 * @brief  LEDOn.
 * @param  None.
 * @note   None. 
 * @retval None
 */
void LEDToggle(LEDDeviceStrcut led)
{
    GPIO_TOGGLE_PIN(led.Port, led.Pin);
}

#ifdef ALIENTEK_PANDORA
/**
 * @brief  LEDFlow.
 * @param  interval: 函数调用时间间隔
 * @note   None. 
 * @retval None
 */
void LEDFlow(uint8_t interval)
{
    static uint8_t  state;
    static uint32_t time;
    static uint32_t time_ref;

    time += interval;

    switch (state)
    {
    case 0:         /* RED */
        if(time - time_ref >= 200)
        {
            time_ref = time;
            LEDOn(LedRed);
            LEDOff(LedGreen);
            LEDOff(LedBlue);

            state = 1;
        }
        break;

    case 1:         /* GREEN */
        if(time - time_ref >= 100)
        {
            time_ref = time;
            LEDOff(LedRed);
            LEDOn(LedGreen);
            LEDOff(LedBlue);

            state = 2;
        }
        break;

    case 2:         /* BLUE */
        if(time - time_ref >= 100)
        {
            time_ref = time;
            LEDOff(LedRed);
            LEDOff(LedGreen);
            LEDOn(LedBlue);

            state = 3;
        }
        break;
    
    case 3:         /* OFF */
        if(time - time_ref >= 100)
        {
            time_ref = time;
            LEDOff(LedRed);
            LEDOff(LedGreen);
            LEDOff(LedBlue);

            state = 0;
        }
        break;
    
    default:
        state = 0;
        break;
    }
}
#endif






/**********************************END OF FILE*********************************/


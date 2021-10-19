/**
******************************************************************************
 * @file             : led.h 
 * @brief            : program header 
 * @author           : 404Zen 
 * @date             : 2021-10-10, 21:55:20 
******************************************************************************
* @attention
*   None.
******************************************************************************
*/
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __LED_H__
#define __LED_H__
/* Includes ------------------------------------------------------------------*/
#ifdef USE_HAL_DRIVER
#include "main.h"
#endif

/* Defines ------------------------------------------------------------------ */
#define LED_SUPPORT_NUM                 3

#define GPIO_WRITE_PIN(port, pin, level)                    HAL_GPIO_WritePin(port, pin, level)                      
#define GPIO_TOGGLE_PIN(port, pin)                          HAL_GPIO_TogglePin(port, pin)
/* Exported types ------------------------------------------------------------*/
typedef enum
{
    LED_LOW_LEVEL = 0,
    LED_HIGH_LEVEL,
}LEDState_e;

typedef struct
{
    GPIO_TypeDef*   Port;
    uint16_t        Pin;
    LEDState_e      Level;
}LEDDeviceStrcut;



/* Exported constants --------------------------------------------------------*/

/* Exported macros -----------------------------------------------------------*/

#if 0
extern LEDDeviceStrcut LedRed;
extern LEDDeviceStrcut LedGreen;
extern LEDDeviceStrcut LedBlue;
#endif

#ifdef  FK103M5
extern LEDDeviceStrcut led;
#endif

/* Private macros ------------------------------------------------------------*/

/* Exported functions --------------------------------------------------------*/
void LEDInit(void);
void LEDOn(LEDDeviceStrcut led);
void LEDOff(LEDDeviceStrcut led);
void LEDToggle(LEDDeviceStrcut led);

/* Only for Pandora Board V2.61 */
void LEDFlow(uint8_t interval);


/* Private functions ---------------------------------------------------------*/


#endif /* __LED_H__ */
/**********************************END OF FILE*********************************/


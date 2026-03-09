#include "general_definiens.h"
/**************STM32 hardware pin setting*******************/
void SYS_GPIO_KPON();
void BEEF_GPIO_Init();
void KEY_GPIO_Init();
void KEY_EXTI_Init();
void OLED_GPIO_Init();
void OLED_IIC1_Init();
void MAX30102_GPIO_Init();
void MAX30102_IIC2_init();
void BuleTeeth_GPIO_Init();
void BuleTeeth_USART_Init(u32 bound);
void BattryVoltage_GPIO_Init();
void BV_LMT_ADC_Init();
void LMT70_GPIO_Init();
/**************STM32 hardware headerfiles*******************/
#include "OLED.h"
#include "MAX30102.h" 
#include "ADC.h"
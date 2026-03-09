#include "general_definiens.h"
#include "hard_ware.h"
#include "delay.h"
#include "menu.h"
int main()
{
	SystemInit();
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);//outside interrupt&remap need enable AFIO
	SYS_GPIO_KPON();
	KEY_GPIO_Init();
	KEY_EXTI_Init();
	BattryVoltage_GPIO_Init();
  BV_LMT_ADC_Init();
  LMT70_GPIO_Init();
	BuleTeeth_GPIO_Init();
	BuleTeeth_USART_Init(9600);
	OLED_GPIO_Init();
	OLED_IIC1_Init();
	OLED_Init();
	MAX30102_GPIO_Init();
	MAX30102_IIC2_init();
	MAX30102_Init(SPO2_MODE);
	while(1)
	{
		HR_Updata();
		OLED_ShowCNum(2,FCOLMIDDLE_8X(3),HR,3,ENABLE,FONTSIZE_8X16);
	}
	return 0;
}
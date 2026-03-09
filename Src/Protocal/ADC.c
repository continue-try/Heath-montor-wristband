#include "ADC.h"
#include "delay.h"
/*-----------------------------Digtal-----------------------------------*/
u16 BOTEMP = 0;
u16 BATVOLT = 0;
/*-----------------------------function-----------------------------------*/	
void Battry_Voltage_Updata()
{
	u16 v=Get_ADC_TimesTotal(ADC_Channel_0,10);
	BATVOLT=100.0*v/8275;//battery voltage transform ratio complement:8275(10*(4096*2)/(3.3V*3))
	Delay_ms(1000);
}
void Body_Temperture_Updata()
{
	u16 v=Get_ADC_TimesTotal(ADC_Channel_1,10);
	u32 Vtao = 80.6*v;
	BOTEMP= -0.0194*Vtao + 21297;
	Delay_ms(1000);
}
/*-----------------------------Basic function-----------------------------------*/	
u16 Get_ADC(u8 ch)   
{
  //Set the ADC rule transform channe,a sequence,cample time
	ADC_RegularChannelConfig(ADC1, ch, 1, ADC_SampleTime_239Cycles5);	//ADC1,ADC channe,sample cycle 239.5T	  			    
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);		//Enable ADC1 softward transform start
	 
	while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));//wait for end of transform
	return ADC_GetConversionValue(ADC1);	//return last ADC1 transform result
}

u16 Get_ADC_TimesTotal(u8 ch,u8 times)
{
	u16 total=0;
	u8 t;
	for(t=0;t<times;t++)
	{
		total+=Get_ADC(ch);
		Delay_ms(5);
	}
	return total;
} 


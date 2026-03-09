#include "hard_ware.h"
/*----------------------------on------------------------------------*/
void SYS_GPIO_KPON()
{
	GPIO_InitTypeDef GPIO_InitStructure; 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	GPIO_WriteBit(GPIOB, GPIO_Pin_0, (BitAction)(ENABLE));
}	
/*--------------------------BEEF-------------------------------------*/
void BEEF_GPIO_Init()
{
	GPIO_InitTypeDef GPIO_InitStructure; 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
}
/*-----------------------------KEY-----------------------------------*/
void KEY_GPIO_Init()
{
	GPIO_InitTypeDef GPIO_InitStructure; 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15 | GPIO_Pin_14 | GPIO_Pin_13 | GPIO_Pin_12; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
}
	
void KEY_EXTI_Init()
{
	EXTI_InitTypeDef EXTI_InitStructure; //Init struction
	NVIC_InitTypeDef NVIC_InitStructure;

	/*determine which GPIO Pin for outside interruption*/
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource15); //Select GPIOB for EXTI Line15(key 0)
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource14); //Select GPIOB for EXTI Line14(key 1)
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource13); //Select GPIOB for EXTI Line13(key 2)
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource12); //Select GPIOB for EXTI Line12(key 3)
	
	/*EXIT Init Struction Setting*/
	EXTI_InitStructure.EXTI_Line=EXTI_Line15|EXTI_Line14|EXTI_Line13|EXTI_Line12; //setting of all channels 
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt; 
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;//go down to reach interrupt
	EXTI_InitStructure.EXTI_LineCmd = ENABLE; 
	EXTI_Init(&EXTI_InitStructure); //EXTI Init function
	
	/*NVIC Init Struction Setting*/
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//interrupt Priority group setting	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02; 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02; //first respond
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;  
	NVIC_Init(&NVIC_InitStructure); 
}
/*-----------------------------OLED-----------------------------------*/
void OLED_GPIO_Init()
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	GPIO_PinRemapConfig(GPIO_Remap_I2C1,ENABLE);//remap to get I2C function to PB8~9
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;//IIC-SDA
 	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;//IIC-SCL
 	GPIO_Init(GPIOB, &GPIO_InitStructure);
}

void OLED_IIC1_Init()
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);
	I2C_DeInit(I2C1);
	I2C_InitTypeDef I2C_InitStructure;
	I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
	I2C_InitStructure.I2C_ClockSpeed = 120000;
	I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_16_9;//SCL lowlevel:highlevel=16:9 for leave more peroid to up level
	I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;//defualt stm give response
	I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;//stm as slave address bit num
	I2C_InitStructure.I2C_OwnAddress1 = 0x00;//stm as slave address to be called
	I2C_Init(I2C1, &I2C_InitStructure);
	I2C_Cmd(I2C1,ENABLE);
}
/*-----------------------------MAX30102-----------------------------------*/
void MAX30102_GPIO_Init()
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;//IIC-SCL/SDA
 	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	MAXPW_ABLE(ENABLE);
}

void MAX30102_IIC2_init()
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C2, ENABLE);
	I2C_DeInit(I2C2);
	I2C_InitTypeDef I2C_InitStructure;
	I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
	I2C_InitStructure.I2C_ClockSpeed = 120000;
	I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_16_9;//SCL lowlevel:highlevel=16:9 for leave more peroid to up level
	I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;//defualt stm give response
	I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;//stm as slave address bit num
	I2C_InitStructure.I2C_OwnAddress1 = 0x00;//stm as slave address to be called
	I2C_Init(I2C2, &I2C_InitStructure);
	I2C_Cmd(I2C2,ENABLE);
}
/*-----------------------------HC-05-----------------------------------*/	
void BuleTeeth_GPIO_Init()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOA, ENABLE);
	GPIO_PinRemapConfig(GPIO_Remap_USART1,ENABLE);//remap USART1 to PB6,7
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6; //ISART1_TX PB.6
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; //both side send together
	GPIO_Init(GPIOB, &GPIO_InitStructure); //init GPIOB.6
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7; //USART1_RX PB.7
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; //both side receive together
	GPIO_Init(GPIOB, &GPIO_InitStructure); //init GPIOB.7
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5; //state PB.5
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //receive 1 when link access
	GPIO_Init(GPIOB, &GPIO_InitStructure); //init GPIOB.5
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	LANYA_ABLE(ENABLE);//Hardware ENABLE Pin set 1
}

void BuleTeeth_USART_Init(u32 bound)
{
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	USART_DeInit(USART1); //reset USART1
	
	/*USART Setting*/
	USART_InitStructure.USART_BaudRate = bound; //bps
	USART_InitStructure.USART_WordLength = USART_WordLength_8b; //woed 8 bit
	USART_InitStructure.USART_StopBits = USART_StopBits_1; //one stop bit
	USART_InitStructure.USART_Parity = USART_Parity_No; //no ckeck bit
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; 
	USART_InitStructure.USART_Mode = USART_Mode_Rx|USART_Mode_Tx;//send and recive mode
	USART_Init(USART1, &USART_InitStructure); //init USART1
	
	/*if Recive then Interruption Setting*/
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;//USART Interrupt
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ; //The last Priority in NVIC group2
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3; 
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ channel Enable
	NVIC_Init(&NVIC_InitStructure); //init NVIC
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE); //open USART interruption 

	/*Enable USRAT1*/
	USART_Cmd(USART1, ENABLE); 
}
/*-----------------------------battry-----------------------------------*/
void BattryVoltage_GPIO_Init()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	 
	//PA0 as analog input pin                          
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		//analog input pin
	GPIO_Init(GPIOA, &GPIO_InitStructure);	
}
void BV_LMT_ADC_Init()
{
	ADC_InitTypeDef ADC_InitStructure; 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);	  //Enable ADC1 clock
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);   //set ADC division:6 72M/6=12M;ADC max frequent is 14M
	ADC_DeInit(ADC1);  //Reset ADC1
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;	//ADC mode:ADC1&ADC2 work in independent mode
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;	//Digtal to analog work in sigle channe mode
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;	//Digtal to analog work in first transform mode
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	//transform start by softward not interruption
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;	//ADC digtal align with right
	ADC_InitStructure.ADC_NbrOfChannel = 1;	//The number of rule transform ADC channe
	ADC_Init(ADC1, &ADC_InitStructure);	// ADC_InitStruct to init ADCx   
	ADC_Cmd(ADC1, ENABLE);	//Enable ADC1
	ADC_ResetCalibration(ADC1);	//Enable reset-align
	while(ADC_GetResetCalibrationStatus(ADC1));	//wait for restet end
	ADC_StartCalibration(ADC1);	 //Enable AD align
	while(ADC_GetCalibrationStatus(ADC1));	 //wait for align end
}	
/*-----------------------------LMT40-----------------------------------*/	
void LMT70_GPIO_Init()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	 
	//PA0 as analog input pin                          
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		//analog input pin
	GPIO_Init(GPIOA, &GPIO_InitStructure);	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;		
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}


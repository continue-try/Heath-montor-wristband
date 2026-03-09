#include "USART.h"
/*------------------------Send Function------------------------------*/
void BuleTeeth_Message_Send(u8 *Mes, u8 num)
{
	for(int i =0; i < num; i++ )
	{
		USART_SendData(USART1, Mes[i]);
		while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);
	}
}
/*------------------------Handler Function---------------------------*/
u8 USART1_RX_BUF[200]; //Receive Buff,USART_REC_LEN most
u16 USART1_RX_STA=0; //Receive situation mark:initvalue 0
																					/*bit15,		Receive finsih mark
																						bit14,		Receive 0x0d mark
																						bit13~0,	The number of access halfword*/
void USART1_IRQHandler(void) 
{
	u8 Res;
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)//RXNE interrupt reach 
	{
	Res =USART_ReceiveData(USART1); 
		if((USART1_RX_STA&0x8000)==0)//bit15:Receive unfinish
		{
			if(USART1_RX_STA&0x4000)//bit14:received 0x0d(first stop bit of receive)
			{
				if(Res!=0x0a)USART1_RX_STA=0;//reset as second stop bit miss
				else USART1_RX_STA|=0x8000;//write down bit15 as all stop bit get
			}
			else //bit14:not received 0x0d
			{
				if(Res==0x0d)USART1_RX_STA|=0x4000;//write down bit14 when Receiving 0x0d 
				else//normal receive data
				{
				USART1_RX_BUF[USART1_RX_STA&0X3FFF]=Res ;//save bit to receive buff
					USART1_RX_STA++;//bit13~0:add once to save next bit
					if(USART1_RX_STA>(199))USART1_RX_STA=0;//reset when num of bit longer than init leght
				}
			}
		}
	}
}
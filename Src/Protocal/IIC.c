#include "IIC.h"

/*-IIC1-*/
void IIC_SendHead(u8 slave_addr,u8 reg_addr)
{
	I2C_GenerateSTART(I2C1,ENABLE);	
	while(I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_MODE_SELECT) != SUCCESS);//I2C situation register to diffrent event
	
	I2C_Send7bitAddress(I2C1,slave_addr,I2C_Direction_Transmitter);//- for check:began,sent addr,regs empty and acked
	while(I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED) != SUCCESS);//- sending and acked,sent no new in
	
	I2C_SendData(I2C1,reg_addr);
	while(I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_BYTE_TRANSMITTING) != SUCCESS);
}

void IIC_ReceHead(u8 slave_addr,u8 reg_addr,FunctionalState iftimes)
{
	I2C_GenerateSTART(I2C1,ENABLE);
	while(I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_MODE_SELECT) != SUCCESS);//I2C situation register to diffrent event
	
	I2C_Send7bitAddress(I2C1,slave_addr,I2C_Direction_Transmitter);//- for check:began,sent addr,received	
	while(I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED) != SUCCESS); 
	
	I2C_SendData(I2C1,reg_addr);
	while(I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_BYTE_TRANSMITTED) != SUCCESS);
	
	I2C_GenerateSTART(I2C1,ENABLE);
	while(I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_MODE_SELECT) != SUCCESS);
	
	I2C_Send7bitAddress(I2C1,slave_addr,I2C_Direction_Receiver);
	while(I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED) != SUCCESS);
	
	if(!iftimes)
	{
		I2C_AcknowledgeConfig(I2C1,DISABLE);//no ack and set stopping before recieve
		I2C_GenerateSTOP(I2C1,ENABLE);
	}
}

void IIC_ReceTimesEnd()
{
	I2C_AcknowledgeConfig(I2C1,DISABLE);//no ack and set stopping before recieve
	I2C_GenerateSTOP(I2C1,ENABLE);
}

void IIC_AByteSend(u8 data)
{
	I2C_SendData(I2C1,data);
}

void IIC_BytesSend(const u8 *Data,u16 num, u16 start, FunctionalState ifsame)
{
	if(ifsame){
		u8 DataT = (u8)Data;
		for(u16 i = 0;i < num; i++)
		{
			I2C_SendData(I2C1,DataT);
			while(I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_BYTE_TRANSMITTING) != SUCCESS);
		}
	}
	else
	{
		for(u16 i = start;i < start + num; i++)
		{
			I2C_SendData(I2C1,Data[i]);
			while(I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_BYTE_TRANSMITTING) != SUCCESS);
		}
	}
}

u8 IIC_ByteEnter()
{
	u8 data=0;
	while(I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_BYTE_RECEIVED) != SUCCESS);
	data = I2C_ReceiveData(I2C1);
	I2C_AcknowledgeConfig(I2C1,ENABLE);//set back defualt ack
	return data;
}

void IIC_SendEnd()
{
	while(I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_BYTE_TRANSMITTED) != SUCCESS);
	I2C_GenerateSTOP(I2C1,ENABLE);
}

/*-IIC2-*/
void IIC_SendHead_(u8 slave_addr,u8 reg_addr)
{
	I2C_GenerateSTART(I2C2,ENABLE);	
	while(I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_MODE_SELECT) != SUCCESS);//I2C situation register to diffrent event
	
	I2C_Send7bitAddress(I2C2,slave_addr,I2C_Direction_Transmitter);//- for check:began,sent addr,regs enpty and acked
	while(I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED) != SUCCESS);//- sending and acked,sent no new in
	
	I2C_SendData(I2C2,reg_addr);
	while(I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_BYTE_TRANSMITTING) != SUCCESS);
}

void IIC_ReceHead_(u8 slave_addr,u8 reg_addr,FunctionalState iftimes)
{
	I2C_GenerateSTART(I2C2,ENABLE);
	while(I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_MODE_SELECT) != SUCCESS);//I2C situation register to diffrent event
	
	I2C_Send7bitAddress(I2C2,slave_addr,I2C_Direction_Transmitter);//- for check:began,sent addr,received	
	while(I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED) != SUCCESS); 
	
	I2C_SendData(I2C2,reg_addr);
	while(I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_BYTE_TRANSMITTED) != SUCCESS);
	
	I2C_GenerateSTART(I2C2,ENABLE);
	while(I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_MODE_SELECT) != SUCCESS);
	
	I2C_Send7bitAddress(I2C2,slave_addr,I2C_Direction_Receiver);
	while(I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED) != SUCCESS);
	
	if(!iftimes)
	{
		I2C_AcknowledgeConfig(I2C2,DISABLE);//no ack and set stopping before recieve
		I2C_GenerateSTOP(I2C2,ENABLE);
	}
}

void IIC_ReceTimesEnd_()
{
	I2C_AcknowledgeConfig(I2C2,DISABLE);//no ack and set stopping before recieve
	I2C_GenerateSTOP(I2C2,ENABLE);
}

void IIC_AByteSend_(u8 data)
{
	I2C_SendData(I2C2,data);
}

void IIC_BytesSend_(const u8 *Data,u16 num, u16 start, FunctionalState ifsame)
{
	if(ifsame){
		u8 DataT = (u8)Data;
		for(u16 i = 0;i < num; i++)
		{
			I2C_SendData(I2C2,DataT);
			while(I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_BYTE_TRANSMITTING) != SUCCESS);
		}
	}
	else
	{
		for(u16 i = start;i < start + num; i++)
		{
			I2C_SendData(I2C2,Data[i]);
			while(I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_BYTE_TRANSMITTING) != SUCCESS);
		}
	}
}

u8 IIC_ByteEnter_()
{
	u8 data=0;
	while(I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_BYTE_RECEIVED) != SUCCESS);
	data = I2C_ReceiveData(I2C2);
	I2C_AcknowledgeConfig(I2C2,ENABLE);//set back defualt ack
	return data;
}

void IIC_SendEnd_()
{
	while(I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_BYTE_TRANSMITTED) != SUCCESS);
	I2C_GenerateSTOP(I2C2,ENABLE);
}

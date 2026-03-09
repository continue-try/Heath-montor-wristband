#include "MAX30102.h"
#include "hr_spo2_caculation.h"
#include "OLED.h"
#include "delay.h"
#include "IIC.h"
/*------------------situation word----------------------*/
u8 SENOR_CALLBACK = 0x00;
/*------------------health value----------------------*/
u8 HR = 0;
u8 SPO2 = 0;
/********************Data Memory****************************/
u32 MAX30102_IRBuff[100] = {0};
u32 MAX30102_REDBuff[100] = {0};
/********************Function****************************/
void MAX30102_RegWrite(u8 reg_addr,u8 data)
{
	IIC_SendHead_(MAX30102_ADDR,reg_addr);	
	IIC_AByteSend_(data); 
	IIC_SendEnd_();
	Delay_ms(5);
}

u8 MAX30102_ARegRead(u8 reg_addr)
{
	u8 data = 0;
	IIC_ReceHead_(MAX30102_ADDR,reg_addr,DISABLE);
	data = IIC_ByteEnter_();
	return data;
}

void MAX30102_RegReadTimes(u8 reg_addr, u8 *byte_index, u8 times)
{
	u8 i = 0;
	IIC_ReceHead_(MAX30102_ADDR,reg_addr,ENABLE);
	for(; i < times - 1;i++)
	{
		*(byte_index + i) = IIC_ByteEnter_();
	}
	IIC_ReceTimesEnd_();
	*(byte_index + i) = IIC_ByteEnter_();
}

void MAX30102_Init(u8 mode)
{
	MAX30102_ReStart();
	MAX30102_RegWrite(REG_INTR_ENABLE_1,0xC0);//使能寄存器将满和寄存器更新两个中断
	MAX30102_RegWrite(REG_INTR_ENABLE_2,0x00);
	MAX30102_RegWrite(REG_FIFO_WR_PTR,0x00);//清空FIFO
	MAX30102_RegWrite(REG_OVR_COUNTER,0x00);
	MAX30102_RegWrite(REG_FIFO_RD_PTR,0x00);
	MAX30102_RegWrite(REG_FIFO_CONFIG,0x4F);//四次采样平均，将满触发值为15，寄存器读后才写
	MAX30102_RegWrite(REG_MODE_CONFIG,mode);//芯片模式设置
	MAX30102_RegWrite(REG_SPO2_CONFIG,0x27);//ADC量程4096nA电流，采样率100Hz,LED脉宽411us（采样精度18bit）
	MAX30102_RegWrite(REG_LED1_PA,0x24);//LED1电流7mA
	MAX30102_RegWrite(REG_LED2_PA,0x24);//LED2电流7mA
	MAX30102_RegWrite(REG_PILOT_PA,0x7F);//心率和心率血氧模式的LED电流为25mA
}

void MAX30102_ShutDown()
{
	MAX30102_RegWrite(REG_MODE_CONFIG,DOWN_MODE);
}

void MAX30102_ReStart()
{
	MAX30102_RegWrite(REG_MODE_CONFIG,REON_MODE);//芯片复位
}

u8	 MAX30102_GetStatusCl()
{
	u8 flag = 0;
	flag = (MAX30102_ARegRead(REG_INTR_STATUS_1) & 0xF1) | (MAX30102_ARegRead(REG_INTR_STATUS_2) & 0x02);
	//xxxx--xx:依次为A_FULL，PPG_RDY，ALC_OVF，PROX_INT，DIE_TEMP_RDY，PWR_RDY
	return flag;
}

u8   MAX30102_GetSampleNum()
{
	u8	wp = MAX30102_ARegRead(REG_FIFO_WR_PTR);
	u8	rp	=	MAX30102_ARegRead(REG_FIFO_RD_PTR);
	if(wp == rp){return 0;}
	else
	{
		if(wp > rp){return wp - rp;}
		else{return wp + 32 - rp;}
	}
}

void MAX30102_GetOneSample(u32 *red,u32 *ir)
{
	u8 data_array[6] = {0};
	MAX30102_RegReadTimes(REG_FIFO_DATA,data_array,6);
	*(red) = ((u32)(data_array[0] << 16) | (u16)(data_array[1] << 8) | data_array[2] ) & 0x0003FFFF;
	*(ir) = ((u32)(data_array[3] << 16) | (u16)(data_array[4] << 8) | data_array[5] ) & 0x0003FFFF;
}

void MAX30102_BuffUpdata()
{
	u8 Index = 0;
	u8 sampleNum = 0;
	while(Index < 100)
	{
		sampleNum = MAX30102_GetSampleNum();
		while(sampleNum > 0 && Index < 100)
		{
			MAX30102_GetOneSample(MAX30102_REDBuff + Index, MAX30102_IRBuff +Index);
			Index ++;
			sampleNum --;
		}
	}
}

FlagStatus Finger_Check()
{
	if(Average(MAX30102_IRBuff,100) < 100000)
	{
		return RESET;
	}
	else{return SET;}
}

void HR_Updata()
{
	MAX30102_BuffUpdata();
	if(Finger_Check())
	{
		s32 IR_Value[100] = {0};
		u8 IR_Pos[15] = {0};
		u32 IR_Ave = Average(MAX30102_IRBuff,100);
		for(int i=0; i < 100; i++)
		{
			IR_Value[i] = IR_Ave - MAX30102_IRBuff[i];
		}
		u8 IR_PNum = ZonePeakFind(IR_Value, 100, IR_Pos, 0, 15);
		u8 IR_PNumA = ClosePeakLoss(IR_Value, IR_Pos, IR_PNum, 6);
		HRCalculate(IR_Pos, IR_PNumA, 15, 25);
		SENOR_CALLBACK &= 0xEF;
	}
	else{SENOR_CALLBACK |= 0x10;HR = 0;}
}

void HR_SPO2_Updata()
{
	 MAX30102_BuffUpdata();
	if(Finger_Check())
	{
		s32 IR_Value[100] = {0};
		s32 RED_Value[100] = {0};
		u8 IR_Pos[15] = {0};
		u8 RED_Pos[15] = {0};
		u32 IR_Ave = Average(MAX30102_IRBuff,100);
		u32 RED_Ave = Average(MAX30102_REDBuff,100);
		for(int i=0; i < 100; i++)
		{
			IR_Value[i] = IR_Ave - MAX30102_IRBuff[i];
		}
		for(int i=0; i < 100; i++)
		{
			RED_Value[i] = RED_Ave - MAX30102_REDBuff[i];
		}
		u8 IR_PNum = ZonePeakFind(IR_Value, 100, IR_Pos, 0, 15);
		u8 IR_PNumA = ClosePeakLoss(IR_Value, IR_Pos, IR_PNum, 5);
		u8 RED_PNum = ZonePeakFind(RED_Value, 100, RED_Pos, 0, 15);
		u8 RED_PNumA = ClosePeakLoss(RED_Value, RED_Pos, RED_PNum, 5);
		if(HRCalculate(IR_Pos, IR_PNumA, 15, 25))
		{SPO2Calculate(IR_Pos,IR_PNum,RED_Pos,RED_PNum,15);}
		else{SPO2 = 0;}
	}
	else{
	HR = 0;
	SPO2 = 0;
	}
}

void MAX30102_Test()
{
	HR_SPO2_Updata();
	OLED_ShowNum(1,1,HR,3,ENABLE,FONTSIZE_8X16);
}
#include "stm32f10x.h"

/********************slave address****************************/
#define MAX30102_ADDR							0xAE
/**********************chip mode******************************/
#define DOWN_MODE									0x80
#define REON_MODE									0x40
#define HR_MODE										0x02
#define SPO2_MODE									0x03
#define MUTI_MODE									0x07
/********************Register Map****************************/
#define REG_MODE_CONFIG						0x09
#define REG_INTR_ENABLE_1					0x00
#define REG_INTR_STATUS_1					0x01
#define REG_INTR_STATUS_2					0x02
#define REG_INTR_ENABLE_2					0x03
#define REG_FIFO_WR_PTR						0x04
#define REG_OVR_COUNTER						0x05
#define REG_FIFO_RD_PTR						0x06
#define REG_FIFO_DATA							0x07
#define REG_FIFO_CONFIG						0x08
#define REG_SPO2_CONFIG						0x0A
#define REG_LED1_PA								0x0C
#define REG_LED2_PA								0x0D
#define REG_PILOT_PA							0x10
#define REG_REV_ID								0xFE
#define REG_PART_ID								0xFF
/********IIC Transform protocol format for slave-Read&slave-Write********/
void MAX30102_RegWrite(u8 reg_addr,u8 data);
u8   MAX30102_ARegRead(u8 reg_addr);
void MAX30102_RegReadTimes(u8 reg_addr, u8 *byte_index,u8 times);
/*********************command init&data award****************************/
void MAX30102_Init(u8 mode);
void MAX30102_ShutDown();
void MAX30102_ReStart();
u8	 MAX30102_GetStatusCl();
u8   MAX30102_GetSampleNum();
void MAX30102_GetOneSample(u32 *red,u32 *ir);
/************************data save&process*******************************/
void MAX30102_BuffUpdata();
FlagStatus Finger_Check();
/*************************health value updata****************************/
void HR_Updata();
void HR_SPO2_Updata();
/*********************test program***************************************/
void MAX30102_Test();
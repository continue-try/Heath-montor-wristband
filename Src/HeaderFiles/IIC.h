#include "stm32f10x.h"
/***********PRE DEFINE*************/

/***********IIC Transform protocol format*************/
/*-IIC1-*/
void IIC_SendHead(u8 slave_addr,u8 reg_addr);
void IIC_ReceHead(u8 slave_addr,u8 reg_addr,FunctionalState iftimes);
void IIC_AByteSend(u8 data);
void IIC_BytesSend(const u8 *Data,u16 num, u16 start, FunctionalState ifsame);
u8 	 IIC_ByteEnter();
void IIC_SendEnd();
void IIC_ReceTimesEnd();
/*-IIC2-*/
void IIC_SendHead_(u8 slave_addr,u8 reg_addr);
void IIC_ReceHead_(u8 slave_addr,u8 reg_addr,FunctionalState iftimes);
void IIC_AByteSend_(u8 data);
void IIC_BytesSend_(const u8 *Data, u16 num, u16 start, FunctionalState ifsame);
u8   IIC_ByteEnter_();
void IIC_SendEnd_();
void IIC_ReceTimesEnd_();
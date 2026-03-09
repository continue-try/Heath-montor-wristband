#include "stm32f10x.h"
/*equation:
	AliasAddr = 
	bit_band_base(fisrt addr num+0x02000000)+(byte_offset(last 5 addr num)*2^5+bit_num*2^2)*/
						
#define BITBAND(addr, bitnum) ((addr & 0xF0000000)+0x2000000+((addr&0xFFFFF)<<5)+(bitnum<<2)) 
#define MEM_ADDR(addr) *((volatile unsigned long *)(addr)) 
#define BIT_ADDR(addr, bitnum) MEM_ADDR(BITBAND(addr, bitnum)) 

/*input&output register address(addr) GPIOx*/
#define GPIOA_ODR_Addr (GPIOA_BASE+12) //0x4001080C 
#define GPIOB_ODR_Addr (GPIOB_BASE+12) //0x40010C0C 
#define GPIOC_ODR_Addr (GPIOC_BASE+12) //0x4001100C 
#define GPIOA_IDR_Addr (GPIOA_BASE+8) //0x40010808 
#define GPIOB_IDR_Addr (GPIOB_BASE+8) //0x40010C08 
#define GPIOC_IDR_Addr (GPIOC_BASE+8) //0x40011008 

/*bit_num under register address(bitnum) Pin_num*/
#define PAout(n) BIT_ADDR(GPIOA_ODR_Addr,n) //output
#define PAin(n) BIT_ADDR(GPIOA_IDR_Addr,n) //input
#define PBout(n) BIT_ADDR(GPIOB_ODR_Addr,n)
#define PBin(n) BIT_ADDR(GPIOB_IDR_Addr,n)
#define PCout(n) BIT_ADDR(GPIOC_ODR_Addr,n)
#define PCin(n) BIT_ADDR(GPIOC_IDR_Addr,n)
/*--------------GPIO define-------------------------------*/
#define KEY0 PBin(15)  // PB15
#define KEY1 PBin(14)  // PB14
#define KEY2 PBin(13)  // PB13 
#define KEY3 PBin(12)  // PB12
#define BEEF PAin(6)	 // PA6
#define SYSTM_OFF					GPIO_WriteBit(GPIOB, GPIO_Pin_0, (BitAction)(DISABLE));
#define LANYA_ABLE(x)			GPIO_WriteBit(GPIOA, GPIO_Pin_10, (BitAction)(x));
#define MAXPW_ABLE(x)			GPIO_WriteBit(GPIOA, GPIO_Pin_8, (BitAction)(x));
#define LMTST_ABLE(x)			GPIO_WriteBit(GPIOA, GPIO_Pin_9, (BitAction)(x));
/*--------------health value----------------------------*/
extern u8 HR;
extern u8 SPO2;
extern u16 BOTEMP;
extern u16 BATVOLT;
/*--------------Status word-----------------------------*/
extern u8 MENU_PAGE;
extern u8 SENOR_CALLBACK;
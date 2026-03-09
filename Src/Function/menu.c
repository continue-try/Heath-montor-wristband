#include "menu.h"
#include "OLED.h"
#include "Font.h"

/********************Control word****************************/
u8 MENU_PAGE = 0x20;
//xx,xx,xxxx:pointer:00->1,01->1,10->2,11->3;control:00flesh,01skip->10updata->11draw->00;page:0~15(total:16)
/********************Function****************************/
void Menu_Cursor()
{
	if((MENU_PAGE&0x0F)==0)//screen 0
	{
		if((MENU_PAGE & 0xC0) == 0x00)//MENU_PAGE:00xxxxxx point first line
		{
			OLED_DrawRect(0,0,64,32);
		}	
		if((MENU_PAGE & 0xC0) == 0x40)//MENU_PAGE:01xxxxxx point second line
		{ 
			OLED_DrawRect(64,0,64,32);
		}	
		if((MENU_PAGE & 0xC0) == 0x80)//MENU_PAGE:10xxxxxx point third line
		{ 
			OLED_DrawRect(0,32,64,32);
		}	
		if((MENU_PAGE & 0xC0) == 0xC0)//MENU_PAGE;11xxxxxx point forth line
		{ 
			OLED_DrawRect(64,32,64,32);
		}
	}
	else
	{
		if((MENU_PAGE & 0xC0) == 0x00)//MENU_PAGE:0001xxxx point first line
		{
			OLED_BuffUpdata(0,48,128,16,0);
			OLED_InverseArea(0,0,128,16);
		}	
		if((MENU_PAGE & 0xC0) == 0x40)//MENU_PAGE:0010xxxx point second line
		{ 
			OLED_BuffUpdata(0,0,128,16,0);
			OLED_InverseArea(0,16,128,16);
		}	
		if((MENU_PAGE & 0xC0) == 0x80)//MENU_PAGE:0100xxxx point third line
		{ 
			OLED_BuffUpdata(0,16,128,16,0);
			OLED_InverseArea(0,32,128,16);
		}	
		if((MENU_PAGE & 0xC0) == 0xC0)//MENU_PAGE;1000xxxx point forth line
		{ 
			OLED_BuffUpdata(0,32,128,16,0);
			OLED_InverseArea(0,48,128,16);
		}
	}
}

void Menu_StaticUpdata()
{
if((MENU_PAGE&0x30) == 0x20){
	if((MENU_PAGE & 0x0F) == 0)
	{OLED_ShowImg(0,0,128,64,ENABLE,DISABLE,Image_desk);}
		if((MENU_PAGE & 0x0F) == 1)
		{
			OLED_ShowChineseN(1,1,DISABLE,"心率");
			OLED_ShowChar(1,FCOLLES16_6X(3),':',DISABLE,FONTSIZE_6X8);
		}
			if((MENU_PAGE & 0x0F) == 2)
				{OLED_ShowString(FLINEUPS16_X8(1),FCOLMIDDLE_6X(5),"PAGE2",DISABLE,FONTSIZE_6X8);}
				if((MENU_PAGE & 0x0F) == 3)
					{OLED_ShowString(FLINEUPS16_X8(1),FCOLMIDDLE_6X(5),"PAGE3",DISABLE,FONTSIZE_6X8);}
					if((MENU_PAGE & 0x0F) == 4)
						{OLED_ShowString(FLINEUPS16_X8(1),FCOLMIDDLE_6X(5),"PAGE4",DISABLE,FONTSIZE_6X8);}
						if((MENU_PAGE & 0x0F) == 5)
							{OLED_ShowString(FLINEUPS16_X8(1),FCOLMIDDLE_6X(5),"PAGE5",DISABLE,FONTSIZE_6X8);}
							if((MENU_PAGE & 0x0F) == 6)
								{OLED_ShowString(FLINEUPS16_X8(1),FCOLMIDDLE_6X(5),"PAGE6",DISABLE,FONTSIZE_6X8);}
								if((MENU_PAGE & 0x0F) == 7)
									{OLED_ShowString(FLINEUPS16_X8(1),FCOLMIDDLE_6X(5),"PAGE7",DISABLE,FONTSIZE_6X8);}
									MENU_PAGE|=0x30;
								}
}

void Menu_StaticDraw()
{
	if((MENU_PAGE&0x30) == 0x30)
	{
		OLED_BuffUpdata(0,0,128,64,DISABLE);
		MENU_PAGE &= 0xCF;
	}
}

void Menu_SkipRoot(u8 page, u8 f_to_p, u8 s_to_p, u8 t_to_p, u8 fo_to_p)
{
	u8 Page_Save = MENU_PAGE&0x0F;
	if(Page_Save == page && (MENU_PAGE&0x30) == 0x10)
	{
		MENU_PAGE &= 0xC0;MENU_PAGE |= 0x20;
		if((MENU_PAGE & 0xC0) == 0x00){MENU_PAGE += f_to_p;
			if(Page_Save != f_to_p){MENU_PAGE &= 0x3F;
				OLED_Clear();OLED_BuffClearAll();}}
			else if((MENU_PAGE & 0xC0) == 0x40){MENU_PAGE += s_to_p;
				if(Page_Save != s_to_p){MENU_PAGE &= 0x3F;
					OLED_Clear();OLED_BuffClearAll();}}
				else if((MENU_PAGE & 0xC0) == 0x80){MENU_PAGE += t_to_p;
					if(Page_Save != t_to_p){MENU_PAGE &= 0x3F;
						OLED_Clear();OLED_BuffClearAll();}}
					else{MENU_PAGE += fo_to_p;
						if(Page_Save != fo_to_p){MENU_PAGE &= 0x3F;
							OLED_Clear();OLED_BuffClearAll();}}
	}
}

void Menu_Skip()
{
	Menu_SkipRoot(0, 1, 2, 3, 4);
	Menu_SkipRoot(1, 5, 1, 1, 1);
	Menu_SkipRoot(2, 6, 2, 2, 2);
	Menu_SkipRoot(3, 7, 3, 3, 3);
	Menu_SkipRoot(4, 4, 4, 4, 4);
}


void Menu_Show()
{
	Menu_Skip();
	Menu_StaticUpdata();
	Menu_StaticDraw();
	if((MENU_PAGE & 0x0F) == 1)
	{
		if(SENOR_CALLBACK&0x10)
		{OLED_ShowString(2,FCOLMIDDLE_8X(16),"finger out point",ENABLE,FONTSIZE_8X16);}
		else{OLED_ShowCNum(2,FCOLMIDDLE_8X(3),HR,3,ENABLE,FONTSIZE_8X16);}
	}
	Menu_Cursor();
//	OLED_BuffUpdata(0,0,128,64,DISABLE);
}
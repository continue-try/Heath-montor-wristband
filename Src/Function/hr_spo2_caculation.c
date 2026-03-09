#include "hr_spo2_caculation.h"
/*---------------------basic fuction------------------------*/
u8 	DiffABS(u8 x1, u8 x2)
{
	return (x1 > x2) ? (x1 - x2) : (x2 - x1);
}

u32 Average(u32 *datas, u8 dnum)
{
	u32 ts = datas[0];
	u32 ad = 0;
	u32 di = 0;
	for(u8 i = 1; i < dnum; i++)
	{
		if(datas[0] > datas[i])
		{di += (datas[0] - datas[i]);}
		else{ad += (datas[i] - datas[0]);}
	}
	if(ad > di){ts +=(ad - di)/100;}
	else{ts -=(u8)(di - ad)/100;}
	return ts;
}
u8	MaxIndex(u32 *datas, u8 spos,u8 epos)
{
	
	u8 maxIndex = 0;
	for(int i = spos; i < epos; i++)
	{
		if(datas[i] > datas[maxIndex])
		{
			maxIndex = i;
		}
	}
	return maxIndex;
}

void BubbleSort(u8 *datas, u8 dnum)
{
	for(int i = 0; i < dnum; i++)
	{
		for(int j = i; j < dnum - 1; j++)
		{
			if(datas[i] > datas[j + 1])
			{
				u8 temp = datas[i];
				datas[i] = datas[j + 1];
				datas[j + 1] = temp;
			}
		}
	}
}

void Index_Value_BubbleSort(s32 *datas, u8 *Index, u8 dnum)
{
	for(int i = 0; i < dnum; i++)
	{
		for(int j = i; j < dnum - 1; j++)
		{
			if(datas[Index[i]] < datas[Index[j + 1]])
			{
				u8 temp = Index[i];
				Index[i] = Index[j + 1];
				Index[j + 1] = temp;
			}
		}
	}
}

s32 LineXtoY(s8 ydiff, s8 xdiff , s8 xdiff_, s8 diffy)
{
	s32 yneed = 0;
	yneed = ydiff * xdiff_;
	yneed = yneed / xdiff + diffy;
	return yneed;
}
/*---------------------fuction------------------------*/
u8 ZonePeakFind(s32 *datas, u8 dnum, u8 *peakpos, u8 lowerlim, u8 maxpnum)
{
	u8 i = 1;
	u8 PNum = 0;
	u8 Pose = 0;
	while(i < dnum - 1)
	{
		if(datas[i] > lowerlim && datas[i] > datas[i-1])//up
		{
			Pose = 1;
			while(i + Pose < dnum - 1 && datas[i] == datas[i + Pose])
			{Pose ++;}//plant
			if(PNum < maxpnum && datas[i] > datas[i + Pose])
			{
				peakpos[PNum] = i;
				PNum ++;
				i += Pose + 1;
			}//peakfind
			else{i += Pose;}
		}
		else//down
		{
			i++;
		}
	}
	return PNum;
}

u8 ClosePeakLoss(s32 *peakval, u8 *peakpos, u8 pnum, u8 closelim)
{
	Index_Value_BubbleSort(peakval, peakpos, pnum);
	u8 pNumA = pnum;
	for(s8 i = -1; i < pNumA; i++)
	{
		pnum = pNumA;
		pNumA = i + 1;
		for(int j = i + 1; j < pnum; j++)
		{
			u8 d = (i == -1) ? peakpos[j] : DiffABS(peakpos[j],peakpos[i]);
			if(d > closelim){peakpos[pNumA] = peakpos[j]; pNumA++;}
			else{continue;}
		}
	}
	BubbleSort(peakpos, pNumA);
	return pNumA;
}

ErrorStatus HRCalculate(u8 *peakdis, u8 pnuma, u8 posize, u16 samplefre)
{
	if(pnuma > 1)
	{
		u16 sum = 0;
		u8  disN = pnuma - 1;
		for(int i = 0; i < pnuma - 1; i++)
		{
			sum += peakdis[i + 1] - peakdis[i];
		}
		HR = 60.0*samplefre*disN/sum;
		return SUCCESS;
	}
	else{return ERROR;}
}
void SPO2Calculate(u8 *peakdis, u8 pnuma, u8 *peakdis_, u8 pnuma_, u8 posize)
{
	int16_t i;	
}
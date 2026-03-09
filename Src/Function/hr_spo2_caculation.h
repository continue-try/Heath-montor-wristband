#include "general_definiens.h"

/*---------------------fuction------------------------*/
u8 	DiffABS(u8 x1, u8 x2);
u8	MaxIndex(u32 *datas, u8 spos, u8 epos);
u32 Average(u32 *datas, u8 dnum);
void BubbleSort(u8 *datas, u8 dnum);
void Index_Value_BubbleSort(s32 *datas, u8 *Index, u8 dnum);
s32 LineXtoY(s8 ydiff, s8 xdiff , s8 xdiff_, s8 diffy);
u8 ZonePeakFind(s32 *datas, u8 dnum, u8 *peakpos, u8 lowerlim, u8 maxpnum);
u8 ClosePeakLoss(s32 *peakval, u8 *peakpos, u8 pnum, u8 closelim);
ErrorStatus HRCalculate(u8 *peakdis, u8 pnuma, u8 posize, u16 samplefre);
void SPO2Calculate(u8 *peakdis, u8 pnuma, u8 *peakdis_, u8 pnuma_, u8 posize);
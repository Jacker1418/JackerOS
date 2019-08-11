#ifndef __MODESWITCH_H__
#define __MODESWITCH_H__

#include "Types.h"

void readCPUID( DWORD in_dwEAX, DWORD* out_dwEAX, DWORD* out_dwEBX, DWORD* out_dwECX, DWORD* out_dwEDX );
void switchExcute64bitKernel(void);

#endif

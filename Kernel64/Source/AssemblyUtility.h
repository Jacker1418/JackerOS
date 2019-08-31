#ifndef __ASSEMBLYUTILITY_H__
#define __ASSEMBLYUTILITY_H__

#include "Types.h"

BYTE inPortByte( WORD wPort);

void outPOrtByte( WORD wPort, BYTE bData);

void kLoadGDTR( QWORD in_GDTRAddress);
void kLoadTR( WORD in_TS_SegmentOffset);
void kLOadIDTR( QWORD in_IDTRAddress);

#endif

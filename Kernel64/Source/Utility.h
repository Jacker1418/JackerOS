#ifndef __UTILITY_H__
#define __UTILITY_H__

#include "Types.h"

void setMemory( void* in_destination, BYTE in_data, int in_size);
int copyMemory( void* in_destination, const void* in_source, int in_size);
int cmpMemory( const void* in_destination, const void* in_source, int in_size);

void printString(int in_x, int in_y, const char* pString);
#endif

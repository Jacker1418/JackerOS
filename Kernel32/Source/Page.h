#ifndef __PAGE_H__
#define __PAGE_H__

#include "Types.h"

#define PAGE_FLAGS_P    0x00000001 //Present
#define PAGE_FLAGS_RW   0x00000002 //Read/Write
#define PAGE_FLAGS_US   0x00000004 // User / Supervisor
#define PAGE_FLAGS_PWT  0x00000008 // Page Level Write-Through
#define PAGE_FLAGS_PCD  0x00000010 // Page Level Cache Disable
#define PAGE_FLAGS_A    0x00000020 // Accessed
#define PAGE_FLAGS_D    0x00000040 // Dirty
#define PAGE_FLAGS_PS   0x00000080 // Page Size
#define PAGE_FLAGS_G    0x00000100 // Global
#define PAGE_FLAGS_PAT  0x00001000 // Page Attribute Table Index
#define PAGE_FLAGS_EXB  0x80000000 // Excute Disable
#define PAGE_FLAGS_DEFAULT   PAGE_FLAGS_P | PAGE_FLAGS_RW 
#define PAGE_TABLE_SIZE 0x1000
#define PAGE_MAX_ENTRY_COUNT    512
#define PAGE_DEFULAT_SIZE   0x200000

#pragma pack(push , 1)

typedef struct PageTableEntry{

    DWORD   dwAttribute_Lower;
    DWORD   dwAttribute_Higher;
} PML4, PDPT, PD, PT;

#pragma pack (pop)


void initializePageTable(void);
void setPageEntryData(PT* out_pt, DWORD in_dwAttribute_Higher, DWORD in_dwAttribute_Lower, DWORD in_dwLowerFlags, DWORD in_dwHigherFlags);

#endif


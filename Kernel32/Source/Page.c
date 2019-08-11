#include "Page.h"

void initializePageTable(void){
    PML4    *pPML4_Entry;
    PDPT    *pPDPT_Entry;
    PD      *pPD_Entry;

    DWORD   mappingAddress;

    int i;

    pPML4_Entry = (PML4 *)(0x100000);

    setPageEntryData( &(pPML4_Entry[0]), 0x00, 0x101000, PAGE_FLAGS_DEFAULT, 0);
    for(i = 1; i < PAGE_MAX_ENTRY_COUNT; i++){
        setPageEntryData( &(pPML4_Entry[i]), 0, 0, 0, 0);
    }

    pPDPT_Entry = (PDPT *)(0x101000);
    for(i = 0; i < 64; i++){
        setPageEntryData( &(pPDPT_Entry[i]), 0x00, 0x102000 + (i + PAGE_TABLE_SIZE), PAGE_FLAGS_DEFAULT, 0);
    }

    for(i = 64; i < PAGE_MAX_ENTRY_COUNT; i++){
        setPageEntryData( &(pPDPT_Entry[i]), 0, 0, 0, 0);
    }

    pPD_Entry = (PD *)(0x102000);
    mappingAddress = 0;
    for(i = 0; i < PAGE_MAX_ENTRY_COUNT * 64; i++){
        setPageEntryData( &(pPD_Entry[i]), (i * (PAGE_DEFULAT_SIZE >> 20) ) >> 12, mappingAddress, PAGE_FLAGS_DEFAULT | PAGE_FLAGS_PS, 0);
        mappingAddress += PAGE_DEFULAT_SIZE;
    }

}

void setPageEntryData(PT* out_pt, DWORD in_dwAttribute_Higher, DWORD in_dwAttribute_Lower, DWORD in_dwLowerFlags, DWORD in_dwHigherFlags){
    out_pt->dwAttribute_Lower = in_dwAttribute_Lower | in_dwLowerFlags;
    out_pt->dwAttribute_Higher = (in_dwAttribute_Higher & 0xFF) | in_dwHigherFlags;
}



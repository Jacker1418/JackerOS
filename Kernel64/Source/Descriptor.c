#include "Descriptor.h"
#include "Utility.h"

void initialize_GDT_Table_Tss(void){

    GDTR*   pstGDTR;
    GDT_ENTRY8* pstEntry;
    TSS_SEGMENT* pstTSS;

    int i;

    pstGDTR = (GDTR *)GDTR_START_ADDRESS;
    pstEntry = (GDT_ENTRY8 *)(GDTR_START_ADDRESS + sizeof(GDTR));
    
    pstGDTR->wLimit = GDT_TABLE_SIZE - 1;
    pstGDTR->qwBaseAddress = (QWORD) pstEntry;

    pstTSS = (TSS_SEGMENT *) ( (QWORD)pstEntry + GDT_TABLE_SIZE );

    setGDT_Entry8( &(pstEntry[0]), 0, 0, 0, 0, 0);
    setGDT_Entry8( &(pstEntry[1]), 0, 0xFFFF, GDT_FLAGS_UPPER_CODE, GDT_FLAGS_LOWER_KERNELCODE, GDT_TYPE_CODE);
    setGDT_Entry8( &(pstEntry[2]), 0, 0xFFFF, GDT_FLAGS_UPPER_DATA, GDT_FLAGS_LOWER_KERNELDATA, GDT_TYPE_DATA);

    setGDT_Entry16( (GDT_ENTRY16 *) &(pstEntry[3]), (QWORD)pstTSS, sizeof(TSS_SEGMENT) - 1, GDT_FLAGS_UPPER_TSS, GDT_FLAGS_LOWER_TSS, GDT_TYPE_TSS);

    initialize_TSS_Segment(pstTSS);

}
void initialize_TSS_Segment( TSS_SEGMENT* out_tss ){

    setMemory( out_tss, 0, sizeof(TSS_SEGMENT));
    out_tss->qwIST[0] = IST_START_ADDRESS + IST_SIZE;
    out_tss->wIOMapBaseAddress = 0xFFFF;

}
void initialize_IDT_Tables(void){

    IDTR* pstIDTR;
    IDT_ENTRY* pstEntry;

    int i;

    pstIDTR = (IDTR *)IDTR_START_ADDRESS;
    pstEntry = (IDT_ENTRY *)(IDTR_START_ADDRESS + sizeof(IDTR));
    
    pstIDTR->qwBaseAddress = (QWORD) pstEntry;
    pstIDTR->wLimit = IDT_TABLE_SIZE - 1;

    for(i = 0; i < IDT_MAX_ENTRY_COUNT; i++){
        setIDT_Entry( &(pstEntry[i]), dummyHandler, 0x08, IDT_FLAGS_IST0, IDT_FLAGS_KERNEL, IDT_TYPE_INTERRUPT);
    }
}

void setGDT_Entry8( GDT_ENTRY8* out_entry, DWORD in_base_address, DWORD in_limit, BYTE in_upper_flags, BYTE in_lower_flags, BYTE in_type){

    out_entry->wLowerLimit = in_limit & 0xFFFF;
    out_entry->wLowerBaseAddress = in_base_address & 0xFFFF;
    out_entry->bUpperBaseAddress1 = (in_base_address >> 16) & 0xFF;
    out_entry->bTypeAndLowerFlag = in_lower_flags | in_type;
    out_entry->bUpperLimitAndUpperFlag = ( (in_limit >> 16) & 0x0F) | in_upper_flags;
    out_entry->bUpperBaseAddress2 = (in_base_address >> 24) & 0xFF;

}
void setGDT_Entry16( GDT_ENTRY16* out_entry, QWORD in_base_address, DWORD in_limit, BYTE in_upper_flags, BYTE in_lower_flags, BYTE in_type){

    out_entry->wLowerLimit = in_limit & 0xFFFF;
    out_entry->wLowerBaseAddress = in_base_address & 0xFFFF;
    out_entry->bMiddleBaseAddress1 = (in_base_address >> 16) & 0xFF;
    out_entry->bTypeAndLowerFlag = in_lower_flags | in_type;
    out_entry->bUpperLimitAndUpperFlag = ( (in_limit >> 16 ) & 0x0F ) | in_upper_flags;
    out_entry->bMiddleBaseAddress2 = (in_base_address >> 24) & 0xFF;
    out_entry->dwUpperBaseAddress = in_base_address >> 32;
    out_entry->dwReserved = 0;

}

void setIDT_Entry( IDT_ENTRY* out_entry, void* in_handler, WORD in_selector, BYTE in_ist, BYTE in_flags, BYTE in_type){

    out_entry->wLowerBaseAddress = (QWORD) in_handler & 0xFFFF;
    out_entry->wSegmentSelector = in_selector;
    out_entry->bIST = in_ist & 0x3;
    out_entry->bTypeAndFlags = in_type | in_flags;
    out_entry->wMiddleBaseAddress = ( (QWORD) in_handler >> 16) & 0xFFFF;
    out_entry->dwUpperBaseAddress = (QWORD) in_handler >> 32;
    out_entry->dwReserved = 0;

}
void dummyHandler(void){ 

    printString( 0, 0, "=================================================" );
    printString( 0, 1, "       Dummy Interrupt Handler Execute~!!!       " );
    printString( 0, 2, "        Interrupt or Exception Occure~!!!        " );
    printString( 0, 3, "=================================================" );

    while(1);
}
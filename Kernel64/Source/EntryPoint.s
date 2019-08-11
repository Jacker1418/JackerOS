[BITS 64]

SECTION .text

extern Main

START:

    MOV ax, 0x10
    MOV ds, ax
    MOV es, ax
    MOV fs, ax
    MOV gs, ax
    
    MOV ss, ax
    MOV rsp, 0x6FFFF8
    MOV rbp, 0x6FFFF8

    CALL Main

    JMP $

    
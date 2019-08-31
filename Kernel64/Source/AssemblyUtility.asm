[BITS 64]

global inPortByte, outPortByte, kLoadGDTR, kLoadTR, kLoadIDTR

SECTION .text

inPortByte:

    push RDX

    mov RDX, RDI
    mov RAX, 0
    in  AL, DX

    pop RDX
    ret

outPortByte:
    push RDX
    push RAX

    mov RDX, RDI
    mov RAX, RSI
    out DX,  AL 

    pop RAX
    pop RDX
    ret

kLoadGDTR:
    LGDT [RDI]

    ret

kLoadTR:
    LTR DI

    ret

kLoadIDTR:
    LIDT [RDI]

    ret
[BITS 64]

SECTION .text

global inPortByte, outPortByte

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

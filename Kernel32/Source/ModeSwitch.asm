[BITS 32]

global readCPUID, switchExcute64bitKernel

SECTION .text

readCPUID:

    PUSH ebp
    MOV ebp, esp
    PUSH eax
    PUSH ebx
    PUSH ecx
    PUSH edx
    PUSH esi

    MOV eax, DWORD [ ebp + 8 ]
    CPUID

    MOV esi, DWORD [ ebp + 12]
    MOV DWORD [ esi ], eax
    
    MOV esi, DWORD [ ebp + 16 ]
    MOV DWORD[ esi ], ebx

    MOV esi, DWORD [ ebp + 20 ]
    MOV DWORD [ esi ], ecx

    MOV esi, DWORD [ ebp + 24 ]
    MOV DWORD [ esi ], edx

    POP esi
    POP edx
    POP ecx
    POP ebx
    POP eax
    POP ebp

    RET

switchExcute64bitKernel:

    MOV eax, cr4
    OR eax, 0x20
    MOV cr4, eax

    MOV eax, 0x100000
    MOV cr3, eax

    MOV ecx, 0xC0000080
    RDMSR

    OR eax, 0x0100

    WRMSR

    MOV eax, cr0
    OR eax, 0xE0000000
    XOR eax, 0x60000000
    MOV cr0, eax

    JMP 0x08:0x200000

    JMP $
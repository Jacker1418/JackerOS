TOTALSECTORCOUNT: dw 1024

SECTORNUMBER: db 0x02
HEADNUMBER: db 0x00
TRACKNUMBER: db 0x00

	mov SI, 0x1000

	mov ES, si
	mov BX, 0x0000

	mov DI, word [TOTALSECTORCOUNT]

READDATA:

	cmp DI, 0
	je READEND
	sub DI, 0x1

	mov AH, 0x02
	mov AL, 0x01

	mov CH, byte [TRACKNUMBER]
	mov CL, byte [SECTORNUMBER]
	
	mov DH, byte [HEADNUMBER]
	mov DL, 0x00

	int 0x13
	jc HEADLEDDISKERROR

	mov SI, 0x0020
	mov ES, SI

	mov AL, byte [SECTORNUMBER]
	add AL, 0x01
	mov byte [SECTORNUMBER], AL
	
	cmp AL, 19
	jl READDATA

	xor byte [HEADNUMBER], 0x01
	mov byte [SECTORNUMBER], 0x01

	cmp byte [HEADNUMBER], 0x00
	jne READDATA
READEND:

HANDLEDISKERROR:

	jmp $


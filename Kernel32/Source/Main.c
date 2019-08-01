#include "Types.h"

void printString(int in_x, int in_y, const char* in_string);
BOOL Initialize_Kernel64_Area(void);
BOOL Is_Memory_Enough(void);

void Main(void){

	int numLine = 3;

	printString(0, numLine++, "First C Source Code in Kernel32 [PASS]");

	printString(0, numLine, "Minimum Memory size Check...................[    ]");
	if(Is_Memory_Enough()){
		printString(45, numLine, "Pass");
	}else{
		printString(45, numLine, "Fail");
		printString(0, ++numLine, "Not Enough Memory, JackerOS Requires Over 64M byte Memory");

		while(1);
	}
	numLine++;

	printString(0, numLine, "IA-32e Kernel Area Initialize...............[    ]" );
	if(Initialize_Kernel64_Area() ){
		printString(45, numLine, "Pass");
	}else{
		printString(45, numLine, "Fail");
		printString(0, numLine++, "Kernel Area Initialize Fail");

		while(1);
	}
}

void printString(int in_x, int in_y, const char* in_string){

	CHARACTER* pScreen = (CHARACTER *)(0xB8000);
	int i = 0;

	pScreen += (in_y * 80) + in_x;

	for(i = 0; in_string[i] != 0; i++){
		pScreen[i].bCharacter = in_string[i];
	}
}

BOOL Initialize_Kernel64_Area(void){
	DWORD* currentAddress;

	currentAddress = (DWORD *)0x100000;

	while( (DWORD) currentAddress < 0x600000){
		*currentAddress = 0x00;

		if( *currentAddress != 0x00){
			return FALSE;
		}

		currentAddress++;
	}

	return TRUE;
}

BOOL Is_Memory_Enough(void){
	DWORD *currentAddress;

	currentAddress = (DWORD *) 0x100000;

	while( (DWORD) currentAddress < 0x4000000){
		*currentAddress = 0x12345678;

		if(*currentAddress != 0x12345678){
			return FALSE;
		}

		currentAddress += (0x100000 / 4);
	}
	return TRUE;
}

#include "Types.h"
#include "Page.h"
#include "ModeSwitch.h"

void printString(int in_x, int in_y, const char* in_string);
BOOL Initialize_Kernel64_Area(void);
BOOL Is_Memory_Enough(void);

void copyKernel64_Image(void);

void Main(void){

	DWORD i;
	DWORD dwEAX, dwEBX, dwECX, dwEDX;

	char strVendorName[13] = {0,};

	int numLine = 3;

	printString(0, numLine++, "Protected Mode C Language Kernel Start......[PASS]");

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
	numLine++;

	printString(0, numLine, "IA-32e Page Table Initialize................[    ]");
	initializePageTable();
	printString(45, numLine, "PASS");

	numLine++;
	readCPUID( 0x00, &dwEAX, &dwEBX, &dwECX, &dwEDX);
	*(DWORD *) strVendorName = dwEBX;
	*( (DWORD *) strVendorName + 1 ) = dwEDX;
	*( (DWORD *) strVendorName + 2 ) = dwECX;

	printString(0, numLine, "Processor Vendor String.....................[             ]");
	printString(45, numLine++, strVendorName);

	readCPUID(0x80000001, &dwEAX, &dwEBX, &dwECX, &dwEDX);
	printString(0, numLine, "64bit Mode Support Check....................[    ]");
	if( dwEDX & (1 << 29)){
		printString(45, numLine++, "PASS");
	}else{
		printString(45, numLine, "Fail");
		printString(0, ++numLine, "This processor does not support 64bit mode~!");
		while(1);
	}

	printString(0, numLine, "Copy IA-32e Kernel To 2Mbyte Address........[    ]");
	copyKernel64_Image();
	printString(45, numLine++, "Pass");

	printString(0, numLine, "Switch To IA-32e Mode");
	switchExcute64bitKernel();

	while(1);

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

void copyKernel64_Image(void){

	WORD countKernel32_Sector, countTotalKernel_Sector;
	DWORD * pdwSourceAddress, * pdwDestinationAddress;
	
	int i;

	countTotalKernel_Sector = *( (WORD *) 0x7C05);
	countKernel32_Sector = *( (WORD *) 0x7C07);

	if(countTotalKernel_Sector == 7){
		printString(0, 12, "countTotalKernel_Sector = 7");
	}

	if(countKernel32_Sector == 6){
		printString(0, 13, "countKernel32_Sector = 6");
	}

	pdwSourceAddress = (DWORD *)( 0x10000 + (countKernel32_Sector * 512) );
	pdwDestinationAddress = (DWORD *) 0x200000;

	for(i = 0; i < 512 * (countTotalKernel_Sector - countKernel32_Sector) / 4; i++){
		*pdwDestinationAddress = *pdwSourceAddress;
		pdwDestinationAddress++;
		pdwSourceAddress++;
	}
}
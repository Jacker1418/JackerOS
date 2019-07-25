#include "Types.h"

void printString(int in_x, int in_y, const char* in_string);

void Main(void){

	printString(0, 3, "First C Source Code in Kernel32");

	while(1);

}

void printString(int in_x, int in_y, const char* in_string){

	CHARACTER* pScreen = (CHARACTER *)(0xB8000);
	int i = 0;

	pScreen += (in_y * 80) + in_x;

	for(i = 0; in_string[i] != 0; i++){
		pScreen[i].pCharactor = in_string[i];
	}
}

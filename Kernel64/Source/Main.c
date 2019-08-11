#include "Types.h"

void printString(int in_x, int in_y, const char* pString);

void Main(void){

    printString(0, 10, "Switch To IA-32e Mode Success~!!");
    printString(0, 11, "IA-32e C Language Kernel Start......................[PASS]");
}

void printString(int in_x, int in_y, const char* pString){

    CHARACTER *pScreen = (CHARACTER *)0xB8000;

    int i = 0;

    pScreen += (in_y * 80) + in_x;

    for(i = 0; i < pString[i] != 0; i++){
        pScreen[i].bCharacter = pString[i];
    }
}
#include "Types.h"
#include "Keyboard.h"

void printString(int in_x, int in_y, const char* pString);

void Main(void){

    char vcTemp[2] = {0,};

    BYTE bFlags;
    BYTE bTemp;

    int i = 0;

    int line = 10;

    printString(0, line++, "Switch To IA-32e Mode Success~!!");
    printString(0, line++, "IA-32e C Language Kernel Start..............[PASS]");
    printString(0, line, "Keyboard Activate...........................[      ]");

    if( activateKeyboard() == TRUE){
        printString(45, line++, "PASS");
        changeKeyboardLED(FALSE, FALSE, FALSE);
    }else{
        printString(45, line++, "FAIL");
        while(1);
    }

    while(1){

        if(isOutputBuffer_Full() == TRUE){
            bTemp = getKeyboard_ScanCode();

            if( ConvertScanCodeToASCIICode(bTemp, &(vcTemp[0]), &bFlags) == TRUE ){

                if(bFlags & KEY_FLAGS_DOWN){
                    
                    if(vcTemp[0] == KEY_ENTER){
                        vcTemp[0] = KEY_NONE;
                        i = 0;
                        if( i / 80 > 0){
                            line += (i / 80) + 2;
                        }else{
                            line++;
                        }
                    }else{
                        printString(i++, line, vcTemp);
                    }
                }
            }
        }
    }

}

void printString(int in_x, int in_y, const char* pString){

    CHARACTER *pScreen = (CHARACTER *)0xB8000;

    int i = 0;

    pScreen += (in_y * 80) + in_x;

    for(i = 0; i < pString[i] != 0; i++){
        pScreen[i].bCharacter = pString[i];
    }
}
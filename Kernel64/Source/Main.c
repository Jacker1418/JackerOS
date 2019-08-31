#include "Types.h"
#include "Keyboard.h"
#include "Descriptor.h"
#include "Utility.h"
#include "AssemblyUtility.h"

void Main(void){

    char vcTemp[2] = {0,};

    BYTE bFlags;
    BYTE bTemp;

    int i = 0;

    int line = 10;

    printString(0, line++, "Switch To IA-32e Mode Success~!!");
    printString(0, line++, "IA-32e C Language Kernel Start..............[PASS]");

    printString(0, line, "GDT Initialize and Switch For IA-32e Mode...       ]");
    initialize_GDT_Table_Tss();
    kLoadGDTR( GDTR_START_ADDRESS);
    printString(45, line++, "PASS");

    printString(0, line, "TSS Segment Load............................        ]");
    kLoadTR(GDT_TSS_SEGMENT);
    printString(45, line++, "PASS");

    printString(0, line, "IDT Initialize..............................        ]");
    initialize_IDT_Tables();
    kLoadIDTR(IDTR_START_ADDRESS);
    printString(45, line++, "PASS");

    printString(0, line, "Keyboard Activate...........................        ]");

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
                    }else if(vcTemp[0] == KEY_ESC){
                        bTemp = bTemp / 0;
                    }else{
                        printString(i++, line, vcTemp);
                    }
                }
            }
        }
    }

}
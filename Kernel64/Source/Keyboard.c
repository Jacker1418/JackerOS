#include "Types.h"
#include "AssemblyUtility.h"
#include "Keyboard.h"

BOOL isOutputBuffer_Full(void){

    if(inPortByte(0x64) & 0x01){
        return TRUE;
    }

    return FALSE;
}

BOOL isInputBuffer_Full(void){

    if( inPortByte(0x64) & 0x02){

        return TRUE;
    }

    return FALSE;
}

BOOL activateKeyboard(void){

    int i;
    int j;

    outPortByte(0x64, 0xAE);

    return TRUE;

    for( i = 0; i < 0xFFFF; i++){
        if(isInputBuffer_Full() == FALSE){
            break;
        }
    }

    outPortByte(0x60, 0xF4);

    for(j = 0; j < 100; j++){

        for(i = 0; i < 0xFFFF; i++){

            if( isOutputBuffer_Full() == TRUE){
                break;
            }
        }

        if(inPortByte(0x60) == 0xFA){
            return TRUE;
        }
    }
    
    return FALSE;
}

BYTE getKeyboard_ScanCode(void){

    while(isOutputBuffer_Full() == FALSE){
        ;
    }

    return inPortByte(0x60);
}

BOOL changeKeyboardLED(BOOL in_CapLockOn, BOOL in_NumLockOn, BOOL in_ScrollLockOn){

    int i, j;

    for(i = 0; i < 0xFFFF; i++){

        if(isInputBuffer_Full() == FALSE){
            break;
        }
    }

    outPortByte(0x60, 0xED);
    for( i = 0; i < 0xFFFF; i++){
        if(isInputBuffer_Full() == FALSE){
            break;
        }
    }
    
    for(j = 0; j < 100; j++){
        for(i = 0; i < 0xFFFF; i++){
            if(isOutputBuffer_Full() == TRUE){
                break;
            }
        }

        if(inPortByte(0x60) == 0xFA){
            break;
        }
    }

    if( j >= 100){
        return FALSE;
    }

    outPortByte(0x60, (in_CapLockOn << 2) | (in_NumLockOn << 1) | in_ScrollLockOn);
    for(i = 0; i < 0xFFFF; i++){
        if(isInputBuffer_Full() == FALSE){
            break;
        }
    }

    for(j = 0; j < 100; j++){
        for( i = 0; i < 0xFFFF; i++){
            if(isOutputBuffer_Full() == TRUE){
                break;
            }

            if(inPortByte(0x60) == 0xFA){
                break;
            }
        }

        if( j >= 100){
            return FALSE;
        }
        
        return TRUE;
    }
}

void enableA20Gate(void){

    BYTE outputPortData;
    int i;

    outPortByte(0x64, 0xD0);

    for(i = 0; i < 0xFFFF; i++){
        if(isOutputBuffer_Full() == TRUE){
            break;
        }
    }

    outputPortData = inPortByte(0x60);

    outputPortData != 0x02;

    for( i = 0; i < 0xFFFF; i++){
        if(isInputBuffer_Full() == FALSE){
            break;
        }
    }

    outPortByte(0x64, 0xD1);

    outPortByte(0x60, outputPortData);
}

void Reboot(void){

    int i;

    for( i = 0; i < 0xFFFF; i++){
        if(isInputBuffer_Full() == FALSE){
            break;
        }
    }

    outPortByte(0x64, 0xD1);

    outPortByte(0x60, 0x00);

    while(1){
        ;
    }
}

static KEYBOARDMANAGER gs_stKeyboardManager = {0, };

static KEYMAPPINGENTRY gs_vstKeyMappingTable[ KEY_MAPPINGTABLEMAXCOUNT ] = {
    { KEY_NONE      ,   KEY_NONE    },
    { KEY_ESC       ,   KEY_ESC     },
    { '1'           ,   '!'         },
    { '2'           ,   '@'         },
    { '3'           ,   '#'         },
    { '4'           ,   '$'         },
    { '5'           ,   '%'         },
    { '6'           ,   '^'         },
    { '7'           ,   '&'         },
    { '8'           ,   '*'         },
    { '9'           ,   '('         },
    { '0'           ,   ')'         },
    { '-'           ,   '-'         },
    { '='           ,   '+'         },
    { KEY_BACKSPACE , KEY_BACKSPACE },
    { KEY_TAB       , KEY_TAB       },
    { 'q'           , 'Q'           },
    { 'w'           , 'W'           },
    { 'e'           , 'E'           },
    { 'r'           , 'R'           },
    { 't'           , 'T'           },
    { 'y'           , 'Y'           },
    { 'u'           , 'U'           },
    { 'i'           , 'I'           },
    { 'o'           , 'O'           },
    { 'p'           , 'P'           },
    { '['           , '{'           },
    { ']'           , '}'           },
    { '\n'          , '\n'          },
    { KEY_CTRL      , KEY_CTRL      },
    { 'a'           , 'A'           },
    { 's'           , 'S'           },
    { 'd'           , 'D'           },
    { 'f'           , 'F'           },
    { 'g'           , 'G'           },
    { 'h'           , 'H'           },
    { 'j'           , 'J'           },
    { 'k'           , 'K'           },
    { 'l'           , 'L'           },
    { ';'           , ':'           },
    { '\''          , '\"'          },
    { '`'           , '~'           },
    { KEY_LSHIFT     , KEY_LSHIFT    },
    { '\\'          , '|'           },
    { 'z'           , 'Z'           },
    { 'x'           , 'X'           },
    { 'c'           , 'C'           },
    { 'v'           , 'V'           },
    { 'b'           , 'B'           },
    { 'n'           , 'N'           },
    { 'm'           , 'M'           },
    { ','           , '<'           },
    { '.'           , '>'           },
    { '/'           , '?'           },
    { KEY_RSHIFT    , KEY_RSHIFT    },
    { '*'           , '*'           },
    { KEY_LALT      , KEY_LALT      },
    { ' '           , ' '           },
    { KEY_CAPSLOCK  , KEY_CAPSLOCK  },
    { KEY_F1        , KEY_F1        },
    { KEY_F2        , KEY_F2        },
    { KEY_F3        , KEY_F3        },
    { KEY_F4        , KEY_F4        },
    { KEY_F5        , KEY_F5        },
    { KEY_F6        , KEY_F6        },
    { KEY_F7        , KEY_F7        },
    { KEY_F8        , KEY_F8        },
    { KEY_F9        , KEY_F9        },
    { KEY_F10       , KEY_F10       },
    { KEY_NUMLOCK   , KEY_NUMLOCK   },
    { KEY_SCROLLLOCK , KEY_SCROLLLOCK },

    { KEY_HOME      , '7'           },
    { KEY_UP        , '8'           },
    { KEY_PAGEUP    , '9'           },
    { '-'           , '-'           },
    { KEY_LEFT      , '4'           },
    { KEY_CENTER    , '5'           },
    { KEY_RIGHT     , '6'           },
    { '+'           , '+'           },

    { KEY_END       , '1'           },
    { KEY_DOWN      , '2'           },
    { KEY_PAGEDOWN  , '3'           },
    { KEY_INS       , '0'           },
    { KEY_DEL       , '.'           },
    { KEY_NONE      , KEY_NONE      },
    { KEY_NONE      , KEY_NONE      },
    { KEY_NONE      , KEY_NONE      },
    { KEY_F11       , KEY_F11       },
    { KEY_F12       , KEY_F12       }
};

BOOL isAlphabetScanCode (BYTE in_scanCode){

    if( ('a' <= gs_vstKeyMappingTable[ in_scanCode ].bNormalCode ) && (gs_vstKeyMappingTable[in_scanCode].bNormalCode <= 'z')){
        return TRUE;
    }

    return FALSE;
}

BOOL isNumberorSymbol_ScanCode(BYTE in_scanCode){
    
    if( (2 <= in_scanCode) && (in_scanCode <= 53) && (isAlphabetScanCode(in_scanCode) == FALSE)){
        return TRUE;
    }

    return FALSE;
}

BOOL isNumberPad_ScanCode(BYTE in_scanCode){
    if( (71 <= in_scanCode) && (in_scanCode <= 83) ){
        return TRUE;
    }

    return FALSE;
}

BOOL isUseCombinedCode(BYTE in_scanCode){

    BYTE downScanCode;
    BOOL useCombinedKey = FALSE;

    downScanCode = in_scanCode & 0x7F;

    if( isAlphabetScanCode(downScanCode) == TRUE){
        if(gs_stKeyboardManager.bShiftDown ^ gs_stKeyboardManager.bCapsLockOn){
            useCombinedKey = TRUE;
        }else{
            useCombinedKey = FALSE;
        }
    }else if( isNumberorSymbol_ScanCode(downScanCode) == TRUE){
        if(gs_stKeyboardManager.bShiftDown == TRUE){
            useCombinedKey = TRUE;
        }else{
            useCombinedKey = FALSE;
        }
    }else if( (isNumberorSymbol_ScanCode(downScanCode) == TRUE) && (gs_stKeyboardManager.bExtendedCodeIn == FALSE)){
        if(gs_stKeyboardManager.bNumLockOn == TRUE){
            useCombinedKey = TRUE;
        }else{
            useCombinedKey = FALSE;
        }
    }

    return useCombinedKey;
}

void UpdateCombinationKeyStatusAndLED( BYTE in_scanCode){
    
    BOOL bDown;
    BYTE bDownScanCode;
    BOOL bLEDStatusChanged = FALSE;

    if( in_scanCode & 0x80 ){
        bDown = FALSE;
        bDownScanCode = in_scanCode & 0x7F;
    }else{
        bDown = TRUE;
        bDownScanCode = in_scanCode;
    }

    if( (bDownScanCode == 42 ) || ( bDownScanCode == 54 ) ){
        gs_stKeyboardManager.bShiftDown = bDown;
    }else if( (bDownScanCode == 58 ) && (bDown == TRUE) ){
        gs_stKeyboardManager.bCapsLockOn ^= TRUE;
        bLEDStatusChanged = TRUE;
    }else if( (bDownScanCode == 69 ) && (bDown == TRUE) ){
        gs_stKeyboardManager.bNumLockOn ^= TRUE;
        bLEDStatusChanged = TRUE;
    }else if( (bDownScanCode == 70 ) && ( bDown == TRUE) ){
        gs_stKeyboardManager.bScrollLockOn ^= TRUE;
        bLEDStatusChanged = TRUE;
    }

    if(bLEDStatusChanged == TRUE){
        changeKeyboardLED( gs_stKeyboardManager.bCapsLockOn, gs_stKeyboardManager.bNumLockOn, gs_stKeyboardManager.bScrollLockOn);
    }
}

BOOL ConvertScanCodeToASCIICode( BYTE in_scanCode, BYTE* in_ASCIICode, BOOL* in_flags){

    BOOL bUseCombinedKey;

    if( gs_stKeyboardManager.SkipCountForPause > 0){
        gs_stKeyboardManager.SkipCountForPause--;
        return FALSE;
    }

    if(in_scanCode == 0xE1){
        *in_ASCIICode = KEY_PAUSE;
        *in_flags = KEY_FLAGS_DOWN;
        gs_stKeyboardManager.SkipCountForPause = KEY_SKIPCOUNTFORPAUSE;
        return TRUE;
    }else if ( in_scanCode == 0xE0){
        gs_stKeyboardManager.bExtendedCodeIn = TRUE;
        return FALSE;
    }

    bUseCombinedKey = isUseCombinedCode( in_scanCode );

    if(bUseCombinedKey == TRUE){
        *in_ASCIICode = gs_vstKeyMappingTable[ in_scanCode & 0x7F ].bCombinedCode;
    }else{
        *in_ASCIICode = gs_vstKeyMappingTable[ in_scanCode & 0x7F ].bNormalCode;
    }

    if( gs_stKeyboardManager.bExtendedCodeIn == TRUE){
        *in_flags = KEY_FLAGS_EXTENEDKEY;
        gs_stKeyboardManager.bExtendedCodeIn = FALSE;
    }else{
        *in_flags = 0;
    }

    if( (in_scanCode & 0x80 ) == 0){
        *in_flags |= KEY_FLAGS_DOWN;
    }

    UpdateCombinationKeyStatusAndLED(in_scanCode);
    return TRUE;
}
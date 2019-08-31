#include "Utility.h"

void setMemory( void* in_destination, BYTE in_data, int in_size){

    int i;

    for(i = 0; i < in_size; i++){
        ( (char *) in_destination)[i] = in_data;
    }

}
int copyMemory( void* in_destination, const void* in_source, int in_size){

    int i;

    for( i = 0; i < in_size; i++){
        ((char *)in_destination)[i] = ((char *)in_source)[i];
    }

    return i;

}
int cmpMemory( const void* in_destination, const void* in_source, int in_size){

    int i;
    char temp;

    for( i = 0; i < in_size; i++){

        temp = ((char *)in_destination)[i] - ((char *)in_source)[i];
        if(temp != 0){
            return (int)temp;
        }
    }

    return 0;
    
}

void printString(int in_x, int in_y, const char* pString){

    CHARACTER *pScreen = (CHARACTER *)0xB8000;

    int i = 0;

    pScreen += (in_y * 80) + in_x;

    for(i = 0; i < pString[i] != 0; i++){
        pScreen[i].bCharacter = pString[i];
    }
}
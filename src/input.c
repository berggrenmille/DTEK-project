
#include <stdint.h>
#include <pic32mx.h>

void init_input()
{
    TRISDSET  = 0xFE0; //Set bit index 5 - 11 to output
    TRISFSET  = 0x2;   
}

int get_btns(int btn)
{
    int result = ((PORTD >> 4) & 0xE) | ((PORTF >> 1) & 0x1); //The bits for the 4 buttons
    switch(btn)
    {
        case 1: return result & 0x1;
        case 2: return (result >> 1) & 0x1;
        case 3: return (result >> 2) & 0x1;
        case 4: return (result >> 3) & 0x1;
        default: return 0;
    }
}

int get_swts(int swt)
{
    int result = (PORTD >> 8) & 0xF; //The bits for the 4 switches
    switch(swt)
    {
        case 1: return result & 0x1;
        case 2: return (result >> 1) & 0x1;
        case 3: return (result >> 2) & 0x1;
        case 4: return (result >> 3) & 0x1;
        default: return 0;
    }
}

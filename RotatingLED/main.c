#include "msp.h"

enum Rot_States{Rot_Init,Rot_Blue,Rot_Green,Rot_Red}
Rot_State;

void Initialization(){
    P2 -> DIR = 0x07;
    P2 -> OUT = 0x00;
    SysTick -> CTRL = 00000007;
    SysTick -> LOAD = 1500000;
    Rot_State = Rot_Init;
}

void Rotate_LEDs(){
    switch(Rot_State){
    case(Rot_Init):
        P2 -> OUT = 0x00;
        Rot_State = Rot_Blue;
        break;
    case(Rot_Blue):
        P2 -> OUT ^= 0x04;
        Rot_State = Rot_Green;
        break;
    case(Rot_Green):
        P2 -> OUT ^= 0x02;
        Rot_State = Rot_Red;
        break;
    case(Rot_Red):
        P2 -> OUT ^= 0x01;
        break;
    default:
        P2 -> OUT = 0x00;
        Rot_State = Rot_Init;
    }
}

void main(void)
{
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;     // stop watchdog timer
    Initialization();
    Rotate_LEDs();
}

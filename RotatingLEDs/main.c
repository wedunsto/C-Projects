#include "msp.h"

enum Rot_States{Rot_Init,Rot_Blue,Rot_Green,Rot_Red}
Rot_State;//define the different states in the state machine

void Initialization(){//initialize output pins, SysTick settings, and initial state
    P2 -> DIR = 0x07;//enables P2.0, P2.2, P2.2 as outputs
    P2 -> OUT = 0x00;//initializes all outputs as low
    SysTick -> CTRL = 00000007;//enables SysTicks module
    SysTick -> LOAD = 6000000;//the system clock is set to 3 MHz. 6M ticks is equal to 2 seconds
    Rot_State = Rot_Init;//initializes the SM state
}

void Rotate_LEDs(){//rotates through the LEDs on P2
    switch(Rot_State){
    case(Rot_Init):
        P2 -> OUT = 0x00;
        Rot_State = Rot_Blue;
        break;
    case(Rot_Blue):
        P2 -> OUT = 0x04;
        Rot_State = Rot_Green;
        break;
    case(Rot_Green):
        P2 -> OUT = 0x02;
        Rot_State = Rot_Red;
        break;
    case(Rot_Red):
        P2 -> OUT = 0x01;
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
}

void SysTick_Handler(){//tells the SysTick which method to call every period
    Rotate_LEDs();
}

#include "msp.h"

unsigned char i;//counter variable used to keep track of varying periods

enum Rot_States{Rot_Init, Rot_Green, Rot_Blue, Rot_Red}
     Rot_State;//define states in state machine

     /*
      Green LED period : 2 seconds
      Blue LED period : 2 seconds
      Red LED period : 10 seconds
     */

void RotateLEDs(void){//rotate LEDs with varying periods
    switch(Rot_State){
        case(Rot_Init):
            P2 -> OUT = 0x00;
            i = 0;
            Rot_State = Rot_Green;
            break;
        case(Rot_Green):
            P2 -> OUT = 0x02;
            i++;
            Rot_State = Rot_Blue;
            break;
        case(Rot_Blue):
            P2 -> OUT = 0x04;
            i++;
            if(i>=4){//if current time is 8 seconds
                Rot_State = Rot_Red;//at the 10th second call red state
            }
            else{
                Rot_State = Rot_Green;
            }
            break;
        case(Rot_Red):
            P2 -> OUT = 0x01;
            i = 0;//reset counter
            Rot_State = Rot_Green;//go to green state
            break;
        default:
            P2 -> OUT = 0x00;
            Rot_State = Rot_Init;
            break;
     }
}

void Initialization(void){
    P2 -> DIR = 0x07;
    P2 -> OUT = 0x00;
    i=0;
    SysTick -> CTRL = 0x00000007;
    SysTick -> LOAD = 6000000;
    Rot_State = Rot_Init;
}

void main(void)
{
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer
	Initialization();
}

void SysTick_Handler(void){
    RotateLEDs();
}

#include "msp.h"
void toggleRedLED(){//When switch 1 is pressed toggle RED LED
    P1 -> DIR = 0x01 | ~(0x02);//sets P1.0 as an output and P1.1 as an input
    P1 -> REN = 0x02;//enables the pull up / pull down resistor on P1.1
    P1 -> OUT = 0x02;//configures pull up resistor and initializes output low

    while(1){//create an infinite while loop
        int i;
        for(i=0;i<500;i++){}//applies a delay to ensure proper functionality
            if((P1 -> IN & 0x02) == 0x00){//read the value on P1.1
                P1 -> OUT ^= 0x01;//changes the state of P1.0
            }
    }
}

void toggleGreenLED(){
    P1 -> DIR = ~(0x10);//sets P1.4 as an input
    P1 -> REN = 0x10;//enables the pull up / pull down resistor on P1.4
    P1 -> OUT = 0x10;//configures pull up resistor
    P2 -> DIR = 0x02;//sets P2.1 as an output
    P2 -> OUT = 0x00;//initializes output low

    while(1){//creates an infinite while loop
        int i;
        for(i=0;i<500;i++){}//applies a delay to ensure proper functionality
            if((P1 -> IN & 0x10) == 0x00){//read the value on P1.4
                P2 -> OUT ^= 0x02;//changes the state of P2.1
            }
    }
}

void toggleRedAndGreenLED(){
    P1 -> DIR = ~(0x02 | 0x10) | 0x01;//sets P1.1 and P1.4 as inputs and P1.0 as output
    P1 -> REN = 0x02 | 0x10;//enables the pull up / pull down resistors on P1.1 and P1.4
    P1 -> OUT = 0x02 | 0x10;//configures pull up resistor
    P2 -> DIR = 0x02;//sets P2.1 as an output
    P2 -> OUT = 0x00;//initializes output low

    while(1){//creates an infinite while loop
        int i;
        for(i=0;i<500;i++){}//applies a delay to ensure proper functionality
        if(((P1 -> IN & 0x02) == 0x00) && ((P1 -> IN & 0x10) != 0x00)){//read the value of P1.1
            P1 -> OUT ^= 0x01;//changes the state of P1.0
        }
        else if(((P1 -> IN & 0x10) == 0x00) && ((P1 -> IN & 0x02) != 0x00)){//read the value of P1.4
            P2 -> OUT ^= 0x02;//changes the state of P2.1
        }

    }
}

void blinkBlueLED(){
    P2 -> DIR |= 0x04;//sets P2.2 as output
    P1 -> OUT = ~0x04;//initializes output low
    SysTick -> CTRL = 0x00000007;//enable systick module
    SysTick -> LOAD = 1500000;//sets the period of the systick module
}

void SysTick_Handler(){//Called every tick of the systick period
    P2 -> OUT ^= 0x04;//toggle P1.0 RED LED
}

void main(){
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;// Stop WDT


    //toggleRedLED();
    //toggleGreenLED();
    //toggleRedAndGreenLED();
    //blinkBlueLED();
}

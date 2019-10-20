#include "msp.h"

typedef struct arrayTask{
    int state;
    unsigned long period;
    unsigned long elapseTime;
    int (*TickFct)(int);
} arrayTask;

static int arr[4];

arrayTask verify[2];

const unsigned char taskCount = 2;
const unsigned long taskPeriodGCD = 6000000;
volatile unsigned char index = 0;

enum add_States{add_Initial,add_Start,add_Stop} add_State;
enum stop_States{stop_Initial,stop_Stop}stop_State;

int Populate_Array(int state){
    switch(state){
    case add_Initial:
        P2 -> OUT = 0x02;
        state = add_Start;
        break;
    case add_Start:
        arr[index] = 0;
        index++;
        if(index == 2){
            P2 -> OUT = 0x04;
            state = add_Start;
        }
        else if(index>2){
            state = add_Stop;
        }
        break;
    case add_Stop:
        P2 -> OUT = 0x00;
        break;
    default:
        index = 0;
        state = add_Initial;
        break;
    }
    return state;
}

int DPopulate_Array(int state){
    switch(state){
    case stop_Initial:
        if(index == 3){
            state = stop_Stop;
        }
        else{
            state = stop_Initial;
        }
        break;
    case stop_Stop:
        P1 -> OUT = 0x01;
        break;
    }
    return state;
}

void populateArray(){
    unsigned i;
    for(i=0; i<taskCount;++i){
        if(verify[i].elapseTime >= verify[i].period){
            verify[i].state = verify[i].TickFct(verify[i].state);
            verify[i].elapseTime = 0;
        }
        verify[i].elapseTime += taskPeriodGCD;
    }
}



void main(void)
{
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer

	SysTick -> CTRL = 0x00000007;
	SysTick -> LOAD = taskPeriodGCD;
	P1 -> DIR = 0x01;
	P1 -> OUT = 0x00;
	P2 -> DIR = 0x06;
	P2 -> OUT = 0x00;

	unsigned char i = 0;
	verify[i].state = add_Initial;
	verify[i].period = taskPeriodGCD;
	verify[i].elapseTime = taskPeriodGCD;
	verify[i].TickFct = &Populate_Array;
	++i;
	verify[i].state = stop_Initial;
	verify[i].period = taskPeriodGCD;
	verify[i].elapseTime = taskPeriodGCD;
	verify[i].TickFct = &DPopulate_Array;
}

void SysTick_Handler(void){
    populateArray();
}

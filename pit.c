#include "pit.h"

void pitInitialize(void) {
	SIM->SCGC6 |= SIM_SCGC6_PIT_MASK; 
	PIT->MCR &= ~PIT_MCR_MDIS_MASK;
	PIT->MCR |= PIT_MCR_FRZ_MASK;
	
	PIT->CHANNEL[0].LDVAL = 0xc3500;  

	NVIC_ClearPendingIRQ(PIT_IRQn);  
	NVIC_EnableIRQ(PIT_IRQn);
	NVIC_SetPriority(PIT_IRQn, 2); 
	__enable_irq();
	
	//PIT->CHANNEL[0].TFLG &= PIT_TFLG_TIF_MASK;
	//PIT->CHANNEL[0].TCTRL &= ~PIT_TCTRL_CHN_MASK; 
	PIT->CHANNEL[0].TCTRL |= PIT_TCTRL_TIE_MASK;   
	
	PIT->CHANNEL[0].TCTRL |= PIT_TCTRL_TEN_MASK; 
	PIT->MCR = 0x00; 
}

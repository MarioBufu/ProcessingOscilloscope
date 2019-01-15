#include <lm4f120h5gr.h>

int main()
{
	volatile int adcResult = 0;
	SYSCTL->RCGCADC = 1 << 1;  //use ADC1
	SYSCTL->RCGCGPIO = (1 << 4); //enable gpio port e
	GPIOE->DIR &= ~(1 << 1); // E as input
	
	GPIOE->AFSEL = 1 << 1; // use PE1 as ADC input
	GPIOE->DEN &= ~(1 << 1);// disable digital function for PE1
	GPIOE->AMSEL = 1 << 1;// disable the analog isolation circuit
	
	ADC1->ACTSS &= ~(1 << 3); // disable the ADC sequencer
	ADC1->EMUX = 0XF << 12; // sample seq 3 continously sample
	ADC1->SSMUX3 = 2; // select PE1 as analog input
	ADC1->SSCTL3 = 0x2;// end of sequence
	ADC1->ACTSS |= 1<<3; // enable the ADC sequencer
	
	while(1)
	{
		// check if data is ready
		if((ADC1->RIS & (1 << 3))
		{
			// read data from ADC register
			adcResult = ADC1->SSFIFO3;
			// send data to pc
			
			// clear flag for next conversion
			ADC1->ISC |= 1 << 3;
		}
	}
	
	return 0;
}

//http://shukra.cedt.iisc.ernet.in/edwiki/EmSys:ADC_Programming_with_the_Tiva_TM4C123G
//https://www.engr.colostate.edu/ECE251/Labs/TM4C_datasheet_ADC.pdf
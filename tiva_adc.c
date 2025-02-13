#include <tm4c123.h>

int main()
{
	volatile int adcResult = 0;
	SYSCTL_RCGCADC_R |= 1 << 1;  //use ADC1
	ADC1_ACTSS_R &= ~(1 << 3); // disable the ADC sequencer
	SYSCTL_RCGCGPIO_R |= (1 << 4); //enable gpio port e
	GPIO_PORTE_DIR_R &= ~(1 << 1); // E as input
	GPIO_PORTE_AFSEL_R= 1 << 1; // use PE1 as ADC input
	GPIO_PORTE_DEN_R &= ~(1 << 1);// disable digital function for PE1
	GPIO_PORTE_AMSEL_R |= 1 << 1;// disable the analog isolation circuit
	ADC1_EMUX_R = 0x0 << 12; // start converion with D3 bit of ADCPSSI reg
	ADC1_SSMUX3_R |= 2; // select PE1 as analog input
	ADC1_SSCTL3_R |= 0x2;// end of sequence
	ADC1_ACTSS_R |= 1<<3; // enable the ADC sequencer
	
	SYSCTL_SRCR2_USB0 |= 1; // reset USB module
	SYSCTL_RCGCUSB_R |=1; // enable USB
	SYSCTL_RCGCGPIO_R |= 1 << 3; // enable clock to port D
	/*
	The next step is to enable the USB PLL so that the correct clocking is provided to the PHY. To ensure that voltage is not
supplied to the bus incorrectly, the external power control signal, USB0EPEN, should be negated on
start up by configuring the USB0EPEN and USB0PFLT pins to be controlled by the USB controller
and not exhibit their default GPIO behavior.
	GPIO_PCTL_PD2_USB0EPEN
	GPIO_PCTL_PD3_USB0PFLT
	*/
	
	/*endpoint config*/
	
	// start conversion
	ADC1_PSSI_R |= 1 << 3; 
	
	while(1)
	{
		// check if data is ready
		if((ADC1_RIS_R & (1 << 3))
		{
			// read data from ADC register
			adcResult = ADC1_SSFIFO3_R;
			// send data to pc
			
			// clear flag
			ADC1_ISC_R |= 1 << 3;
		}
		// check ADC status
		if(ADC1_ACTSS_R & (1 << 16) == 0) // check busy flag
		{
			// start next conversion
			ADC1_PSSI_R |= 1 << 3;
		}
	}
	
	return 0;
}

//http://shukra.cedt.iisc.ernet.in/edwiki/EmSys:ADC_Programming_with_the_Tiva_TM4C123G
//https://www.engr.colostate.edu/ECE251/Labs/TM4C_datasheet_ADC.pdf

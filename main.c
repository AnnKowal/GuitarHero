#include "frdm_bsp.h" 
#include "tsi.h"
//#include "spi.h"
#include "tpm.h"  
//#include "bitmaps.h"


void SysTick_Handler(void);
void press_and_play_right(uint8_t);

void wait(void);
static uint8_t msTicks = 0;
static uint8_t newTick = 0;
static uint8_t liczba1= 0;

static char znak='a';


int main (void)
{	
	
	uint8_t sliderTemp;
	TSI_init(); //inicjalizacja slidera

	//SysTick_Config(1000000); //inicjalizacja timera

	UART0_Init();
	UART0_read2();
	wait();
	wait();
	wait();
	wait();
	wait();
	wait();
		wait();
	wait();
	wait();
	wait();
	wait();
	wait();
		wait();
		
	TPM0_Init();	
	//TPM0_Play1();	

	SysTick_Config(SystemCoreClock/1000);
	//tpm1_init_pwm();
	/*
	spi_init();
	spi_write_data(title);
	wait();
	wait();
	wait();
	spi_write_data(authors);
	wait();
	wait();
	wait();
		spi_write_data(beginning);
	wait();
	wait();
	spi_write_data(snd1);
		wait();
	spi_write_data(snd2);
		wait();
	spi_write_data(snd3);
	*/			
	while(1)
	{
		
	
	__WFI();
	if (newTick==1){
		//if( msTicks%2 == 0 ) {
				sliderTemp = TSI_ReadSlider();
				if (sliderTemp > 0) {
					//UART0_read3();
					//	wait();
					//	wait();
					//	wait();
					//	wait();
					//	wait();				
					//	wait();
					//	wait();
					//	wait();
					//	wait();
					///	wait();
						//wait();
						//wait();
						//wait();
					liczba1=msTicks%4;
						while(!(UART0->S1 & UART0_S1_TDRE_MASK));
						UART0->D = liczba1;
						TPM0_Play1();
			}
				newTick=0;
		}
	
}
	}
		/*if( msTicks%2 == 1 ) {
				sliderTemp = TSI_ReadSlider();
			if (sliderTemp > 0) {
						UART0_read2();
						wait();
						wait();
						wait();
						wait();
						wait();				
						wait();
						wait();
						wait();
						wait();
						wait();
						wait();
						wait();
					TPM0_Play0();
			}
		}
		
	}
}
	}
*/
void SysTick_Handler(void) {
	msTicks++;
	newTick = 1;
}

void wait(void){
	for(volatile int k=0; k<=2600; k++){
		for(volatile int i=0; i<=600; i++){
		}
	}
}
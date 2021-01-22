#include "frdm_bsp.h" 
#include "tsi.h"
#include "spi.h"
#include "tpm.h"  
#include "bitmaps.h"


void SysTick_Handler(void);
void press_and_play_right(uint8_t);

void wait(void);
static uint8_t msTicks = 0;
static uint8_t newTick = 0;


static int nr=0; 

int main (void)
{	

	
	uint8_t sliderTemp;
 //inicjalizacja slidera
TSI_init();
	SysTick_Config(1000000); //inicjalizacja timera
	//SysTick_Config(SystemCoreClock/1000);

	
TPM0_Init();
UART0_Init();

//	const unsigned char *tablica[];
	
	spi_init();
	spi_write_data(table[nr++]);
	//nr++;
	wait();
	wait();
	wait();
	wait();
	spi_write_data(table[nr++]);
	wait();
	wait();
	wait();
	wait();
		spi_write_data(table[nr++]);
	wait();
	wait();
	//spi_write_data(snd1);

	spi_write_data(table[nr++]);
	wait();
	spi_write_data(table[nr++]);
	wait();
	spi_write_data(table[nr++]);
	wait();
	spi_write_data(table[nr++]);
	wait();
	spi_write_data(table[nr++]);
	wait();
	spi_write_data(table[nr++]);
	wait();
	spi_write_data(table[nr++]);
	wait();
	spi_write_data(table[nr++]);
	wait();
	spi_write_data(table[nr++]);
	wait();
	spi_write_data(table[nr++]);
	wait();
	spi_write_data(table[nr++]);
	


//TPM0_Play6(1);
	while(1)
	{
//wait();
	//spi_write_data(snd2);
		//wait();
	//spi_write_data(snd3);
	spi_write_data(table[nr++]);
	wait();
	//spi_write_data(o13pelne);
	//wait();
	//__WFI();
	
	//	__WFI();
	if (newTick==1){
		newTick=0;
		if( msTicks%2 == 0 ) {
							spi_write_data(table[nr++]);

				UART0_read2();
//wait();
				sliderTemp = TSI_ReadSlider();
				
				if (sliderTemp > 0) {
					
						
						TPM0_Play6(1);
	//				wait();
					//	UART0_read2();
						//TPM0_Play6(1);
			}
				else{
			spi_write_data(table[nr++]);
			wait();
			//wait();

		}
		}
	}
		
}
}
void SysTick_Handler(void) {
	msTicks++;
	newTick = 1;
}

void wait(void){
	for(volatile int k=0; k<=2600; k++){
		for(volatile int i=0; i<=500; i++){
		}
	}
}

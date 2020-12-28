#include "frdm_bsp.h" 
#include "tsi.h"
#include "tpm_pcm.h"  

void SysTick_Handler(void);
void wait(void);

static uint8_t slider = 0;
static uint8_t msTicks = 0;
static uint8_t newTick = 0;

int main (void) { 
	

	TSI_Init(); //inicjalizacja slidera
	SysTick_Config(1000000); //inicjalizacja timera
	
	TPM0_Init(); //inicjalizacja przerwania
	
	while(1){
		__WFI();	//czekanie na przerwanie
		if (newTick==1){ //jezeli bylo przerwanie
			if( msTicks%2 == 0 ) {
			slider=TSI_ReadSlider(); //odczytanie wartosci ze slidera
			if(slider>0){
				TPM0_Play(); //wlaczenie piosenki
				newTick=0; //wyzerowanie zmiennej informujacej o przerwaniu
				//wait(); //wywolanie funkcji realizujacej opoznienie
				//TPM0_Pause(); //pauzowanie piosenki
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
	for(volatile int k=0; k<=3600; k++){
		for(volatile int i=0; i<=600; i++){
		}
	}
}

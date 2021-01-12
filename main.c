#include "spi.h"
#include "tpm.h"
#include "frdm_bsp.h" 
#include "tsi.h"
#include "bitmaps.h"


void wait(void);
void SysTick_Handler(void);
void press_and_play_right(uint8_t, uint8_t);
void press_and_play_left(uint8_t, uint8_t);
void press_and_play_middle(uint8_t, uint8_t);
void hold_and_play_right(uint8_t);


static uint8_t slider = 0;
static uint8_t msTicks = 0;
static uint8_t newTick = 0;
static uint8_t liczba_p=0;
static uint8_t liczba_s=1;

int main (void)
{
	TSI_Init(); //inicjalizacja slidera
	SysTick_Config(SystemCoreClock/1000);
	tpm1_init_pwm();
	TPM0_Init(); //inicjalizacja przerwania
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
	while(1)
	{
		__WFI();	//czekanie na przerwanie
		
				if (newTick==1){ //jezeli bylo przerwanie
					slider=TSI_ReadSlider();
					liczba_p=liczba_s%6;
					press_and_play_right(slider, liczba_p);
					liczba_s=liczba_s+1;
		}
		
	}
}
void press_and_play_right(uint8_t slider1, uint8_t liczba1){
	if (slider1>66){
		if (liczba1==0){
			TPM0_Play2();
		}
		else if (liczba1==1){
			TPM0_Play3();
		}
		
		else if (liczba1==2){
			TPM0_Play4();
		}
		else if (liczba1==3){
			TPM0_Play5();
		}
		else if(liczba1==4){
			TPM0_Play6();
		}

	}

		
}
	
void press_and_play_middle(uint8_t slider1, uint8_t liczba1){
	if (slider1>=33 && slider1<=66){
		if (liczba1==0){
			TPM0_Play2();
		}
		else if (liczba1==1){
			TPM0_Play3();
		}
		
		else if (liczba1==2){
			TPM0_Play4();
		}
		else if (liczba1==3){
			TPM0_Play5();
		}
		else if(liczba1==4){
			TPM0_Play6();
		}
	
	}
	}


void press_and_play_left(uint8_t slider1, uint8_t liczba1){
	if (slider1>0 && slider1<33){
		if (liczba1==0){
			TPM0_Play2();
		}
		else if (liczba1==1){
			TPM0_Play3();
		}
		else if (liczba1==2){
			TPM0_Play4();
		}
		else if(liczba1==3){
			TPM0_Play5();
		}
		else if(liczba1==4){
			TPM0_Play6();
		}

	
	}
}

void hold_and_play_right(uint8_t slider1){
	uint8_t zmienna=0;
	uint8_t slider2=0;
	if (slider1>66){
		zmienna=1;
		
		if (zmienna==1){
			slider2=TSI_ReadSlider();
			if (slider2<=0){
			zmienna=0;
			TPM0_Play2();
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
		for(volatile int i=0; i<=600; i++){
		}
	}
}

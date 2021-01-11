#include "frdm_bsp.h" 
#include "tsi.h"
#include "spi.h"
#include "tpm.h"  

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


const unsigned char logo_mini_mono [] = {
0xFC, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0x7F, 0x7F, 0x7F, 0xFF, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F,
0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x7F, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFE, 0xFC, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0x7F, 0x3F, 0x0F, 0x03, 0x00, 0x00, 0x00, 0x80, 0xE0, 0x01, 0x01, 0x02, 0x00, 0x04, 0x08, 0xF8,
0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF8, 0xF8, 0xF8, 0xF8, 0xF8, 0xF8,
0xF8, 0xF9, 0xFB, 0x7F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0x7F, 0x1F, 0x07, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0E, 0x03, 0x00, 0x00, 0x00, 0x00,
0x00, 0xE0, 0x0C, 0x03, 0x03, 0x03, 0x03, 0x03, 0x07, 0x07, 0x07, 0x07, 0x03, 0x03, 0x03, 0x03,
0x03, 0x81, 0x81, 0x81, 0xC1, 0xC0, 0xC0, 0xFC, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x3E, 0xFF, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFC, 0xFC, 0xFE, 0xFE, 0xFE,
0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0x3F, 0x7F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0xFC, 0xFC,
0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFE, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F, 0x3F,
};

int main (void) { 
	

	TSI_init(); //inicjalizacja slidera
	SysTick_Config(1000000); //inicjalizacja timera
	TPM0_Init(); 
	
	tpm1_init_pwm();
	spi_init();
	spi_write_data(logo_mini_mono);
	
	while(1){
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



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









///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "frdm_bsp.h" 
#include "tsi.h"
#include "spi.h"
#include "tpm.h"  
#include "uart.h" 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void SysTick_Handler(void);
void press_and_play_right(uint8_t);

void TPM0_IRQHandler(void);
void TPM0_Play(void);
void UART0_read(void);
static uint8_t slider = 0;
static uint8_t msTicks = 0;
static uint8_t newTick = 0;
static uint8_t liczba_p=0;
static uint8_t liczba_s=1;
char rx_buf[]={0x01,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09};


static uint32_t upSampleCNT = 0;
static uint32_t probka = 0;
static uint32_t dlugosc = 5000;
static uint32_t probka_do_odt = 0;
static uint32_t upsampling = 20;
static uint8_t  play = 1;
uint8_t  piosenka_FULL = 1;
uint8_t temp=0;
uint8_t temp2=0;
static uint8_t piosenka2[];
static uint8_t piosenka3[];



void TPM0_IRQHandler(void){
	if (play==1) {
		if (upSampleCNT == 0){
			probka_do_odt=probka++;
			TPM0->CONTROLS[2].CnV = piosenka3[probka_do_odt]; 
		}	
		if (probka > dlugosc ) {
			play = 0;         
			TPM0->CONTROLS[2].CnV = 0;
	
		}
	
		if (++upSampleCNT > (upsampling-1)) 
		{
			upSampleCNT = 0;
		}
		}
	TPM0->CONTROLS[0].CnSC |= TPM_CnSC_CHF_MASK; 
	}

void TPM0_Play(void) {   

	play=1;
	probka=0;
}
void UART0_read(){
	if(UART0->S1 & UART0_S1_RDRF_MASK)
	{

		temp=UART0->D;	
		if(!piosenka_FULL)
		{
			piosenka2[0] = temp;	
			piosenka_FULL=1;
		}
	}
}

int main (void)
{	
	TSI_init(); //inicjalizacja slidera
	//SysTick_Config(SystemCoreClock/1000);
	SysTick_Config(1000000); //inicjalizacja timera
	TPM0_Init(); //inicjalizacja przerwania
	UART0_Init();

					
	while(1)
	{
		
	
	__WFI();
	if (newTick==1){
		for(uint16_t k=0; k<5000; k++){	
						UART0_read();
						if(piosenka_FULL)		
						{
						piosenka3[k]=piosenka2[0];
						}
						piosenka_FULL=0;
		}
		
		for (uint16_t t=0; t<5000; t++){
		while(!(UART0->S1 & UART0_S1_TDRE_MASK));
					UART0->D = piosenka3[t];
		}
	
		if( msTicks%2 == 0 ) {
			slider=TSI_ReadSlider();
			press_and_play_right(slider);
					}
			}
		}
	}	
	
	
	
	void press_and_play_right(uint8_t slider1){
	if (slider1>66){
	
			TPM0_Play();
		}
	}
void SysTick_Handler(void) {
	msTicks++;
	newTick = 1;
}



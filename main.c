#include "frdm_bsp.h" 
#include "tsi.h"
#include "spi.h"
#include "tpm.h"  
#include "bitmaps.h"


void SysTick_Handler(void);
void wait(void);

static uint8_t msTicks = 0;
static uint8_t newTick = 0;
static uint8_t points=0;
static int nr=0; 
static int tsi_nr=0;
static int iter=0;

int main (void)
{	
	uint8_t sliderTemp;

	TSI_init(); //inicjalizacja slidera
	SysTick_Config(1000000); //ustawienie timera
	

	tpm1_init_pwm(); //inicjalizacja przerwania od wyswietlacza
	TPM0_Init(); //inicjalizacja przerwania od glosnika
	UART0_Init(); //inicjalizacja portu UART

	spi_init(); //inicjalizacja protokolu SPI

	//wyswietlenie poczatkowych bitmap
	spi_write_data(title); 
	wait();
	wait();
	wait();
	wait();
	
	spi_write_data(authors);
	wait();
	wait();
	
	spi_write_data(beginning);
	wait();
	wait();
	wait();
	wait();
	
	
	spi_write_data(o1);
	wait();
	wait();
	wait();
	
	spi_write_data(o2);
	wait();
	wait();
	wait();
	
	spi_write_data(o3);
	wait();
	wait();
	wait();
	
	spi_write_data(o4);
	wait();
	wait();
	wait();
	
	spi_write_data(o5);
	wait();
	wait();
	wait();
	
	spi_write_data(o6);
	wait();
	wait();
	wait();
	
	spi_write_data(o7);
	wait();
	wait();
	wait();
	
	spi_write_data(o8);
	wait();
	wait();
	wait();
	
	spi_write_data(o9);
	wait();
	wait();
	wait();
	
	spi_write_data(o10);
	wait();
	wait();
	wait();
	
	spi_write_data(o12);
	wait();
	wait();
	wait();
	
	while(1)
	{
	if (newTick==1){ //jezeli bylo przerwanie
		newTick=0;
		if( msTicks%2 == 0 ) { //jezeli liczba przerwan jest podzielna bez reszty przez 2
			spi_write_data(table[nr++]); //przeslanie do wyswietlacza kolejnej bitmapy 
			UART0_read2(); //odczyt probek dzwieku z komputera poprzez UART
			sliderTemp = TSI_ReadSlider(); //sprawdzenie stanu slidera dotykowego
				
			if ((slider_tab[tsi_nr][1]>= sliderTemp) && (sliderTemp> slider_tab[tsi_nr][0])) //jezeli dotknieto w odpowiednim, zgodnym ze schematem na wyswietlaczu miejscu
			{
				TPM0_Play6(1); //odtworzenie fragmentu piosenki
				points=points+1; //naliczenie punktu
			}
			else{ //jezeli nie wcisieto wcale lub wcisnieto w zlym miejscu, dzwiek nie jest odtwarzany i punkt nie nalicza sie
				wait();
				wait();
			}
			
			tsi_nr++;
				
		}
	}
	if (nr==6 && iter==0){ //jezeli minal pierwszy obieg po tablicy z bitmapami, bitmapy zaczynaja wwyswietlac sie od poczatku tablicy
		nr=0;
		iter=iter+1;
		tsi_nr=0;
	}
		
	
	if (nr==6 && iter==1){ //jezeli minal drugi obieg po tablicy z bitmapami, bitmapy zaczynaja wwyswietlac sie od poczatku tablicy
		nr=6;
		iter=iter+1;
		tsi_nr=0;
	}
	
	
	
	if (nr==14 && iter==2){ //jezeli gra sie skonczyla
		spi_write_data(pp); //wyswietlenie bitmapy "points"
		wait();
		wait();
		wait();
		wait();
		wait();
		wait();
		wait();
		//w zaleznosci od ilosci zdobytych punktow, wyswietlenie bitmapy, informujacej o ich liczbie
		if (points==0){
		spi_write_data(p0);
		}
		else if (points==1){
		spi_write_data(p10);
		}
		else if (points==2){
		spi_write_data(p20);
		}
		else if (points==2){
		spi_write_data(p20);
		}
		else if (points==2){
		spi_write_data(p20);
		}
		else if (points==3){
		spi_write_data(p30);
		}
		else if (points==4){
		spi_write_data(p40);
		}
		else if (points==5){
		spi_write_data(p50);
		}
		else if (points==6){
		spi_write_data(p60);
		}
		else if (points==7){
		spi_write_data(p70);
		}
		else if (points==8){
		spi_write_data(p80);
		}
		else if (points==9){
		spi_write_data(p90);
		}
		else if (points==10){
		spi_write_data(p100);
		}
		else if (points==11){
		spi_write_data(p110);
		}
		else if (points==12){
		spi_write_data(p120);
		}
		else if (points==13){
		spi_write_data(p130);
		}
		else if (points==14){
		spi_write_data(p140);
		}
		else if (points==15){
		spi_write_data(p150);
		}
		else if (points==16){
		spi_write_data(p160);
		}
		else if (points==17){
		spi_write_data(p170);
		}
		else if (points==18){
		spi_write_data(p180);
		}
		else if (points==19){
		spi_write_data(p190);
		}
		else if (points==20){
		spi_write_data(p200);
		}
		
		wait();
		wait();
		wait();
		wait();
		spi_write_data(ending); //wyswietlenie koncowej bitmapy
		wait();
		wait();
		wait();
		wait();
		wait();
		wait();
		wait();
		wait();
	
	}
	
}
}

void SysTick_Handler(void) {
	msTicks++;
	newTick = 1;
}

void wait(void){ //funkcja realizujaca opoznienie
	for(volatile int k=0; k<=2600; k++){
		for(volatile int i=0; i<=500; i++){
		}
	}
}

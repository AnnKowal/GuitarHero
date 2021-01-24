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
static uint8_t points=0;

static int nr=0; 
static int tsi_nr=0;
static int iter=0;

int main (void)
{	

	
uint8_t sliderTemp;

	TSI_init();
	SysTick_Config(1000000); 
	

	
	TPM0_Init();
	UART0_Init();

	spi_init();

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
	spi_write_data(o2);
	spi_write_data(o3);
	spi_write_data(o4);
	spi_write_data(o5);
	spi_write_data(o6);
	spi_write_data(o7);
	spi_write_data(o8);
	spi_write_data(o9);
	spi_write_data(o10);
	spi_write_data(o11);
	spi_write_data(o12);
	


//TPM0_Play6(1);
	while(1)
	{
//wait();
	//spi_write_data(snd2);
		//wait();
	//spi_write_data(snd3);
	//spi_write_data(table[nr++]);
	//wait();
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
				
			if ((slider_tab[tsi_nr][1]>= sliderTemp) && (sliderTemp> slider_tab[tsi_nr][0])){
					
						TPM0_Play6(1);
						points=points+1;
	//				wait();
					//	UART0_read2();
						//TPM0_Play6(1);
			}
				else{
			spi_write_data(table[nr++]);
			wait();
			//wait();

		}
				tsi_nr++;
				
		}
	}
	if (nr==8 && iter<2){
		nr=0;
		iter=iter+1;
		tsi_nr=0;
	}
		
	if (nr==8 && iter==2){
		
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
		else if (points==21){
		spi_write_data(p210);
		}
		else if (points==22){
		spi_write_data(p220);
		}/*
		else if (points==23){
		spi_write_data(p230);
		}
		else if (points==24){
		spi_write_data(p240);
		}
		*/
		wait();
		wait();
		wait();
		wait();
		wait();
		wait();
		spi_write_data(ending);
		wait();
		wait();
		wait();
		wait();
		wait();
		wait();
	}
	
}
	/*if (points==0){
		spi_write_data(p0);
		wait();
	}
	else if (points==1){
		spi_write_data(p1);
	}
*/

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
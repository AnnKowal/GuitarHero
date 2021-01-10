#include "tsi.h"
static uint16_t scan_value [2];
static uint8_t end_flag = TRUE;
static uint8_t current_electrode = 0;
static uint16_t tsi_count [2];
static uint16_t delta[2];
void TSI_init(void)
{
	unsigned char scan_trigger_mode;
	SIM->SCGC5 |= SIM_SCGC5_TSI_MASK;  // enable clock for tsi
  SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK | SIM_SCGC5_PORTB_MASK; // enable clock for port A and port B
	PORTA->PCR[13] = PORT_PCR_MUX(0); // set PTA13 as TSI channel 9  
  PORTB->PCR[12] = PORT_PCR_MUX(0); // set PTB12 as TSI channel 8 
	TSI0->GENCS |= (TSI_GENCS_ESOR_MASK // End-of-scan interrupt allowed
                | TSI_GENCS_MODE(0) // Capacitive sensing mode
                | TSI_GENCS_REFCHRG(4) // Reference Oscillator charge and discharge current value = 8uA
                | TSI_GENCS_DVOLT(0) // DV = 1.03V, Vp = 1.33V, Vm = 0.30V
                | TSI_GENCS_EXTCHRG(7)  // Electrode Oscillator charge and discharge current value = 64uA
                | TSI_GENCS_PS(4) // Electrode Oscillator Frequency divided by 16
                | TSI_GENCS_NSCN(11) // Scan Number: 12 times per electrode
                | TSI_GENCS_TSIIEN_MASK  // TSI interrupt enabled
                | TSI_GENCS_STPE_MASK // Allow TSI to run in all low power modes
								| TSI_GENCS_TSIEN_MASK); // TSI module enabled
	NVIC_ClearPendingIRQ(TSI0_IRQn); // clear pending interrupts for TSI0
	NVIC_EnableIRQ(TSI0_IRQn); // enable interrupts for TSI0
	TSI0->GENCS |= TSI_GENCS_EOSF_MASK; // Scan completed - clear End of Scan Flag
	TSI0->GENCS &= ~TSI_GENCS_TSIEN_MASK; // TSI module disabled 
	if(TSI0->GENCS & TSI_GENCS_STM_MASK) scan_trigger_mode = 1; // if hardware trigger scan mode, set scan_trigger_mode as 1
  else scan_trigger_mode = 0; // if software trigger scan mode, set scan_trigger_mode as 0
	TSI0->GENCS &= ~TSI_GENCS_STM_MASK; // use software trigger scan mode
  TSI0->GENCS &= ~TSI_GENCS_TSIIEN_MASK; // TSI interrupt disabled
  TSI0->GENCS |= TSI_GENCS_TSIEN_MASK; // TSI module enabled
	for(volatile int i=9; i > 7; i--){ //check each electrode (channel 9 and 8) 
    TSI0->DATA = (uint32_t)((i<<TSI_DATA_TSICH_SHIFT)); // specify current channel to be measured
    TSI0->DATA |= TSI_DATA_SWTS_MASK; // start a scan
    while(!(TSI0->GENCS & TSI_GENCS_EOSF_MASK)); // wait until scan is completed
    TSI0->GENCS |= TSI_GENCS_EOSF_MASK;// Scan complete - clear End of Scan Flag
    scan_value[9-i] = (TSI0->DATA & TSI_DATA_TSICNT_MASK); //record the accumulated scan counter value ticked by the reference oscillator for selected electrode
  }
	TSI0->GENCS &= ~TSI_GENCS_TSIEN_MASK; // TSI module disabled
  TSI0->GENCS |= TSI_GENCS_TSIIEN_MASK; // TSI interrupt enabled
  if(scan_trigger_mode) TSI0->GENCS |= TSI_GENCS_STM_MASK; // if scan_trigger_mode = 1, set hardware trigger scan mode again 
  else TSI0->GENCS &= ~TSI_GENCS_STM_MASK; // if scan_trigger_mode = 0, set software trigger scan mode again
  TSI0->GENCS |= TSI_GENCS_TSIEN_MASK; // TSI module enabled
  TSI0->DATA = (uint32_t)((9<<TSI_DATA_TSICH_SHIFT)); // specify current channel to be measured
  TSI0->DATA |= TSI_DATA_SWTS_MASK; // start a scan
}

void TSI0_IRQHandler(void) {

  end_flag = TRUE; // End of Scan - set end_flag true
  TSI0->GENCS |= TSI_GENCS_EOSF_MASK; // Scan completed - clear End of Scan Flag
  
	int16_t temp_delta;
  tsi_count[current_electrode] = (TSI0->DATA & TSI_DATA_TSICNT_MASK); //record the accumulated scan counter value ticked by the reference oscillator for selected electrode
  temp_delta =  (int16_t)(tsi_count[current_electrode] - scan_value[current_electrode]); // count the difference between count value from init and current count value
  if( temp_delta < 0) delta[current_electrode] = 0; // until the current count value < count value from init, set delta for current electrode as 0
  else delta[current_electrode] = (uint16_t)temp_delta; // in another case, set delta for current electrode as temp_delta
	if(1 > current_electrode) current_electrode++; // if selected electrode 0, change to electrode 1
	else current_electrode = 0; // if selected electrode 1, change to electrode 0
	TSI0->DATA = (uint32_t)(((9-current_electrode)<<TSI_DATA_TSICH_SHIFT)); // specify current channel to be measured
	TSI0->DATA |= TSI_DATA_SWTS_MASK; // start a scan

}

uint8_t TSI_ReadSlider (void) {
  int a = 0;
  int b = 0;
	if(end_flag){ // if an interruption has occured
		end_flag = FALSE; // set end_flag false, waiting for next interrupt 
		if((delta[0]>100)||(delta[1]>100)){ // if the difference between count value from init and current count value of any electrode is more than 100
		  a = (delta[0]*100)/(delta[0]+delta[1]); // set coefficient a according to given formula 
		  b = (delta[1]*100)/(delta[0]+delta[1]); // set coefficient b according to given formula
		  return (uint8_t)((100 - a + b)/2); // count the slider's value 
		}else{
		 return 0; // if the difference is less or equal to 100 for both electrodes, do nothing
		}
	}else{
	  return 0;// if interruption has not occured, do nothing
	}
}

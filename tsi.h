#ifndef TSI_H
#define TSI_H

#include "frdm_bsp.h"
void TSI_init(void);
void TSI0_IRQHandler(void);
uint8_t TSI_ReadSlider (void);

#endif

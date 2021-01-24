#ifndef SPI_H
#define SPI_H

#include "frdm_bsp.h"

#define D_C 6
#define RST 10
#define SCE 11
void delayMs (int n);
void spi_init(void);
void spi_write_data(const unsigned char bitmap[]);
void spi_write (uint8_t address);

#endif
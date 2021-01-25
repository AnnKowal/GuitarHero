 #include "tpm.h"

void TPM0_IRQHandler(void);

static unsigned char temp=0;
static uint8_t temp2=0;
static uint32_t temp3=0;
static uint8_t temp4=0;
uint8_t  piosenka_FULL = 1;
static uint32_t dlugosc = 12000;
static uint8_t enable = 0;
static uint32_t upSampleCNT = 0;
static uint32_t probka = 0;
static const uint32_t upsampling =11;
static uint8_t  play=0;
static uint8_t  pause = 0;

//poczatkowe probki piosenki, ktore sa odtwarzane zanim nastapi odczyt z UARTA
static volatile uint8_t piosenka5[3000]={
0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
	0x7F, 0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80, 0x80,
	0x80, 0x7F, 0x7F, 0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80, 0x80, 0x80, 0x7F,
	0x7F, 0x80, 0x80, 0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80, 0x7F, 0x7F, 0x80,
	0x80, 0x7F, 0x7F, 0x80, 0x80, 0x7F, 0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80,
	0x7F, 0x80, 0x80, 0x7F, 0x80, 0x80, 0x7F, 0x80, 0x80, 0x80, 0x7F, 0x7F,
	0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80, 0x7F, 0x7F,
	0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80, 0x7F, 0x80, 0x80, 0x7F, 0x7F, 0x80,
	0x80, 0x7F, 0x7F, 0x80, 0x80, 0x7F, 0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80,
	0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x7F, 0x80, 0x80, 0x80, 0x7F, 0x80,
	0x80, 0x80, 0x7F, 0x80, 0x80, 0x7F, 0x7F, 0x80, 0x7F, 0x7F, 0x80, 0x80,
	0x7F, 0x7F, 0x80, 0x80, 0x7F, 0x80, 0x80, 0x7F, 0x80, 0x80, 0x80, 0x7F,
	0x7F, 0x80, 0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80,
	0x7F, 0x7F, 0x80, 0x80, 0x7F, 0x7F, 0x7F, 0x80, 0x80, 0x7F, 0x7F, 0x80,
	0x80, 0x7F, 0x7F, 0x80, 0x7F, 0x7F, 0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80,
	0x7F, 0x80, 0x80, 0x7F, 0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80, 0x7F, 0x80,
	0x80, 0x80, 0x7F, 0x80, 0x80, 0x80, 0x7F, 0x80, 0x80, 0x7F, 0x80, 0x80,
	0x7F, 0x7F, 0x80, 0x80, 0x7F, 0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80, 0x7F,
	0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80, 0x7F, 0x80,
	0x80, 0x7F, 0x7F, 0x80, 0x80, 0x80, 0x7F, 0x80, 0x80, 0x80, 0x7F, 0x80,
	0x80, 0x7F, 0x80, 0x80, 0x7F, 0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80, 0x7F,
	0x7F, 0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80, 0x80, 0x80, 0x7F, 0x80, 0x80,
	0x7F, 0x7F, 0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80, 0x80, 0x7F, 0x7F, 0x80,
	0x80, 0x80, 0x7F, 0x80, 0x80, 0x80, 0x7F, 0x80, 0x80, 0x7F, 0x7F, 0x80,
	0x80, 0x7F, 0x7F, 0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80, 0x7F, 0x7F, 0x80,
	0x80, 0x7F, 0x7F, 0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80, 0x7F, 0x7F, 0x80,
	0x80, 0x7F, 0x7F, 0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80, 0x7F, 0x80, 0x7F,
	0x7F, 0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80, 0x7F, 0x80, 0x80, 0x80, 0x7F,
	0x7F, 0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80, 0x7F, 0x80, 0x80, 0x80, 0x7F,
	0x7F, 0x80, 0x80, 0x7F, 0x80, 0x80, 0x7F, 0x80, 0x80, 0x7F, 0x7F, 0x80,
	0x80, 0x7F, 0x7F, 0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80, 0x7F, 0x7F, 0x80,
	0x80, 0x7F, 0x7F, 0x80, 0x80, 0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80, 0x7F,
	0x7F, 0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80, 0x7F,
	0x7F, 0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80,
	0x7F, 0x80, 0x80, 0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80, 0x80, 0x7F, 0x7F,
	0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80, 0x7F, 0x80,
	0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80, 0x7F,
	0x7F, 0x80, 0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80,
	0x80, 0x7F, 0x7F, 0x80, 0x80, 0x7F, 0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80,
	0x80, 0x7F, 0x7F, 0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80, 0x80, 0x80, 0x7F,
	0x7F, 0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80,
	0x7F, 0x7F, 0x80, 0x80, 0x7F, 0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80, 0x7F,
	0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80, 0x7F, 0x80, 0x80, 0x7F, 0x7F, 0x80,
	0x80, 0x7F, 0x7F, 0x80, 0x80, 0x7F, 0x80, 0x80, 0x80, 0x7F, 0x80, 0x80,
	0x80, 0x7F, 0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80,
	0x7F, 0x7F, 0x80, 0x80, 0x7F, 0x7F, 0x80, 0x7F, 0x7F, 0x80, 0x80, 0x80,
	0x80, 0x7F, 0x7F, 0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80, 0x80, 0x80, 0x7F,
	0x7F, 0x80, 0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80, 0x7F, 0x80, 0x80, 0x7F,
	0x7F, 0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80, 0x7F, 0x80, 0x80, 0x7F, 0x7F,
	0x80, 0x80, 0x7F, 0x7F, 0x80, 0x7F, 0x7F, 0x80, 0x80, 0x7F, 0x7F, 0x80,
	0x80, 0x7F, 0x80, 0x80, 0x7F, 0x80, 0x80, 0x80, 0x80, 0x80, 0x7F, 0x80,
	0x80, 0x80, 0x7F, 0x7F, 0x7F, 0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80, 0x80,
	0x7F, 0x7F, 0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80, 0x80, 0x80, 0x7F, 0x80,
	0x80, 0x7F, 0x7F, 0x80, 0x7F, 0x7F, 0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80,
	0x7F, 0x80, 0x80, 0x7F, 0x80, 0x80, 0x80, 0x80, 0x7F, 0x80, 0x80, 0x7F,
	0x7F, 0x80, 0x80, 0x7F, 0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80, 0x7F, 0x7F,
	0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80, 0x80, 0x7F,
	0x7F, 0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80, 0x80,
	0x7F, 0x7F, 0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80, 0x80, 0x7F, 0x7F, 0x80,
	0x80, 0x7F, 0x7F, 0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80, 0x7F, 0x7F, 0x80,
	0x80, 0x7F, 0x7F, 0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80, 0x80, 0x7F, 0x7F,
	0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80, 0x80, 0x7F,
	0x7F, 0x7F, 0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80, 0x7F, 0x7F, 0x80, 0x7F,
	0x7F, 0x80, 0x80, 0x7F, 0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80, 0x7F, 0x80,
	0x80, 0x7F, 0x7F, 0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80, 0x7F, 0x7F, 0x80,
	0x80, 0x7F, 0x7F, 0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80, 0x7F, 0x7F, 0x80,
	0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80, 0x7F, 0x80,
	0x80, 0x80, 0x7F, 0x80, 0x80, 0x7F, 0x7F, 0x80, 0x7F, 0x80, 0x80, 0x80,
	0x7F, 0x80, 0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80,
	0x7F, 0x80, 0x80, 0x80, 0x80, 0x80, 0x7F, 0x80, 0x80, 0x7F, 0x7F, 0x80,
	0x80, 0x7F, 0x7F, 0x80, 0x80, 0x7F, 0x80, 0x80, 0x7F, 0x80, 0x80, 0x80,
	0x80, 0x80, 0x80, 0x80, 0x80, 0x7F, 0x80, 0x80, 0x80, 0x7F, 0x7F, 0x80,
	0x80, 0x7F, 0x7F, 0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80, 0x7F, 0x7F, 0x80,
	0x80, 0x7F, 0x7F, 0x80, 0x7F, 0x80, 0x80, 0x80, 0x7F, 0x80, 0x80, 0x7F,
	0x7F, 0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80, 0x80, 0x80, 0x7F, 0x7F, 0x80,
	0x80, 0x7F, 0x7F, 0x80, 0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80, 0x80, 0x7F,
	0x7F, 0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80, 0x7F,
	0x80, 0x80, 0x80, 0x7F, 0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80, 0x7F, 0x7F,
	0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80, 0x7F, 0x7F,
	0x80, 0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80, 0x7F,
	0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x7F, 0x80,
	0x80, 0x80, 0x7F, 0x80, 0x80, 0x80, 0x7F, 0x80, 0x80, 0x7F, 0x7F, 0x80,
	0x80, 0x7F, 0x7F, 0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80, 0x7F, 0x7F, 0x80,
	0x80, 0x80, 0x7F, 0x80, 0x80, 0x7F, 0x7F, 0x80, 0x7F, 0x7F, 0x80, 0x80,
	0x7F, 0x7F, 0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80, 0x7F, 0x80, 0x80, 0x7F,
	0x7F, 0x80, 0x80, 0x80, 0x7F, 0x80, 0x80, 0x80, 0x7F, 0x7F, 0x7F, 0x80,
	0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80, 0x7F,
	0x80, 0x80, 0x7F, 0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80, 0x7F, 0x80, 0x80,
	0x7F, 0x7F, 0x80, 0x80, 0x7F, 0x80, 0x7F, 0x7F, 0x80, 0x80, 0x7F, 0x7F,
	0x7F, 0x80, 0x80, 0x80, 0x7F, 0x80, 0x80, 0x80, 0x80, 0x7F, 0x7F, 0x80,
	0x80, 0x7F, 0x80, 0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80, 0x7F, 0x7F, 0x80,
	0x80, 0x7F, 0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80, 0x80, 0x80, 0x7F, 0x7F,
	0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80, 0x7F,
	0x7F, 0x80, 0x80, 0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80, 0x80, 0x7F, 0x7F,
	0x80, 0x80, 0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80,
	0x7F, 0x7F, 0x80, 0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80, 0x7F, 0x7F, 0x80,
	0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80, 0x80,
	0x7F, 0x7F, 0x80, 0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80, 0x80, 0x7F, 0x7F,
	0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80, 0x80, 0x7F,
	0x7F, 0x80, 0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80,
	0x80, 0x7F, 0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80,
	0x7F, 0x7F, 0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80,
	0x7F, 0x7F, 0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80, 0x7F, 0x80, 0x80, 0x80,
	0x7F, 0x7F, 0x80, 0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80, 0x7F, 0x80, 0x80,
	0x7F, 0x80, 0x80, 0x7F, 0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80, 0x7F, 0x80,
	0x80, 0x7F, 0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80, 0x80, 0x7F, 0x7F, 0x80,
	0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80, 0x80, 0x7F, 0x80, 0x80, 0x7F, 0x80,
	0x80, 0x7F, 0x7F, 0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80, 0x80, 0x7F, 0x7F,
	0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x7F, 0x80, 0x80, 0x80,
	0x7F, 0x7F, 0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80, 0x80, 0x7F, 0x7F, 0x80,
	0x80, 0x7F, 0x7F, 0x80, 0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80, 0x7F, 0x80,
	0x80, 0x7F, 0x7F, 0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80, 0x7F, 0x7F, 0x80,
	0x80, 0x7F, 0x7F, 0x80, 0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80, 0x80, 0x7F,
	0x7F, 0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80, 0x7F, 0x80, 0x80, 0x7F, 0x7F,
	0x80, 0x80, 0x7F, 0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80, 0x7F, 0x7F, 0x80,
	0x80, 0x80, 0x7F, 0x80, 0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80, 0x7F, 0x7F,
	0x80, 0x80, 0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80, 0x80, 0x7F, 0x7F, 0x80,
	0x80, 0x7F, 0x7F, 0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80, 0x7F, 0x7F, 0x80,
	0x80, 0x80, 0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80,
	0x7F, 0x7F, 0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80, 0x7F, 0x80, 0x80, 0x80,
	0x7F, 0x7F, 0x80, 0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80, 0x7F, 0x7F, 0x80,
	0x80, 0x7F, 0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80,
	0x80, 0x7F, 0x7F, 0x80, 0x80, 0x80, 0x7F, 0x80, 0x80, 0x80, 0x80, 0x80,
	0x80, 0x80, 0x80, 0x80, 0x7F, 0x80, 0x80, 0x80, 0x7F, 0x80, 0x80, 0x80,
	0x7F, 0x80, 0x80, 0x7F, 0x80, 0x80, 0x80, 0x80, 0x80, 0x7F, 0x80, 0x80,
	0x80, 0x7F, 0x7F, 0x80, 0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80, 0x7F, 0x80,
	0x80, 0x7F, 0x7F, 0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80, 0x7F, 0x80, 0x80,
	0x7F, 0x7F, 0x80, 0x80, 0x7F, 0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80, 0x80,
	0x80, 0x7F, 0x7F, 0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80, 0x7F, 0x80, 0x80,
	0x7F, 0x80, 0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80,
	0x7F, 0x7F, 0x80, 0x80, 0x80, 0x7F, 0x7F, 0x7F, 0x80, 0x80, 0x7F, 0x7F,
	0x80, 0x7F, 0x7F, 0x80, 0x80, 0x7F, 0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80,
	0x7F, 0x7F, 0x80, 0x80, 0x80, 0x80, 0x7F, 0x80, 0x80, 0x7F, 0x7F, 0x80,
	0x80, 0x7F, 0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80, 0x80, 0x7F, 0x80, 0x80,
	0x80, 0x7F, 0x7F, 0x80, 0x80, 0x80, 0x80, 0x7F, 0x80, 0x80, 0x80, 0x7F,
	0x7F, 0x7F, 0x80, 0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80, 0x7F, 0x7F, 0x80,
	0x80, 0x7F, 0x80, 0x80, 0x7F, 0x80, 0x80, 0x80, 0x7F, 0x80, 0x80, 0x80,
	0x80, 0x7F, 0x7F, 0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80, 0x7F, 0x7F, 0x80,
	0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80, 0x7F, 0x80,
	0x80, 0x7F, 0x7F, 0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80, 0x80, 0x80, 0x7F,
	0x7F, 0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80, 0x7F,
	0x7F, 0x80, 0x80, 0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80, 0x7F, 0x7F, 0x80,
	0x80, 0x7F, 0x80, 0x80, 0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80, 0x7F, 0x80,
	0x80, 0x7F, 0x7F, 0x80, 0x80, 0x7F, 0x80, 0x80, 0x80, 0x7F, 0x80, 0x80,
	0x80, 0x80, 0x80, 0x80, 0x80, 0x7F, 0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80,
	0x7F, 0x80, 0x80, 0x7F, 0x7F, 0x80, 0x7F, 0x7F, 0x80, 0x80, 0x7F, 0x7F,
	0x80, 0x80, 0x80, 0x7F, 0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80, 0x7F, 0x80,
	0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x7F, 0x80, 0x80, 0x7F, 0x7F, 0x80,
	0x80, 0x80, 0x7F, 0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80, 0x7F, 0x7F, 0x80,
	0x80, 0x7F, 0x80, 0x80, 0x80, 0x7F, 0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80,
	0x7F, 0x7F, 0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80,
	0x7F, 0x7F, 0x80, 0x80, 0x7F, 0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80, 0x7F,
	0x7F, 0x80, 0x80, 0x80, 0x80, 0x7F, 0x80, 0x80, 0x80, 0x80, 0x80, 0x7F,
	0x7F, 0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80, 0x7F, 0x80, 0x80, 0x7F, 0x7F,
	0x7F, 0x80, 0x80, 0x80, 0x7F, 0x80, 0x80, 0x80, 0x7F, 0x80, 0x80, 0x7F,
	0x7F, 0x80, 0x80, 0x80, 0x7F, 0x80, 0x80, 0x80, 0x7F, 0x80, 0x80, 0x7F,
	0x80, 0x80, 0x7F, 0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80, 0x7F, 0x7F, 0x80,
	0x80, 0x7F, 0x7F, 0x80, 0x80, 0x80, 0x7F, 0x7F, 0x7F, 0x80, 0x80, 0x7F,
	0x7F, 0x80, 0x80, 0x80, 0x7F, 0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80, 0x80,
	0x7F, 0x7F, 0x80, 0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80, 0x7F, 0x7F, 0x80,
	0x80, 0x7F, 0x7F, 0x80, 0x80, 0x7F, 0x7F, 0x7F, 0x80, 0x80, 0x80, 0x7F,
	0x7F, 0x80, 0x80, 0x7F, 0x80, 0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80, 0x7F,
	0x7F, 0x80, 0x80, 0x7F, 0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80, 0x7F, 0x80,
	0x80, 0x7F, 0x7F, 0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80, 0x7F, 0x7F, 0x80,
	0x80, 0x7F, 0x7F, 0x80, 0x80, 0x7F, 0x80, 0x7F, 0x7F, 0x80, 0x80, 0x7F,
	0x7F, 0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80, 0x7F,
	0x7F, 0x80, 0x7F, 0x7F, 0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80, 0x7F, 0x7F,
	0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80, 0x7F,
	0x7F, 0x80, 0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80, 0x80, 0x7F, 0x7F, 0x80,
	0x80, 0x7F, 0x7F, 0x80, 0x80, 0x80, 0x7F, 0x80, 0x80, 0x80, 0x80, 0x80,
	0x7F, 0x80, 0x80, 0x80, 0x7F, 0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80, 0x7F,
	0x7F, 0x80, 0x80, 0x7F, 0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80, 0x7F, 0x80,
	0x80, 0x80, 0x7F, 0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80, 0x7F, 0x80, 0x80,
	0x7F, 0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80, 0x80,
	0x80, 0x7F, 0x7F, 0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80, 0x7F, 0x7F, 0x80,
	0x80, 0x7F, 0x7F, 0x80, 0x80, 0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80, 0x80,
	0x7F, 0x7F, 0x80, 0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80, 0x7F, 0x7F, 0x80,
	0x80, 0x7F, 0x7F, 0x80, 0x80, 0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80, 0x7F,
	0x80, 0x80, 0x7F, 0x80, 0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80, 0x7F, 0x7F,
	0x80, 0x80, 0x80, 0x80, 0x7F, 0x80, 0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80,
	0x7F, 0x7F, 0x7F, 0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80, 0x7F, 0x80, 0x80,
	0x7F, 0x7F, 0x80, 0x80, 0x7F, 0x7F, 0x80, 0x7F, 0x7F, 0x80, 0x80, 0x7F,
	0x7F, 0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80,
	0x7F, 0x7F, 0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80, 0x80, 0x7F, 0x7F, 0x80,
	0x80, 0x7F, 0x7F, 0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80, 0x7F, 0x7F, 0x80,
	0x80, 0x80, 0x7F, 0x80, 0x80, 0x7F, 0x7F, 0x80, 0x7F, 0x80, 0x80, 0x7F,
	0x7F, 0x80, 0x80, 0x7F, 0x80, 0x80, 0x80, 0x80, 0x80, 0x7F, 0x7F, 0x80,
	0x80, 0x7F, 0x7F, 0x80, 0x80, 0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80, 0x7F,
	0x7F, 0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80, 0x80,
	0x80, 0x7F, 0x7F, 0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80, 0x80, 0x7F, 0x7F,
	0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80, 0x80,
	0x7F, 0x7F, 0x80, 0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80, 0x7F, 0x80, 0x80,
	0x7F, 0x7F, 0x80, 0x80, 0x80, 0x7F, 0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80,
	0x7F, 0x80, 0x80, 0x80, 0x80, 0x80, 0x7F, 0x80, 0x80, 0x80, 0x80, 0x7F,
	0x80, 0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80, 0x7F,
	0x7F, 0x80, 0x80, 0x7F, 0x80, 0x80, 0x7F, 0x80, 0x80, 0x7F, 0x7F, 0x80,
	0x80, 0x7F, 0x80, 0x80, 0x7F, 0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80, 0x7F,
	0x7F, 0x80, 0x80, 0x7F, 0x80, 0x7F, 0x80, 0x80, 0x80, 0x7F, 0x80, 0x80,
	0x7F, 0x7F, 0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80,
	0x80, 0x80, 0x80, 0x80, 0x80, 0x7F, 0x80, 0x80, 0x7F, 0x80, 0x80, 0x7F,
	0x7F, 0x80, 0x7F, 0x7F, 0x80, 0x80, 0x7F, 0x80, 0x80, 0x80, 0x7F, 0x80,
	0x80, 0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80, 0x7F,
	0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80, 0x7F, 0x7F, 0x7F, 0x80, 0x80, 0x7F,
	0x7F, 0x80, 0x80, 0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80, 0x7F, 0x7F, 0x80,
	0x80, 0x7F, 0x7F, 0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80, 0x7F, 0x80, 0x80,
	0x80, 0x7F, 0x80, 0x80, 0x80, 0x80, 0x7F, 0x80, 0x80, 0x80, 0x7F, 0x80,
	0x80, 0x80, 0x80, 0x80, 0x7F, 0x80, 0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80,
	0x80, 0x80, 0x7F, 0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80, 0x7F, 0x80, 0x80,
	0x80, 0x7F, 0x7F, 0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80, 0x7F, 0x7F, 0x80,
	0x80, 0x7F, 0x80, 0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80, 0x7F, 0x7F, 0x80,
	0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80, 0x80, 0x7F, 0x7F, 0x80, 0x80, 0x7F,
	0x7F, 0x80, 0x7F, 0x80, 0x80, 0x80, 0x7F, 0x80, 0x80, 0x7F, 0x80, 0x7F,
	0x80, 0x7F, 0x80, 0x7F, 0x80, 0x7F, 0x80, 0x7F, 0x80, 0x7F, 0x80, 0x7F,
	0x80, 0x7F, 0x80, 0x7F, 0x80, 0x7F, 0x80, 0x7F, 0x80, 0x7F, 0x80, 0x7F,
	0x80, 0x7F, 0x80, 0x7F, 0x80, 0x7F, 0x80, 0x7F, 0x80, 0x7F, 0x80, 0x7F,
	0x80, 0x7F, 0x80, 0x7F, 0x80, 0x7F, 0x80, 0x7F, 0x80, 0x7F, 0x80, 0x7F,
	0x80, 0x7F, 0x80, 0x7F, 0x80, 0x7F, 0x80, 0x7F, 0x80, 0x7F, 0x80, 0x7F,
	0x80, 0x7F, 0x80, 0x7F, 0x80, 0x7F, 0x80, 0x7F, 0x80, 0x7F, 0x80, 0x7F,
	0x80, 0x7F, 0x80, 0x7F, 0x80, 0x7F, 0x80, 0x7F, 0x80, 0x7F, 0x80, 0x7F,
	0x80, 0x7F, 0x80, 0x7F, 0x80, 0x7F, 0x80, 0x7F, 0x80, 0x7F, 0x80, 0x7F,
	0x80, 0x7F, 0x80, 0x7F, 0x80, 0x7F, 0x80, 0x7F, 0x80, 0x7F, 0x80, 0x7F,
	0x80, 0x7F, 0x80, 0x7F, 0x80, 0x7F, 0x80, 0x7F, 0x80, 0x7F, 0x80, 0x7F,
	0x80, 0x7F, 0x80, 0x7F, 0x80, 0x7F, 0x80, 0x7F, 0x80, 0x7F, 0x80, 0x7F,
	0x80, 0x7F, 0x80, 0x7F, 0x80, 0x7F, 0x80, 0x7F, 0x80, 0x7F, 0x80, 0x7F,
	0x80, 0x7F, 0x80, 0x7F, 0x80, 0x7F, 0x80, 0x7F, 0x80, 0x7F, 0x80, 0x7F,
	0x80, 0x7F, 0x80, 0x7F, 0x80, 0x7F, 0x80, 0x7F, 0x80, 0x7F, 0x80, 0x7F,
	0x80, 0x7F, 0x80, 0x80, 0x80, 0x7F, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
	0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
	0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
	0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
	0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
	0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
	0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
	0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
	0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
	0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
	0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
	0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
	0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
	0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
	0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
	0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
	0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
	0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
	0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
	0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
	0x80, 0x80, 0x80, 0x80, 0x80, 0x7F, 0x80, 0x7F, 0x80, 0x7F, 0x80, 0x7F,
	0x80, 0x7F, 0x80, 0x7F, 0x80, 0x7F, 0x80, 0x7F, 0x80, 0x7F, 0x80, 0x7F,
	0x80, 0x7F, 0x80, 0x7F, 0x80, 0x7F, 0x80, 0x7F, 0x80, 0x80, 0x80, 0x7F,
	0x80, 0x7F, 0x80, 0x7F, 0x80, 0x7F, 0x80, 0x7F, 0x80, 0x7F, 0x80, 0x7F};


static uint8_t znak=5;
void UART0_read2(void);
void UART0_Init(void);
uint8_t UART0_read(void);


void tpm1_init_pwm(void)
{

	SIM->SCGC6 |= SIM_SCGC6_TPM1_MASK;
	SIM->SOPT2 |= SIM_SOPT2_TPMSRC(1);
	SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK;
	PORTA->PCR[12] = PORT_PCR_MUX(2);
	TPM1->SC |= TPM_SC_PS(7);
	TPM1->SC |= TPM_SC_CMOD(1);
	TPM1->MOD = 100;
	TPM1->SC &= ~TPM_SC_CPWMS_MASK; 
	TPM1->CONTROLS[0].CnSC |= (TPM_CnSC_MSB_MASK | TPM_CnSC_ELSA_MASK);
	TPM1->CONTROLS[0].CnV = 20;


}


void TPM0_Init(void) {
			
  	SIM->SCGC6 |= SIM_SCGC6_TPM0_MASK;	//wlaczenie maski 
	SIM->SOPT2 |= SIM_SOPT2_TPMSRC(1);	//wybor zrodla zegara

	SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK; 	//podlaczenie zegara do portu B
	PORTB->PCR[7] = PORT_PCR_MUX(2);	//wybor multipleksera	
	
	TPM0->SC |= TPM_SC_PS(2);  	//ustawienie prescalera 				  
	TPM0->SC |= TPM_SC_CMOD(1);	//wybor zegara				  

	TPM0->MOD = 255; //wybor wartosci modulo										  
	

	TPM0->SC &= ~TPM_SC_CPWMS_MASK; //zliczanie w gore		
	TPM0->CONTROLS[2].CnSC |= (TPM_CnSC_MSB_MASK | TPM_CnSC_ELSB_MASK); 
	TPM0->CONTROLS[2].CnV = 0; 
	
	

	TPM0->SC &= ~TPM_SC_CPWMS_MASK;
	TPM0->CONTROLS[0].CnSC |= (TPM_CnSC_MSA_MASK | TPM_CnSC_ELSA_MASK);
	TPM0->CONTROLS[0].CnV = 0;
  
	TPM0->CONTROLS[0].CnSC |= TPM_CnSC_CHIE_MASK; //zezwolenie na przerwanie
	
	NVIC_SetPriority(TPM0_IRQn, 1);  //priorytet przerwania

	NVIC_ClearPendingIRQ(TPM0_IRQn); 
	NVIC_EnableIRQ(TPM0_IRQn);	//zezwolenie na przerwanie
	
	enable= 1; 
}
void UART0_Init(void)
{
	SIM->SCGC4 |= SIM_SCGC4_UART0_MASK;	//dolaczenie sygnalu taktujacego do modulu UART						
	SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK;	//dolaczenie sygnalu taktujacego do portu B						
	SIM->SOPT2 |= SIM_SOPT2_UART0SRC(MCGFLLCLK);	//ustawienie zrodla zegara taktujaego	
	PORTB->PCR[1] = PORT_PCR_MUX(2); 	//ustawienie nadajnika								
	PORTB->PCR[2] = PORT_PCR_MUX(2);	//ustawienie odbiornika								
	
	UART0->C2 &= ~(UART0_C2_TE_MASK | UART0_C2_RE_MASK );	//blokada nadajnika i odbiornika	
	
	//ustawienie wartosci zrodla zegara dla nadajnika i odbiornika:  41943040/(16*921600)=3
	UART0->BDH = 0;		// starsze bity 
	UART0->BDL =3;		// mlodsze bity
	UART0->C4 &= ~UART0_C4_OSR_MASK;			
	UART0->C4 |= UART0_C4_OSR(15);		//ustawienie dzielnika probkowania nadmiarowego	
	UART0->C5 |= UART0_C5_BOTHEDGE_MASK;	//probkowanie danych na obydwu zboczach zegara
	UART0->C2 |= UART0_C2_RIE_MASK;		//wlaczenie przerwania od odbiornika	
	UART0->C2 |= (UART0_C2_TE_MASK | UART0_C2_RE_MASK);	//wlaczenie nadajnika i odbiornika	
}

void UART0_read2(){
	while(!(UART0->S1 & UART0_S1_TDRE_MASK)); 
	UART0->D = znak; //wyslanie przez UART zmiennej swiadczacej o checi przyjecia probek dzwieku
	
	for (uint32_t k=0; k<dlugosc; k++){	
		while(!(UART0->S1 & UART0_S1_RDRF_MASK)){}
		temp2=UART0->D;
			
		if (k%4==3)
		{
			if (temp2=='a' || temp2=='b' || temp2=='c' || temp2=='d' || temp2 == 'e' || temp2=='f')
			{temp4=temp4*16+(temp2-87);}
			else{temp4=temp4*16+(temp2-0x30);
			
			}
				while(!(UART0->S1 & UART0_S1_TDRE_MASK));			UART0->D = temp4;
				piosenka5[temp3]=temp4;
				temp3++;	
		else if(k%4==2)
		{
			if (temp2=='a' || temp2=='b' || temp2=='c' || temp2=='d' || temp2 == 'e' || temp2=='f')
			{temp4=temp4+(temp2-87);}
			else
			{temp4=temp4+(temp2-0x30);}
		}
		else
		{
			temp4=0;
		}
			piosenka_FULL=0;
	}
	play=0;
	temp3=0;
	temp4=0;
}




void TPM0_Play6(unsigned char z) {   
	probka=0;
	play=1;
}

void TPM0_IRQHandler(void) {
			
	if (play!=0) {
		if (upSampleCNT == 0){
			TPM0->CONTROLS[2].CnV = piosenka5[probka++];
		}
		if (probka >=2999 ) {
			play = 0;         
			probka=0;
		}
		if (++upSampleCNT > (upsampling-1)) 
		{
			upSampleCNT = 0;
						}
	}
		
	TPM0->CONTROLS[0].CnSC |= TPM_CnSC_CHF_MASK; 
}

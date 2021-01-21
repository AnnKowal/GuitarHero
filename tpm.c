 #include "tpm.h"

static unsigned char temp=0;
static uint8_t temp2=0;
static uint32_t temp3=0;
static uint8_t temp4=0;
uint8_t  piosenka_FULL = 1;
static uint32_t dlugosc = 12000;
void TPM0_IRQHandler(void);
static uint8_t enable = 0;
static uint32_t upSampleCNT = 0;
static uint32_t probka = 0;
static uint32_t probka_do_odt = 0;
static const uint32_t upsampling =11;
static uint8_t  play=0;
static uint8_t  pause = 0;
static volatile uint8_t piosenka5[3000]={
0x81 ,
0x80 ,
0x82 ,
0x81 ,
0x82 ,
0x82 ,
0x80 ,
0x80 ,
0x80 ,
0x80 ,
0x80 ,
0x7f ,
0x7e ,
0x7f ,
0x7e ,
0x7e ,
0x7d ,
0x7d ,
0x7e ,
0x7e ,
0x7e ,
0x7e ,
0x7e ,
0x7f ,
0x80 ,
0x80 ,
0x81 ,
0x80 ,
0x81 ,
0x81 ,
0x81 ,
0x81 ,
0x82 ,
0x81 ,
0x81 ,
0x80 ,
0x80 ,
0x7f ,
0x80 ,
0x7f ,
0x7f ,
0x7f ,
0x7f ,
0x7f ,
0x7e ,
0x7d ,
0x7e ,
0x7e ,
0x7e ,
0x7f ,
0x7e ,
0x7f ,
0x7f ,
0x7f ,
0x80 ,
0x80 ,
0x80 ,
0x80 ,
0x81 ,
0x81 ,
0x80 ,
0x80 ,
0x81 ,
0x80 ,
0x81 ,
0x81 ,
0x80 ,
0x80 ,
0x7f ,
0x7f ,
0x7f ,
0x7f ,
0x7f ,
0x7f ,
0x7f ,
0x7f ,
0x7f ,
0x7f ,
0x7e ,
0x7f ,
0x7f ,
0x7f ,
0x7f ,
0x7f ,
0x7f ,
0x7f ,
0x7f ,
0x80 ,
0x80 ,
0x80 ,
0x80 ,
0x80 ,
0x80 ,
0x80 ,
0x81 ,
0x81 ,
0x81 ,
0x80 ,
0x81 ,
0x80 ,
0x80 ,
0x80 ,
0x80 ,
0x80 ,
0x7f ,
0x7f ,
0x7f ,
0x7f ,
0x7e ,
0x7e ,
0x7e ,
0x7e ,
0x7e ,
0x7e ,
0x7e ,
0x7f ,
0x7f ,
0x7f ,
0x80 ,
0x80 ,
0x80 ,
0x81 ,
0x81 ,
0x81 ,
0x81 ,
0x81 ,
0x81 ,
0x81 ,
0x81 ,
0x81 ,
0x80 ,
0x80 ,
0x80 ,
0x7f ,
0x7f ,
0x7f ,
0x7e ,
0x7e ,
0x7e ,
0x7e ,
0x7e ,
0x7e ,
0x7e ,
0x7e ,
0x7e ,
0x7f ,
0x7f ,
0x80 ,
0x80 ,
0x80 ,
0x81 ,
0x81 ,
0x81 ,
0x81 ,
0x81 ,
0x81 ,
0x81 ,
0x81 ,
0x81 ,
0x80 ,
0x80 ,
0x80 ,
0x7f ,
0x7f ,
0x7f ,
0x7f ,
0x7e ,
0x7e ,
0x7e ,
0x7e ,
0x7e ,
0x7e ,
0x7e ,
0x7f ,
0x7f ,
0x7f ,
0x7f ,
0x80 ,
0x80 ,
0x80 ,
0x80 ,
0x80 ,
0x81 ,
0x81 ,
0x81 ,
0x81 ,
0x81 ,
0x80 ,
0x80 ,
0x80 ,
0x80 ,
0x80 ,
0x7f ,
0x7f ,
0x7f ,
0x7f ,
0x7f ,
0x7f ,
0x7f ,
0x7f ,
0x7e ,
0x7f ,
0x7e ,
0x7f ,
0x7f ,
0x7f ,
0x7f ,
0x7f ,
0x7f ,
0x80 ,
0x80 ,
0x80 ,
0x80 ,
0x80 ,
0x80 ,
0x80 ,
0x81 ,
0x80 ,
0x81 ,
0x80 ,
0x80 ,
0x80 ,
0x80 ,
0x80 ,
0x80 ,
0x7f ,
0x7f ,
0x7f ,
0x7f ,
0x7f ,
0x7e ,
0x7e ,
0x7e ,
0x7e ,
0x7e ,
0x7e ,
0x7e ,
0x7f ,
0x7f ,
0x7f ,
0x80 ,
0x80 ,
0x80 ,
0x80 ,
0x81 ,
0x81 ,
0x81 ,
0x81 ,
0x81 ,
0x81 ,
0x81 ,
0x80 ,
0x80 ,
0x80 ,
0x7f ,
0x7f ,
0x7f ,
0x7f ,
0x7e ,
0x7e ,
0x7e ,
0x7e ,
0x7e ,
0x7e ,
0x7e ,
0x7e ,
0x7f ,
0x7f ,
0x7f ,
0x80 ,
0x80 ,
0x80 ,
0x80 ,
0x81 ,
0x81 ,
0x81 ,
0x81 ,
0x81 ,
0x81 ,
0x80 ,
0x80 ,
0x80 ,
0x80 ,
0x80 ,
0x7f ,
0x7f ,
0x7f ,
0x7f ,
0x7e ,
0x7f ,
0x7e ,
0x7e ,
0x7f ,
0x7f ,
0x7f ,
0x7f ,
0x7f ,
0x7f ,
0x7f ,
0x80 ,
0x7f ,
0x80 ,
0x80 ,
0x81 ,
0x7e ,
0x84 ,
0x83 ,
0x82 ,
0x80 ,
0x76 ,
0x60 ,
0x72 ,
0x76 ,
0x88 ,
0x91 ,
0x9d ,
0xa1 ,
0x99 ,
0x8d ,
0x8b ,
0x85 ,
0x80 ,
0x67 ,
0x74 ,
0x6c ,
0x88 ,
0x81 ,
0x82 ,
0x5e ,
0x61 ,
0x4d ,
0x52 ,
0x6c ,
0x77 ,
0x8b ,
0xab ,
0xa2 ,
0x9e ,
0x9e ,
0x93 ,
0x83 ,
0x86 ,
0x76 ,
0x81 ,
0x86 ,
0x92 ,
0x77 ,
0x74 ,
0x63 ,
0x79 ,
0x5f ,
0x72 ,
0x6e ,
0x82 ,
0x91 ,
0x92 ,
0x96 ,
0x8c ,
0x82 ,
0x80 ,
0x81 ,
0x7c ,
0x83 ,
0x7a ,
0x92 ,
0x7d ,
0x5e ,
0x66 ,
0x57 ,
0x57 ,
0x7c ,
0x74 ,
0x76 ,
0x84 ,
0x97 ,
0x9d ,
0x9a ,
0x9f ,
0x89 ,
0x8b ,
0x88 ,
0x6f ,
0x75 ,
0x76 ,
0x7a ,
0x7d ,
0x73 ,
0x5c ,
0x63 ,
0x79 ,
0x76 ,
0x83 ,
0x82 ,
0x9b ,
0x95 ,
0x93 ,
0x98 ,
0x89 ,
0x7f ,
0x8e ,
0x87 ,
0x72 ,
0x8a ,
0x8b ,
0x84 ,
0x82 ,
0x6e ,
0x5c ,
0x54 ,
0x74 ,
0x68 ,
0x7e ,
0x96 ,
0x94 ,
0x8e ,
0xa3 ,
0x96 ,
0x7d ,
0x8d ,
0x71 ,
0x6c ,
0x75 ,
0x89 ,
0x85 ,
0x76 ,
0x71 ,
0x66 ,
0x5d ,
0x83 ,
0x6e ,
0x6e ,
0x97 ,
0x92 ,
0x99 ,
0x8a ,
0x8b ,
0x7e ,
0x7c ,
0x88 ,
0x85 ,
0x7f ,
0x85 ,
0x8d ,
0x74 ,
0x7a ,
0x7b ,
0x46 ,
0x69 ,
0x63 ,
0x7a ,
0x94 ,
0x93 ,
0x94 ,
0x9d ,
0xa2 ,
0x94 ,
0x86 ,
0x75 ,
0x7f ,
0x67 ,
0x88 ,
0x8b ,
0x7b ,
0x75 ,
0x74 ,
0x64 ,
0x76 ,
0x75 ,
0x65 ,
0x81 ,
0x8f ,
0x94 ,
0x8c ,
0x94 ,
0x86 ,
0x82 ,
0x91 ,
0x7e ,
0x7d ,
0x76 ,
0x8e ,
0x82 ,
0x82 ,
0x84 ,
0x53 ,
0x52 ,
0x63 ,
0x6d ,
0x7a ,
0x8e ,
0x81 ,
0xa2 ,
0xa6 ,
0x97 ,
0x82 ,
0x78 ,
0x91 ,
0x75 ,
0x7c ,
0x8c ,
0x7a ,
0x7b ,
0x87 ,
0x78 ,
0x66 ,
0x78 ,
0x69 ,
0x71 ,
0x7e ,
0x94 ,
0x87 ,
0x8b ,
0x8a ,
0x88 ,
0x7d ,
0x8d ,
0x6e ,
0x7a ,
0x87 ,
0x92 ,
0x88 ,
0x7a ,
0x86 ,
0x63 ,
0x75 ,
0x70 ,
0x6b ,
0x68 ,
0x94 ,
0x86 ,
0xab ,
0x9c ,
0x8d ,
0x82 ,
0x70 ,
0x91 ,
0x74 ,
0x7b ,
0x7f ,
0x88 ,
0x7f ,
0x8b ,
0x62 ,
0x63 ,
0x78 ,
0x6c ,
0x7a ,
0x77 ,
0x8c ,
0x8a ,
0x90 ,
0x97 ,
0x87 ,
0x72 ,
0x86 ,
0x74 ,
0x8a ,
0x92 ,
0x88 ,
0x80 ,
0x75 ,
0x87 ,
0x66 ,
0x74 ,
0x5f ,
0x6f ,
0x7a ,
0x93 ,
0x8a ,
0x9c ,
0x98 ,
0x95 ,
0x80 ,
0x76 ,
0x7a ,
0x75 ,
0x7e ,
0x90 ,
0x7f ,
0x6d ,
0x82 ,
0x5d ,
0x84 ,
0x79 ,
0x64 ,
0x72 ,
0x7d ,
0x96 ,
0x9a ,
0x8a ,
0x8a ,
0x87 ,
0x83 ,
0x89 ,
0x75 ,
0x7a ,
0x8e ,
0x92 ,
0x83 ,
0x7f ,
0x63 ,
0x67 ,
0x78 ,
0x6d ,
0x71 ,
0x6f ,
0x90 ,
0x8a ,
0xa0 ,
0x96 ,
0x8e ,
0x83 ,
0x83 ,
0x85 ,
0x75 ,
0x78 ,
0x86 ,
0x7b ,
0x80 ,
0x81 ,
0x5d ,
0x80 ,
0x75 ,
0x74 ,
0x7a ,
0x78 ,
0x8c ,
0x91 ,
0x8b ,
0x8d ,
0x74 ,
0x7a ,
0x81 ,
0x7d ,
0x88 ,
0x87 ,
0x8a ,
0x78 ,
0x91 ,
0x68 ,
0x60 ,
0x75 ,
0x63 ,
0x76 ,
0x85 ,
0x81 ,
0x98 ,
0x97 ,
0xa1 ,
0x92 ,
0x70 ,
0x7f ,
0x7a ,
0x77 ,
0x8d ,
0x78 ,
0x7e ,
0x73 ,
0x74 ,
0x64 ,
0x76 ,
0x79 ,
0x71 ,
0x80 ,
0x93 ,
0x79 ,
0x9b ,
0x7d ,
0x94 ,
0x86 ,
0x80 ,
0x99 ,
0x84 ,
0x97 ,
0xa2 ,
0x89 ,
0x95 ,
0x90 ,
0x5e ,
0x64 ,
0x44 ,
0x44 ,
0x4e ,
0x50 ,
0x54 ,
0x57 ,
0x63 ,
0x68 ,
0x6e ,
0x59 ,
0x69 ,
0x73 ,
0x8f ,
0xa7 ,
0xa5 ,
0xa4 ,
0xbc ,
0xac ,
0xa1 ,
0xb9 ,
0xa8 ,
0xb0 ,
0xbc ,
0xc3 ,
0xb9 ,
0xb4 ,
0xae ,
0x9b ,
0x6c ,
0x67 ,
0x4d ,
0x43 ,
0x5b ,
0x5b ,
0x3f ,
0x3a ,
0x38 ,
0x35 ,
0x3f ,
0x47 ,
0x40 ,
0x4c ,
0x7c ,
0x7d ,
0x90 ,
0x9f ,
0xaf ,
0xb5 ,
0xab ,
0xae ,
0xaf ,
0xa6 ,
0xc8 ,
0xbb ,
0x9d ,
0xb1 ,
0x91 ,
0x94 ,
0xa5 ,
0x8f ,
0x93 ,
0x88 ,
0x93 ,
0x91 ,
0x7f ,
0x83 ,
0x75 ,
0x5f ,
0x65 ,
0x57 ,
0x5e ,
0x6d ,
0x75 ,
0x69 ,
0x5b ,
0x5e ,
0x4d ,
0x55 ,
0x57 ,
0x49 ,
0x50 ,
0x6c ,
0x63 ,
0x72 ,
0x6f ,
0x79 ,
0x66 ,
0x66 ,
0x5f ,
0x66 ,
0x67 ,
0x8a ,
0x7b ,
0x73 ,
0x92 ,
0x77 ,
0x92 ,
0xa9 ,
0x9c ,
0xae ,
0xbb ,
0xc9 ,
0xcf ,
0xbb ,
0xd6 ,
0xc0 ,
0xae ,
0xb0 ,
0xa2 ,
0x9e ,
0xc1 ,
0xb5 ,
0x97 ,
0x87 ,
0x74 ,
0x67 ,
0x69 ,
0x5f ,
0x45 ,
0x3e ,
0x5a ,
0x4b ,
0x4c ,
0x48 ,
0x4c ,
0x49 ,
0x48 ,
0x40 ,
0x44 ,
0x46 ,
0x65 ,
0x5c ,
0x47 ,
0x6b ,
0x54 ,
0x68 ,
0x86 ,
0x71 ,
0x90 ,
0x9a ,
0xab ,
0xbe ,
0xb2 ,
0xcd ,
0xc1 ,
0xab ,
0xbd ,
0xaf ,
0xb1 ,
0xd1 ,
0xc2 ,
0xb5 ,
0xb3 ,
0xa0 ,
0x94 ,
0xa1 ,
0x8c ,
0x88 ,
0x7b ,
0x98 ,
0x83 ,
0x7f ,
0x85 ,
0x75 ,
0x60 ,
0x60 ,
0x4a ,
0x4a ,
0x55 ,
0x5c ,
0x50 ,
0x36 ,
0x51 ,
0x35 ,
0x54 ,
0x5a ,
0x49 ,
0x59 ,
0x72 ,
0x63 ,
0x73 ,
0x60 ,
0x7c ,
0x79 ,
0x70 ,
0x7c ,
0x79 ,
0x7c ,
0xa7 ,
0x9d ,
0x8e ,
0xa2 ,
0x85 ,
0x97 ,
0xa6 ,
0x9d ,
0xa0 ,
0x97 ,
0xac ,
0xa9 ,
0x9a ,
0xb2 ,
0xa7 ,
0x9a ,
0x9d ,
0x89 ,
0x84 ,
0x8a ,
0x93 ,
0x83 ,
0x78 ,
0x88 ,
0x72 ,
0x7f ,
0x81 ,
0x6d ,
0x71 ,
0x82 ,
0x6e ,
0x7b ,
0x6d ,
0x7c ,
0x6c ,
0x65 ,
0x64 ,
0x66 ,
0x61 ,
0x84 ,
0x73 ,
0x69 ,
0x83 ,
0x60 ,
0x73 ,
0x7c ,
0x69 ,
0x74 ,
0x76 ,
0x7e ,
0x83 ,
0x70 ,
0x92 ,
0x7f ,
0x7f ,
0x84 ,
0x79 ,
0x7a ,
0x90 ,
0x8d ,
0x83 ,
0x7f ,
0x81 ,
0x85 ,
0x90 ,
0x94 ,
0x85 ,
0x88 ,
0x96 ,
0x87 ,
0x80 ,
0x83 ,
0x87 ,
0x89 ,
0x83 ,
0x80 ,
0x7e ,
0x79 ,
0x8c ,
0x85 ,
0x83 ,
0x90 ,
0x7c ,
0x7e ,
0x86 ,
0x7e ,
0x7a ,
0x7b ,
0x77 ,
0x7f ,
0x75 ,
0x84 ,
0x78 ,
0x74 ,
0x7b ,
0x76 ,
0x70 ,
0x7e ,
0x7b ,
0x78 ,
0x82 ,
0x7b ,
0x78 ,
0x82 ,
0x82 ,
0x7f ,
0x81 ,
0x86 ,
0x80 ,
0x82 ,
0x83 ,
0x84 ,
0x7a ,
0x7e ,
0x7f ,
0x7d ,
0x82 ,
0x86 ,
0x80 ,
0x7f ,
0x84 ,
0x7c ,
0x80 ,
0x82 ,
0x7d ,
0x7c ,
0x82 ,
0x7c ,
0x81 ,
0x7b ,
0x83 ,
0x7d ,
0x7d ,
0x80 ,
0x7c ,
0x7a ,
0x82 ,
0x80 ,
0x7e ,
0x83 ,
0x7e ,
0x7c ,
0x83 ,
0x82 ,
0x80 ,
0x81 ,
0x81 ,
0x80 ,
0x7f ,
0x80 ,
0x80 ,
0x7d ,
0x80 ,
0x7f ,
0x7c ,
0x7f ,
0x7f ,
0x7f ,
0x80 ,
0x80 ,
0x7e ,
0x81 ,
0x80 ,
0x80 ,
0x7f ,
0x80 ,
0x7f ,
0x80 ,
0x7f ,
0x80 ,
0x80 ,
0x80 ,
0x80 ,
0x80 ,
0x7f ,
0x7f ,
0x80 ,
0x80 ,
0x80 ,
0x7f ,
0x80 ,
0x80 ,
0x7f ,
0x7f ,
0x7f ,
0x7f ,
0x7f ,
0x7f ,
0x7f ,
0x7f ,
0x7f ,
0x7f ,
0x7f ,
0x7f ,
0x7f ,
0x7f ,
0x7f ,
0x7f ,
0x80 ,
0x80 ,
0x80 ,
0x80 ,
0x80 ,
0x80 ,
0x80 ,
0x80 ,
0x80 ,
0x80 ,
0x80 ,
0x80 ,
0x80 ,
0x80 ,
0x80 ,
0x80 ,
0x80 ,
0x7f ,
0x7f ,
0x7f ,
0x7f ,
0x7f ,
0x7f ,
0x7f ,
0x7f ,
0x7f ,
0x7f ,
0x7f ,
0x7f ,
0x7f ,
0x7f ,
0x80 ,
0x80 ,
0x80 ,
0x80 ,
0x80 ,
0x80 ,
0x80 ,
0x80 ,
0x80 ,
0x80 ,
0x81 ,
0x81 ,
0x7f ,
0x7f ,
0x80 ,
0x7f ,
0x7f ,
0x7f ,
0x7f ,
0x7f ,
0x7f ,
0x7f ,
0x7d ,
0x7f ,
0x80 ,
0x80 ,
0x7f ,
0x7f ,
0x7f ,
0x7f ,
0x80 ,
0x80 ,
0x80 ,
0x80 ,
0x7f ,
0x81 ,
0x80 ,
0x80 ,
0x80 ,
0x7f ,
0x80 ,
0x80 ,
0x7f ,
0x80 ,
0x81 ,
0x7f ,
0x7f ,
0x7e ,
0x7f ,
0x7f ,
0x7f ,
0x7f ,
0x7f ,
0x7f ,
0x7f ,
0x7f ,
0x7f ,
0x7f ,
0x80 ,
0x7f ,
0x7f ,
0x80 ,
0x81 ,
0x80 ,
0x7f ,
0x7f ,
0x80 ,
0x80 ,
0x80 ,
0x80 ,
0x7f ,
0x80 ,
0x80 ,
0x80 ,
0x7f ,
0x80 ,
0x7f ,
0x80 ,
0x80 ,
0x7f ,
0x7f ,
0x7f ,
0x7f ,
0x7f ,
0x7e ,
0x7f ,
0x80 ,
0x80 ,
0x7f ,
0x7f ,
0x7f ,
0x7f ,
0x80 ,
0x80 ,
0x80 ,
0x80 ,
0x80 ,
0x80 ,
0x7f ,
0x80 ,
0x7f ,
0x80 ,
0x80 ,
0x80 ,
0x7f ,
0x7f ,
0x7f ,
0x80 ,
0x7f ,
0x7f ,
0x80 ,
0x7f ,
0x7f ,
0x7f ,
0x7f ,
0x7f ,
0x7f ,
0x7f ,
0x7f ,
0x7f ,
0x80 ,
0x7f ,
0x7f ,
0x80 ,
0x80 ,
0x80 ,
0x80 ,
0x80 ,
0x80 ,
0x80 ,
0x80 ,
0x80 ,
0x80 ,
0x80 ,
0x81 ,
0x80 ,
0x7f ,
0x7f ,
0x7f ,
0x7f ,
0x80 ,
0x7f ,
0x7f ,
0x7f ,
0x7f ,
0x7f ,
0x7f ,
0x7f ,
0x7f ,
0x80 ,
0x80 ,
0x7f ,
0x7f ,
0x7f ,
0x80 ,
0x80 ,
0x80 ,
0x80 ,
0x80 ,
0x80 ,
0x80 ,
0x80 ,
0x80 ,
0x80 ,
0x80 ,
0x80 ,
0x7f ,
0x7f ,
0x7f ,
0x7f ,
0x80 ,
0x7f ,
0x7f ,
0x7f ,
0x7f ,
0x7f ,
0x7f ,
0x7f ,
0x7f ,
0x7f ,
0x7f ,
0x80 ,
0x7f ,
0x80 ,
0x80 ,
0x80 ,
0x80 ,
0x80 ,
0x80 ,
0x80 ,
0x7f ,
0x80 ,
0x80 ,
0x80 ,
0x80 ,
0x80 ,
0x7f ,
0x7f ,
0x7f ,
0x7f ,
0x80 ,
0x7f ,
0x7f ,
0x7f ,
0x7f ,
0x7f ,
0x7f ,
0x7f ,
0x7f ,
0x7f ,
0x7f ,
0x7f ,
0x7f ,
0x7f ,
0x7f ,
0x80 ,
0x80 ,
0x80 ,
0x80 ,
0x80 ,
0x80 ,
0x80 ,
0x80 ,
0x80 ,
0x80 ,
0x80 ,
0x80 ,
0x80 ,
0x80 ,
0x80 ,
0x80 ,
0x7f ,
0x7f ,
0x7f ,
0x7f ,
0x7f ,
0x7f ,
0x7f ,
0x7f ,
0x7f ,
0x7f ,
0x7f ,
0x7f ,
0x7f ,
0x7f ,
0x80 ,
0x80 ,
0x80 ,
0x80 ,
0x80 ,
0x80 ,
0x80 ,
0x80 ,
0x80 ,
0x80 ,
0x80 ,
0x80 ,
0x80 ,
0x80 ,
0x80 ,
0x7f ,
0x7f ,
0x7f ,
0x7f ,
0x7f ,
0x7f ,
0x7f ,
0x7f ,
0x7f ,
0x7f ,
0x7f ,
0x7f ,
0x7f ,
0x7f ,
0x7f ,
0x80 ,
0x80 ,
0x80 ,
0x80 ,
0x80 ,
0x80 ,
0x80 ,
0x80 ,
0x80 ,
0x80 ,
0x80 ,
0x80 ,
0x80 ,
0x80 ,
0x7f ,
0x7f ,
0x7f ,
0x7f ,
0x7f ,
0x7f ,
0x7f ,
0x7f ,
0x7f ,
0x7f ,
0x7f ,
0x7f ,
0x7f ,
0x7f ,
0x7f ,
0x80 ,
0x80 ,
0x80 ,
0x80 ,
0x80 ,
0x80 ,
0x80 ,
0x80 ,
0x80 ,
0x80 ,
0x80 ,
0x80 ,
0x80 ,
0x80 ,
0x80 ,
0x7f ,
0x7f ,
0x7f ,
0x7f ,
0x7f ,
0x7f ,
0x7f ,
0x7f ,
0x7f ,
0x7f ,
0x7f ,
0x7f ,
0x7f ,
0x7f ,
0x7f ,
0x7f ,
0x7f ,
0x7f ,
0x80 ,
0x80 ,
0x80 ,
0x80 ,
0x80 ,
0x80 ,
0x80 ,
0x80 ,
0x80 ,
0x80 ,
0x80 ,
0x80 ,
0x80 ,
0x80 ,
0x80 ,
0x7f ,
0x7f ,
0x7f ,
0x7f ,
0x7f ,
0x7f ,
0x7f ,
0x7f ,
0x7f ,
0x7f ,
0x7f ,
0x7f ,
0x7f ,
0x7f ,
0x7f ,
0x7e ,
0x81 ,
0x82 ,
0x84 ,
0x7f ,
0x7c ,
0x7f ,
0x7e ,
0x6c ,
0x6a ,
0x6c ,
0x88 ,
0x86 ,
0x96 ,
0x9c ,
0x9b ,
0xa4 ,
0x92 ,
0x91 ,
0x88 ,
0x8f ,
0x83 ,
0x6b ,
0x71 ,
0x6f ,
0x72 ,
0x83 ,
0x8a ,
0x86 ,
0x6e ,
0x67 ,
0x53 ,
0x4a ,
0x50 ,
0x70 ,
0x7a ,
0x95 ,
0xa7 ,
0x9c ,
0xa9 ,
0xa6 ,
0x97 ,
0x8c ,
0x7f ,
0x8a ,
0x81 ,
0x76 ,
0x7e ,
0x8a ,
0x70 ,
0x7f ,
0x74 ,
0x62 ,
0x6c ,
0x73 ,
0x70 ,
0x6e ,
0x75 ,
0x8f ,
0x94 ,
0x91 ,
0x90 ,
0x94 ,
0x89 ,
0x80 ,
0x88 ,
0x89 ,
0x8b ,
0x79 ,
0x85 ,
0x8d ,
0x88 ,
0x6b ,
0x5e ,
0x61 ,
0x48 ,
0x69 ,
0x7e ,
0x7a ,
0x74 ,
0x92 ,
0xa2 ,
0x9b ,
0x9c ,
0x98 ,
0x91 ,
0x90 ,
0x7e ,
0x84 ,
0x67 ,
0x6a ,
0x7b ,
0x8d ,
0x91 ,
0x7a ,
0x6d ,
0x69 ,
0x61 ,
0x83 ,
0x84 ,
0x85 ,
0x5c ,
0x93 ,
0x94 ,
0x90 ,
0xa5 ,
0x91 ,
0x83 ,
0x70 ,
0x8b ,
0x8a ,
0x7e ,
0x74 ,
0x73 ,
0x80 ,
0x81 ,
0x82 ,
0x6d ,
0x57 ,
0x4f ,
0x73 ,
0x7b ,
0x83 ,
0x72 ,
0x98 ,
0x96 ,
0x87 ,
0xa5 ,
0x85 ,
0x95 ,
0x8e ,
0x7d ,
0x7c ,
0x69 ,
0x70 ,
0x8a ,
0x9b ,
0x6f ,
0x7f ,
0x7c ,
0x53 ,
0x76 ,
0x81 ,
0x7f ,
0x78 ,
0x7e ,
0x89 ,
0x99 ,
0x96 ,
0x91 ,
0x85 ,
0x95 ,
0x7e ,
0x98 ,
0x80 ,
0x72 ,
0x74 ,
0x79 ,
0x82 ,
0x78 ,
0x82 ,
0x75 ,
0x40 ,
0x6e ,
0x77 ,
0x7c ,
0x79 ,
0x8e ,
0x82 ,
0x92 ,
0x91 ,
0x93 ,
0x8d ,
0x8d ,
0x73 ,
0x85 ,
0x69 ,
0x68 ,
0x83 ,
0x83 ,
0x80 ,
0x6f ,
0x88 ,
0x60 ,
0x63 ,
0x78 ,
0x7f ,
0x6b ,
0x83 ,
0x83 ,
0x89 ,
0x91 ,
0xa3 ,
0x8c ,
0xa3 ,
0x79 ,
0x94 ,
0x8a ,
0x77 ,
0x6c ,
0x8b ,
0x7c ,
0x89 ,
0x7e ,
0x80 ,
0x47 ,
0x6f ,
0x6b ,
0x7b ,
0x86 ,
0x7f ,
0x81 ,
0x90 ,
0x84 ,
0xa7 ,
0x9c ,
0x92 ,
0x7d ,
0x89 ,
0x7e ,
0x71 ,
0x74 ,
0x7f ,
0x81 ,
0x6e ,
0x8d ,
0x7b ,
0x62 ,
0x78 ,
0x66 ,
0x6b ,
0x81 ,
0x7e ,
0x91 ,
0x7a ,
0x87 ,
0x95 ,
0x93 ,
0x90 ,
0x86 ,
0x8d ,
0x7e ,
0x6f ,
0x76 ,
0x8b ,
0x80 ,
0x77 ,
0x88 ,
0x5c ,
0x5b ,
0x70 ,
0x7a ,
0x7f ,
0x73 ,
0x81 ,
0x98 ,
0x91 ,
0xa1 ,
0x92 ,
0x91 ,
0x88 ,
0x82 ,
0x87 ,
0x7c ,
0x74 ,
0x76 ,
0x7a ,
0x8f ,
0x79 ,
0x9d ,
0x5e ,
0x6d ,
0x65 ,
0x7c ,
0x78 ,
0x87 ,
0x87 ,
0x83 ,
0x87 ,
0x91 ,
0x99 ,
0x96 ,
0x7d ,
0x80 ,
0x82 ,
0x78 ,
0x82 ,
0x79 ,
0x7e ,
0x7c ,
0x7c ,
0x83 ,
0x65 ,
0x72 ,
0x72 ,
0x69 ,
0x7e ,
0x79 ,
0x97 ,
0x89 ,
0x99 ,
0x7d ,
0x9c ,
0x86 ,
0x8e ,
0x84 ,
0x82 ,
0x60 ,
0x74 ,
0x7e ,
0x8b ,
0x7f ,
0x91 ,
0x68 ,
0x6a ,
0x79 ,
0x74 ,
0x7c ,
0x84 ,
0x75 ,
0x87 ,
0x87 ,
0x8f ,
0x8a ,
0x94 ,
0x8b ,
0x82 ,
0x88 ,
0x89 ,
0x79 ,
0x7f ,
0x7c ,
0x7a ,
0x7b ,
0x8b ,
0x6d ,
0x64 ,
0x6f ,
0x73 ,
0x6c ,
0x7d ,
0x86 ,
0x7e ,
0x8f ,
0x8c ,
0x86 ,
0x99 ,
0x88 ,
0x78 ,
0x7d ,
0x78 ,
0x6a ,
0x80 ,
0x7d ,
0x7a ,
0x6b ,
0x89 ,
0x6e ,
0x7c ,
0x79 ,
0x6f ,
0x6e ,
0x7d ,
0x8e ,
0x84 ,
0x91 ,
0x7c ,
0x96 ,
0x88 ,
0x99 ,
0x87 ,
0x8e ,
0x77 ,
0x80 ,
0x79 ,
0x8e ,
0x79 ,
0x7a ,
0x76 ,
0x6b ,
0x76 ,
0x75 ,
0x74 ,
0x71 ,
0x77 ,
0x8f ,
0x90 ,
0x9b ,
0x89 ,
0x87 ,
0x8b ,
0x85 ,
0x88 ,
0x8b ,
0x6d ,
0x6f ,
0x82 ,
0x76 ,
0x81 ,
0x7a ,
0x71 ,
0x66 ,
0x7c ,
0x77 ,
0x82 ,
0x6f ,
0x7a ,
0x80 ,
0x82 ,
0x8e ,
0x89 ,
0x99 ,
0x8b ,
0x80 ,
0x8a ,
0x91 ,
0x78 ,
0x81 ,
0x79 ,
0x82 ,
0x81 ,
0x87 ,
0x6d ,
0x61 ,
0x72 ,
0x72 ,
0x7f ,
0x8d ,
0x86 ,
0x88 ,
0x96 ,
0x89 ,
0x8f ,
0xa5 ,
0x7d ,
0x84 ,
0x84 ,
0x81 ,
0x6e ,
0x7c ,
0x6f ,
0x75 ,
0x6b ,
0x8e ,
0x74 ,
0x70 ,
0x78 ,
0x6d ,
0x70 ,
0x8d ,
0x86 ,
0x83 ,
0x89 ,
0x84 ,
0x93 ,
0x96 ,
0x91 ,
0x71 ,
0x8d ,
0x7e ,
0x86 ,
0x88 ,
0x82 ,
0x6b ,
0x81 ,
0x7c ,
0x6e ,
0x70 ,
0x6b ,
0x6d ,
0x74 ,
0x88 ,
0x92 ,
0x83 ,
0x8a ,
0x85 ,
0x86 ,
0xa3 ,
0x8c ,
0x89 ,
0x80 ,
0x80 ,
0x72 ,
0x83 ,
0x73 ,
0x7a ,
0x72 ,
0x89 ,
0x74 ,
0x7e ,
0x7d ,
0x67 ,
0x75 ,
0x83 ,
0x8e ,
0x81 ,
0x84 ,
0x7a ,
0x95 ,
0x89 ,
0x85 ,
0x82 ,
0x7f ,
0x76 ,
0x79 ,
0x84 ,
0x82 ,
0x74 ,
0x7f ,
0x78 ,
0x6a ,
0x79 ,
0x75 ,
0x70 ,
0x82 ,
0x7d ,
0x9a ,
0x84 ,
0x93 ,
0x77 ,
0x98 ,
0x82 ,
0x90 ,
0x87 ,
0x81 ,
0x6e ,
0x7b ,
0x81 ,
0x79 ,
0x7f ,
0x79 ,
0x79 ,
0x6b ,
0x88 ,
0x76 ,
0x81 ,
0x7b ,
0x8c ,
0x84 ,
0x89 ,
0x7e ,
0x77 ,
0x91 ,
0x87 ,
0x83 ,
0x90 ,
0x89 ,
0x71 ,
0x88 ,
0x77 ,
0x75 ,
0x7e ,
0x78 ,
0x6c ,
0x69 ,
0x7a ,
0x7a ,
0x78 ,
0x84 ,
0x82 ,
0x81 ,
0x95 ,
0x86 ,
0x87 ,
0x97 ,
0x7f ,
0x8f ,
0x85 ,
0x82 ,
0x66 ,
0x83 ,
0x77 ,
0x7f ,
0x77 ,
0x7e ,
0x70 ,
0x77 ,
0x81 ,
0x75 ,
0x7d ,
0x82 ,
0x89 ,
0x76 ,
0x98 ,
0x7b ,
0x89 ,
0x89 ,
0x93 ,
0x86 ,
0x91 ,
0x7e ,
0x72 ,
0x86 ,
0x78 ,
0x73 ,
0x80 ,
0x6a ,
0x69 ,
0x6e ,
0x79 ,
0x77 ,
0x78 ,
0x78 ,
0x8b ,
0x7f ,
0x9a ,
0x81 ,
0x84 ,
0x8a ,
0x81 ,
0x8c ,
0x86 ,
0x77 ,
0x6c ,
0x86 ,
0x72 ,
0x85 ,
0x73 ,
0x72 ,
0x6b ,
0x7a ,
0x85 ,
0x81 ,
0x76 ,
0x85 ,
0x8d ,
0x85 ,
0x8e ,
0x7f ,
0x87 ,
0x89 ,
0x83 ,
0x8f ,
0x90 ,
0x73 ,
0x7b ,
0x7c ,
0x7f ,
0x7c ,
0x81 ,
0x69 ,
0x6c ,
0x71 ,
0x7d ,
0x78 ,
0x80 ,
0x7a ,
0x95 ,
0x94 ,
0x92 ,
0x8d ,
0x85 ,
0x85 ,
0x85 ,
0x85 ,
0x88 ,
0x67 ,
0x74 ,
0x7a ,
0x79 ,
0x7e ,
0x81 ,
0x71 ,
0x75 ,
0x7c ,
0x7e ,
0x7f ,
0x71 ,
0x86 ,
0x81 ,
0x98 ,
0x83 ,
0x8a ,
0x8d ,
0x91 ,
0x7b ,
0x90 ,
0x87 ,
0x73 ,
0x7e ,
0x75 ,
0x80 ,
0x82 ,
0x86 ,
0x6b ,
0x76 ,
0x78 ,
0x79 ,
0x76 ,
0x83 ,
0x89 ,
0x84 ,
0x98 ,
0x8d ,
0x86 ,
0x94 ,
0x7e ,
0x89 ,
0x85 ,
0x80 ,
0x6b ,
0x7d ,
0x71 ,
0x7e ,
0x72 ,
0x82 ,
0x6e ,
0x7b ,
0x84 ,
0x73 ,
0x7a ,
0x7e ,
0x8e ,
0x76 ,
0x91 ,
0x7a ,
0x87 ,
0x87 ,
0x88 ,
0x81 ,
0x90 ,
0x7f ,
0x7b ,
0x87 ,
0x7d ,
0x73 ,
0x80 ,
0x6e ,
0x6c ,
0x73 ,
0x7e ,
0x7b ,
0x7d ,
0x7f ,
0x92 ,
0x7f ,
0x92 ,
0x80 ,
0x84 ,
0x8c ,
0x83 ,
0x8d ,
0x88 ,
0x78 ,
0x72 ,
0x83 ,
0x79 ,
0x82 ,
0x7e ,
0x73 ,
0x74 ,
0x7b ,
0x7f ,
0x7b ,
0x72 ,
0x85 ,
0x81 ,
0x84 ,
0x85 ,
0x7c ,
0x8c ,
0x85 ,
0x7e ,
0x89 ,
0x88 ,
0x75 ,
0x7d ,
0x7f ,
0x82 ,
0x77 ,
0x87 ,
0x69 ,
0x78 ,
0x71 ,
0x79 ,
0x78 ,
0x83 ,
0x79 ,
0x85 ,
0x93 ,
0x8b ,
0x8a ,
0x91 ,
0x86 ,
0x8b ,
0x86 ,
0x80 ,
0x6a ,
0x7a ,
0x7d ,
0x7b ,
0x84 ,
0x80 ,
0x73 ,
0x7e ,
0x7b ,
0x74 ,
0x81 ,
0x7b ,
0x86 ,
0x75 ,
0x96 ,
0x79 ,
0x84 ,
0x8f ,
0x94 ,
0x8d ,
0xa2 ,
0x91 ,
0x7c ,
0x93 ,
0x7a ,
0x8c ,
0x91 ,
0x66 ,
0x66 ,
0x4e ,
0x51 ,
0x56 ,
0x43 ,
0x51 ,
0x50 ,
0x4f ,
0x6c ,
0x60 ,
0x6c ,
0x79 ,
0x6e ,
0xa0 ,
0x9b ,
0xa0 ,
0x9f ,
0xbb ,
0xac ,
0xb8 ,
0xad ,
0xaa ,
0xa9 ,
0xb0 ,
0xb6 ,
0xa6 ,
0xa4 ,
0xa1 ,
0x9b ,
0x76 ,
0x7a ,
0x4b ,
0x4e ,
0x4a ,
0x4b ,
0x4a ,
0x59 ,
0x3b ,
0x41 ,
0x49 ,
0x48 ,
0x4d ,
0x5d ,
0x53 ,
0x5f ,
0x72 ,
0x8e ,
0x97 ,
0x99 ,
0xa9 ,
0xc2 ,
0xc6 ,
0xc5 ,
0xbb ,
0xb5 ,
0xb7 ,
0xb5 ,
0xb9 ,
0xb4 ,
0x93 ,
0x90 ,
0x92 ,
0x8a ,
0x91 ,
0x7e ,
0x74 ,
0x6a ,
0x6b ,
0x6e ,
0x65 ,
0x58 ,
0x6f ,
0x67 ,
0x78 ,
0x6b ,
0x6a ,
0x6a ,
0x67 ,
0x62 ,
0x69 ,
0x6a ,
0x4e ,
0x56 ,
0x4b ,
0x5f ,
0x59 ,
0x63 ,
0x4b ,
0x5b ,
0x5d ,
0x65 ,
0x69 ,
0x72 ,
0x80 ,
0x89 ,
0xa6 ,
0xa4 ,
0xac ,
0xb6 ,
0xad ,
0xbe ,
0xbc ,
0xbc ,
0xaa ,
0xb7 ,
0xad ,
0xb5 ,
0xb1 ,
0xaf ,
0x9f ,
0xa4 ,
0xa4 ,
0x99 ,
0x98 ,
0x84 ,
0x93 ,
0x6f ,
0x7f ,
0x5c ,
0x57 ,
0x52 ,
0x4c ,
0x44 ,
0x54 ,
0x42 ,
0x3c ,
0x45 ,
0x3c ,
0x3f ,
0x4f ,
0x43 ,
0x42 ,
0x53 ,
0x5f ,
0x63 ,
0x68 ,
0x7f ,
0x89 ,
0x86 ,
0xa6 ,
0x99 ,
0xab ,
0xba ,
0xaf ,
0xc5 ,
0xbf ,
0xb5 ,
0xab ,
0xbb ,
0xb0 ,
0xb2 ,
0xb0 ,
0xa4 ,
0xa3 ,
0xa5 ,
0xa7 ,
0x97 ,
0x8d ,
0x98 ,
0x8e ,
0x83 ,
0x88 ,
0x6b ,
0x7b ,
0x6e ,
0x6c ,
0x64 ,
0x67 ,
0x50 ,
0x4f ,
0x56 ,
0x55 ,
0x41 ,
0x5a ,
0x39 ,
0x4a ,
0x45 ,
0x4e ,
0x52 ,
0x57 ,
0x60 ,
0x67 ,
0x78 ,
0x7b ,
0x76 ,
0x7f ,
0x88 ,
0x8c ,
0x90 ,
0x8f ,
0x83 ,
0x8e ,
0x95 ,
0x9b ,
0xa7 ,
0xa0 ,
0x9e ,
0xa3 ,
0xa5 ,
0xa1 ,
0xa2 ,
0x97 ,
0xab ,
0x93 ,
0xaf ,
0x94 ,
0x98 ,
0x9a ,
0x93 ,
0x8c ,
0x8c ,
0x86 ,
0x71 ,
0x7e ,
0x6c ,
0x72 ,
0x6e ,
0x69 ,
0x5e ,
0x6b ,
0x64 ,
0x6b ,
0x68 ,
0x78 ,
0x6f ,
0x70 ,
0x89 ,
0x70 ,
0x7c ,
0x7b ,
0x72 ,
0x83 ,
0x78 ,
0x71 ,
0x65 ,
0x75 ,
0x6b ,
0x6e ,
0x7b ,
0x67 ,
0x6e ,
0x7b ,
0x81 ,
0x7a ,
0x83 ,
0x85 ,
0x92 ,
0x84 ,
0x9a ,
0x7b ,
0x88 ,
0x8b ,
0x8b ,
0x8b ,
0x98 ,
0x81 ,
0x82 ,
0x8d ,
0x79 ,
0x7b ,
0x8b ,
0x72 ,
0x76 ,
0x80 ,
0x85 ,
0x85 ,
0x80 ,
0x8b ,
0x8b ,
0x93 ,
0x94 ,
0x86 ,
0x86 ,
0x8e ,
0x75 ,
0x87 ,
0x82 ,
0x6c ,
0x6b ,
0x74 ,
0x70 ,
0x7c ,
0x77 ,
0x71 ,
0x72 ,
0x7b ,
0x7e ,
0x75 ,
0x77 ,
0x87 ,
0x83 ,
0x90 ,
0x8c ,
0x82 ,
0x88 ,
0x85 ,
0x8a ,
0x83 ,
0x8f ,
0x72 ,
0x7d ,
0x76 ,
0x82 ,
0x79 ,
0x8d ,
0x6f ,
0x7b ,
0x77 ,
0x79 ,
0x7a ,
0x77 ,
0x81 ,
0x7f ,
0x98 ,
0x8c ,
0x89 ,
0x86 ,
0x81 ,
0x83 ,
0x84 ,
0x81 ,
0x71 ,
0x73 ,
0x74 ,
0x7b ,
0x86 ,
0x7d ,
0x77 ,
0x80 ,
0x84 ,
0x7f ,
0x83 ,
0x74 ,
0x8f ,
0x75 ,
0x93 ,
0x7f ,
0x80 ,
0x8a ,
0x7f ,
0x89 ,
0x8d ,
0x85 ,
0x7b ,
0x82 ,
0x6e ,
0x81 ,
0x80 ,
0x79 ,
0x6f ,
0x7e ,
0x7d ,
0x7b ,
0x7a ,
0x85 ,
0x87 ,
0x81 ,
0x93 ,
0x7f ,
0x86 ,
0x84 ,
0x75 ,
0x91 ,
0x84 ,
0x7d ,
0x73 ,
0x7e ,
0x76 ,
0x76 ,
0x80 ,
0x6b ,
0x77 ,
0x80 ,
0x84 ,
0x7e ,
0x80 ,
0x7d ,
0x86 ,
0x7c ,
0x8f ,
0x70 ,
0x87 ,
0x83 ,
0x8a ,
0x83 ,
0x91 ,
0x7b ,
0x7b ,
0x83 ,
0x7d ,
0x75 ,
0x8d ,
0x6a ,
0x78 ,
0x7c ,
0x7a ,
0x7f ,
0x77 ,
0x8b ,
0x80 ,
0x90 ,
0x8e ,
0x83 ,
0x89 ,
0x8c ,
0x81 ,
0x8a ,
0x82 ,
0x73 ,
0x72 ,
0x77 ,
0x7b ,
0x7c ,
0x7d ,
0x74 ,
0x81 ,
0x82 ,
0x7f ,
0x77 ,
0x76 ,
0x88 ,
0x75 ,
0x92 ,
0x82 ,
0x80 ,
0x8c ,
0x85 ,
0x8b ,
0x7e ,
0x86 ,
0x74 ,
0x82 ,
0x7a ,
0x80 ,
0x75 ,
0x7a ,
0x6e ,
0x7e ,
0x78 ,
0x7b ,
0x79 ,
0x83 ,
0x85 ,
0x7e ,
0x98 ,
0x81 ,
0x87 ,
0x82 ,
0x86 ,
0x90 ,
0x87 ,
0x7c ,
0x73 ,
0x7c ,
0x73 ,
0x75 ,
0x86 ,
0x6a ,
0x78 ,
0x81 ,
0x84 ,
0x80 ,
0x7f ,
0x7b ,
0x90 ,
0x78 ,
0x92 ,
0x74 ,
0x81 ,
0x84 ,
0x7c ,
0x85 ,
0x88 ,
0x7c ,
0x79 ,
0x82 ,
0x6f ,
0x79 ,
0x7c ,
0x6c ,
0x6e ,
0x7f ,
0x7b ,
0x80 ,
0x7b ,
0x8c ,
0x84 ,
0x8f ,
0x92 ,
0x82 ,
0x85 ,
0x8c ,
0x78 ,
0x8b ,
0x87 ,
0x72 ,
0x74 ,
0x78 ,
0x77 ,
0x78 ,
0x87 ,
0x70 ,
0x79 ,
0x82 ,
0x84 ,
0x78 ,
0x80 ,
0x86 ,
0x87 ,
0x8f ,
0x8e ,
0x7d ,
0x85 ,
0x86 ,
0x84 ,
0x80 ,
0x8e ,
0x73 ,
0x7b ,
0x7b ,
0x77 ,
0x75 ,
0x8d ,
0x6e ,
0x79 ,
0x7a ,
0x7a ,
0x7b ,
0x75 ,
0x89 ,
0x7b ,
0x99 ,
0x8e ,
0x86 ,
0x8b ,
0x89 ,
0x7c ,
0x85 ,
0x81 ,
0x74 ,
0x72 ,
0x72 ,
0x7a ,
0x83 ,
0x80 ,
0x79 ,
0x81 ,
0x86 ,
0x7f ,
0x7b ,
0x79 ,
0x92 ,
0x77 ,
0x93 ,
0x85 ,
0x7e ,
0x8b ,
0x7c ,
0x91 ,
0x84 ,
0x8a ,
0x7a ,
0x80 ,
0x72 ,
0x80 ,
0x78 ,
0x7f ,
0x6e ,
0x7f ,
0x7b ,
0x7b ,
0x7b ,
0x7e ,
0x85 ,
0x7a ,
0x93 ,
0x82 ,
0x83 ,
0x81 ,
0x7a ,
0x8b ,
0x87 ,
0x7e ,
0x76 ,
0x7a ,
0x76 ,
0x76 ,
0x8a ,
0x69 ,
0x7b ,
0x82 ,
0x85 ,
0x83 ,
0x82 ,
0x7a ,
0x8a ,
0x77 ,
0x8e ,
0x74 ,
0x83 ,
0x83 ,
0x81 ,
0x8b ,
0x8c ,
0x7d ,
0x7c ,
0x81 ,
0x74 ,
0x7d ,
0x8b ,
0x6d ,
0x7b ,
0x7f ,
0x79 ,
0x7e ,
0x76 ,
0x8b ,
0x79 ,
0x8e ,
0x8f ,
0x80 ,
0x8c ,
0x86 ,
0x7b ,
0x8e ,
0x80 ,
0x73 ,
0x72 ,
0x78 ,
0x7b ,
0x77 ,
0x83 ,
0x6e ,
0x82 ,
0x82 ,
0x7e ,
0x7c ,
0x7d ,
0x80 ,
0x77 ,
0x8d ,
0x87 ,
0x7a ,
0x88 ,
0x85 ,
0x90 ,
0x7e ,
0x8b ,
0x74 ,
0x80 ,
0x7b ,
0x7d ,
0x77 ,
0x82 ,
0x6f ,
0x7e ,
0x7f ,
0x79 ,
0x7d ,
0x7a ,
0x8d ,
0x76 ,
0x99 ,
0x81 ,
0x87 ,
0x82 ,
0x8b ,
0x89 ,
0x85 ,
0x7e ,
0x72 ,
0x78 ,
0x71 ,
0x76 ,
0x7e ,
0x6b ,
0x78 ,
0x83 ,
0x86 ,
0x83 ,
0x78 ,
0x7b ,
0x8f ,
0x79 ,
0x92 ,
0x77 ,
0x7d ,
0x84 ,
0x7d ,
0x90 ,
0x81 ,
0x7e ,
0x7b ,
0x82 ,
0x73 ,
0x7e ,
0x75 ,
0x6f ,
0x6e ,
0x7f ,
0x7e ,
0x7e ,
0x7c ,
0x86 ,
0x88 ,
0x8b ,
0x92 ,
0x7f ,
0x83 ,
0x82 ,
0x7f ,
0x8f ,
0x87 ,
0x74 ,
0x7a ,
0x77 ,
0x75 ,
0x77 ,
0x8a ,
0x6c ,
0x7b};
static uint8_t znak=5;
void UART0_read2(void);
void UART0_Init(void);
uint8_t UART0_read(void);


void tpm1_init_pwm(void)
{
	SIM->SCGC6 |= SIM_SCGC6_TPM0_MASK;
	SIM->SOPT2 |= SIM_SOPT2_TPMSRC(1);
	SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK;
	PORTA->PCR[12] = PORT_PCR_MUX(2);
	TPM1->SC |= TPM_SC_PS(7);
	TPM1->SC |= TPM_SC_CMOD(2);
	TPM1->MOD = 100;
	TPM1->SC &= ~TPM_SC_CPWMS_MASK; 
	TPM1->CONTROLS[0].CnSC |= (TPM_CnSC_MSB_MASK | TPM_CnSC_ELSA_MASK);
	TPM1->CONTROLS[0].CnV = 10;

}


void TPM0_Init(void) {
			
  SIM->SCGC6 |= SIM_SCGC6_TPM0_MASK;		//wlaczenie maski 
	SIM->SOPT2 |= SIM_SOPT2_TPMSRC(1);    //wybor zrodla zegara

	SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK; //podlaczenie zegara do portu B
	PORTB->PCR[7] = PORT_PCR_MUX(2);		//wybor multipleksera	
	
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
	SIM->SCGC4 |= SIM_SCGC4_UART0_MASK;							
	SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK;							
	SIM->SOPT2 |= SIM_SOPT2_UART0SRC(MCGFLLCLK);		
	PORTB->PCR[1] = PORT_PCR_MUX(2);								
	PORTB->PCR[2] = PORT_PCR_MUX(2);								
	
	UART0->C2 &= ~(UART0_C2_TE_MASK | UART0_C2_RE_MASK );		
	UART0->BDH = 0;
	UART0->BDL =3;	//20 11	6
	UART0->C4 &= ~UART0_C4_OSR_MASK;
	UART0->C4 |= UART0_C4_OSR(15);	
	UART0->C5 |= UART0_C5_BOTHEDGE_MASK;	
	UART0->C2 |= UART0_C2_RIE_MASK;		
	UART0->C2 |= (UART0_C2_TE_MASK | UART0_C2_RE_MASK);		
}

uint8_t UART0_read(){

	
		if(!piosenka_FULL)
		{
			piosenka_FULL=1;
		}

	return temp;
}

void UART0_read2(){
	play=1;
	while(!(UART0->S1 & UART0_S1_TDRE_MASK));
	UART0->D = znak;
	for (uint32_t k=0; k<dlugosc; k++){	
			while(!(UART0->S1 & UART0_S1_RDRF_MASK)){}
			temp2=UART0->D;
			//temp2=UART0_read();
			
		if (k%4==3)
		{
			if (temp2=='a' || temp2=='b' || temp2=='c' || temp2=='d' || temp2 == 'e' || temp2=='f')
			{temp4=temp4*16+(temp2-87);}
			else{temp4=temp4*16+(temp2-0x30);
			
			}
				while(!(UART0->S1 & UART0_S1_TDRE_MASK));			UART0->D = temp4;
				piosenka5[temp3]=temp4;
				temp3++;	
//			play=1;

		//	TPM0->CONTROLS[2].CnV = temp4; 
			//				TPM0->CONTROLS[0].CnSC |= TPM_CnSC_CHF_MASK; 

			}
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
		//temp4=0;
									//	play=1;

	}
	play=0;
	temp3=0;
	temp4=0;
}




void TPM0_Play6(unsigned char z) {   
	probka=0;
	play=1;
}

void TPM0_Pause(void){
	play=0;
	pause=1;

}
void TPM0_IRQHandler(void) {
			
	if (play!=0) {
					
						if (upSampleCNT == 0){
					
							TPM0->CONTROLS[2].CnV = piosenka5[probka++];
								//probka++;
					
						}
						if (probka >=2999 ) {
					play = 0;         
						probka=0;
						}
	
	//					TPM0->CONTROLS[2].CnV = 0;
					//	}
						if (++upSampleCNT > (upsampling-1)) 
						{
						upSampleCNT = 0;
						}
					}
				TPM0->CONTROLS[0].CnSC |= TPM_CnSC_CHF_MASK; 
}



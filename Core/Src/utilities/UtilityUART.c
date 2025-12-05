///////////////////////////////////////////////////////////////////////////////
//ARQUIVO:    UtilityUART
//AUTOR:      Fábio Almeida
//CRIADO:     03/01/2024
//OBSERVAÇÕES:
//USART1 - GNSS
//USART2 - NC
//USART3 - LoRa
//USART4 - RS485
////////////////////////////////////////////////////////////////////////////////
#include "main.h"
#include "global.h"
/*==============================================================================
CONSTANTES DO ARQUIVO
==============================================================================*/
/*==============================================================================
SPRINTF RS485
==============================================================================*/
void sprintFRS485(uint8_t valor) {

	switch(valor) {
		case 0: strcat(bufferEnviaRS485, "0"); break;
		case 1: strcat(bufferEnviaRS485, "1"); break;
		case 2: strcat(bufferEnviaRS485, "2"); break;
		case 3: strcat(bufferEnviaRS485, "3"); break;
		case 4: strcat(bufferEnviaRS485, "4"); break;
		case 5: strcat(bufferEnviaRS485, "5"); break;
		case 6: strcat(bufferEnviaRS485, "6"); break;
		case 7: strcat(bufferEnviaRS485, "7"); break;
		case 8: strcat(bufferEnviaRS485, "8"); break;
		case 9: strcat(bufferEnviaRS485, "9"); break;

		case 0x0A: strcat(bufferEnviaRS485, "A"); break;
		case 0x0B: strcat(bufferEnviaRS485, "B"); break;
		case 0x0C: strcat(bufferEnviaRS485, "C"); break;
		case 0x0D: strcat(bufferEnviaRS485, "D"); break;
		case 0x0E: strcat(bufferEnviaRS485, "E"); break;
		case 0x0F: strcat(bufferEnviaRS485, "F"); break;
	}
}
/*==============================================================================
APAGA BUFFER LORA
==============================================================================*/
void apagaLoraBuffer() {
	contadorLoraBuffer = 0;
	for(uint8_t i = 0; i < TAMANHO_BUFFER_LORA; i ++) {
		bufferLora[i] = 0;
	}
}
/*==============================================================================
APAGA BUFFER RS485
==============================================================================*/
void apagaRS485Buffer() {
	contadorRS485Buffer = 0;
	for(uint8_t i = 0; i < TAMANHO_BUFFER_RS485; i ++) {
		bufferRS485[i] = 0;
	}
}
/*==============================================================================
FIM DO ARQUIVO
==============================================================================*/

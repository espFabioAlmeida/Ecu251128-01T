///////////////////////////////////////////////////////////////////////////////
//ARQUIVO:    UtilityLoRa
//AUTOR:      Fábio Almeida
//CRIADO:     15/08/2024
//OBSERVAÇÕES:
////////////////////////////////////////////////////////////////////////////////
#include "main.h"
#include "global.h"
#include "string.h"
/*==============================================================================
CONSTANTES DO ARQUIVO
==============================================================================*/
/*==============================================================================
AGUARDA Lora
==============================================================================*/
void aguardaLora(uint16_t tempo) {
	contadorTimeoutLora = tempo;
	while(contadorTimeoutLora) {
		HAL_UART_Receive_IT(&huart3, &loraDataIn, 1);
	}
	//HAL_UART_Transmit(&huart4, &bufferLoRa, strlen(bufferLoRa), 100); //debug
	//apagaLoraBuffer();
}
/*=============================================================================
APAGA BUFFER ENVIO GPRS
==============================================================================*/
void apagabufferEnvioLora() {
	for(uint8_t i = 0; i < TAMANHO_BUFFER_LORA; i ++) {
		bufferEnvioLora[i] = 0x00;
	}
}
/*=============================================================================
SPRINTF LORA
==============================================================================*/
void sprintfLora(uint32_t valor, uint8_t qntdDig) {
	//Enviar 0 em qntdDig para ignorar "zeros" a esquerda
	char dataChar[9];
	sprintf(dataChar, "%u", valor);

	switch(qntdDig) {
		case 9:
			if(valor < 100000000) {
				strcat(bufferEnvioLora, "0");
			}
		case 8:
			if(valor < 10000000) {
				strcat(bufferEnvioLora, "0");
			}
		case 7:
			if(valor < 1000000) {
				strcat(bufferEnvioLora, "0");
			}
		case 6:
			if(valor < 100000) {
				strcat(bufferEnvioLora, "0");
			}
		case 5:
			if(valor < 10000) {
				strcat(bufferEnvioLora, "0");
			}
		case 4:
			if(valor < 1000) {
				strcat(bufferEnvioLora, "0");
			}
		case 3:
			if(valor < 100) {
				strcat(bufferEnvioLora, "0");
			}
		case 2:
			if(valor < 10) {
				strcat(bufferEnvioLora, "0");
			}
	}

	strcat(bufferEnvioLora, dataChar);
}
/*==============================================================================
CONFIGURA LoRa
==============================================================================*/
uint8_t configuraLora() {
	on(LORA_M0_GPIO_Port, LORA_M0_Pin);
	on(LORA_M1_GPIO_Port, LORA_M1_Pin);
	HAL_Delay(100);

	if(debounceInverso(LORA_AUX_GPIO_Port, LORA_AUX_Pin)) {
		uint8_t sucesso = false;
		uint8_t ponteiro = 0;
		apagabufferEnvioLora();
		bufferEnvioLora[0] = 0xC0; //Salvar
		bufferEnvioLora[1] = make8(enderecoLoraTransmissor, 1);
		bufferEnvioLora[2] = make8(enderecoLoraTransmissor, 0);
		bufferEnvioLora[3] = 0x1A; //8N1, 9600bps, 2.4k
		bufferEnvioLora[4] = canalLora;
		bufferEnvioLora[5] = 0xC4; //opções
		HAL_UART_Transmit(&huart3, &bufferEnvioLora, 6, 100);
		aguardaLora(20);

		for(uint8_t i = 0; i < TAMANHO_BUFFER_LORA; i ++) {
			if(bufferLora[i] == 0xC0) {
				i = TAMANHO_BUFFER_LORA;
			}
			else {
				ponteiro ++;
			}
		}

		sucesso = true;
		for(uint8_t i = 0; i < 6; i ++) {
			if(bufferLora[i + ponteiro] != bufferEnvioLora[i]) {
				sucesso = false;
			}
		}

		apagaLoraBuffer();
		off(LORA_M0_GPIO_Port, LORA_M0_Pin);
		off(LORA_M1_GPIO_Port, LORA_M1_Pin);
		HAL_Delay(100);
		return sucesso;
	}

	off(LORA_M0_GPIO_Port, LORA_M0_Pin);
	off(LORA_M1_GPIO_Port, LORA_M1_Pin);
	HAL_Delay(100);

	return false;
}
/*==============================================================================
FIM DO ARQUIVO
==============================================================================*/

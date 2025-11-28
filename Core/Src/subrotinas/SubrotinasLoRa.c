///////////////////////////////////////////////////////////////////////////////
//ARQUIVO:    SubrotinasLoRa
//AUTOR:      Fábio Almeida
//CRIADO:     03/01/2024
//OBSERVAÇÕES:
////////////////////////////////////////////////////////////////////////////////
#include "main.h"
#include "global.h"
#include "string.h"
/*==============================================================================
CONSTANTES DO ARQUIVO
==============================================================================*/
/*==============================================================================
PROTOCOLO LORA
==============================================================================*/
void protocoloLora() {

	if(flagPacoteLora) {
		signed int index = indexOf(bufferLora, "$,01,");

		if(index >= 0) {
			uint8_t comando = charToByte(bufferLora[index + 6]);
			flagLedCOM = true; //por enquanto somente feedback
		}

		flagPacoteLora = false;
		apagaLoraBuffer();
	}
}
/*==============================================================================
ENVIA PACOTE LORA
==============================================================================*/
void enviaPacoteLora() {
	char headerEnvioLora[8];
	memset(headerEnvioLora, 0x00, 8);

	if(!flagEnviaPacoteLora) {
		return;
	}

	apagabufferEnvioLora();

	headerEnvioLora[0] = make8(enderecoLoraReceptor, 1);
	headerEnvioLora[1] = make8(enderecoLoraReceptor, 0);
	headerEnvioLora[2] = canalLora;

	strcat(bufferEnvioLora, "$,01,");
	sprintfLora(flagEntradaAcionamento, 1);
	strcat(bufferEnvioLora, ",\r\n");

	HAL_UART_Transmit(&huart3, &headerEnvioLora, 3, 300);
	HAL_UART_Transmit(&huart3, &bufferEnvioLora, strlen(bufferEnvioLora), 300);

	flagEnviaPacoteLora = false;
}
/*==============================================================================
FIM DO ARQUIVO
==============================================================================*/

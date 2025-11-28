///////////////////////////////////////////////////////////////////////////////
//ARQUIVO:    SubrotinasRS485
//AUTOR:      Fábio Almeida
//CRIADO:     03/01/2024
//OBSERVAÇÕES:
////////////////////////////////////////////////////////////////////////////////
#include "main.h"
#include "global.h"
/*==============================================================================
CONSTANTES DO ARQUIVO
==============================================================================*/
/*==============================================================================
CONSTANTES DO ARQUIVO
==============================================================================*/
void respostaDadosRadio() {
	memset(bufferEnviaRS485, 0x00, 32);

	uint8_t nibbleHH = byteToNibble(make8(enderecoLoraTransmissor, 1), 1);
	uint8_t nibbleHL = byteToNibble(make8(enderecoLoraTransmissor, 1), 0);
	uint8_t nibbleLH = byteToNibble(make8(enderecoLoraTransmissor, 0), 1);
	uint8_t nibbleLL = byteToNibble(make8(enderecoLoraTransmissor, 0), 0);

	sprintFRS485(nibbleHH);
	sprintFRS485(nibbleHL);
	sprintFRS485(nibbleLH);
	sprintFRS485(nibbleLL);

	HAL_UART_Transmit(&huart4, "Endereco Transmissor: ", 22, 200);
	HAL_UART_Transmit(&huart4, &bufferEnviaRS485, strlen(bufferEnviaRS485), 200);
	HAL_UART_Transmit(&huart4, "\r\nEndereco Receptor: ", 21, 200);

	memset(bufferEnviaRS485, 0x00, 32);
	nibbleHH = byteToNibble(make8(enderecoLoraReceptor, 1), 1);
	nibbleHL = byteToNibble(make8(enderecoLoraReceptor, 1), 0);
	nibbleLH = byteToNibble(make8(enderecoLoraReceptor, 0), 1);
	nibbleLL = byteToNibble(make8(enderecoLoraReceptor, 0), 0);

	sprintFRS485(nibbleHH);
	sprintFRS485(nibbleHL);
	sprintFRS485(nibbleLH);
	sprintFRS485(nibbleLL);

	HAL_UART_Transmit(&huart4, &bufferEnviaRS485, strlen(bufferEnviaRS485), 200);
	HAL_UART_Transmit(&huart4, "\r\nCanal: ", 9, 200);

	memset(bufferEnviaRS485, 0x00, 32);
	sprintFRS485(byteToNibble(canalLora, 1));
	sprintFRS485(byteToNibble(canalLora, 0));

	HAL_UART_Transmit(&huart4, &bufferEnviaRS485, strlen(bufferEnviaRS485), 200);
	HAL_UART_Transmit(&huart4, "\r\n", 2, 200);
}
/*==============================================================================
COMANDO CONFIGURA LORA
==============================================================================*/
void recebeConfiguracaoLora(uint8_t index) {
	enderecoLoraTransmissor = make16(nibblesToByte(charToByte(bufferRS485[index + 5]), charToByte(bufferRS485[index + 6])),
			nibblesToByte(charToByte(bufferRS485[index + 7]), 0x04));

	enderecoLoraReceptor = enderecoLoraTransmissor + 1;

	canalLora = nibblesToByte(charToByte(bufferRS485[index + 9]), charToByte(bufferRS485[index + 10]));

	if(configuraLora()) {
		HAL_UART_Transmit(&huart4, "Sucesso ao configurar\r\n", 23, 200);
		respostaDadosRadio();
		salvaConfiguracoesLora();
		return;
	}

	HAL_UART_Transmit(&huart4, "Erro ao configurar\r\n", 20, 200);
}
/*==============================================================================
PROTOCOLO RS485
==============================================================================*/
void protocoloRS485() {

	if(flagPacoteRS485) {
		signed int index = indexOf(bufferRS485, "$,");

		if(index >= 0) {
			uint8_t comando = charToByte(bufferRS485[index + 2]);
			comando *= 10;
			comando += charToByte(bufferRS485[index + 3]);

			switch(comando) {
				case 1: recebeConfiguracaoLora(index); break;
				case 2: respostaDadosRadio(); break;
			}

		}

		flagPacoteRS485 = false;
		apagaRS485Buffer();
	}
}
/*==============================================================================
FIM DO ARQUIVO
==============================================================================*/

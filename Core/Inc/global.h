/*
 * global.h
 *
 *  Created on: Aug 23, 2023
 *      Author: User
 */

#ifndef INC_GLOBAL_H_
#define INC_GLOBAL_H_

#define VERSAO_FIRMWARE 1

enum BOOL {
	false,
	true
};

#define TAMANHO_BUFFER_RS485 	32
#define TAMANHO_BUFFER_LORA 32

extern UART_HandleTypeDef huart3;
extern UART_HandleTypeDef huart4;

extern uint8_t
	flagEntradaAcionamento,

	flagPacoteRs485,
	flagPacoteLora;

extern uint8_t
	contadorRS485Buffer,
	contadorLoraBuffer,
	canalLora;

extern uint16_t
	enderecoLoraTransmissor,
	enderecoLoraReceptor,
	contadorTimeoutLora;

extern char
	loraDataIn,
	rs485DataIn;

extern char
	bufferRS485[TAMANHO_BUFFER_RS485],
	bufferLora[TAMANHO_BUFFER_LORA],
	bufferEnvioLora[TAMANHO_BUFFER_LORA];
#endif /* INC_GLOBAL_H_ */

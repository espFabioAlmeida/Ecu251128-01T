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

#define TAMANHO_BUFFER_485 	32
#define TAMANHO_BUFFER_LORA 32

extern uint8_t
	flagEntradaAcionamento,

	flagPacoteRs485,
	flagPacoteLora;

extern uint8_t
	contadorRS485Buffer,
	contadorLoraBuffer;

extern char
	loraDataIn,
	rs485DataIn;

extern char
	buffer485[TAMANHO_BUFFER_485],
	bufferLora[TAMANHO_BUFFER_LORA];
#endif /* INC_GLOBAL_H_ */

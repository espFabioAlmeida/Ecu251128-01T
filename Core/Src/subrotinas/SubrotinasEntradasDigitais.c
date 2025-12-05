///////////////////////////////////////////////////////////////////////////////
//ARQUIVO:    SubrotinasEntradasDigitais
//AUTOR:      Fábio Almeida
//CIRADO:     25/04/2024
//OBSERVAÇÕES:
////////////////////////////////////////////////////////////////////////////////
#include "main.h"
#include "global.h"
/*=============================================================================
LEITURA ENTRADAS DIGITAIS
==============================================================================*/
void entradasDigitais() {
	if(flagEntradaAcionamento) {
		if(debounceInverso(IN1_GPIO_Port, IN1_Pin)) {
			flagEntradaAcionamento = false;
		}
	}
	else {
		if(debounce(IN1_GPIO_Port, IN1_Pin)) {
			flagEntradaAcionamento = true;
		}
	}
}
/*=============================================================================
FIM DO ARQUIVO
==============================================================================*/

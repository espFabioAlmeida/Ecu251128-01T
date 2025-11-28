# Ecu251128-01T
Projeto Automasensor

# Escopo
Projeto utiliza a placa ECU-GPS V1. <br>
Envia para a placa receptora o estado da entrada digital via rádio. <br>
Para configurar o rádio se utiliza a rs485. <br>

# Protocolo Rádio
-$,01,ESTADO,\r\n <br>
Estado: 0= desligado e 1= ligado. <br>
A placa receptora irá ecoar o que recebeu como forma de feed back <br>

# Protocolo RS485 - Configuração
-$,01,123,0A,\r\n <br>
123: É o endereço, o software irá colocar o número 4 no final. 123 fica 1234, o endereço do receptor será o mesmo, porém finalizado em 5 (1235). <br>
0A: É o canal, que deve ser o mesmo do receptor. <br>
A placa irá responder se conseguiu escrever o endereço e o canal no rádio, informando qual o enedereço escrito. <br>

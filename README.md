Controle de Matriz de LEDs com Debounce em Push Buttons
Este projeto demonstra como controlar uma matriz de LEDs utilizando botões com debounce implementado através de interrupções. O código incrementa e decrementa um contador para exibir números na matriz de LEDs.

Funcionalidades
Manipulação de Interrupções: Utiliza interrupções GPIO para lidar com os pressionamentos de botões.

Lógica de Debounce: Implementa lógica de debounce para garantir pressionamentos de botões estáveis.

Controle da Matriz de LEDs: Configura e controla uma matriz de LEDs para exibir números de 0 a 9.

Configuração de Cor: Permite a configuração da cor RGB dos LEDs.

Componentes
Botões: Dois botões (BOTTON_inc e BOTTON_dec) para incrementar e decrementar o número exibido.

Matriz de LEDs: Uma matriz de LEDs RGB para exibir os números.

LED Vermelho: Um único LED vermelho para fornecer feedback visual piscando.

Estrutura do Código
Inicialização: Configura a comunicação serial, os pinos GPIO e as interrupções.

Manipulador de Interrupções: Trata os eventos de pressionamento de botões e gerencia a lógica de debounce.

Funções da Matriz de LEDs: Configura a matriz de LEDs e define a cor dos LEDs.

Explicação do Código
O código inicializa o sistema, configura os pinos GPIO e configura as interrupções para os botões. O manipulador de interrupções garante que a lógica de debounce seja aplicada para evitar múltiplas detecções de um único pressionamento de botão. A matriz de LEDs é controlada através de funções dedicadas que definem a cor e o brilho dos LEDs individuais.

O loop principal verifica continuamente o valor do contador e atualiza a matriz de LEDs para exibir o número correspondente. O LED vermelho fornece feedback visual piscando.

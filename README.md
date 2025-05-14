# Sensor de Luz, Temperatura e Umidade

Este projeto utiliza sensores de luz (LDR), temperatura (TMP) e umidade (DHT11) integrados com Arduino UNO para monitorar as condições ambientais e controlar LEDs, um buzzer e um display LCD, com base em diferentes condições.

## Autores

- Erick Jooji (RM: 564482)
- Luiz Dalboni (RM: 564189)
- Matheus Tozarelli (RM: 563490)
- Rafael Lorenzini (RM: 563643)

## Ferramentas e Tecnologias

- **Linguagem de programação:** C++
- **Placa:** Arduino UNO
- **Simulação:** [Tinkercad - Projeto SensorLuz](https://www.tinkercad.com/things/1FLMw0RI0Qp/editel?sharecode=3U-bvGk7_IB4qhG56tbSyutXl7edE_MXuUWwf2XKvjU)

## Componentes Utilizados

- **1** Resistor de 1kΩ (para o LDR)
- **7** Resistores de 220Ω (para os LEDs)
- **24** Jumpers
- **7** LEDs (Vermelho, Amarelo, Verde)
- **1** Buzzer
- **1** LDR (Sensor de Luz)
- **1** TMP (Sensor de Temperatura)
- **1** DHT11 (Sensor de Umidade)
- **1** Display LCD com módulo I2C

## Como Funciona

O projeto utiliza sensores de luz, temperatura e umidade para avaliar as condições ambientais e exibir essas informações em um display LCD. Além disso, LEDs e um buzzer indicam o estado atual de cada parâmetro monitorado.

### Exemplo de Funcionamento

#### Luminosidade
- **IDEAL (0% - 40%)**: O LED verde acende.
- **ALERTA (40% - 60%)**: O LED amarelo acende, e o buzzer toca intermitentemente.
- **PROBLEMA (> 60%)**: O LED vermelho acende, e o buzzer emite um sinal contínuo.

#### Temperatura
- **IDEAL (10°C - 15°C)**: O LED verde acende.
- **BAIXA (< 10°C)**: O LED vermelho acende, e o buzzer emite um sinal contínuo.
- **ALTA (> 15°C)**: O LED vermelho acende, e o buzzer emite um sinal contínuo.

#### Umidade
- **IDEAL (50% - 70%)**: O LED verde acende.
- **BAIXA (< 50%)**: O LED vermelho acende, e o buzzer emite um sinal contínuo.
- **ALTA (> 70%)**: O LED vermelho acende, e o buzzer emite um sinal contínuo.

---

## Código Explicado

### Estrutura do Código

1. **Inicialização dos Sensores e Display**:
   - Sensores de luz, temperatura e umidade são lidos nas entradas analógicas.
   - O display LCD com módulo I2C é configurado para exibir as informações ambientais.

2. **Uso de Buffers para Médias**:
   - Buffers são utilizados para calcular a média dos valores lidos, garantindo maior estabilidade nas medições.

3. **Controle dos LEDs e Buzzer**:
   - LEDs e o buzzer indicam as condições de **IDEAL**, **ALERTA** ou **PROBLEMA** para cada parâmetro monitorado.

4. **Função `processaLUZ`**:
   - Determina o estado da luminosidade com base na média calculada.
   - Controla os LEDs e o buzzer para indicar o estado.

5. **Função `processaTEMPERATURA`**:
   - Determina o estado da temperatura com base na média calculada.
   - Controla os LEDs e o buzzer para indicar o estado.

6. **Função `processaUMIDADE`**:
   - Determina o estado da umidade com base na média calculada.
   - Controla os LEDs e o buzzer para indicar o estado.

7. **Atualização do Display LCD**:
   - Exibe no LCD as condições ambientais atuais para a luminosidade, temperatura e umidade.

8. **Cálculo de Médias de Valores**:
   - **Buffers de Leitura**: Cada sensor (luz, temperatura, umidade) utiliza um buffer circular de 5 leituras para calcular a média.
   - **Cálculo da Média**:
     ```cpp
     float calculaMedia(int buffer[], int tamanho) {
       int soma = 0;
       for (int i = 0; i < tamanho; i++) {
         soma += buffer[i];
       }
       return soma / (float)tamanho;
     }
     ```
     - Essa abordagem reduz flutuações nas leituras, garantindo maior confiabilidade nos valores monitorados.

9. **Atualização de Valores no Buffer**:
   - **Lógica**:
     As novas leituras são inseridas no buffer, substituindo as mais antigas de forma circular:
     ```cpp
     void atualizaMedias(int luz, int temperatura, int umidade, float &luzMedia, float &temperaturaMedia, float &umidadeMedia) {
       luzBuffer[luzIndex] = luz; // Atualiza buffer de luz
       luzIndex = (luzIndex + 1) % 5; // Incrementa o índice de forma circular

       temperaturaBuffer[temperaturaIndex] = temperatura; // Atualiza buffer de temperatura
       temperaturaIndex = (temperaturaIndex + 1) % 5;

       umidadeBuffer[umidadeIndex] = umidade; // Atualiza buffer de umidade
       umidadeIndex = (umidadeIndex + 1) % 5;

       // Calcula as médias
       luzMedia = calculaMedia(luzBuffer, 5);
       temperaturaMedia = calculaMedia(temperaturaBuffer, 5);
       umidadeMedia = calculaMedia(umidadeBuffer, 5);
     }
     ```
---

## Como Executar

1. Monte o circuito seguindo o esquema no [Tinkercad](https://www.tinkercad.com/things/1FLMw0RI0Qp/editel?sharecode=3U-bvGk7_IB4qhG56tbSyutXl7edE_MXuUWwf2XKvjU).
2. Faça o upload do código para o Arduino UNO usando a IDE Arduino.
3. Conecte o circuito ao computador ou a uma fonte de alimentação.
4. Observe o comportamento dos LEDs, o buzzer e o display LCD com base nas condições ambientais.

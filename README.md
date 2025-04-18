# SensorLuz

Este projeto utiliza um sensor de luz (LDR) integrado com Arduino UNO para controlar LEDs e um buzzer com base em diferentes condições de luminosidade.

## Autores

- Erick Jooji
- Guilherme Godoy
- Luiz Dalboni
- Matheus Tozarelli
- Rafael Lorenzini

## Ferramentas e Tecnologias

- **Linguagem de programação:** C++
- **Placa:** Arduino UNO
- **Simulação:** [Tinkercad - Projeto SensorLuz](https://www.tinkercad.com/things/c1h5FtxbSvR/editel?returnTo=%2Fdashboard)

## Componentes Utilizados

- **1** Resistor de 10kΩ
- **1** Resistor de 1kΩ
- **3** Resistores de 220Ω
- **11** Jumpers
- **3** LEDs (Vermelho, Amarelo, Verde)
- **1** Buzzer
- **1** LDR (Sensor de Luz)

## Como Funciona

O projeto utiliza um LDR (sensor de luz) para medir a intensidade da luz ambiente. Com base nos valores medidos, o Arduino controla LEDs e um buzzer para indicar diferentes condições de luminosidade. 

### Exemplo de Funcionamento:
- **Alta luminosidade:** O LED verde acende.
- **Média luminosidade:** O LED amarelo acende.
- **Baixa luminosidade:** O LED vermelho acende e o buzzer é ativado.

## Como Executar

1. Monte o circuito seguindo o esquema fornecido no [Tinkercad](https://www.tinkercad.com/things/c1h5FtxbSvR/editel?returnTo=%2Fdashboard).
2. Faça o upload do código para o Arduino UNO usando a IDE Arduino.
3. Conecte o circuito ao computador ou a uma fonte de alimentação e observe o comportamento dos LEDs e do buzzer com base na luminosidade.

## Contribuição

Contribuições são bem-vindas! Se você tiver sugestões ou melhorias, sinta-se à vontade para abrir uma issue ou um pull request.

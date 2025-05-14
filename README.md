# Sensor de Luz

Este projeto utiliza um sensor de luz (LDR) integrado com Arduino UNO para controlar LEDs e um buzzer com base em diferentes condições de luminosidade, temperatura e umidade.

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

## Como Funciona

O projeto utiliza sensores de luz, temperatura e umidade para avaliar o estado das condições do ambiente onde estão as uvas. Por meio de LEDs, um buzzer e um display LCD, é possível monitorar e garantir a qualidade das uvas.

### Exemplo de Funcionamento

#### Luminosidade
- **IDEAL**: O LED verde acende.
- **ALERTA**: O LED amarelo acende e o buzzer toca por 3 segundos, repetindo após mais 3 segundos.
- **PROBLEMAS**: O LED vermelho acende e o buzzer emite um sinal contínuo.

#### Temperatura
- **IDEAL**: O LED verde acende.
- **PROBLEMAS**: O LED vermelho acende e o buzzer emite um sinal contínuo.

#### Umidade
- **IDEAL**: O LED verde acende.
- **PROBLEMAS**: O LED vermelho acende e o buzzer emite um sinal contínuo.

## Código Explicado

### Estrutura do Código

1. **Configuração de LEDs e Buzzer**:
   - LEDs (vermelho, amarelo e verde) e o buzzer são atribuídos a pinos digitais específicos.
   - Funções auxiliares controlam os estados dos LEDs e do buzzer.

2. **Função `acendeSomente`**:
   - Ativa apenas o LED correspondente à condição atual e desliga os demais.

3. **Lógica Principal (`void loop`)**:
   - Lê os valores do LDR, temperatura e umidade.
   - Determina as condições **IDEAL**, **ALERTA** ou **PROBLEMA** usando estruturas `if-else`.

### Trechos de Código

#### Configuração Inicial (`setup`)
```cpp
void setup() {
  Serial.begin(9600);  // Inicializa o monitor serial para debug
  pinMode(buzina, OUTPUT);  // Define o buzzer como saída
  pinMode(vermelho, OUTPUT);  // Define o LED vermelho como saída
  pinMode(amarelo, OUTPUT);  // Define o LED amarelo como saída
  pinMode(verde, OUTPUT);  // Define o LED verde como saída
}
```

#### Função Auxiliar: `acendeSomente`
```cpp
void acendeSomente(int led) {
  digitalWrite(vermelho, led == 10 ? HIGH : LOW);
  digitalWrite(amarelo,  led == 9 ? HIGH : LOW);
  digitalWrite(verde,    led == 8 ? HIGH : LOW); 
}
```
Essa função ativa apenas o LED indicado e garante que os outros dois LEDs estejam desligados.

#### Lógica Principal (`void loop`)
1. **Leitura da Luminosidade**
   ```cpp
   int luz = analogRead(A0);  // Lê o valor do LDR
   int ideal_min = 900;
   int ideal_max = 950;
   int margem_erroMIN = 100;
   int margem_erroMAX = 970;
   unsigned long agora = millis();  // Tempo atual do loop
   ```
   - Determina o estado com base nos limites definidos.

2. **Condição IDEAL**
   ```cpp
   if (luz >= ideal_min && luz <= ideal_max) {
       acendeSomente(verde);  // Liga o LED verde
       noTone(buzina);  // Desliga o buzzer
       naoPodetocar = false;  // Libera o alerta para tocar no futuro
   }
   ```

3. **Condição ALERTA**
   ```cpp
   else if ((luz > ideal_max && luz < margem_erroMAX) || (luz < ideal_min && luz > margem_erroMIN)) {
       acendeSomente(amarelo);  // Liga o LED amarelo

       if (!naoPodetocar) {
           tone(buzina, 200);  // Toca o buzzer a 200 Hz
           tempoAnterior = agora;  // Atualiza o temporizador
           buzinaLigada = true;
           naoPodetocar = true;  // Impede reativação imediata do alerta
       }

       if (agora - tempoAnterior >= 3000) {
           tempoAnterior = agora;
           if (buzinaLigada) {
               noTone(buzina);  // Desliga o buzzer
               buzinaLigada = false;
           } else {
               tone(buzina, 200);  // Liga o buzzer
               buzinaLigada = true;
           }
       }
   }
   ```

4. **Condição PROBLEMA**
   ```cpp
   else {
       acendeSomente(vermelho);  // Liga o LED vermelho
       naoPodetocar = false;  // Reseta a variável de controle
       noTone(buzina);  // Desativa qualquer som do buzzer
   }
   ```

## Como Executar

1. Monte o circuito seguindo o esquema no [Tinkercad](https://www.tinkercad.com/things/1FLMw0RI0Qp/editel?sharecode=3U-bvGk7_IB4qhG56tbSyutXl7edE_MXuUWwf2XKvjU).
2. Faça o upload do código para o Arduino UNO usando a IDE Arduino.
3. Conecte o circuito ao computador ou a uma fonte de alimentação.
4. Observe o comportamento dos LEDs e do buzzer com base nas condições do ambiente.

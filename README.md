# Sensor de Luz

Este projeto utiliza um sensor de luz (LDR) integrado com Arduino UNO para controlar LEDs e um buzzer com base em diferentes condições de luminosidade.

## Autores

- Erick Jooji (RM: 564482)
- Luiz Dalboni (RM: 564189)
- Matheus Tozarelli (RM: 563490)
- Rafael Lorenzini (RM: 563643)

## Ferramentas e Tecnologias

- **Linguagem de programação:** C++
- **Placa:** Arduino UNO
- **Simulação:** [Tinkercad - Projeto SensorLuz]([https://www.tinkercad.com/things/c1h5FtxbSvR/editel?returnTo=%2Fdashboard&classId=61ce3daf-e9a6-49bd-91bb-a29ab66ae1d3&assignmentId=8ca11dbd-a233-45ac-8140-88877fc2df04&submissionId=6a8c72ea-fb7b-863b-47da-6bf3e5e043a8&sharecode=ZvjRef9xMrJKNGLz6X485Ed7jBBOPLuEBe1Sdcigd8c](https://www.tinkercad.com/things/1FLMw0RI0Qp/editel?sharecode=3U-bvGk7_IB4qhG56tbSyutXl7edE_MXuUWwf2XKvjU))


## Componentes Utilizados

- **1** Resistor de 1kΩ (para o LDR)
- **7** Resistores de 220Ω (para os LEDs)
- **24** Jumpers
- **7** LEDs (Vermelho, Amarelo, Verde)
- **1** Buzzer
- **1** LDR (Sensor de Luz)
- **1** TMP (Sensor de Temperatura)
- **1** DHT11 (Sensor de umidade)

## Como Funciona

O projeto utiliza receptores de iluminação, temperatura e umidade, para avaliar o estado das uvas. Que através de LEDS, um buzzer e um display de LCD, podem verificar sempre manter o controle<br>
da situação e garantir a qualidade da uva.

### Exemplo de Funcionamento:

- **Luminosidade IDEAL**: O LED verde acende.
- **Luminosidade em ALERTA**: O LED amarelo acende e o buzzer toca por 3 segundos, voltando a tocar novamente após mais 3 segundos.
- **Luminosidade com PROBLEMAS**: O LED vermelho acende e o buzzer emite um sinal contínuo.

- **Temperatura IDEAL**: O LED verde acende.
- **Temperatura com PROBLEMAS**: O LED vermelho acende e o buzzer emite um sinal contínuo.

- **umidade IDEAL**: O LED verde acende.
- **umidade com PROBLEMAS**: O LED vermelho acende e o buzzer emite um sinal contínuo.

---

## Código Explicado

### Estrutura do Código

1. **Configuração de LEDs e Buzzer**:
   - Os LEDs (vermelho, amarelo e verde) e o buzzer estão atribuídos a pinos digitais específicos.
   - Funções auxiliares controlam o estado dos LEDs e do buzzer.

2. **Função `acendeSomente`**:
   - Simplifica o controle dos LEDs, ativando apenas o LED correspondente à condição atual e desligando os outros dois.

3. **Lógica Principal (`void loop`)**:
   - O programa lê o valor do LDR para determinar a luminosidade ambiente.
   - Com base no valor lido, as condições **IDEAL**, **ALERTA** ou **PROBLEMA** são determinadas por meio de estruturas `if-else`.

---

### Detalhamento por Trechos de Código

#### **Configuração Inicial (`setup`)**
```cpp
void setup() {
  Serial.begin(9600);  // Inicializa o monitor serial para debug
  pinMode(buzina, OUTPUT);  // Define o buzzer como saída
  pinMode(vermelho, OUTPUT);  // Define o LED vermelho como saída
  pinMode(amarelo, OUTPUT);  // Define o LED amarelo como saída
  pinMode(verde, OUTPUT);  // Define o LED verde como saída
}
```

#### **Função Auxiliar: `acendeSomente`**
```cpp
void acendeSomente(int led) {
  digitalWrite(vermelho, led == 10 ? HIGH : LOW);
  digitalWrite(amarelo,  led == 9 ? HIGH : LOW);
  digitalWrite(verde,    led == 8 ? HIGH : LOW); 
}
```
Essa função ativa apenas o LED indicado e garante que os outros dois LEDs estejam desligados.

---

#### **Lógica Principal (`void loop`)**

1. **Leitura da Luminosidade**
   ```cpp
   int luz = analogRead(A0);  // Lê o valor do LDR
   int ideal_min = 900;
   int ideal_max = 950;
   int margem_erroMIN = 100;
   int margem_erroMAX = 970;
   unsigned long agora = millis();  // Tempo atual do loop
   ```
   - Os valores de luminosidade são comparados com os limites definidos para determinar o estado atual.

2. **Condição IDEAL**
   ```cpp
   if (luz >= ideal_min && luz <= ideal_max) {
       acendeSomente(verde);  // Liga o LED verde
       noTone(buzina);  // Desliga o buzzer
       naoPodetocar = false;  // Libera o estado para tocar o alerta no futuro
   }
   ```
   - Indica que a luminosidade está no intervalo ideal. Apenas o LED verde é ligado.

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
       naoPodetocar = false;  // Reseta a variável de controle do alerta
       noTone(buzina);  // Desativa qualquer som do buzzer
       
       // Caso queira habilitar o som para PROBLEMA, descomente o trecho abaixo:
       /*
       if (agora - ultimoBeep >= 1000) {
           ultimoBeep = agora;
           if (beepAtivo) {
               noTone(buzina);  // Desliga o buzzer
           } else {
               tone(buzina, 1000);  // Liga o buzzer a 1000 Hz
           }
           beepAtivo = !beepAtivo;  // Alterna o estado do beep
       }
       */
   }
   ```

---

## Como Executar

1. Monte o circuito seguindo o esquema fornecido no [Tinkercad]([https://www.tinkercad.com/things/c1h5FtxbSvR/editel?returnTo=%2Fdashboard&classId=61ce3daf-e9a6-49bd-91bb-a29ab66ae1d3&assignmentId=8ca11dbd-a233-45ac-8140-88877fc2df04&submissionId=6a8c72ea-fb7b-863b-47da-6bf3e5e043a8&sharecode=ZvjRef9xMrJKNGLz6X485Ed7jBBOPLuEBe1Sdcigd8c](https://www.tinkercad.com/things/1FLMw0RI0Qp/editel?sharecode=3U-bvGk7_IB4qhG56tbSyutXl7edE_MXuUWwf2XKvjU)).
2. Faça o upload do código para o Arduino UNO usando a IDE Arduino.
3. Conecte o circuito ao computador ou a uma fonte de alimentação.
4. Observe o comportamento dos LEDs e do buzzer com base na intensidade de luz.



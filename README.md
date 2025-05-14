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
- **IDEAL (11°C - 15°C)**: O LED verde acende.
- **BAIXA (< 11°C)**: O LED vermelho acende, e o buzzer emite um sinal contínuo.
- **ALTA (> 15°C)**: O LED vermelho acende, e o buzzer emite um sinal contínuo.

#### Umidade
- **IDEAL (60% - 80%)**: O LED verde acende.
- **BAIXA (< 60%)**: O LED vermelho acende, e o buzzer emite um sinal contínuo.
- **ALTA (> 80%)**: O LED vermelho acende, e o buzzer emite um sinal contínuo.

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

---

### Detalhamento por Trechos de Código

#### Configuração Inicial (`setup`)
```cpp
void setup() {
  Serial.begin(9600);

  lcd.init();
  lcd.backlight();
  lcd.clear();

  pinMode(buzina, OUTPUT);

  pinMode(vermelhoLUZ, OUTPUT);
  pinMode(amareloLUZ, OUTPUT);
  pinMode(verdeLUZ, OUTPUT);

  pinMode(vermelhoTEMPERATURA, OUTPUT);
  pinMode(verdeTEMPERATURA, OUTPUT);

  pinMode(vermelhoUMIDADE, OUTPUT);
  pinMode(verdeUMIDADE, OUTPUT);

  inicializaBuffers();
}
```

#### Cálculo de Média com Buffers
```cpp
float calculaMedia(int buffer[], int tamanho) {
  int soma = 0;
  for (int i = 0; i < tamanho; i++) {
    soma += buffer[i];
  }
  return soma / (float)tamanho;
}
```
- Essa função calcula a média dos valores armazenados no buffer, permitindo maior estabilidade nas leituras.

#### Controle da Luminosidade (`processaLUZ`)
```cpp
void processaLUZ(float luzMedia, unsigned long agora) {
  int ideal_min = 0;
  int ideal_max = 40;
  int margem_erroMIN = 0;
  int margem_erroMAX = 60;

  if (luzMedia >= ideal_min && luzMedia <= ideal_max) {
    acendeSomenteLUZ(verdeLUZ);
    noTone(buzina);
    naoPodetocar = false;
    casoAtualLUZ = "OK";
  } else if ((luzMedia > ideal_max && luzMedia < margem_erroMAX) || (luzMedia < ideal_min && luzMedia > margem_erroMIN)) {
    acendeSomenteLUZ(amareloLUZ);
    if (naoPodetocar == false) {
      tone(buzina, 200);
      tempoAnterior = agora;
      buzinaLigada = true;
      naoPodetocar = true;
    }
    if (agora - tempoAnterior >= 3000) {
      tempoAnterior = agora;
      if (buzinaLigada) {
        noTone(buzina);
        buzinaLigada = false;
      } else {
        tone(buzina, 200);
        buzinaLigada = true;
      }
    }
    casoAtualLUZ = "ALERTA";
  } else {
    acendeSomenteLUZ(vermelhoLUZ);
    naoPodetocar = false;
    noTone(buzina);
    tone(buzina, 2000);
    casoAtualLUZ = "PROBLEMA";
  }
}
```

#### Atualização do Display LCD
```cpp
void atualizaDisplay(float luzMedia, float temperaturaMedia, float umidadeMedia) {
  unsigned long agora = millis();

  if (agora - tempoDisplayAnterior >= 5000) {
    tempoDisplayAnterior = agora;
    estadoDisplay = (estadoDisplay + 1) % 3;
  }

  String linha1, linha2;

  switch (estadoDisplay) {
    case 0:
      linha1 = "Luz: " + String(luzMedia, 1) + "%";
      linha2 = (casoAtualLUZ == "OK") ? "Luz Ideal!" : 
               (casoAtualLUZ == "ALERTA") ? "Meia Luz!" : 
               "Muita Luz!";
      break;

    case 1:
      linha1 = "Temp.: " + String(temperaturaMedia, 1) + "C";
      linha2 = (casoAtualTEMPERATURA == "OK") ? "Temp. Ideal!" : 
               (casoAtualTEMPERATURA == "BAIXA") ? "Temp. Baixa!" : 
               "Temp. Alta!";
      break;

    case 2:
      linha1 = "Umidade: " + String(umidadeMedia, 1) + "%";
      linha2 = (casoAtualUMIDADE == "OK") ? "Umidade Ideal!" : 
               (casoAtualUMIDADE == "BAIXA") ? "Umidade Baixa!" : 
               "Umidade Alta!";
      break;
  }

  if (linha1 != textoAnteriorLinha1) {
    lcd.setCursor(0, 0);
    lcd.print("                ");
    lcd.setCursor(0, 0);
    lcd.print(linha1);
    textoAnteriorLinha1 = linha1;
  }

  if (linha2 != textoAnteriorLinha2) {
    lcd.setCursor(0, 1);
    lcd.print("                ");
    lcd.setCursor(0, 1);
    lcd.print(linha2);
    textoAnteriorLinha2 = linha2;
  }
}
```

---

## Como Executar

1. Monte o circuito seguindo o esquema no [Tinkercad](https://www.tinkercad.com/things/1FLMw0RI0Qp/editel?sharecode=3U-bvGk7_IB4qhG56tbSyutXl7edE_MXuUWwf2XKvjU).
2. Faça o upload do código para o Arduino UNO usando a IDE Arduino.
3. Conecte o circuito ao computador ou a uma fonte de alimentação.
4. Observe o comportamento dos LEDs, o buzzer e o display LCD com base nas condições ambientais.

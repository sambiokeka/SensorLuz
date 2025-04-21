# Sensor de Luz

Este projeto utiliza um sensor de luz (LDR) integrado com Arduino UNO para controlar LEDs e um buzzer com base em diferentes condições de luminosidade.

## Autores

-Erick Jooji (RM: 564482)

-Guilherme Godoy (RM: 564417)

-Luiz Dalboni (RM: 564189)

-Matheus Tozarelli (RM: 563490)

-Rafael Lorenzini (RM: 563643)

## Ferramentas e Tecnologias

- **Linguagem de programação:** C++
- **Placa:** Arduino UNO
- **Simulação:** [Tinkercad - Projeto SensorLuz](https://www.tinkercad.com/things/c1h5FtxbSvR/editel?returnTo=%2Fdashboard)

## Componentes Utilizados

- **1** Resistor de 10kΩ (LDR, utilize valores menores no resistor caso queira que o LDR retorne valores também)
- **1** Resistor de 1kΩ (Buzzer)
- **3** Resistores de 220Ω (3 LEDs)
- **11** Jumpers
- **3** LEDs (Vermelho, Amarelo, Verde)
- **1** Buzzer
- **1** LDR (Sensor de Luz)

## Como Funciona

O projeto utiliza um LDR (sensor de luz) para medir a intensidade da luz ambiente. Com base nos valores medidos, o Arduino controla LEDs e um buzzer para indicar diferentes condições de luminosidade. 

### Exemplo de Funcionamento:
- **luminosidade IDEAL:** O LED verde acende.
- **luminosidade em ALERTA:** O LED amarelo acende.
- **luminosidade com PROBLEMAS:** O LED vermelho acende e o buzzer é ativado.

## Código

(linhas 1 à 7)
Entradas dos leds.

(linha 11 à 22)
Depois temos variáveis, que serão utilizadas na função do
void loop,  elas servem para ativar ou desativar a buzina.
Nesta mesma parte temos um codigo comentado que serve para 
a buzina vermelha, que esta desativada, dado a sua falta de 
necessidade.

(linhas 27 à 31)
Utilizamos uma função que facilita ligar e desligar leds,
por exemplo ao invez de digitar isto para cada uma das situações:
  "digitalWrite(vermelho, HIGH);
  digitalWrite(amarelo, LOW);
  digitalWrite(verde, LOW);"
A função acendeSomente faz isso sem precisar de quase 9 linhas,
como seria, aplicando para cada uma das situações, no exemplo dado.
Então só utilizamos uma linha para ativar 1 led e os outros ficam desativados:
  "acendeSomente(vermelho);"

  
(linhas 34 à 40)
Após isso temos os Setups.


(linhas 44 à 141)
Temos o void loop, que faz o sensor de luz funcionar.

  Dentro do void loop:
  
  (linhas 46 à 54)
  Declaramos 6 variáveis:
  1 para o analogRead do LDR;
  2 para os valores de luz ideal minima e maxima;
  2 para as margens de erro que ativarão o estado de ALERTA;
  1 para contagem de tempo, o nome dela é "agora" (será útil depois para controlar o tempo da buzina tocada no estado de ALERTA).

  (linha 56)
  É utilizado um Serial.println para acompanhar os valores que o LDR esta retornando.

  (linhas 59 até 138)
  Temos a lógica útilizada para verificar qual situação o LDR está (if, else if e else):
  <br>
    (linhas 59 à 67)
    Dentro do if, é verificado se o valor lido pelo LDR está dentro dos valores colocados como ideal minimo e ideal maximo de luz, se estiver:
      IDEAL:
        -Desliga qualquer buzina que estivesse tocando antes de entrar na situação IDEAL;
        -Liga (os outros dois desligam se estavam ligados) e é inserimos o valor de uma variavel como false,  "naoPodetocar = false;" esta variável servira para quando estivermos na situação ALERTA.
        <br>
        <br>
    (linhas 70 à 103)
    Dentro do else if, é verificado se o valor lido pelo LDR esta fora do ideal máximo mas dentro da margem de erro máxima, ou se esta fora do ideal mínimo mas dentro da margem de erro mínima, se estiver:
      ALERTA:
        -A mais complicadinha de todas, ela verifica uma série de valores, mas primeiro de tudo.
        -Liga o LED amarelo (desligando os outros 2 se estavam ligados);
        (linhas 75 à 84)
        -Verifica se o valor da váriavel "naoPodeTocar" está como false, se estiver:
            --Liga a buzina;
            --Coloca o valor da váriavel "tempoAnterior" como o mesmo valor da variável agora, isso servira pouco abaixo, para que de 3 em 3 segundos algo aconteça;
            --Coloca o valor da váriavel "buzinaLigada" como true, ela servira pouco abaixo para a lógica do que acontecera de 3 em 3 segundos;
            --Por fim coloca o valor da variável "naoPodetocar" como true, para que enquanto o código estiver na situação ALERTA, ela não fique ativando o que esta dentro do "if(naoPodeTocar == false)"
            <br>
            <br>
        (linhas 87 a 102)
        -Verifica se tempoAnterior-agora é igual a 3000 milisegundos, se for:
          --faz com que o "tempoAnterior" seja novamente igual ao valor de "agora", para que esse if continue sempre (enquanto estivermos na situação de ALERTA, é claro) de 3 em 3 segundos;
          --Verifica se a variavel "buzinaLigada" é igual a true (ou seja que a buzina está tocando), se for:
          --desliga a buzina e coloca o valor de "buzinaLigada" como false.
        -Caso "buzinaLigada" não seja true, ele faz:
          --A buzina ligar;
          --Coloca o valor da variável "buzinaLigada" como true.
         
  (linhas 107 à 138)
  Caso nem o if da situação IDEAL, nem o else if da situação ALERTA, forem verdade, ele faz:
    PROBLEMA:
    -Liga o LED vermelho (desliga os outros 2 se estavam ligados);
    -Faz com que naoPodeTocar seja false (Agora que vimos a situação ALERTA, posso explicar de forma mais simples, dentro da propria situação ALERTA, a primeira coisa que é feita é verificar se naoPodeTocar é false, se for ativa uma serie de coisas,
    e coloca o valor dessa mesma variavel como true, e até o fim da situação ALERTA, isso não é mudado, ou seja, caso ocorra uma troca de situações e o naoPodeTocar continue como true, ex: ALERTA>PROBLEMA>ALERTA, somente o primeiro ALERTA ativaria essa serie de coisas, sendo uma delas a buzina,
    depois disso quando fosse trocado para a situação PROBLEMA e depois para o ALERTA de novo, o ALERTA não ativaria as coisas da maneira devida);
    -Desliga qualquer buzina que estivesse tocando anteriormente.
    


## Como Executar

1. Monte o circuito seguindo o esquema fornecido no [Tinkercad](https://www.tinkercad.com/things/c1h5FtxbSvR/editel?returnTo=%2Fdashboard).
2. Faça o upload do código para o Arduino UNO usando a IDE Arduino.
3. Conecte o circuito ao computador ou a uma fonte de alimentação e observe o comportamento dos LEDs e do buzzer com base na luminosidade.



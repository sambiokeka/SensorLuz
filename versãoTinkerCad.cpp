#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#define col 16
#define lin 2
#define ende 0x27

LiquidCrystal_I2C lcd(ende, col, lin);


int vermelhoLUZ = 10;
int amareloLUZ = 9;
int verdeLUZ = 8;

int vermelhoTEMPERATURA = 7;
int verdeTEMPERATURA = 6;

int vermelhoUMIDADE = 5;
int verdeUMIDADE = 4;
int buzina = 11;

int estadoDisplay = 0;

unsigned long tempoAnterior = 0;
unsigned long tempoDisplayAnterior = 0;
bool buzinaLigada = false;
bool naoPodetocar = false;

String textoAnteriorLinha1 = "";
String textoAnteriorLinha2 = "";

String casoAtualLUZ = "";
String casoAtualTEMPERATURA = "";
String casoAtualUMIDADE = "";

int luzBuffer[5] = {0};
int temperaturaBuffer[5] = {0};
int umidadeBuffer[5] = {0};

int luzIndex = 0;
int temperaturaIndex = 0;
int umidadeIndex = 0;

void inicializaBuffers() {
  for (int i = 0; i < 5; i++) {
    luzBuffer[i] = map(analogRead(A0), 6, 679, 0, 100);
    temperaturaBuffer[i] = map(analogRead(A1), 20, 358, -40, 125);
    umidadeBuffer[i] = map(analogRead(A2), 0, 1023, 0, 100);
  }
}

float calculaMedia(int buffer[], int tamanho) {
  int soma = 0;
  for (int i = 0; i < tamanho; i++) {
    soma += buffer[i];
  }
  return soma / (float)tamanho;
}

void atualizaMedias(int luz, int temperatura, int umidade, float &luzMedia, float &temperaturaMedia, float &umidadeMedia) {
  luzBuffer[luzIndex] = luz;
  luzIndex = (luzIndex + 1) % 5;

  temperaturaBuffer[temperaturaIndex] = temperatura;
  temperaturaIndex = (temperaturaIndex + 1) % 5;

  umidadeBuffer[umidadeIndex] = umidade;
  umidadeIndex = (umidadeIndex + 1) % 5;

  luzMedia = calculaMedia(luzBuffer, 5);
  temperaturaMedia = calculaMedia(temperaturaBuffer, 5);
  umidadeMedia = calculaMedia(umidadeBuffer, 5);
}

void acendeSomenteLUZ(int led) {
  digitalWrite(vermelhoLUZ, led == 10 ? HIGH : LOW);
  digitalWrite(amareloLUZ, led == 9 ? HIGH : LOW);
  digitalWrite(verdeLUZ, led == 8 ? HIGH : LOW);
}

void acendeSomenteTEMPERATURA(int led) {
  digitalWrite(vermelhoTEMPERATURA, led == 7 ? HIGH : LOW);
  digitalWrite(verdeTEMPERATURA, led == 6 ? HIGH : LOW);
}

void acendeSomenteUMIDADE(int led) {
  digitalWrite(vermelhoUMIDADE, led == 5 ? HIGH : LOW);
  digitalWrite(verdeUMIDADE, led == 4 ? HIGH : LOW);
}

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

void processaTEMPERATURA(float temperaturaMedia) {
  int ideal_min = 10;
  int ideal_max = 15;

  if (temperaturaMedia >= ideal_min && temperaturaMedia <= ideal_max) {
    acendeSomenteTEMPERATURA(verdeTEMPERATURA);
    casoAtualTEMPERATURA = "OK";
  } else if (temperaturaMedia < ideal_min) {
    acendeSomenteTEMPERATURA(vermelhoTEMPERATURA);
    casoAtualTEMPERATURA = "BAIXA";

    tone(buzina, 2000);
  } else if (temperaturaMedia > ideal_max) {
    acendeSomenteTEMPERATURA(vermelhoTEMPERATURA);
    casoAtualTEMPERATURA = "ALTA";

    tone(buzina, 2000);
  }
}


void processaUMIDADE(float umidadeMedia) {
  int ideal_min = 50;
  int ideal_max = 70;

  if (umidadeMedia >= ideal_min && umidadeMedia <= ideal_max) {
    acendeSomenteUMIDADE(verdeUMIDADE);
    casoAtualUMIDADE = "OK";

  } else if (umidadeMedia < ideal_min) {
    acendeSomenteUMIDADE(vermelhoUMIDADE);
    casoAtualUMIDADE = "BAIXA";

    tone(buzina, 2000);
  } else if (umidadeMedia > ideal_max) {
    acendeSomenteUMIDADE(vermelhoUMIDADE);
    casoAtualUMIDADE = "ALTA";

    tone(buzina, 2000);
  }
}

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
      if (casoAtualLUZ == "OK") {
        linha2 = "Luz Ideal!";
      }else if (casoAtualLUZ == "ALERTA") {
        linha2 = "Meia Luz!";
      }else if (casoAtualLUZ == "PROBLEMA") {
        linha2 = "Muita Luz!";
      }
      break;

    case 1:
      linha1 = "Temp.: " + String(temperaturaMedia, 1) + "C";
      if (casoAtualTEMPERATURA == "OK") {
        linha2 = "Temp. Ideal!";
      }else if (casoAtualTEMPERATURA == "BAIXA") {
        linha2 = "Temp. Baixa!";
      }else if (casoAtualTEMPERATURA == "ALTA") {
        linha2 = "Temp. Alta!";
      }
      break;

    case 2:
      linha1 = "Umidade: " + String(umidadeMedia, 1) + "%";
      if (casoAtualUMIDADE == "OK") {
        linha2 = "Umidade Ideal!";
      }else if (casoAtualUMIDADE == "BAIXA") {
        linha2 = "Umidade Baixa!";
      }else if (casoAtualUMIDADE == "ALTA") {
        linha2 = "Umidade Alta!";
      }
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


void loop() {
  int luz = analogRead(A0);
  int temperatura = analogRead(A1);
  
  int umidade = analogRead(A2);

  int luzAjustada = map(constrain(luz, 6, 679), 6, 679, 0, 100);
  int temperaturaAjustada = map(constrain(temperatura, 20, 358), 20, 358, -40, 125);
  int umidadeAjustada = map(constrain(umidade, 0, 1023), 0, 1023, 0, 100);

  float luzMedia, temperaturaMedia, umidadeMedia;
  atualizaMedias(luzAjustada, temperaturaAjustada, umidadeAjustada, luzMedia, temperaturaMedia, umidadeMedia);

  if (luzMedia < 0 || luzMedia > 100) luzMedia = 50;
  if (temperaturaMedia < -40 || temperaturaMedia > 125) temperaturaMedia = 25;
  if (umidadeMedia < 0 || umidadeMedia > 100) umidadeMedia = 50;

  unsigned long agora = millis();
  processaLUZ(luzMedia, agora);
  processaTEMPERATURA(temperaturaMedia);
  processaUMIDADE(umidadeMedia);

  atualizaDisplay(luzMedia, temperaturaMedia, umidadeMedia);
}
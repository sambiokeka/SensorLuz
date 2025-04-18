int vermelho = 10;

int amarelo = 9;

int verde = 8;

int buzina = 7;

unsigned long tempoAnterior = 0;

bool buzinaLigada = false;

bool naoPodetocar = false;

unsigned long ultimoBeep = 0;

unsigned long intervalo = 3000;

bool beepAtivo = false;

//Função mil QI para ligar um ledo só
void acendeSomente(int led) {

  digitalWrite(vermelho, led == 10 ? HIGH : LOW);

  digitalWrite(amarelo,  led == 9  ? HIGH : LOW);

  digitalWrite(verde,  led == 8  ? HIGH : LOW); 

}

//Setups das entradas, os analog n precisa
void setup() {
  pinMode(buzina, OUTPUT);

  pinMode(vermelho, OUTPUT);

  pinMode(amarelo, OUTPUT);

  pinMode(verde, OUTPUT);
  
}


//Loop legal e maneiro
void loop() {
    
    int luz = analogRead(A0); //Luz recebe o valor do LDR
    
    unsigned long agora = millis();//Tempo do loop
    
    //OK
    if (luz < 600) {
        
        acendeSomente(verde);//Verde 
        
        noTone(buzina);//Sem buzinas por aqui
        
        naoPodetocar = false;//Buzina de 3 segundos pode tocar
        
    } 
    
    //ALERTA
    else if (luz < 900) {
        
        acendeSomente(amarelo);//Amarelo
        
        //Se pode tocar buzina de 3 segundos
        if (naoPodetocar == false) {
        
            tone(buzina, 200);// Toca instantaneamente
        
            tempoAnterior = agora;// Começa a contar os 3 segundos
        
            buzinaLigada = true;//A buzina esta ligada
        
            naoPodetocar = true;//Não pode mais tocar
        }

        //A cada 3 segundos
        if (agora - tempoAnterior >= 3000) {
        
            tempoAnterior = agora;//Reinicia a contagem
            
            if (buzinaLigada) {
                
                noTone(buzina);//Se a buzina estiver ligada ela é desligada
            
            } else {
                
                tone(buzina, 200);//Se não liga ela
                
            }
            
            buzinaLigada = false;//Buzina não esta ligada
        
        }
    } 
    
    //PROBLEMA
    else {
        
        acendeSomente(vermelho);//Vermelho
        
        naoPodetocar = false;//Buzina de 3 segundos pode tocar
        
        if (agora - ultimoBeep >= 100) {
        
            ultimoBeep = agora;//Temporizador para os beeps

            //Se tiver tocando os beeps
            if (beepAtivo) {
                
                noTone(buzina);//Desliga a buzina
                
            } else {
                
                tone(buzina, 500);//Liga a buzina
                
            }

            beepAtivo = !beepAtivo;//Não esta tocando os beeps
        
        }
    }
}



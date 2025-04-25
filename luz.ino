int vermelho = 10;

int amarelo = 9;

int verde = 8;

int buzina = 7;


//Variáveis que vão ser usadas depois
unsigned long tempoAnterior = 0;

bool buzinaLigada = false;

bool naoPodetocar = false;

/* para buzina do vermelho
unsigned long ultimoBeep = 0;

bool beepAtivo = false;
*/


//Função mil QI para ligar um led só
void acendeSomente(int led) {
  digitalWrite(vermelho, led == 10 ? HIGH : LOW);
  digitalWrite(amarelo,  led == 9  ? HIGH : LOW);
  digitalWrite(verde,  led == 8  ? HIGH : LOW); 
}

//Setups das entradas, os analog n precisa
void setup() {
  Serial.begin(9600);
  pinMode(buzina, OUTPUT);
  pinMode(vermelho, OUTPUT);
  pinMode(amarelo, OUTPUT);
  pinMode(verde, OUTPUT);
}


//Loop legal e maneiro
void loop() {

  	int luz = analogRead(A0); //Luz recebe o valor do LDR
  	
    int ideal_min = 900;
   	int ideal_max = 950;  
	
  	int margem_erroMIN = 100;
  	int margem_erroMAX = 970;
  	
    
    unsigned long agora = millis();//Tempo do loop
  
    Serial.println(luz);
        
    //IDEAL / OK
    if (luz >= ideal_min && luz <= ideal_max) {
        
        acendeSomente(verde);//Verde 
        
        noTone(buzina);//Sem buzinas por aqui
        
        naoPodetocar = false;//Buzina de 3 segundos pode tocar
        
    } 
    
    //ALERTA
    else if ((luz > ideal_max && luz < margem_erroMAX) || (luz < ideal_min && luz > margem_erroMIN) ) {
        
        acendeSomente(amarelo);//Amarelo
        
        //Se pode tocar buzina de 3 segundos
        if (naoPodetocar == false) {
        
            tone(buzina, 200);// Toca instantaneamente
        
            tempoAnterior = agora;//Faz o tempoAnterior ser igual ao agora
        
            buzinaLigada = true;//A buzina esta ligada
        
            naoPodetocar = true;//Não pode mais tocar
        }

        //A cada 3 segundos
        if (agora - tempoAnterior >= 3000) {
        
            tempoAnterior = agora;//Reinicia a contagem
            
            if (buzinaLigada) {
                
                noTone(buzina);//Se a buzina estiver ligada ela é desligada
             	buzinaLigada = false; // Atualiza o estado da buzina
            
            } else {
                
                tone(buzina, 200);//Se não liga ela
                buzinaLigada = true; // Atualiza o estado da buzina
                
            }       
        }
    } 

    
    //PROBLEMA
    else {
        
        acendeSomente(vermelho);//Vermelho
        
        naoPodetocar = false;//Buzina de 3 segundos pode tocar
      	
      	noTone(buzina);
      
        /* CASO VERMELHO DEVA TOCAR BUZINA
        
        if (agora - ultimoBeep >= 0) {
        
            ultimoBeep = agora;//Temporizador para os beeps
          

            //Se tiver tocando os beeps
            if (beepAtivo) {
                
                noTone(buzina);//Desliga a buzina
                
            } else {
                
                tone(buzina, 1000);//Liga a buzina
                
            }
                                   	         
            beepAtivo = !beepAtivo;//Não esta tocando os beeps
            
         
        }
		*/         
    }
}



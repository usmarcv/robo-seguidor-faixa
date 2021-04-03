/*
   Projeto de Iniciação Cientifíca - Construção do Robô Seguidor de Linha: Integração de componentes eletrônicos e da lógica de programação.
   Projeto de Extensão - Robótica educacional: Participação em campeonatos e eventos.
   Escopo algoritmo - Robô seguidor de linha (Aécio Neves).
*/

#define sensorDir A1 // Porta analógica 1
#define sensorEsq A0 // Porta analógica 0
#define INTERVALO 200 // Intervalo de leitura de cor do sensor   de faixa (preto > 200) 
#define ANDANDO 132 // Controle de velocidade (PWM) dos motores
#define PARADO 0

int motorDir = 5; // Porta digital do motor direito
int motorEsq = 6; // Porta digital do motor esquerdo

int ESQUERDA; // Variável para armazenamento de leitura do sensor de faixa esquerdo 
int DIREITA; // Variável para armazenamento de leitura do sensor de faixa diretito

void Frente();
void Horario();
void Antihorario();

void setup(){ // Configurações do robô

  Serial.begin(9600); // Leitura de valores no monitor serial da IDE Arduino
  
  pinMode(motorDir, OUTPUT);
  pinMode(motorEsq, OUTPUT);
  
  Frente(); 
}

void loop(){ 

  ESQUERDA = analogRead(sensorEsq); // Leitura do sensor infravermelho esquerdo
  DIREITA = analogRead(sensorDir); // Leitura do sensor infravermelho direito

  if ((DIREITA < INTERVALO) && (ESQUERDA < INTERVALO)){// Robô não encontrou a faixa, movimento continua para frente
    
    Frente();
  
  }
  
  else if (DIREITA > INTERVALO){ // Robô encontrou a faixa com o sensor direito
    
    Horario();
    
    while(1){
      
      ESQUERDA = analogRead(sensorEsq); // Leitura do sensor infravermelho esquerdo
      
      if(ESQUERDA > INTERVALO) break;
      
    }
  }
  
  else if (ESQUERDA > INTERVALO){ // Robô encontrou a faixa com o sensor esquerdo
    
    Antihorario();
    
    while(1){
      
      DIREITA = analogRead(sensorDir); // Leitura do sensor infravermelho direito
      
      if(DIREITA > INTERVALO) break;
      
    }
  }
  
  else if ((DIREITA > INTERVALO) && (ESQUERDA > INTERVALO)){ // Robô encontrou o sensor com as duas faixas 

    Horario(); // Movimenta para esquerda até encontrar alguma faixa 

    while(1){
      
      ESQUERDA = analogRead(sensorEsq); // Leitura do sensor infravermelho esquerdo
      
      if(ESQUERDA > INTERVALO) break;
      
    }
  }


}


//Robô movimento para frente
void Frente(){
  analogWrite(motorDir, ANDANDO);
  analogWrite(motorEsq, ANDANDO);
}

//Robô movimento no sentido antihorário
void Antihorario(){
  analogWrite(motorDir, ANDANDO);
  analogWrite(motorEsq, PARADO);
}

//Robô movimento no sentido horário
void Horario(){
  analogWrite(motorDir, PARADO);
  analogWrite(motorEsq, ANDANDO);
}

//Robô permanece em repouso
void Parar(){
  analogWrite(motorDir, PARADO);
  analogWrite(motorEsq, PARADO);
}

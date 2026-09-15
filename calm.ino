//Variáveis para sensores de linha e velocidade

int sensorDD, sensorDM, sensorMD, sensorME, sensorEM, sensorEE; // Sensores - D = Direita, M = Meio, E = Esquerda
int velMin = 70, velMed = 120, velMax = 185; // Velocidade dos motores - 0 a 255
int limiar = 600; // Limiar do sensor de luz - acima de 600 = preto, abaixo de 600 = branco

//Variáveis para sensores de início e fim de pista

int sensorFim; // Detecta o fim do percurso
int contaFim = 4; // Conta cada marca do percurso
boolean flagFim = false; // Conta uma vez só ao invés de contar a todo momento que estiver em cima da marca
long tempoTotal; // Detecta tempo desde que o arduino foi ligado
long tempoExtra = 2000; // Tempo extra para funcionar depois da última marca do percurso

// Definições dos pinos do Arduino ligados a entrada da Ponte H

// Motor Esquerdo
int ENA = 5;
int IN1 = 7;
int IN2 = 6;

// Motor Direito
int ENB = 3;
int IN3 = 4;
int IN4 = 2;

// Define os pinos como saida e como entrada

void setup(){
  pinMode(IN1, OUTPUT);  
  pinMode(IN2, OUTPUT);  
  pinMode(IN3, OUTPUT);  
  pinMode(IN4, OUTPUT);
  pinMode(ENA,  OUTPUT);  
  pinMode(ENB,  OUTPUT); 

  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  pinMode(A4, INPUT);
  pinMode(A5, INPUT); 

  Serial.begin(9600);
}

void paraFrente(int vel) {
  //Configura velocidade dos motores
  analogWrite(ENA, vel);
  analogWrite(ENB, vel);

  //Aciona o motores
  digitalWrite(IN1, LOW); //E 
  digitalWrite(IN2, HIGH); //E
  digitalWrite(IN3, LOW); //D
  digitalWrite(IN4, HIGH); //D
}

void viraEsquerda(int velE, int velD) {
  analogWrite(ENA, vel);
  analogWrite(ENB, vel);

  // Motor Esquerdo < Motor Direito (Virar Esquerda)
  digitalWrite(IN1, LOW); //E 
  digitalWrite(IN2, LOW); //E
  digitalWrite(IN3, LOW); //D
  digitalWrite(IN4, HIGH); //D
}

void viraDireita(int velE, int velD) {
  analogWrite(ENA, velE);
  analogWrite(ENB, velD);

  // Motor Direito < Motor Esquerdo (Virar Direita)
  digitalWrite(IN1, LOW); //E 
  digitalWrite(IN2, HIGH); //E
  digitalWrite(IN3, LOW); //D
  digitalWrite(IN4, LOW); //D
}

void para_motores() {
  // Motor Esquerdo para
  digitalWrite(IN1, HIGH); //E
  digitalWrite(IN2, HIGH); //E

  // Motor Direito para
  digitalWrite(IN3, HIGH); //D
  digitalWrite(IN4, HIGH);//D
}

void segueLinha(){  

  //le os sensores
  sensorDir   = analogRead(A1); //Sensor 7
  
  sensorLinhaD = analogRead(A2); //Sensor 5
  sensorLinhaE = analogRead(A3); //Sensor 4
  
  sensorEsq   = analogRead(A4); //Sensor 2

  /*
  sensorEE = analogRead(A0);
  sensorEM = analogRead(A1);
  sensorME = analogRead(A2);
  sensorMD = analogRead(A3);
  sensorDM = analogRead(A4);
  sensorDD = analogRead(A5);
  */

  //Se estiver na linha segue em frente 
  //if (sensorME < limiar && sensorMD < limiar){
  if (sensorLinhaE < limiar || sensorLinhaD < limiar){
    Serial.println("para_frente");
    para_frente(velMed);    
  }
 
  //Se sensorDir acha linha vire para a direita
  //if (sensorEM < limiar && sensorEE < limiar && sensorME > limiar && sensorMD > limiar){
  if (sensorDir < limiar && sensorLinhaD > limiar){
    //Serial.println("para_direita");
    //vira_direita(velMed);
    Serial.println("para_esquerda");
    vira_esquerda(velMed);
  }

  //Se sensorEsq acha linha vire para a esquerda
  //if (sensorDM < limiar && sensorDD < limiar && sensorME > limiar && sensorMD > limiar){
  if (sensorEsq < limiar && sensorLinhaE > limiar){
    //Serial.println("para_esquerda");
    //vira_esquerda(velMed);
    Serial.println("para_direita");
    vira_direita(velMed);
  }

  
  /*
  //TESTE MOTORES
  para_frente(velENAx);
  delay(2000);
  vira_direita(velMed);
  delay(2000);
  vira_esquerda(velMed);
  delay(2000);
  */
}
 
void loop(){
  //Segue linha até encontrar ENArca de fim de pista
  while(contaFim > 0){
    segueLinha();
    
    /*
    if (sensorFim < limiar)
       flagFim = true; 
    if (sensorFim > limiar && flagFim == true){
       flagFim=false;
       contaFim--;
    }
    */

    delay(200);
  }

 //Segue linha por ENAis 2 segundos antes de parar
 tempoTotal = millis();
 while((millis() - tempoTotal) < tempoExtra)
   segueLinha();

 //Pára motores
 para_motores();

 //Espera 10s
 delay(10000);
 }
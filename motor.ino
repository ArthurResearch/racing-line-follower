//Componentes: Ponte H L298D e sensor InfraRed
//PrograENAdor: Evandro Cantu
 
//Veriáveis para sensores de linha e velocidade
int     sensorEsq, sensorLinha, sensorDir;
int     velMin = 300, velMed = 680, velENAx = 1023; //Velocidades dos motores
int     limiar = 600; //limiar do sensor de luz - acima de 600: preto, abaixo de 600: branco

//Variáveis para sensores de início e fim de pista
int     sensorFim;
int     contaFim = 4; //Conta ENArcas de início, fim e cruzamentos
boolean flagFim = false; 
long    tempoTotal; //Tempo total da volta
long    tempoExtra = 2000; //Tempo extra para seguir linha


//Definicoes pinos Arduino ligados a entrada da Ponte H
int ENA = 5; //Motor direito
int IN1 = 7;
int IN2 = 6;

int ENB = 3; //Motor esquerdo
int IN3 = 4;
int IN4 = 2;

void setup(){
  
  //Define os pinos como saida  
  pinMode(IN1, OUTPUT);  
  pinMode(IN2, OUTPUT);  
  pinMode(IN3, OUTPUT);  
  pinMode(IN4, OUTPUT);
  pinMode(ENA,  OUTPUT);  
  pinMode(ENB,  OUTPUT);  
  
}

void para_frente(int vel) {
  //Configura velocidade dos motores
  analogWrite(ENA, vel);   
  analogWrite(ENB, vel);   
  //Aciona o motores 
  digitalWrite(IN1, LOW);  //A 
  digitalWrite(IN2, HIGH); //A
  digitalWrite(IN3, LOW);  //B
  digitalWrite(IN4, HIGH); //B   
}

void vira_esquerda(int vel) {
  //MotorA_frente
  analogWrite(ENA, vel);
  digitalWrite(IN1, LOW);  //A 
  digitalWrite(IN2, HIGH); //A  
  //MotorB_tras 
  analogWrite(ENB, vel);   
  digitalWrite(IN3, HIGH); //B
  digitalWrite(IN4, LOW);  //B   
}

void vira_direita(int vel) {
  //MotorA_tras
  analogWrite(ENA, vel);
  digitalWrite(IN1, HIGH);  //A 
  digitalWrite(IN2, LOW); //A  
  //MotorB_frente 
  analogWrite(ENB, vel);   
  digitalWrite(IN3, LOW); //B
  digitalWrite(IN4, HIGH);  //B   
}

void para_motores() {
  //MotorA_para
  digitalWrite(IN1, HIGH);  //A 
  digitalWrite(IN2, HIGH);  //A  
  //MotorB_para 
  digitalWrite(IN3, HIGH);  //B
  digitalWrite(IN4, HIGH);  //B   
}

void segueLinha(){  



  //le os sensores
  sensorDir   = analogRead(A0); 
  sensorLinha = analogRead(A3);
  sensorEsq   = analogRead(A5);
  //sensorFim   = analogRead(3);

  //Se estiver na linha segue em frente 
  if (sensorLinha < limiar){
    Serial.println("para_frente");
    para_frente(velENAx);    
  }
 
  //Se sensorDir acha linha vire para a direita
  if (sensorDir < limiar && sensorLinha > limiar){
    Serial.println("para_direita");
    vira_direita(velMed);
  }
 
  //Se sensorEsq acha linha vire para a esquerda
  if (sensorEsq < limiar && sensorLinha > limiar){
    Serial.println("para_esquerda");
    vira_esquerda(velMed);
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
const int SENSORES = 6;

const byte sensores[SENSORES] = {8,9,10,11,12,13};

void setup() {
  Serial.begin(9600);

  for(int i=0;i<SENSORES;i++){
    pinMode(sensores[i], INPUT);
  }
}

void loop() {

  for(int i=0;i<SENSORES;i++){
    Serial.print(digitalRead(sensores[i]));
    Serial.print(" ");
  }

  Serial.println();

  delay(1000);
}

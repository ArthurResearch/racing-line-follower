#include <QTRSensors.h>

QTRSensors qtr;

const uint8_t NUM_SENSORS = 6;
uint16_t sensorValues[NUM_SENSORS];

void setup() {
  Serial.begin(9600);

  qtr.setTypeRC();

  qtr.setSensorPins(
    (const uint8_t[]){8, 9, 10, 11, 12, 13},
    NUM_SENSORS
  );

  // Calibração
  for (uint16_t i = 0; i < 300; i++)
  {
    qtr.calibrate();
    delay(10);
  }

  Serial.println("Calibrado");
}

void loop() {
  uint16_t posicao = qtr.readLineBlack(sensorValues);

  Serial.print("Posicao: ");
  Serial.println(posicao);

  delay(50);
}


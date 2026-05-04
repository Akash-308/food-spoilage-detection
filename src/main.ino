const int mq6Pin = A0;
const int redLedPin = 8;
const int greenLedPin = 7;
const int buzzerPin = 9;

const int gasThreshold = 300;

unsigned long previousMillis = 0;
const long interval = 15000; // 15 seconds

int readGasSensor() {
  return analogRead(mq6Pin);
}

void alertGasDetected() {
  digitalWrite(redLedPin, HIGH);
  digitalWrite(greenLedPin, LOW);
  digitalWrite(buzzerPin, HIGH);
}

void normalCondition() {
  digitalWrite(redLedPin, LOW);
  digitalWrite(greenLedPin, HIGH);
  digitalWrite(buzzerPin, LOW);
}

void setup() {
  Serial.begin(9600);

  pinMode(redLedPin, OUTPUT);
  pinMode(greenLedPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
}

void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    int sensorValue = readGasSensor();

    Serial.print("MQ-6 Value: ");
    Serial.println(sensorValue);

    if (sensorValue > gasThreshold) {
      alertGasDetected();
    } else {
      normalCondition();
    }
  }
}

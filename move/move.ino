const int ledPin = 13;
const int switchPin = 2;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(switchPin, INPUT);
}

void loop() {
  int value = digitalRead(switchPin); 
  if (HIGH == value) {
    digitalWrite(ledPin, HIGH);
  } else {
    digitalWrite(ledPin, LOW); 
  }
}


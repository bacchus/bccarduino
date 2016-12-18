const int light_pin = A0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  int light = analogRead(light_pin);
  Serial.println(light);
  delay(100);
}


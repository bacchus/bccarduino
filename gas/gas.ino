const int gas_pin = A0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int val = analogRead(gas_pin);
  if (val > 150) {
    Serial.print("panic: ");
  }
  Serial.println(val);
  delay(1000);
}


const int ax1_pin = A0;
const int ax2_pin = A1;
const int btn_pin = 2;

void setup() {
  Serial.begin(9600);
  pinMode(btn_pin, INPUT);
}

void loop() {
  int ax1 = analogRead(ax1_pin);
  delay(100);
  int ax2 = analogRead(ax2_pin);
  delay(100);
  if (digitalRead(btn_pin) == HIGH) {
    Serial.print("on : ");
  } else {
    Serial.print("off: ");
  }

  Serial.print(ax1);
  Serial.print(";");
  Serial.print(ax2);
  Serial.println("");
  
  delay(1000);
}


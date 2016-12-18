const int ao_pin = A0;

const int do_pin = 2;

void setup() {
  Serial.begin(9600);
  
  pinMode(do_pin, INPUT);
}

void loop() {
  int val = analogRead(ao_pin);
  int dval = digitalRead(do_pin);
  
  Serial.print(dval);
  Serial.print(": ");
  Serial.println(val);
  
  delay(1000);
}

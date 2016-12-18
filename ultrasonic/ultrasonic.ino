const int trig_pin = 8;
const int echo_pin = 9;

void setup() {
  Serial.begin(9600);
  pinMode(trig_pin, OUTPUT);
  pinMode(echo_pin, INPUT);
  digitalWrite(trig_pin, LOW);
}

void loop() {
  digitalWrite(trig_pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig_pin, LOW);
  long dist = pulseIn(echo_pin, HIGH)/58;
  Serial.println(dist);
  delay(1000);
}


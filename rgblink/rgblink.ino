// rgb test

int rid = 10;
int gid = 11;
int bid = 12;

void setup() {
  pinMode(rid, OUTPUT);
  pinMode(gid, OUTPUT);
  pinMode(bid, OUTPUT);

  off();
}

void off() {
  digitalWrite(rid, LOW);
  digitalWrite(gid, LOW);
  digitalWrite(bid, LOW);
}

void xon(int x) {
  off();
  digitalWrite(x, HIGH);
}

void ron() { xon(rid); }
void gon() { xon(gid); }
void bon() { xon(bid); }

void rgbon(float r, float g, float b) {
  float sum = r + g + b;
  float tm = 1000;
  r *= tm/sum;
  g *= tm/sum;
  b *= tm/sum;
  
  ron(); delayMicroseconds(r);
  gon(); delayMicroseconds(g);
  bon(); delayMicroseconds(b);
}

void loop() {
  //rgbon(1000, 100, 20);
  off();
  delay(2000);
}


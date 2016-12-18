const int Pin0 = 10;
const int Pin1 = 11;
const int Pin2 = 12;
const int Pin3 = 13;

void setup() {
  pinMode(Pin0, OUTPUT);
  pinMode(Pin1, OUTPUT);
  pinMode(Pin2, OUTPUT);
  pinMode(Pin3, OUTPUT);
}

int stepSequence[8][4] = {
  {0,0,0,1},
  {0,0,1,1},
  {0,0,1,0},
  {0,1,1,0},
  {0,1,0,0},
  {1,1,0,0},
  {1,0,0,0},
  {1,0,0,1},
};
  
void loop() {
  turnFDegree(360); //As discussed above
  delay(1000);

  turnBDegree(360); //As discussed above
  delay(1000);
}

void turnFDegree(int deg) {
  int DEG =  deg * (90);
  DEG = DEG/(127);
  DEG = 2*DEG;
  for (int i=0; i <DEG; i++) {
    turnForward();
    nullTurn();
  }
}

void turnBDegree(int deg) {
  int DEG =  deg * (90);
  DEG = DEG/(127);
  DEG = 2*DEG;
  for (int i=0; i <DEG; i++) {
    turnBackward();
    nullTurn();
  }
}

void turnForward() {
  for (int i = 0; i <= 7; i++) {
    digitalWrite(Pin0, stepSequence[i][0]);
    digitalWrite(Pin1, stepSequence[i][1]);
    digitalWrite(Pin2, stepSequence[i][2]);
    digitalWrite(Pin3, stepSequence[i][3]);
    delay(1);
  }
}

void turnBackward() {
  for (int i = 7; i >= 0; i--){
    digitalWrite(Pin0, stepSequence[i][0]);
    digitalWrite(Pin1, stepSequence[i][1]);
    digitalWrite(Pin2, stepSequence[i][2]);
    digitalWrite(Pin3, stepSequence[i][3]);
    delay(1);
  }
}

void nullTurn() {
  digitalWrite(Pin0, 0);
  digitalWrite(Pin1, 0);
  digitalWrite(Pin2, 0);
  digitalWrite(Pin3, 0);
}


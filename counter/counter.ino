
int number[10][10] = {
  {0,1,0,1,1,1,1,0,1},
  {0,0,0,0,1,0,0,0,1},
  {1,0,0,1,1,1,1,0,0},
  {1,0,0,1,1,0,1,0,1},
  {1,1,0,0,1,0,0,0,1},
  {1,1,0,1,0,0,1,0,1},
  {1,1,0,1,0,1,1,0,1},
  {0,0,0,1,1,0,0,0,1},
  {1,1,0,1,1,1,1,1,1},
  {1,1,0,1,1,0,0,0,1},
}; // Declaring the arrays corresponding to numbers from 0 to 9

void setup() {
  for (int i = 1; i <= 10; i++) {
    pinMode(i, OUTPUT);
  }
}

void loop() {
  for (int j = 0; j <= 9;  j++) { // j = current number displayed
    for (int i = 1; i <= 10; i++) { // i = array element being used
      digitalWrite(i,1 - number[j][i-1]);
    }
    delay(1000); // Pause 1 sec
  }
}


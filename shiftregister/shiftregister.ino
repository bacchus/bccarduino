//Pin connection to the Arduino
int latch_pin = 1;
int clock_pin = 2;
int data_pin = 3;
 
//The array has thebinary representation of the 10 digits to be displayed
int dec[11] = {0,126,72,61,109,75,103,119,76,127,79};

void setup() {
  pinMode(latch_pin,OUTPUT);
  pinMode(clock_pin,OUTPUT);
  pinMode(data_pin,OUTPUT);
}

void loop() {
  //Declaring some variables that will be used later
  int count;
  int display_number;
  
  //Looping through the 10 numbers to be displayed
  for (count = 0; count<11; count++){
    //Latch pin is low so the display will not fluctuate
    digitalWrite(latch_pin,LOW);
    //We found the number we want to display
    display_number = 127 - dec[count];
    
    //This function shifts the 8-bit information into the shift register
    shiftOut(data_pin,clock_pin, MSBFIRST,display_number);
    //And when the latch pin is high, the new 8-bit info will be displayed
    digitalWrite(latch_pin, HIGH);
    delay(1000);
  }
}


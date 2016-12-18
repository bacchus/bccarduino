/*
  SD card read/write

  MOSI - pin 11
  MISO - pin 12
  CLK - pin 13
  CS - pin 4
*/

#include <SPI.h>
#include <SD.h>

File myFile;

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  // wait for serial port to connect
  // needed for native USB port only
  while (!Serial);

  Serial.print("Initializing SD card...");

  if (!SD.begin(4)) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");

  /*
    // open the file. note that only one file can be open at a time,
    // so you have to close this one before opening another.
    myFile = SD.open("test.txt", FILE_WRITE);

    // if the file opened okay, write to it:
    if (myFile) {
    Serial.print("Writing to test.txt...");
    myFile.println("testing 1, 2, 3.");
    // close the file:
    myFile.close();
    Serial.println("done.");
    } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
    }

    // re-open the file for reading:
    myFile = SD.open("index.htm");
    if (myFile) {
    Serial.println("index.htm:");

    // read from the file until there's nothing else in it:
    while (myFile.available()) {
      Serial.write(myFile.read());
    }
    // close the file:
    myFile.close();
    } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
    }
  */

  myFile = SD.open("INDEX.HTM");
  if (myFile) {
    Serial.println("INDEX.HTM:");

    // read from the file until there's nothing else in it:
    while (myFile.available()) {
      Serial.write(myFile.read());
    }
    // close the file:
    myFile.close();
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening INDEX.HTM");
  }
}

void loop() {
  // nothing happens after setup
}


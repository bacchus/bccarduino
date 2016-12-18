#include <SoftwareSerial.h>
#include <SPI.h>
#include <SD.h>

File myFile;
SoftwareSerial esp8266(7, 6); // RX, TX

void setup() {

  // start: Serial
  Serial.begin(9600);

  // start: wifi
  esp8266.begin(9600);

  // start: SD
  if (!SD.begin(4)) {
    Serial.println("SD failed!");
    return;
  } else {
    Serial.println("SD ok");
  }


  // check for INDEX.HTM
  /*
    if (!SD.exists("index.html")) {
    Serial.println("ERROR - Can't find index.html file!");
    return;  // can't find index file
    }
  */

  // give it some time
  delay(5000);

/*
  // start: wifi server
  sendData("AT\r\n", 2000); // reset module
  delay(5000);
  sendData("AT+RST\r\n", 2000); // reset module
  delay(5000);
  sendData("AT+CWMODE=2\r\n", 1000); // configure as access point
  delay(3000);
  sendData("AT+CWSAP=\"bccesp\",\"habrahabr\",10,4\r\n", 1000); // configure as access point
  delay(3000);
*/
  // hot start: wifi server
  sendData("AT+CIFSR\r\n", 1000); // get ip address
  delay(3000);
  sendData("AT+CIPMODE=0\r\n", 1000); // configure for multiple connections
  delay(3000);
  sendData("AT+CIPMUX=1\r\n", 1000); // configure for multiple connections
  delay(3000);
  sendData("AT+CIPSERVER=1,80\r\n", 1000); // turn on server on port 80
  delay(3000);

  // start: blinking led
  //pinMode(2, OUTPUT);

  Serial.println("hello bacchus");
}

void loop() {

  // check if the esp is sending a message
  if (esp8266.available()) {

    if (esp8266.find("+IPD,")) {

      delay(1000); // so-so

      int id = esp8266.read() - 48; // ASCII value of 0 is 48

      if (esp8266.find("GET")) {

        String request = "";
        char c = 0;
        while (esp8266.available() && c != '\n')
        {
          char c = esp8266.read();
          request += c;
        }
        Serial.println(request);

        // debug print c
        //Serial.print("Char c: ");
        //Serial.print(c);
        //Serial.print("; int: ");
        //Serial.print((int)c);

        //if (c == '\n') // request ok
        //{
        if (request.indexOf("favicon.ico") > -1) {
          return;
        }

        myFile = SD.open("INDEX.HTM");
        if (myFile) {
          sendFile(id, myFile);
          myFile.close();
        } else {
          Serial.println("error opening INDEX.HTM");
        }

        String closeCommand = "AT+CIPCLOSE=";
        closeCommand += id;
        closeCommand += "\r\n";
        sendData(closeCommand, 3000);

        //} // c == '\n'
      } // esp8266.find("GET")
    } // esp8266.find("+IPD,")
  } // esp8266.available()
} // loop

void sendFile(int connectionId, File file) {

  while (myFile.available()) {
    char buff[64];
    char c = 0;
    int i = 0;
    while (i < 63) {
      c = myFile.read();
      if (c == '\n' || c == '\r')
        break;
      buff[i] = c;
      ++i;
    }
    buff[i] = 0;
    String line (buff);
    if (i > 0) {
      //line += (char)0;
      sendPage(connectionId, line);
    }
  }
}

void sendPage(int connectionId, String webpage) {

  String cipSend = "AT+CIPSEND=";
  cipSend += connectionId;
  cipSend += ",";
  cipSend += webpage.length();
  cipSend += "\r\n";

  sendData(cipSend, 1000);
  sendData(webpage, 1000);
}

String sendData(String command, const int timeout) {

  // echo
  //Serial.println(command);

  int i = 0;
  int len = command.length();
  while (i < len) {
    esp8266.write(command[i]);
    ++i;
    delay(10);
  }

  // direct write to Serial, not returned
  //while (esp8266.available() > 0) {
  //    Serial.write(esp8266.read());
  //}

  // wrong: delay
  //delay(1000);

  // wrong: send all
  //esp8266.print(command);

  // read responce to print to Serial and return
  String response = "";
  long int time = millis();
  while ((time + timeout) > millis()) {
    while (esp8266.available()) {
      char c = esp8266.read();
      response += c;
    }
  }
  Serial.println(response);

  return response;
}


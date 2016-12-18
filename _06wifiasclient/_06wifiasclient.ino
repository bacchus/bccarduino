#include <SoftwareSerial.h>
#include <DHT.h>

#define BCC_DBG 0

DHT dht_sens(2, DHT11);
//File myFile;

#if BCC_DBG
SoftwareSerial dbgSerial(6, 7); // RX, TX
#endif // BCC_DBG

int id = 0;

void dbg(String msg) {
#if BCC_DBG
  dbgSerial.println(msg);
#endif // BCC_DBG
}

void setup() {

#if BCC_DBG
  // start: dbgSerial
  dbgSerial.begin(9600);
#endif // BCC_DBG

  // start dht
  dht_sens.begin();

  // start: wifi through hardware serial
  Serial.begin(115200);

  // start: SD
  //  if (!SD.begin(4)) {
  //    dbgSerial.println("SD failed!");
  //    return;
  //  } else {
  //    dbgSerial.println("SD ok");
  //  }


  // check for INDEX.HTM
  /*
    if (!SD.exists("index.html")) {
    dbgSerial.println("ERROR - Can't find index.html file!");
    return;  // can't find index file
    }
  */

  // give it some time
  delay(2000);

  dbg("lets rock");

  startServer();
  
  // start: blinking led
  //pinMode(2, OUTPUT);

  dbg("hello bacchus");
}

void loop() {

  // check if the esp is sending a message
  if (Serial.available()) {

    if (Serial.find("+IPD,")) {

      delay(1000); // so-so

      id = Serial.read() - 48; // ASCII value of 0 is 48
      dbg("id: " + String(id));
      //id = 1;

      if (Serial.find("GET")) {

        String request = "";
        char c = 0;
        while (Serial.available() && c != '\n') {
          char c = Serial.read();
          request += c;
        }
        dbg(request);

        //if (c == '\n') // request ok
        //{

        //sendPage("HTTP/1.1 200 OK");

        if (request.indexOf("favicon.ico") > -1) {

          //return;

        } else if (request.indexOf("ajax_inputs") > -1) {

          dbg("get xml");

          //sendPage("Content-Type: text/xml");
          //sendPage("Connection: keep-alive");
          delay(5000);
          sendXmlResponse();

        } else if (request.indexOf("Forwarded") > -1) {

          //return;
          
        } else {

          dbg("get page");
          // send rest of HTTP header
          //sendPage("Content-Type: text/html");
          //sendPage("Connection: keep-alive");

          sendIndex();
          /*
            myFile = SD.open("INDEX.HTM");
            if (myFile) {
            sendFile(myFile);
            myFile.close();
            } else {
            dbgSerial.println("error opening INDEX.HTM");
            }
          */

        }

        String closeCommand = "AT+CIPCLOSE=";
        closeCommand += id;
        closeCommand += "\r\n";
        sendData(closeCommand, 3000);

        //} // c == '\n'
      } // Serial.find("GET")
    } // Serial.find("+IPD,")
  } // Serial.available()
} // loop

void startServer() {

  // reset module
  sendData("AT\r\n", 1000); // reset module
  delay(5000);
  //dbg("AT");
  sendData("AT+RST\r\n", 1000); // reset module
  delay(10000);
  //dbg("AT+RST");

  /*
  // start: wifi as server
  sendData("AT+CWMODE=2\r\n", 1000); // configure as access point
  delay(3000);
  dbg("AT+CWMODE=2");
  sendData("AT+CWSAP=\"bccesp\",\"habrahabr\",10,4\r\n", 1000); // configure as access point
  delay(3000);
  dbg("AT+CWSAP=...");
  */
 
  // start wifi as client
  sendData("AT+CWMODE=1\r\n", 1000); // configure as STA
  delay(3000);
  sendData("AT+CWJAP=\"bccwifi\",\"qazwsxedc\"\r\n", 1000); // connect to wifi
  delay(10000); // lets wait here to connect 10 sec

  // hot start: wifi server
  sendData("AT+CIFSR\r\n", 1000); // get ip address
  delay(2000);
  //dbg("AT+CIFSR");
  sendData("AT+CIPMODE=0\r\n", 1000); // configure for multiple connections
  delay(2000);
  //dbg("AT+CIPMODE=0");
  sendData("AT+CIPMUX=1\r\n", 1000); // configure for multiple connections
  delay(2000);
  //dbg("AT+CIPMUX=1");
  sendData("AT+CIPSERVER=1,8888\r\n", 1000); // turn on server on port 80
  delay(2000);
  //dbg("AT+CIPSERVER=1,80");
}

void sendIndex() {
  //sendPage("hello bacchus");

  
  String page;
  page = "<p>Temperature: <span id=\"d1\">...</span> *c</p>";
  sendPage(page);
  page = "<p>Humidity: <span id=\"d2\">...</span> %</p>";
  sendPage(page);
  page = "<script>function fn() { var req = new XMLHttpRequest();";
  sendPage(page);
  page = "req.onreadystatechange = function() {";
  sendPage(page);
  page = "if (req.readyState==4 && req.status==200) {";
  sendPage(page);
  page = "var xmlDoc = req.responseXML;";
  sendPage(page);
  page = "document.getElementById(\"d1\").innerHTML = xmlDoc.";
  sendPage(page);
  page = "getElementsByTagName(\"d1\")[0].childNodes[0].nodeValue;";
  sendPage(page);
  page = "document.getElementById(\"d2\").innerHTML = xmlDoc.";
  sendPage(page);
  page = "getElementsByTagName(\"d2\")[0].childNodes[0].nodeValue;";
  sendPage(page);
  page = "}};req.open(\"GET\", \"ajax_inputs\", true);req.send(null);}";
  sendPage(page);
  page = "</script><button onclick=\"fn()\">Try it</button>";
  sendPage(page);
  
}

void sendXmlResponse() {

  float d1 = dht_sens.readTemperature();
  float d2 = dht_sens.readHumidity();

  // <?xml version = \"1.0\" ?>
  String resp;

  resp = "<inputs>";
  sendPage(resp);
  
  if (isnan(d1) || isnan(d2)) {
    resp = "<d1>FAIL</d1><d2>FAIL</d2>";
    sendPage(resp);
  } else {
    resp = "<d1>" + String((int)d1) + "</d1>";
    sendPage(resp);
    resp = "<d2>" + String((int)d2) + "</d2>";
    sendPage(resp);
  }

  resp = "</inputs>";
  sendPage(resp);
}

/*
void sendFile(File file) {

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
      sendPage(line);
    }
  }
}
*/
void sendPage(String webpage) {

  String cipSend = "AT+CIPSEND=";
  cipSend += id;
  cipSend += ",";
  cipSend += webpage.length();
  cipSend += "\r\n";

  sendData(cipSend, 1000);
  sendData(webpage, 1000);
}

String sendData(String command, const int timeout) {

  // echo
  //dbgSerial.println(command);

  int i = 0;
  int len = command.length();
  while (i < len) {
    Serial.write(command[i]);
    ++i;
    delay(30);
  }

  // direct write to dbgSerial, not returned
  //while (Serial.available() > 0) {
  //    dbgSerial.write(Serial.read());
  //}

  // wrong: delay
  //delay(1000);

  // wrong: send all
  //Serial.print(command);

  // read responce to print to dbgSerial and return
  String response = "";

#if BCC_DBG
  long int time = millis();
  while ((time + timeout) > millis()) {
    while (Serial.available()) {
      char c = Serial.read();
      response += c;
    }
  }
  dbg(response);
#endif // BCC_DBG

  return response;
}


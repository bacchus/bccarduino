#include <SoftwareSerial.h>

//File myFile;
SoftwareSerial dbgSerial(6, 7); // RX, TX
int id = 0;
int test_on = 0;

void dbg(String msg) {
  dbgSerial.println(msg);
}

void setup() {

  // start: dbgSerial
  dbgSerial.begin(9600);

  // start: wifi
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
  delay(5000);

  dbg("lets rock");

  /*
    // start: wifi server
    sendData("AT\r\n", 2000); // reset module
    delay(5000);
    dbg("AT");
    sendData("AT+RST\r\n", 2000); // reset module
    delay(5000);
    dbg("AT+RST");
    sendData("AT+CWMODE=2\r\n", 1000); // configure as access point
    delay(3000);
    dbg("AT+CWMODE=2");
    sendData("AT+CWSAP=\"bccesp\",\"habrahabr\",10,4\r\n", 1000); // configure as access point
    delay(3000);
    dbg("AT+CWSAP=...");
  */

  // hot start: wifi server
  sendData("AT+CIFSR\r\n", 1000); // get ip address
  delay(3000);
  dbg("AT+CIFSR");
  sendData("AT+CIPMODE=0\r\n", 1000); // configure for multiple connections
  delay(3000);
  dbg("AT+CIPMODE=0");
  sendData("AT+CIPMUX=1\r\n", 1000); // configure for multiple connections
  delay(3000);
  dbg("AT+CIPMUX=1");
  sendData("AT+CIPSERVER=1,80\r\n", 1000); // turn on server on port 80
  delay(3000);
  dbg("AT+CIPSERVER=1,80");

  // start: blinking led
  //pinMode(2, OUTPUT);

  dbgSerial.println("hello bacchus");
}

void loop() {

  // check if the esp is sending a message
  if (Serial.available()) {

    if (Serial.find("+IPD,")) {

      delay(1000); // so-so

      id = Serial.read() - 48; // ASCII value of 0 is 48

      if (Serial.find("GET")) {

        String request = "";
        char c = 0;
        while (Serial.available() && c != '\n')
        {
          char c = Serial.read();
          request += c;
        }
        dbgSerial.println(request);

        // debug print c
        //dbgSerial.print("Char c: ");
        //dbgSerial.print(c);
        //dbgSerial.print("; int: ");
        //dbgSerial.print((int)c);

        //if (c == '\n') // request ok
        //{

        //sendPage("HTTP/1.1 200 OK");

        if (request.indexOf("favicon.ico") > -1) {

          //return;

        } else if (request.indexOf("ajax_inputs") > -1) {

          dbgSerial.println("get xml");

          //sendPage("Content-Type: text/xml");
          //sendPage("Connection: keep-alive");
          sendXmlResponse();

        } else {

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

void sendIndex() {
  sendPage("<button onclick=\"fn()\">Try it</button>");
  sendPage("<p>(pin  7): <span id=\"in1\">...</span></p>");
  sendPage("<script>");
  sendPage("function fn() {");
  sendPage("alert(\"test\");");
  sendPage("var req = new XMLHttpRequest();");

  sendPage("req.onreadystatechange = function() {");
  sendPage("if (req.readyState==4 && req.status==200) {");
  sendPage("document.getElementById(\"in1\").innerHTML =");
  sendPage("req.responseText; }};");
  
  sendPage("req.open(\"GET\", \"ajax_inputs\", true);");
  sendPage("req.send(null);}");
  sendPage("</script>");

  /*
  sendPage("<!DOCTYPE html>");
  sendPage("<html>");
  sendPage("<head>");
  sendPage("<title>Arduino Web Page ajax + xml</title>");
  sendPage("</head>");
  sendPage("<body>");
  sendPage("<h1>Arduino inputs ajax + xml</h1>");
  sendPage("<p>(pin  7): <span id=\"i1\">...</span></p>");

  sendPage("<button onclick=\"getArduinoInputs()\">Try it</button>");

  sendPage("<script>");
  sendPage("function getArduinoInputs() {");
  sendPage("alert(\"test\");");
  sendPage("nocache = \"&nocache=\" + Math.random()*1000000;");
  sendPage("var req = new XMLHttpRequest();");
  
  sendPage("req.onreadystatechange = function() {");
  sendPage("if (this.readyState == 4) {");
  sendPage("if (this.status == 200) {");
  sendPage("if (this.responseText != null) {");
  sendPage("document.getElementById(\"i1\").innerHTML =");
  sendPage("this.responseXML.getElementsByTagName('b1')[0].childNodes[0].nodeValue;");
  sendPage("}}}}");
  
  sendPage("req.open(\"GET\", \"ajax_inputs\" + nocache, true);");
  sendPage("req.send(null);");
  sendPage("setTimeout(\"getArduinoInputs()\", 30000);");
  sendPage("}");
  sendPage("</script>");

  sendPage("</body>");
  sendPage("</html>");
  */
}

void sendXmlResponse() {

  sendPage("<?xml version = \"1.0\" ?>");
  sendPage("<inputs>");

  if (test_on > 2) {
    sendPage("<b1>ON</b1>");
    test_on = 0;
  } else {
    sendPage("<b1>OFF</b1>");
  }
  ++test_on;

  sendPage("</inputs>");

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
    delay(20);
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
  long int time = millis();
  while ((time + timeout) > millis()) {
    while (Serial.available()) {
      char c = Serial.read();
      response += c;
    }
  }
  dbgSerial.println(response);

  return response;
}


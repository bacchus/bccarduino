#include <SoftwareSerial.h>

SoftwareSerial dbgSerial(6, 7); // RX, TX

void setup()
{
    dbgSerial.begin(9600);
    Serial.begin(115200);

    delay(5000);

    /*
    sendData("AT\r\n",2000); // reset module
    delay(5000);
    sendData("AT+RST\r\n",2000); // reset module
    delay(5000);
    sendData("AT+CWMODE=2\r\n",1000); // configure as access point
    delay(3000);
    sendData("AT+CWSAP=\"bccesp\",\"habrahabr\",10,4\r\n",1000); // configure as access point
    delay(3000);
    */

    
    sendData("AT+CIFSR\r\n",1000); // get ip address
    delay(3000);
    sendData("AT+CIPMODE=0\r\n",1000); // configure for multiple connections
    delay(3000);
    sendData("AT+CIPMUX=1\r\n",1000); // configure for multiple connections
    delay(3000);
    sendData("AT+CIPSERVER=1,80\r\n",1000); // turn on server on port 80
    delay(3000);
    
    pinMode(2, OUTPUT);
    
    dbgSerial.println("hello bacchus");
}
 
void loop()
{
    // check if the esp is sending a message
    if (Serial.available())
    {

        if (Serial.find("+IPD,"))
        {
            delay(1000);

            int id = Serial.read() - 48;
            // subtract 48 because the read() function returns 
            // the ASCII decimal value and 0 (the first decimal number) starts at 48

            if (Serial.find("GET"))
            {
              String request = "";
              char c = 0;
              while (Serial.available() && c != '\n')
              {
                char c = Serial.read();
                request += c;
              }

              dbgSerial.println(request);


              int ledStatus = 0;
              //if (c == '\n') // request ok
              {
                if (request.indexOf("favicon.ico") > -1) {
                  return;
                }

                
                
                if (request.indexOf("LED2=2") > -1) {
                  ledStatus = 1 - ledStatus;
                }
                if (ledStatus == 1) {
                  digitalWrite(2, HIGH);
                } else {
                  digitalWrite(2, LOW);
                }

                sendPage(id, "<!DOCTYPE html><html><head><title>Arduino LED Control</title>");
                sendPage(id, "</head><body><h1>LED</h1><p>Click to switch.</p>");
                sendPage(id, "<form method=\"GET\"><input type=\"checkbox\" name=\"LED2\" ");
                sendPage(id, "value=\"2\" onclick=\"submit();\" ");
                if (ledStatus == 1)
                  sendPage(id, "checked");
                sendPage(id, ">LED2</form></body></html>");
  
                String closeCommand = "AT+CIPCLOSE="; 
                closeCommand += id; // append connection id
                closeCommand += "\r\n";
                sendData(closeCommand,3000);
                
              }

            }
        }
    }
}

void sendPage(int connectionId, String webpage) {

    String cipSend = "AT+CIPSEND=";
    cipSend += connectionId;
    cipSend += ",";
    cipSend += webpage.length();
    cipSend += "\r\n";

    sendData(cipSend,1000);
    sendData(webpage,1000);
}
 
String sendData(String command, const int timeout)
{
    ////dbgSerial.println(command);

    int i = 0;
    int len = command.length();
    while (i < len) 
    {
        Serial.write(command[i]);
        ++i;
        delay(100);
    }

    //while (Serial.available() > 0) {
    //    //dbgSerial.write(Serial.read());
    //}

    //delay(1000);

    //Serial.print(command); // send the read character to the Serial
    
    //while (Serial.available() > 0) {
    //    //dbgSerial.write(mySerial.read());
    //}

    String response = "";
    
    long int time = millis();

    while ((time+timeout) > millis())
    {
        while (Serial.available())
        {
            // The esp has data so display its output to the serial window 
            char c = Serial.read(); // read the next character.
            response += c;
        }
    }

    //dbgSerial.println(response);
    
    return response;
}


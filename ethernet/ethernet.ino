// A simple web server that always just says "Hello World"

/*
CS - pin 10
SI - pin 11
SO - pin 12
SCK - pin 13
VCC - 3v3
GND - GND
 */

#include "etherShield.h"
#include "ETHER_28J60.h"

// Define MAC address and IP address - both should be unique in your network
static uint8_t mac[6] = {0x54, 0x55, 0x58, 0x10, 0x00, 0x24};  
static uint8_t ip[4] = {192, 168, 1, 15}; 
static uint16_t port = 80; // Use port 80 - the standard for HTTP                                     

ETHER_28J60 ethernet;

void setup()
{
  Serial.begin(9600);
  ethernet.setup(mac, ip, port);
}

void loop()
{
  char* req = ethernet.serviceRequest();
  //if (req)
  {
    Serial.println(req);
    ethernet.print("<H1>Hello World</H1>");
    ethernet.respond();
  }
  delay(1000);
}


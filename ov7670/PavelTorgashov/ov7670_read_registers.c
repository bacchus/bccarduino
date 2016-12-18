/*----------------
Read registers of OV7670.

pin 11  -> 4.7k -> XCLK -> 4.7k -> GND
pin A5  -> SIOC -> 3.3k -> +3.3V
pin A4  -> SIOD -> 3.3k -> +3.3V
--------------------*/

#include <Wire.h>

void readRegisters(char addr)  
{
  byte val;

  for(int i=0;i<256;i++)
  {
    // set address
    Wire.beginTransmission(addr);
    Wire.write(i);  //reg address low byte
    Wire.endTransmission();
    
    // read 1 byte
    Wire.requestFrom(addr, 1);
    while(Wire.available()) 
    {
      val = Wire.read();
    }
    Serial.print("REG 0x");
    Serial.print(i, HEX);    
    Serial.print(": 0x");
    Serial.println(val, HEX);
  }
}

void setup() 
{
  Wire.begin();
  Serial.begin(9600);
  
  /* Setup the 8MHz PWM clock 
  * This will be on pin 11*/
  DDRB|=(1<<3);//pin 11 output
  ASSR &= ~(_BV(EXCLK) | _BV(AS2));
  TCCR2A=(1<<COM2A0)|(1<<WGM21)|(1<<WGM20);
  TCCR2B=(1<<WGM22)|(1<<CS20);
  delay(3000);
  
  //set up twi for 100khz
  TWSR&=~3;//disable prescaler for TWI
  TWBR=72;//set to 100khz
  
  //------- To debug TWI: freq = 10kHz
  //  TWSR|=2;//enable prescaler for TWI
  //  TWBR= (byte) (((F_CPU / 2000L) - 16) / 2 );
  //-------
  
  readRegisters(0x21);// OV-7670 has address 0x21
}

void loop() 
{
}

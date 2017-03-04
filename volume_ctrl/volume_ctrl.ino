//
//USB Rotary Volume Control
//

#include "HID-Project.h"

// Define Arduino pin numbers for buttons and LEDs
//#define CAPSLOCKLED 2
//#define SCRLLOCKLED 3
//#define NUMLOCKLED 4
#define ROTARY_A 5
#define ROTARY_B 6

boolean A, a, B, b;
int t;

void setup() {
    pinMode(ROTARY_A, INPUT_PULLUP);
    pinMode(ROTARY_B, INPUT_PULLUP);

    //pinMode(CAPSLOCKLED, OUTPUT);
    //pinMode(SCRLLOCKLED, OUTPUT);
    //pinMode(NUMLOCKLED, OUTPUT);

    a = b = false;
    t = 0;

    Consumer.begin();
    //BootKeyboard.begin(); // For num caps scrl
    //System.begin(); // For System functions
    //Gamepad.begin(); // For gamepad functions
    //Mouse.begin(); // For mouse functions
    //AbsoluteMouse.begin(); // For the Absolute Mouse

    /*
    // Flash the LEDs just to show we're in business
    digitalWrite(CAPSLOCKLED, HIGH);    delay(200);
    digitalWrite(SCRLLOCKLED, HIGH);    delay(200);
    digitalWrite(NUMLOCKLED, HIGH);     delay(200);
    
    digitalWrite(CAPSLOCKLED, LOW);     delay(200);
    digitalWrite(SCRLLOCKLED, LOW);     delay(200);
    digitalWrite(NUMLOCKLED, LOW);      delay(200);
    */
}

void loop() {
    if (millis() + 5 > t) {
        A = digitalRead(ROTARY_A) == LOW;
        B = digitalRead(ROTARY_B) == LOW;

        if (A && !a) {
            Consumer.write(B ? MEDIA_VOL_UP : MEDIA_VOL_DOWN);
        } else if (!A && a) {
            Consumer.write(B ? MEDIA_VOL_DOWN : MEDIA_VOL_UP);
        }
        
        a = A;
        
        /*
        if (BootKeyboard.getLeds() & LED_CAPS_LOCK)
            digitalWrite(CAPSLOCKLED, HIGH);
        else
            digitalWrite(CAPSLOCKLED, LOW);
          
        if (BootKeyboard.getLeds() & LED_SCROLL_LOCK)
            digitalWrite(SCRLLOCKLED, HIGH);
        else
            digitalWrite(SCRLLOCKLED, LOW);
          
        if (BootKeyboard.getLeds() & LED_NUM_LOCK) 
            digitalWrite(NUMLOCKLED, HIGH);
        else
            digitalWrite(NUMLOCKLED, LOW);
        */
    }
}


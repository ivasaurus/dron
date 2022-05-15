#include <SPI.h>
#include <RF24.h>
#include <nRF24L01.h>

// https://nrf24.github.io/RF24/classRF24.html#ace7dd139fabc16b77cb8325faa07620f
// https://forum.arduino.cc/t/issues-with-leonardo-and-nrf24l01/675099/2
// za Leonarda ovako
// za esp32 je 21, 22????

#define CE_PIN  9
#define CSN_PIN 10

const byte address[6] = "00001";

RF24 radio(CE_PIN, CSN_PIN);

char message[5] = {0};

int yaw;
int pitch;
int roll;
int power;


//===========

/*
 * 0-250 - podatci
 * 254 - pocetak poruke
 * 255 - kraj poruke
 * yaw, pitch, roll, power
 * 
 * 
 */

void setup() {
   Serial.begin(9600);
   delay(3000);
   Serial.println("SimpleRx Starting");
   radio.begin();
   radio.openReadingPipe(1, address);
   radio.startListening();
}

//=============

void loop() {
  if (radio.available()) {
    char c;
    radio.read(&c, 1);
    Serial.println((int)c);
    
    for (int i=0; i<4; i++) {
      message[i] = message[i+1];
    }
    message[4] = c;
    
    if (message[4] == 255) {
      yaw = charToInt(message[0]);
      pitch = charToInt(message[1]);
      roll = charToInt(message[2]);
      power = charToInt(message[3]);

      Serial.print("yaw: ");
      Serial.print(yaw);
      Serial.print(" pitch: ");
      Serial.print(pitch);
      Serial.print(" roll: ");
      Serial.print(roll);
      Serial.print(" power: ");
      Serial.println(power);
    } else {
      //Serial.println("Wrong message");
    }
  }
}

//==============

int charToInt(char x) {
  return (x*4)+1000;
}

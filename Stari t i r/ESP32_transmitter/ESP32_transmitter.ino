#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define CE_PIN  22
#define CSN_PIN 21

RF24 radio(CE_PIN, CSN_PIN);  // CE, CSN

const byte address[6] = "00001";

void setup()
{
  radio.begin();
  

  radio.openWritingPipe(address);
  

  radio.stopListening();
}
void loop()
{
  
  const char text[] = "HOW YOU DOIN"; //message
  radio.write(&text, sizeof(text));
  
  delay(1000);
}

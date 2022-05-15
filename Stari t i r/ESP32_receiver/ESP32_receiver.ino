#include <SPI.h>
#include <RF24.h>
#include <nRF24L01.h>


#define CE_PIN  22
#define CSN_PIN 21

const byte address[6] = "00001";

RF24 radio(CE_PIN, CSN_PIN);

char dataReceived[10]; // this must match dataToSend in the TX
bool newData = false;

//===========

void setup()
{

   Serial.begin(9600);
   delay(3000);
   Serial.println("SimpleRx Starting");
   radio.begin();
   radio.openReadingPipe(1, address);
   radio.startListening();
}

//=============

void loop()
{
   getData();
   showData();
}

//==============

void getData()
{
   if ( radio.available() )
   {
      radio.read( &dataReceived, sizeof(dataReceived) );
      newData = true;
   }
}

void showData()
{
   if (newData == true)
   {
      Serial.print("Data received ");
      Serial.println(dataReceived);
      newData = false;
   }
}

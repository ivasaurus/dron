#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define CE_PIN  7
#define CSN_PIN 8

RF24 radio(CE_PIN, CSN_PIN);  // CE, CSN

int potYaw = 26;
int potRoll = 32;
int potPitch = 33;
int potPow = 25;

const byte address[6] = "00001";

//unsigned long lastMicros = 0;

const int FPS = 250;

int getYaw() {
   int val = map(analogRead(potYaw), 0, 4087, 1000, 2000);
   return val;
}

int getPitch() {
  int val = map(analogRead(potPitch), 0, 4087, 1000, 2000);
  return val;
}

int getRoll() {
  int val = map(analogRead(potRoll), 0, 4087, 1000, 2000);
  return val;
}

int getPower() {
  int val = map(analogRead(potPow), 0, 4087, 1000, 2000);
  return val;
}

char toChar(int x) {
  if (x<1000) {x=1000;}
  if (x>2000) {x=2000;}
  char y = (x-1000)/4;
  return y;
}

void sendMessage() {
  char message[5] = "";

  int yaw = getYaw();
  int pitch = getPitch();
  int roll = getRoll();
  int power = getPower();

  Serial.print("yaw: ");
  Serial.print(yaw);
  Serial.print(" pitch: ");
  Serial.print(pitch);
  Serial.print(" roll: ");
  Serial.print(roll);
  Serial.print(" power: ");
  Serial.println(power);
  
  message[0] = toChar(yaw);
  message[1] = toChar(pitch);
  message[2] = toChar(roll);
  message[3] = toChar(power);
  message[4] = 255;

  radio.write(&message, 5);
}

void setup() {

  Serial.begin(9600);
  
  pinMode(potYaw, INPUT);
  pinMode(potRoll, INPUT);
  pinMode(potPitch, INPUT);
  pinMode(potPow, INPUT);
  
  radio.begin();
 
  radio.openWritingPipe(address);
  
  radio.stopListening();

  //lastMicros = micros();
}
void loop() {
  sendMessage();
  delayMicroseconds(1000000/FPS);
  
} 

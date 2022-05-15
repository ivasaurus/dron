/*
 * ESC to Arduino
 *  narančasta - pin
 *  crvena - 5V
 *  smeđa - GND
 * 
 * 
 *
 */

#include <Servo.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

// =========== RADIO ================

#define CE_PIN  7
#define CSN_PIN 8

const byte address[6] = "00001";

RF24 radio(CE_PIN, CSN_PIN);

char message[5];

// =========== ESC ================

byte escPin_1 = 9;
byte escPin_2 = 10;
byte escPin_3 = 11;
byte escPin_4 = 13;

Servo esc_1;
Servo esc_2;
Servo esc_3;
Servo esc_4;

// =========== DRONE ================

int motor_1_val;
int motor_2_val;
int motor_3_val;
int motor_4_val;

int newYaw;
int newRoll;
int newPitch;
int newPower;

int currentYaw;
int currentRoll;
int currentPitch;
int currentPow;

int readRadio() {
  Serial.println(radio.available());
  if (radio.available()) {
    message[4] = 42;
    radio.read(&message, 5);

    if (message[4] == 255) {
      newYaw = charToInt(message[0]);
      newPitch = charToInt(message[1]);
      newRoll = charToInt(message[2]);
      newPower = charToInt(message[3]);
      Serial.print("Ya, Pi, Ro, Po: ");
      Serial.print(newYaw);
      Serial.print(", ");
      Serial.print(newPitch);
      Serial.print(", ");
      Serial.print(newRoll);
      Serial.print(", ");
      Serial.print(newPower);
      Serial.println();
      return 1;
    }
  }
  return 0;
}

void setMotorValues() {
  motor_1_val = map(newYaw, 0, 250, 1100, 1900);
  motor_2_val = map(newRoll, 0, 250, 1100, 1900);
  motor_3_val = map(newPitch, 0, 250, 1100, 1900);
  motor_4_val = map(newPower, 0, 250, 1100, 1900);
  
}

void updateESCValues() {
  esc_1.writeMicroseconds(motor_1_val);
  esc_2.writeMicroseconds(motor_2_val);
  esc_3.writeMicroseconds(motor_3_val);
  esc_4.writeMicroseconds(motor_4_val);
}

void setup() {
  Serial.begin(9600);
  
  delay(3000);
  Serial.println("Starting radio");
  radio.begin();
  radio.openReadingPipe(1, address);
  radio.startListening();
 
  Serial.println("Starting escs");
  esc_1.attach(escPin_1);
  esc_1.writeMicroseconds(1500);
  esc_2.attach(escPin_2);
  esc_2.writeMicroseconds(1500);
  esc_3.attach(escPin_3);
  esc_3.writeMicroseconds(1500);
  esc_4.attach(escPin_4);
  esc_4.writeMicroseconds(1500);
  
  Serial.println("Waiting 7 seconds to allow esc to recognize the stopped signal");
  delay(7000);
  Serial.println("Starting loop");
}

void loop() {
  readRadio();
  //setMotorValues();
  //updateESCValues();
  
}


int charToInt(char x) {
  return (x*4)+1000;
}

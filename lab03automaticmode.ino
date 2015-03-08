#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_PWMServoDriver.h"

Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor *mymotor = AFMS.getMotor(1);

const int switchPin = 7;
int switchState;
int sensorValue;
const int sensorPin = A0;
int count ;
int turns = 0; 
boolean running=true;

void setup(){
  //set up motor and serial monitor
  Serial.begin(9600);
  AFMS.begin();
  mymotor->setSpeed(200);
  mymotor->run(RELEASE);
}
void loop(){
 switchState = digitalRead(switchPin);
 //currentmillis = millis();
 
if (running && switchState == 0){
  //if not in locked position
   mymotor->setSpeed(200);
   mymotor->run(FORWARD);
   count = 0;
}
else if(running) {
  //if in locked position
  if(count == 0){
    //pause the first time it reaches locked
    mymotor->setSpeed(0);
    mymotor->run(FORWARD);
    delay(500);
    sensorValue = analogRead(sensorPin);
    //scan the petri dish and display results
    if (sensorValue <= 400){
      Serial.println("This petri dish is occupied with material");
    }
    else{
      Serial.println("This petri dish is empty");
    }
    delay(500);
    turns++;
    count=+1;
  }
  //move on to the next plate
  mymotor->setSpeed(200);
  mymotor->run(FORWARD);
}
if (turns >= 4){
  //stop after all petri dishes are scanned. 
   mymotor->setSpeed(0);
   mymotor->run(FORWARD); 
   running=false;
}
}


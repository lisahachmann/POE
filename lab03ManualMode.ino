byte posit = 0;
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_PWMServoDriver.h"

Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor *mymotor = AFMS.getMotor(1);

unsigned long prevmillis = 0;
unsigned long currentmillis;
const int switchPin = 7;
int switchState;
int sensorValue;
const int sensorPin = A0;
int count ;
int turns = 0; 
int pos = 0;
int lastpos = 0; 
int gopos;
boolean running=true;

void setup() 
{
  Serial.begin(9600);
  while (! Serial);  //Wait for serial to be ready/opened
  Serial.println("Enter Petri Dish Number 0 to 4 or 'x' to clear");
  AFMS.begin(); //intialize motor
  mymotor->setSpeed(200);
  mymotor->run(RELEASE);
}

void loop() 
{
  if (Serial.available())
  {
    //Input through serial monitor
    char ch = Serial.read();
    if (ch >= '0' && ch <= '4')
    {
      pos = ch - '0';
      if (pos > 0){
        running = true;
      }
      bitSet(posit, pos);
    }
    if (ch == 'x')
    {
      posit = 0;
      Serial.println("Cleared");
    }
  }
  switchState = digitalRead(switchPin);
if (pos  > lastpos){
  //Ex: If going to position 4 from position 2
     gopos = pos-lastpos;
     mymotor->setSpeed(200);
     mymotor->run(FORWARD);
}
if (pos < lastpos){
  //Ex: If going to position 1 from position 2
  gopos = lastpos - pos;
  gopos = map(gopos, 1, 3, 3, 1);
  mymotor->setSpeed(200);
  mymotor->run(FORWARD);
   }
if (pos == lastpos){
  //Ex: If calling for position 1 from position 1
  mymotor->setSpeed(0);
  mymotor->run(FORWARD);
  gopos = 0;
}  
if (running && switchState == 0){
  //If scanner isn't in a possibly locked position
   count = 0;
}
else if(running) {
  //If petri dish is possibly ready to lock into place
  if(count == 0){
    turns++;
    count=+1;
  }
  //keep going because the desired position moves isn't done
  mymotor->setSpeed(200);
  mymotor->run(FORWARD);
  
}
if (turns == gopos){
  //The desired position is here
   mymotor->setSpeed(0);
   mymotor->run(FORWARD); 
   running=false;
    sensorValue = analogRead(sensorPin);
    //read and display sensor results
   if (sensorValue <= 400){
    Serial.println("This petri dish is occupied with material");
      }
   else{
      Serial.println("This petri dish is empty");
     }
    turns = 0;
    //be ready for the next input
    lastpos = pos;
    Serial.flush();
    while(!Serial.available()) ;
}
}


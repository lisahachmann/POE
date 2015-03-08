#include <Servo.h>
Servo servotilt;
Servo servopan;
int pos = 0;
int tiltpos = 45;
int x; 

void setup(){
  Serial.begin(9600);
  servotilt.attach(9);
  servopan.attach(11);
}


void loop(){ 
  //Data will be sent through serial monitor as:
  // pos, tiltpos, x 
  // (where x is the data from the IR sensor)
  while (pos < 120)
  {
    //Take data for the serial monitor while pan servo is going 
    //forwards, from 0-120 degrees
    servopan.write(pos);
    pos +=1;
    //Serial.print("Position: ");
    Serial.print(pos);
    Serial.print(',');
    Serial.print(tiltpos);
    Serial.print(',');
    x = analogRead(2);
    Serial.print(x);
    Serial.println(',');
    //Serial.println('X');
    
    delay(10);
  }
    //Change the tilt servo position every time the pan servo 
    //has reached 120 degrees
    //Also take data for the serial monitor 
    tiltpos -= 3;
    servotilt.write(tiltpos);
    Serial.print(pos);
    Serial.print(',');
    Serial.print(tiltpos);
    Serial.print(',');
    x = analogRead(2);
    Serial.print(x);
    Serial.println(',');
    
    delay(5);
  
  while (pos > 0)
  {
    //Take data for the serial monitor while pan servo is going
    //backwards, from 120-0 degrees
    servopan.write(pos);
    Serial.print(pos);
    Serial.print(',');
    Serial.print(tiltpos);
    Serial.print(',');
    x = analogRead(2);
    Serial.print(x);
    Serial.println(',');
    
    pos -=1;
    delay(10);
  }
    //Change the tilt servo position every time the pan servo 
    //has reached 120 degrees
    //Also take data for the serial monitor 
    tiltpos -=3;
    servotilt.write(tiltpos);
    Serial.print(pos);
    Serial.print(',');
    Serial.print(tiltpos);
    Serial.print(',');
    x = analogRead(2);
    Serial.print(x);
    Serial.println(',');
    
    delay(5);
  
}





#include <Servo.h>


#define pinServo1 10
#define pinServo2 9
#define pot_servo A8
#define green A12
#define red A13

Servo servo1;
Servo servo2;

int x;

void setup() {
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  servo1.attach(pinServo1);
  servo2.attach(pinServo2);
  Serial.begin(9600);
}

void loop() {
  x = analogRead(pot_servo);
  x = map(x, 0, 1023, 0, 180);
  if (x >160){
    analogWrite(green, x);
  }else{
    analogWrite(red, x);
    }
  servo1.write(x);
  servo2.write(x);
  Serial.println(x);
  delay(1000);
}

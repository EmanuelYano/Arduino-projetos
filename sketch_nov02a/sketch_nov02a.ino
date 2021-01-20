#include <Servo.h>


#define pinServo1 8
#define pinServo2 9

Servo servo1;
Servo servo2;

void setup() {

   servo1.attach(pinServo1);
   servo2.attach(pinServo2);
   Serial.begin(9600);
}

void loop() {
  for (int i=1; i<10; i++){
    servo1.write(0);
    servo2.write(0);
    delay(1000);
    servo1.write(90);
    servo2.write(90);
    delay(1000);
    servo1.write(180);
    servo2.write(180);
    delay(1000);
    i = i - 1;
  }
  delay(100);

}

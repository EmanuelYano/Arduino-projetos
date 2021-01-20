#include <AFMotor.h>

double passos_total = 2048; 
 
int porta_motor = 2, x;

int angulo = 360; 
 
void setup() {
  // put your setup code here, to run once:
   motor_de_passo.setSpeed(10);
   Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
    motor_de_passo.step(passos_total, FORWARD, DOUBLE);
    motor_de_passo.release();
}

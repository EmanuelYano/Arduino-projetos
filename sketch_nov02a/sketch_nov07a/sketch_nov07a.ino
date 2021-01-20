#include <AFMotor.h>

double passos_total = 2048; 
 
int porta_motor = 2, x;

int angulo = 360; 
 

  
AF_Stepper motor_de_passo(passos_total, porta_motor);
 
void setup()
{
  motor_de_passo.setSpeed(10);

  Serial.begin(9600);
}
 
void loop()
{

  Serial.print("Numero de passos : ");

  //FORWARD  sentido horario <---> BACKWARD  anti-horario
  motor_de_passo.step(passos_total, BACKWARD, DOUBLE);
  motor_de_passo.release();
 
  delay(500);
}

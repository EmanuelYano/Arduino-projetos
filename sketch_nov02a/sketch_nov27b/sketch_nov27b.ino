#include <AFMotor.h>
#include <Servo.h>

int x,y;

//Motores
AF_DCMotor motor1(1); 

//Servos
#define pinServo1 10
#define pinServo2 9

Servo servo1;
Servo servo2;

int porta_motor = 2, angulo = 360;
double passos_total = 2048;
AF_Stepper motor_de_passo(passos_total, porta_motor);

//botoes
#define but A9

//potenciometros
#define pot_1 A12
#define pot_2 A15

#define led 25

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  motor_de_passo.setSpeed(10);
  servo1.attach(pinServo1);
  servo2.attach(pinServo2);
  pinMode(but, INPUT);
  pinMode(led, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
   int bot = analogRead(but);
   Serial.println(bot);
   delay(100);
   x = analogRead(pot_1);
   y = analogRead(pot_2);
   x = map(x, 0, 1023, 0, 180);
   y = map(y, 0, 1023, 0, 180);
   Serial.println(x);
   Serial.println(y);
   
   if (bot > 140 && bot < 160){ // liga motor dc sentido horario
      digitalWrite(led, HIGH);
      motor1.setSpeed(255);
      motor1.run(FORWARD); //FORWARD - BACKWARD - RELEASE 
      delay(5000);
      
    }else if (bot > 161 && bot < 180){ //liga motor sentido anti-horario
       motor1.setSpeed(255);
       motor1.run(BACKWARD);       
       delay(5000);
       
      }else if  (bot > 190 && bot < 215){ //desliga motor
        digitalWrite(led, LOW);
        motor1.setSpeed(0);
        motor1.run(RELEASE);
        delay(5000);
        
        }else if  (bot > 240 && bot < 260){  //ligar motor de passo sentido horario
          motor_de_passo.step(passos_total, FORWARD, DOUBLE);
          motor_de_passo.release();
          while (true == true){
            digitalWrite(led, HIGH);
            delay(500);
            digitalWrite(led, LOW);
            delay(500);
          }
          }else if (bot > 330 && bot < 350){ // ligar moto de passo sentido anti-horario
            motor_de_passo.step(passos_total, BACKWARD, DOUBLE);
            motor_de_passo.release();
            while (true == true){
              digitalWrite(led, HIGH);
              delay(300);
              digitalWrite(led, LOW);
              delay(300);
            }            
            }else if (bot > 500 && bot < 520){ // desligar motor de passo ou parada momentanea
              passos_total = passos_total - passos_total;
              motor_de_passo.step(passos_total, RELEASE, DOUBLE);
              motor_de_passo.release();
              while(true == true){
                digitalWrite(led, HIGH);
                delay(100);
                digitalWrite(led, LOW);
                delay(100);
              }
             }
    servo1.write(x);
    delay(100);
    servo2.write(y);
    delay(100);
}

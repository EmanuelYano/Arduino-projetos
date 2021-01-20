//incluir bibliotecas
#include <SoftwareSerial.h>
#include <Servo.h>
 
SoftwareSerial esp8266(19, 18); //definir pino RX = 5 e TX = 4 (do ESP8266)
 
//definir variáveis
#define DEBUG true //mostrar as mensagens do ESP8266 no Serial Monitor
#define SERV1 3  //servo 1 na porta digital 9
#define SERV2 10 //servo 2 na porta digital 10
 
Servo s1; //servo 1
Servo s2; //servo 2
int pos1 = 170; //posição atual do servo 1
int pos2 = 170; //posição atual do servo 2
int vel = 10; //velocidade dos servos (100 -> 90º in 1 s)(1 -> 90º in 9 s)
int pos1min = 20; //posição mínima do servo 1
int pos2min = 20; //posição mínima do servo 2
int pos1max = 160; //posição máxima do servo 1
int pos2max = 160; //posição máxima do servo 2
 
 
//*****************
// Setup do Arduino
//*****************
void setup()
{
 
  //definir servos e definir posição inicial
  s1.attach(SERV1);
  s2.attach(SERV2);
  s1.write(pos1max);
  s2.write(pos2max);
  s1.detach();
  s2.detach();
 
  //iniciar comunicação serial
  Serial.begin(9600);
  esp8266.begin(19200);
 
  sendData("AT+RST\r\n", 2000, DEBUG); //resetar modulo
  sendData("AT+CWMODE=1\r\n", 1000, DEBUG); //definir modo station
  sendData("AT+CWJAP=\"XXXXX\",\"YYYYY\"\r\n", 2000, DEBUG);   //conectar rede wi-fi
  while(!esp8266.find("OK")) { //aguardar conexão
  } 
  sendData("AT+CIFSR\r\n", 1000, DEBUG); //mostrar endereço IP
  sendData("AT+CIPMUX=1\r\n", 1000, DEBUG); //permitir múltiplas conexões
  sendData("AT+CIPSERVER=1,80\r\n", 1000, DEBUG); //iniciar web server na porta 80
}
 
//***************
// Loop Principal
//***************
void loop()
{
  if (esp8266.available())  //verificar se existem dados disponíveis no ESP8266
  {
    if (esp8266.find("+IPD,")) //se houver um novo comando
    {
      String msg;
      esp8266.find("?"); //correr o cursor até encontrar o conteúdo da mensagem
      msg = esp8266.readStringUntil(' '); //ler a mensagem
      String command = msg.substring(0, 3); //os comandos são informados nos três primeiros caracteres. "sr1" = comando para o servo #1 e "sr2" = comando para o servo #2
      String valueStr = msg.substring(4);   //os 3 caracteres seguintes informam o ângulo desejado
      int value = valueStr.toInt();
      if (DEBUG) {
        Serial.println(command);
        Serial.println(value);
      }
      delay(100);
 
      //****************
      // mover os servos
      //****************
 
      //mover o servo1 para o Ângulo desejado
      if(command == "sr1") {
        //limitar o ângulo
        if (value >= pos1max) {
          value = pos1max;
        }
        if (value <= pos1min) {
          value = pos1min;
        }
        s1.attach(SERV1);
        while(pos1 != value) {
          if (pos1 > value) {
            pos1 -= 1;
            s1.write(pos1);
            delay(100/vel);
          }
          if (pos1 < value) {
            pos1 += 1;
            s1.write(pos1);
            delay(100/vel);
          }
        }
        s1.detach();
      }
 
      //mover o servo2 para o ângulo desejado
      if(command == "sr2") {
        //limitar o ângulo
        if (value >= pos2max) {
          value = pos2max;
        }
        if (value <= pos2min) {
          value = pos2min;
        }
        s2.attach(SERV2);
        while(pos2 != value) {
          if (pos2 > value) {
            pos2 -= 1;
            s2.write(pos2);
            delay(100/vel);
          }
          if (pos2 < value) {
            pos2 += 1;
            s2.write(pos2);
            delay(100/vel);
          }
        }   
        s2.detach();     
      } 
    }
  }
}
 
 
//********************
// Funções auxiliares
//********************
 
//Enviar dados para o ESP8266
String sendData(String command, const int timeout, boolean debug)
{
  String response = "";
  esp8266.print(command);
  long int time = millis();
  while ( (time + timeout) > millis())
  {
    while (esp8266.available())
    {
      char c = esp8266.read();
      response += c;
    }
  }
  if (debug)
  {
    Serial.print(response);
  }
  return response;
}

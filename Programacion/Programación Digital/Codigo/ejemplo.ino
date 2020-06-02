// Dimmer Bluetooth Arduino_Control_House
// Descargar App: https://play.google.com/store/apps/details?id=appinventor.ai_el_profe_garcia.Arduino_Control_House_2
// By: http://elprofegarcia.com


#include <Servo.h> 
Servo servo1;         // Crea el servo1 con las librerias de Servo.h

int estado=0;
int analogo=0;
int luz_int=6400;   // Variable del tiempo de disparo del Deslizador 1 (Dimmer)
int mot_int=6450;   // Variable del tiempo de disparo del Deslizador 2 (Dimmer)
int time_int=0;     // Tiempo de diferencia entre los dos Deslizadores

void setup() {
  servo1.attach(7);  //conexion del servo por pin 7
  pinMode(13,OUTPUT);
  pinMode(12,OUTPUT);
  pinMode(11,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(8,OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(4 ,OUTPUT);
  pinMode(3,OUTPUT);
  Serial.begin(9600);
  attachInterrupt(0,interrupcion0,RISING);  // Interrupcion 0 (pin2) 
}                                           // LOW, CHANGE, RISING, FALLING
 
void loop() {
   if(Serial.available()>0){           // Si el puerto serie esta habilitado
        estado = Serial.read();       // Lee lo que llega por el puerto Serie
 }

  if(estado== 'a'){                    // on/off de los pin 13 al pin 6
       digitalWrite(13,HIGH);
 }
 if(estado== 'b' ){
       digitalWrite(13,LOW);
 }
 if(estado== 'c'){ 
       digitalWrite(12,HIGH);
 }
 if(estado== 'd' ){
       digitalWrite(12,LOW);
 }
 if(estado== 'e'){ 
       digitalWrite(11,HIGH);
 }
 if(estado== 'f' ){
       digitalWrite(11,LOW);
 }
 if(estado== 'g' ){
       digitalWrite(10,HIGH);
 }
 if(estado== 'h' ){
       digitalWrite(10,LOW);
 }
 if(estado== 'i' ){
        digitalWrite(9,HIGH);
 }
 if(estado== 'j' ){
       digitalWrite(9,LOW);
      }
 if(estado== 'k' ){
        digitalWrite(8,HIGH);
 }
 if(estado== 'l' ){
      digitalWrite(8,LOW);
 }
 if(estado== 'm' ){
       digitalWrite(7,HIGH);
 }
 if(estado== 'n' ){
       digitalWrite(7,LOW);
 }
 if(estado== 'o' ){
      digitalWrite(6,HIGH);
 }
 if(estado== 'p' ){
       digitalWrite(6,LOW);
 }
 if(estado== 'A' ){      // Movimiento del Servo
      servo1.write(0);  
      }
 if(estado== 'B' ){
      servo1.write(90); 
      }
 if(estado== 'C' ){
      servo1.write(180);  
      }
 if(estado=='s') mot_int = 6350;  // Los 8 saltos del Deslizador 2 (Dimmer)
 if(estado=='t') mot_int = 6250; 
 if(estado=='u') mot_int = 5750;  
 if(estado=='v') mot_int = 5450;  
 if(estado=='w') mot_int = 5150;  
 if(estado=='x') mot_int = 4850; 
 if(estado=='y') mot_int = 4550; 
 if(estado=='z') mot_int = 3550; 
 
 if(estado=='1') luz_int = 6300;   // Los 8 saltos del Deslizador 1 (Dimmer)
 if(estado=='2') luz_int = 6100;  
 if(estado=='3') luz_int = 5200;  
 if(estado=='4') luz_int = 4900;  
 if(estado=='5') luz_int = 4500; 
 if(estado=='6') luz_int = 4100; 
 if(estado=='7') luz_int = 3500;  
 if(estado=='8') luz_int = 3000; 

if(estado=='q'){         // envia el valor leido del puerto analogo A0
  analogo=analogRead(A0);
  Serial.print(analogo);
  Serial.println("C");
  estado=0;
 }

}
 
void interrupcion0()    // Funcion que se ejecuta durante cada interrupion
{
  if (mot_int >= luz_int){        // Determina cual es mayo y encuentra el tiempo de la diferencia 
    time_int = mot_int - luz_int;
    delayMicroseconds(luz_int); 
    digitalWrite(3,HIGH);
    delayMicroseconds(time_int);
    digitalWrite(5,HIGH);
  }
  if (mot_int <= luz_int){
    time_int = luz_int - mot_int;
    delayMicroseconds(mot_int);
    digitalWrite(5,HIGH);
    delayMicroseconds(time_int);
    digitalWrite(3,HIGH);
  }

  delayMicroseconds(100);
  digitalWrite(5,LOW);
  digitalWrite(3,LOW);
 
}

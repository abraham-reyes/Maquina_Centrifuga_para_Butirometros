int mot_int = 6450; // Variable del tiempo de disparo del Deslizador 2 (Dimmer)
int estado = 'c';
int waitTime = 0;
int delayTime = 0;

void setup() {
  pinMode(3, OUTPUT); // RELAY
  pinMode(5, OUTPUT); // ENTRADA TRIAC
  Serial.begin(9600);
  attachInterrupt(0, interrupcion0, RISING); // Interrupcion 0 (pin2)
}
void loop() {
  if (Serial.available() > 0) {       // Si el puerto serie esta habilitado
    estado = Serial.read();       // Lee lo que llega por el puerto Serie
  }
  if (estado == 'c') {//Paro de emergencia
    digitalWrite(3, LOW);
    digitalWrite(5, LOW);
  }
  if (estado == 'a') {//Activar motor
    digitalWrite(3, HIGH);
  } else if (estado == 'b') {
    digitalWrite(3, LOW);
  } else {
    estado == 'c';
  }

  if (estado == 's') mot_int = 6350; // Los 8 saltos del Deslizador 2 (Dimmer)
  if (estado == 't') mot_int = 6250;
  if (estado == 'u') mot_int = 5750;
  if (estado == 'v') mot_int = 5450;
  if (estado == 'w') mot_int = 5150;
  if (estado == 'x') mot_int = 4850;
  if (estado == 'y') mot_int = 4550;
  if (estado == 'z') mot_int = 3550;

  if (estado == 'd') waitTime = 22.5; // Los 8 saltos del tiempo hasta 3 min max (180s)
  if (estado == 'e') waitTime = 45;
  if (estado == 'f') waitTime = 67.5;
  if (estado == 'g') waitTime = 90;
  if (estado == 'h') waitTime = 112.5;
  if (estado == 'i') waitTime = 135;
  if (estado == 'j') waitTime = 157.5;
  if (estado == 'k') waitTime = 180;

}
void interrupcion0()    // Funcion que se ejecuta durante cada interrupion
{
  delayTime = waitTime * 1000;
  if (digitalRead(3) == HIGH  && delayTime > 0)  {
    delayMicroseconds(mot_int);
    digitalWrite(5, HIGH);
  }

  delay(delayTime);
  digitalWrite(5, LOW);
  digitalWrite(3, LOW);
  delayTime = 0;
  waitTime = 0;
}

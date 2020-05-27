
#define DETECT 2  //Detección del cruce por zero
#define GATE 9    //Gate del Triac
#define PULSE 10   //Ancho de pulso del disparo (conteos)
int i=70,val=0,y;
int analogPin = 0;

void setup(){
  Serial.begin(9600);
  pinMode(DETECT, INPUT);     //zero cross detect
  digitalWrite(DETECT, HIGH); //enable pull-up resistor
  pinMode(GATE, OUTPUT);      //triac gate control

  // set up Timer1
  //(see ATMEGA 328 data sheet pg 134 for more details)
  OCR1A = 100;      //initialize the comparator
  TIMSK1 = 0x02;    //enable comparator A and overflow interrupts PAGINA 184 DATA SHEET
  TCCR1A = 0x00;    //timer control registers set for   PAGINA 170 DATA SHEET
  TCCR1B = 0x00;    //normal operation, timer disabled  PAGINA 173 DATA SHEET
  TCCR1B = 0x04;    //start timer with divide by 256 input


  // set up zero crossing interrupt
  attachInterrupt(0,zeroCrossingInterrupt,CHANGE); 
    //IRQ0 is pin 2. Call zeroCrossingInterrupt
    //on rising signal

}

//Interrupt Service Routines

void zeroCrossingInterrupt(){ //detección de cruce por cero
  val = digitalRead(DETECT);   // lectura del pin de entrada
  switch (val)
  {   case 0:
      digitalWrite(GATE,LOW);
     
       break;
     case 1:
    // digitalWrite(GATE,HIGH);
     // TCCR1B=0x04; //start timer with divide by 256 input
    TCNT1 = 0;   //reset timer - count from zero
     break;
  } 

}

ISR(TIMER1_COMPA_vect){ //comparator match
   val = digitalRead(DETECT);   // read the input pin
  switch (val)
  {   case 0:
      digitalWrite(GATE,LOW);
     break;
     case 1:
      digitalWrite(GATE,HIGH);  //set triac gate to high
     break;
  } 

}

ISR(TIMER1_OVF_vect){ //timer1 o
 // digitalWrite(GATE,LOverflowW); //turn off triac gate
  TCCR1B = 0x00;          //disable timer stopd unintended triggers
}

void loop(){ // sample code to exercise the circuit
 val = analogRead(analogPin);
 delay(100);
 y = map(val, 0, 1023, 475, 1);
 
  //Serial.print(val);             // debug value                
  //Serial.print("---");
  //Serial.println(y);
  // OCR1A = y ;

}

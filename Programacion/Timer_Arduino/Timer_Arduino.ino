#include <LiquidCrystal.h> //Libreria del display LCD
#define TONO_ERROR 600
#define TIME_INTERVAL 3000

LiquidCrystal lcd(7, 8, 9, 10, 11, 12); //Inicializamos la libreria con el numero de los pines a utilizar

int buzzer = 5;            //Alarma
int aminutos = 0;          //Variable a mostrar por LCD de los minutos
int asegundos = 0;         //Variable a mostrar por LCD de los segundos
int segundostotal = 0;     //Tiempo total
int msg= 0;                //Barrera para el mensaje de bienvenida
int start = A1;            //Pulsador de arranque
int empieza = 1024;        // Variable para almacenaje del pulsador de arranque
int butm = A4;             //Pulsador de Minutos
int buts = A3;             //Pulsador de segundos
int varbutm = 0;           //Variable para almacenar el valor del pulsador de minutos
int varbuts = 0;           //Variable para almacenar el valor del pulsador de segundos

void setup()
{
   lcd.begin(16, 2);         // Configuramos el numero de columnas y filas del LCD. 
  
   pinMode(buzzer, OUTPUT);  //Pin de alarma --> Salida
   pinMode(butm, INPUT);     //Pin de pulsador de minutos --> Entrada
   pinMode(buts, INPUT);     //Pin de pulsador de segundos --> Entrada
   pinMode(start, INPUT);    //Pin de pulsador de arranque --> Entrada
  
   msg = 0;                  //Barrera del mensaje de bienvenida
   empieza = 1024;           //Barrera de arranque

   varbutm = 1;              //Barrera de minutos
   varbuts = 1;              //Barrera de segundos  
   Serial.begin(9600);
}

void loop()
{
     if(msg==0)             //Mostramos el mensaje de bienvenida solo una vez
     {
       lcd.setCursor(0,0);
       lcd.print("Temporizador con");
       lcd.setCursor(1,1);
       lcd.print("Tiempo centrifuga");
       delay(2500);
       msg = 1;
       lcd.clear();
     }
    
     //-------------------------------------------------------------------------------------------------    
     // LECTURA DE LOS BOTONES Y ELECCIÓN DEL TIEMPO, NO SALE DEL BUCLE HASTA PULSAR
     // EL BOTON DE ARRANQUE
     //-------------------------------------------------------------------------------------------------
    
     do                  
     {
       varbutm = analogRead(butm);   //Leemos boton de minutos
       varbuts = analogRead(buts);   //Leemos boton de segundos
      
        if(varbutm > 0)            //Si el boton ha sido pulsado, aumentamos los minutos en una unidad
       {
         aminutos = aminutos + 1;
         if(aminutos == 60) aminutos = 0;
         delay(250);
       } 
      
        if(varbuts > 0)            //Si el boton ha sido pulsado, aumentamos los segundos en una unidad
       {
         asegundos = asegundos + 1;
         if(asegundos == 60) asegundos = 0;
         delay(250);
       } 
            
       lcd.setCursor(0,0);
       lcd.print("Elige el tiempo");  //Muestra mensaje y las HH:MM:SS que vayamos aumentando
       lcd.setCursor(4,1);    

      if (aminutos < 10) lcd.print("0");  // Si los minutos son menor que 10, pone un "0" delante.
       lcd.print(aminutos);               // Sin este codigo, se muestra asi: H:M:S  (H:1:S)


       lcd.print(":");
      if (asegundos < 10) lcd.print("0"); // Si los segundos son menor que 10, pone un "0" delante.
       lcd.print(asegundos);              // Sin este codigo, se muestra asi: H:M:S  (H:M:1)
      
      
     } while(analogRead(start) == 0);  // Se repite el menu de elegir tiempo hasta que pulsemos el boton de arranque.
     
    segundostotal = asegundos + (aminutos * 60);  //Convierte el tiempo elegido en segundos!!
      
      //-------------------------------------------------------------------------------------------------
      // UNA VEZ PULSADO EL BOTON DE ARRANQUE Y ACUMULADO EL TIEMPO, ENTRA EN EL SIGUIENTE WHILE
      // Y NO FINALIZA HASTA TERMINAR LA CUENTA.
      //-------------------------------------------------------------------------------------------------

      while (segundostotal > 0)
      {
        delay (1000);          //Descontamos en periodos de 1 segundo
        segundostotal--;    
        
        aminutos = (segundostotal / 60) % 60;  //Convertimos los segundos totales en minutos
        asegundos = segundostotal % 60;        //Convertimos los segundos totales en periodos de 60 segundos

        lcd.setCursor(0,0);
        lcd.print("Tiempo restante");        //Mostramos mensaje de tiempo restante

        if (aminutos < 10) lcd.print("0");   // Si los minutos son menor que 10, pone un "0" delante.
        lcd.print(aminutos);                 // Sin este codigo, se muestra asi: H:M:S  (H:1:S)


        lcd.print(":");
        if (asegundos < 10) lcd.print("0");  // si el valor de segundo esta por debajo de 9 (unidad) antepone un cero
        lcd.print(asegundos);                // Sin este codigo, se muestra asi: H:M:S  (H:M:1)
       
          if (segundostotal == 0)            //Si finaliza el tiempo
          {          
             while(1)                        //Bucle infinito mostrando mensaje y haciendo parpadear un led
             {              
                  lcd.clear();
                  lcd.setCursor(5,0);
                  lcd.print("Tiempo");
                  lcd.setCursor(3,1);
                  lcd.print("Finalizado");
                
               
                 sonarTono(TONO_ERROR,TIME_INTERVAL);
                 exit(0);
             }     
          }
     }  
}
    //------------------------------------
    // SONAR TONO
    //------------------------------------
    void sonarTono(int tono, int duracion)
    {
      tone(buzzer,tono,duracion);
      delay(duracion);
    }

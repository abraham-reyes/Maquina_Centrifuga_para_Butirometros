#include <Keypad.h> //llama a la librería Keypad.h
#include <LiquidCrystal.h>
#include <Wire.h>      // libreria de comunicacion por I2C
#include <LiquidCrystal_I2C.h>    // libreria para LCD por I2C

LiquidCrystal_I2C lcd(0x27, 16, 4);


/////////////////TECLADO//////////////////////////////////////////////////////////////////////////////////////////////
const byte ROWS = 4; //Numero de filas del teclado que se esta usando
const byte COLS = 4; //Numero de columnas del teclado que se esta usando

char hexaKeys[ROWS][COLS] =  //Aquí pondremos la disposición de los caracteres tal cual están en nuestro teclado
{
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {9, 8, 7, 6}; //Seleccionamos los pines en el arduino donde iran conectadas las filas
byte colPins[COLS] = {5, 4, 3, 2}; //Seleccionamos los pines en el arduino donde iran conectadas las filas

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); //inicializa el teclado
char tecla;
/////////////////TECLADO//////////////////////////////////////////////////////////////////////////////////////////////

////////////////     LCD   ///////////////////////////////////////////////////////////////////////////////////////////
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
////////////////     LCD   ///////////////////////////////////////////////////////////////////////////////////////////
void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
}

void loop() {
  tecla = customKeypad.getKey();
  if (tecla) {
    switch (tecla) {
        SubMenu1();
    }
  }
}


///////////////////MENUS/////////////////////////////
void SubMenu1() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Time :");
  lcd.setCursor(0, 1);
  lcd.print("RPM :");
  delay(100);
  SubMenu2();
}
////////////////////////////////////////////////////
void SubMenu2() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("¿Quieres continuar?");
  lcd.setCursor(0, 1);
  lcd.print("Si(*)   No(#)");
  delay(100);
  tecla = customKeypad.getKey();
  if (tecla) {
    switch (tecla) {
      case '*':
        SubMenu3();
        break;
      case'#':
        SubMenu1();
        break;
    }
  }
}
////////////////////////////////////////////////////
void SubMenu3() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Colacando seguro");
  delay(1000);
  tecla = customKeypad.getKey();
  if (tecla) {
    switch (tecla) {
      case 'B':
        lcd.setCursor(0, 0);
        lcd.print("Ingrese Tiempo");
        lcd.setCursor(0, 1);
        lcd.print("Ingrese RPM");
        delay(1000);
        break;
    }
  }
}

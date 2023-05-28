#include "Keypad.h"
#include "stdio.h"
#include "stdlib.h"

//Declaraciones de pinout.
const int c3      = D4;
const int f1      = D0;
const int f2      = D5;
const int f3      = D6;
const int c1      = D7;
const int c2      = D8;
const int f4      = D1;
const int relay   = D2;
const int Error   = D3;

//Declaraciones de teclado matricial.
const short int largopassword = 10;  //determina el largo de la passwordaseña superior (si no es igual tendra problema de funcionamiento)
const char PASSWORD[largopassword] = { '1', '1', '4', '7', '7', '9', '1', '7', '4', '4'};  //modiicar estos numeros para cambiar la passwordaseña

char key;
const int cantidadFilas = 4; //cuatro filas
const int cantidadColumnas = 3; //cuatro columna
byte pinFilas[cantidadFilas] = {f1,f2,f3,f4}; //este es el pinout de las filas del teclado
byte pinColumnas[cantidadColumnas] = {c1,c2,c3}; //este es el pinout de las columnas del teclado

char teclas[cantidadFilas][cantidadColumnas] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};
Keypad keypad = Keypad( makeKeymap(teclas), pinFilas, pinColumnas, cantidadFilas, cantidadColumnas );

int initGPIO (void){
  /*
  pinMode(t1,INPUT_PULLUP);
  pinMode(t2,INPUT_PULLUP);
  pinMode(t3,INPUT_PULLUP);
  pinMode(t4,INPUT_PULLUP);
  pinMode(t5,INPUT_PULLUP);
  pinMode(t6,INPUT_PULLUP);
  pinMode(t7,INPUT_PULLUP);
  */
  pinMode(relay,OUTPUT);
  pinMode(Error,OUTPUT);
  return 0;
}
int checkPassword(void) {
  Serial.println("Lectura de password");
  char password[largopassword];

  for (int i = 0; i < largopassword; i++) {
    password[i] = keypad.waitForKey();
    Serial.print("Tecla Presionada: "); Serial.println(password[i]);
    if (PASSWORD[i] != password[i]) {
      return 1;
      Serial.println("ERROR, return salteado");
    }
  }
  return 0;
  Serial.println("ERROR, return salteado");
}

void setup() {
  Serial.begin(74880);
  Serial.println("Starting Protocols...");
  if(initGPIO ()){
    Serial.println("GPIO PROTOCOL FAILED...");
  }
  digitalWrite(relay,HIGH); Serial.println("Relay encendido: Electroiman Activado...");  
}

void loop() {
  if(checkPassword() == 0){
    digitalWrite(relay,LOW); Serial.println("Relay Apagado: Electroiman Desactivado...");
  }else Serial.println("Digito Incorrecto."); 
  digitalWrite(Error,HIGH); delay(200); digitalWrite(Error,LOW);
}
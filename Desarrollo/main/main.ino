#include "Keypad.h"

//Declaraciones de pinout.
const int t1      = A0;
const int t2      = D0;
const int t3      = D5;
const int t4      = D6;
const int t5      = D7;
const int t6      = D8;
const int t7      = D1;
const int relay   = D3;
const int Error   = D2;

//Declaraciones de teclado matricial.
const short int largopassword = 10;  //determina el largo de la passwordaseña superior (si no es igual tendra problema de funcionamiento)
const char PASSWORD[largopassword] = { '8', '4', '5', '5', '6', '6', '8', '5', '5', '4'};  //modiicar estos numeros para cambiar la passwordaseña

char key;
const int cantidadFilas = 4; //cuatro filas
const int cantidadColumnas = 3; //cuatro columna
byte pinFilas[cantidadFilas] = {t1,t2,t3,t4}; //este es el pinout de las filas del teclado
byte pinColumnas[cantidadColumnas] = {t5,t6,t7}; //este es el pinout de las columnas del teclado

char teclas[cantidadFilas][cantidadColumnas] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};
Keypad keypad = Keypad( makeKeymap(teclas), pinFilas, pinColumnas, cantidadFilas, cantidadColumnas );

int initGPIO (void){
  pinMode(t1,INPUT_PULLUP);
  pinMode(t2,INPUT_PULLUP);
  pinMode(t3,INPUT_PULLUP);
  pinMode(t4,INPUT_PULLUP);
  pinMode(t5,INPUT_PULLUP);
  pinMode(t6,INPUT_PULLUP);
  pinMode(t7,INPUT_PULLUP);
  pinMode(relay,OUTPUT);
  pinMode(Error,OUTPUT);
  return 0;
}
int checkPassword(void) {
  Serial.println("Lectura de password");
  char password[largopassword];

  for (int i = 0; i < largopassword; i++) {
    password[i] = keypad.getKey();
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
  key = keypad.getKey();
  if(checkPassword() == 0){
    digitalWrite(relay,LOW); Serial.println("Relay Apagado: Electroiman Desactivado...");
  }else Serial.println("Digito Incorrecto.");
}
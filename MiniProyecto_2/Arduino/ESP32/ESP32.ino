//Universidad del Valle de Guatemala
//EJEMPLO DE ADAFRUIT EN ARDUINO
//ADAPTACION PARA MINIPROYECTO 2
//SANTIAGO SEBASTIAN GALICIA REYES
//CARNET 18483
//IE3027- ELECTRONICA DIGITAL 2

//Ayuda en https://www.arduino.cc/reference/es/
//Para mas ayuda en https://www.arduino.cc/en/Tutorial/HomePage



// Adafruit IO Publish Example
//
// Adafruit invests time and resources providing this open source code.
// Please support Adafruit and open source hardware by purchasing
// products from Adafruit!
//
// Written by Todd Treece for Adafruit Industries
// Copyright (c) 2016 Adafruit Industries
// Licensed under the MIT license.
//
// All text above must be included in any redistribution.

/************************** Configuration ***********************************/

// edit the config.h tab and enter your Adafruit IO credentials
// and any additional configuration needed for WiFi, cellular,
// or ethernet clients.
#include "config.h"
//aqui le ponemos la clave de internet y de la configuracion del dashboard del adafruit


/************************ Example Starts Here *******************************/

// this int will hold the current count for our sketch
//Variables
int count = 0;
int entrada = 0;
int valu1 = 1;
int valu2 = 2;
int valu3 = 3;
int valu4 = 4;
//byte  valu1 = 1;
//byte  valu2 = 2;
//byte  valu3 = 3;
//byte  valu4 = 4;
String Intled;
int datof =0;  
int giro=0;
// set up the 'counter' feed
AdafruitIO_Feed *L1 = io.feed("L1");//led azul
AdafruitIO_Feed *L2 = io.feed("L2");//led roja


//_-----------------------------------mensaje adafruit-----------------------
void handleMessage(AdafruitIO_Data *data){
  Intled = data->value();
  }
//-------------------------------------------SETUP--------------------------
void setup() {

  // start the serial connection
  Serial.begin(9600);// baudrate de el ESP32 y del pic16f887

  // connect to io.adafruit.com
  io.connect();

  L1->onMessage(handleMessage);// LedA
  L2->onMessage(handleMessage);
  // wait for a connection
  while(io.status() < AIO_CONNECTED) {
    digitalWrite(2,HIGH);
    delay(500);
  }
  digitalWrite(2,LOW);
  // we are connected
  L1->get();
  L2->get();

}


//--------------------Loop-------------------------------------------------
void loop() {

  // io.run(); is required for all sketches.
  // it should always be present at the top of your loop
  // function. it keeps the client connected to
  // io.adafruit.com, and processes any incoming data.
  io.run();
 // if(Serial.available()>0){
  //  entrada = Serial.read(); //es para obtener el dato del PIC16f887
//    giro->save((entrada, DEC));
   // }
  
  datof=Intled.toInt();// cambiar dato a entero
  switch(datof){
    case 1:
    if(Serial.availableForWrite()){
      //Caso led azul prendida
      Serial.write(1); }
      //Serial.println(1, DEC);   
      break;
    case 2:
    if(Serial.availableForWrite()){
      //Caso led azul apagada
      Serial.write(2);}
      //Serial.println(2, DEC);}
      break;
    case 3:
    if(Serial.availableForWrite()){
      //Caso led roja prendida
      Serial.write(3);}
      //Serial.println(3, DEC);
      break;
    case 4:
    if(Serial.availableForWrite()){
      //Caso led roja apagada
      Serial.write(4);}
      //Serial.println(4, DEC);
      break;
      default:
    break;
    }
  // Adafruit IO is rate limited for publishing, so a delay is required in
  // between feed->save events. In this example, we will wait three seconds
  // (1000 milliseconds == 1 second) during each loop.
  delay(3000);

}

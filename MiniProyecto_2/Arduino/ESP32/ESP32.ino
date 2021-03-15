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
#define IO_LOOP_DELAY 10000
// this int will hold the current count for our sketch
//Variables
int count = 0;
int entrada = 0;
char *valu1 = 1;
char *valu2 = 2;
int valu4 = 4;
float x_d;
float y_d;
float z_d;
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
AdafruitIO_Feed *EJE_X = io.feed("EJE X");//dato de adafruit de eje x
AdafruitIO_Feed *EJE_Y = io.feed("EJE Y");
AdafruitIO_Feed *EJE_Z = io.feed("EJE Z");


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

  L1->onMessage(adaled);
  L2->onMessage(adaled1);
  
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
  
  // Adafruit IO is rate limited for publishing, so a delay is required in
  // between feed->save events. In this example, we will wait three seconds
  // (1000 milliseconds == 1 second) during each loop.
  delay(3000);

}

void adaled(AdafruitIO_Data *data){
   Serial.print("received <- ");
  valu1 =  data->value();
  Serial.println(valu1);
  if(*valu1 == '1')Serial.write(1); 
  else Serial.write(2); 
  return;
  }
  
void adaled1(AdafruitIO_Data *data){
   Serial.print("received <- ");
  valu2 =  data->value(); 
  Serial.println(valu2);
  if(*valu2 == '1')Serial.write(3); 
  else Serial.write(4); 
  return;
  }

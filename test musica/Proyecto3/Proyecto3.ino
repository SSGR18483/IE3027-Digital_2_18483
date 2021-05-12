//***************************************************************************************************************************************
/* Librería para el uso de la pantalla ILI9341 en modo 8 bits
 * Basado en el código de martinayotte - https://www.stm32duino.com/viewtopic.php?t=637
 * Adaptación, migración y creación de nuevas funciones: Pablo Mazariegos y José Morales
 * Con ayuda de: José Guerra
 * IE3027: Electrónica Digital 2 - 2019
 */
//***************************************************************************************************************************************
#include <stdint.h>
#include <stdbool.h>
#include <TM4C123GH6PM.h>
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/debug.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/rom_map.h"
#include "driverlib/rom.h"
#include "driverlib/sysctl.h"
#include "driverlib/timer.h"
#include "sonidos.h"
#include "bitmaps.h"
#include "font.h"
#include "lcd_registers.h"

#define LCD_RST PD_0
#define LCD_CS PD_1
#define LCD_RS PD_2
#define LCD_WR PD_3
#define LCD_RD PE_1
int DPINS[] = {PB_0, PB_1, PB_2, PB_3, PB_4, PB_5, PB_6, PB_7};  

//***************************************************************************************************************************************
// Algunas variables y botones
//***************************************************************************************************************************************
//Definimos unos colores básicos
#define Blanco 0xFFFF
#define Negro 0x0000
#define Azul   0x001F
#define Rojo   0xF800
#define Amarillo 0xFFE0

//Donde se encontrarán nuestros botones para los jugadores
const int UP1 = PD_7;
const int DO1= PF_4;
const int UP2= PC_7;
const int DO2= PD_6;

extern uint8_t inicio[];

//Posiciones iniciales para los jugadores en x
const int p1x=35;
const int p2x=240;

const int pa_alt=23;

//Variables para vel el puntaje y como corre el juego
int scorej1=0;
int scorej2=0;
int maxpuntos=5;
int end_to_start = 0;
int start_btn;
int x_s = 1;

//Valores iniciales para los jugadores y la pelota 
uint8_t p1y= 110;
uint8_t p2y= 110;
uint8_t pex=64;
uint8_t pey=32;
uint8_t coorx=1;
uint8_t coory=1;


boolean reinicio=false;
boolean juego=true;

unsigned long peupdate;
unsigned long paupdate;

const unsigned long perate=1;
const unsigned long parate=1;
//***************************************************************************************************************************************
// Functions Prototypes
//***************************************************************************************************************************************
void LCD_Init(void);
void LCD_CMD(uint8_t cmd);
void LCD_DATA(uint8_t data);
void SetWindows(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2);
void LCD_Clear(unsigned int c);
void H_line(unsigned int x, unsigned int y, unsigned int l, unsigned int c);
void V_line(unsigned int x, unsigned int y, unsigned int l, unsigned int c);
void Rect(unsigned int x, unsigned int y, unsigned int w, unsigned int h, unsigned int c);
void FillRect(unsigned int x, unsigned int y, unsigned int w, unsigned int h, unsigned int c);
void LCD_Print(String text, int x, int y, int fontSize, int color, int background);

//Función para pantalla de inicio
void start_screen(void);
//Fución para finalizar el juego
void fin(void);
//Dibujar el background
void background(void);
void backgroundjuego(void);
//Enseñar puntaje
void score(void);

void LCD_Bitmap(unsigned int x, unsigned int y, unsigned int width, unsigned int height, unsigned char bitmap[]);
void LCD_Sprite(int x, int y, int width, int height, unsigned char bitmap[],int columns, int index, char flip, char offset);

//***************************************************************************************************************************************
// Inicialización
//***************************************************************************************************************************************
void setup() {
  //Los botones para los jugadores se definen como inputs
  pinMode(UP1, INPUT);
  pinMode(DO1, INPUT);
  pinMode(UP2, INPUT);
  pinMode(DO2, INPUT);
  pinMode(PUSH1, INPUT);

  //Se configura para que corra la pantalla
  SysCtlClockSet(SYSCTL_SYSDIV_2_5|SYSCTL_USE_PLL|SYSCTL_OSC_MAIN|SYSCTL_XTAL_16MHZ);
  Serial.begin(9600);
  GPIOPadConfigSet(GPIO_PORTB_BASE, 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7, GPIO_STRENGTH_8MA, GPIO_PIN_TYPE_STD_WPU);
  Serial.println("Inicio");
  LCD_Init();
  LCD_Clear(0x00);
  //Función para la pantalla de inicio
  start_screen(); 
  //Enseñamos la pantalla de bienvenida con instrucciones
  FillRect(0, 0, 320, 240, Negro);
  String text1 = "Bienvenidos!";
  LCD_Print(text1, 60, 100, 2, 0xffff, Negro);
  String text2 = "El primero que ";
  LCD_Print(text2, 50, 130, 2, 0xffff, Negro);
  String text3 = "llegue a 5 gana! ";
  LCD_Print(text3, 30, 150, 2, 0xffff, Negro);
  delay(2000);
  backgroundjuego();


  //Esperamos un tiempo para empezar el movimiento de la pelota
  unsigned long start= millis();
  while(millis()-start<2000);
  peupdate=millis();
  paupdate=peupdate;
  //Se escogen unas coordenadas random para ver la posición de la pelota 
  pex=random(120,125);
  pey=random(20,30);
  
}
//***************************************************************************************************************************************
// Loop Infinito
//***************************************************************************************************************************************
void loop() {
  unsigned long time= millis();
  //Definimos de esta manera el digitalRead de los botones para que sea más fácil ver si se presiono el botón 
  static bool UP1_state=false;
  static bool DO1_state=false;
  static bool UP2_state=false;
  static bool DO2_state=false;
  UP1_state |= (digitalRead(UP1)==LOW);
  DO1_state |= (digitalRead(DO1)==LOW);
  UP2_state |= (digitalRead(UP2)==LOW);
  DO2_state |= (digitalRead(DO2)==LOW);
  //Si se reinicio, la pelota empieza desde coordenadas random y se dibuja el background
  if(reinicio){
    backgroundjuego();
    pex=random(120,125);
    pey=random(20,30);
    do{
      coorx=random(-1,2);
      }
      while(coorx==0);
     do{
      coory=random(-1,2);
      }
      while(coory==0);
      reinicio=false;
    }
  //El movmiento de la pelota se realiza al sumar un valor random a la coordenada que ya se tenía
  if(time > peupdate && juego){
    uint8_t newx=pex+coorx;
    uint8_t newy=pey+coory;
    //Definimos algunas condiciones para el movimiento
    //Extremos verticales
    if (newx ==10){  //Extremo izquierdo
      //Se le agrega uno al puntaje de jugador 2
      scorej2++;
      if (scorej2==maxpuntos){
        fin();
        }
       else{
        //Show score
        musica(melody2, durations2, songLength2);
        score();
        }
      //Música
      //musica(melody2, durations2, songLength2);
      }
      
    if (newx ==255){ //Extremo derecho
      //Se le agrega uno al puntaje de jugador 1
      scorej1++;
        if (scorej1==maxpuntos){
        fin();
        }
       else{
        //Show score
        musica(melody3, durations3, songLength3);
        score();
        }
      //Música
      //musica(melody3, durations3, songLength3);
      }
      
  //Extremos horizontales 
    if (newy== 17 || newy==215){
      //Cambiamos de dirección
      coory=-coory;
      newy+=coory+coory;
      }
   //Jugador 1 le pegó (El de la izquierda)
   if (newx=p1x  && newy>=p1y && newy<= p1y+ pa_alt){
      coorx=-coorx;
      newx+=coorx+coorx;
     
    }
   
   //Jugador 2 le pegó (El de la derecha)
   if (newx=p2x  && newy>=p2y && newy<= p2y+ pa_alt){
      coorx = -coorx;
      newx += coorx+coorx;
      
  }
  //Hacemos suma para que se dé el movimiento
    newx=pex+coorx;
    newy=pey+coory;
    FillRect(pex, pey, 8, 8, Negro);
    FillRect(newx, newy, 8, 8, Amarillo);
    
    pex=newx;
    pey=newy;
    peupdate += perate;
  }
 //Ahora definimos como se veran las raquetas de los jugadores y su movimiento 
  if (time> paupdate && juego){
    paupdate += parate;
  
    //Jugador uno
    V_line(p1x, p1y, pa_alt, Negro);
    if(UP1_state){
      p1y-=1;
      }
    if(DO1_state){
      p1y+=1;
      }  
     UP1_state=DO1_state= false;
     if (p1y<17) p1y=17;
     if (p1y+pa_alt>215) p1y=215-pa_alt;
     V_line(p1x, p1y, pa_alt, Negro);

     
    //Jugador dos
    V_line(p2x, p2y, pa_alt, Negro);
    if(UP2_state){
      p2y-=1;
      }
    if(DO2_state){
      p2y+=1;
      }  
     UP2_state=DO2_state= false;
     if (p2y<17) p2y=17;
     if (p2y+pa_alt>215) p2y=215-pa_alt;
     V_line(p2x, p2y, pa_alt, Negro);

     //Paletas de los jugadores con su movimiento
    LCD_Sprite(p1x, p1y, 32, 32, planta, 1, 0, 1,0);;
    LCD_Sprite(p2x, p2y, 32, 32, planta, 1, 0, 1,0);
    
  
     
    }

}
//***************************************************************************************************************************************
// Funciones
//***************************************************************************************************************************************
//----------------------------------------------------------------------------------
//Función de pantalla de inicio
void start_screen(void){ 
  LCD_Bitmap(0, 0, 320, 240, inicio);
  musica(melody1, durations1, songLength1);
  delay(100);

}
//----------------------------------------------------------------------------------
//Game Over al llegar a ciertos puntos
void fin(){
  juego =false; 
  LCD_Clear(0x00);
  delay(1000);
  background();
  if(scorej1>scorej2){
    String text4 = "El Jugador 1 es el ganador!";
    LCD_Print(text4, 60, 100, 1, Blanco, Azul);
    musica(melody4, durations4, songLength4);
    }
  else{
    String text5 = "El Jugador 2 es el ganador!";
    LCD_Print(text5, 60, 100, 1, Blanco, Azul);
    musica(melody4, durations4, songLength4);
    }
    delay(2500);
    LCD_Print(String(scorej1), 110, 115, 1, Blanco, Azul);
    LCD_Print(String(scorej2), 150, 115, 1, Blanco, Azul);
    delay(1000);
    

   while (digitalRead(UP1)==LOW && digitalRead(DO1)==LOW && digitalRead(UP2)==LOW && digitalRead(DO2)==LOW){
    delay(100);
    }
    juego= true;
    scorej1=scorej2=0;
    unsigned long start= millis();
    //LCD_Clear(0x00);
    while(millis()-start<2000);
    peupdate=millis();
    paupdate=peupdate;
    juego= true;
    reinicio= true;
  
  }
  //----------------------------------------------------------------------------------
  //Función para enseñar el puntaje 
  void score(){
    juego= false;
    LCD_Clear(0x00);
    delay(100);
    unsigned long start= millis();
    background();
    String text5="Marcador";
    LCD_Print(text5, 100, 100, 1, 0xFFFF, 0x6400);
    LCD_Print(String(scorej1), 110, 115, 1, Blanco, Azul);
    LCD_Print(String(scorej2), 150, 115, 1, Blanco, Azul);
    delay(1000);
    LCD_Clear(0x00);
    while(millis()-start<2000);
    peupdate=millis();
    paupdate=peupdate;
    juego= true;
    reinicio= true;
    p1y=100;
    p2y=100;
    
    }
  //----------------------------------------------------------------------------------
  //Función de background
  void background(){
   LCD_Clear(0x00);
   FillRect(0, 0, 320, 240, 0x6400);

   for(int x = 0; x <319; x++){
      LCD_Bitmap(x, 1, 16, 16, tile);
     
      LCD_Bitmap(x, 223, 16, 16, tile);
      x += 15;
   }

    }
  //----------------------------------------------------------------------------------
  //Función de background para el juego
  void backgroundjuego(){
   LCD_Clear(0x00);
   FillRect(0, 0, 320, 240, Negro);

   for(int x = 0; x <319; x++){
      LCD_Bitmap(x, 1, 16, 16, tile);
     
      LCD_Bitmap(x, 223, 16, 16, tile);
      x += 15;
   }

    }
//***************************************************************************************************************************************
// Función para inicializar LCD
//***************************************************************************************************************************************
void LCD_Init(void) {
  pinMode(LCD_RST, OUTPUT);
  pinMode(LCD_CS, OUTPUT);
  pinMode(LCD_RS, OUTPUT);
  pinMode(LCD_WR, OUTPUT);
  pinMode(LCD_RD, OUTPUT);
  for (uint8_t i = 0; i < 8; i++){
    pinMode(DPINS[i], OUTPUT);
  }
  //****************************************
  // Secuencia de Inicialización
  //****************************************
  digitalWrite(LCD_CS, HIGH);
  digitalWrite(LCD_RS, HIGH);
  digitalWrite(LCD_WR, HIGH);
  digitalWrite(LCD_RD, HIGH);
  digitalWrite(LCD_RST, HIGH);
  delay(5);
  digitalWrite(LCD_RST, LOW);
  delay(20);
  digitalWrite(LCD_RST, HIGH);
  delay(150);
  digitalWrite(LCD_CS, LOW);
  //****************************************
  LCD_CMD(0xE9);  // SETPANELRELATED
  LCD_DATA(0x20);
  //****************************************
  LCD_CMD(0x11); // Exit Sleep SLEEP OUT (SLPOUT)
  delay(100);
  //****************************************
  LCD_CMD(0xD1);    // (SETVCOM)
  LCD_DATA(0x00);
  LCD_DATA(0x71);
  LCD_DATA(0x19);
  //****************************************
  LCD_CMD(0xD0);   // (SETPOWER) 
  LCD_DATA(0x07);
  LCD_DATA(0x01);
  LCD_DATA(0x08);
  //****************************************
  LCD_CMD(0x36);  // (MEMORYACCESS)
  LCD_DATA(0x40|0x80|0x20|0x08); // LCD_DATA(0x19);
  //****************************************
  LCD_CMD(0x3A); // Set_pixel_format (PIXELFORMAT)
  LCD_DATA(0x05); // color setings, 05h - 16bit pixel, 11h - 3bit pixel
  //****************************************
  LCD_CMD(0xC1);    // (POWERCONTROL2)
  LCD_DATA(0x10);
  LCD_DATA(0x10);
  LCD_DATA(0x02);
  LCD_DATA(0x02);
  //****************************************
  LCD_CMD(0xC0); // Set Default Gamma (POWERCONTROL1)
  LCD_DATA(0x00);
  LCD_DATA(0x35);
  LCD_DATA(0x00);
  LCD_DATA(0x00);
  LCD_DATA(0x01);
  LCD_DATA(0x02);
  //****************************************
  LCD_CMD(0xC5); // Set Frame Rate (VCOMCONTROL1)
  LCD_DATA(0x04); // 72Hz
  //****************************************
  LCD_CMD(0xD2); // Power Settings  (SETPWRNORMAL)
  LCD_DATA(0x01);
  LCD_DATA(0x44);
  //****************************************
  LCD_CMD(0xC8); //Set Gamma  (GAMMASET)
  LCD_DATA(0x04);
  LCD_DATA(0x67);
  LCD_DATA(0x35);
  LCD_DATA(0x04);
  LCD_DATA(0x08);
  LCD_DATA(0x06);
  LCD_DATA(0x24);
  LCD_DATA(0x01);
  LCD_DATA(0x37);
  LCD_DATA(0x40);
  LCD_DATA(0x03);
  LCD_DATA(0x10);
  LCD_DATA(0x08);
  LCD_DATA(0x80);
  LCD_DATA(0x00);
  //****************************************
  LCD_CMD(0x2A); // Set_column_address 320px (CASET)
  LCD_DATA(0x00);
  LCD_DATA(0x00);
  LCD_DATA(0x01);
  LCD_DATA(0x3F);
  //****************************************
  LCD_CMD(0x2B); // Set_page_address 480px (PASET)
  LCD_DATA(0x00);
  LCD_DATA(0x00);
  LCD_DATA(0x01);
  LCD_DATA(0xE0);
//  LCD_DATA(0x8F);
  LCD_CMD(0x29); //display on 
  LCD_CMD(0x2C); //display on

  LCD_CMD(ILI9341_INVOFF); //Invert Off
  delay(120);
  LCD_CMD(ILI9341_SLPOUT);    //Exit Sleep
  delay(120);
  LCD_CMD(ILI9341_DISPON);    //Display on
  digitalWrite(LCD_CS, HIGH);
}
//***************************************************************************************************************************************
// Función para enviar comandos a la LCD - parámetro (comando)
//***************************************************************************************************************************************
void LCD_CMD(uint8_t cmd) {
  digitalWrite(LCD_RS, LOW);
  digitalWrite(LCD_WR, LOW);
  GPIO_PORTB_DATA_R = cmd;
  digitalWrite(LCD_WR, HIGH);
}
//***************************************************************************************************************************************
// Función para enviar datos a la LCD - parámetro (dato)
//***************************************************************************************************************************************
void LCD_DATA(uint8_t data) {
  digitalWrite(LCD_RS, HIGH);
  digitalWrite(LCD_WR, LOW);
  GPIO_PORTB_DATA_R = data;
  digitalWrite(LCD_WR, HIGH);
}
//***************************************************************************************************************************************
// Función para definir rango de direcciones de memoria con las cuales se trabajara (se define una ventana)
//***************************************************************************************************************************************
void SetWindows(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2) {
  LCD_CMD(0x2a); // Set_column_address 4 parameters
  LCD_DATA(x1 >> 8);
  LCD_DATA(x1);   
  LCD_DATA(x2 >> 8);
  LCD_DATA(x2);   
  LCD_CMD(0x2b); // Set_page_address 4 parameters
  LCD_DATA(y1 >> 8);
  LCD_DATA(y1);   
  LCD_DATA(y2 >> 8);
  LCD_DATA(y2);   
  LCD_CMD(0x2c); // Write_memory_start
}
//***************************************************************************************************************************************
// Función para borrar la pantalla - parámetros (color)
//***************************************************************************************************************************************
void LCD_Clear(unsigned int c){  
  unsigned int x, y;
  LCD_CMD(0x02c); // write_memory_start
  digitalWrite(LCD_RS, HIGH);
  digitalWrite(LCD_CS, LOW);   
  SetWindows(0, 0, 319, 239); // 479, 319);
  for (x = 0; x < 320; x++)
    for (y = 0; y < 240; y++) {
      LCD_DATA(c >> 8); 
      LCD_DATA(c); 
    }
  digitalWrite(LCD_CS, HIGH);
} 
//***************************************************************************************************************************************
// Función para dibujar una línea horizontal - parámetros ( coordenada x, cordenada y, longitud, color)
//*************************************************************************************************************************************** 
void H_line(unsigned int x, unsigned int y, unsigned int l, unsigned int c) {  
  unsigned int i, j;
  LCD_CMD(0x02c); //write_memory_start
  digitalWrite(LCD_RS, HIGH);
  digitalWrite(LCD_CS, LOW);
  l = l + x;
  SetWindows(x, y, l, y);
  j = l;// * 2;
  for (i = 0; i < l; i++) {
      LCD_DATA(c >> 8); 
      LCD_DATA(c); 
  }
  digitalWrite(LCD_CS, HIGH);
}
//***************************************************************************************************************************************
// Función para dibujar una línea vertical - parámetros ( coordenada x, cordenada y, longitud, color)
//*************************************************************************************************************************************** 
void V_line(unsigned int x, unsigned int y, unsigned int l, unsigned int c) {  
  unsigned int i,j;
  LCD_CMD(0x02c); //write_memory_start
  digitalWrite(LCD_RS, HIGH);
  digitalWrite(LCD_CS, LOW);
  l = l + y;
  SetWindows(x, y, x, l);
  j = l; //* 2;
  for (i = 1; i <= j; i++) {
    LCD_DATA(c >> 8); 
    LCD_DATA(c);
  }
  digitalWrite(LCD_CS, HIGH);  
}
//***************************************************************************************************************************************
// Función para dibujar un rectángulo - parámetros ( coordenada x, cordenada y, ancho, alto, color)
//***************************************************************************************************************************************
void Rect(unsigned int x, unsigned int y, unsigned int w, unsigned int h, unsigned int c) {
  H_line(x  , y  , w, c);
  H_line(x  , y+h, w, c);
  V_line(x  , y  , h, c);
  V_line(x+w, y  , h, c);
}
//***************************************************************************************************************************************
// Función para dibujar un rectángulo relleno - parámetros ( coordenada x, cordenada y, ancho, alto, color)
//***************************************************************************************************************************************
void FillRect(unsigned int x, unsigned int y, unsigned int w, unsigned int h, unsigned int c) {
  unsigned int i;
  for (i = 0; i < h; i++) {
    H_line(x  , y  , w, c);
    H_line(x  , y+i, w, c);
  }
}
//***************************************************************************************************************************************
// Función para dibujar texto - parámetros ( texto, coordenada x, cordenada y, color, background) 
//***************************************************************************************************************************************
void LCD_Print(String text, int x, int y, int fontSize, int color, int background) {
  int fontXSize ;
  int fontYSize ;
  
  if(fontSize == 1){
    fontXSize = fontXSizeSmal ;
    fontYSize = fontYSizeSmal ;
  }
  if(fontSize == 2){
    fontXSize = fontXSizeBig ;
    fontYSize = fontYSizeBig ;
  }
  
  char charInput ;
  int cLength = text.length();
  Serial.println(cLength,DEC);
  int charDec ;
  int c ;
  int charHex ;
  char char_array[cLength+1];
  text.toCharArray(char_array, cLength+1) ;
  for (int i = 0; i < cLength ; i++) {
    charInput = char_array[i];
    Serial.println(char_array[i]);
    charDec = int(charInput);
    digitalWrite(LCD_CS, LOW);
    SetWindows(x + (i * fontXSize), y, x + (i * fontXSize) + fontXSize - 1, y + fontYSize );
    long charHex1 ;
    for ( int n = 0 ; n < fontYSize ; n++ ) {
      if (fontSize == 1){
        charHex1 = pgm_read_word_near(smallFont + ((charDec - 32) * fontYSize) + n);
      }
      if (fontSize == 2){
        charHex1 = pgm_read_word_near(bigFont + ((charDec - 32) * fontYSize) + n);
      }
      for (int t = 1; t < fontXSize + 1 ; t++) {
        if (( charHex1 & (1 << (fontXSize - t))) > 0 ) {
          c = color ;
        } else {
          c = background ;
        }
        LCD_DATA(c >> 8);
        LCD_DATA(c);
      }
    }
    digitalWrite(LCD_CS, HIGH);
  }
}
//***************************************************************************************************************************************
// Función para dibujar una imagen a partir de un arreglo de colores (Bitmap) Formato (Color 16bit R 5bits G 6bits B 5bits)
//***************************************************************************************************************************************
void LCD_Bitmap(unsigned int x, unsigned int y, unsigned int width, unsigned int height, unsigned char bitmap[]){  
  LCD_CMD(0x02c); // write_memory_start
  digitalWrite(LCD_RS, HIGH);
  digitalWrite(LCD_CS, LOW); 
  
  unsigned int x2, y2;
  x2 = x+width;
  y2 = y+height;
  SetWindows(x, y, x2-1, y2-1);
  unsigned int k = 0;
  unsigned int i, j;

  for (int i = 0; i < width; i++) {
    for (int j = 0; j < height; j++) {
      LCD_DATA(bitmap[k]);
      LCD_DATA(bitmap[k+1]);
      //LCD_DATA(bitmap[k]);    
      k = k + 2;
     } 
  }
  digitalWrite(LCD_CS, HIGH);
}
//***************************************************************************************************************************************
// Función para dibujar una imagen sprite - los parámetros columns = número de imagenes en el sprite, index = cual desplegar, flip = darle vuelta
//***************************************************************************************************************************************
void LCD_Sprite(int x, int y, int width, int height, unsigned char bitmap[],int columns, int index, char flip, char offset){
  LCD_CMD(0x02c); // write_memory_start
  digitalWrite(LCD_RS, HIGH);
  digitalWrite(LCD_CS, LOW); 

  unsigned int x2, y2;
  x2 =   x+width;
  y2=    y+height;
  SetWindows(x, y, x2-1, y2-1);
  int k = 0;
  int ancho = ((width*columns));
  if(flip){
  for (int j = 0; j < height; j++){
      k = (j*(ancho) + index*width -1 - offset)*2;
      k = k+width*2;
     for (int i = 0; i < width; i++){
      LCD_DATA(bitmap[k]);
      LCD_DATA(bitmap[k+1]);
      k = k - 2;
     } 
  }
  }else{
     for (int j = 0; j < height; j++){
      k = (j*(ancho) + index*width + 1 + offset)*2;
     for (int i = 0; i < width; i++){
      LCD_DATA(bitmap[k]);
      LCD_DATA(bitmap[k+1]);
      k = k + 2;
     } 
  }
    
    
    }
  digitalWrite(LCD_CS, HIGH);
}

//pseudo codigo santiago galicia
//18483

#define LED RED_LED
#define LED1 GREEN_LED
#define LED2 BLUE_LED
int buttonPin1 = PUSH1;
int buttonPin2 = PUSH2;

int val =0;
int val1 = 0;
int cont1=0;
int cont2=0;
//JUGADOR 1 PINES:
int led1 = PB_5;
int led2 = PB_0;
int led3 = PB_1;
int led4 = PE_4;
int led5 = PE_5;
int led6 = PB_4;
int led7 = PA_5;
int led8 = PA_6;
int gan1 = PA_7;
//JUGADOR 2 PINES:
int led9 = PA_2;
int led10 = PD_7;
int led11 = PD_6;
int led12 = PC_7;
int led13 = PC_6;
int led14 = PC_5;
int led15 = PC_4;
int led16 = PB_3;
int gan2 = PB_2;
//Declaracion de funciones a usar
void semaforo(void);
void ganador(void);
void p1(void);
void p2(void);


int cont3 = 0;

void setup() {
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(led5, OUTPUT);
  pinMode(led6, OUTPUT);
  pinMode(led7, OUTPUT);
  pinMode(led8, OUTPUT);
  pinMode(led9,  OUTPUT);
  pinMode(led10, OUTPUT);
  pinMode(led11, OUTPUT);
  pinMode(led12, OUTPUT);
  pinMode(led13, OUTPUT);
  pinMode(led14, OUTPUT);
  pinMode(led15, OUTPUT);
  pinMode(led16, OUTPUT);
  pinMode(gan1, OUTPUT);
  pinMode(gan2, OUTPUT);

  // put your setup code here, to run once:
  pinMode(LED, OUTPUT);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(buttonPin1, INPUT_PULLUP);
  pinMode(buttonPin2, INPUT_PULLUP);
  delay(1000);
  semaforo();
}

void semaforo(void){
    delay(100);
    digitalWrite(LED, HIGH);
    delay(1100);
    digitalWrite(LED1, HIGH);
    delay(1100);
    digitalWrite(LED, LOW);
    delay(1100);
    digitalWrite(LED1, LOW);
  }
void ganador(void){
  if(cont1>8){
    digitalWrite(gan1, HIGH);
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    digitalWrite(led4, LOW);
    digitalWrite(led5, LOW);
    digitalWrite(led6, LOW);
    digitalWrite(led7, LOW);
    digitalWrite(led8, LOW);
    cont3=1;
    loop();
    }
  if(cont2>8){
    digitalWrite(gan2, HIGH);
    digitalWrite(led9, LOW);
    digitalWrite(led10, LOW);
    digitalWrite(led11, LOW);
    digitalWrite(led12, LOW);
    digitalWrite(led13, LOW);
    digitalWrite(led14, LOW);
    digitalWrite(led15, LOW);
    digitalWrite(led16, LOW);
    cont3=1;
    loop();}
}
void p1(void){
  if(digitalRead(buttonPin1)== LOW){
    val=1;
    delay(100);
    }
  if(digitalRead(buttonPin1)==HIGH && val ==1){//antibounce primer boton
    val=0;
    delay(50);
    cont1++;
    }
 if(cont3==0){
  switch(cont1){
    case 0:
      digitalWrite(led1, LOW); 
      digitalWrite(led2, LOW);
      digitalWrite(led3, LOW);
      digitalWrite(led4, LOW);
      digitalWrite(led5, LOW);
      digitalWrite(led6, LOW);
      digitalWrite(led7, LOW);
      digitalWrite(led8, LOW);
      break;
    case 1:
      digitalWrite(led1, HIGH); 
      digitalWrite(led2, LOW);
      digitalWrite(led3, LOW);
      digitalWrite(led4, LOW);
      digitalWrite(led5, LOW);
      digitalWrite(led6, LOW);
      digitalWrite(led7, LOW);
      digitalWrite(led8, LOW);
      break;
    case 2:
      digitalWrite(led1, HIGH); 
      digitalWrite(led2, HIGH);
      digitalWrite(led3, LOW);
      digitalWrite(led4, LOW);
      digitalWrite(led5, LOW);
      digitalWrite(led6, LOW);
      digitalWrite(led7, LOW);
      digitalWrite(led8, LOW);
      break;
    case 3:
      digitalWrite(led1, HIGH); 
      digitalWrite(led2, HIGH);
      digitalWrite(led3, HIGH);
      digitalWrite(led4, LOW);
      digitalWrite(led5, LOW);
      digitalWrite(led6, LOW);
      digitalWrite(led7, LOW);
      digitalWrite(led8, LOW);
      break;
    case 4:
      digitalWrite(led1, HIGH); 
      digitalWrite(led2, HIGH);
      digitalWrite(led3, HIGH);
      digitalWrite(led4, HIGH);
      digitalWrite(led5, LOW);
      digitalWrite(led6, LOW);
      digitalWrite(led7, LOW);
      digitalWrite(led8, LOW);
      break;
    case 5:
      digitalWrite(led1, HIGH); 
      digitalWrite(led2, HIGH);
      digitalWrite(led3, HIGH);
      digitalWrite(led4, HIGH);
      digitalWrite(led5, HIGH);
      digitalWrite(led6, LOW);
      digitalWrite(led7, LOW);
      digitalWrite(led8, LOW);
      break;
    case 6:
      digitalWrite(led1, HIGH); 
      digitalWrite(led2, HIGH);
      digitalWrite(led3, HIGH);
      digitalWrite(led4, HIGH);
      digitalWrite(led5, HIGH);
      digitalWrite(led6, HIGH);
      digitalWrite(led7, LOW);
      digitalWrite(led8, LOW);
      break;      
    case 7:
      digitalWrite(led1, HIGH); 
      digitalWrite(led2, HIGH);
      digitalWrite(led3, HIGH);
      digitalWrite(led4, HIGH);
      digitalWrite(led5, HIGH);
      digitalWrite(led6, HIGH);
      digitalWrite(led7, HIGH);
      digitalWrite(led8, LOW);
      break;      
    case 8:
      digitalWrite(led1, HIGH); 
      digitalWrite(led2, HIGH);
      digitalWrite(led3, HIGH);
      digitalWrite(led4, HIGH);
      digitalWrite(led5, HIGH);
      digitalWrite(led6, HIGH);
      digitalWrite(led7, HIGH);
      digitalWrite(led8, HIGH);
      break;      
    }
 }
  }

  
void p2(void){
  if(digitalRead(buttonPin2)== LOW){
    val1=1;
    delay(100);
    }
  if(digitalRead(buttonPin2)==HIGH && val1 ==1){//antibounce primer boton
    val1=0;
    delay(50);
    cont2++;
    }
  if(cont3==0){
  switch(cont2){
    case 0:
      digitalWrite(led9, LOW); 
      digitalWrite(led10, LOW);
      digitalWrite(led11, LOW);
      digitalWrite(led12, LOW);
      digitalWrite(led13, LOW);
      digitalWrite(led14, LOW);
      digitalWrite(led15, LOW);
      digitalWrite(led16, LOW);
      break;
    case 1:
      digitalWrite(led9, HIGH); 
      digitalWrite(led10, LOW);
      digitalWrite(led11, LOW);
      digitalWrite(led12, LOW);
      digitalWrite(led13, LOW);
      digitalWrite(led14, LOW);
      digitalWrite(led15, LOW);
      digitalWrite(led16, LOW);
      break;
    case 2:
      digitalWrite(led9, HIGH); 
      digitalWrite(led10, HIGH);
      digitalWrite(led11, LOW);
      digitalWrite(led12, LOW);
      digitalWrite(led13, LOW);
      digitalWrite(led14, LOW);
      digitalWrite(led15, LOW);
      digitalWrite(led16, LOW);
      break;
    case 3:
      digitalWrite(led9, HIGH); 
      digitalWrite(led10, HIGH);
      digitalWrite(led11, HIGH);
      digitalWrite(led12, LOW);
      digitalWrite(led13, LOW);
      digitalWrite(led14, LOW);
      digitalWrite(led15, LOW);
      digitalWrite(led16, LOW);
      break;
    case 4:
      digitalWrite(led9, HIGH); 
      digitalWrite(led10, HIGH);
      digitalWrite(led11, HIGH);
      digitalWrite(led12, HIGH);
      digitalWrite(led13, LOW);
      digitalWrite(led14, LOW);
      digitalWrite(led15, LOW);
      digitalWrite(led16, LOW);
      break;
    case 5:
      digitalWrite(led9, HIGH); 
      digitalWrite(led10, HIGH);
      digitalWrite(led11, HIGH);
      digitalWrite(led12, HIGH);
      digitalWrite(led13, HIGH);
      digitalWrite(led14, LOW);
      digitalWrite(led15, LOW);
      digitalWrite(led16, LOW);
      break;
    case 6:
      digitalWrite(led9, HIGH); 
      digitalWrite(led10, HIGH);
      digitalWrite(led11, HIGH);
      digitalWrite(led12, HIGH);
      digitalWrite(led13, HIGH);
      digitalWrite(led14, HIGH);
      digitalWrite(led15, LOW);
      digitalWrite(led16, LOW);
      break;      
    case 7:
      digitalWrite(led9, HIGH); 
      digitalWrite(led10, HIGH);
      digitalWrite(led11, HIGH);
      digitalWrite(led12, HIGH);
      digitalWrite(led13, HIGH);
      digitalWrite(led14, HIGH);
      digitalWrite(led15, HIGH);
      digitalWrite(led16, LOW);
      break;      
    case 8:
      digitalWrite(led9, HIGH); 
      digitalWrite(led10, HIGH);
      digitalWrite(led11, HIGH);
      digitalWrite(led12, HIGH);
      digitalWrite(led13, HIGH);
      digitalWrite(led14, HIGH);
      digitalWrite(led15, HIGH);
      digitalWrite(led16, HIGH);
      break;      
    }
  }
  }

void loop() {
  p1();
  p2();
  ganador();
}

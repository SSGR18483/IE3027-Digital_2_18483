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
    loop();
    }
  if(cont2>8){}
}
void p1(void){
  }
void p2(void){
  }

void loop() {
  p1();
  p2();
  ganador();
}

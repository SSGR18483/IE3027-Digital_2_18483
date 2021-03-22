//pseudo codigo santiago galicia
//18483

#define LED RED_LED
#define LED1 GREEN_LED
#define LED2 BLUE_LED
#define LED3 YELLOW_LED
#define LED4 PINK_LED
const int buttonPin1 = PUSH1
const int buttonPin2 = PUSH2

int val =0;
int val1 = 0;
int cont1=1;
int cont2=1;

void setup() {
  // put your setup code here, to run once:
  pinMode(LED, OUTPUT);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  pinMode(buttonPin1, INPUT_PULLUP);
  pinMode(buttonPin2, INPUT_PULLUP);
}

void loop() {
  // put your main code here, to run repeatedly: 
  val= digitalRead(buttonPin1);
  val1= digitalRead(buttonPin2);
  if (val ==HIGH || val1 == HIGH) {
    digitalWrite(LED, HIGH);
    delay(300);
    digitalWrite(LED3, HIGH);
    delay(300);
    digitalWrite(LED1, HIGH);
    delay(300);
    if(val==HIGH){
      cont1<<1;
      }
     else if(val1==HIGH){
      cont2<<1;
      }
     else{Serial.printf("a c mamo");}    
}
if(cont1 ==10000000){
  digitalWrite(LED2, HIGH);}
if(cont2 == 10000000){
    digitalWrite(LED4, HIGH);}
}

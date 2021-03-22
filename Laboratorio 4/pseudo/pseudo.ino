//pseudo codigo santiago galicia
//18483

#define LED RED_LED
#define LED1 GREEN_LED
#define LED2 BLUE_LED
const int buttonPin1 = PUSH1;
const int buttonPin2 = PUSH2;

int val =0;
int val1 = 0;
int cont1=B00000001;
int cont2=B00000001;
int cont3 = 0;

void setup() {
    Serial.begin(115200);
  // put your setup code here, to run once:
  pinMode(LED, OUTPUT);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(buttonPin1, INPUT_PULLUP);
  pinMode(buttonPin2, INPUT_PULLUP);
}

void iniciar(){
      delay(100);
    digitalWrite(LED, HIGH);
    delay(1100);
    digitalWrite(LED1, HIGH);
    delay(1100);
    digitalWrite(LED, LOW);
    delay(1100);
    digitalWrite(LED1, LOW);
  }
void loop() {
  // put your main code here, to run repeatedly: 
  val= digitalRead(buttonPin1);
  delay(100);
  val1= digitalRead(buttonPin2);
  delay(100);
  if (val ==LOW || val1 == LOW) {
    if(cont3==0){
    cont3++;
  iniciar();
  }}
 if(val==LOW){
  delay(100);
  if(val ==HIGH){
      delay(100);
      cont1<<1;}
      }
 if(val1==LOW){
  delay(100);
  if(val ==HIGH){
      delay(100);
      cont2<<1;}
      }    

if(cont1 == 128){
  digitalWrite(LED2, HIGH);
  digitalWrite(LED1, LOW);
  digitalWrite(LED, LOW);}
if(cont2 == 128){
    digitalWrite(LED, HIGH);
    digitalWrite(LED2, HIGH);
    digitalWrite(LED1, LOW);}
}

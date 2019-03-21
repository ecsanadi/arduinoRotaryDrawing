/*

*/

// Variables for left control
int encoderLPinA = 5;
int encoderLPinB = 6;
int encoderLClk = 7;
int encoderLPos = 0;
int encoderLPinALast = LOW;
int l = LOW;

//Variables for right control
int encoderRPinA = 2;
int encoderRPinB = 3;
int encoderRClk = 4;
int encoderRPos = 0;
int encoderRPinALast = LOW;
int r = LOW;
int lButtonState = LOW;
int rButtonState = LOW;

void setup() {
  pinMode (encoderLPinA, INPUT);
  pinMode (encoderLPinB, INPUT);
  pinMode (encoderLClk, INPUT);
  pinMode (encoderRPinA, INPUT);
  pinMode (encoderRPinB, INPUT);
  pinMode (encoderRClk, INPUT);
  Serial.begin (9600);
}

void loop() {
  //Follow rotary states
  l = digitalRead(encoderLPinA);
  r = digitalRead(encoderRPinA);
  if ((encoderLPinALast == LOW) && (l == HIGH)) {
    if (digitalRead(encoderLPinB) == LOW) {
      encoderLPos--;
    } else {
      encoderLPos++;
    }
    Serial.print (encoderLPos);
    
  }
  if ((encoderRPinALast == LOW) && (r == HIGH)) {
    if (digitalRead(encoderRPinB) == LOW) {
      encoderRPos--;
    } else {
      encoderRPos++;
    }
    Serial.print (encoderRPos);   
  }
  
  //Check if clicked as push button
  lButtonState = digitalRead(encoderLClk);
  rButtonState = digitalRead(encoderRClk);
  if (lButtonState == HIGH)
  {
    Serial.print (lButtonState);
  }else{Serial.print (0);}
  if (rButtonState == HIGH)
  {
    Serial.print (rButtonState);
  }else{Serial.print (0);}
  encoderLPinALast = l;
  encoderRPinALast = r;
}

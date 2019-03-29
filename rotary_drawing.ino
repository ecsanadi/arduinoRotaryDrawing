/*

*/

//TODO: set as HID if Arduino Leonardo, Micro or Pro Micro (or Due, Zero, M0). Those can emulate a keyboard.

// Variables for left control
int encoderLPinA = 7;
int encoderLPinB = 6;
int encoderLSw = 5;
int encoderLPos = 0;
int encoderLPinALast = LOW;
int l = LOW;

//Variables for right control
int encoderRPinA = 4;
int encoderRPinB = 3;
int encoderRSw = 2;
int encoderRPos = 0;
int encoderRPinALast = LOW;
int r = LOW;

int lButtonState = LOW;
int rButtonState = LOW;
int lButtonState_last = LOW;
int rButtonState_last = LOW;

int counterl =0;
int counterr =0;



byte myByte = B00000000;


String output;

void setup() {
  pinMode (encoderLPinA, INPUT);
  pinMode (encoderLPinB, INPUT);
  pinMode (encoderLSw, INPUT_PULLUP);
  pinMode (encoderRPinA, INPUT);
  pinMode (encoderRPinB, INPUT);
  pinMode (encoderRSw, INPUT_PULLUP);
  Serial.begin (9600);
}

void loop() {
  //Follow rotary states
  myByte = B00000000;
  l = digitalRead(encoderLPinA);
  r = digitalRead(encoderRPinA);
  if ((encoderLPinALast == LOW) && (l == HIGH)) {
    if (digitalRead(encoderLPinB) == LOW) {      
      bitSet(myByte,3);
    } else {     
      bitSet(myByte,2);
    }   
  }
  encoderLPinALast = l;
  if ((encoderRPinALast == LOW) && (r == HIGH)) {
    if (digitalRead(encoderRPinB) == LOW) {     
      bitSet(myByte,1);
    } else {    
      bitSet(myByte, 0);
    }  
  }
  encoderRPinALast = r;
 
  //Check if clicked as push button
  lButtonState = digitalRead(encoderLSw);
  rButtonState = digitalRead(encoderRSw);
  if (lButtonState != lButtonState_last)
  {
    if (counterl % 2)
    {
      bitSet(myByte,5);
    }
    lButtonState_last = lButtonState;    
    counterl++;    
  }
  if (rButtonState != rButtonState_last)
  {
    if (counterr % 2)
    {
      bitSet(myByte,4);
    }
    rButtonState_last = rButtonState;
    counterr++;
  }
  if(myByte != B00000000)
  {
    Serial.write(myByte);
  }
  
}

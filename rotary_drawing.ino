/*

*/

//TODO: set as HID dev. if Arduino Leonardo, Micro or Pro Micro (or Due, Zero, M0). Those can emulate a keyboard.

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

double lastMillis = 0;
double currMillis = 0;
int interval = 1000;

byte myByte = B00000000;

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
  currMillis = millis();
  l = digitalRead(encoderLPinA);
  r = digitalRead(encoderRPinA);
  if ((encoderLPinALast == LOW) && (l == HIGH)) {
    if (digitalRead(encoderLPinB) == LOW) {
      encoderLPos-=1;
    } else {     
      encoderLPos+=1;
    }   
  }
  encoderLPinALast = l;
  
  if ((encoderRPinALast == LOW) && (r == HIGH)) {
    if (digitalRead(encoderRPinB) == LOW) {    
      encoderRPos-=1;
    } else {    
      encoderRPos+=1;
    }  
  }
  encoderRPinALast = r;

  if ( (currMillis - lastMillis > interval)  
    && (encoderLPos !=0 || encoderRPos != 0) 
    || ( abs(encoderLPos) > 62 || abs(encoderRPos) > 62 ) )
  {
    //left rotary moving
    if (encoderLPos != 0 )
    {      
      
      myByte = byte(encoderLPos);      
      myByte &= 0x7f;  
      
      //String myByteStr = String(myByte,BIN);   
      //Serial.print(myByteStr);
      Serial.write(myByte);
      encoderLPos = 0;
    }    
    
    if (encoderRPos != 0)
    {
      
      myByte = byte(encoderRPos);
      myByte |= 0x80;
      //myByte = 2;
      //String myByteStr = String(myByte,BIN);   
      //Serial.print(myByteStr);
      Serial.write(myByte);
      encoderRPos = 0;
    }       
    
    lastMillis = currMillis;
  }
 
  //Check if clicked as push button
  lButtonState = digitalRead(encoderLSw);
  rButtonState = digitalRead(encoderRSw);
  if (lButtonState != lButtonState_last)
  {
    if (counterl % 2)
    {
      myByte = B00000000;
      Serial.write(myByte);
    }
    lButtonState_last = lButtonState;    
    counterl++;    
  }
  if (rButtonState != rButtonState_last)
  {
    if (counterr % 2)
    {
      myByte = B10000000;
      Serial.write(myByte);
    }
    rButtonState_last = rButtonState;
    counterr++;
  }
  
  
}

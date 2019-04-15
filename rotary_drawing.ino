/*
This program counts the output of two rotary encoder and sends the result into serial port using one byte.
*/

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

//counters for avoid push button state duplication
int counterl =0;
int counterr =0;

//time measuring
double currMillis = 0;
double lastMillis = 0;
double lastMillis2 = 0;
int interval = 100;
int interval2 = 1000;

//output
byte myByte = B00000000;

//testing port and connection
byte incomingByte;         // should be: " "
byte detectionByte= 0x20;  // " "
byte outcomingByte= 0x2e;  // "."

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
  //save the current time
  currMillis = millis();  

  //answer for the query if needed
  if (Serial.available()) 
  {
    incomingByte = Serial.read();
    if(incomingByte == detectionByte){
      Serial.write(outcomingByte);
    }      
  }
  
  //Follow rotary states    
  // Left
  l = digitalRead(encoderLPinA);
  r = digitalRead(encoderRPinA);
  if ((encoderLPinALast == LOW) && (l == HIGH)) {
    if (digitalRead(encoderLPinB) == LOW) {
      encoderLPos-=3;
    } else {     
      encoderLPos+=3;
    }   
  }
  encoderLPinALast = l;
  // Right
  if ((encoderRPinALast == LOW) && (r == HIGH)) {
    if (digitalRead(encoderRPinB) == LOW) {    
      encoderRPos-=3;
    } else {    
      encoderRPos+=3;
    }  
  }
  encoderRPinALast = r;

  //send data if reach time or size
  if ( (currMillis - lastMillis > interval)  
    && (encoderLPos !=0 || encoderRPos != 0) 
    || ( abs(encoderLPos) > 62 || abs(encoderRPos) > 62 ) )
  {
    //send left rotary moving
    if (encoderLPos != 0 )
    {            
      myByte = byte(encoderLPos);      
      myByte &= 0x7f;  
      Serial.write(myByte);
      encoderLPos = 0;
    }    
    //send right rotary moving
    if (encoderRPos != 0)
    {      
      myByte = byte(encoderRPos);
      myByte |= 0x80;
      Serial.write(myByte);
      encoderRPos = 0;
    }      
    //set back time counter  
    lastMillis = currMillis;
  }
 
  //Check if clicked as push button
  lButtonState = digitalRead(encoderLSw);
  rButtonState = digitalRead(encoderRSw);
  //Left
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
  //Right
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



#include <Servo.h>
Servo servo1;  
Servo servo2;   
int pos = 180; 
int Thr=20;
int state;        // 0:Open 1:Moving 2:Closed
long duration,cm;  
int trigPin = A3;    
int echoPin = A4; 
unsigned long prevMillis = 0;
unsigned long currentMillis = 0;

void setup() 
{
  servo1.attach(A1); 
  servo2.attach(A2);
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  state = 0;  //Open
}  


void loop()
{ 
  currentMillis = millis();
  if(currentMillis - prevMillis >= 250)
    {
      measureDist();
      prevMillis = currentMillis;
    }
    
if(cm>5 && cm<Thr)      //Near Ground => Open
{ 
  if(state == 0)
    pos = 180;

  else
  {
    if(pos == 180)
      state = 0;
    else
      pos++;
  }
}
 
else if(cm>Thr)         //Away from Ground
{ 
  if(state == 2)      //closed
    pos = 0;

  else                // closing
  {
    if(pos == 0)
      state = 2;
    else
      pos--;
  } 
}
servo1.write(pos);
servo2.write(pos);
delayMicroseconds(15);
}

void measureDist()
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  pinMode(echoPin, INPUT);
  
  duration = pulseIn(echoPin, HIGH);
  cm = (duration/2) / 29.1;
 
  Serial.print("****measuring**** cm");
  Serial.print(cm);
  Serial.println();
}


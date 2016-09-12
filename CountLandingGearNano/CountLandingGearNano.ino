#include <Servo.h>
Servo servo1; 

int maxAngle=150;
int pos = maxAngle; 
int Thr=20;
int state;    
int trigPin = A3;    
int echoPin = A4; 

void setup()
{
  //Serial.begin(9600);
  servo1.attach(A1); 
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}
long duration, cm, count=0;

void loop()
{
  
  
  if(count%100==0)
    {
    measureDist();  
    //Serial.println("***************************Measuring***");
    }
  
/*
  Serial.print("State: ");
  Serial.print(state);
  Serial.print("  Position: ");
  Serial.print(pos);
  Serial.print("  Distance: ");
  Serial.println(cm);
*/
  if(cm>5 && cm<Thr)      //Near Ground => Open
    { 
     if(state == 0)
        pos = maxAngle;

     else
      {
       if(pos == maxAngle)
        state = 0;
       else
        {
         state = 1;
         pos++;
         //Serial.println("Opening...");
        }
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
    {
      state = 1;
      pos--;
      //Serial.println("Closing....");
    }
  } 
}

servo1.write(pos);

delayMicroseconds(100);  
  count++;
 }
  
long measureDist()
{
  
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  
  cm = (duration/29)/2;  
}


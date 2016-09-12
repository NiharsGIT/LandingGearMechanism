#include <Servo.h>
Servo servo1; 

int maxAngle=150;
int pos = maxAngle; 
int Thr=20;
int state;    
int trigPin = A3;    
int echoPin = A4; 
int cm[30]={0}, cmCount;
bool start = false;
float cmAvg;

void setup()
{
  //Serial.begin(9600);
  servo1.attach(A1); 
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}
long duration, count=0;

void loop()
{
  
  
  if(count%100==0)
    {
    measureDist();  
    if(!cm[30])
      start = true;
    //Serial.println("***************************Measuring***");
    }
  
/*
  Serial.print("State: ");
  Serial.print(state);
  Serial.print("  Position: ");
  Serial.print(pos);
  Serial.print("  Distance: ");
  Serial.println(cm[]);
*/
if(start)
{
  if(cmAvg < 20)      //Near Ground => Open
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
 
else if(cmAvg>20)         //Away from Ground
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
}
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
  
  cmAvg = 0;
  
  for(int i=29 ; i>0 ; i--)
     {
      cmAvg += cm[i];
      cm[i] = cm[i-1];
     }
     
  cm[0] = (duration/29)/2;
  cmAvg += cm[0];
  cmAvg = cmAvg/30;   
}


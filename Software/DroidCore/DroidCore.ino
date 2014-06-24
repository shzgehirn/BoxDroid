#include <Servo.h>

struct Actuator 
{
  Servo  ServoObj;
  byte   CurrentPosition;    
};

Actuator ServoActuator[10];//delcare 10 Servo Motor Object

byte CurrentStep;
byte FramePosition[10];
int  StepSize,Increment,i;
byte FrameFinish = 10;

unsigned long ServoTimer;

void setup()
{
  ServoActuator[0].ServoObj.attach(1);
  ServoActuator[1].ServoObj.attach(2);
  ServoActuator[2].ServoObj.attach(3);
  ServoActuator[3].ServoObj.attach(4);
  ServoActuator[4].ServoObj.attach(5);
  ServoActuator[5].ServoObj.attach(6);
  ServoActuator[6].ServoObj.attach(7);
  ServoActuator[7].ServoObj.attach(8);
  ServoActuator[8].ServoObj.attach(9);
  ServoActuator[9].ServoObj.attach(10);
}

void loop()
{
  
}

void action()
{  
  int FrameStatus;
  if((millis() - ServoTimer) >= 20)
  {
    FrameFinish = 10;
    for(i=0; i++; i<10)
    {
      FrameStatus = Move(i,FramePosition[i]);
      if(FrameStatus == 0)
        FrameFinish--;  
    }    
    ServoTimer = millis();
  }
}

void UpdatePosition()
{
  
}

int Move(byte channel, byte target)
{
 int newIcrement = 0;   
 newIcrement = IncrementCal(ServoActuator[channel].CurrentPosition, target);
 ServoActuator[channel].CurrentPosition += newIcrement;
 ServoActuator[0].ServoObj.write(ServoActuator[channel].CurrentPosition);  
 return newIcrement;
}

int IncrementCal(byte CurrentPos, byte TargetPos)
{
 static int check = 0; 
 static int IncResult = 0; 
 check = CurrentPos-TargetPos;
 if((check>=(-StepSize))&check<0)
   IncResult = -check;
 else if((check<StepSize)&check<0)
   IncResult = StepSize;
 
 if((check<=StepSize)&check>0)
   IncResult = -check;
 else if((check>StepSize)&check>0)
   IncResult = -StepSize;
   
 if(check==0)
   IncResult = 0;
   
 return IncResult;
}   




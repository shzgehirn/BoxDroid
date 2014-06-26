#include <Servo.h>

#define INIT_POSE 0

struct Actuator//Servo Object Wrapper Declaration 
{
  Servo  ServoObj;
  byte   CurrentPosition;    
  byte   Speed;
};

Actuator ServoActuator[10];//delcare 10 Servo Motor Object

//global variable
byte CurrentStep;
byte FramePosition[10] = {0,0,0,0,0,0,0,0,0,0};//buffer to store action frame position
int  StepSize,i;
unsigned short FrameFinish, Flag;//16-bits flag to check servo status

int servo_en = 13;

unsigned long ServoTimer;

void setup()
{
  StepSize = 1;
 
  pinMode(servo_en, OUTPUT); 
  digitalWrite(servo_en, LOW);   
  
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
  
  ServoActuator[2].CurrentPosition = 45;
  ServoActuator[2].ServoObj.write(ServoActuator[2].CurrentPosition); 
  ServoActuator[3].Speed = 5;
  ServoActuator[2].Speed = 1;
  //action(INIT_POSE);//Make droid initial pose
  FrameFinish = 0x000;
  ServoTimer = millis();
}

void loop()
{
  action(1);  
}

void action(byte action_number)
{  
  int MotorStatus;
  
  if((millis() - ServoTimer) >= 20)
  {    
    
    for(i=0; i<10; i++)
    {
      digitalWrite(servo_en, HIGH);
      MotorStatus = Move(i,FramePosition[i]);
      if((MotorStatus == 0))
      {
        FrameFinish = (FrameFinish | (0x1<<i));
      }  
    } 
    ServoTimer = millis();
    if(FrameFinish == 0x3FF)
    {
      FrameFinish = 0x000;
      UpdatePosition();
    }
  }  
}

void UpdatePosition()
{
  
  static boolean p = true;
  if(p)
  {
    FramePosition[2] = 45;
    FramePosition[3] = 5;
    p = false;
  }
  else
  {
    FramePosition[2] = 135;
    FramePosition[3] = 180;
    p = true;
  }
}

int Move(byte channel, byte target)
{
 int newIcrement = 0;   
 newIcrement = IncrementCal(ServoActuator[channel].CurrentPosition, target, ServoActuator[channel].Speed);
 ServoActuator[channel].CurrentPosition += newIcrement;
 ServoActuator[channel].ServoObj.write(ServoActuator[channel].CurrentPosition);  
 return newIcrement;
}

int IncrementCal(byte CurrentPos, byte TargetPos, byte Speed)
{
 static int check = 0; 
 static int IncResult = 0; 
 check = CurrentPos-TargetPos;
 if((check>=(-Speed))&check<0)
   IncResult = -check;
 else if((check<Speed)&check<0)
   IncResult = Speed;
 
 if((check<=Speed)&check>0)
   IncResult = -check;
 else if((check>Speed)&check>0)
   IncResult = -Speed;
   
 if(check==0)
   IncResult = 0;
   
 return IncResult;
}   




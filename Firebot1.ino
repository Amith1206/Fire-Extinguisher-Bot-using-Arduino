/*c=clockwise ac=anticlockwise*/
#include <Servo.h>
Servo myservo;
 
int pos = 0;    
boolean fire = false;
 
#define Left_S A0      // left sensor
#define Right_S A1      // right sensor
#define Forward_S A2 //forward sensor
#define Fire_S 8
 //backward sensor

 

#define LM1 2       // left motor c
#define LM2 3       // left motor ac
#define RM1 4       // right motor c
#define RM2 5       // right motor ac
#define pump 6
void setup()
{
  pinMode(Left_S, INPUT);
  pinMode(Right_S, INPUT);
  pinMode(Forward_S, INPUT);
  pinMode(LM1, OUTPUT);
  pinMode(LM2, OUTPUT);
  pinMode(RM1, OUTPUT);
  pinMode(RM2, OUTPUT);
  pinMode(pump, OUTPUT);
 
  myservo.attach(11);
  myservo.write(90);
  //Serial.begin(9600); 
}
 
void put_off_fire()
{
    
 
    digitalWrite(LM1, HIGH);
    digitalWrite(LM2, HIGH);
    digitalWrite(RM1, HIGH);
    digitalWrite(RM2, HIGH);
    
   digitalWrite(pump, HIGH);
   delay(500);
    
    for (pos = 50; pos <= 130; pos += 1) { 
    myservo.write(pos); 
    delay(10);  
  }
  for (pos = 130; pos >= 50; pos -= 1) { 
    myservo.write(pos); 
    delay(10);
  }
  
  digitalWrite(pump,LOW);
  myservo.write(90);
  
  fire=false;
}
 
void loop()
{

//Serial.println(analogRead(Forward_S));
//Serial.println(analogRead(Right_S));
//Serial.println(analogRead(Left_S));


   myservo.write(90); //Sweep_Servo();  
 
    if ((analogRead(Left_S) >850 && analogRead(Right_S)>850 && analogRead(Forward_S) >850)) //If Fire not detected all sensors are zero
    {
    //Do not move the robot
    digitalWrite(LM1, LOW);
    digitalWrite(LM2, LOW);
    digitalWrite(RM1, LOW);
    digitalWrite(RM2, LOW);
    }
  //  else if(digitalRead(Fire_S)==0)
  //  {
//   fire==true;
//    }
    
    else if ((analogRead(Forward_S) <analogRead(Right_S) && analogRead(Right_S) <analogRead(Left_S))||(analogRead(Forward_S) <analogRead(Left_S) && analogRead(Left_S) <analogRead(Right_S))) //If Fire is straight ahead
    {
    //Move the robot forward
    digitalWrite(LM1, HIGH);
    digitalWrite(LM2, LOW);
    digitalWrite(RM1, HIGH);
    digitalWrite(RM2, LOW);
    
    }
    
    else if ((analogRead(Left_S) <analogRead(Right_S) && analogRead(Right_S) <analogRead(Forward_S))||(analogRead(Left_S) <analogRead(Forward_S) && analogRead(Forward_S) <analogRead(Right_S))) //If Fire is to the left
    {
    //Move the robot left
    digitalWrite(LM1, LOW);
    digitalWrite(LM2, HIGH);
    digitalWrite(RM1, LOW);
    digitalWrite(RM2, LOW);
    }
    
    else if ((analogRead(Right_S) <analogRead(Left_S) && analogRead(Left_S) <analogRead(Forward_S))||(analogRead(Right_S) <analogRead(Forward_S) && analogRead(Forward_S) <analogRead(Right_S))) //If Fire is to the right
    {
    //Move the robot right
    digitalWrite(LM1, LOW);
    digitalWrite(LM2, LOW);
    digitalWrite(RM1, LOW);
    digitalWrite(RM2, HIGH);
    }
    
   
    
    
delay(300); //Slow down the speed of robot
 
     while (digitalRead(Fire_S)==0)
     {
      put_off_fire();
     }
}

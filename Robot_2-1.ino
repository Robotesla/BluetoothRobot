#define cmdL 'L'
#define cmdR 'R'
char incomingByte;
char L_Data[4];
byte L_index = 0;
char R_Data[4];
byte R_index = 0;
char command;
//#include <Servo.h>
#include <AFMotor.h>
//#define trigPin 2
//#define echoPin 13
#define delay_turn_time 20
AF_DCMotor motor_e1(3);
AF_DCMotor motor_e2(4);
//Servo SRV1;
//Servo SRV2;
//int d1,d2;
void set_speed(int speed)
{
  motor_e1.setSpeed(255);
  motor_e2.setSpeed(255);
}
void robot_forward()
{
  motor_e1.run(FORWARD);
  motor_e2.run(FORWARD);
}
void robot_backward()
{
  motor_e1.run(BACKWARD);
  motor_e2.run(BACKWARD);
}
void robot_release()
{
  //Serial.println("Stop");
  motor_e1.run(RELEASE);
  motor_e2.run(RELEASE);
}
void turning_to_the_right()
{
  motor_e1.run(BACKWARD);
  motor_e2.run(FORWARD);
  delay(delay_turn_time);
}
void turning_to_the_left()
{
  motor_e1.run(FORWARD);
  motor_e2.run(BACKWARD);
  delay(delay_turn_time);
}
//int get_distance()
//{
//long duration; 
//int d1,d2,average=d1+d2/2;
  //digitalWrite(trigPin, LOW);
  //delayMicroseconds(2);
  //digitalWrite(trigPin, HIGH);
  //delayMicroseconds(10);
  //digitalWrite(trigPin, LOW);
  //duration = pulseIn(echoPin,HIGH);
  //d1=(int)duration/58.2;
  
  //digitalWrite(trigPin,LOW);
  //delayMicroseconds(2);
  //digitalWrite(trigPin,HIGH);
  //delayMicroseconds(10);
  //digitalWrite(trigPin,LOW);
  //duration=pulseIn(echoPin,HIGH);
  //d2=(int)duration/58.2;
  
  //average=(int) (d1+d2)/2;
  //Serial.print("distance:");
  //Serial.println(average);
  //return average;
//}

void Control4WD(int mLeft, int mRight)
{
  bool directionL, directionR;
  int valueL, valueR;
  if(mLeft > 0)
  {
    valueL = mLeft;
    directionL = 0;
  }
  else if(mLeft < 0)
  {
    valueL = abs(mLeft);
    directionL = 1;
  }
  else
  {
    directionL = 0;
    valueL = 0;
  }
  if(mRight > 0)
  {
    valueR = mRight;
    directionR = 0;
  }
  else if(mRight < 0)
  {
    valueR = abs(mRight);
    directionR = 1;
  }
  else
  {
    directionR = 0;
    valueR = 0;
  }
  motor_e1.setSpeed(valueR);
  motor_e2.setSpeed(valueL);
  if(directionR == 0)
  {
    motor_e1.run(FORWARD);
//    delay(100);
  }
  else
  {
    motor_e1.run(BACKWARD);
//    delay(100);
  }
  if(directionL == 0)
  {
    motor_e2.run(FORWARD);
//    delay(100);
  }
  else
  {
    motor_e2.run(BACKWARD);
//    delay(100);
  }
  if(valueR == 0)
  {
    motor_e1.run(RELEASE);
  }
  if(valueL == 0)
  {
    motor_e2.run(RELEASE);
  }
  //if(directionR == 0)
  //{
 //   motor_e1.run(RELEASE);
 // }
}

void setup()
{
  Serial.begin(9600);
  motor_e1.setSpeed(255);
  motor_e2.setSpeed(255);
  motor_e1.run(RELEASE);
  motor_e2.run(RELEASE);
  //pinMode(trigPin,OUTPUT);
  //pinMode(echoPin,INPUT);
  //SRV1.attach(10);
  //SRV2.attach(9);
  //SRV1.write(90);
  //SRV2.write(120);
  //set_speed(200);
  //robot_forward();
}
void loop()
{
  if(Serial.available() > 0)
  {
    incomingByte=Serial.read();
    if(incomingByte == cmdL)
    {
      command = cmdL;
      memset(L_Data,0,sizeof(L_Data));
      L_index = 0;
    }
    else if(incomingByte == cmdR)
    {
      command = cmdR;
      memset(R_Data,0,sizeof(R_Data));
      R_index = 0;
    }
    else if(incomingByte == '\r') command = 'e';
    if((command == cmdL) && (incomingByte != cmdL))
    {
      L_Data[L_index] = incomingByte;
      L_index++;
    }
    else if((command == cmdR) && (incomingByte != cmdR))
    {
      R_Data[R_index] = incomingByte;
      R_index++;
    }
    else if(command == 'e')
    {
      Control4WD(atoi(L_Data),atoi(R_Data));
      delay(10);
    }
  }
  //if(get_distance()<30)
  //{
    //robot_release();
    //SRV1.write(155);
    //delay(1000);
    //d1=get_distance();
    //SRV1.write(30);
    //delay(1000);
    //d2=get_distance();
    //if(d1<d2)
   //{
      //Serial.print("turn_to_the_right");
      //turning_to_the_right();
   //}
  //else
    //{
      //Serial.print("turn_to_the_left");
      //turning_to_the_left();
    //}
    //SRV1.write(90);
    //delay(500);
    //robot_forward();   
  //}
}


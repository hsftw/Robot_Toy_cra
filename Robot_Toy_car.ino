/* Robot Toy car
  藍牙HC-06 2,3
  減速馬達1:150
  馬達控制板L9110 5,9 6,10
  超音波測距HC-SR04 12,13
  伺服馬達SG90 8
*/
#include <Ultrasonic.h>
#include <Servo.h>
#include <SoftwareSerial.h>

#define TRIGGER_PIN  12
#define ECHO_PIN     13

SoftwareSerial BT(2,3);//藍芽接收傳送腳
char command;//BT接收的資訊
Ultrasonic ultrasonic(TRIGGER_PIN, ECHO_PIN);
Servo myservo; // 建立Servo物件，控制伺服馬達

int x;

const int AIA = 9;  // (pwm) pin 9 connected to pin A-IA 
const int AIB = 5;  // (pwm) pin 5 connected to pin A-IB 
const int BIA = 10; // (pwm) pin 10 connected to pin B-IA  
const int BIB = 6;  // (pwm) pin 6 connected to pin B-IB 

byte speed = 255;  // change this (0-255) to control the speed of the motors 

void setup() {
  BT.begin(9600);//啟動軟體序列埠
  Serial.begin(9600);
  myservo.attach(8); // 連接數位腳位8，伺服馬達的訊號線
  
  pinMode(AIA, OUTPUT); // set pins to output
  pinMode(AIB, OUTPUT);
  pinMode(BIA, OUTPUT);
  pinMode(BIB, OUTPUT);
}

void loop() {
  float cmMsec, inMsec;
  long microsec = ultrasonic.timing();
  
  cmMsec = ultrasonic.convert(microsec, Ultrasonic::CM);
  inMsec = ultrasonic.convert(microsec, Ultrasonic::IN);
  Serial.print(",    MS: ");
  Serial.print(microsec);
  //判斷MS是否低於500
  if(microsec<500)//前方有障礙
  {
    for(int i=90 ; i<180 ; i =i+15)//see轉左
    {
      myservo.write(i);// 使用write，傳入角度
      Stop();
      delay(100);
      BTcontrcl();//BT控制
    }
    microsec = ultrasonic.timing();
    if(microsec<500)//左方是否有障礙
    {
      for(int i=180 ; i>0 ; i =i-15)//see轉右
      {
        myservo.write(i);// 使用write，傳入角度
        Stop();
        delay(100);
        BTcontrcl();
      }
      microsec = ultrasonic.timing();
      if(microsec<500)//右方是否有障礙
      {
        backward();
        delay(2000);
        microsec = ultrasonic.timing();
        if(microsec>500)//右方是否有障礙
        {
          right();
          delay(1000);
        }
        for(int i=180 ; i>90 ; i =i-15)
        {
          myservo.write(i);// 使用write，傳入角度
          Stop();
          delay(100);
          BTcontrcl();
        }
      }
      else//右方沒障礙右轉
      {
        right();
        delay(1000);
        for(int i=180 ; i>90 ; i =i-15)
        {
          myservo.write(i);// 使用write，傳入角度
          Stop();
          delay(100);
          BTcontrcl();
        }
        BTcontrcl();//BT控制
      }
    }
    else//左方沒障礙左轉
    {
      left();//左轉
      delay(1000);
      for(int i=180 ; i>90 ; i =i-15)
      {
        myservo.write(i);// 使用write，傳入角度
        Stop();
        delay(100);
        BTcontrcl();
      }
      BTcontrcl();//BT控制
    }
  }
  else
  {
    forward(); 
    BTcontrcl();//BT控制
  }

  
  //forward(); 
  //delay(1000);
  //backward();
  //delay(500);
  //left();
  //delay(1000);
  //right();
  //delay(1000);
}

void BTcontrcl()//藍芽控制
{
  if (BT.available()>0)
  {
    command = BT.read();//讀取BT
    
    switch (command)
    {
      case 'L' ://左轉
        left();
        delay(2000);
        break;
      case 'R' ://右轉
        right();
        delay(2000);
        break;
      case 'B' ://前進
        forward();
        break;
      case 'S' ://停止
        Stop();
        delay(5000);
        break;
      case 'A' ://後退
        backward();
        delay(2000);
        break;
      default :
        break;
    }
  }
}

void backward()
{
  analogWrite(AIA, 0);
  analogWrite(AIB, speed);
  analogWrite(BIA, 0);
  analogWrite(BIB, speed);
}

void forward()
{
  analogWrite(AIA, speed);
  analogWrite(AIB, 0);
  analogWrite(BIA, speed);
  analogWrite(BIB, 0);
}

void left()
{
  analogWrite(AIA, speed);
  analogWrite(AIB, 0);
  analogWrite(BIA, 0);
  analogWrite(BIB, speed);
}

void right()
{
  analogWrite(AIA, 0);
  analogWrite(AIB, speed);
  analogWrite(BIA, speed);
  analogWrite(BIB, 0);
}

void Stop()
{
  analogWrite(AIA, 0);
  analogWrite(AIB, 0);
  analogWrite(BIA, 0);
  analogWrite(BIB, 0);
}

#include <Ultrasonic.h>
#include <Servo.h>
#include <SoftwareSerial.h>

#define TRIGGER_PIN  12
#define ECHO_PIN     13

SoftwareSerial BT(10,11);//藍芽接收傳送腳
char command;//BT接收的資訊
Ultrasonic ultrasonic(TRIGGER_PIN, ECHO_PIN);
Servo myservo; // 建立Servo物件，控制伺服馬達

int x;
void setup() 
{ 
  BT.begin(9600);//啟動軟體序列埠
  Serial.begin(9600);
  //步進馬達設定
  pinMode(5,OUTPUT); //Enable 
  pinMode(4,OUTPUT); //Step 
  pinMode(3,OUTPUT); // Dir 
  digitalWrite(5,LOW); // Set Enable low 
  pinMode(8,OUTPUT); //Enable 
  pinMode(7,OUTPUT); //Step 
  pinMode(6,OUTPUT); // Dir 
  digitalWrite(8,LOW); // Set Enable low
  myservo.attach(9); // 連接數位腳位9，伺服馬達的訊號線
}

void loop() 
{
  float cmMsec, inMsec;
  long microsec = ultrasonic.timing();
  
  cmMsec = ultrasonic.convert(microsec, Ultrasonic::CM);
  inMsec = ultrasonic.convert(microsec, Ultrasonic::IN);
  Serial.print(",    MS: ");
  Serial.print(microsec);
//判斷MS是否低於500,低於500又ㄝ則右轉,否則直走
  if(microsec>1500)
  {
    for(int i=45 ; i<135 ; i =i+15)
    {
      myservo.write(i);// 使用write，傳入角度
      BTcontrcl();//BT控制
      Straight();//直走
    }
    for(int i=135 ; i>45 ; i =i-15)
    {
      myservo.write(i);// 使用write，傳入角度
      BTcontrcl();
      Straight();//直走
    }   
  }
  else
  {
    if (microsec>300)
    {
      Turn_left();//左轉
      BTcontrcl();
    }
    else
    {
      Pull_out();//後退
      BTcontrcl();
    }
  }
}

void BTcontrcl()//藍芽控制
{
  if (BT.available()>0)
  {
    command = BT.read();//讀取BT
    
    switch (command)
    {
      case 'L' ://左轉
        Turn_left();
        break;
      case 'R' ://右轉
        Turn_right();
        break;
      case 'A' ://前進
        Pull_out();
        break;
      case 'S' ://停止
        Stop();
        break;
      case 'B' ://後退
        Straight();
        break;
      default :
        break;
    }
  }
}

void Stop()//停止5秒
{
  digitalWrite(5,HIGH);
  digitalWrite(8,HIGH);
  delay(5000);
  digitalWrite(5,LOW);
  digitalWrite(8,LOW);
}

void Straight()//直走
{
  digitalWrite(3,HIGH); // Set Dir high
  digitalWrite(6,LOW); // Set Dir high
  for(x = 0; x < 200; x++) // Loop 200 times 
  { 
    digitalWrite(4,HIGH); // Output high
    digitalWrite(7,HIGH); // Output high
    delayMicroseconds(500); // Wait 1/2 a ms 
    digitalWrite(4,LOW); // Output low 
    digitalWrite(7,LOW); // Output low 
    delayMicroseconds(500); // Wait 1/2 a ms 
  }
}
void Turn_left()//左轉
{
  digitalWrite(3,HIGH); // Set Dir high
  digitalWrite(6,HIGH); // Set Dir high
  for(x = 0; x < 2000; x++) // Loop 200 times 
  { 
    digitalWrite(4,HIGH); // Output high
    digitalWrite(7,HIGH); // Output high
    delayMicroseconds(500); // Wait 1/2 a ms 
    digitalWrite(4,LOW); // Output low 
    digitalWrite(7,LOW); // Output low 
    delayMicroseconds(500); // Wait 1/2 a ms 
  }
}
void Turn_right()//右轉
{
  digitalWrite(3,LOW); // Set Dir high
  digitalWrite(6,LOW); // Set Dir high
  for(x = 0; x < 2000; x++) // Loop 200 times 
  { 
    digitalWrite(4,HIGH); // Output high
    digitalWrite(7,HIGH); // Output high
    delayMicroseconds(500); // Wait 1/2 a ms 
    digitalWrite(4,LOW); // Output low 
    digitalWrite(7,LOW); // Output low 
    delayMicroseconds(500); // Wait 1/2 a ms 
  }
}
void Pull_out()//後退
{
  digitalWrite(3,LOW); // Set Dir high
  digitalWrite(6,HIGH); // Set Dir high
  for(x = 0; x < 3000; x++) // Loop 200 times 
  { 
    digitalWrite(4,HIGH); // Output high
    digitalWrite(7,HIGH); // Output high
    delayMicroseconds(500); // Wait 1/2 a ms 
    digitalWrite(4,LOW); // Output low 
    digitalWrite(7,LOW); // Output low 
    delayMicroseconds(500); // Wait 1/2 a ms 
  }
}

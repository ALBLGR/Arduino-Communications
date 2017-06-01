//============================智宇科技===========================
//  智能小车前进实验
//===============================================================
//#include <Servo.h> 
#include <LiquidCrystal.h> //鐢虫槑1602娑叉櫠鐨勫嚱鏁板簱
#include <Wire.h>

int Left_motor_go=12;     //左电机前进(IN1)
int Left_motor_back=10;     //左电机后退(IN2)

int Right_motor_go=13;    // 右电机前进(IN3)
int Right_motor_back=11;    // 右电机后退(IN4)

LiquidCrystal lcd(8,7,6,5,4,3,2); //4数据口模式连线声明
int i;


int Echo = A1;  // Echo回声脚(P2.0)
int Trig =A2;  //  Trig 触发脚(P2.1)
int Distance = 0;


int SL_2;    //左红外传感器状态
int SR_2;    //右红外传感器状态

void setup()
{
  Serial.begin(9600);     // 初始化串口
  Wire.begin(4);
  Wire.onReceive(receiveEvent);
  //初始化电机驱动IO为输出方式
  //初始化超声波引脚
  pinMode(Echo, INPUT);    // 定义超声波输入脚
  pinMode(Trig, OUTPUT);   // 定义超声波输出脚
 
  

  lcd.begin(16,2);      //初始化1602液晶工作                       模式
                       //定义1602液晶显示范围为2行16列字符
                       
   lcd.home();        //把光标移回左上角，即从头开始输出   
    lcd.print("Hello World!"); //显示
   
 
  //初始化电机驱动IO为输出方式
  pinMode(Left_motor_go,OUTPUT); // PIN 8 8脚无PWM功能
  pinMode(Left_motor_back,OUTPUT); // PIN 9 (PWM)
  pinMode(Right_motor_go,OUTPUT);// PIN 10 (PWM) 
  pinMode(Right_motor_back,OUTPUT);// PIN 11 (PWM)
  


}

char commandArray [7];

void receiveEvent(int howMany)
{
  int i=0;
  lcd.clear();
  lcd.setCursor(0,0);
  Serial.println("");
  Serial.print("wire rx ");
  char c;
// 循环读取接收到的数据，最后一个数据单独读取
  while( Wire.available()>0)
  {
     c= Wire.read(); // 以字符形式接收数据
    Serial.print(c);       // 串口输出该字符
    i++;
    if(i==11){
    lcd.setCursor(0,1);
    }
    if(i>=11 && i<=17){
    commandArray[i-11] = c;
    }
  lcd.print(c);
} 
  lcd.print(Distance);
    Serial.println("");
   
 int timeout = (int)(commandArray[5])-48;  
 Serial.println(timeout);
 Serial.println("!!!");
 Serial.println((char)commandArray[0]);
  Serial.println((char)commandArray[1]);
   Serial.println((char)commandArray[2]);
    Serial.println((char)commandArray[3]);
     Serial.println((char)commandArray[4]);
      Serial.println((char)commandArray[5]);
       Serial.println((char)commandArray[6]);

   if((char)commandArray[0]=='F'&&(char)commandArray[1]=='O'&&(char)commandArray[2]=='R'&&(char)commandArray[3]=='W'&&(char)commandArray[4]=='D'){
   advance();
      Serial.println("go");
   }
 if((char)commandArray[0]=='B'&&(char)commandArray[1]=='A'&&(char)commandArray[2]=='C'&&(char)commandArray[3]=='K'&&(char)commandArray[4]=='S'){
   back(0);
      Serial.println("bk");
   } if((char)commandArray[0]=='S'&&(char)commandArray[1]=='T'&&(char)commandArray[2]=='O'&&(char)commandArray[3]=='P'&&(char)commandArray[4]=='S'){
   brake(0);
      Serial.println("stop");
   } if((char)commandArray[0]=='L'&&(char)commandArray[1]=='E'&&(char)commandArray[2]=='F'&&(char)commandArray[3]=='T'&&(char)commandArray[4]=='S'){
   left();
      Serial.println("lt");
   } if((char)commandArray[0]=='R'&&(char)commandArray[1]=='I'&&(char)commandArray[2]=='G'&&(char)commandArray[3]=='H'&&(char)commandArray[4]=='T'){
   right();
      Serial.println("RT");
   }
  
   
}

void requestEvent() {
//  Distance_test();
//  int h,t,o;
//  if (Distance<1000){
//    h=(int)(Distance%1000);
//    Wire.write(h); // respond with message of 6 bytes
//
//  
//  }
//    Serial.println(h);
//  // as expected by master
}

void Distance_test()   // 量出前方距离 
{
  digitalWrite(Trig, LOW);   // 给触发脚低电平2μs
  delayMicroseconds(2);
  digitalWrite(Trig, HIGH);  // 给触发脚高电平10μs，这里至少是10μs
  delayMicroseconds(10);
  digitalWrite(Trig, LOW);    // 持续给触发脚低电
  float Fdistance = pulseIn(Echo, HIGH);  // 读取高电平时间(单位：微秒)
  Fdistance= Fdistance/58;       //为什么除以58等于厘米，  Y米=（X秒*344）/2
  // X秒=（ 2*Y米）/344 ==》X秒=0.0058*Y米 ==》厘米=微秒/58
  Serial.print("Distance:");      //输出距离（单位：厘米）
  Serial.println(Fdistance);         //显示距离
  Distance = Fdistance;
}  

//=======================智能小车的基本动作=========================
//void run(int time)     // 前进
void run()     // 前进
{
  //advance();
}


void advance(){
  
  digitalWrite(Right_motor_go,HIGH);  // 右电机前进
  digitalWrite(Right_motor_back,LOW);     
  analogWrite(Right_motor_go,180);//PWM比例0~255调速，左右轮差异略增减
  analogWrite(Right_motor_back,0);
  digitalWrite(Left_motor_go,HIGH);  // 左电机前进
  digitalWrite(Left_motor_back,LOW);
  analogWrite(Left_motor_go,180);//PWM比例0~255调速，左右轮差异略增减
  analogWrite(Left_motor_back,0);
//  delay(1000);   //执行时间，可以调整  
}
void brake(int time)  //刹车，停车
{
  digitalWrite(Right_motor_go,LOW);
  digitalWrite(Right_motor_back,LOW);
  digitalWrite(Left_motor_go,LOW);
  digitalWrite(Left_motor_back,LOW);
 // delay(time * 100);//执行时间，可以调整  
}

//void left(int time)         //左转(左轮不动，右轮前进)
void left()         //左转(左轮不动，右轮前进)
{
   digitalWrite(Right_motor_go,HIGH);	// 右电机前进
  digitalWrite(Right_motor_back,LOW);
  analogWrite(Right_motor_go,130); 
  analogWrite(Right_motor_back,0);//PWM比例0~255调速
  digitalWrite(Left_motor_go,LOW);   //左轮后退
  digitalWrite(Left_motor_back,LOW);
  analogWrite(Left_motor_go,0); 
  analogWrite(Left_motor_back,0);//PWM比例0~255调速
  //delay(time * 100);	//执行时间，可以调整  
}

void spin_left(int time)         //左转(左轮后退，右轮前进)
{
   digitalWrite(Right_motor_go,HIGH);	// 右电机前进
  digitalWrite(Right_motor_back,LOW);
  analogWrite(Right_motor_go,130); 
  analogWrite(Right_motor_back,0);//PWM比例0~255调速
  digitalWrite(Left_motor_go,LOW);   //左轮后退
  digitalWrite(Left_motor_back,HIGH);
  analogWrite(Left_motor_go,0); 
  analogWrite(Left_motor_back,130);//PWM比例0~255调速
  //delay(time * 100);	//执行时间，可以调整    
}

//void right(int time)
void right()        //右转(右轮不动，左轮前进)
{
   digitalWrite(Right_motor_go,LOW);   //右电机后退
  digitalWrite(Right_motor_back,LOW);
  analogWrite(Right_motor_go,0); 
  analogWrite(Right_motor_back,0);//PWM比例0~255调速
  digitalWrite(Left_motor_go,HIGH);//左电机前进
  digitalWrite(Left_motor_back,LOW);
  analogWrite(Left_motor_go,130); 
  analogWrite(Left_motor_back,0);//PWM比例0~255调速
  //delay(time * 100);	//执行时间，可以调整  
}

void spin_right(int time)        //右转(右轮后退，左轮前进)
{
  digitalWrite(Right_motor_go,LOW);   //右电机后退
  digitalWrite(Right_motor_back,HIGH);
  analogWrite(Right_motor_go,0); 
  analogWrite(Right_motor_back,130);//PWM比例0~255调速
  digitalWrite(Left_motor_go,HIGH);//左电机前进
  digitalWrite(Left_motor_back,LOW);
  analogWrite(Left_motor_go,130); 
  analogWrite(Left_motor_back,0);//PWM比例0~255调速
  delay(time * 100);	//执行时间，可以调整      
}

void back(int time)          //后退
{
  digitalWrite(Right_motor_go,LOW);  //右轮后退
  digitalWrite(Right_motor_back,HIGH);
  analogWrite(Right_motor_go,0);
  analogWrite(Right_motor_back,180);//PWM比例0~255调速
  digitalWrite(Left_motor_go,HIGH);  //左轮后退
  digitalWrite(Left_motor_back,LOW);
  analogWrite(Left_motor_go,0);
  analogWrite(Left_motor_back,180);//PWM比例0~255调速
  delay(time * 100);     //执行时间，可以调整  
}

void loop()
{
  Distance_test();
  if(Distance<20){
  brake(0);
  analogWrite(A3,200);
  }
  else{
  analogWrite(A3,0);
  }
// Serialreading();
// distanceDisplay();
    //Distance_test();
 /* digitalWrite(greenled, LOW);
  //keysacn();	   //调用按键扫描函数
  while(1)
  {
    //有信号为LOW  没有信号为HIGH
    SR_2 = digitalRead(SensorRight_2);
    SL_2 = digitalRead(SensorLeft_2);
    distanceDisplay();
    
    if (SL_2 == HIGH&& SR_2==HIGH && Distance>20)
    {
        digitalWrite(greenled, HIGH);//点亮红色小灯
        digitalWrite(yellowled, LOW);//点亮红色小灯
        lcd.print(" ALL CLR");
      advance();   //调用前进函数
    }
    else if (SL_2 == HIGH & SR_2 == LOW  && Distance<20)// 右边探测到有障碍物，有信号返回，向左转 
       {
            digitalWrite(yellowled, HIGH);//点亮红色小灯
    digitalWrite(greenled, LOW);//点亮红色小灯
         lcd.print(" RT BLK"); 
         left();
       }
    else if (SR_2 == HIGH & SL_2 == LOW && Distance<20) //左边探测到有障碍物，有信号返回，向右转  
     {
       lcd.print(" LT BLK"); 
          digitalWrite(yellowled, HIGH);//点亮红色小灯
    digitalWrite(greenled, LOW);//点亮红色小灯
       right();
     }
    else // 都是有障碍物, 后退
    {
       lcd.print(" ALL BLK"); 
         digitalWrite(yellowled, HIGH);//点亮红色小灯
    digitalWrite(greenled, LOW);//点亮红色小灯
      back(4.5);//后退
      spin_right(4.5);//有旋转，调整方向
    }
  }*/
   
}
  
void distanceDisplay(){
   Distance_test();
  
}

int incomingByte =  0; 
void Serialreading(){
{
  delay(500);
 lcd.clear();
 incomingByte = Serial.read();  
    lcd.println("I received: ");  

    
     lcd.setCursor(1,2);   //把光标定位在第2行，第6列
    lcd.println(incomingByte);
    Serial.println("I received: ");
     Serial.println(incomingByte,DEC);
    if(incomingByte=='1'){
    advance();
   
    }
    else if(incomingByte=='2')
    back(10);
    else if(incomingByte=='3')
    left();
    else if(incomingByte=='4')
    right();
    else if(incomingByte=='5')
    spin_left(10);
    else if(incomingByte=='6')
    spin_right(10);
    else if(incomingByte=='7')
    brake(10);
     
     delay(1000);  
     
}

}
/*
void loop()
{
Serialreading();
  
  
  distanceDisplay();
  brake(10);
  distanceDisplay();
  advance();
  delay(1000);
 
  distanceDisplay();
 brake( 10);
 distanceDisplay();
 back(10);
 	//前进
distanceDisplay();

  distanceDisplay();
  
}
*/



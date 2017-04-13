
#include <LiquidCrystal.h> //申明1602液晶的函数库
//申明1602液晶的引脚所连接的Arduino数字端口，8线或4线数据模式，任选其一
//LiquidCrystal lcd(12,11,10,9,8,7,6,5,4,3,2);   //8数据口模式连线声明
LiquidCrystal lcd(8,7,6,9,4,3,2); //4数据口模式连线声明
int Echo = A3;  // Echo回声脚(P2.0)
int Trig =A2;  //  Trig 触发脚(P2.1)
int beep = A4;

int redled=A0;
int greenled=A1;
int yellowled = A5;

const byte rxPin = 0;
const byte txPin = 1;
void setup()
{
  Serial.begin(9600);
  lcd.begin(16,2);  
     lcd.home();        //把光标移回左上角，即从头开始输出   
    lcd.print("Hello World"); //显示
    lcd.setCursor(0,1);   //把光标定位在第1行，第0列
    lcd.print("Welcome to Use!");       //显示 
 
}

 void access_granted(){
   
    lcd.setCursor(0,1);
    lcd.print("PASS"); //显示
  analogWrite(greenled, 230);
  delay(100);
  analogWrite(greenled, 0);
   delay(100);
    analogWrite(greenled, 230);
  delay(100);
  analogWrite(greenled, 0);
   delay(100);
    analogWrite(greenled, 0);
 
  }
   
    void access_denied(){
          
       lcd.setCursor(0,1);
       lcd.print("DENY"); //显示
  analogWrite(redled, 200);
  delay(500);
  analogWrite(redled, 0);
  }

boolean isPass(){
if (digitalRead(5)){
return true;
}
else{
//Serial.println(str);
  return false;
}  
}
void loop()
{


   lcd.home();        //把光标移回左上角，即从头开始输出   
  lcd.clear();
  lcd.print("Standby.");
   while (isPass() == false)
   {
   }
   access_granted();


  
  
  
  
}


void traffic(){
 
  analogWrite(redled, 200);
  for (int i =0; i<10; i++)
  {
     analogWrite(beep, 200);
     if(i==9)
     analogWrite(yellowled, 200);
     delay(100);
     analogWrite(beep,0);
     delay(900);
 }

   analogWrite(redled, 0);
   analogWrite(yellowled, 0);
  //////////////////////////////////////////// 
   analogWrite(greenled, 200);
    
   for (int i =0; i<20; i++)
  {
     analogWrite(beep, 200);
     delay(100);
     analogWrite(beep,0);
     delay(100);
  }
  ///////////////////////////////////
     for (int i =0; i<5; i++)
  {
   analogWrite(greenled, 200);
   analogWrite(beep, 200);
   delay(100);
   analogWrite(beep,0);
   delay(100);
   analogWrite(beep, 200);
   delay(100);
   analogWrite(beep,0);
   delay(100);
   
   analogWrite(greenled, 0);
    
   analogWrite(beep, 200);
   delay(100);
   analogWrite(beep,0);
   delay(100);
   analogWrite(beep, 200);
   delay(100);
   analogWrite(beep,0);
 delay(500);

  }
   
   analogWrite(redled, 0);
   /////////////////////////////////////
   analogWrite(yellowled, 200);
     for (int i =0; i<3; i++)
  {
     analogWrite(beep, 200);
     delay(100);
     analogWrite(beep,0);
     delay(900);
 }
   
}

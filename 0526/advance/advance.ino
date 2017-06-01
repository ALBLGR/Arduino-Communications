


int Echo = A0;  // Echo回声脚(P2.0)
int Trig =A1;  //  Trig 触发脚(P2.1)
int Echo2 = A2;  // Echo回声脚(P2.0)
int Trig2 =A3;  //  Trig 触发脚(P2.1)
int Distance = 0;
int Distance2 = 0;


void setup()
{
  Serial.begin(9600);     // 初始化串口
   pinMode(7,OUTPUT);
   pinMode(Echo, INPUT);    // 定义超声波输入脚
  pinMode(Trig, OUTPUT);   // 定义超声波输出脚
    pinMode(Echo2, INPUT);    // 定义超声波输入
  pinMode(Trig2, OUTPUT);   // 定义超声波输出脚
  analogWrite(7,255);
  analogWrite(8,255);
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
void Distance_test2()   // 量出前方距离 
{
  digitalWrite(Trig2, LOW);   // 给触发脚低电平2μs
  delayMicroseconds(2);
  digitalWrite(Trig2, HIGH);  // 给触发脚高电平10μs，这里至少是10μs
  delayMicroseconds(10);
  digitalWrite(Trig2, LOW);    // 持续给触发脚低电
  float Fdistance = pulseIn(Echo2, HIGH);  // 读取高电平时间(单位：微秒)
  Fdistance= Fdistance/58;       //为什么除以58等于厘米，  Y米=（X秒*344）/2
  // X秒=（ 2*Y米）/344 ==》X秒=0.0058*Y米 ==》厘米=微秒/58
  Serial.print("1Distance:");      //输出距离（单位：厘米）
  Serial.println(Fdistance);         //显示距离
  Distance2 = Fdistance;
}  


void loop(){
  Distance_test();
   Distance_test2();
  if(Distance<50  && Distance>4){
  analogWrite(7,0);
  analogWrite(6,255);
  delay(100);
  analogWrite(7,255);
  delay(3000);
  analogWrite(6,0);
  }
  else if (Distance2<50 && Distance2>4){
  analogWrite(8,0);
  analogWrite(6,255);
  delay(100);
  analogWrite(8,255);
  delay(3000);
  analogWrite(6,0);
  }
  else{
    analogWrite(7,255);
    delay(50);
  }
  
}

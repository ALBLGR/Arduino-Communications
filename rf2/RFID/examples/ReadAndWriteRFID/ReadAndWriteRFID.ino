//整理者：极客工坊bg1lsy (lsy@sogou.com)
//整理时间：2013.05.25
#include <SPI.h>
#include <RFID.h>

#include <LiquidCrystal.h> //申明1602液晶的函数库
//申明1602液晶的引脚所连接的Arduino数字端口，8线或4线数据模式，任选其一
//LiquidCrystal lcd(12,11,10,9,8,7,6,5,4,3,2);   //8数据口模式连线声明
LiquidCrystal lcd(8,7,6,9,4,3,2); //4数据口模式连线声明
int Echo = A3;  // Echo回声脚(P2.0)
int Trig =A2;  //  Trig 触发脚(P2.1)


RFID rfid(10,5);    //D10--读卡器MOSI引脚、D5--读卡器RST引脚
int redled=A0;
int greenled=A1;
//4字节卡序列号，第5字节为校验字节
unsigned char serNum[5];
//写卡数据
unsigned char writeDate[16] ={'G', 'e', 'e', 'k', '-', 'W', 'o', 'r', 'k', 'S', 'h', 'o', 'p', 0, 0, 0};
//原扇区A密码，16个扇区，每个扇区密码6Byte
unsigned char sectorKeyA[16][16] = {
        {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
        {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
        {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},};
//新扇区A密码，16个扇区，每个扇区密码6Byte
unsigned char sectorNewKeyA[16][16] = {
        {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
        {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xff,0x07,0x80,0x69, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
        {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xff,0x07,0x80,0x69, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},};


int Card[6][100];
int CardCount=0;
void addCard(){
    Card[0][CardCount]= (rfid.serNum[0],HEX);
    Card[1][CardCount]= (rfid.serNum[1],HEX);
    Card[2][CardCount]= (rfid.serNum[2],HEX);
    Card[3][CardCount]= (rfid.serNum[3],HEX);
    Card[0][CardCount]= CardCount;
    CardCount++;
}








void setup()
{
  Serial.begin(9600);
  SPI.begin();
  rfid.init();
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
  
  boolean verify(){
   boolean IsCard = false;
  for (int i =0; i<=CardCount;i++)
 {
  if( Card[0][CardCount]== (rfid.serNum[0],HEX) && Card[1][CardCount]== (rfid.serNum[1],HEX) &&  Card[2][CardCount]== (rfid.serNum[2],HEX) && Card[3][CardCount]== (rfid.serNum[3],HEX))

    return true; 
 }
 
 return IsCard;
}
  int Distance=0;
  
  
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
   lcd.print(Fdistance);         //显示距离
}  


void loop()
{


   lcd.home();        //把光标移回左上角，即从头开始输出   
  lcd.clear();
  lcd.print("Standby.");
   ////////////////////////////
  unsigned char i,tmp;
  unsigned char status;
  unsigned char str[MAX_LEN];
  unsigned char RC_size;
  unsigned char blockAddr;        //选择操作的块地址0～63

  //找卡
  rfid.isCard();
  //读取卡序列号
  if (rfid.readCardSerial())
  {
    Serial.print ("The card's number is  : ");
    Serial.print (rfid.serNum[0],HEX);
     Serial.print(rfid.serNum[1],HEX);
     Serial.print(rfid.serNum[2],HEX);
     Serial.print(rfid.serNum[3],HEX);
    // Serial.print =(rfid.serNum[4],HEX);
     Serial.println(" ");
    lcd.clear();
     lcd.setCursor(0,0);
     lcd.print(rfid.serNum[0],HEX);
    lcd.print(rfid.serNum[1],HEX);
    lcd.print(rfid.serNum[2],HEX);
    lcd.print(rfid.serNum[3],HEX);
    
  if(CardCount==0){
    addCard();
     access_granted();
  }
  else{
    verify() ? access_granted() : access_denied();
   
  }
    
    
    
  }
  
 
    
    
    ///////////////////////////////////
    /*
     if( rfid.serNum[0]==0x8B && rfid.serNum[1]==0x7B && rfid.serNum[2]==0x66 && rfid.serNum[3]==0xB8 ) {
            Serial.println("Hey Eno!");
            
            access_granted();
           
        } else if(rfid.serNum[0]==0x80 && rfid.serNum[1]==0xC3 && rfid.serNum[2]==0xA0 && rfid.serNum[3]==0x7C) {
          Serial.println("Hello Greg!");
             access_granted();
        }else{
           Serial.println("Hello unkown guy!");
            access_denied();
        }
       ////////////////////////////
     // Distance_test();
    
  }
   
  
  
  
  
  

  //选卡，返回卡容量（锁定卡片，防止多次读写）
  rfid.selectTag(rfid.serNum);
  
  //写数据卡
  blockAddr = 7;                //数据块7
  if (rfid.auth(PICC_AUTHENT1A, blockAddr, sectorKeyA[blockAddr/4], rfid.serNum) == MI_OK)  //认证
  {
    //写数据
    status = rfid.write(blockAddr, sectorNewKeyA[blockAddr/4]);
    Serial.print("set the new card password, and can modify the data of the Sector: ");
    Serial.println(blockAddr/4,DEC);
    //写数据
    blockAddr = blockAddr - 3 ; //数据块4
    status = rfid.write(blockAddr, writeDate);
    if(status == MI_OK)
    {
     Serial.println("Write card OK!");
    }
    
  }

  //读卡
  blockAddr = 7;                //数据块7
  status = rfid.auth(PICC_AUTHENT1A, blockAddr, sectorNewKeyA[blockAddr/4], rfid.serNum);
  if (status == MI_OK)  //认证
  {
    //读数据
    blockAddr = blockAddr - 3 ; //数据块4
    if( rfid.read(blockAddr, str) == MI_OK)
    {
    Serial.print("Read from the card ,the data is : ");
       Serial.println((char *)str);
    }
  }
  */
  rfid.halt();
}

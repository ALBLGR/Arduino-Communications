#include <Wire.h>


int LED_RED=3, LED_GREEN=4,LED_BLUE=5;
int BACK_SOUND=7,LEFT_SOUND=9, RIGHT_SOUND=10, GO_SOUND=6, STOP_SOUND=8;

void setup() {
   pinMode(LED_RED,OUTPUT);
  pinMode(LED_GREEN,OUTPUT);
  pinMode(LED_BLUE,OUTPUT);
  pinMode(BACK_SOUND,OUTPUT);
  pinMode(GO_SOUND,OUTPUT);
  pinMode(LEFT_SOUND,OUTPUT);
  pinMode(RIGHT_SOUND,OUTPUT);
  pinMode(STOP_SOUND,OUTPUT);
  analogWrite(BACK_SOUND,255);
  analogWrite(LEFT_SOUND,255);
  analogWrite(RIGHT_SOUND,255);
  analogWrite(GO_SOUND,255);
  analogWrite(STOP_SOUND,255);
                  analogWrite(LED_BLUE,255); 
                 analogWrite(LED_RED,255); 
                  analogWrite(LED_GREEN,255); 
 Wire.begin(4);
  Wire.onReceive(receiveEvent);
  Serial.begin(9600);
}
char commandArray [7];

void receiveEvent(int howMany)
{
  int i=0;
  Serial.println("");
  Serial.print("wire rx ");
  char c;
// 循环读取接收到的数据，最后一个数据单独读取
  while( Wire.available()>0)
  {
     c= Wire.read(); // 以字符形式接收数据
    Serial.print(c);       // 串口输出该字符
    i++;
    if(i>=11 && i<=17){
    commandArray[i-11] = c;
    }

} 
  analogWrite(BACK_SOUND,255);
  analogWrite(LEFT_SOUND,255);
  analogWrite(RIGHT_SOUND,255);
  analogWrite(GO_SOUND,255);
  analogWrite(STOP_SOUND,255);
   
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
  
  
  
            
             if ((char)commandArray[3]=='O'&&(char)commandArray[4]=='F'){
                analogWrite(LED_BLUE,255); 
                 analogWrite(LED_RED,255); 
                  analogWrite(LED_GREEN,255); 
               }
               else { if ((char)commandArray[5]=='R'&&(char)commandArray[6]=='D'){
                analogWrite(LED_RED,0); 
                  analogWrite(LED_BLUE,255);
                  analogWrite(LED_GREEN,255); 
               }
               
              if ((char)commandArray[5]=='G'&&(char)commandArray[6]=='N'){
                analogWrite(LED_GREEN,0); 
                analogWrite(LED_BLUE,255); 
                 analogWrite(LED_RED,255); 
               }
              if ((char)commandArray[5]=='B'&&(char)commandArray[6]=='L'){
                analogWrite(LED_BLUE,0); 
                analogWrite(LED_RED,255); 
                  analogWrite(LED_GREEN,255);   
             }     
               }          
            
               if((char)commandArray[0]=='B'&&(char)commandArray[1]=='A'&&(char)commandArray[2]=='C'&&(char)commandArray[3]=='K'&&(char)commandArray[4]=='S'){
                analogWrite(BACK_SOUND,0);
                Serial.println("sound");


               }
               if((char)commandArray[0]=='R'&&(char)commandArray[1]=='I'&&(char)commandArray[2]=='G'&&(char)commandArray[3]=='H'&&(char)commandArray[4]=='T'){
                analogWrite(RIGHT_SOUND,0);
                Serial.println("sound");


               }
                if((char)commandArray[0]=='L'&&(char)commandArray[1]=='E'&&(char)commandArray[2]=='F'&&(char)commandArray[3]=='T'&&(char)commandArray[4]=='S'){
                analogWrite(LEFT_SOUND,0);
                Serial.println("sound");

               }
                if((char)commandArray[0]=='F'&&(char)commandArray[1]=='O'&&(char)commandArray[2]=='R'&&(char)commandArray[3]=='W'&&(char)commandArray[4]=='D'){
                analogWrite(GO_SOUND,0);
                Serial.println("sound");

               }
                if((char)commandArray[0]=='S'&&(char)commandArray[1]=='T'&&(char)commandArray[2]=='O'&&(char)commandArray[3]=='P'&&(char)commandArray[4]=='S'){
                analogWrite(STOP_SOUND,0);
                Serial.println("sound");

               }
   
}
void loop() {

        
}

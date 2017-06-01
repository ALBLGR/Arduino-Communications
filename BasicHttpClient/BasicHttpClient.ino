
#include <WiFiClient.h>
#include <WiFiServer.h>
#include <WiFiUdp.h>
#include <Wire.h>


#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

#include <ESP8266HTTPClient.h>

#define USE_SERIAL Serial
HTTPClient http;


void setup() {

  Wire.begin(); 
    USE_SERIAL.begin(9600);
   USE_SERIAL.setDebugOutput(true);

    USE_SERIAL.println();
    USE_SERIAL.println();
    USE_SERIAL.println();
    WiFi.mode(WIFI_STA);  
     WiFi.begin("G1-4", "82155936");
      while(WiFi.waitForConnectResult() != WL_CONNECTED){

    Serial.println("WiFi failed, retrying.");
  }
        Serial.print ( "IP address: " );
	Serial.println ( WiFi.localIP() );

       
        // configure server and url
       http.begin("http://alblgr.vicp.net/console/read.php");

}

void loop() {
    // wait for WiFi connection
    if((WiFi.status() == WL_CONNECTED)) {
//         Wire.requestFrom(4, 6);    // request 6 bytes from slave device #2
//        
//          while(Wire.available())    // slave may send less than requested
//          { 
//            char c = Wire.read();    // receive a byte as character
//          } 

      // configure server and url
//       http.begin("http://board.org.cn/console/read.php");
        USE_SERIAL.print("[HTTP] GET...\n");
        // start connection and send HTTP header
        
        int httpCode = http.GET();
        
        if(httpCode > 0) {
            // HTTP header has been send and Server response header has been handled
            USE_SERIAL.printf("[HTTP] GET... CODE: %d\n", httpCode);

            // file found at server
            if(httpCode == HTTP_CODE_OK) {
//               // get lenght of document (is -1 when Server sends no Content-Length header)
//                int len = http.getSize();
//                // create buffer for read
//                uint8_t buff[256] = { 0 };
//                // get tcp stream
//               WiFiClient * stream = http.getStreamPtr();
//             // read all data from server
//                    // get available data size
//                    size_t size = stream->available();
//                        // read up to 128 byte
////                        int c = stream->readBytes(buff, ((size > sizeof(buff)) ? sizeof(buff) : size));
//                        stream->readBytes(buff, ((size > sizeof(buff)) ? sizeof(buff) : size));
//                        // write it to Serial
//                        USE_SERIAL.write(buff,256);
                        USE_SERIAL.write(http._EnoResponse.c_str());
              Wire.beginTransmission(4); //向地址为4的从机传送数据
              Wire.write(http._EnoResponse.c_str());              // 发送1个字节的数据      
              Wire.endTransmission();    // 结束传送
              Wire.beginTransmission(5); //向地址为4的从机传送数据
              Wire.write(http._EnoResponse.c_str());              // 发送1个字节的数据      
              Wire.endTransmission();    // 结束传送
              
              String command = http._EnoResponse.substring(10,http._EnoResponse.length()).c_str();
               USE_SERIAL.println(command);
            
               

                USE_SERIAL.println(); 
            }
        }
         else {
            USE_SERIAL.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
      }
       // http.end();
   

    }
}




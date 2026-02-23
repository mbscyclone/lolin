#include <WiFiClient.h>

void sendserver8080(String htpServerip, String goserver)
{ if(goserver.length()<5)return;
  String msg2 = "http://" + htpServerip + ":8080/"+ YOL + "/" + esphostname + "-" + goserver;

          Serial.println(msg2);
      
          if ((WiFi.status() == WL_CONNECTED)) {

            WiFiClient client2;
            HTTPClient http2;
            http2.setTimeout(200);
            http2.begin(client2, msg2);  // HTTP

            //Serial.print("[HTTP] GET...\n");
            // start connection and send HTTP header and body
            int httpCode2 = http2.GET();
            delay(100);
            // httpCode will be negative on error
            if (httpCode2 > 0) {
            edegisenler=degisenler;
            Serial.println("Gönderildi.");
            
            }else {
              Serial.printf("[HTTP] GET... failed, error: %s\n", http2.errorToString(httpCode2).c_str());
            }

          }
            yield();
}











void sendserver80(String htpServerip, String port, String goserver)
{ if(goserver.length()<5)return;

String msg2="";

  if(port!=""){port=":"+port;}
  else port="";
  
  if(htpServerip.indexOf("http")!= 0) htpServerip="http://" + htpServerip; 
  
  msg2 = htpServerip + port + goserver;

  Serial.println(htpServerip);
  Serial.println(port);
          Serial.println(msg2);
      
          if ((WiFi.status() == WL_CONNECTED)) {

            WiFiClient client2;
            HTTPClient http2;
            if(port.indexOf("8080")>-1)http2.setTimeout(250);
            else http2.setTimeout(2000);
            http2.begin(client2, msg2);  // HTTP

            //Serial.print("[HTTP] GET...\n");
            // start connection and send HTTP header and body
            int httpCode2 = http2.GET();
            delay(100);
            // httpCode will be negative on error
            if (httpCode2 > 0) {
            edegisenler=degisenler;
            Serial.println("Gönderildi.");
            
            }else {
              Serial.printf("[HTTP] GET... failed, error: %s\n", http2.errorToString(httpCode2).c_str());
            }

          }
            yield();
}
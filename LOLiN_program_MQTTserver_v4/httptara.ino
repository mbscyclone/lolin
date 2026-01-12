/*/
//burada olanlar ///////////////////
#include <WiFiClient.h>

void httptara()
{
  if(WiFi.status()==!WL_CONNECTED)return;




            IPAddress lip = WiFi.localIP();
            String lipStr = String(lip[0]) + '.' + String(lip[1]) + '.' + String(lip[2]) + '.' + String(lip[3]);


    if(kimdir==(int)(lip[3]))kimdir+=1;
    String testserver = String(lip[0]) + '.' + String(lip[1]) + '.' + String(lip[2]) + '.' + String(kimdir);
    testserver="http://" + testserver + ":8080/ser:"+ lipStr;
    kimdirsonyeri=kimdir;

  Serial.println(testserver);
      
          if ((WiFi.status() == WL_CONNECTED)) {

            WiFiClient client2;
            HTTPClient http2;
            http2.setTimeout(800);
            //Serial.print("[HTTP] begin...\n");
            // configure traged server and url
            http2.begin(client2, testserver);  // HTTP

            //Serial.print("[HTTP] GET...\n");
            // start connection and send HTTP header and body
            int http2Code = http2.GET();

            // httpCode will be negative on error
            if (http2Code > 0) {
              // HTTP header has been send and Server response header has been handled
              //Serial.printf("[HTTP] GET... code: %d\n", httpCode);

              // file found at server
              if (http2Code == HTTP_CODE_OK) {
                const String& payload2 = http2.getString();
                //Serial.println("received payload:\n<<");
                Serial.println(payload2);
                //Serial.println(">>");
                String testbesp=payload2;
                // error var
                if(payload2.indexOf("]")>-1)
                {

                  for(int j=19;j>espv4sayac;j--)
                  {
                    bulunanespv4[j+1]=bulunanespv4[j];
                  }
                  for(int j=espv4sayac+1;j<21;j++)
                  {
                    if(payload2.substring(0,payload2.indexOf("]")) == bulunanespv4[j].substring(0,bulunanespv4[j].indexOf("]")))
                    {
                      bulunanespv4[j]="";
                    }
                  }
                  bulunanespv4[espv4sayac]=payload2;
               }
                espv4sayac+=1;
              }

            } else {
              Serial.println("");
              //Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
            }

            http2.end();

            kimdir+=1;
            if(kimdir>255){
            kimdir=-2;kimdirsonyeri=-2;delay(1200);return;
            //esplerikaydet();
            }

          }

}
*/

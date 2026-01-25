#include <WiFiClient.h>

void httptara()
{

            if(millis()-otuzsaniye > 29000)
            {
                tarazamani=millis();
               if(millis()-otuzsaniye > 32000)otuzsaniye=millis();
               else return;
            }

  tarazamani=millis();
  
  if(WiFi.status()==!WL_CONNECTED){kimdir=-2;return;}

                                          if(kimdir==1)    // silme işlemi
                                          {   LittleFS.remove("/espler.txt");
                                              LittleFS.remove("/kimdirf.txt");
                                                            for(int j=1;j<21;j++)
                                                            {
                                                                bulunanespv4[j]="";
                                                            }
                                          }


            IPAddress lip = WiFi.localIP();
            String lipStr = String(lip[0]) + '.' + String(lip[1]) + '.' + String(lip[2]) + '.' + String(lip[3]);


    if(kimdir==(int)(lip[3]))kimdir+=1;
    String testserver = String(lip[0]) + '.' + String(lip[1]) + '.' + String(lip[2]) + '.' + String(kimdir);
            String esphostnamegec = esphostname;
            esphostnamegec.toUpperCase();
            if (esphostnamegec.indexOf("LOGSERVER") < 0) {testserver="http://" + testserver + ":8080/ser:"+ lipStr;}
            else {testserver="http://" + testserver + ":8080/";}
    kimdirsonyeri=kimdir;

  Serial.println(testserver);
      
          if ((WiFi.status() == WL_CONNECTED)) {

            WiFiClient client2;
            HTTPClient http2;
            http2.setTimeout(http2setTimeout);
            //Serial.print("[HTTP] begin...\n");
            // configure traged server and url
            yield();
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
            kimdir=-2;kimdirsonyeri=-2;
            esplerikaydet();
            }

          }

}


void esplerikaydet()
{
  File espler;
  espler.close();
  LittleFS.remove("/espler.txt");
  espler = LittleFS.open("/espler.txt", "w+");
                  for(int j=1;j<21;j++)
                  {
                    if(bulunanespv4[j] != "")
                    {
                      if(bulunanespv4[j].indexOf("\n") >0) bulunanespv4[j] = bulunanespv4[j].substring(0,bulunanespv4[j].indexOf("\n"));
                      espler.println(bulunanespv4[j]);
                    }
                  }
 espler.close();

  File kimdirf;
  kimdirf.close();
  LittleFS.remove("/kimdirf.txt");
  kimdirf = LittleFS.open("/kimdirf.txt", "w+");
  kimdirf.println((String)kimdirsonyeri);
  kimdirf.close();

}




void esplerioku()
{
  File espler;
  espler.close();
  espler = LittleFS.open("/espler.txt", "r");
    String geciciespler = espler.readString();
                  for(int j=1;j<21;j++)
                  {
                    if(geciciespler.length() >0)
                    {
                      bulunanespv4[j] = geciciespler.substring(0,geciciespler.indexOf("\n"));
                      geciciespler=geciciespler.substring(geciciespler.indexOf("\n")+1, geciciespler.length());
                    }else break;
                  }
 espler.close();

  File kimdirf;
  kimdirf.close();
  kimdirf = LittleFS.open("/kimdirf.txt", "r");
  String kimdirSSonyeri  = kimdirf.readString();
  kimdirsonyeri=kimdirSSonyeri.toInt();
 kimdirf.close();
}

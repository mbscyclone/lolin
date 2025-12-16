/*

 ana programda yukarıda tanımlanacaklar///////////////
int kimdir=0;
unsigned int kimdirsayac;
int espv4sayac=1;
String bulunanespv4[10];
///////////////////////////////////
ana programda loop içinde//////////
  
  
        if (Firebase_ready && zamanfark > 2950 && zamanfark < 3000)
        {
            zamanfark=3001;
            if(kimdir==0)
            {
            programrun();
            fbsayacoku();
            }
        }

  
  
  if(kimdir>0)
  {
    httptara();
  }
//////////////////////////////////////////////////////

htpcl.ino içinde ////////////////////////////////////
if(header.indexOf("/whois")>-1){
  if(kimdir==0)kimdir=1;header="GET /pinayar HTTP/1.1";headerOld=header; espv4sayac=1;
  }

menu sıfırda bilgi ///
 if(kimdir!=0) xilent.println("<label style='font-size: 12px;vertical-align: top;'>Ağ taraması " +String((int)((kimdir*100)/255)) + " %</label><br>");




            xilent.println("Giris formati (Bosluk kullanma, Bosluklarin yerine \"|\" isareti kullanilacak.)<br>pinAdi pinModu pinSinyalTipi pinMinDegeri pinDegeri pinMaxDegeri pinEtiketi");
            xilent.println("<table>  <caption>PIN AYARLARI VE AĞDAKİ ESPLER</caption> <tr> <td scope=\"col\">pin ayarları:</td><td scope=\"col\">Ağdaki ESPv4 cihazları</td></tr>");
            xilent.println("<td><form method='get' action='pinayar'><br>");
            xilent.println("<textarea name='is' id='id' cols='50' rows='10' >");
            xilent.println(pinayar);
            xilent.println("</textarea>");
            xilent.println("<br>ESP ye bağlı Cihazları kapatın.<br>");
            xilent.println("<input type='submit' value='Pinayar Kaydet'>");
            xilent.println("</form></td><td>");
            

            xilent.println("<label style='font-size:12px;vertical-align:top;'>");
            for(int i=1;i<51;i++)
            {
              if(bulunanespv4[i]!="")
              {
                xilent.println(bulunanespv4[i]+"<br>");
              }else break;
            }
            xilent.println("</label></td>");

            xilent.println("</table><br>");
            xilent.println("Altta ESP-Wemos pinleri icin bir ornek verilmistir.<br>");
            xilent.println("D0|OUT|DIG|0|0|1|Sarj1_pirizi<br>");
            xilent.println("D1|OUT|PWM|0|0|1|Servo<br>");
            xilent.println("D3|INP|DHT1|1|-2|-5|Temp_Hum<br>");
            xilent.println("A0|INP|ANG|0|0|1024|Volt3v3<br>");
            xilent.println("<br><br>");






burada olanlar ///////////////////
#include <WiFiClient.h>

int taranacakip=1;

void httptara()
{
  if(WiFi.status()==!WL_CONNECTED)return;

    if(kimdirsayac<200){kimdirsayac+=1;return;}
    else 
    {
      kimdirsayac=0;
    }

            IPAddress lip = WiFi.localIP();
            String lipStr = String(lip[0]) + '.' + String(lip[1]) + '.' + String(lip[2]) + '.' + String(lip[3]);

      WiFiClient client;
      HTTPClient http;

    kimdir+=1;
    if(kimdir==(int)(lip[3]))kimdir+=1;
    if(kimdir>255){kimdir=0;return;}
    String testserver = String(lip[0]) + '.' + String(lip[1]) + '.' + String(lip[2]) + '.' + String(kimdir);
    testserver="http://" + testserver + ":8080";


  Serial.println(testserver);
      
          if ((WiFi.status() == WL_CONNECTED)) {

            WiFiClient client;
            HTTPClient http;
            http.setTimeout(1000);
            //Serial.print("[HTTP] begin...\n");
            // configure traged server and url
            http.begin(client, testserver);  // HTTP

            //Serial.print("[HTTP] GET...\n");
            // start connection and send HTTP header and body
            int httpCode = http.GET();

            // httpCode will be negative on error
            if (httpCode > 0) {
              // HTTP header has been send and Server response header has been handled
              //Serial.printf("[HTTP] GET... code: %d\n", httpCode);

              // file found at server
              if (httpCode == HTTP_CODE_OK) {
                const String& payload = http.getString();
                //Serial.println("received payload:\n<<");
                Serial.println(payload);
                //Serial.println(">>");
                bulunanespv4[espv4sayac]=payload;espv4sayac+=1;
              }
            } else {
              Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
            }

            http.end();
          }

}

*/
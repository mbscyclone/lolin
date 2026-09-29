#include <WiFiClient.h>
void paypinistevoid(int pps)
{
int pp;
if(paypinistesirasi+1<totalmac+1)pp=paypinistesirasi;
else pp=pps;

String istek="http://" + ip[pp] + "/payM";
Serial.print("\n"+ istek+"\n");

            WiFiClient client21;
            HTTPClient http21;
            http21.setTimeout(http2setTimeout);

            http21.begin(client21, istek);  // HTTP

            Serial.print("[HTTP] GET...\n");
            // start connection and send HTTP header and body
            int http2Code1 = http21.GET();

            // httpCode will be negative on error
            if (http2Code1 > 0) {

              if (http2Code1 == HTTP_CODE_OK) {
                const String& payload21 = http21.getString();
                //Serial.println("received payload:\n<<");
                //Serial.println(payload2);
                //Serial.println(">>");
                String istekp=payload21;
                // error var
                if(payload21.indexOf("payĞ")>-1)
                {
                  Serial.println("bilgi geldi");
                  Serial.println(istekp);

                  /////////////////////////// bilgileri yerleştir
                  String gpay=istekp.substring(istekp.indexOf("payĞ")+5,istekp.indexOf("<br><br>"));
                  
                                if(gpay.indexOf("\n")<0)gpay+="\n";
                                String dats=gpay;
                                dats="[" + gpay +"ğ";
                                dats.replace("\n","][");
                                if(dats.indexOf("[ğ")>1)dats=dats.substring(0,dats.length()-3);

                  pa[pp] = dats;
                  istekp = istekp.substring(istekp.indexOf("<br><br>")+8,istekp.length());
                  String pig=istekp.substring(istekp.indexOf("pinĞ")+5,istekp.indexOf("<br><br>"));

                  pi[pp] = pig;
                  istekp = istekp.substring(istekp.indexOf("<br><br>")+8,istekp.length());
                  r[pp] = istekp.substring(istekp.indexOf("rĞ")+3,istekp.indexOf("<br><br>"));
                  
                  fbSdataguncelle(pp);
                  ///////////////////////////

                  paypinistemesuresi=millis()-http2setTimeout;
                }
              } else Serial.println(http2Code1);

            } else {
              Serial.println("");
              //Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
            }

            http21.end();
            



}
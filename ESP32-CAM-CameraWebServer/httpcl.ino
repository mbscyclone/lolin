int xcurrentTime=0;
int timeoutTime=5000;


void htpcl() {
  WiFiClient xilent = htserver.available();
  header = "";
  if (xilent) {

    // If a new xilent connects,

    String currentLine = "";                             // make a String to hold incoming data from the xilent
    xcurrentTime = 0;
    while (xilent.connected() && xcurrentTime <= timeoutTime) {  // loop while the xilent's connected
      xcurrentTime += 1;
      if (xilent.available()) {  // if there's bytes to read from the xilent,

        for (int q = 0; q < 2000; q++) {
          char c = xilent.read();  // read a byte, then

          // Serial.print((int)c);
          if (int(c) == 255) break;
          Serial.print(c);  // print it out the serial monitor
          header += c;
        }
          if(header.indexOf("\n")<1)return;


          // Read the first line of HTTP request
          // First line of HTTP request looks like "GET /path HTTP/1.1"
          // Retrieve the "/path" part by finding the spaces

          header = header.substring(0, header.indexOf("\n"));

          Serial.println(header);
          Serial.println("");

///////////////////////////////////////          
    if(header.indexOf("/favicon") > -1)return;
///////////////////////////////////////

////////////////////////////
          if (header.indexOf("/SPAYPIN") > -1) {
              xilent.println("HTTP/1.1 404 \r\nContent-Type: text/plain\r\n\r\n");
              xilent.println("404");
            return;
          }
////////////////////////////



  if (header.indexOf("/gerT") > -1) {
    dosyaokumyssidname();
    IPAddress lip = WiFi.localIP();
    String lipStr = String(lip[0]) + '.' + String(lip[1]) + '.' + String(lip[2]) + '.' + String(lip[3]);
    String gd = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\n" + YOL + "[" + esphostname + "]" + lipStr;
    xilent.println(gd);
    xilent.println("");
    Serial.println("Server geldi  header: " + header);
    return;
  }


    if (header.indexOf("/pipo") > -1)pirpin=1;

    xilent.println("HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n<html>ESP32: Selam");
    xilent.println("<head><meta charset=\"UTF-8\"><style>body {background-color: #999999;} </style>");
                        xilent.println("<meta name=\"viewport\" xo=\"width=device-width, initial-scale=1\">");
                        //xilent.println("<META charset=iso-8859-9\">";
                        xilent.println("<link rel=\"icon\" href=\"data:,\">");
                        xilent.println("</head>");
                        xilent.println("<body>");
                        xilent.println("<font size=\"3\" color=\"#FF0000\">" + esphostname + "</font>");
                        xilent.println("<br><table style=\"border:5px solid black;width:500px\"><tr>");
                        xilent.println("<td style=\"border:1px solid black;width:250p; align:center; \">");
                        xilent.println("<p><form action=\"/\" method=\"POST\"><input type=\"submit\" value=\"Anasayfa\"></form></p></td>");
                        xilent.println("<td style=\"border:1px solid black;width:250p; align:center; \">");
                        xilent.println("<p><form action=\"/durum\" method=\"POST\"><input type=\"submit\" value=\"Durum\"></form></p></td>");
                        //xilent.println("<td style=\"border:1px solid black;width:250px\">");
                        //xilent.println("<p><form action=\"/pnayar\" method=\"POST\"><input type=\"submit\" value=\"Pin ayar\"></form></p></td>");
                        xilent.println("<td style=\"border:1px solid black;width:250px;\">");
                        xilent.println("<p><form action=\"/ssidset\" method=\"POST\"><input type=\"submit\" value=\"Bağlantı ayar\"></form></p></td>");
                        xilent.println("<td style=\"border:1px solid black;width:250px\">");
                        xilent.println("<p><form action=\"/myssidnameayar\" method=\"POST\"><input type=\"submit\" value=\"Cihaz adı ayar\"></form></p></td>");
                        xilent.println("<td style=\"border:1px solid black;width:250px\">");
                        xilent.println("<p><form action=\"/telegramset\" method=\"POST\"><input type=\"submit\" value=\"Telegram bot ayar\"></form></p></td>");
                        
                        //xilent.println("<td style=\"border:1px solid black;width:250px\">");
                        //xilent.println("<p><form action=\"/mqttipayar\" method=\"POST\"><input type=\"submit\" value=\"MQTT ayar\"></form></p></td>");
                        //xilent.println("<td style=\"border:1px solid black;width:250px\">");
                        //xilent.println("<p><form action=\"/firebaseset\" method=\"POST\"><input type=\"submit\" value=\"Firebase ayar\"></form></p></td>");

                        xilent.println("</tr></table>");

    // ssidpass başı /////////////////////
   if (header.indexOf("/ssidset") > -1) {
    xilent.println("Bağlantı ayar bölümü");
    xilent.println("<br><br>");
    xilent.println("        BAĞLANTI YAPILACAK CİHAZ BİLGİLERİ GİRİŞİ");
    xilent.println("<hr style=\"height:6px;border-width:1;color:black;background-color:black\">");
    xilent.println("<br>");

    // ssidpass başı /////////////////////
    if (header.indexOf("/ssidset?") > -1) {
      //   "/ssidset?ssid=Zyxel&pass=bebedede14"
      // yazma kısmı
      Serial.println("ssidset yazma kısmı");
      if (header.indexOf("ssid=") > -1) {
        ssid = header.substring((header.indexOf("ssid=") + 5), header.indexOf("&"));
        Serial.println(ssid);
      }
      if (header.indexOf("&pass=") > -1) {
        pass = header.substring((header.indexOf("&pass=") + 6), header.indexOf(" HTTP/"));
        Serial.println(pass);
        dosyayazssidpass();
        ////client.abort();;
        ESP.restart();
      }
    }

    IPAddress gip = WiFi.gatewayIP();
    String gipStr = String(gip[0]) + '.' + String(gip[1]) + '.' + String(gip[2]) + '.' + String(gip[3]);
    IPAddress dns = WiFi.dnsIP();
    String dnsStr = String(gip[0]) + '.' + String(gip[1]) + '.' + String(gip[2]) + '.' + String(gip[3]);
    IPAddress ip = WiFi.softAPIP();
    String ipStr = String(ip[0]) + '.' + String(ip[1]) + '.' + String(ip[2]) + '.' + String(ip[3]);

    xilent.println("<table style=\"border:2px solid green;width:500px\"><tr><td style=\"border:1px solid black;width:250px\">");
    xilent.println("Bilgiler");
    xilent.println("<br><br>");
    if(WiFi.status()==WL_CONNECTED)xilent.println("Bağlanılan wifi cihazı:" + ssid);
    else xilent.println("Herhangi bir wifi cihaza bağlı değilim");
    xilent.println("<br>");
    xilent.println("Local IP : ");
    IPAddress lip = WiFi.localIP();
    String lipStr = String(lip[0]) + '.' + String(lip[1]) + '.' + String(lip[2]) + '.' + String(lip[3]);
    xilent.println(lipStr);
    xilent.println("<br>");
    xilent.println("Local Gateway : ");
    xilent.println(gipStr);
    xilent.println("<br>");
    xilent.println("Access IP : ");
    xilent.println(ipStr);
    xilent.println("</td><td style=\"border:1px solid black;width:250px\">");
    xilent.println("<form action=\"/ssidsetscanwifi\" method=\"POST\"><input type=\"submit\" value=\"Wifi tara\"></form>");
    if (header.indexOf("scanwifi HTTP") > -1) {
      rescanwifi = 1;
    }
              xilent.println("<br>Wifi tara tıkladıktan sonra 10 sn bekle<br>");
              xilent.println("<br>Sonra tarama sonucu butonuna tıkla<br>");
              xilent.println("<form action=\"/ssidset\" method=\"POST\"><input type=\"submit\" value=\"Tarama sonucu\"></form>");
              xilent.println("</td></tr></table>");


              xilent.println("<p>");
              xilent.println("<table style=\"border:2px solid black;width:500px\"><tr><td style=\"border:1px solid black;width:500px\">");
              xilent.println("Tarama sonucunda bulunabilen Wifi cihazları listesi</td><tr><td>");
              xilent.println("<br>");
              xilent.println(st);
              xilent.println("</td><tr></table><br>");
              xilent.println("Bağlanılacak Modemin Wifi ismi (SSID) ve Şifresi (PASSWORD) giriş bölümü.");
              xilent.println("            Kaydettikten sonra cihaza ⚠️ reset gerekli.");
              xilent.println("<br><form action=\"/ssidset\" method=\"get\"><label>SSID: </label><input name='ssid' length=32><label>PASS: </label><input name='pass' length=32><input type='submit'value='Kaydet'></form>");
// ssidpass sonu /////////////////////
   }

// myssidname başı //////////////////
             if (header.indexOf("/myssidnameayar") > -1) {  
              xilent.println("Cihaz adı ayar bölümü");
              xilent.println("<br><br>");
              xilent.println("        BENİM ADIM BİLGİ GİRİŞİ");
              xilent.println("<hr style=\"height:6px;border-width:1;color:black;background-color:black\">");
              xilent.println("<br><br>");

// myssidname başı //////////////////
            if (header.indexOf("/myssidnameayar?is=") > -1) {
              myssidyazilimi = header.substring((header.indexOf("?is=") + 4), header.indexOf(" HTTP/"));
              Serial.println("buradan geçtim");
              dosyayazmyssidname();
            }

            if (header.indexOf("/myssidnameayar?fbyol=") > -1) {
              YOL = header.substring((header.indexOf("?fbyol=") + 7), header.indexOf(" HTTP/"));
              Serial.println("buradan geçtim");
              dosyayazfbyol();
            }

              xilent.println("    Benim Wifi ismim giriş bölümüdür.<br>");
              xilent.println("    <form method='get' action='myssidnameayar'><label>Benim wifi ismim (SSID) : " + esphostnameOnek + "-</label><input name='is' length=32 value='");
              xilent.println(myssidyazilimi);
              //xilent.println("><br>");
              //xilent.println("<label>Baglanilacak SERVER adressi: </label><input name='mq' length=32 value=");
//              xo += SERVERip;
              xilent.println("'>    <input type='submit'>");
              xilent.println("</form>");


              xilent.println("'><br><br>");
              xilent.println("<form method='get' action='myssidnameayar'>");
              xilent.println("<label>Database deki Yol (Örnek: Balıkesir ev1: bev1, yazlık 10Yz1, gibi kısa kodlar kullanın. Database için kullanılmaz. Yerel server için gereklidir.)<br> YOL : </label><input name='fbyol' id='fbyol' style=\"width:70px;\" value='");
              xilent.println(YOL);
              xilent.println("'><input type='submit'>");
              xilent.println("</form>");

             }

// myssidname sonu ///////////////////////


// telegram başı //////////////////
    // ssidpass başı /////////////////////
   if (header.indexOf("/telegramset") > -1) {
    xilent.println("Telegram ayar bölümü");
    xilent.println("<br><br>");
    xilent.println("        TELEGRAM CHATBOT BİLGİLERİ GİRİŞİ");
    xilent.println("<hr style=\"height:6px;border-width:1;color:black;background-color:black\">");
    xilent.println("<br>");

    // ssidpass başı /////////////////////
    if (header.indexOf("/telegramset?") > -1) {
      //
      // yazma kısmı
      if (header.indexOf("token=") > -1) {
        telegram_botToken = header.substring((header.indexOf("token=") + 6), header.indexOf("&"));
        Serial.println(telegram_botToken);
      }
      if (header.indexOf("&chatid=") > -1) {
        telegram_chatID = header.substring((header.indexOf("&chatid=") + 8), header.indexOf(" HTTP/"));
        Serial.println(telegram_chatID);
        telegramtokendosyayaz();
        ////client.abort();;
        ESP.restart();
      }
    }



              xilent.println("Telegram Chat bot ayarları giriş bölümü.");
              xilent.println("            Kaydettikten sonra cihaza ⚠️ reset çekilecektir.");
              xilent.println("<br><form action=\"/telegramset\" method=\"get\"><label>Telegram Token: </label><input name='token' length=32 value='" + telegram_botToken +  "'><label>Telegram chatID: </label><input name='chatid' length=32 value='" + telegram_chatID + "'><input type='submit'value='Kaydet'></form>");
   }
// telegram sonu //////////////////






            if (header.indexOf("/durum HTTP/1.1") > -1) {

              // Serial.println(Menu);
              // Serial.println(header);
              // Serial.println(xo);
              IPAddress lip = WiFi.localIP();
              String lipStr = String(lip[0]) + '.' + String(lip[1]) + '.' + String(lip[2]) + '.' + String(lip[3]);
              IPAddress gip = WiFi.gatewayIP();
              String gipStr = String(gip[0]) + '.' + String(gip[1]) + '.' + String(gip[2]) + '.' + String(gip[3]);
              IPAddress dns = WiFi.dnsIP();
              String dnsStr = String(gip[0]) + '.' + String(gip[1]) + '.' + String(gip[2]) + '.' + String(gip[3]);
              IPAddress ip = WiFi.softAPIP();
              String ipStr = String(ip[0]) + '.' + String(ip[1]) + '.' + String(ip[2]) + '.' + String(ip[3]);


              //xilent.println("<p>");
              xilent.println("Durum sayfası");
              //if(Firebase.ready()) xilent.println("<font size=\"3\" color=\"#FF0000\">Dikkat Firebase çalışıyor. <br> Ayarlar yapılıp kaydedilirken ESP ye bağlı tüm cihazların gücünü kapatın.<br> Kayıttan sonra Reset anında pinlere İstek dışında enerji yollanabilir.<br> cihazlar istek dışı çalışabilir.<br></font>");
              xilent.println("<br><br>");
              xilent.println("    Local IP : ");
              xilent.println(lipStr);
              xilent.println("<br>");

              xilent.println("    Local Gateway : ");
              xilent.println(gipStr);
              xilent.println("<br>");

              xilent.println("    Access IP : ");
              xilent.println(ipStr);

              xilent.println("<br>");
              xilent.println("<br>    Wifi ismim       :" + esphostname);
              if (WiFi.status() == WL_CONNECTED) xilent.println("<br>    Bağlanılan Wifi  :" + ssid + "  Sinyal gücü : " + WiFi.RSSI());
              else xilent.println("<br>    Kayıtlı Wifi  :" + ssid + "  bağlanılamadı.");

              xilent.println("<br>    Kamera durum: ");
              //xilent.printf("Camera init failed with error 0x%x", err);

              if (err != ESP_OK) {
                  xilent.println("Camera init failed with error 0x% x");
                  xilent.println(err);
                } else
                { xilent.printf("Camera init OK ");// camerr="Camera init OK " + err;
                  xilent.println(err);
                }

//⚠️🔐🚨
              if(telegram_hazir==true) xilent.println("<br>    Telegram Chat Bot ayarları: yapılmış ✅<br>");
              else xilent.println("<br>    Telegram Chat Bot ayarları: yapılmamış ❌    <br>");
              xilent.println("<br><br>");
              xilent.println("<hr style=\"height:6px;border-width:1;color:black;background-color:black\">");
              xilent.println("<br>");


              xilent.println("    Reset bölümüdür.<br>");
              xilent.println("    <form method='post' action='reset'><label>        ⚠️ Reset</label>");
              xilent.println("   <input type='submit'>");
              xilent.println("</form>");

              xilent.println("<br>");
              xilent.println("<hr style=\"height:6px;border-width:1;color:black;background-color:black\">");
              xilent.println("<br>");
              } 



              if (header.indexOf("/pirdevrede")>-1 || header.indexOf("/ HTTP/1.1") > -1) {
              if(header.indexOf("/pirdevrede?")>-1)
              {
                if (header.indexOf("pir=") > -1) {
                  pirdevrede = header.substring((header.indexOf("pir=") + 4), header.indexOf(" HTTP/1.1"));
                  Serial.println(pirdevrede);
                  dosyayazpirdevrede();
                }
              }
              xilent.println("_______________________________");
              xilent.println("<br>");
              //camera_fb_t *fb = esp_camera_fb_get();

              xilent.println("Hareket sensörü");
//              xilent.println("            Kaydettikten sonra cihaza ⚠️ reset çekilecektir.");
              xilent.println("<br><form action=\"/pirdevrede\" method=\"get\"><label>Pir durum:");
              if(pirdevrede=="1")xilent.println(" devrede ");
              else xilent.println(" devre dışı ");
              xilent.println("</label><br><br><label >Pir devrede ? </label><input type='submit' name='pir' value='1'>Evet     <input type='submit' name='pir' value='0'>Hayır</form>");


              xilent.println("<br>");
              xilent.println("_______________________________");
              //xilent.println("    <label style='font-size:16px;'>📷</label>İzleme<br>");
              //xilent.println("    <form method='get' action='foto'><label>        Foto göster</label>");
              //xilent.println("   <input type='submit'>");
              //xilent.println("</form>");

  xilent.println("<br>");
  }
              IPAddress lip = WiFi.localIP();
              String lipStr = String(lip[0]) + '.' + String(lip[1]) + '.' + String(lip[2]) + '.' + String(lip[3]);
    //xilent.println("<a id=\"save-still\" href=" + lipStr + ":80/#\" class=\"button save\" download=\"capture.jpg\">Save</a>");
    xilent.println("</body></html>\r\n\r\n");


          xilent.stop();
          Serial.println("Client disconnected.");
          Serial.println("");
          if(header.indexOf("/reset")>-1)ESP.restart();
      }
    }
  }
}

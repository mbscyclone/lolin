void httpheader(WiFiClient xilent) {
  xilent.println("<!DOCTYPE HTML>\r\n<html>");
  xilent.println("<head><meta name=\"viewport\" xo=\"width=device-width, initial-scale=1\">");
  //xilent.println("<META charset=iso-8859-9\">";
  xilent.println("<meta charset=\"UTF-8\">");
  xilent.println("<link rel=\"icon\" href=\"data:,\">");

  xilent.println("<style>html {font-family:Helvetica;display:inline-block;margin:0px auto;text-align:left;}");
  xilent.println(".button{background-color:#195B6A;border:none;color:white; padding:16px 40px;font-size:10px; margin:2px;cursor:pointer;}");
  xilent.println(".button2{background-color:#77878A;border:none;color:white; padding:16px 40px;font-size:10px; margin:2px;cursor:pointer;}");
  xilent.println(".button3{background-color:#77878A;border:none;color:black; padding:16px 40px;font-size:10px; margin:2px;cursor:pointer;}");
  xilent.println("</style>");
  xilent.println("</head>");
  xilent.println("<body>");
  xilent.println("<font size=\"3\" color=\"#FF0000\">" + esphostname + "</font>");
  xilent.println("<br><table style=\"border:5px solid black;width:500px\"><tr>");
  xilent.println("<td style=\"border:1px solid black;width:250p; align:center; \">");
  xilent.println("<p><form action=\"/Menu0\" method=\"POST\"><input type=\"submit\" value=\"Anasayfa\"></form></p></td>");
  xilent.println("<td style=\"border:1px solid black;width:250p; align:center; \">");
  xilent.println("<p><form action=\"/\" method=\"POST\"><input type=\"submit\" value=\"Durum\"></form></p></td>");
  xilent.println("<td style=\"border:1px solid black;width:250px\">");
  xilent.println("<p><form action=\"/pnayar\" method=\"POST\"><input type=\"submit\" value=\"Pin ayar\"></form></p></td>");
  xilent.println("<td style=\"border:1px solid black;width:250px;\">");
  xilent.println("<p><form action=\"/ssidset\" method=\"POST\"><input type=\"submit\" value=\"Bağlantı ayar\"></form></p></td>");
  xilent.println("<td style=\"border:1px solid black;width:250px\">");
  xilent.println("<p><form action=\"/myssidnameayar\" method=\"POST\"><input type=\"submit\" value=\"Cihaz adı ayar\"></form></p></td>");
  xilent.println("<td style=\"border:1px solid black;width:250px\">");
  xilent.println("<p><form action=\"/serveripayar\" method=\"POST\"><input type=\"submit\" value=\"Server ip ayar\"></form></p></td>");

  xilent.println("<td style=\"border:1px solid black;width:250px\">");
  xilent.println("<p><form action=\"/mqttipayar\" method=\"POST\"><input type=\"submit\" value=\"MQTT ayar\"></form></p></td>");
  xilent.println("<td style=\"border:1px solid black;width:250px\">");
  xilent.println("<p><form action=\"/firebaseset\" method=\"POST\"><input type=\"submit\" value=\"Firebase ayar\"></form></p></td>");

  xilent.println("</tr></table>");
  //xilent.println("<font size=\"2\" color=\"#FFDDDD\">");
  //xilent.println(logintimeout);
  //xilent.println("<br></font>");
}

void htpcl() {
  WiFiClient xilent = httpserver.available();
  header.reserve(512);
  header = "";
  if (xilent) {

    // If a new xilent connects,
    Serial.println("New Client. fben:" + String(fben));  // print a message out in the serial port
    String currentLine = "";                             // make a String to hold incoming data from the xilent
    xcurrentTime = 0;
    while (xilent.connected() && xcurrentTime <= timeoutTime) {  // loop while the xilent's connected
      xcurrentTime += 1;
      if (xilent.available()) {  // if there's bytes to read from the xilent,

        for (int q = 0; q < 2000; q++) {
          char c = xilent.read();  // read a byte, then

          //Serial.print((int)c);
          if (int(c) == 255) break;
          Serial.print(c);  // print it out the serial monitor
          header += c;
        }
        if (header.indexOf("\n") > -1) {
          header = header.substring(0, header.indexOf("\n"));
          reConnectsayac = millis();

          //zamanfark=1555;

          IPAddress lip = WiFi.localIP();
          String lipStr = String(lip[0]) + '.' + String(lip[1]) + '.' + String(lip[2]) + '.' + String(lip[3]);


          creator = "M";
          // login kısmı
          //////////////////
          //////////////////
          //////////////////
          // http://192.168.2.84/auth:?capt=2927&unme=admin&pwrd=1234
          // bilgi geldiyse aut = 1 yapmak için
          /*  
          String xo2;
          if (aut == 0) {
            if (header.indexOf("?capt=") > -1) {
              String capttmp;
              String unmetmp;
              String pwrdtmp;
              if (header.indexOf("capt=") > -1) {
                capttmp = header.substring((header.indexOf("capt=") + 5), (header.indexOf("&unme")));
                xo2 = capttmp + "<br>";

                if (header.indexOf("&unme=") > -1) {
                  unmetmp = header.substring((header.indexOf("&unme=") + 6), (header.indexOf("&pwrd")));
                  xo2 += unmetmp + "<br>";
                }
                if (header.indexOf("&pwrd=") > -1) {
                  pwrdtmp = header.substring((header.indexOf("&pwrd=") + 6), (header.indexOf(" HTTP")));
                  xo2 += pwrdtmp + "<br>";
                }
              }
              if (capt == capttmp && unme == unmetmp && pwrd == pwrdtmp) {
                aut = 1;
                logintimeout = logintimeoutmax;
              } else {
                xo2 += "<br> HATALI GiRiS.";
              }
            }
          }

          if (aut == 0) {
            if (header.indexOf("/") > -1) {
              capt = String(random(1000, 9999));
              IPAddress lip = WiFi.localIP();
              String lipStr = String(lip[0]) + '.' + String(lip[1]) + '.' + String(lip[2]) + '.' + String(lip[3]);
              IPAddress gip = WiFi.gatewayIP();
              String gipStr = String(gip[0]) + '.' + String(gip[1]) + '.' + String(gip[2]) + '.' + String(gip[3]);
              IPAddress dns = WiFi.dnsIP();
              String dnsStr = String(gip[0]) + '.' + String(gip[1]) + '.' + String(gip[2]) + '.' + String(gip[3]);
              IPAddress ip = WiFi.softAPIP();
              String ipStr = String(ip[0]) + '.' + String(ip[1]) + '.' + String(ip[2]) + '.' + String(ip[3]);
              xilent.println("<!DOCTYPE HTML>\r\n<html>");
              xilent.println("<head><meta name=\"viewport\" xo=\"width=device-width, initial-scale=1\">");
              xilent.println("<META charset=iso-8859-9\">");
              xilent.println("</head>");
              //xilent.println("<body scroll=\"yes\" style=\"overflow: hidden\"><br>";
              xilent.println("<body><br>");
              xilent.println("<font size=\"3\" color=\"#FF0000\">" + esphostname + "</font>");

              xilent.println("<br>informations<br>");
               xilent.println(xo2);
              xilent.println("<br>");

              xilent.println("<br>");
              xilent.println("Local IP : ");
              xilent.println(lipStr);
              xilent.println("<br>");
              xilent.println("Local Gateway : ");
               xilent.println(gipStr);
              xilent.println("<br>");
              xilent.println("Access IP : ");
               xilent.println(ipStr);
              xilent.println("</td>");
              xilent.println("<form autocomplete=\"off\" action=\"/auth:\" method=\"get\"><br><label>" + capt + "<br><label>kodu gir: </label><input name='capt' length=4><br><label>Username: </label><input name='unme' length=32><label><br>password: </label><input name='pwrd' type='password' length=32><input type='submit'></form>");
              xilent.println("<br>");
              xilent.println("<br><br>");
              xilent.println("<br</body>");

              xilent.println();
              xilent.abort();;
              return;
            }
          }
*/

          //////////////////
          //////////////////

          creator += "ur";


          int headerset = 1;
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the xilent HTTP request, so send a response:  /*

          if (header.indexOf("/Menu0") > -1) Menu = 0;
          if (header.indexOf("/Menu1") > -1) Menu = 1;


          ///////////////////////////////////////////////////////////////
          ///////////////////////////////////////////////////////////////
          String seriptm = header;
          String serip = Karakterduzeltfunc(seriptm);
          if (serip.indexOf("/SEND>") > -1) {
            String htpServerip = "";
            String htpport = "";
            String port = "";
            String Sdata ="";
            if (serip.indexOf("http://") > -1) {
              htpServerip = serip.substring(serip.indexOf("http://"), serip.indexOf(",data:"));
              String porttmp = htpServerip.substring(htpServerip.indexOf("http://") + 7, htpServerip.length());
              if (porttmp.indexOf(":") > -1) {
                int portbas = porttmp.indexOf(":");
                htpServerip = serip.substring(serip.indexOf("http://"), portbas);
                port = serip.substring(portbas, serip.length());
              }
               Sdata = "/SEND>" + serip.substring(serip.indexOf("data:") + 5, serip.indexOf(" HTTP/1.1"));
            }
            else
            {
              Sdata = serip.substring(serip.indexOf("data:") + 5, serip.length());
            }

            Serial.print("Sdata: ");
            Serial.println(Sdata);

            if (htpServerip.length() > 0) {
              sendserver80(htpServerip, port, Sdata);
            } else {
              for (int z = 0; z < 11; z++) {
                if (Sdata.length() < 1) break;
                String pnm;
                String pns;

                if (Sdata.indexOf(":") > -1) {
                  pnm = Sdata.substring(0, Sdata.indexOf(":"));
                  if (Sdata.indexOf(",") > -1) {
                    pns = Sdata.substring(Sdata.indexOf(":") + 1, Sdata.indexOf(","));
                    Sdata = Sdata.substring(Sdata.indexOf(",") + 1, Sdata.length());
                  } else {
                    pns = Sdata.substring(Sdata.indexOf(":") + 1, Sdata.indexOf(" HTTP/1.1"));
                    Sdata = "";
                  }
                  Serial.println(pnm + " pnm1  ---  1pns " + pns);
                  if (pnm.indexOf("VR") == 0) {
                    Serial.println(pnm + " pnm2  ---  2pns " + pns);
                    for (int vrr = 0; vrr < 6; vrr++) {
                      if (pnm.indexOf("VR" + (String)vrr) == 0) {
                        VRP[vrr] = pns;
                      }
                    }
                  } else
                    for (int hh = 0; hh < 11; hh++) {
                      Serial.print("pnm=");
                      Serial.print(pnm);
                      Serial.print("pinname[hh]=");
                      Serial.println(pinname[hh]);
                      if (pnm == pinname[hh]) {
                        Serial.println(pnm + " pnm3  ---  3pns " + pns);
                        PinState[hh] = pns;
                        updateoutput();
                        break;
                      }
                    }
                }
              }
            }
          }

          /////////////////////////////////////////////////////////
          /////////////////////////////////////////////////////////////////////
          //////////////////////////////////////////////////////
          ////////////////////////////////////////////////////////////////














          if (Menu == 1) {

            if (header.indexOf("habp=Off") > -1) {
              habp = 0;
              dosyayazhabp();
              delay(10);
              ESP.reset();
            }

            if (header.indexOf("habp=mqt") > -1) {
              habp = 1;
              dosyayazhabp();
              delay(10);
              ESP.reset();
            }

            if (header.indexOf("habp=fir") > -1) {
              habp = 2;
              dosyayazhabp();
              delay(10);
              ESP.reset();
            }





            creator += "at";

            httpheader(xilent);

            if (header.indexOf("/pnayar") > -1 || header.indexOf("/programkayit") > -1) {
              if (header.indexOf("/programkayit?is=") > -1) {
                Serial.println("HEADER");
                Serial.println(header);
                String programdatatm = header.substring(header.indexOf("kayit?is=") + 9, (header.indexOf(" HTTP/")));
                Serial.println("PROGRAM YAZMAYA GİDİYORUM");
                Serial.println(programdatatm);
                dosyaYazprogram(programdatatm);
              }
              if (header.indexOf("/pnayar?is=") > -1) {
                pinayar = header.substring((header.indexOf("?is=") + 4), (header.indexOf(" HTTP/")));
                Serial.println(pinayar);
                pinayarchg = true;
                dosyaYazpinayar();
                dosyaOkupinayar();
              }


              xilent.println("Pin ayar sayfası <table> <caption>PIN AYARLARI</caption> <tr> <td scope=\"col\">pin ayarları:</td><td scope=\"col\">Pin Hata</td></tr>");
              xilent.println("<td><form method='get' action='pnayar'>");
              xilent.println("<textarea name='is' id='id' cols='40' rows='10' >");
              xilent.println(pinayar);
              xilent.println("</textarea><br>");
              //xilent.println("<br>ESP ye bağlı Cihazları kapatın.<br>");
              xilent.println("<input type='submit' value='Pinayar Kaydet'>");
              xilent.println("</form></td>");


              xilent.println("<td style='font-size:12px;vertical-align:top;'>");
              xilent.println(erlog);
              xilent.println("</td></tr></table>");
              xilent.println("<label style='font-size:14px;'>");
              xilent.println("Altta bir ornek verilmistir.<br>");
              xilent.println("<a href=\"https://mbscyclone.github.io/lolin/Help/Turkce/lolin_tr.pdf\" target=\"_blank\">Yardım [TR]</a>");
              xilent.println("D1|OUT|DIG|0|0|1|Sarj1_pirizi<br>");
              xilent.println("</label><br>");


              xilent.println("<table><caption>PROGRAM GiRiSi</caption><tr> <td scope=\"col\">Program:</td><td scope=\"col\">Program Hata</td></tr>");
              xilent.println("<tr><td>");

              xilent.println("<form method='get' action='programkayit'>");
              xilent.println("<textarea name='is' id='id' cols='40' rows='10' >");
              xilent.println(programdata);
              xilent.println("</textarea>");
              xilent.println("<br>");
              xilent.println("<input type='submit'>");
              xilent.println("</form>");
              xilent.println("</td><td style='font-size:12px;vertical-align:top;'>");
              xilent.println(perlog);
              xilent.println("</td></tr></table>Pinleri invert etmek için: PIN_INVERT; <br>");



              // Clear the header variable

              //xilent.abort();
            }
            creator += " B";
            //Serial.println(header);


            creator += "EK";

            if (header.indexOf("/ssidset") > -1) {


              if (header.indexOf("/ssidset?") > -1) {  //   "/ssidset?ssid=Zyxel&pass=bebedede14"

                // yazma kısmı

                if (header.indexOf("ssid=") > -1) {
                  ssid = header.substring((header.indexOf("ssid=") + 5), (header.indexOf("&")));
                  Serial.println(ssid);
                }
                if (header.indexOf("&pass=") > -1) {
                  pass = header.substring((header.indexOf("&pass=") + 6), (header.indexOf(" HTTP")));
                  Serial.println(pass);
                  dosyayazssidpass();
                  xilent.println();
                  ////xilent.abort();;
                  ESP.reset();
                }
              }

              IPAddress gip = WiFi.gatewayIP();
              String gipStr = String(gip[0]) + '.' + String(gip[1]) + '.' + String(gip[2]) + '.' + String(gip[3]);
              IPAddress dns = WiFi.dnsIP();
              String dnsStr = String(gip[0]) + '.' + String(gip[1]) + '.' + String(gip[2]) + '.' + String(gip[3]);
              IPAddress ip = WiFi.softAPIP();
              String ipStr = String(ip[0]) + '.' + String(ip[1]) + '.' + String(ip[2]) + '.' + String(ip[3]);

              xilent.println("Bağlantı ayar sayfası<table style=\"border:2px solid green;width:500px\"><tr><td style=\"border:1px solid black;width:250px\">");
              xilent.println("Bilgiler");
              xilent.println("<br>");
              xilent.println("<br>");
              xilent.println("Local IP : ");
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
              xilent.println("</td><tr></table>");
              xilent.println("Kaydettikten sonra cihaza resetlenir.");
              xilent.println("<br><form action=\"/ssidset\" method=\"get\"><label>SSID: </label><input name='ssid' length=32><label>PASS: </label><input name='pass' length=32><input type='submit'value='Kaydet'></form>");
              xilent.println("<br>");
              //xilent.println("Local IP : ");
              //xilent.println(lipStr);
              //xilent.println("<br>");
              //xilent.println("Local Gateway : ");
              //xilent.println(gipStr);
              //xilent.println("<br>");
              //xilent.println("Access IP : ");
              //xilent.println(ipStr);

              xilent.println("<br><br>");
              xilent.println("<br><br><br>");
            }




            if (header.indexOf(" /myssidnameayar") > -1) {

              if (header.indexOf(" /myssidnameayar?is=") > -1) {
                myssidyazilimi = header.substring((header.indexOf("?is=") + 4), (header.indexOf(" HTTP/")));
                Serial.println("baradan geçtim)");
                dosyayazmyssidname();
              }


              xilent.println("Cihaz adı ayar sayfası<form method='get' action='myssidnameayar'><label>Benim wifi ismim (SSID) : </label><input name='is' length=32 value=");
              xilent.println(myssidyazilimi);
              //xilent.println("><br>");
              //xilent.println("<label>Baglanilacak SERVER adressi: </label><input name='mq' length=32 value=");
              //              xo += SERVERip;
              xilent.println("><input type='submit'>");
              xilent.println("</form>");
              xilent.println("<br><br><br><br>");

              // Clear the header variable

              //xilent.abort();;
            }



            if (header.indexOf(" /serveripayar") > -1) {

              if (header.indexOf(" /serveripayar?is=") > -1) {
                htServerip = header.substring((header.indexOf("?is=") + 4), (header.indexOf(" HTTP/")));
                htserverkaydet(htServerip);
              }


              xilent.println("Server ip ayar sayfası<form method='get' action='serveripayar'><label>Haberleşilecek cihaz ip no (Boş ise işlem yapılmaz.): </label><input name='is' length=64 value=");
              xilent.println(htServerip);
              //xilent.println("><br>");
              //xilent.println("<label>Baglanilacak SERVER adressi: </label><input name='mq' length=32 value=");
              //              xo += SERVERip;
              xilent.println("><input type='submit'>");
              xilent.println("</form>");
              xilent.println("<br><br><br><br>");

              // Clear the header variable

              //xilent.abort();;
            }



            if (header.indexOf(" /mqttipayar") > -1) {

              if (header.indexOf(" /mqttipayar?is=") > -1) {
                MQTTip = header.substring((header.indexOf("?is=") + 4), (header.indexOf(" HTTP/")));
                mqttipkaydet(MQTTip);
              }


              xilent.println("MQTT ayar sayfası<form method='get' action='mqttipayar'><label>Bağlanılacak MQTT server ip: </label><input name='is' length=64 value=");
              xilent.println(MQTTip);
              //xilent.println("><br>");
              //xilent.println("<label>Baglanilacak SERVER adressi: </label><input name='mq' length=32 value=");
              //              xo += SERVERip;
              xilent.println("><input type='submit'>");
              xilent.println("</form>");
              xilent.println("<br><br><br><br>");

              // Clear the header variable

              //xilent.abort();;
            }


            creator += "T";
            //Serial.println(header);



            creator += "AŞ";
            /*
            if (header.indexOf(" /Boardtype?is=") > -1) {
              String Boardtypetmp = header.substring((header.indexOf("?is=") + 4), (header.indexOf("&mq=")));
              Boardtype = Boardtypetmp.toInt();
              dosyaYazBoardtype();
              Serial.println("Write flash file ssidname;Boardtype;");
              Serial.println(Boardtype);
              httpheader(xilent);
              xilent.println("<form method='get' action='/Boardtype'><label>ESP Board tipi ( Esp-01 icin 0  Esp-lolin icin 1) : </label><input name='is' length=32 value=");
              xilent.println(Boardtype);
              xilent.println("><input type='submit'>");
              xilent.println("</form>");
              if (Boardtype == 0) xilent.println("<form method='get' action='SERVERayar'><label>My SSID Name: </label><input name='is' length=32 value=");
              if (Boardtype == 1) xilent.println("<form method='get' action='SERVERayar'><label>My SSID Name: </label><input name='is' length=32 value=");
              xilent.println(myssidyazilimi);
              xilent.println("><br>");
              xilent.println("<label>Baglanilacak SERVER adressi: </label><input name='mq' length=32 value=");
//              xo += SERVERip;
              xilent.println("><input type='submit'>");
              xilent.println("</form>");
              xilent.println("<br>");
            }
*/


            /*

            if (header.indexOf(" /SERVERuser") > -1) {
              httpheader(xilent);
              dosyaOkuusers();
              xilent.println("Kullanici Adi ve Sifresi giris formati admin|sifre seklinde olmalidir.");
              xilent.println("<form method='get' action='SERVERusrkayit'><label>Kullanici Adlari ve sifreleri:</label>");
              xilent.println("<br>");
              xilent.println("<textarea name='is' id='id' cols='30' rows='10' >");
              xilent.println(users);
              xilent.println("</textarea>");

              xilent.println("<br>");
              xilent.println("<input type='submit'>");
              xilent.println("</form>");
              xilent.println("<br><br><br>Altta giris ornegi verilmistir.<br><br>admin|1234<br>murat|123456<br>ali|111222<br><br><br><br>");

              // Clear the header variable

              //xilent.abort();;
            }

            //Serial.println(header);

            if (header.indexOf(" /SERVERusrkayit?is=") > -1) {
              users = header.substring((header.indexOf("?is=") + 4), (header.indexOf(" HTTP/")));

              dosyaYazusers();

              dosyaOkuusers();
              Serial.println("Write flash file users");
              Serial.println(users);


              httpheader(xilent);

              xilent.println("<form method='get' action='SERVERusrkayit'><label>SERVER users</label> ");
              xilent.println("<textarea name='is' id='id' cols='30' rows='10' >");
              xilent.println(users);
              xilent.println("</textarea>");
              xilent.println("<br>");
              xilent.println("<input type='submit'>");
              xilent.println("</form>");
              xilent.println("<br><br><br><br><br><br><br><br>");


              //---------------------------------------- Write flash for ssid and pass
            }
            
            
            */





            Serial.println(header);
            if (header.indexOf(" /firebaseset") > -1) {
              /*
              dosyaokufburl();
              dosyaokufbapi();
              dosyaokufbyol();
              dosyaokufbusername();
              dosyaokufbuserpass();
*/









              xilent.println("Firebase ayar sayfası<br>Realtime Database Ayarlari<br><br>");


              String errstring = "";
              if (header.indexOf("?fburl=") > -1)

              {
                String hdrt = header;
                header = Karakterduzeltfunc(hdrt);
                //Serial.println(header);
                DATABASE_URL = header.substring(header.indexOf("?fburl=") + 7, header.indexOf("&fbapi="));
                if (DATABASE_URL.indexOf(".") > -2 && DATABASE_URL.indexOf(".") < 2) {
                  errstring += "URL Yanlis girilmis.<br>";
                }
                if (DATABASE_URL.length() == 0 || DATABASE_URL == "") {
                  errstring += "URL boş birakilmis.<br>";
                }


                API_KEY = header.substring(header.indexOf("&fbapi=") + 7, header.indexOf("&fbyol"));
                if (API_KEY.length() < 32) {
                  errstring += "API_KEY Yanlış.<br>";
                }

                if (API_KEY.length() < 1 || API_KEY == "") {
                  errstring += " API_KEY boş.<br>";
                }

                YOL = header.substring(header.indexOf("&fbyol=") + 7, header.indexOf(" HTTP/1.1"));
                if (YOL.length() > 10) {
                  errstring += "YOL Yanlış.<br>";
                }

                if (YOL.length() < 1 || YOL == "") {
                  errstring += " YOL boş.<br>";
                }



                if (errstring == "") {
                  dosyayazfburl();
                  dosyayazfbapi();
                  dosyayazfbyol();
                }
              }






              if (header.indexOf("?fbeml1=") > -1)

              {
                String hdrt = header;
                header = Karakterduzeltfunc(hdrt);
                //Serial.println(header);
                USER_EMAIL1 = header.substring(header.indexOf("?fbeml1=") + 8, header.indexOf("&fbeml2="));
                if (USER_EMAIL1.length() == 0 || USER_EMAIL1 == "") {
                  errstring += "E-MAIL ön boş.<br>";
                }
                USER_EMAIL2 = header.substring(header.indexOf("&fbeml2=") + 8, header.indexOf("&fbupw="));
                if (USER_EMAIL2.indexOf(".") < 0) {
                  errstring += "E-MAIL Yanlis.<br>";
                }
                if (USER_EMAIL2.length() == 0 || USER_EMAIL2 == "") {
                  errstring += "E-MAIL boş.<br>";
                }

                USER_PASSWORD = header.substring(header.indexOf("&fbupw=") + 7, header.indexOf(" HTTP/1.1"));
                if (USER_PASSWORD.length() < 2) {
                  errstring += " PASSWORD Yanlış.<br>";
                }

                if (USER_PASSWORD.length() < 1 || USER_PASSWORD == "") {
                  errstring += " PASSWORD boş.<br>";
                }
                if (errstring == "") {
                  dosyayazfbusername();
                  dosyayazfbuserpass();
                }
              }


              if (fben == 1 && DATABASE_URL != "" && API_KEY != "" && USER_EMAIL != "" && USER_PASSWORD != "") {
                errstring = "Firebase Ayarları yapılmış.";
              }

              // autocomplete=\"off\"

              xilent.println("<hr style=\"height:4px;border-width:0;color:black;background-color:gray\">");

              xilent.println("<br>");

              USER_EMAIL1 = USER_EMAIL.substring(0, USER_EMAIL.indexOf("@"));
              USER_EMAIL2 = USER_EMAIL.substring(USER_EMAIL.indexOf("@") + 1, USER_EMAIL.length());


              xilent.println("<form method='get' action='/firebaseset'>");
              xilent.println("<label>FBRTD nin URL ve API_KEY'i yazın <br> URL  : </label>");
              xilent.println("<input name='fburl' id='fburl' style=\"width:350px;\" value='");
              xilent.println(DATABASE_URL);
              xilent.println("'><br><br>");
              xilent.println("<label>API_KEY:</label><input name='fbapi' id='fbapi' style=\"width:320px;\" value='");
              xilent.println(API_KEY);
              xilent.println("'><br><br>");
              xilent.println("<label>Database deki Yol (Örnek: Balıkesir ev1: bev1, yazlık 10Yz1, gibi kısa kodlar kullanın)<br> YOL : </label><input name='fbyol' id='fbyol' style=\"width:70px;\" value='");
              xilent.println(YOL);
              xilent.println("'><input type='submit'>");
              xilent.println("</form>");
              xilent.println("<hr style=\"height:4px;border-width:0;color:black;background-color:gray\">");

              xilent.println("<form method='get' action='/firebaseset'>");
              xilent.println("<label>Auth kullanıcı e-mailini ve şifresini girin <br> E-MAIL : </label>");
              xilent.println("<input name='fbeml1' id='fbeml1' style=\"width:150px;\" value='");
              xilent.println(USER_EMAIL1);
              xilent.println("'>@");

              xilent.println("<input name='fbeml2' id='fbeml2' style=\"width:150px;\" value='");
              xilent.println(USER_EMAIL2);
              xilent.println("'>");


              xilent.println("<br><br>");
              xilent.println("<label>PASSWORD:</label><input name='fbupw' id='fbupw' style=\"width:120px;\" value='");
              xilent.println(USER_PASSWORD);
              xilent.println("'><input type='submit'>");
              xilent.println("</form>");
              xilent.println("<br><hr style=\"height:4px;border-width:0;color:black;background-color:gray\">");


              ////////
              if (DATABASE_URL != "" && API_KEY != "" && USER_EMAIL != "" && USER_PASSWORD != "") {
                xilent.println("<form action=\"/firebaseset\"><label for=\"option\">Firebase protokolu:</label><select id=\"fireb\" name=\"fireb\" ");

                xilent.println(">");

                if (header.indexOf("fireb=Off") > -1) {
                  fben = 0;
                  dosyayazfben();
                  delay(10);
                  ESP.reset();
                }
                if (fben == 0) {
                  xilent.println("<option value=\"Off\" selected");
                } else {
                  xilent.println("<option value=\"Off\"");
                }

                xilent.println(">Kapali</option>");

                if (header.indexOf("fireb=On") > -1) {
                  fben = 1;
                  dosyayazfben();
                  delay(10);
                  ESP.reset();
                }
                if (fben == 1) {
                  xilent.println("<option value=\"On\" selected");
                } else {
                  xilent.println("<option value=\"On\"");
                }



                xilent.println(">Acik</ option>");
                xilent.println("</select><input type=\"submit\" value=\"Submit\"></form>");
              }
              ////////




              xilent.println("<br><br>" + errstring + "<br><br>");

              // Clear the header variable

              //xilent.abort();;
            }


            if (header.indexOf("/ HTTP/1.1") > -1 || header.indexOf("/ HTTP/1.1") > -1 || header.indexOf("/Menu1") > -1) {

              //Serial.println(Menu);
              //Serial.println(header);
              //Serial.println(xo);
              IPAddress lip = WiFi.localIP();
              String lipStr = String(lip[0]) + '.' + String(lip[1]) + '.' + String(lip[2]) + '.' + String(lip[3]);
              IPAddress gip = WiFi.gatewayIP();
              String gipStr = String(gip[0]) + '.' + String(gip[1]) + '.' + String(gip[2]) + '.' + String(gip[3]);
              IPAddress dns = WiFi.dnsIP();
              String dnsStr = String(gip[0]) + '.' + String(gip[1]) + '.' + String(gip[2]) + '.' + String(gip[3]);
              IPAddress ip = WiFi.softAPIP();
              String ipStr = String(ip[0]) + '.' + String(ip[1]) + '.' + String(ip[2]) + '.' + String(ip[3]);


              //xilent.println("<p>");
              xilent.println("<br> Durum sayfası");
              //if(Firebase.ready()) xilent.println("<font size=\"3\" color=\"#FF0000\">Dikkat Firebase çalışıyor. <br> Ayarlar yapılıp kaydedilirken ESP ye bağlı tüm cihazların gücünü kapatın.<br> Kayıttan sonra Reset anında pinlere İstek dışında enerji yollanabilir.<br> cihazlar istek dışı çalışabilir.<br></font>");
              xilent.println("<br>");
              xilent.println("Local IP : ");
              xilent.println(lipStr);
              xilent.println("<br>");

              xilent.println("Local Gateway : ");
              xilent.println(gipStr);
              xilent.println("<br>");

              xilent.println("Access IP : ");
              xilent.println(ipStr);

              xilent.println("<br>");
              xilent.println("<br>Wifi ismim       :" + esphostname);
              if (WiFi.status() == WL_CONNECTED) xilent.println("<br>Bağlanılan Wifi  :" + ssid + "  Sinyal gücü : " + WiFi.RSSI());
              else xilent.println("<br>Kayıtlı Wifi  :" + ssid + "  bağlanılamadı.");
              if (pinayar.length() < 2) xilent.println("<br>Pin ayarları yapılmamış!");
              else xilent.println("<br>Pin ayarları tamam");
              xilent.println("<br>Bağlanılacak MQTT server ip:" + MQTTip);
              xilent.println("<br>Firebase data yolu:" + YOL);
              xilent.println("<br>Firebase url     :" + DATABASE_URL);
              xilent.println("<br>FB RTD kullanıcısı:" + USER_EMAIL);


              xilent.println("<br><br>Diğer cihazlarla haberleşilecek protokol değiştirildiğinde ESP restart yapılacak!!!");
              xilent.println("<form action=\"/habp\"><label for=\"option\">Diğer cihazlarla haberleşilecek protokol:</label><select id=\"habp\" name=\"habp\" ");
              xilent.println(">");


              if (habp == 0) {
                xilent.println("<option value=\"off\" selected");
              } else {
                xilent.println("<option value=\"off\"");
              }

              xilent.println(">Kapali</option>");

              if (habp == 1) {
                xilent.println("<option value=\"mqt\" selected");
              } else {
                xilent.println("<option value=\"mqt\"");
              }

              xilent.println(">MQTT</option>");

              if (habp == 2) {
                xilent.println("<option value=\"fir\" selected");
              } else {
                xilent.println("<option value=\"fir\"");
              }
              xilent.println(">Firebase</option>");
              xilent.println("</select><input type=\"submit\" value=\"Submit\"></form>");










              xilent.println("<br><br><br>");
              xilent.println("<a href=\"https://mbscyclone.github.io/lolin/Help/Turkce/lolin_tr.pdf\" target=\"_blank\">Yardım [TR]</a>");
              xilent.println("<br>");

              // Clear the header variable


              xilent.println();
            }


            // Clear the header variable
            xilent.println("coded by " + creator + ". ESP kontrol (v4");
            xilent.println("<label style='font-size:1px;'>" + WiFi.macAddress() + "</label>04.01.2026)<br><br>");
            xilent.println("</html>");
            xilent.println();
            /////xilent.abort();;
          }

          if (Menu == 0) {

            creator += "at";
            //                              Serial.print("butonpbgcol:");
            //                          Serial.println(butonpbgcol);
            //dosyaOkupinayar();

            //xo+="Connection: close";

            // LOW İKEN RÖLE ÇALIŞIYOR

            // turns the GPIOs on   Motor
            // İşlemler

            String Headerparcala = header;
            int indis = -1;
            String pinismi = "";
            String pinkomut;
            String PWMdeger;
            String Analoggelendeger;
            String Digitalgelendeger;

            //Serial.print("Headerparcala :"); Serial.println(Headerparcala);


            //butonactcol butonpascol butonayrcol butonpbgcol


            //String butonactcol = "#d1ca03";
            //String butonpascol = "#A3A3A3";
            //String butonayrcol = "#20d3c8";
            //String butonpbgcol = "#ffb12a";


            if (Headerparcala.indexOf(" /butonactcol") > -1) {
              Headerparcala = Headerparcala.substring(Headerparcala.indexOf("/butonactcol") + 16, Headerparcala.length());
              butonactcol = Headerparcala.substring(0, Headerparcala.indexOf(" HTTP"));
              butonactcolyaz();
            }

            if (Headerparcala.indexOf(" /butonpascol") > -1) {
              Headerparcala = Headerparcala.substring(Headerparcala.indexOf("/butonpascol") + 16, Headerparcala.length());
              butonpascol = Headerparcala.substring(0, Headerparcala.indexOf(" HTTP"));
              butonpascolyaz();
            }

            if (Headerparcala.indexOf(" /butonayrcol") > -1) {
              Headerparcala = Headerparcala.substring(Headerparcala.indexOf("/butonayrcol") + 16, Headerparcala.length());
              butonayrcol = Headerparcala.substring(0, Headerparcala.indexOf(" HTTP"));
              butonayrcolyaz();
            }

            if (Headerparcala.indexOf(" /butonpbgcol") > -1) {
              Headerparcala = Headerparcala.substring(Headerparcala.indexOf("/butonpbgcol") + 16, Headerparcala.length());
              //Serial.println(Headerparcala);
              butonpbgcol = Headerparcala.substring(0, Headerparcala.indexOf(" HTTP"));
              butonpbgcolyaz();
            }

            creator += " B";

            //LOLİN için
            if (Headerparcala.indexOf("GET /D") > -1) {

              if (header.indexOf("?pwm=") > -1) {
                Headerparcala = Headerparcala.substring(Headerparcala.indexOf(" /D") + 2, Headerparcala.length());
                pinismi = Headerparcala.substring(0, Headerparcala.indexOf("?"));
              } else if (header.indexOf("?ser=") > -1) {
                Headerparcala = Headerparcala.substring(Headerparcala.indexOf(" /D") + 2, Headerparcala.length());
                pinismi = Headerparcala.substring(0, Headerparcala.indexOf("?"));
              } else {
                Headerparcala = Headerparcala.substring(Headerparcala.indexOf(" /D") + 2, Headerparcala.length());
                pinismi = Headerparcala.substring(0, Headerparcala.indexOf("/"));
              }


              int pinismiint;
              if (pinismi.length() > 1)
                pinismiint = pinismi.substring(1, 2).toInt();
              else pinismiint = pinismi.toInt();
              /*
                for(int qq=0;qq<sizeof(Pin)+1qq++){
                  Serial.print( qq ); Serial.println("       " + pinsignaltype[qq]);
                }
              Serial.println(pinsignaltype[pinismiint]);
*/
              // pinsinyaline göre parametre eklenecek PWM için PWM degeri
              if (pinsignaltype[pinismiint] == "PWM") {
                // Serial.println(Headerparcala);
                Headerparcala = Headerparcala.substring(Headerparcala.indexOf("?pwm=") + 5, Headerparcala.length());
                pinkomut = "";
                PWMdeger = Headerparcala.substring(0, Headerparcala.indexOf(" HTTP"));
                //Serial.println(PWMdeger);
                //Serial.println("pwmdeger:::::::::::::::::::::: " + PWMdeger);
                PinState[pinismiint] = PWMdeger;
              } else if (pinsignaltype[pinismiint] == "SER") {
                //Serial.println(Headerparcala);
                Headerparcala = Headerparcala.substring(Headerparcala.indexOf("?ser=") + 5, Headerparcala.length());
                pinkomut = "";
                PWMdeger = Headerparcala.substring(0, Headerparcala.indexOf(" HTTP"));
                //Serial.println(PWMdeger);
                //Serial.println("pwmdeger:::::::::::::::::::::: " + PWMdeger);
                PinState[pinismiint] = PWMdeger;
              } else {
                Headerparcala = Headerparcala.substring(Headerparcala.indexOf(":") + 1, Headerparcala.length());
                pinkomut = Headerparcala.substring(0, Headerparcala.indexOf(" HTTP"));
              }


              //Serial.print("pinkomut : ");Serial.println(pinkomut);




              //Programtakip(programdata);
              zamanfark = 1555;
            }
            creator += "EK";











            if (header.indexOf("GET /A") > -1) {

              if (header.indexOf("?pwm=") > -1) {
                Headerparcala = Headerparcala.substring(Headerparcala.indexOf(" /D") + 2, Headerparcala.length());
                pinismi = Headerparcala.substring(0, Headerparcala.indexOf("?"));
              } else if (header.indexOf("?ser=") > -1) {
                Headerparcala = Headerparcala.substring(Headerparcala.indexOf(" /D") + 2, Headerparcala.length());
                pinismi = Headerparcala.substring(0, Headerparcala.indexOf("?"));
              } else {
                Headerparcala = Headerparcala.substring(Headerparcala.indexOf(" /D") + 2, Headerparcala.length());
                pinismi = Headerparcala.substring(0, Headerparcala.indexOf("/"));
              }


              int pinismiint;
              if (pinismi.length() > 1)
                pinismiint = pinismi.substring(1, 2).toInt();
              else pinismiint = pinismi.toInt();


              if (pinismi.indexOf("A") > -1) pinismiint += 9;



              Serial.print(pinismi + " ");

              if (pinmode[pinismiint] == "OUT" & pinsignaltype[pinismiint] == "DIG") {

                if (pinkomut == "1" || pinkomut == "HIGH" || pinkomut == "ON") {
                  PinState[pinismiint] = "1";
                }

                if (pinkomut == "0" || pinkomut == "LOW" || pinkomut == "OFF") {
                  PinState[pinismiint] = "0";
                }
              }


              if (pinmode[pinismiint] == "OUT" && pinsignaltype[pinismiint] == "PWM") {
                int PWMdegerint = PWMdeger.toInt();
                PinState[pinismiint] = PWMdeger;
                if (PinState[pinismiint] != ePinState[pinismiint]) {
                  Outpwm(pinismi, PWMdegerint);
                }
              }
              zamanfark = 1555;
            }











            creator += "T";

            if (header.indexOf((" /rr120")) > -1) sayfayenile = 120;
            if (header.indexOf((" /rr30")) > -1) sayfayenile = 30;
            if (header.indexOf((" /rr10")) > -1) sayfayenile = 10;
            if (header.indexOf((" /rr0")) > -1) sayfayenile = 0;

            pinkomut.toUpperCase();
            //Serial.print("pinkomut.toUpperCase()"); Serial.println(pinkomut);
            //dosyaOkupinayar();

            int pinismiint;
            if (pinismi.length() > 1)
              pinismiint = pinismi.substring(1, 2).toInt();
            else pinismiint = pinismi.toInt();

            if (pinismi.indexOf("A") > -1) pinismiint += 9;

            creator += "AŞ";

            Serial.print(pinismi + " ");

            if (pinmode[pinismiint] == "OUT" & pinsignaltype[pinismiint] == "DIG") {

              if (pinkomut == "1" || pinkomut == "HIGH" || pinkomut == "ON") {
                PinState[pinismiint] = "1";
                //Programtakip(programdata);
              }

              if (pinkomut == "0" || pinkomut == "LOW" || pinkomut == "OFF") {
                PinState[pinismiint] = "0";
                //Programtakip(programdata);
              }
            }


            if (pinmode[pinismiint] == "OUT" && pinsignaltype[pinismiint] == "PWM") {
              int PWMdegerint = PWMdeger.toInt();
              PinState[pinismiint] = PWMdeger;
              if (PinState[pinismiint] != ePinState[pinismiint]) {
                Outpwm(pinismi, PWMdegerint);
                //Programtakip(programdata);
              }
            }

            if (pinmode[pinismiint] == "OUT" && pinsignaltype[pinismiint] == "SER") {
              int PWMdegerint = PWMdeger.toInt();
              if (PWMdegerint > 180) PWMdegerint = 180;
              PinState[pinismiint] = String(PWMdegerint);
              if (PinState[pinismiint] != ePinState[pinismiint]) {
                myservo[pinismiint].write(PWMdegerint);
                //Programtakip(programdata);
              }
            }










            for (int x = 0; x < sizeof(Pin) + 1; x++) {

              if (pinmode[x] == "OUT" & pinsignaltype[x] == "DIG") {
                if (PinState[x] == "0.00" || PinState[x] == "0" || PinState[x] == "LOW" || PinState[x] == "OFF") {
                  if (high_low_invert == false) digitalWrite(Pin[x], LOW);
                  else digitalWrite(Pin[x], HIGH);
                }

                if (PinState[x] == "1.00" || PinState[x] == "1" || PinState[x] == "HIGH" || PinState[x] == "ON") {
                  if (high_low_invert == false) digitalWrite(Pin[x], HIGH);
                  else digitalWrite(Pin[x], LOW);
                }
              }


              if (pinmode[x] == "OUT" && pinsignaltype[x] == "PWM") {
                int PWMdegerint = PinState[x].toInt();
                Outpwm(pinname[x], PWMdegerint);
              }

              if (pinmode[x] == "OUT" && pinsignaltype[x] == "SER") {
                int PWMdegerint = PinState[x].toInt();
                myservo[x].write(PWMdegerint);
              }
            }





            IPAddress lip = WiFi.localIP();
            String lipStr = String(lip[0]) + '.' + String(lip[1]) + '.' + String(lip[2]) + '.' + String(lip[3]);

            xilent.println("<!DOCTYPE html><html><head><title>" + esphostname + "  -> " + lipStr + " - ESP8266-Pro.v4</title>");

            xilent.println("<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            xilent.println("<meta charset=\"UTF-8\">");

            if (sayfayenile > 0) xilent.println("<script> setTimeout(function(){window.location.href = \"\";}, " + String(sayfayenile * 1000) + ");</script>");

            xilent.println("<link rel=\"icon\" href=\"data:,\">");
            // CSS to style the on/off buttons
            // Feel free to change the background-color and font-size attributes to fit your preferences
            xilent.println("<style>html{ font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            // xilent.println(".button { background-color: #195B6A; border: none; color: white; padding: 16px 40px;text-decoration: none; font-size: 20px; margin: 2px; cursor: pointer;}");


            //xilent.println(".button { background-color: #195B6A; border: none; color: white; padding: 16px 40px;text-decoration: none; font-size: 10px; margin: 2px; cursor: pointer;}";
            //xilent.println(".button2 {background-color: #77878A; border: none; color: white; padding: 16px 40px;text-decoration: none; font-size: 10px; margin: 2px; cursor: pointer;}";
            //xilent.println(".button3 {background-color: #77878A; border: none; color: black; padding: 16px 40px;text-decoration: none; font-size: 10px; margin: 2px; cursor: pointer;}";


            //xilent.println(".button { background-color: #196B7A; border: none; color: white; padding: 10px 10px;text-decoration: none; font-size: 10px; margin: 1px; cursor: pointer;}");
            //xilent.println(".butoff {background-color: #A3A3A3; border: none; color: white; padding: 10px 10px;text-decoration: none; font-size: 10px; margin: 1px; cursor: pointer;");

            xilent.println(".button { background-color: #" + butonactcol + "; border: 5px solid yellow; border-radius: 10px 10px 10px 10px; color: white; padding: 10px 10px;text-decoration: none; font-size: 12px; margin: 1px; cursor: pointer;}");
            xilent.println(".butoff {background-color: #" + butonpascol + "; border: 5px solid gray; border-radius: 10px 10px 10px 10px; color: white; padding: 10px 10px;text-decoration: none; font-size: 12px; margin: 1px; cursor: pointer;}");
            xilent.println(".butayr {background-color: #" + butonayrcol + "; border: 5px solid gray; border-radius: 6px 6px 20px 15px; color: black; padding: 10px 10px;text-decoration: none; font-size: 12px; margin: 1px; cursor: pointer;}");
            xilent.println("</style>");

            xilent.println("<style>body {background-color: #" + butonpbgcol + ";} </style>");  //darkblue, lightblue, #b0b0b0 gibi



            xilent.println("</head>");

            // Web Page Heading
            String sonek = esphostname.substring(esphostname.indexOf("-") + 1, esphostname.length());

            xilent.println("<body><div align=\"center\">");
            xilent.println("<label style='font-size: 10px;'>Sayfayı yenileme için alttaki düğmeyi kullanabilirsiniz</label><br>");
            xilent.println("<table style=\"border:5px solid black;width:00px\"><tr>");
            xilent.println("<td style=\"border:0px solid black;width:90p; align:center; \">");

            xilent.println("<td style=\"border:1px solid black;width:250p; align:center; \">");
            if (sayfayenile == 120)
              xilent.println("<form action=\"/rr120\" method=\"POST\"><input type=\"submit\" value=\"120s\" style='width:50px;background-color:yellow;'></form></td>");
            else
              xilent.println("<form action=\"/rr120\" method=\"POST\"><input type=\"submit\" value=\"120s\" style='width:50px;'></form></td>");

            xilent.println("<td style=\"border:1px solid black;width:250p; align:center; \">");
            if (sayfayenile == 30)
              xilent.println("<form action=\"/rr30\" method=\"POST\"><input type=\"submit\" value=\"30s\" style='width:50px;background-color:yellow;'></form></td>");
            else
              xilent.println("<form action=\"/rr30\" method=\"POST\"><input type=\"submit\" value=\"30s\" style='width:50px;'></form></td>");

            xilent.println("<td style=\"border:1px solid black;width:250p; align:center; \">");
            if (sayfayenile == 10)
              xilent.println("<form action=\"/rr10\" method=\"POST\"><input type=\"submit\" value=\"10s\" style='width:50px;background-color:yellow;'></form></td>");
            else
              xilent.println("<form action=\"/rr10\" method=\"POST\"><input type=\"submit\" value=\"10s\" style='width:50px;'></form></td>");

            xilent.println("<td style=\"border:1px solid black;width:250p; align:center; \">");

            xilent.println("<form action=\"/rr0\" method=\"POST\"><input type=\"submit\" value=\"Kapat\" style='width:50px;'></form></td>");

            xilent.println("<td style=\"border:1px solid black;width:250p; align:center; \">");

            xilent.println("<form action='/rr0' method=\"POST\"><input type=\"submit\" value=\" Yenile\" style='width:80px;'></form>");
            //xilent.println("<form action='/' method=\"POST\"><input type=\"submit\" value=\" Yenile\" style='width:80px;'></form>");
            xilent.println("</td></table></div>");

            if (sayfayenile > 0) xilent.println("<label style='font-size: 10px;'>Sayfayı yenile Açık " + String(sayfayenile) + " saniyede bir yenilenecek</label>");
            if (sayfayenile == 0) xilent.println("<label style='font-size: 10px;'>Sayfayı yenile Kapalı</label>");

            xilent.println("<h2>" + sonek + "</h2>");
            //xilent.println("> Device_ident: ");
            //xilent.println(esphostname + "<br>");
            lip = WiFi.localIP();
            lipStr = String(lip[0]) + '.' + String(lip[1]) + '.' + String(lip[2]) + '.' + String(lip[3]);
            if (String(lip[0]) == "0") xilent.println(" Not connected.");
            if (String(lip[0]) != "0") {
              xilent.println("  Ipadr: ");
              xilent.println(lipStr);
            }
            if (header.indexOf("fireb=On") > -1) {
              fben = 1;
              dosyayazfben();
              delay(10);
              ESP.reset();
            }
            if (header.indexOf("fireb=Off") > -1) {
              fben = 0;
              dosyayazfben();
              delay(10);
              ESP.reset();
            }

            xilent.println("<br>");
            xilent.println("<label style='font-size: 12px;'>");
            if (fben == 1) xilent.println("<form action=\"/firebaseset?fireb=Off\" method=\"POST\">Firebase Açık<input type=\"submit\" value=\"FB Kapat\">! Reset çekilir !</form></label>");
            if (fben == 0) xilent.println("<form action=\"/firebaseset?fireb=On\" method=\"POST\">Firebase Kapalı<input type=\"submit\" value=\"FB Aç\">! Reset çekilir !</form></label>");




            xilent.println("<br><form action=\"/habp\"><label style='font-size: 12px;' for=\"option\">Haberleşme protokolü:<select id=\"habp\" name=\"habp\" ");
            xilent.println(">");


            if (habp == 0) {
              xilent.println("<option value=\"off\" selected");
            } else {
              xilent.println("<option value=\"off\"");
            }

            xilent.println(">Kapali</option>");

            if (habp == 1) {
              xilent.println("<option value=\"mqt\" selected");
            } else {
              xilent.println("<option value=\"mqt\"");
            }

            xilent.println(">MQTT</option>");

            if (habp == 2) {
              xilent.println("<option value=\"fir\" selected");
            } else {
              xilent.println("<option value=\"fir\"");
            }
            xilent.println(">Firebase</option>");
            xilent.println("</select><input type=\"submit\" value=\"Değistir\">ildiğinde ! Reset çekilir !</form></label>");





            int pindolusay = -1;
            for (int m = 9; m > 0; m--) {
              if (pinname[m] != "") {
                pindolusay = m + 1;
                break;
              }
            }
            if (pindolusay == -1) {
              xilent.println("<p>Pin Ayarları Yok</p>");
              xilent.println("<br><br><br><br><p><a href=\"/Menu1\"><button class=\"button butayr\">Ayarlar</button></a></p>");
              // The HTTP response ends with another blank line
              xilent.println("HTTP/1.1 200 OK");
              xilent.println("Content-type:text/html");
              xilent.println("Connection: close");
              xilent.println();
              ////xilent.abort();;
              return;
            }
            for (int x = 0; x < pindolusay; x++) {


              if (pinname[x] != "") {
                xilent.println("<hr style=\"height:6px;border-width:1;color:black;background-color:black\">");
                //xilent.println(pinsignaltype[x] + "<br>");
                if (pinmode[x] == "OUT" && pinsignaltype[x] == "DIG") {
                  // Display current state, and ON/OFF buttons for GPIO x
                  xilent.println(pinlabel[x] + " [" + pinname[x] + "]= " + PinState[x] + " ");
                  // If the Pin0State is off, it displays the ON button
                  if (PinState[x] == "") PinState[x] = "0";  //                    v--- " + pinlabel[x] + " [" +  pinname[x] + "]= " + PinState[x] + "

                  if (PinState[x] == "0") {  //                    v--- " + pinlabel[x] + " [" +  pinname[x] + "]= " + PinState[x] + "
                    xilent.println("<a href=\"/" + pinname[x] + ":1\"><button class=\"button butoff\">-0-</button></a>");
                    if (high_low_invert == true) xilent.println(" Çıkış [1]");
                  }

                  if (PinState[x] == "1") {
                    xilent.println("<a href=\"/" + pinname[x] + ":0\"><button class=\"button button\">-1-</button></a>");
                    if (high_low_invert == true) xilent.println(" Çıkış [0]");
                  }
                }



                if (pinmode[x] == "OUT" && pinsignaltype[x] == "PWM") {



                  /*
const char* cvv1 = R"literal(<div class='slidecontainer'><form method='get' id='form)literal";

const char* cvv11 = R"literalcvv11(' action='/)literalcvv11";

const char* cvv2 = R"literal1(<input type='range' min=')literal1";


const char* minva1 = R"literal2(' max=')literal2";

const char* maxva1 = R"literal3(' value=')literal3";



                  //<button class="button butayr"> > </button>
const char* cvv3 = R"literal4(' class='slider' name='pwm' id='myRange)literal4";

const char* cvv31 = R"literal31('>
  <span id='demo)literal31";

const char* cvv32 = R"literalcvv32('></span>

  <input type='submit' style='width:50px;' value='>'></form></div>


<script>
var slider = document.getElementById('myRange)literalcvv32";

const char* cvv33 = R"literalcvv33(');
var output)literalcvv33";


const char* out331 = R"literalout331( = document.getElementById('demo)literalout331";

const char* cvv34 = R"literalcvv34(');
output)literalcvv34";

const char* out333 = R"literalout333(.innerHTML = slider.value;

slider.oninput = function() {
  output)literalout333";


const char* out332 = R"literalout332(.innerHTML = this.value;
}
slider.onmouseup = function () {
 document.getElementById("form)literalout332";

const char* cvv35 = R"literalcvv35(").submit();
}
</script>
)literalcvv35";

                  String cv1 = String(cvv1);
                  String cv11 = String(cvv11);
                  String cv2 = String(cvv2);
                  String minv = String(minva1);
                  String maxv = String(maxva1);
                  String cv3 = String(cvv3);
                  String cv31 = String(cvv31);
                  String cv32 = String(cvv32);
                  String cv33 = String(cvv33);
                  String out31 = String(out331);
                  String cv34 = String(cvv34);
                  String out33 = String(out333);
                  String out32 = String(out332);
                  String cv35 = String(cvv35);
                  //Serial.print("pinmaxvalue[x] :");Serial.print(pinmaxvalue[x]);

                  xilent.println("<br><br>" + cv1 + pinname[x] + cv11 + pinname[x] + "'>" + pinlabel[x] + " [" + pinname[x] + "]" + cv2 + "" + pinminvalue[x] + minv + pinmaxvalue[x] + maxv + PinState[x] + cv3 + pinname[x] + cv31 + pinname[x] + cv32 + pinname[x] + cv33 + pinname[x] + out31 + pinname[x] + cv34 + pinname[x] + out33 + pinname[x] + out32 + pinname[x] + cv35);
*/


                  const char* liter = R"lite1(<div class='slidecontainer'>
  <form method='get' id='formĞname' action='/Ğname'>Ğlabel [Ğname]<input type='range' min='Ğmin' max='Ğmax' value='Ğstate' class='slider' name='pwm' id='myRangeĞname'>
  
  <span id='demoĞname'></span>
  
  <input type='submit' style='width:50px;' value='>'>
  </form></div>

<script>

var sliderĞname = document.getElementById('myRangeĞname');
var outputĞname = document.getElementById('demoĞname');

outputĞname.innerHTML = sliderĞname.value;

sliderĞname.oninput = function() {
  outputĞname.innerHTML = this.value;
  }
sliderĞname.onmouseup = function () {
  document.getElementById("formĞname").submit();
  }
</script>
)lite1";

                  String dizgiorj = String(liter);

                  dizgiorj.replace("Ğname", pinname[x]);
                  dizgiorj.replace("Ğlabel", pinlabel[x]);
                  dizgiorj.replace("Ğmin", pinminvalue[x]);
                  dizgiorj.replace("Ğmax", pinmaxvalue[x]);
                  dizgiorj.replace("Ğstate", PinState[x]);

                  //Serial.print(dizgiorj);Serial.println();
                  xilent.println("<label style='font-size: 12px;'> min: " + pinminvalue[x] + "-max: " + pinmaxvalue[x] + "</label><br>");
                  xilent.println(dizgiorj);

                  //xilent.println("<br><br>" + cv1 + pinname[x] + cv11 + pinname[x] + "'>" + pinlabel[x] + " [" + pinname[x] + "]" + cv2 + "" + pinminvalue[x] + minv + pinmaxvalue[x] + maxv + PinState[x] + cv3 + pinname[x] + cv31 + pinname[x] + cv32 + pinname[x] + cv33 + pinname[x] + out31 + pinname[x] + cv34 + pinname[x] + out33 + pinname[x] + out32 + pinname[x] + cv35);

                  /*
if(gonderdimbekleint>0) 
{
xilent.println("<br><label style='font-size: 12px;'> min: " + pinminvalue[x] +"          -         max: " + pinmaxvalue[x] + "</label><br>");
xilent.println(pinlabel[x] + " ["+ pinname[x] +"] =" + PinState[x] +"<br> ");
}
else
{
xilent.println("<label style='font-size: 12px;'> min: " + pinminvalue[x] +"          -         max: " + pinmaxvalue[x] + "</label>");
xilent.println("<form method='get' id='form" + pinname[x] + "' action='/" + pinname[x] + "'>"+ pinlabel[x] + " ["+ pinname[x] +"] <input name='pwm' length=4 style=\"width:70px;\" value='" + PinState[x] + "'> <input type='submit' style='width:50px;' value='>'></form>");
}
*/


                  //xilent.println( buraya slider formu yapacağım)

                  Outpwm(pinname[x], PinState[x].toInt());
                }




                if (pinmode[x] == "OUT" && pinsignaltype[x] == "SER") {

                  xilent.println("<br><br><form method='get' action='/" + pinname[x] + "'><label> " + pinlabel[x] + " [" + pinname[x] + "] </label><input name='ser' length=4 value=");
                  xilent.println(PinState[x]);
                  xilent.println("><input type='submit'>");
                  xilent.println("</form>");

                  myservo[x].write(PinState[x].toInt());
                  Serial.print("myservo[x].write(PinState[x].toInt());     :");
                  Serial.println(PinState[x].toInt());
                }


                const char* angg1 = R"literal5(
// html düz yapıştır
)literal5";


                const char* angg2 = R"literal7(
// html düz yapıştır
)literal7";

                String ang1 = String(angg1);
                String ang2 = String(angg2);

                if (pinmode[x] == "INP" && pinsignaltype[x] == "ANG") {
                  pinMode(Pin[x], INPUT);
                  PinState[x] = analogRead(Pin[x]);
                  xilent.println("<br>" + pinlabel[x] + " [" + pinname[x] + "]= " + PinState[x] + "<br>");
                }

                if (pinmode[x] == "INP" && pinsignaltype[x] == "DIG") {
                  pinMode(Pin[x], INPUT);
                  PinState[x] = digitalRead(Pin[x]);
                  xilent.println("<br>" + pinlabel[x] + " [" + pinname[x] + "]= " + PinState[x] + "<br>");
                }

                if (pinmode[x] == "INP" && pinsignaltype[x].indexOf("DHT") == 0) {
                  String t;
                  String h;
                  if (PinState[x].indexOf("t") > -1) {
                    String pstmp = PinState[x];
                    t = pstmp.substring(1, pstmp.indexOf("h"));
                    pstmp = pstmp.substring(pstmp.indexOf("h") + 1, pstmp.length());
                    h = pstmp;
                  }
                  xilent.println("<br>" + pinlabel[x] + " [" + pinname[x] + "]= " + t + " C° " + h + "0% <br>");
                }

                if (pinmode[x] == "INP" && pinsignaltype[x] == "HCE") {
                  xilent.println("<br>" + pinlabel[x] + " [" + pinname[x] + "]= " + PinState[x] + "cm.<br>");
                }
              }
            }

            xilent.println("<hr style=\"height:5px;border-width:1;color:black;background-color:black\">");
            xilent.println("<div align=\"left\">");
            xilent.println("<table><td style=\"border:2px solid black;width:400p; align:center; \">");
            if (high_low_invert == true) xilent.println("<label style='font-size: 10px;'>PIN_INVERT komutu çıkışı ters çalıştırılıyor.</label><br>");
            if (progmsg != "") xilent.println("<label style='font-size: 10px;'>" + progmsg + "</label><br>");
            if (errorlog != "") xilent.println("<br>Hata: " + errorlog + "<br>");
            xilent.println("</td></table></div><p><a href=\"/Menu1\"><button class=\"button butayr\">Ayarlar</button></a></p>");

            // The HTTP response ends with another blank line
            xilent.println("<br>hcsrloopvar:" + (String)hcsrloopvar + "<br>");
            xilent.println("<br>habp:" + (String)habp + "<br>");
            xilent.println("coded by " + creator + ". ESP kontrol (v4");
            xilent.println("<label style='font-size:1px;'>" + WiFi.macAddress() + "</label>04.01.2026)<br><br>");
            //String butonactcol = "#d1ca03";
            //String butonpascol = "#A3A3A3";
            //String butonayrcol = "#20d3c8";
            //String butonpbgcol = "#ffb12a";
            xilent.println("<div align=\"left\">");
            xilent.println("<form method='get' action='/butonactcol'><label>Acik konumundaki buton rengi. #</label><input name='is' length=6 style=\"width:50px\" value=");
            xilent.println(butonactcol);
            xilent.println("><input type='submit'>");
            xilent.println("d1ca03</form><br>");


            xilent.println("<form method='get' action='/butonpascol'><label>Kapalı konumunda buton rengi  #</label><input name='is' length=6 style=\"width:50px\" value=");
            xilent.println(butonpascol);
            xilent.println("><input type='submit'>");
            xilent.println("A3A3A3</form><br>");

            xilent.println("<form method='get' action='/butonayrcol'><label>Ayar, pwm gönder buton rengi.  #</label><input name='is' length=6 style=\"width:50px\" value=");
            xilent.println(butonayrcol);
            xilent.println("><input type='submit'>");
            xilent.println("20d3c8</form><br>");

            xilent.println("<form method='get' action='/butonpbgcol'><label>Bu sayfanin arka planının rengi #</label><input name='is' length=6 style=\"width:50px\" value=");
            xilent.println(butonpbgcol);
            //Serial.print("butonpbgcol:");
            //Serial.println(butonpbgcol);
            xilent.println("><input type='submit'>");
            xilent.println("ffb12a</form></td>");
            /*                        butonactcol butonpascol butonayrcol butonpbgcol
            xilent.println(".button { background-color: #d1ca03; border: none; color: white; padding: 10px 10px;text-decoration: none; font-size: 10px; margin: 1px; cursor: pointer;}");
            xilent.println(".butoff {background-color: #A3A3A3; border: none; color: white; padding: 10px 10px;text-decoration: none; font-size: 10px; margin: 1px; cursor: pointer;}");
            xilent.println(".butayr {background-color: #20d3c8; border: none; color: black; padding: 10px 10px;text-decoration: none; font-size: 10px; margin: 1px; cursor: pointer;}");
            xilent.println("</style>");
            
            xilent.println("<style>body {background-color: #ffb12a;} </style>");  //darkblue, lightblue, #b0b0b0 gibi
    
*/


            const char* ocz = R"ocz(<script>var uri = window.location.toString();
if (uri.indexOf("?") > 0) {
    var clean_uri = uri.substring(0, uri.indexOf("?"));
    window.history.replaceState({}, document.title, clean_uri);
}</script>)ocz";

            String ocz2 = String(ocz);

            //xilent.println(ocz2);
            // url variable hidden url , url hide

            // menu0bitti



            xilent.println("</body></html>");
            xilent.println();

            //xilent.flush();
            //xilent.close();
            if (header.indexOf("/resetle") > -1) ESP.reset();
          }
          yield();
        }
      }
    }
  }
}

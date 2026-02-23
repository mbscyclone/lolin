void serin()
{ 
  if(Serial.available())
  {
        String sergel=Serial.readStringUntil('\n');
        Serial.println(sergel);



// ssid ve pass kısmı başladı ///////////////////////////////////////////////////

      if(sergel=="wifitara")
      {
        wifiscan();
      }

      if(sergel.indexOf("ssid?")==0)
      {
        Serial.println(sergel + " = " + ssid);
      }
      if(sergel.indexOf("pass?")==0)
      {
        Serial.println(sergel + " = " + pass);
      }

      if(sergel.indexOf("ssid=")==0)
      {
        ssid=sergel.substring(5,sergel.length());
      Serial.println(ssid + " ssid güncellendi. ssid şifresini girin pass=.....");
      }

      if(sergel.indexOf("pass=")==0)
      {
        pass=sergel.substring(5,sergel.length());
        Serial.println(pass + " pass guncellendi 'kaydet' ile kaydedin.");
      }

      if(sergel.indexOf("kaydet")==0)
      {
        dosyayazssidpass();
        Serial.println("kaydedildi. 'reset' ile resetleyin...");
      }

///////////////////////////////////////////////////////////// ssid pass kısmı bitti

// ismim kısmı başı ////////////////////////////////

      if(sergel.indexOf("ismim=")==0)
      {
        esphostname=sergel.substring(6,sergel.length());
        dosyayazmyssidname();
        Serial.println( "Cihaz ismi güncellendi.");
      }


/////////////////////////////////// ismim kısmı sonu




      if(sergel.indexOf("pl ")==0)
      {
        String mel=sergel.substring(sergel.indexOf("pl ")+3,sergel.length());
        play(mel);
      }



      if(sergel.indexOf("kacmp3")==0)
      {


      int fileCounts = 0;

          myDFPlayer.readFileCounts();
          fileCounts = myDFPlayer.readFileCountsInFolder(0);

          Serial.println(fileCounts);

            myDFPlayer.volume(24);  //Set volume value. From 0 to 30
            myDFPlayer.play(1);     //Play the first mp3
      }


///////////////////////////////////////////////////////////// firebase bitti
      if(sergel.indexOf("d=")==0)
      { String flnm=sergel.substring(sergel.indexOf("d=")+2,sergel.length());
        dosya = LittleFS.open(flnm, "r");
        Serial.println(flnm +"dosya içeriği");
        Serial.println(dosya.readString());
        dosya.close();
      }

      if(sergel.indexOf("habp0")>-1) 
      {
        habp = 0; dosyayazhabp();
        delay(100); ESP.reset();
      }

      if(sergel.indexOf("habp1")>-1) 
      {
        habp = 1; dosyayazhabp();
        delay(100); ESP.reset();
      }


      if(sergel.indexOf("htpcd")>-1) 
      {
        htpcldis = true;
      }
      
      if(sergel.indexOf("htpcl")>-1) 
      {
        htpcldis = false;
      }



/// yardım başı /////////////////////////////////////////////////////////

      if(sergel.length()<1 || sergel.indexOf("yardım")==0)
      {
            Serial.println("wifitara   - wifi taramak için");
            Serial.println("ssid=      - ssid ayarları başlatmak için.");
            Serial.println("ismim=     - Cihaza isim vermek için.");
            Serial.println("htserverip - Httpserver ip gösterir");
            Serial.println("habpX      - X=0 kapali 1 MQTT 2 Firebase  resetler");
            Serial.println("htpcldis   - htpclye git kapali htpcldis=T");
            Serial.println("htpcl      - htpclye git açık htpcldis=F");
            Serial.println("durum      - durumları listeler");
            Serial.println("reset      - Cihazı resetler. ");
      }
  

      if(sergel.indexOf("durum")==0)
      {
//            if(Firebase.ready())Serial.println("Firebase durumu: Bağlı" );
//            if(!Firebase.ready())Serial.println("Firebase durumu: Bağlı değil" );
            Serial.println("reset  - Cihazı resetler. ");
            Serial.println(httpserver.status());
      }

      if(sergel.indexOf("htserverip")==0)
      {
            Serial.println("http 8080 Serveri : "+ htServerip);
      }


      if(sergel.indexOf("dosyasil:")==0)
      {
                String ds=sergel.substring(sergel.indexOf("il:")+3,sergel.length());
                dosya.close();
                LittleFS.remove(ds);
                Serial.println(ds + " dosyası silindi.");
      }

      if(sergel.indexOf("dosyaoku:")==0)
      {
                String ds=sergel.substring(sergel.indexOf("ku:")+3,sergel.length());
                dosya.close();
                dosya = LittleFS.open(ds, "r");
                if (dosya) {
                String en = dosya.readString();
                Serial.println(ds + "dosya içeriği"); Serial.println(dosya);
                }else{
                Serial.println(ds + " dosyası yok ");
                }
                dosya.close();
      }

      if(sergel.indexOf("mac")==0)
      {
        Serial.print("Mac:");Serial.println(Serial.println(WiFi.macAddress()));
      }
//////////////////////////////////////////////////////////yardım bitti

      if(sergel.indexOf("resetle")==0)ESP.restart();

  }
}
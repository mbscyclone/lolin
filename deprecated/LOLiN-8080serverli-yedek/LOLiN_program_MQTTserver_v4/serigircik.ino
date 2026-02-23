
void serin()
{ return;
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




/// yardım başı /////////////////////////////////////////////////////////

      if(sergel.length()<1 || sergel.indexOf("yardım")>-1)
      {
            Serial.println("wifitara - wifi taramak için");
            Serial.println("ssid=    - ssid ayarları başlatmak için.");
            Serial.println("ismim=   - Cihaza isim vermek için.");
            Serial.println("durum=   - durumları listeler");
            Serial.println("reset  - Cihazı resetler. ");
      }
  

      if(sergel.indexOf("durum")>-1)
      {
            Serial.println("firebase Açık  : "+ String(fben));
//            if(Firebase.ready())Serial.println("Firebase durumu: Bağlı" );
//            if(!Firebase.ready())Serial.println("Firebase durumu: Bağlı değil" );
            Serial.println("reset  - Cihazı resetler. ");
            Serial.println(httpserver.status());
      }



//////////////////////////////////////////////////////////yardım bitti





      if(sergel.indexOf("resetle")==0)ESP.restart();

  }
}
/*
void dosyaOkuSERVERusers(){

  dosya.close();
  dosya = LittleFS.open("/SERVERusers.txt", "r");
  if (dosya) {
          String geciciSERVERusers = dosya.readString();
          geciciSERVERusers = geciciSERVERusers.substring(0, geciciSERVERusers.length() - 1);
          SERVERusers = geciciSERVERusers;
          Serial.println("geciciSERVERusers v ");
          Serial.println(geciciSERVERusers);
          Serial.print("SERVERusers=================>");
          Serial.print(SERVERusers);
          Serial.println("<");
          dosya.close();
        SERVERkullanici=SERVERusers;


          for (int j=0;j<SERVERkullanici.length();j++){
              Kullaniciadi[j] = SERVERkullanici.substring(0,SERVERkullanici.indexOf("|"));
              SERVERkullanici= SERVERkullanici.substring(SERVERkullanici.indexOf("|")+1,SERVERkullanici.length());

              Kullanicisifresi[j] = SERVERkullanici.substring(0,SERVERkullanici.indexOf("\n"));
              SERVERkullanici= SERVERkullanici.substring(SERVERkullanici.indexOf("\n")+1,SERVERkullanici.length());

              if(SERVERkullanici.length()<1) break;

              Serial.println(Kullaniciadi[j]+"|"+ Kullanicisifresi[j]);

          }
      }
}


void dosyaYazSERVERusers(){
  dosya.close();
  LittleFS.remove("/SERVERusers.txt");
  Serial.println(SERVERusers);
  if(SERVERusers.indexOf(SERVERusers.substring(SERVERusers.length()- 5, 5)),"%0"<0)SERVERusers;
  dosya = LittleFS.open("/SERVERusers.txt", "w+");
  SERVERusers=Karakterduzeltfunc(SERVERusers);
  dosya.println(SERVERusers);
  dosya.close();
  dosyaOkuSERVERusers();

  //ESP.reset();
}
*/

void dosyaokussidpass() {

  //if (digitalRead(FactoryDefault) == HIGH) {
    // cleareprom();
  //}

  dosya = LittleFS.open("/ssidpass.txt", "r");
  if (dosya) {
    // dosya başarı ile açıldı;
    String ssidoc = dosya.readStringUntil('\n');
    ssid = ssidoc.substring(0, ssidoc.length() - 1);
    //Serial.println(ssid);

    String passoc = dosya.readStringUntil('\n');
    pass = passoc.substring(0, passoc.length() - 1);
    //Serial.println(pass);

    dosya.close();
    //Serial.println("read bitti");
  }else{ssid="Zyxel";pass="bebedede14";}
  if(ssid.length()<2){ssid="Zyxel";pass="bebedede14";}
}



void dosyayazssidpass()
{
                  reConnectsayac=millis();
                dosya.close();
                LittleFS.remove("/ssidpass.txt");
                dosya = LittleFS.open("/ssidpass.txt", "w+");
                if (dosya) {
                  dosya.println(ssid);
                  dosya.println(pass);
                  dosya.close();
                  Serial.println("Write bitti");
                }
                dosya.close();

}


String myssidyazilimi = "";
void dosyayazmyssidname() {
  dosya.close();
  LittleFS.remove("/myssidname.txt");
  dosya = LittleFS.open("/myssidname.txt", "w+");
  if(dosya){
  dosya.println(myssidyazilimi);
  Serial.println(myssidyazilimi);
  dosya.close();
  dosyaokumyssidname();
  WiFi.hostname(esphostname);
  WiFi.softAP(esphostname, "12345678");
  }
//  fbchzkaydial();
}



void dosyaokumyssidname() {
  //   я
  int yazili = 0;
  myssidyazilimi = "";
  dosya.close();
  dosya = LittleFS.open("/myssidname.txt", "r");

  if (dosya) {
    String gecicimyssidname = dosya.readStringUntil('\n');
    gecicimyssidname = gecicimyssidname.substring(0, gecicimyssidname.length() - 1);
    Serial.println(gecicimyssidname);
    myssidyazilimi = gecicimyssidname;
    yazili = gecicimyssidname.length();
    dosya.close();
    if (yazili < 1) { myssidyazilimi = "v4"; }

    esphostname = esphostnameOnek + "-" + myssidyazilimi;
  
  }
}



void telegramtokendosyaoku() {

  //if (digitalRead(FactoryDefault) == HIGH) {
    // cleareprom();
  //}

  dosya = LittleFS.open("/telegramdata.txt", "r");
  if (dosya) {
    // dosya başarı ile açıldı;
    String telegram_botTokentmp = dosya.readStringUntil('\n');
    telegram_botToken = telegram_botTokentmp.substring(0, telegram_botTokentmp.length() - 1);

    String telegram_chatIDtmp = dosya.readStringUntil('\n');
    telegram_chatID = telegram_chatIDtmp.substring(0, telegram_chatIDtmp.length() - 1);
    telegram_hazir=true;
    dosya.close();
    Serial.println("read bitti");
    Serial.println(telegram_chatID);
    Serial.println(telegram_botToken);

  }else{telegram_hazir=false;}
  if(telegram_botToken.length()<2){telegram_hazir=false;}
}



void telegramtokendosyayaz()
{
                dosya.close();
                LittleFS.remove("/telegramdata.txt");
                dosya = LittleFS.open("/telegramdata.txt", "w+");
                if (dosya) {
                  dosya.println(telegram_botToken);
                  dosya.println(telegram_chatID);
                  dosya.close();
                  Serial.println("telegram Write bitti");
                }
                dosya.close();
                telegramtokendosyaoku();
}





String pirdevredemi = "";
void dosyayazpirdevrede() {
  dosya.close();
  LittleFS.remove("/pirdevrede.txt");
  dosya = LittleFS.open("/pirdevrede.txt", "w+");
  if(dosya){
  dosya.println(pirdevrede);
  Serial.println(pirdevrede);
  dosya.close();
  }
}



void dosyaokupirdevrede() {
  //   я
  int yazili = 0;
  pirdevrede = "";
  dosya.close();
  dosya = LittleFS.open("/pirdevrede.txt", "r");

  if (dosya) {
    String pirdevredemi = dosya.readStringUntil('\n');
    pirdevredemi = pirdevredemi.substring(0, pirdevredemi.length() - 1);
    Serial.println(pirdevredemi);
    pirdevrede = pirdevredemi;
    dosya.close();
  }
}



void dosyaokufbyol()
{
                dosya.close();
                dosya = LittleFS.open("/fbyol.txt", "r");
                if (dosya) {
                YOL = dosya.readStringUntil('\n');
                YOL= YOL.substring(0,YOL.length()-1);
                dosya.close();
                }
}

void dosyayazfbyol()
{
                  reConnectsayac=0;
                dosya.close();
                LittleFS.remove("/fbyol.txt");
                dosya = LittleFS.open("/fbyol.txt", "w+");
                if (dosya) {
                  dosya.println(YOL);
                  dosya.close();
                  dosyaokufbyol();
                }
}

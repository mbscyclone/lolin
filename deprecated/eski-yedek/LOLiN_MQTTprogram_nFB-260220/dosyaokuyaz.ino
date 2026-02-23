void htserveroku(){
                 dosya.close();
                dosya = LittleFS.open("/httpserverip.txt", "r");
                if (dosya) {
                String sip = dosya.readStringUntil('\n');
                htServerip = sip.substring(0,sip.length()-1);
                //Serial.print("fben:");
                //Serial.println(fben);
                }
                dosya.close();
}

void htserverkaydet(String hServerip)
{
                dosya.close();
                LittleFS.remove("/httpserverip.txt");
                dosya = LittleFS.open("/httpserverip.txt", "w+");
                if (dosya) {
                  dosya.println(String(hServerip));
                }
                dosya.close();
                htserveroku();
}

void mqttipoku(){
                 dosya.close();
                dosya = LittleFS.open("/mqttip.txt", "r");
                if (dosya) {
                String mip = dosya.readStringUntil('\n');
                MQTTip = mip.substring(0,mip.length()-1);
                //Serial.print("fben:");
                //Serial.println(fben);
                }
                dosya.close();
}

void mqttipkaydet(String MQTTip)
{
                dosya.close();
                LittleFS.remove("/mqttip.txt");
                dosya = LittleFS.open("/mqttip.txt", "w+");
                if (dosya) {
                  dosya.println(String(MQTTip));
                   if(MQTTip.length()>0)mqttconnectsayac=0;
                }
                dosya.close();
                mqttipoku();
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
                  delay(100);
                  ESP.reset();
                }
                dosya.close();

}

void dosyaokussidpass() {
  dosya.close();
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
  }
}

String myssidyazilimi = "";
void dosyayazmyssidname() {
                  reConnectsayac=0;
  dosya.close();
  LittleFS.remove("/myssidname.txt");
  dosya = LittleFS.open("/myssidname.txt", "w+");
  dosya.println(myssidyazilimi);
Serial.println(myssidyazilimi);
  dosya.close();
  dosyaokumyssidname();
  WiFi.hostname(esphostname);
  WiFi.softAP(esphostname, "12345678");
//  fbchzkaydial();
    fbdataguncelle();
}


void dosyaYazusers()
{
                dosya.close();
                LittleFS.remove("/usrnamepass.txt");
                dosya = LittleFS.open("/usrnamepass.txt", "w+");
                if (dosya) {
                  dosya.println(unme);
                  dosya.println(pwrd);
                  dosya.close();
                  Serial.println("Write bitti");
                }
                dosya.close();

}

void dosyaOkuusers() {

  dosya = LittleFS.open("/usrnamepass.txt", "r");
  if (dosya) {
    // dosya başarı ile açıldı;

    String unmetmp = dosya.readStringUntil('\n');

    for(int sil=0;sil<4;sil++){
    if(unmetmp.indexOf('\r')==0) unmetmp=unmetmp.substring(1,unmetmp.length()); 
    if(unmetmp.indexOf('\n')==0) unmetmp=unmetmp.substring(1,unmetmp.length()); 
    if(unmetmp.indexOf('\r')>2) unmetmp=unmetmp.substring(0,unmetmp.length()-1);
    if(unmetmp.indexOf('\n')>2) unmetmp=unmetmp.substring(0,unmetmp.length()-1);
    }
    unme=unmetmp;
    String pwrdtmp = dosya.readStringUntil('\n');
    for(int sil=0;sil<4;sil++){
    if(pwrdtmp.indexOf('\r')==0) pwrdtmp=pwrdtmp.substring(1,pwrdtmp.length()); 
    if(pwrdtmp.indexOf('\n')==0) pwrdtmp=pwrdtmp.substring(1,pwrdtmp.length());
    if(pwrdtmp.indexOf('\r')>2) pwrdtmp=pwrdtmp.substring(0,pwrdtmp.length()-1);
    if(pwrdtmp.indexOf('\n')>2) pwrdtmp=pwrdtmp.substring(0,pwrdtmp.length()-1);
    }

    pwrd=pwrdtmp;
    dosya.close();
    //Serial.println("read bitti");
  }else
  {
    unme = "admin";
    pwrd = "1111";
  dosyaYazusers();

  }
  dosya.close();
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
    if (yazili < 1) { myssidyazilimi = "v3"; }
         esphostname = "" + myssidyazilimi;
  }
}



void dosyaokufben()
{
                dosya.close();
                dosya = LittleFS.open("/fben.txt", "r");
                if (dosya) {
                String en = dosya.readStringUntil('\n');
                en= en.substring(0,en.length()-1);
                fben = en.toInt();
                //Serial.print("fben:");
                //Serial.println(fben);
                }
                dosya.close();
}

void dosyayazfben()
{
                  reConnectsayac=0;
                dosya.close();
                LittleFS.remove("/fben.txt");
                dosya = LittleFS.open("/fben.txt", "w+");
                if (dosya) {
                  dosya.println(String(fben));
                }
                dosya.close();
                dosyaokufben();
                if(fben==1)connectfb();
                delay(100);
                
}

void dosyaokuhabp()
{
                dosya.close();
                dosya = LittleFS.open("/habp.txt", "r");
                if (dosya) {
                String hab = dosya.readStringUntil('\n');
                hab = hab.substring(0,hab.length()-1);
                habp = hab.toInt();
                ehabp = habp;
                //Serial.print("fben:");
                //Serial.println(fben);
                }else habp=0;
                dosya.close();
}

void dosyayazhabp()
{
                dosya.close();
                LittleFS.remove("/habp.txt");
                dosya = LittleFS.open("/habp.txt", "w+");
                if (dosya) {
                  dosya.println(String(habp));
                }
                dosya.close();
}


/*
void dosyaokupindurum()
{
                pindurumrecyap=false;
                dosya.close();
                dosya = LittleFS.open("/pindurum.txt", "r");
                if (dosya) {
                String en = dosya.readStringUntil('\n');
                pindurumrec = en.substring(0,en.length()-1);
                }
                dosya.close();
                Serial.print("pindurumrec "); Serial.println(pindurumrec);

if(fben==0){
                String pindurumrectmp = pindurumrec;                
                for (int y=0;y<pinsayisi;y++)
                {
                  if(pindurumrectmp.length()<2) break;
                  String pn=pindurumrectmp.substring(0,pindurumrectmp.indexOf(":"));
                  String ps=pindurumrectmp.substring(pindurumrectmp.indexOf(":")+1,pindurumrectmp.indexOf(","));
                  pindurumrectmp=pindurumrectmp.substring(pindurumrectmp.indexOf(",")+1,pindurumrectmp.length());
                  //Serial.println(pn);
                  //Serial.println("pindurumrectmp : " + pindurumrectmp);
                  for (int x=0;x<pinsayisi;x++)
                  {
                    if(pn==pinname[x]){
                      PinState[x]=ps;ePinState[x]=ps;
                    //  Serial.print("pinname ");Serial.print(pn);Serial.print(" pinstate ");Serial.println(ps);
                    break;
                    }
                  }
                }
            }
}




void dosyayazpindurum()
{

                String pindurumrec="";
                pindurumrecyap=false;                
                for (int x=0;x<pinsayisi;x++)
                {
                  if(pinmode[x]=="OUT")
                  {
                    pindurumrec+= pinname[x]+":"+PinState[x]+",";
                  }
                }
              
                dosya.close();
                LittleFS.remove("/pindurum.txt");
                dosya = LittleFS.open("/pindurum.txt", "w+");
                if (dosya) {
                  dosya.println(pindurumrec);
                }
                dosya.close();
                

if(fben==0){
                String pindurumrectmp = pindurumrec;                
                for (int y=0;y<pinsayisi;y++)
                {
                  if(pindurumrectmp.length()<2) break;
                  String pn=pindurumrectmp.substring(0,pindurumrectmp.indexOf(":"));
                  String ps=pindurumrectmp.substring(pindurumrectmp.indexOf(":")+1,pindurumrectmp.indexOf(","));
                  pindurumrectmp=pindurumrectmp.substring(pindurumrectmp.indexOf(",")+1,pindurumrectmp.length());
                  //Serial.println(pn);
                  //Serial.println("pindurumrectmp : " + pindurumrectmp);
                  for (int x=0;x<pinsayisi;x++)
                  {
                    if(pn==pinname[x]){
                      PinState[x]=ps;ePinState[x]=ps;
                    //  Serial.print("pinname ");Serial.print(pn);Serial.print(" pinstate ");Serial.println(ps);
                    break;
                    }
                  }
                }
            }



}
*/






void dosyaokufburl()
{
                dosya.close();
                dosya = LittleFS.open("/fburl.txt", "r");
                if (dosya) {
                DATABASE_URL = dosya.readStringUntil('\n');
                DATABASE_URL= DATABASE_URL.substring(0,DATABASE_URL.length()-1);
                dosya.close();
                }

}

void dosyayazfburl()
{
                  reConnectsayac=0;
                dosya.close();
                LittleFS.remove("/fburl.txt");
                dosya = LittleFS.open("/fburl.txt", "w+");
                if (dosya) {
                  if(!DATABASE_URL.endsWith("/"))DATABASE_URL+="/";
                  dosya.println(DATABASE_URL);
                  dosya.close();
                  dosyaokufburl();
                }
}


void dosyaokufbapi()
{
  dosya.close();
  dosya = LittleFS.open("/fbapi.txt", "r");
  if (dosya) {
    // dosya başarı ile açıldı;
    API_KEY = dosya.readStringUntil('\n');
    API_KEY = API_KEY.substring(0,API_KEY.length()-1);
    dosya.close();
    }
}               


void dosyayazfbapi()
{
                  reConnectsayac=0;
                dosya.close();
                LittleFS.remove("/fbapi.txt");

                dosya = LittleFS.open("/fbapi.txt", "w+");
                if (dosya) {
                  dosya.println(API_KEY);
                dosya.close();
                }
    //Serial.print("fbapi yazılıyo");Serial.println(fbapi);

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

void dosyaokufbusername()
{
                dosya.close();
                dosya = LittleFS.open("/fbusername.txt", "r");
                if (dosya) {
                USER_EMAIL = dosya.readStringUntil('\n');
                USER_EMAIL= USER_EMAIL.substring(0,USER_EMAIL.length()-1);
                dosya.close();
                }

}

void dosyayazfbusername()
{
                  reConnectsayac=0;
                dosya.close();
                LittleFS.remove("/fbusername.txt");
                dosya = LittleFS.open("/fbusername.txt", "w+");
                if (dosya) {
                  USER_EMAIL=USER_EMAIL1+"@"+USER_EMAIL2;
                  dosya.println(USER_EMAIL);
                  dosya.close();
                  dosyaokufburl();
                }
}


void dosyaokufbuserpass()
{
                dosya.close();
                dosya = LittleFS.open("/fbuserpass.txt", "r");
                if (dosya) {
                USER_PASSWORD = dosya.readStringUntil('\n');
                USER_PASSWORD= USER_PASSWORD.substring(0,USER_PASSWORD.length()-1);
                dosya.close();
                }

}

void dosyayazfbuserpass()
{
                  reConnectsayac=0;
                dosya.close();
                LittleFS.remove("/fbuserpass.txt");
                dosya = LittleFS.open("/fbuserpass.txt", "w+");
                if (dosya) {
                  dosya.println(USER_PASSWORD);
                  dosya.close();
                  dosyaokufburl();
                }
}


String butonactcol = "d1ca03";
String butonpascol = "A3A3A3";
String butonayrcol = "20d3c8";
String butonpbgcol = "ffb12a";


void butonactcoloku() {
  dosya.close();
  dosya = LittleFS.open("/butonactcol.txt", "r");
  if (dosya) {
    String butonactcol1 = dosya.readStringUntil('\n');
    butonactcol = butonactcol1.substring(0, butonactcol1.length() - 1);
    //Serial.println(butonactcol);
    dosya.close();
  } else {
    butonactcol = "d1ca03";
  }
}

void butonactcolyaz() {
  dosya.close();
  LittleFS.remove("/butonactcol.txt");
  //Serial.println(butonactcol);
  dosya = LittleFS.open("/butonactcol.txt", "w+");
  dosya.println(butonactcol);
  dosya.close();
  butonactcoloku();
}

void butonpascoloku() {
  dosya.close();
  dosya = LittleFS.open("/butonpascol.txt", "r");
  if (dosya) {
    String butonpascol1 = dosya.readStringUntil('\n');
    butonpascol = butonpascol1.substring(0, butonpascol1.length() - 1);
    //Serial.println(butonpascol);
    dosya.close();
  } else {
    butonpascol = "A3A3A3";
  }
}

void butonpascolyaz() {
  dosya.close();
  LittleFS.remove("/butonpascol.txt");
  //Serial.println(butonpascol);
  dosya = LittleFS.open("/butonpascol.txt", "w+");
  dosya.println(butonpascol);
  dosya.close();
  butonpascoloku();
}

void butonayrcoloku() {
  dosya.close();
  dosya = LittleFS.open("/butonayrcol.txt", "r");
  if (dosya) {
    String butonayrcol1 = dosya.readStringUntil('\n');
    butonayrcol = butonayrcol1.substring(0, butonayrcol1.length() - 1);
    //Serial.println(butonayrcol);
    dosya.close();
  } else {
    butonayrcol = "20d3c8";
  }
}

void butonayrcolyaz() {
  dosya.close();
  LittleFS.remove("/butonayrcol.txt");
  //Serial.println(butonayrcol);
  dosya = LittleFS.open("/butonayrcol.txt", "w+");
  dosya.println(butonayrcol);
  dosya.close();
  butonayrcoloku();
}

void butonpbgcoloku() {
  dosya.close();
  dosya = LittleFS.open("/butonpbgcol.txt", "r");
  if (dosya) {
    String butonpbgcol1 = dosya.readStringUntil('\n');
    butonpbgcol = butonpbgcol1.substring(0, butonpbgcol1.length() - 1);
    //Serial.print("butonpbgcol:"); Serial.println(butonpbgcol);
    dosya.close();
  } else {
    butonpbgcol = "ffb12a";
  }
}

void butonpbgcolyaz() {
  dosya.close();
  LittleFS.remove("/butonpbgcol.txt");
  //Serial.println(butonpbgcol);
  dosya = LittleFS.open("/butonpbgcol.txt", "w+");
  dosya.println(butonpbgcol);
  dosya.close();
  butonpbgcoloku();
}


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









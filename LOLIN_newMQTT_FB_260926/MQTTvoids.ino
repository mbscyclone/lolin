
///// MQTT İŞLEMLERİ BAŞLANGICI /////////////////////////
String mqgonderen;
String mdegisenler;
String mdegisen;

void MQTTConnect() {

  if (mqttconnectsayac == 0) {
    mqtterror=true;
    //dosyaOkuusers();
    //dosyaOkuMQTTip();
    const char* ipAdres = MQTTip.c_str();
    mqttclient.begin(ipAdres, mqttnet);
    String capt = String(random(1000, 9999));
    String Client_IDm = esphostname +"-"+ capt;
    const char* Client_IDconstchar = Client_IDm.c_str();
    mqttclient.connect(Client_IDconstchar, "public", "public");
    mqttclient.onMessage(messageReceived);
    Serial.println("\nTry connect! " + String(ipAdres));
    mqttconnectsayac = 1;
  }

  if (mqttconnectsayac>0 && mqttconnectsayac<5001)
  {
    mqttconnectsayac += 1;
    if(mqttconnectsayac % 1000 == 0) Serial.println("*");
     if(mqttconnectsayac>=5000){mqtterror=true;}
  }

  if (mqttclient.connected() == true) {
    mqttconnectsayac = 0;
    mqtterror=false;
    Serial.println("\nconnected!");
    mqttclient.subscribe("/"+YOL+"/#");
    // client.unsubscribe("/hello");
    mqttconnectsayac = 0;
    //String pat= "/"+YOL+"/#";
    //String msghello = "hello:" + esphostname; 
    //mqttsend(pat,msghello);
  }

}

String Gelenmsg;
String eGelenMesaj = "";
String Gelentopic;
String eTopic;
String ePayload;
String publishmesaj;


void messageReceived(String& topic, String& payload) {
  Serial.println("incoming: " + topic + " - " + payload);

  if (payload.indexOf("!") == 0) return;
  //if (payload==mqsenddataold) return;

  Gelenmsg = payload;
  //Serial.println(Gelentopic);
  //Serial.println(Gelenmsg);
  Gelentopic = topic;

  //for(int v=1;v<51;v++){
  //if(Gelenmsg == degisenmq[v])return;
  //}



if(Gelenmsg.indexOf("FBWPA:")>-1 && habp==2) 
{
        String goesphostname="";
        goesphostname=Gelenmsg.substring(Gelenmsg.indexOf(YOL + "/")+YOL.length()+1,Gelenmsg.length());
        FBSERVER=goesphostname;
        String myol = "/" + YOL + "/"  + goesphostname;
      if(pinayar.length()>1){
        String FBPAY = "payM:" + WiFi.macAddress() +"<" + esphostname + ">"+mylocalip;
        /*
        for (int x = 0; x < pinsayisi + 1; x++) {
          if(pinname[x]!=""){
            FBPAY += pinname[x] + "|";
            FBPAY += pinmode[x] + "|";
            FBPAY += pinsignaltype[x] + "|";
            FBPAY += pinminvalue[x] + "|";
            FBPAY += pinval[x] + "|";
            FBPAY += PinState[x] + "|";
            FBPAY += pinmaxvalue[x] + "|";
            FBPAY += acilseviyesi[x] + "|";
            FBPAY += acildeger[x] + "|";
            FBPAY += pinlabel[x] + "\n";
          }
        }
        */
        mqttsend(myol,FBPAY);
      }
        
}

/*
      if(BenFbServerim)
        if(Gelenmsg.indexOf("FBPA:")>-1){
        String espname=Gelenmsg.substring(Gelenmsg.indexOf("FBPA:")+5,Gelenmsg.indexOf(">")-1);
        String espmacadres=Gelenmsg.substring(Gelenmsg.indexOf(">")+1,Gelenmsg.indexOf("<")-1);
        String esppay=Gelenmsg.substring(Gelenmsg.indexOf("<")+1,Gelenmsg.length());
        for(int mac=1;mac<21;mac++)
        {
          if(espmacadres==espma[mac])
          {
            espna[mac]=espname;
            esppa[mac]=esppay;
            
            Serial.print("Sayı=");Serial.println (mac);
            Serial.print("espname=");Serial.println (espna[mac]);
            
            break;
          }
          if(espma[mac]=="")
          {
            espna[mac]=espname;
            espma[mac]=espmacadres;
            esppa[mac]=esppay;

            Serial.print("Sayı=");Serial.println (mac);
            Serial.print("espname=");Serial.println (espna[mac]);
            Serial.print("mac=");Serial.println (espma[mac]);

            break;
          }
        }
      }
*/


  if(ACLilanciyim==true)
  {
    if(Gelenmsg.indexOf("ACIL:")>-1)
      {
        String goesphostname="";
        if(Gelenmsg.indexOf("ACIL:")>-1) goesphostname=Gelenmsg.substring(Gelenmsg.indexOf("<")+1,Gelenmsg.indexOf(">"));

        if(goesphostname!=esphostname){
        String myol = "/"+YOL + "/"  + goesphostname;
        mqttsend(myol, "/" + YOL+"/ALLDEV=ACL:"+ACL);
        }
        return;
      }
  }

  for(int v=1;v<6;v++){
  if(Gelentopic == mqyol[v]  && Gelenmsg == degisenmq[v])return;
  }


  if (Gelenmsg == ePayload && Gelentopic == eTopic) return;
  else {

    eTopic = Gelentopic;
    ePayload = Gelenmsg;

  Serial.println(Gelentopic);
  Serial.println(Gelenmsg);
  String tampon = Gelenmsg;
  
  if(Gelentopic.indexOf(esphostname)>-1 || Gelentopic.indexOf("ALLDEV")>-1)
Serial.println("\ntampon  indexofFBP> " + tampon.indexOf("FBP>"));
    if(tampon.indexOf("FBP>")==0)
    {
      tampon = tampon.substring(4,tampon.length());
      Serial.println("\ntampon" + tampon);
      for(int hh=0;hh<11;hh++)
      {
        String pnm1 = tampon.substring(0,tampon.indexOf(":"));
        String pns1 = tampon.substring(tampon.indexOf(":")+1,tampon.indexOf(","));
        tampon = tampon.substring(tampon.indexOf(",")+1,tampon.length());
        Serial.println("\npnm1:"+pnm1+ " pns1" + pns1);  
          for(int jj=0;jj<11;jj++){
                if(pnm1 == pinname[jj])
                { 
                      if(pns1!=PinState[jj] && PinState[jj]==ePinState[jj] && pinmode[jj]!="INP")
                      {
                        PinState[jj] = pns1;
                      }
                  break;
                }
          }
          if(tampon.length()<2)break;
      }
    }
    else mqttisyap(payload);
  }
  // Note: Do not use the client in the callback to publish, subscribe or
  // unsubscribe as it may cause deadlocks when other things arrive while
  // sending and receiving acknowledgments. Instead, change a global variable,
  // or push to a queue and handle it in the lo op after calling `client.lo op()`.



  //publishmesaj = "";
  //publishmesaj = "ĞÇÇ<- [" + esphostname + "!]\n" + "mylocalip";
  //mqttclient.publish(Gelentopic, onek+GonderenKullanici+publishmesaj);
  //publishmesaj="";
  
}


void mqttsend(String mqyol , String mqdata)
{
  String mqpat=mqyol;
  // mqdata = "/"+YOL + "/" + esphostname + "=" + degisenler;
    mqttclient.publish(mqpat, mqdata);
  //if(mqdata.indexOf("BUZ>")>-1)delay(100);
  //else{delay(4);}
  Serial.print("mqttsend yol: ");Serial.print(mqpat);
  Serial.print("mqttsend mqdata: ");Serial.print(mqdata);
  acltekrar=millis()+5000;
}

void mqttisyap(String rsltt)
{
  String rslttmp = rsltt;
                            for(int k=0;k<5;k++){
                              String pnm;
                              String pns;
                              String pnlabel;
                                  if(rslttmp.indexOf("=")>-1){
                                    mqgonderen=rslttmp.substring(0,rslttmp.indexOf("="));
                                  rslttmp = rslttmp.substring(rslttmp.indexOf("=")+1,rslttmp.length());
                                  }
                                  if(rslttmp.indexOf(":")>-1)pnm=rslttmp.substring(0,rslttmp.indexOf(":"));
                                  if(rslttmp.indexOf(",")>-1){
                                    pns=rslttmp.substring(rslttmp.indexOf(":")+1,rslttmp.indexOf(","));
                                    rslttmp = rslttmp.substring(rslttmp.indexOf(",")+1,rslttmp.length());

                                    Serial.print("   rslttmp           " );Serial.println(rslttmp);
                                    Serial.print(mqgonderen);Serial.print(" pnm:");Serial.print(pnm);Serial.print(" pns:");Serial.println(pns);

                                  }
                                  else
                                  {
                                    pns=rslttmp.substring(rslttmp.indexOf(":")+1,rslttmp.length());
                                    rslttmp = "";


                                    Serial.print("   rslttmp           " );Serial.println(rslttmp);
                                    Serial.print(mqgonderen);Serial.print(" pnm:");Serial.print(pnm);Serial.print(" pns:");Serial.println(pns);

                                  }

                                if(pnm.indexOf("VR")==0)
                                {
                                Serial.println(pnm+" "+pns);
                                  for(int vrr=0;vrr<6;vrr++)
                                  {
                                    if(pnm.indexOf("VR"+(String)vrr)==0)VRP[vrr]=pns;
                                  }
                                }
                                else
                                for(int hh=0;hh<11;hh++)
                                {
                                      if(pnm == pinname[hh])
                                      { 
                                            if(pns!=PinState[hh] && PinState[hh]==ePinState[hh])
                                            {
                                              PinState[hh] =pns;
                                              //ePinState[hh] = pns;
                                              //fbPinState[hh] = pns;
                                              //pindurumrecyap=true;
                                            }
                                        break;
                                      }
                                }


                                if(pnm=="ACL")
                                {
                                  ACL=pns;
                                  Serial.println("acil durum ilanı alındı: ACL"+ ACL+"\n");
                                  dosyayazacl();
                                }

                                
                                if(rslttmp.length()<2)break;
                            }

}

///// MQTT İŞLEMLERİ BİTİŞ ///////////////////////

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
    String pat= YOL + "/" + esphostname ;
    String msghello = "hello:" + esphostname; 
    mqttsend(pat,msghello);
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

  if(Gelenmsg.indexOf("hello:")>-1)
  {
  if(ACLilanciyim==true)
  {
    mqttsend(YOL + esphostname, "ALLDEV=ACL:"+ACL);
  }
  }
  for(int v=1;v<51;v++){
  if(Gelentopic == mqyol[v]  && Gelenmsg == degisenmq[v])return;
  }


  if (Gelenmsg == ePayload && Gelentopic == eTopic) return;
  else {

    eTopic = Gelentopic;
    ePayload = Gelenmsg;

  Serial.println(Gelentopic);
  Serial.println(Gelenmsg);

  if(Gelentopic.indexOf(esphostname)>-1 || Gelentopic.indexOf("ALLDEV")>-1)
    mqttisyap(payload);
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
Serial.print("mqgonderen:");Serial.print(mqgonderen);Serial.print(" pnm:");Serial.print(pnm);Serial.print(" pns:");Serial.println(pns);

                                  }
                                  else
                                  {
                                    pns=rslttmp.substring(rslttmp.indexOf(":")+1,rslttmp.length());
                                    rslttmp = "";


                                    Serial.print("   rslttmp           " );Serial.println(rslttmp);
Serial.print("mqgonderen:");Serial.print(mqgonderen);Serial.print(" pnm:");Serial.print(pnm);Serial.print(" pns:");Serial.println(pns);


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
                                  Serial.println("acil durum 1 ilan edildi..");
                                  dosyayazacl();
                                }

                                
                                if(rslttmp.length()<2)break;
                            }

}

///// MQTT İŞLEMLERİ BİTİŞ /////////////////////////

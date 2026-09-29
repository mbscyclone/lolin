
int fbsayac=0;
String esayacyani="";
String tamUrl;


void fbsayacoku()
{
      timereski=millis();

                                  if(psci==true || htpclilepindegisti==true){
                                    fbpinstateleriyaz();
                                    htpclilepindegisti=false;
                                  }


                              String anaUrl = DATABASE_URL;
                              String hedefYol = "/" + YOL + "/r/" + esphostname;
                              tamUrl = anaUrl + hedefYol + ".json" ; 
                              
                              String resul = firebaseGetData(tamUrl.c_str());
                              Serial.println("result:");Serial.println(resul);
                              if(resul=="null")fbdataguncelle();
                              else
                                {
                                  if(resul.toInt()==9){return;}

                                if(resul.toInt()>=5 && resul.toInt()<9){fbpinstatelerioku();fbsayacguncelle();}
                                
                                    if(psco==true || psci==true){
                                    fbpinstateleriyaz();
                                  }
                                }
                          
                          
}


void fbsayacguncelle()
{  
                          String anaUrl = DATABASE_URL;
                          String hedefYol = "/" + YOL + "/r/"+esphostname;
                          String tamUrl = anaUrl + hedefYol + ".json" ; 
                            fbsayac+=1;
                            if(fbsayac>4)fbsayac=0;


                            // save
                            firebasePutData(tamUrl.c_str(),(String)fbsayac);

}


void fbdataguncelle()
{
Serial.println("fbdataguncelle------------");

                              //sayac zaman guncelle 0 yap
                                  fbsayacguncelle();
                              ////////////////////////////

                              // pin ayarlarını yaz
                                  fbpinayarlariyaz();
                              /////////////////////////////

                              //pinstateleri yaz
                                  fbpinstateleriyaz();
                              /////////////////////////////
}

void fbpinstatelerioku()
{

                    if(YOL=="")dosyaokufbyol();


                              //firebaseRealtime.fetch("/" + YOL ,  "/pins/" , fetchDoc);
                          String anaUrl = DATABASE_URL;
                          String hedefYol = "/" + YOL + "/pins/"+esphostname+"pin";
                          String tamUrl = anaUrl + hedefYol + ".json" ; 

                          String resul=firebaseGetData(tamUrl.c_str());

                          if(resul=="null")
                          {
                            fbdataguncelle();
                          }
                          else
                          {
                            String reslt=resul;
                                degisenler="";
                                for(int h=0;h<pinsayisi;h++)
                                {
                                  if(reslt==".")break;
                                  String pnm=reslt.substring(0,reslt.indexOf(":"));
                                  String pns=reslt.substring(reslt.indexOf(":")+1,reslt.indexOf(","));
                                  reslt = reslt.substring(reslt.indexOf(",")+1,reslt.length());
                                  //Serial.println(pnm+" "+pns);
                                  
                                for(int hh=0;hh<pinsayisi;hh++)
                                    {
                                      if(pnm == pinname[hh])
                                      { 

                                        if(pinmode[hh]!="INP"){
                                            if(psco==false && pns!=fbPinState[hh])
                                            {
                                              
                                              PinState[hh] =pns;
                                              fbPinState[hh] = pns;
                                              //pindurumrecyap=true;
                                              degisenler += pinname[hh] + ":" + PinState[hh]+">" + pinlabel[hh] + ",";
                                            }

                                        }

                                        break;
                                      }
                                    }

                                }
                                //if(pindurumrecyap==true)dosyayazpindurum();
                                Serial.print("psco:");
                                Serial.print(psco);
                                Serial.print("  psci:");
                                Serial.println(psci);

                              if(psco==true || psci==true){fbpinstateleriyaz();}


                          }
}

void fbpinstateleriyaz()
{
                            //fbsayacguncelle();
                            //String setpath="/" + YOL + "/pins/" + esphostname+ "pin";
                            
                                String anaUrl = DATABASE_URL;
                                String hedefYol ="/" + YOL + "/pins/" + esphostname+ "pin";
                                String tamUrl = anaUrl + hedefYol + ".json" ; 
                                String dats="";

                                 //Serial.println(" v-- fbpinstateleriyaz  (pinname[h].toCharArray)> char < ascii code int value ");
                                for(int h=0;h<pinsayisi+1;h++)
                                {
                                  //if(pinname[h].indexOf("|")>-1)break;
                                  if(pinname[h].length()>0)
                                  {
                                  Serial.print(String(h) + " ----->"); Serial.print(pinname[h] + " = "); Serial.println(PinState[h]);
                                    if(PinState[h]=="")PinState[h]="0";
                                    int b=pinname[h].length()+1;
                                    char cvc[b];
                                    pinname[h].toCharArray(cvc, b);
                                 // Serial.print("\n-->");
                                 // Serial.print((int)cvc[0]);
                                 // Serial.println("<--- son");
                                    if(pinname[h].length()>0 && (int)cvc[0]!=10) dats+=pinname[h] + ":" + PinState[h] + ",";
                                  }
                                }
                                

                            // save

                                firebasePutData(tamUrl.c_str(),dats);

                                    for(int hh=0;hh<pinsayisi;hh++)
                                    {
                                              //ePinState[hh] = PinState[hh];
                                              fbPinState[hh] = PinState[hh];
                                    }
                            psco=false;
                            psci=false;


}


void fbpinayarlarioku()
{
                            // pin ayarlarını oku yoksa ya da farklıysa fbpinayarlariyaz() ile firebaseye gönder
                          String anaUrl = DATABASE_URL;
                          String hedefYol = "/" + YOL + "/pays/" + esphostname + "pay";
                          String tamUrl = anaUrl + hedefYol + ".json" ; 

                          String resul;
                          resul = firebaseGetData(tamUrl.c_str());

                            String dats="";
                                for(int h=0;h<pinsayisi;h++)
                                {
                                  if( pinsatir[h].length()>0) dats+="[" + pinsatir[h] + "]";
                                }

                                dats="[" + pinayar;
                                dats.replace("\n","][");
                                dats.replace("[]","");
                                if(dats.length()>1)dats=dats.substring(0,dats.length()-1);

                          if(resul=="null")
                          {
                                fbpinayarlariyaz();
                          }
                          else
                          {
                            Serial.println(resul);
                            Serial.println(dats);
                                   if(resul != dats) fbpinayarlariyaz();
                            else{Serial.println("aynı");}
                          }




                            /////////////////////////////
}



void fbpinayarlariyaz()
{
                            // pin ayarlarını yükle

                                String anaUrl = DATABASE_URL;
                                String hedefYol = "/" + YOL + "/pays/" + esphostname + "pay";
                                String tamUrl = anaUrl + hedefYol + ".json" ; 
                                String dats="";
                                for(int h=0;h<pinsayisi;h++)
                                {
                                  if( pinsatir[h].length()>0) dats+="[" + pinsatir[h] + "]";
                                }
                                dats="[" + pinayar;
                                dats.replace("\n","][");
                                dats.replace("[]","");
                                if(dats.length()>1)dats=dats.substring(0,dats.length()-1);

                                firebasePutData(tamUrl.c_str(),dats);

                            // save
                                fbpinstateleriyaz();
                            /////////////////////////////
}


void fbdeletesayac()
{
  //int deleteResponseCode = firebaseRealtime.remove("/" + YOL + "/r/" , esphostname);
}
















































/*
//          if(sayPtakipicin>100){
//            if(programdata.length()>1)Programtakip(programdata);
//            sayPtakipicin=0;
//          }
//          sayPtakipicin+=1;


   // save
  DynamicJsonDocument saveDoc(1024);
  saveDoc["name"] = "Device 1";
  saveDoc["temperature"] = 30.00;
  saveDoc["location"][0] = 48.756080;
  saveDoc["location"][1] = 2.302038;
  String saveJSONData;
  serializeJson(saveDoc, saveJSONData);
  int saveResponseCode = firebaseRealtime.save("devices", "1", saveJSONData);
  Serial.println("\nSave - response code: " + String(saveResponseCode));
  saveDoc.clear();

  // update
  DynamicJsonDocument updateDoc(1024);
  updateDoc["temperature"] = 35.00;
  String updateJSONData;
  serializeJson(updateDoc, updateJSONData);
  int updateResponseCode = firebaseRealtime.save("devices", "1", updateJSONData, true);
  Serial.println("\nUpdate - response code: " + String(updateResponseCode));
  updateDoc.clear();

  // fetch
  DynamicJsonDocument fetchDoc(1024);
  int fetchResponseCode = firebaseRealtime.fetch("devices", "1", fetchDoc);
  float temp = fetchDoc["temperature"];
  String name = fetchDoc["name"];
  float lat = fetchDoc["location"][0];
  float lon = fetchDoc["location"][1];
  Serial.println("\nFetch - response code: " + String(fetchResponseCode));
  Serial.println("Name: " + name + ", Temp: " + String(temp) + ", Lat: " + String(lat) + ", Lon: " + String(lon));
  fetchDoc.clear();


    // delete
  // int deleteResponseCode = remove("devices", "1");
  // Serial.println("\nDelete response code: " + String(deleteResponseCode));

*/
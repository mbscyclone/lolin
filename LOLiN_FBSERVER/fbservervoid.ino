int islemgorenespsira;
String espname;

void fbSroku()
{
      timereski=millis();



                              String anaUrl = DATABASE_URL;
                              String hedefYol = "/" + YOL + "/r/";
                              tamUrl = anaUrl + hedefYol + ".json" ; 
                              
                              String resul = firebaseGetData(tamUrl.c_str());
                              //Serial.println("result:");Serial.println(resul);
                              if(resul=="null") resul=="null";// fbdataguncelle();
                              else
                                {
                                  resul.replace("{","");
                                  resul.replace("\"","");
                                  resul.replace("}","");
                                  resul+=",";
                                  Serial.println("resul  :" + resul);

                                  uint8_t siradaki=1;
                                  for(uint8_t i=1;i<21;i++)
                                  {
                                    String arananname=resul.substring(0,resul.indexOf(":"));
                                    String arananr=resul.substring(resul.indexOf(":")+1,resul.indexOf(","));
                                    resul = resul.substring(resul.indexOf(",")+1,resul.length());
                                    //Serial.println("arananname " + arananname +"\n");
                                    for(uint8_t j=1;j<21;j++)
                                    {
                                      //Serial.println("na[j] " + na[j] +"\n");
                                      if(arananname==na[j])
                                      {
                                        r[j]=arananr;
                                        if(arananr.toInt()>4)
                                        {
                                          islemgorenespsira=j;
                                          Serial.println("fbSpinstatelerioku("+ arananname +")");
                                          fbSpinstatelerioku(islemgorenespsira);
                                        }


                                        break;
                                      }
                                      if(na[j]=="")break;
                                      if(resul.length()<3)break;
                                    }
                                  }





                                  /*
                                  
                                  if(resul.toInt()==9){return;}
                                  if(resul.toInt()>=5 && resul.toInt()<9){fbpinstatelerioku();fbsayacguncelle();}
                                  if(psco==true || psci==true){
                                  fbpinstateleriyaz();
                                  }

                                  */
                                }
                          
                          
}


void fbSrguncelle(int islemgoren)
{  
                          String anaUrl = DATABASE_URL;
                          String hedefYol = "/" + YOL + "/r/"+na[islemgoren];
                          String tamUrl = anaUrl + hedefYol + ".json" ; 
                            r[islemgoren] = String (r[islemgoren].toInt()+1);
                            if(r[islemgoren].toInt()>4)r[islemgoren]="0";


                            // save
                            firebasePutData(tamUrl.c_str(),(String)r[islemgoren]);

}


void fbSdataguncelle(int islemgoren)
{
Serial.println("fbdataguncelle------------");

                              //sayac zaman guncelle 0 yap
                                  fbSrguncelle(islemgoren);
                              ////////////////////////////
mqttclient.loop();
                              // pin ayarlarını yaz
                                  fbSpinayarlariyaz(islemgoren);
                              /////////////////////////////

                              //pinstateleri //////    yaz pinayarları yaz kısmında yapılıyor.
                                  // fbSpinstateleriyaz(islemgoren); 
                              /////////////////////////////
}

void fbSpinstatelerioku(int islemgoren)
{

                    if(YOL=="")dosyaokufbyol();


                              //firebaseRealtime.fetch("/" + YOL ,  "/pins/" , fetchDoc);
                          String anaUrl = DATABASE_URL;
                          String hedefYol = "/" + YOL + "/pins/"+na[islemgoren]+"pin";
                          String tamUrl = anaUrl + hedefYol + ".json" ; 

                          String resul=firebaseGetData(tamUrl.c_str());

                          if(resul=="null")
                          {
                            fbSdataguncelle(islemgoren);
                          }
                          else
                          {


                                  resul.replace("{","");
                                  resul.replace("\"","");
                                  resul.replace("}","");
                                  Serial.println("\nFBdengelenpindeger:"+resul+"\n");

                              String mqyol = "/" + YOL + "/"  + na[islemgoren];
                              String fbpin = "FBP>"+resul;
                              mqttsend(mqyol,fbpin);
                              fbSrguncelle(islemgoren);
                          }
}

void fbSpinstateleriyaz(int islemgoren)
{
                            //fbsayacguncelle();
                            //String setpath="/" + YOL + "/pins/" + esphostname+ "pin";
                            
                                String anaUrl = DATABASE_URL;
                                String hedefYol ="/" + YOL + "/pins/" + na[islemgoren]+ "pin";
                                String tamUrl = anaUrl + hedefYol + ".json" ; 
                                String dats=pi[islemgoren];



                            // save

                                firebasePutData(tamUrl.c_str(),dats);


}


void fbSpinayarlarioku(int islemgoren)
{
                            // pin ayarlarını oku yoksa ya da farklıysa fbpinayarlariyaz() ile firebaseye gönder
                          String anaUrl = DATABASE_URL;
                          String hedefYol = "/" + YOL + "/pays/" + na[islemgoren] + "pay";
                          String tamUrl = anaUrl + hedefYol + ".json" ; 

                          String resul;
                          resul = firebaseGetData(tamUrl.c_str());

                            String dats="";


                                dats="[" + pa[islemgoren];
                                dats.replace("\n","][");
                                dats.replace("[]","");
                                if(dats.length()>1)dats=dats.substring(0,dats.length()-1);

                          if(resul=="null")
                          {
                                fbSpinayarlariyaz(islemgoren);
                          }
                          else
                          {
                            Serial.println(resul);
                            Serial.println(dats);
                                   if(resul != dats) fbSpinayarlariyaz(islemgoren);
                            else{Serial.println("aynı");}
                          }




                            /////////////////////////////
}



void fbSpinayarlariyaz(int islemgoren)
{
                            
// pin ayarlarını yükle
                                String anaUrl = DATABASE_URL;
                                String hedefYol = "/" + YOL + "/pays/" + na[islemgoren] + "pay";
                                String tamUrl = anaUrl + hedefYol + ".json" ; 
                                String dats=pa[islemgoren];
                                dats="[" + pa[islemgoren];
                                dats.replace("\n","][");
                                dats.replace("[]","");
                                
                                firebasePutData(tamUrl.c_str(),dats);
                            // save
                                fbSpinstateleriyaz(islemgoren);
                            /////////////////////////////
}


void fbSdeletesayac(int islemgoren)
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
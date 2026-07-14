int fbsayac=0;
String esayacyani="";
void fbsayacoku()
{
yield();

//if(fbpinayaryaz==true){fbpinayaryaz=false;fbpinayarlariyaz();}

                      //String getpath="/" + YOL + "/r/"+esphostname;
//                    String resul=Firebase.RTDB.getString(&fbdo, getpath) ? fbdo.to<const char *>() : fbdo.errorReason().c_str();
                      

                              DynamicJsonDocument fetchDoc(512);
                              int fetchResponseCode = firebaseRealtime.fetch("/" + YOL, "/r/", fetchDoc);
                              String resul = fetchDoc[esphostname];
                              fetchDoc.clear();

Serial.println("Get str." + resul);
Serial.print("response code ");Serial.println(fetchResponseCode);

                          if(fetchResponseCode==200 && resul=="null")
                          {
                            Serial.println("path not exist");
                            fbdataguncelle();
                          }
                          else
                          {
                            if(resul.indexOf("|")>-1){
                              String rsltt=resul.substring(resul.indexOf("|")+1,resul.length());
                              resul=resul.substring(0,resul.indexOf("|"));
                              fbsayacyanioku(rsltt);
                            }
                            if(resul.toInt()==90){return;}

                            if(resul.toInt()==9 || resul.toInt()==19){fbpinstatelerioku();fbsayacguncelle();}
                            
                            if(resul.toInt()==10){resul="-1";fbpinstateleriyaz();}
                              else                         
                                if(psco==true || psci==true)fbpinstateleriyaz();
                          }
                          
}

void fbsayacyanioku(String rsltt)
{ 

String rslttmp = rsltt;
Serial.print("fbsayacyanı: "); Serial.println(rslttmp);
                            for(int k=0;k<6;k++){
                              String pnm;
                              String pns;
                                  if(rslttmp.indexOf(":")>-1)pnm=rslttmp.substring(0,rslttmp.indexOf(":"));
                                  if(rslttmp.indexOf(",")>-1){
                                    pns=rslttmp.substring(rslttmp.indexOf(":")+1,rslttmp.indexOf(","));
                                    rslttmp = rslttmp.substring(rslttmp.indexOf(",")+1,rslttmp.length());
                                  }
                                  else
                                  {
                                    pns=rslttmp.substring(rslttmp.indexOf(":")+1,rslttmp.length());
                                    rslttmp = "";
                                  }
                                  

Serial.print("pnm:");Serial.print(pnm);Serial.print(" pns:");Serial.print(pns);

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
                                            if(psco==false && pns!=fbPinState[hh])
                                            {
                                              PinState[hh] =pns;
                                              //ePinState[hh] = pns;
                                              fbPinState[hh] = pns;
                                              //pindurumrecyap=true;
                                            }
                                        break;
                                      }
                                }
                                if(rslttmp.length()<2)break;
                            }
}


void fbbaskacihazagonder(String yol1,String fbdt,int fbg)
{
yield();

                      Serial.print("yol1: ");Serial.println(yol1);
                      Serial.print("fbdt: ");Serial.println(fbdt);
                      String yol2=yol1.substring(0,yol1.indexOf("/r/"));
                      String yol3="/r/";
                      String rsl=yol1.substring(yol1.indexOf("/r/")+3,yol1.length());
                      Serial.print("yol2 ");Serial.println(yol2);
                      Serial.print("yol3 ");Serial.println(yol3);

                      //Serial.print("fbg: ");Serial.println(fbg);
                      
                      //String resul=Firebase.RTDB.getString(&fbdo, getpath2) ? fbdo.to<const char *>() : fbdo.errorReason().c_str();
                      //String resul = Database.get<String>(aClient, getpath2);

                              DynamicJsonDocument fetchDoc(512);
                              int fetchResponseCode = firebaseRealtime.fetch(yol2, yol3, fetchDoc);
                              String resul = fetchDoc[rsl];
                              fetchDoc.clear();

                      Serial.println("Get str." + resul);
                          if(fetchResponseCode==200 && resul=="null")
                          {
                                
                          }
                          else{
                            String dats2=fbdt;
                            int sayac=resul.toInt();
                            if(resul.toInt()==90){return;}
                            if(sayac==9)sayac=19; else sayac=10;
                            dats2=String(sayac) + "|" + fbdt;
                            Serial.println("DAAATS: " + dats2);
                            //bool statusz =Database.set<string_t>(aClient, setpath2, string_t(dats2));

                            Serial.print("yol1 ");Serial.println(yol1);
                            Serial.print("dats2 ");Serial.println(dats2);
Serial.print("yol2 ");Serial.println(yol2);
Serial.print("yol3 ");Serial.println(yol3);
                            // save
                            DynamicJsonDocument saveDoc(512);
                            saveDoc[rsl] = dats2;
                            String saveJSONData;
                            serializeJson(saveDoc, saveJSONData);
                            int saveResponseCode = firebaseRealtime.save(yol2, yol3, saveJSONData,true);
                            Serial.println("\nSave - response code: " + String(saveResponseCode));
                            saveDoc.clear();



                            if (saveResponseCode==200)
                                {Serial.println("ok");
                                efbtd[fbg]=fbtd[fbg];
                                }
                            else
                                //Firebase.printf("Error, msg: %s, code: %d\n", aClient.lastError().message().c_str(), aClient.lastError().code());
                                fbtd[fbg]=efbtd[fbg];
                          }
}

void fbsayacguncelle()
{  
                            String setpath="/" + YOL + "/r/"+esphostname;
                            fbsayac+=1;
                            if(fbsayac>7)fbsayac=0;
//                            String resul=Firebase.RTDB.setString(&fbdo, setpath, F("0")) ? (String)fbsayac : fbdo.errorReason().c_str();
                            //Database.set<string_t>(aClient, setpath, string_t((String)fbsayac));

                            // save
                            DynamicJsonDocument saveDoc(512);
                            saveDoc[esphostname] = String(fbsayac);
                            String saveJSONData;
                            serializeJson(saveDoc, saveJSONData);
                            int saveResponseCode = firebaseRealtime.save("/" + YOL, "/r/", saveJSONData,true);
                            Serial.println("\nSave - response code: " + String(saveResponseCode));
                            saveDoc.clear();

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

                    dosyaokufbyol();

                    
//                    String resul=Firebase.RTDB.getString(&fbdo, getpath) ? fbdo.to<const char *>() : fbdo.errorReason().c_str();
                      //String resul = Database.get<String>(aClient, getpath);

                              DynamicJsonDocument fetchDoc(512);
                              int fetchResponseCode = firebaseRealtime.fetch("/" + YOL ,  "/pins/" , fetchDoc);
                              String resul = fetchDoc[esphostname+"pin"];
                              fetchDoc.clear();

//Serial.println(getpath +"  ");
Serial.println("Get str. resul");
                          if(fetchResponseCode==200 && resul=="null")
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



void fbpinayarlarioku()
{
                            // pin ayarlarını yükle
                            //String getpath="/" + YOL + "/pays/" + esphostname + "pay";
                            //Serial.print("Gpath: " + getpath);
//                            String resul=Firebase.RTDB.getString(&fbdo, getpath) ? fbdo.to<const char *>() : fbdo.errorReason().c_str();
                            //String resul = Database.get<String>(aClient, getpath);

                              DynamicJsonDocument fetchDoc(512);
                              int fetchResponseCode = firebaseRealtime.fetch("/" + YOL, "/pays/", fetchDoc);
                              String resul = fetchDoc[esphostname+"pay"];
                              fetchDoc.clear();

                            String dats="";
                                //for(int h=0;h<pinsayisi;h++)
                                //{
                                //  if( pinsatir[h].length()>0) dats+="[" + pinsatir[h] + "]";
                                //}

                                dats="[" + pinayar;
                                dats.replace("\n","][");
                                dats.replace("[]","");
                                if(dats.length()>1)dats=dats.substring(0,dats.length()-1);

                          if(fetchResponseCode==200 && resul=="null")
                          {
                            fbpinayarlariyaz();
                          }else
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
                            //String setpath="/" + YOL + "/pays/" + esphostname + "pay";
                            String dats="";
                                //for(int h=0;h<pinsayisi;h++)
                                //{
                                //  if( pinsatir[h].length()>0) dats+="[" + pinsatir[h] + "]";
                                //}
                                dats="[" + pinayar;
                                dats.replace("\n","][");
                                dats.replace("[]","");
                                if(dats.length()>1)dats=dats.substring(0,dats.length()-1);

                            //Serial.print("Spath: " + setpath);Serial.println(dats);
//                            String resul=Firebase.RTDB.setString(&fbdo, setpath, dats) ? "ok" : fbdo.errorReason().c_str();
                           //Database.set<string_t>(aClient, setpath, string_t(dats));


                            // save
                            DynamicJsonDocument saveDoc(512);
                            saveDoc[esphostname + "pay"] = dats;
                            String saveJSONData;
                            serializeJson(saveDoc, saveJSONData);
                            int saveResponseCode = firebaseRealtime.save("/" + YOL , "/pays/", saveJSONData,true);
                            Serial.println("\nSave - response code: " + String(saveResponseCode));
                            saveDoc.clear();





                            /////////////////////////////
}

void fbpinstateleriyaz()
{
                            fbsayacguncelle();
                            //String setpath="/" + YOL + "/pins/" + esphostname+ "pin";
                            String dats="";

                            Serial.println(" v-- fbpinstateleriyaz  (pinname[h].toCharArray)> char < ascii code int value ");
                                for(int h=0;h<pinsayisi;h++)
                                {
                                  //if(pinname[h].indexOf("|")>-1)break;
                                  Serial.print(h + ">"); Serial.print(pinname[h] + "<"); Serial.println(PinState[h]);
                                  if(PinState[h]=="")PinState[h]="0";
                                  int b=pinname[h].length()+1;
                                  char cvc[b];
                                  pinname[h].toCharArray(cvc, b);
                                  Serial.print(">");
                                  Serial.print((int)cvc[0]);
                                  Serial.println("<");

                                  if(pinname[h].length()>0 && (int)cvc[0]!=10) dats+=pinname[h] + ":" + PinState[h] + ",";
                                }
                                
//                            String resul=Firebase.RTDB.setString(&fbdo, setpath, dats) ? "ok" : fbdo.errorReason().c_str();
                              //Database.set<string_t>(aClient, setpath, string_t(dats));

                            // save
                            DynamicJsonDocument saveDoc(512);
                            saveDoc[esphostname + "pin"] = dats;
                            String saveJSONData;
                            serializeJson(saveDoc, saveJSONData);
                            int saveResponseCode = firebaseRealtime.save("/" + YOL , "/pins/", saveJSONData,true);
                            Serial.println("\nSave - response code: " + String(saveResponseCode));
                            saveDoc.clear();

                                    for(int hh=0;hh<pinsayisi;hh++)
                                    {
                                              //ePinState[hh] = PinState[hh];
                                              fbPinState[hh] = PinState[hh];
                                    }
                            psco=false;
                            psci=false;


}

void fbdeletesayac()
{
  int deleteResponseCode = firebaseRealtime.remove("/" + YOL + "/r/" , esphostname);
}

















































//          if(sayPtakipicin>100){
//            if(programdata.length()>1)Programtakip(programdata);
//            sayPtakipicin=0;
//          }
//          sayPtakipicin+=1;

/*
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

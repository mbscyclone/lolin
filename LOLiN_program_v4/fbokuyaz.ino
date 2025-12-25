int fbsayac=0;
void fbsayacoku()
{

                      String getpath="/" + YOL + "/r/"+esphostname;
//                    String resul=Firebase.RTDB.getString(&fbdo, getpath) ? fbdo.to<const char *>() : fbdo.errorReason().c_str();
                      String resul = Database.get<String>(aClient, getpath);
Serial.println(getpath +"  ");
Serial.println("Get str." + resul);

                          if(resul.indexOf("not connected")>-1)
                          {
                            Serial.println("not connected");
                          }

                          if(resul.indexOf("path not exist")>-1 || resul=="null")
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
                            if(resul.toInt()==9 || resul.toInt()==19)fbpinstatelerioku();
                              if(resul.toInt()==10){resul="-1";fbpinstateleriyaz();}
                              if(resul.toInt()>18) {resul="8";fbpinstateleriyaz();}
                              }
                            if(psco==true || psci==true) fbpinstateleriyaz();
                          }

}

void fbsayacyanioku(String rsltt)
{
  Serial.println("fbsayacyaniokudayım");
                                  String pnm=rsltt.substring(0,rsltt.indexOf(":"));
                                  String pns=rsltt.substring(rsltt.indexOf(":")+1,rsltt.indexOf(","));
                                  rsltt = rsltt.substring(rsltt.indexOf(",")+1,rsltt.length());
                                  //Serial.println(pnm+" "+pns);
                                  
                                for(int hh=0;hh<pinsayisi;hh++)
                                    {
                                      if(pnm == pinname[hh])
                                      { 
                                        if(pinmode[hh]!="INP"){
                                            
                                            if(psco==false && pns!=fbPinState[hh])
                                            {
                                              PinState[hh] =pns;
                                              ePinState[hh] = pns;
                                              fbPinState[hh] = pns;
                                              pindurumrecyap=true;
                                            }
                                        }
                                        break;
                                      }
                                    }
}


void fbbaskacihazagonder(String yol2,String fbdt,int fbg)
{
                      Serial.print("yol2: ");Serial.println(yol2);
                      Serial.print("fbdt: ");Serial.println(fbdt);
                      Serial.print("fbg: ");Serial.println(fbg);
                      
                       delay(10);
                      String getpath2=yol2;
//                    String resul=Firebase.RTDB.getString(&fbdo, getpath2) ? fbdo.to<const char *>() : fbdo.errorReason().c_str();
                      String resul = Database.get<String>(aClient, getpath2);
                      Serial.println(getpath2 +"  ");
                      Serial.println("Get str." + resul);
                          if(resul.indexOf("path not exist")>-1 || resul=="null")
                          {
                                
                          }
                          else{
                            String setpath2=yol2;
                            String dats2=fbdt;
                            int sayac=resul.toInt();
                            if(sayac==9)sayac=19; else sayac=10;
                            dats2=String(sayac) + "|" + fbdt;
                            Serial.println("DAAATS: " + dats2);
                            bool statusz =Database.set<string_t>(aClient, setpath2, string_t(dats2));
                            if (statusz)
                                {Serial.println("ok");
                                efbtd[fbg]=fbtd[fbg];
                                }
                            else
                                Firebase.printf("Error, msg: %s, code: %d\n", aClient.lastError().message().c_str(), aClient.lastError().code());
                                fbtd[fbg]=efbtd[fbg];
                          }
}

void fbsayacguncelle()
{

                            String setpath="/" + YOL + "/r/"+esphostname;
                            fbsayac+=1;
                            if(fbsayac>7)fbsayac=0;
//                            String resul=Firebase.RTDB.setString(&fbdo, setpath, F("0")) ? (String)fbsayac : fbdo.errorReason().c_str();
                              Database.set<string_t>(aClient, setpath, string_t((String)fbsayac));
}


void fbdataguncelle()
{

                              // pin ayarlarını yaz
                                  fbpinayarlariyaz();
                              /////////////////////////////

                              //pinstateleri yaz
                                  fbpinstateleriyaz();
                              /////////////////////////////

                              //sayac zaman guncelle 0 yap
                                  fbsayacguncelle();
                              ////////////////////////////
}

void fbpinstatelerioku()
{

                    dosyaokufbyol();
                    String getpath="/" + YOL + "/pins/"+esphostname+"pin";
                          //  int str_len = getpath.length() + 1; 
                          //  char getp[str_len];
                          //  getpath.toCharArray(getp, str_len);

                    
//                    String resul=Firebase.RTDB.getString(&fbdo, getpath) ? fbdo.to<const char *>() : fbdo.errorReason().c_str();
                      String resul = Database.get<String>(aClient, getpath);
//Serial.println(getpath +"  ");
Serial.println("Get str. resul");
                          if(resul=="path not exist")
                          {
                            fbdataguncelle();
                          }
                          else
                          {
                            String reslt=resul;

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
                                              ePinState[hh] = pns;
                                              fbPinState[hh] = pns;
                                              pindurumrecyap=true;
                                            }

                                        }

                                        break;
                                      }
                                    }
                                    
                                }
                                if(pindurumrecyap==true)dosyayazpindurum();
                                Serial.print("psco:");
                                Serial.print(psco);
                                Serial.print("  psci:");
                                Serial.println(psci);

                              if(psco==true || psci==true) fbpinstateleriyaz();
                            //String resul=Firebase.RTDB.setString(&fbdo, setpath, dats) ? "ok" : fbdo.errorReason().c_str();
                            //Database.set<string_t>(aClient, setpath, string_t(dats));
                            //Serial.println("Set string... " + setpath + " " + resul);
                              fbsayacguncelle();
                          }
}



void fbpinayarlarioku()
{
                            // pin ayarlarını yükle
                            String getpath="/" + YOL + "/pays/" + esphostname + "pay";
                            Serial.print("Gpath: " + getpath);
//                            String resul=Firebase.RTDB.getString(&fbdo, getpath) ? fbdo.to<const char *>() : fbdo.errorReason().c_str();
                            String resul = Database.get<String>(aClient, getpath);


                            String dats="";
                                for(int h=0;h<pinsayisi;h++)
                                {
                                  if( pinsatir[h].length()>0) dats+="[" + pinsatir[h] + "]";
                                }


                          if(resul.indexOf("path not exist")>-1 || resul=="null")
                          {
                            fbpinayarlariyaz();
                          }else
                          {
                            Serial.println(resul);
                            Serial.println(dats);
                            if(resul != dats) fbpinayarlariyaz();
                          }




                            /////////////////////////////
}

void fbpinayarlariyaz()
{
                            // pin ayarlarını yükle
                            String setpath="/" + YOL + "/pays/" + esphostname + "pay";
                            String dats="";
                                for(int h=0;h<pinsayisi;h++)
                                {
                                  if( pinsatir[h].length()>0) dats+="[" + pinsatir[h] + "]";
                                }
                            //Serial.print("Spath: " + setpath);Serial.println(dats);
//                            String resul=Firebase.RTDB.setString(&fbdo, setpath, dats) ? "ok" : fbdo.errorReason().c_str();
                           Database.set<string_t>(aClient, setpath, string_t(dats));

                            /////////////////////////////
}

void fbpinstateleriyaz()
{

                            String setpath="/" + YOL + "/pins/" + esphostname+ "pin";
                            String dats="";
                                for(int h=0;h<pinsayisi;h++)
                                {
                                  //if(pinname[h].indexOf("|")>-1)break;
                                  //Serial.print(pinname[h] + " ");Serial.println(PinState[h]);
                                  if(PinState[h]=="")PinState[h]="0";
                                  if( pinname[h].length()>0) dats+=pinname[h] + ":" + PinState[h] + ",";
                                }
                                
//                            String resul=Firebase.RTDB.setString(&fbdo, setpath, dats) ? "ok" : fbdo.errorReason().c_str();
                              Database.set<string_t>(aClient, setpath, string_t(dats));

                                    for(int hh=0;hh<pinsayisi;hh++)
                                    {
                                              ePinState[hh] = PinState[hh];
                                              fbPinState[hh] = PinState[hh];
                                    }
                            psco=false;
                            psci=false;


                            fbsayacguncelle();
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
*/

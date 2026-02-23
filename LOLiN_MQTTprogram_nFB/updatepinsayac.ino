float t;
int h;
void updatehcsr()
{
          for(int x=0;x<pinsayisi;x++){
            
                        if(pinsignaltype[x]=="HCE"){
                          hcsr04loop(x);
                        }
          }
}


void updateinput()
{ degisenler="";
        for(int x=0;x<pinsayisi;x++){

                       if(pinmode[x]=="INP")
                       {
                        if(pinsignaltype[x]=="ANG"){
                        pinMode(Pin[x], INPUT);
                        //delay(5);
                        int analogokunandeger = analogRead(Pin[x]);
                          if(pinlabel[x].indexOf("DC")>-1)
                          {
                            float dcv;
                            if(analogokunandeger<200){
                              dcv = analogokunandeger*0.015;
                              
                            }else 
                            if(analogokunandeger>=200 && analogokunandeger<231){
                              dcv = 2.80+((analogokunandeger-200)/18.5);
                              
                            }else 
                            if(analogokunandeger>=231 && analogokunandeger<250){
                              dcv = 4.52+((analogokunandeger-231)/14.4);
                              
                            }else 
                            if(analogokunandeger>=250 && analogokunandeger<260){
                              dcv = 5.50+((analogokunandeger-250)/14.4);
                              
                            }else 
                            if(analogokunandeger>=260 && analogokunandeger<331){
                              dcv = 6.47+((analogokunandeger-260)/15.6);
                              
                            }else 
                            {analogokunandeger=analogokunandeger-180;
                              dcv = analogokunandeger*0.0737;
                            }
                            //Serial.print("değer: "); Serial.print(analogokunandeger); Serial.print(" Volt karşılığı: ");Serial.println(dcv);
                            
                            PinState[x] = dcv; 
                          } else PinState[x] = analogokunandeger;
                          
                        }

                        if(pinsignaltype[x]=="DIG"){
                        pinMode(Pin[x], INPUT);
                        //delay(5);
                        PinState[x] = digitalRead(Pin[x]);

                        }

                        if(pinsignaltype[x]=="HCE"){
                          hcsr04loop(x);
                        }
                        
                      if(pinsignaltype[x].indexOf("DHT")==0)
                      { dhtsayac+=1; 
                         if(dhtsayac>5){

                          Serial.println("DHTDONGUSU"); 
                              dhtsayac=0;
                              uint8_t DHT_TYPE;
                              if(pinsignaltype[x]=="DHT1") {DHT_TYPE= DHT11;}
                              if(pinsignaltype[x]=="DHT2") {DHT_TYPE= DHT12;}
                              if(pinsignaltype[x]=="DHT3") {DHT_TYPE= DHT21;}
                              if(pinsignaltype[x]=="DHT4") {DHT_TYPE= DHT22;}
                              DHT DHTA(Pin[x], DHT_TYPE);
                              //DHT

                              t = DHTA.readTemperature();  // boş iken  celcius // f = DHTA.readTemperature(true); fahrenayt 
                              delay(20);

                              h = DHTA.readHumidity();
                              delay(20);

                              // Check if any reads failed and exit early (to try again).
                              if (isnan(h) || isnan(t))  // || isnan(f)
                              {
                                  erlog = "DHT sensor okunamadı";
                              } else 
                              {

                                    if(h<100)
                                    {

                                      // sıcaklık hatası düzelt
                                      float tvehata=t+pinval[x].toFloat();
                                      String ts=(String)tvehata;

                                      // nem hatası düzelt
                                      int hvehata=h+pinmaxvalue[x].toInt();
                                      String hs=(String)hvehata;

                                        // kısa veri gönder
                                      if(pinminvalue[x]=="0") ts = ts.substring(0,ts.length()-1);
                                      if(pinminvalue[x]=="0") hs = hs.substring(0,hs.length()-1);

                                      if(pinminvalue[x]=="1") ts = ts.substring(0,ts.length()-3);
                                      if(pinminvalue[x]=="1") hs = hs.substring(0,hs.length()-1);

                                        PinState[x] ="t" + ts + "h" + hs;
                                        Serial.print(("Nem: "));
                                        Serial.print(hs);
                                        Serial.print(("0%  Sıcaklık: "));
                                        Serial.print(ts);
                                        Serial.print((" C"));
                                        Serial.println(".");
                                    }
                              }
                                                        Serial.println("DHTDONGUSU-çıkış"); 
                        }

                      }

          if(ePinState[x]!=PinState[x])
          {
             if (pinsignaltype[x].indexOf("DH")>-1)
                      {
                          psci=true;
                          
                          ePinState[x] = PinState[x];
                              degisenler += pinname[x] + ":" + PinState[x] + "|" + pinlabel[x] + ",";
                      }



                         if(pinsignaltype[x]=="HCE" && PinState[x].toInt()>2)
                         {
                          psci=true;
                          ePinState[x] = PinState[x];
                              degisenler += pinname[x] + ":" + PinState[x] + "|" + pinlabel[x] + ",";
                              Serial.println(degisenler);
                         } else
                              if(pinsignaltype[x]=="ANG")
                              {

                                int epinstate = ePinState[x].toInt();
                                int pinstate  =  PinState[x].toInt();


                                if(abs(epinstate-pinstate)>10){
                                  //Serial.println("Farklı olan e: " + pinname[x] + " " +ePinState[x] + " >> " + PinState[x]);
                                  psci=true;
                                  ePinState[x] = PinState[x];
                                  degisenler += pinname[x] + ":" + PinState[x] + "|" + pinlabel[x] + ",";
                                }

                              } else
                              {
                              psci=true;
                              ePinState[x] = PinState[x];
                              degisenler += pinname[x] + ":" + PinState[x] + "|" + pinlabel[x] + ",";
                              }





          }

                       }
        }
}


void updatefbvirtual()
{
                for (int fbg=0;fbg<11;fbg++)
                {
                  if(fbc[fbg].length()>0)
                  {
                    //Serial.println("fbcyol: " + fbcyol[fbg]);
                    //Serial.println("fbtd[fbg] " + fbtd[fbg] + "     efbtd[fbg]" +efbtd[fbg] );
                    if(fbtd[fbg]!=efbtd[fbg])
                    {
                      fbbaskacihazagonder(fbcyol[fbg], fbtd[fbg], fbg);
                    }
                  }
                }
}


void updateoutput()
{
      
        for(int x=0;x<pinsayisi;x++){
                  
                  if(pinmode[x]=="OUT"){
                    String pinstatesakla;

                    if(acildeyim[x]==true)
                    {
                      pinstatesakla=PinState[x];
                      PinState[x]=acildeger[x];
                    }

                        if(pinsignaltype[x]=="PWM"){
                          int PWMdegerint=PinState[x].toInt();
                          Outpwm(pinname[x], PWMdegerint);
                        }
                        if(pinsignaltype[x]=="DIG"){
                          bool yildizli; if(pinlabel[x].indexOf("*")+1==pinlabel[x].length())yildizli=true;else yildizli=false;
                                    if(PinState[x]=="0.00" || PinState[x]=="0" || PinState[x] == "LOW" || PinState[x] =="OFF" || PinState[x]=="")  {
                                      if(yildizli==false)digitalWrite(Pin[x], LOW ); else  digitalWrite(Pin[x], HIGH);
                                    }
                                      else
                                    if(PinState[x]=="1.00" || PinState[x]=="1" || PinState[x] == "HIGH" || PinState[x] =="ON")  
                                    {
                                      if(yildizli==false)digitalWrite(Pin[x], HIGH); else  digitalWrite(Pin[x], LOW);
                                    }
                        }


          if(ePinState[x]!=PinState[x])
          {
              //Serial.println("Farklı olan e: " + pinname[x] + " " +ePinState[x] + " >> " + PinState[x]);

                       if(pinmode[x]=="OUT")
                       {
                         psco=true;
                         //pindurumrecyap=true;
                         ePinState[x] = PinState[x];
                         degisenler += pinname[x] + ":" + PinState[x]+ "|" + pinlabel[x] + ",";
                       }
          }

                    if(acildeyim[x]==true)
                    {
                      PinState[x]=pinstatesakla;
                    }

        }
/*
              if(pindurumrecyap==true)
              {
                dosyayazpindurum();
              }
*/
        }
      if(degisenler!="" && degisenler!= edegisenler){
        if(htServerip.length()>3)sendserver80(htServerip, "8080", degisenler);
      }
        yield();

}





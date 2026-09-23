
void udptara(){
if(kimdir==1){udpbaslat();}
if(kimdir==2){udpcevaplaridinle();}
}

void udpbaslat()
{
  // udp tarama başlat
      udp.beginPacket("255.255.255.255", 4210);
      udp.write("DECLEREET");
      udp.endPacket();
      kimdir=2;
      espv4sayac=1;
      udpcevapbeklemesuresi=millis();


                    LittleFS.remove("/espler.txt");
                    LittleFS.remove("/kimdirf.txt");
                                  for(int j=1;j<21;j++)
                                  {
                                      bulunanespv4[j]="";
                                  }
                                  Serial.println("UDP başladı");

}

void udpcevaplaridinle(){
  // cevapları dinle
  int packetSize = udp.parsePacket();
  if (packetSize) {
      char buf[255];
      udp.read(buf, 255);
      Serial.println("Cevap: " + String(buf));
      bulunanespv4[espv4sayac]=String(buf);
      espv4sayac+=1;
  }
  if(millis()>udpcevapbeklemesuresi + 10000)
  {kimdir=-2; Serial.println("UDP dinleme biti");}
}
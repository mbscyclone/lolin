String satirp[100];
String degis[80];
String degdeg[80];
// 0-10  PİN     11-30 bool    31-50 bool sonuç  51-70 degiskenler 71-80  FBden gonderilecek bilgi

int degisecekno = -10000;

int satirsayisip;
uint8_t ifsonuc;

String parantezici;

int aktifpinno;

String ptm;

void programrun() {
  for (int i = 0; i < 11; i++)  // İLK 10 SAYI 10 PİN İSİM VE DEĞERLERİNİ AL degis degdeg e yaz
  {
    degis[i] = pinname[i];
    degdeg[i] = PinState[i];
  }
  for (int i = 11; i < 81; i++) {
    degdeg[i] = "";
    degis[i] = "";
  }



  progmsg = "";

  perlog = "";
  ptm = programdata;
  for (int q = 1; q < 100; q++) {
    satirsayisip = q;
    if (ptm.length() < 3) break;
    satirp[q] = ptm.substring(0, ptm.indexOf("\n"));
    satirislem();
    ptm = ptm.substring(ptm.indexOf("\n") + 1, ptm.length());
    //Serial.println("satirp "); Serial.println(satirp[q]);

    if (perlog != "") return;
  }

  // en son işlem burası //////////////////////////////////
  for (int sta = 0; sta < pinsayisi + 1; sta++) {
    PinState[sta] = degdeg[sta];
    //Serial.print(pinname[sta] + " pinstate:");Serial.println(PinStatetmp[sta]);
  }
  ////////////////////////////////////////////////////////
}

void satirislem() {
  String satiruppercase = satirp[satirsayisip];
  satiruppercase.toUpperCase();
  //Serial.println(satiruppercase);
  // if için ///////////////////////////////////////////

  if (satiruppercase.indexOf("//") == 0) return;
  if (satiruppercase.indexOf("IF") == 0) gotoif();
  if (satiruppercase.indexOf("BOOL") == 0) gotobool();

  // ????????????????????????????????????????????? sonra ne yaparız bilmem
}

void gotobool() {
  String satiruppercase = satirp[satirsayisip];
  satiruppercase.toUpperCase();
  String boolsonrasi = satiruppercase.substring(5, satiruppercase.length());
  boolsonrasi.trim();
  String boolnametmp;
  int boolstatetmp;

  if (boolsonrasi.indexOf("=") > -1) {
    boolnametmp = boolsonrasi.substring(0, boolsonrasi.indexOf("="));
    boolstatetmp = (boolsonrasi.substring(boolsonrasi.indexOf("=") + 1, boolsonrasi.length() - 1)).toInt();
    //Serial.print(boolnametmp);Serial.println(boolstatetmp);
  }

  if (boolsonrasi.indexOf("=") < 0) {
    boolnametmp = boolsonrasi.substring(0, boolsonrasi.indexOf(";"));
    boolstatetmp = 0;
    //Serial.print(boolnametmp);Serial.println(boolstatetmp);
  }


  for (int j = 11; j < 31; j++)  // bool değişkenler 11-30
  {
    if (degis[j] == boolnametmp) {
      degdeg[j] = boolstatetmp;
      break;
    }
    if (degis[j] == "") {
      degis[j] = boolnametmp;
      degdeg[j] = boolstatetmp;
      break;
    }
  }
}

void gotoif() {
  String sol = "";
  String sag = "";
  String solstate;
  String sagstate;
  ifsonuc = 2;

  String sat = satirp[satirsayisip];
  if (sat.indexOf("(") < 1) { perlog += "if ten sonra ( işareti olmalı. Satır:" + (String)satirsayisip + "\n"; }
  if (sat.indexOf(")") < 1) { perlog += "if te ) kapatılmamış." + (String)satirsayisip + "\n"; }
  if (perlog != "") return;
  String parantezici = sat.substring(sat.indexOf("(") + 1, sat.indexOf(")"));
  parantezici.replace(" ", "");

  String satiruppercase = satirp[satirsayisip];
  satiruppercase.toUpperCase();
  String parantezdisi = satiruppercase.substring(satiruppercase.indexOf(")") + 1, satiruppercase.indexOf(";"));




  //Serial.print("parantezici ");Serial.println(parantezici);

  uint8_t op;
  if (parantezici.indexOf("==") > -1) {
    op = 1;
    sol = parantezici.substring(0, parantezici.indexOf("=="));
    sag = parantezici.substring(parantezici.indexOf("==") + 2, parantezici.length());
    if (sag.indexOf("t") == 0) { sag = sag.substring(1, sag.length()); }
    if (sag.indexOf("h") == 0) { sag = sag.substring(1, sag.length()); }
  } else if (parantezici.indexOf(">=") > -1) {
    op = 2;
    sol = parantezici.substring(0, parantezici.indexOf(">="));
    sag = parantezici.substring(parantezici.indexOf(">=") + 2, parantezici.length());
    if (sag.indexOf("t") == 0) { sag = sag.substring(1, sag.length()); }
    if (sag.indexOf("h") == 0) { sag = sag.substring(1, sag.length()); }
  } else if (parantezici.indexOf(">") > -1) {
    op = 3;
    sol = parantezici.substring(0, parantezici.indexOf(">"));
    sag = parantezici.substring(parantezici.indexOf(">") + 1, parantezici.length());
    if (sag.indexOf("t") == 0) { sag = sag.substring(1, sag.length()); }
    if (sag.indexOf("h") == 0) { sag = sag.substring(1, sag.length()); }
  } else if (parantezici.indexOf("<=") > -1) {
    op = 4;
    sol = parantezici.substring(0, parantezici.indexOf("<="));
    sag = parantezici.substring(parantezici.indexOf("<=") + 2, parantezici.length());
    if (sag.indexOf("t") == 0) { sag = sag.substring(1, sag.length()); }
    if (sag.indexOf("h") == 0) { sag = sag.substring(1, sag.length()); }
  } else if (parantezici.indexOf("<") > -1) {
    op = 5;
    sol = parantezici.substring(0, parantezici.indexOf("<"));
    sag = parantezici.substring(parantezici.indexOf("<") + 1, parantezici.length());
    if (sag.indexOf("t") == 0) { sag = sag.substring(1, sag.length()); }
    if (sag.indexOf("h") == 0) { sag = sag.substring(1, sag.length()); }
  } else if (parantezici.indexOf("!=") > -1) {
    op = 6;
    sol = parantezici.substring(0, parantezici.indexOf("!="));
    sag = parantezici.substring(parantezici.indexOf("!=") + 2, parantezici.length());
    if (sag.indexOf("t") == 0) { sag = sag.substring(1, sag.length()); }
    if (sag.indexOf("h") == 0) { sag = sag.substring(1, sag.length()); }
  } else {
    perlog += "if kıyaslama işareti uygun değil '==,>=,>,<,<=,!=' kullanın. Satır:" + (String)satirsayisip + "\n";
  }

  if (sol == "") { perlog += "Kıyaslamada sol taraf boş! Satır:" + (String)satirsayisip + "\n"; }
  if (sag == "") { perlog += "Kıyaslamada sag taraf boş! Satır:" + (String)satirsayisip + "\n"; }
  if (perlog != "") return;
  //Serial.print("sol: "); Serial.println(sol);
  //  Serial.print("sag: "); Serial.println(sag);
  aktifpinno = -10000;


  for (int pinbul = 0; pinbul < 81; pinbul++) {  //Serial.print("pinname: "); Serial.println(pinname[pinbul]);
    if (sol == degis[pinbul]) {
      solstate = degdeg[pinbul];
      aktifpinno = pinbul;
      break;
    }
  }


  if (aktifpinno == -10000) { perlog += "if içi soldaki tanımlı değil " + sol + " Satır:" + (String)satirsayisip + "\n"; }

  if (perlog != "") return;

  Serial.println("PARANTEZ İÇİ");
  Serial.print("sol ");
  Serial.print(sol);
  Serial.print("  ");
  Serial.print(sag);
  Serial.println(" sag");

  //Serial.print("op ");Serial.println(op);

  if (op == 1) {
    if (solstate.toFloat() == sag.toFloat()) ifsonuc = 1;
    else ifsonuc = 0;
  } else if (op == 2) {
    if (solstate.toFloat() >= sag.toFloat()) ifsonuc = 1;
    else ifsonuc = 0;
  } else if (op == 3) {
    if (solstate.toFloat() > sag.toFloat()) ifsonuc = 1;
    else ifsonuc = 0;
  } else if (op == 4) {
    if (solstate.toFloat() <= sag.toFloat()) ifsonuc = 1;
    else ifsonuc = 0;
  } else if (op == 5) {
    if (solstate.toFloat() < sag.toFloat()) ifsonuc = 1;
    else ifsonuc = 0;
  } else if (op == 6) {
    if (solstate.toFloat() != sag.toFloat()) ifsonuc = 1;
    else ifsonuc = 0;
  }
  //Serial.print(parantezici + " ->  ");Serial.println (ifsonuc);

  //PinStatetmp[aktifpinno]=sonucdegeri;

  if (ifsonuc) Serial.println("DOĞRU");
  else Serial.println("YANLIŞ");

  if (ifsonuc == true) ifparantezdisi(satiruppercase, satirsayisip);
}
















void ifparantezdisi(String satiruppercase, int satirsayisip) {
  String yapilacaklar;
  String yapilacakis;
  int yapilacaklarislemsayisi;
  String parantezdisisol;
  String parantezdisisag;
  satiruppercase.toUpperCase();
  yapilacaklar = satiruppercase.substring(satiruppercase.indexOf(")") + 1, satiruppercase.length());
  if(yapilacaklar.indexOf("{")>-1)
  {
    int sonsatir=satirsayisip;
    Serial.print("ptm:");Serial.println(ptm);
    String tmpsatir = ptm.substring(0, ptm.length());
    String tmpsatirincele=tmpsatir.substring(0, tmpsatir.indexOf("\n"));
        Serial.print("tmpsatirincele:");Serial.println(tmpsatirincele);
    for(int g=satirsayisip;g<100;g++){
      tmpsatirincele = tmpsatir.substring(0, tmpsatir.indexOf("\n"));
      Serial.print("tmpsatirincele:");Serial.println(tmpsatirincele);
      if(tmpsatirincele.indexOf("}")>-1){
        sonsatir=g;
        break;
        }
      tmpsatir= tmpsatir.substring(tmpsatir.indexOf("\n")+1,tmpsatir.length());
      if(tmpsatirincele.length()<2){Serial.println("bulunamadı bişey");break;}
    }
    tmpsatir = ptm.substring(0, ptm.indexOf("}"));
    tmpsatir.replace("\n","");
   yapilacaklar=tmpsatir.substring(tmpsatir.indexOf("{")+1,tmpsatir.indexOf("}"));
  }
  Serial.print("yapilacaklar:");   
  Serial.println(yapilacaklar);
  //sonsatir belli;
  
  
                                                         // boşlukları sil
                                                        if (yapilacaklar.indexOf(";") > -1) {
                                                          for (int i = 1; i < 11; i++) {

                                                            if (yapilacaklar.indexOf(" ") == 0) {
                                                              for (int j = 1; j < 100; j++) {
                                                                yapilacaklar = yapilacaklar.substring(1, yapilacaklar.length());
                                                                
                                                                if (yapilacaklar.indexOf(" ") != 0) break;
                                                              }
                                                            }    //baştaki boşlukları sil

      yapilacakis = yapilacaklar.substring(0, yapilacaklar.indexOf(";"));
      yapilacaklar = yapilacaklar.substring(yapilacaklar.indexOf(";") + 1, yapilacaklar.length());
      yapilacaklarislemsayisi = i;
      Serial.print("yapılacak");
      Serial.println(yapilacakis);
      Serial.print("yapilacaklarislemsayisi ");
      Serial.println(yapilacaklarislemsayisi);
      // tam burada yapılacak hesabına git
      yap(yapilacakis,yapilacaklarislemsayisi);
      if (yapilacaklar.length() < 3) break;
    }
  } else {
    perlog += (String)satirsayisip + ". satırda / satır sonunda ';' unutulmuş.\n";
    return;
  }
  return;
}

void yap(String yapilacak,int islemno)
{
      Serial.print("yapılacak");
      Serial.println(yapilacak);
      Serial.print("işlem no");
      Serial.println(islemno);

    String noktalivirgulekadar = yapilacak;
      String dsol = noktalivirgulekadar.substring(0, noktalivirgulekadar.indexOf("="));
      String dsag = noktalivirgulekadar.substring(noktalivirgulekadar.indexOf("=") + 1, noktalivirgulekadar.indexOf(";"));
      for (int indis = 0; indis < 81; indis++)  // her islem için döngü
      {

          if (indis < 11) {
            if (dsol == degis[indis]) { 
            degdeg[indis] = dsag;
            progmsg += degis[indis] + " Program satiri " + (String)satirsayisip + " yuzunden degisti. " + "  Komut: " + satirp[satirsayisip] + " iş:" + yapilacak + "\n";
            Serial.print(pinname[indis] + " ------> ");Serial.println(degis[indis]);
            break;
            }
          } else if (indis >= 11 && indis < 31)  // bool ifade leri tut
          {
            if (dsol == degis[indis]) { 
            degdeg[indis] = dsag;
            progmsg += degis[indis] + " Program satiri " + (String)satirsayisip + " yuzunden degisti. " + "  Komut: " + satirp[satirsayisip] + " iş:" + yapilacak + "\n";
            //Serial.print(pinname[indis] + " ------> ");Serial.println(degis[indis]);
            break;
            }
          } else if (indis >= 31 && indis < 51)  // bool sonuçlar çıkacak
          {
            if (dsol == degis[indis]) { 
            degdeg[indis] = dsag;
            progmsg += degis[indis] + " Program satiri " + (String)satirsayisip + " yuzunden degisti. " + "  Komut: " + satirp[satirsayisip] + " iş:" + yapilacak + "\n";
            //Serial.print(pinname[indis] + " ------> ");Serial.println(degis[indis]);
            break;
            }
          } else if (indis >= 51 && indis < 71)  // degiskenler
          {
            if (dsol == degis[indis]) { 
            degdeg[indis] = dsag;
            progmsg += degis[indis] + " Program satiri " + (String)satirsayisip + " yuzunden degisti. " + "  Komut: " + satirp[satirsayisip] + " iş:" + yapilacak + "\n";
            //Serial.print(pinname[indis] + " ------> ");Serial.println(degis[indis]);
            break;
            }
          } else if (indis >= 71 && indis < 81)  // FB gonderilecek Başka çihazlara
          {
            if (dsol == degis[indis]) { 
            degdeg[indis] = dsag;
            progmsg += degis[indis] + " Program satiri " + (String)satirsayisip + " yuzunden degisti. " + "  Komut: " + satirp[satirsayisip] + " iş:" + yapilacak + "\n";
            //Serial.print(pinname[indis] + " ------> ");Serial.println(degis[indis]);
            break;
            }
          }

          // 0-10  PİN     11-30 bool    31-50 bool sonuç  51-70 degiskenler 71-80  FBden gonderilecek bilgi
    }
  }

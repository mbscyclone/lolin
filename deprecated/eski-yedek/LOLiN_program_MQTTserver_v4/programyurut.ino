
int degisecekno = -10000;

int satirsayisip;
uint8_t ifsonuc;

String parantezici;

int aktifpinno;

String ptm;

void programrun() {
  for (int i = 0; i < 11; i++)  // İLK 10 SAYI 10 PİN İSİM VE DEĞERLERİNİ AL degis degdeg e yaz
  {
    if(programdata.substring(0,1)=="\n")programdata.substring(1,programdata.length());//arada programdata için temizlik yap
    degis[i] = pinname[i];
    degdeg[i] = PinState[i];
    fbc[i]="";fbcyol[i]="";fbtd[i]="";
  }
  for (int i = 11; i < 71; i++) {
    degdeg[i] = "";
    degis[i] = "";
  }

  if(programdata.length()<4)return;

  progmsg = "";

  perlog = "";
  ptm = programdata;
  for (int q = 1; q < 100; q++) {
    satirsayisip = q;
    if (ptm.length() < 3) break;
    if (ptm.indexOf("\n")>4 && ptm.indexOf("\n")<6) break;
    satirp[q] = ptm.substring(0, ptm.indexOf("\n"));
    satirislem();
    if(ptm.substring(ptm.indexOf("\n")>-1)) ptm = ptm.substring(ptm.indexOf("\n") + 1, ptm.length());
    else return;
    //Serial.println("satirp "); Serial.println(satirp[q]);

    if (perlog != "") return;
  }

  // en son işlem burası //////////////////////////////////
  for (int sta = 0; sta < pinsayisi + 1; sta++) {
    PinState[sta] = degdeg[sta];
    //Serial.print(pinname[sta] + " pinstate:");Serial.println(PinStatetmp[sta]);
  }
  ////////////////////////////////////////////////////////

// fbde başka cihaza gonderilecek varmı bak ////////////////





////////////////////////////////////////////////////////////
}

void satirislem() {
  String satiruppercase = satirp[satirsayisip];
  satiruppercase.toUpperCase();
//Serial.println(satiruppercase);
  // if için ///////////////////////////////////////////

  if (satiruppercase.indexOf("//") == 0) return;

  if (satiruppercase.indexOf("FBC ") == 0) firebasecihaztanitimi();
  if (satiruppercase.indexOf("IF") == 0) gotoif();
  if (satiruppercase.indexOf("BOOL") == 0) gotobool();

  // ????????????????????????????????????????????? sonra ne yaparız bilmem
}

void firebasecihaztanitimi()
{
  //Serial.println("FBCihaz tanıtımı");
  for(int ii=0;ii<11;ii++)
  {
      if(satirp[satirsayisip].indexOf("=")>5){
        if(fbc[ii]=="" || fbc[ii]=="null" || fbc[ii]==satirp[satirsayisip].substring(4,satirp[satirsayisip].indexOf("=")))
        {
          String fbcvefbcyol=satirp[satirsayisip]; 
            fbc[ii]=fbcvefbcyol.substring(4,fbcvefbcyol.indexOf("="));
            fbcyol[ii]=fbcvefbcyol.substring(fbcvefbcyol.indexOf("=")+1,fbcvefbcyol.indexOf(";"));
          //Serial.print("ii      ");Serial.println(ii);
          //Serial.print("FBcihaz ");Serial.println(fbc[ii]);
          //Serial.print("FBcyol  ");Serial.println(fbcyol[ii]);
          break;
        }
      }else{progmsg+="fbc hatası. fbc fb1=/yol/cihaz; şeklinde olmalı. satır no: " + (String)satirsayisip + " komut: " + satirp[satirsayisip]+"\n";}
  }
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


  for (int j = 31; j < 51; j++)  // bool değişkenler 11-30
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
  //Serial.print("sag: "); Serial.println(sag);
  aktifpinno = -10000;


  for (int pinbul = 0; pinbul < 71; pinbul++) {  //Serial.print("pinname: "); Serial.println(pinname[pinbul]);
    if (sol == degis[pinbul]) {
      solstate = degdeg[pinbul];
      aktifpinno = pinbul;
      break;
    }
  }


  if (aktifpinno == -10000) { perlog += "if içi soldaki tanımlı değil " + sol + " Satır:" + (String)satirsayisip + "\n"; }

  if (perlog != "") return;

  /*
Serial.println("PARANTEZ İÇİ");
Serial.print("sol ");
Serial.print(sol);
Serial.print("  ");
Serial.print(sag);
Serial.println(" sag");
*/

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

  //if (ifsonuc) Serial.println("DOĞRU");
  //else Serial.println("YANLIŞ");

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
    //Serial.print("ptm:");Serial.println(ptm);
    yapilacaklar=ptm.substring(ptm.indexOf("{")+1,ptm.indexOf("}"));
  //  Serial.print("yapilacaklar:");   
  //  Serial.println(yapilacaklar);
    yapilacaklar.replace("\n","");
  }else
  {
    ptm=ptm.substring(ptm.indexOf("\n")+1,ptm.length());
  }
  //Serial.print("programdata:");   
  //Serial.println(programdata);
  
  //Serial.print("ptm:");   
  //Serial.println(ptm);
  //Serial.print("yapilacaklar:");   
  //Serial.println(yapilacaklar);
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
      yapilacaklarislemsayisi = i;
      Serial.print("yapılacak ");
      Serial.println(yapilacakis);
      //Serial.print("yapilacaklarislemsayisi ");
      //Serial.println(yapilacaklarislemsayisi);
      // tam burada yapılacak hesabına git
      yap(yapilacakis,yapilacaklarislemsayisi);
      yapilacaklar = yapilacaklar.substring(yapilacaklar.indexOf(";") + 1, yapilacaklar.length());

      if(yapilacaklar.indexOf("}")<1){
        yapilacaklar="";
        ptm=ptm.substring(ptm.indexOf("}"),ptm.length());
        }
      if (yapilacaklar.length() < 1){break;}
    }
  } else {
    perlog += (String)satirsayisip + ". satırda / satır sonunda ';' unutulmuş.\n";
    return;
  }
  return;
}

void yap(String yapilacak,int islemno)
{
      //Serial.print("yapılacak  ");
      //Serial.println(yapilacak);
      //Serial.print("  işlem no  ");
      //Serial.println(islemno);

    String noktalivirgulekadar = yapilacak;
      String dsol = noktalivirgulekadar.substring(0, noktalivirgulekadar.indexOf("="));
      String dsag = noktalivirgulekadar.substring(noktalivirgulekadar.indexOf("=") + 1, noktalivirgulekadar.indexOf(";"));
      for (int indis = 0; indis < 81; indis++)  // her islem için döngü
      {
          if (indis < 11) {
            String fbcupercase=fbc[indis];
            fbcupercase.toUpperCase();
        //if(indis<2)Serial.print("dsol ve fbc :");Serial.println(dsol + "   " + fbcupercase);
            if (dsol == fbcupercase) { 
    if(indis<2)Serial.print("efbtd ve fbtd :");Serial.println(efbtd[indis] + "   " + fbtd[indis]);
            fbtd[indis] = dsag;
            if(efbtd[indis]!=fbtd[indis]){
              Serial.print("dsol ve fbc :");Serial.println(dsol + "   " + fbcupercase);
                        //efbtd[indis] = dsag;
              progmsg += fbc[indis] + " Program satiri " + (String)satirsayisip + " yuzunden degisti. " + "  Komut: " + satirp[satirsayisip] + " iş:" + yapilacak + "<br>";
              Serial.print(fbcyol[indis] + " ------> ");Serial.println(fbtd[indis]);
            }
            break;
            }

            if (dsol == degis[indis]) { 
            degdeg[indis] = dsag;
            progmsg += degis[indis] + " Program satiri " + (String)satirsayisip + " yuzunden degisti. " + "  Komut: " + satirp[satirsayisip] + " iş:" + yapilacak + "<br>";
            //Serial.print(pinname[indis] + " ------> ");Serial.println(degis[indis]);
            break;
            }
          } else if (indis >= 11 && indis < 31)  // degiskenleri tut
          {
            if (dsol == degis[indis]) { 
            degdeg[indis] = dsag;
            progmsg += degis[indis] + " Program satiri " + (String)satirsayisip + " yuzunden degisti. " + "  Komut: " + satirp[satirsayisip] + " iş:" + yapilacak + "<br>";
            //Serial.print(pinname[indis] + " ------> ");Serial.println(degis[indis]);
            break;
            }
          } else if (indis >= 31 && indis < 51)  // bool degisken
          {
            if (dsol == degis[indis]) { 
            degdeg[indis] = dsag;
            progmsg += degis[indis] + " Program satiri " + (String)satirsayisip + " yuzunden degisti. " + "  Komut: " + satirp[satirsayisip] + " iş:" + yapilacak + "<br>";
            //Serial.print(pinname[indis] + " ------> ");Serial.println(degis[indis]);
            break;
            }
          } else if (indis >= 51 && indis < 71)  // bool sonuc
          {
            if (dsol == degis[indis]) { 
            degdeg[indis] = dsag;
            progmsg += degis[indis] + " Program satiri " + (String)satirsayisip + " yuzunden degisti. " + "  Komut: " + satirp[satirsayisip] + " iş:" + yapilacak + "<br>";
            //Serial.print(pinname[indis] + " ------> ");Serial.println(degis[indis]);
            break;
            }
          }
          
// 0-10  PİN     11-30 degisken    31-50 booldegisken  51-70 boolsonuc
    }

  }

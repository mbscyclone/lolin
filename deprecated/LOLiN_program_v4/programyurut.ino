
int degisecekno = -10000;

int satirsayisip;

bool ifkiyas[5];
bool vevar[5];
bool ifsonuc;
uint8_t kiyassayisi;
String parantezici;

int aktifpinno;

String ptm;

void programrun() {
  for (int i = 0; i < 11; i++)  // İLK 10 SAYI 10 PİN İSİM VE DEĞERLERİNİ AL degis degdeg e yaz
  {
    if (programdata.substring(0, 1) == "\n") programdata.substring(1, programdata.length());  //arada programdata için temizlik yap
    degis[i] = pinname[i];
    degdeg[i] = PinState[i];
    fbc[i] = "";
    fbcyol[i] = "";
    fbtd[i] = "";
  }
  for (int i = 11; i < 21; i++) {
    degdeg[i] = "";
    degis[i] = "";
  }

  if (programdata.length() < 4) return;

  progmsg = "";

  perlog = "";
  ptm = programdata;
  for (int q = 1; q < 40; q++) {
    satirsayisip = q;
    if (ptm.length() < 3) break;
    if (ptm.indexOf("\n") > 4 && ptm.indexOf("\n") < 6) break;
    satirp = ptm.substring(0, ptm.indexOf("\n"));
    satirislem();
    if (ptm.substring(ptm.indexOf("\n") > -1)) ptm = ptm.substring(ptm.indexOf("\n") + 1, ptm.length());
    else return;
    //Serial.println("satirp "); Serial.println(satirp);
    yield();
  }


  // en son işlem burası //////////////////////////////////
  for (int sta = 0; sta < 11; sta++) {
    PinState[sta] = degdeg[sta];
    //Serial.print(pinname[sta] + " pinstate:");Serial.println(PinStatetmp[sta]);
  }
  ////////////////////////////////////////////////////////

  // fbde başka cihaza gonderilecek varmı bak ////////////////





  ////////////////////////////////////////////////////////////
}

void satirislem() {
  String satiruppercase = satirp;
  satiruppercase.toUpperCase();
  //Serial.println(satiruppercase);
  // if için ///////////////////////////////////////////

  if (satiruppercase.indexOf("//") == 0) return;
  if (satiruppercase.indexOf("FBC ") == 0) firebasecihaztanitimi();
  if (satiruppercase.indexOf("IF") == 0) gotoif();
  if (satiruppercase.indexOf("BOOL") == 0) gotobool();
  // ????????????????????????????????????????????? sonra ne yaparız bilmem
}



void firebasecihaztanitimi() {
  //Serial.println("FBCihaz tanıtımı");
  for (int ii = 0; ii < 11; ii++) {
    if (satirp.indexOf("=") > 5) {
      if (fbc[ii] == "" || fbc[ii] == "null" || fbc[ii] == satirp.substring(4, satirp.indexOf("="))) {
        String fbcvefbcyol = satirp;
        fbc[ii] = fbcvefbcyol.substring(4, fbcvefbcyol.indexOf("="));
        fbcyol[ii] = fbcvefbcyol.substring(fbcvefbcyol.indexOf("=") + 1, fbcvefbcyol.indexOf(";"));
        //Serial.print("ii      ");Serial.println(ii);
        //Serial.print("FBcihaz ");Serial.println(fbc[ii]);
        //Serial.print("FBcyol  ");Serial.println(fbcyol[ii]);
        break;
      }
    } else {
      progmsg += "fbc hatası. fbc fb1=/yol/cihaz; şeklinde olmalı. satır no: " + (String)satirsayisip + " komut: " + satirp + "\n";
    }
  }
}

void gotobool() {
  String satiruppercase = satirp;
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
}


bool paranteziciislem(String parantezi) {
  String sol = "";
  String sag = "";
  String solstate;
  String sagstate;

  bool ifsonucu = false;


  Serial.print("parantezi ");
  Serial.println(parantezi);

  uint8_t op;
  if (parantezi.indexOf("==") > -1) {
    op = 1;
    sol = parantezi.substring(0, parantezi.indexOf("=="));
    sag = parantezi.substring(parantezi.indexOf("==") + 2, parantezi.length());
    if (sag.indexOf("t") == 0) { sag = sag.substring(1, sag.length()); }
    if (sag.indexOf("h") == 0) { sag = sag.substring(1, sag.length()); }
  } else if (parantezi.indexOf(">=") > -1) {
    op = 2;
    sol = parantezi.substring(0, parantezi.indexOf(">="));
    sag = parantezi.substring(parantezi.indexOf(">=") + 2, parantezi.length());
    if (sag.indexOf("t") == 0) { sag = sag.substring(1, sag.length()); }
    if (sag.indexOf("h") == 0) { sag = sag.substring(1, sag.length()); }
  } else if (parantezi.indexOf(">") > -1) {
    op = 3;
    sol = parantezi.substring(0, parantezi.indexOf(">"));
    sag = parantezi.substring(parantezi.indexOf(">") + 1, parantezi.length());
    if (sag.indexOf("t") == 0) { sag = sag.substring(1, sag.length()); }
    if (sag.indexOf("h") == 0) { sag = sag.substring(1, sag.length()); }
  } else if (parantezi.indexOf("<=") > -1) {
    op = 4;
    sol = parantezi.substring(0, parantezi.indexOf("<="));
    sag = parantezi.substring(parantezi.indexOf("<=") + 2, parantezi.length());
    if (sag.indexOf("t") == 0) { sag = sag.substring(1, sag.length()); }
    if (sag.indexOf("h") == 0) { sag = sag.substring(1, sag.length()); }
  } else if (parantezi.indexOf("<") > -1) {
    op = 5;
    sol = parantezi.substring(0, parantezi.indexOf("<"));
    sag = parantezi.substring(parantezi.indexOf("<") + 1, parantezi.length());
    if (sag.indexOf("t") == 0) { sag = sag.substring(1, sag.length()); }
    if (sag.indexOf("h") == 0) { sag = sag.substring(1, sag.length()); }
  } else if (parantezi.indexOf("!=") > -1) {
    op = 6;
    sol = parantezi.substring(0, parantezi.indexOf("!="));
    sag = parantezi.substring(parantezi.indexOf("!=") + 2, parantezi.length());
    if (sag.indexOf("t") == 0) { sag = sag.substring(1, sag.length()); }
    if (sag.indexOf("h") == 0) { sag = sag.substring(1, sag.length()); }
  } else {
    perlog += "if kıyaslama işareti uygun değil '==,>=,>,<,<=,!=' kullanın. Satır:" + (String)satirsayisip + "\n";
  }

  if (sol == "") { perlog += "Kıyaslamada sol taraf boş! Satır:" + (String)satirsayisip + "\n"; }
  if (sag == "") { perlog += "Kıyaslamada sag taraf boş! Satır:" + (String)satirsayisip + "\n"; }
  if (perlog != "") return false;
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

  if (perlog != "") return false;


  Serial.println("PARANTEZ İÇİ");
  Serial.print("sol ");
  Serial.print(sol);
  Serial.print("  ");
  Serial.print(sag);

  Serial.println(" sag");
  Serial.print("Pinstate[2] ");
  Serial.println(PinState[2]);

  Serial.print("op ");
  Serial.println(op);

  if (op == 1) {
    if (solstate.toFloat() == sag.toFloat()) ifsonucu = true;
    else ifsonucu = false;
  } else if (op == 2) {
    if (solstate.toFloat() >= sag.toFloat()) ifsonucu = true;
    else ifsonucu = false;
  } else if (op == 3) {
    if (solstate.toFloat() > sag.toFloat()) {
      ifsonucu = true;
      Serial.print("solstate ");
      Serial.print(solstate.toFloat());
      Serial.print("   sagfloat true çıktı");
      Serial.println(sag.toFloat());
    } else {
      ifsonucu = false;
      Serial.print("solfloat ");
      Serial.print(solstate.toFloat());
      Serial.print("   sagfloat false çıktı");
      Serial.println(sag.toFloat());
    }
  } else if (op == 4) {
    if (solstate.toFloat() <= sag.toFloat()) ifsonucu = true;
    else ifsonucu = false;
  } else if (op == 5) {
    if (solstate.toFloat() < sag.toFloat()) {
      ifsonucu = true;
      Serial.print("solfloat ");
      Serial.print(solstate.toFloat());
      Serial.print("   sagfloat true çıktı");
      Serial.println(sag.toFloat());
    } else {
      ifsonucu = false;
      Serial.print("solfloat ");
      Serial.print(solstate.toFloat());
      Serial.print("   sagfloat false çıktı");
      Serial.println(sag.toFloat());
    }
  } else if (op == 6) {
    if (solstate.toFloat() != sag.toFloat()) ifsonucu = true;
    else ifsonucu = false;
  }
  //Serial.print(parantezici + " ->  ");Serial.println (ifsonuc);

  //PinStatetmp[aktifpinno]=sonucdegeri;

  return ifsonucu;
}

void gotoif() {

  String satiruppercase = satirp;
  satiruppercase.toUpperCase();

  String sat = satirp;
  if (sat.indexOf("(") < 1) { perlog += "if ten sonra ( işareti olmalı. Satır:" + (String)satirsayisip + "\n"; }
  if (sat.indexOf(")") < 1) { perlog += "if te ) kapatılmamış." + (String)satirsayisip + "\n"; }
  if (perlog != "") return;
  String parantezici = sat.substring(sat.indexOf("(") + 1, sat.indexOf(")"));
  parantezici.replace(" ", "");
  int kes = 0;
  int kesv = 0;
  int kesy = 0;
  if (parantezici.indexOf("&&") > -1) kesv = parantezici.indexOf("&&");
  if (parantezici.indexOf("||") > -1) kesy = parantezici.indexOf("||");

  if (kesv == 0 && kesy == 0) kes = 0;
  else if (kesv == 0 && kesy > 0) kes = kesy;
  else if (kesv > 0 && kesy == 0) kes = kesv;
  else if (kesv > 0 && kesy > 0) {
    if (kesv < kesy) kes = kesv;
    else kes = kesy;
  }


  //Serial.print("kes >>>>: ");      Serial.println(kes);
  ifsonuc = false;
  if (kes == 0) ifsonuc = paranteziciislem(parantezici);
  else {

    bool sonis = false;
    ifsonuc = false;
    for (int j = 1; j < 5; j++) {
      kes = 0;
      kesv = 0;
      kesy = 0;
      vevar[j] = false;
      ifkiyas[j] = false;
      if (parantezici.indexOf("&&") > -1) kesv = parantezici.indexOf("&&");
      if (parantezici.indexOf("||") > -1) kesy = parantezici.indexOf("||");
      if (kesv == 0 && kesy == 0) kes = 0;
      else if (kesv == 0 && kesy > 0) {
        kes = kesy;
      } else if (kesv > 0 && kesy == 0) {
        kes = kesv;
        vevar[j] = true;
      } else if (kesv > 0 && kesy > 0) {
        if (kesv < kesy) {
          kes = kesv;
          vevar[j] = true;
        }
        if (kesv > kesy) {
          kes = kesy;
          vevar[j] = false;
        }
      }


      String isyap;
      if (kes > 0) {
        isyap = parantezici.substring(0, kes);
        parantezici = parantezici.substring(kes + 2, parantezici.length());
      } else {
        isyap = parantezici;
        sonis = true;
      }
      Serial.print("isyap >>>>: ");
      Serial.println(isyap);
      ifkiyas[j] = paranteziciislem(isyap);
      Serial.print(j);
      Serial.print("<j ifkiyas[j] = ");
      Serial.print(ifkiyas[j]);
      Serial.print(" sonrasında vevarmı: ");
      Serial.println(vevar[j]);
      kiyassayisi = j;
      if (sonis == true) break;
    }


    Serial.println(" döngü ki döngüsü aşağıdaki ");
    for (int ki = 1; ki < kiyassayisi; ki++) {

      Serial.print(ki);
      Serial.print("<ki ifkiyas[ki+1] = ifkiyas[ki]");
      Serial.print(ifkiyas[ki]);
      Serial.println(ifkiyas[ki + 1]);
      Serial.print("  vevar[ki]    ");
      Serial.println(vevar[ki]);

      if (vevar[ki] == true) {
        if (ifkiyas[ki + 1] == true && ifkiyas[ki] == true) ifkiyas[ki + 1] = true;
        else ifkiyas[ki + 1] = false;
      } else {
        if (ifkiyas[ki + 1] == true || ifkiyas[ki] == true) ifkiyas[ki + 1] = true;
        else ifkiyas[ki + 1] = false;
      }
      ifsonuc = ifkiyas[ki + 1];
    }
  }


  if (ifsonuc == true) ifparantezdisi(satiruppercase, satirsayisip);
}
















void ifparantezdisi(String satiruppercase, int satirsayisip) {
  String yapilacaklar;
  String yapilacaklarn;
  String yapilacakis;
  String yapilacakisn;
  int yapilacaklarislemsayisi;
  String parantezdisisol;
  String parantezdisisag;
  //String
  String satirnormal = satiruppercase;

  satiruppercase.toUpperCase();
  yapilacaklar = satiruppercase.substring(satiruppercase.indexOf(")") + 1, satiruppercase.length());
  yapilacaklarn = satirnormal.substring(satirnormal.indexOf(")") + 1, satirnormal.length());
  if (yapilacaklar.indexOf("{") > -1) {
    //Serial.print("ptm:");Serial.println(ptm);
    yapilacaklar = ptm.substring(ptm.indexOf("{") + 1, ptm.indexOf("}"));
    yapilacaklarn = ptm.substring(ptm.indexOf("{") + 1, ptm.indexOf("}"));
    //  Serial.print("yapilacaklar:");
    //  Serial.println(yapilacaklar);
    yapilacaklar.replace("\n", "");
    yapilacaklarn.replace("\n", "");
  } else {
    ptm = ptm.substring(ptm.indexOf("\n") + 1, ptm.length());
  }
  //Serial.print("programdata:");
  //Serial.println(programdata);

  //Serial.print("ptm:");
  //Serial.println(ptm);
  Serial.print("yapilacaklar:");
  Serial.println(yapilacaklar);
  //sonsatir belli;


  // boşlukları sil
  if (yapilacaklar.indexOf(";") > -1) {
    for (int i = 1; i < 11; i++) {

      if (yapilacaklar.indexOf(" ") == 0) {
        for (int j = 1; j < 100; j++) {
          yapilacaklar = yapilacaklar.substring(1, yapilacaklar.length());
          yapilacaklarn = yapilacaklar.substring(1, yapilacaklar.length());
          if (yapilacaklar.indexOf(" ") != 0) break;
        }
      }  //baştaki boşlukları sil

      yapilacakis = yapilacaklar.substring(0, yapilacaklar.indexOf(";"));
      yapilacakisn = yapilacaklarn.substring(0, yapilacaklarn.indexOf(";"));
      yapilacaklarislemsayisi = i;
      //Serial.print("yapılacak ");
      //Serial.println(yapilacakis);
      //Serial.print("yapilacaklarislemsayisi ");
      //Serial.println(yapilacaklarislemsayisi);
      // tam burada yapılacak hesabına git
      yap(yapilacakisn, yapilacaklarislemsayisi);
      yapilacaklar = yapilacaklar.substring(yapilacaklar.indexOf(";") + 1, yapilacaklar.length());
      yapilacaklarn = yapilacaklarn.substring(yapilacaklarn.indexOf(";") + 1, yapilacaklarn.length());
      if (yapilacaklar.length() < 1) { break; }
    }
  } else {
    perlog += (String)satirsayisip + ". satırda / satır sonunda ';' unutulmuş.\n";
    return;
  }
}

void yap(String yapilacakn, int islemno) {
  //Serial.print("yapılacak  ");
  //Serial.println(yapilacak);
  //Serial.print("  işlem no  ");
  //Serial.println(islemno);

  String noktalivirgulekadar = yapilacakn;
  String dsol = noktalivirgulekadar.substring(0, noktalivirgulekadar.indexOf("="));
  String dsoln = noktalivirgulekadar.substring(0, noktalivirgulekadar.indexOf("="));
  dsol.toUpperCase();
  String dsag = noktalivirgulekadar.substring(noktalivirgulekadar.indexOf("=") + 1, noktalivirgulekadar.indexOf(";"));
  for (int indis = 0; indis < 21; indis++)  // her islem için döngü
  {
    if (indis < 11) {
      String fbcupercase = fbc[indis];
      fbcupercase.toUpperCase();
      //if(indis<2)Serial.print("dsol ve fbc :");Serial.println(dsol + "   " + fbcupercase);
      if (dsol == fbcupercase) {
        //if(indis<2)Serial.print("efbtd ve fbtd :");Serial.println(efbtd[indis] + "   " + fbtd[indis]);
        fbtd[indis] = dsag;
        if (efbtd[indis] != fbtd[indis]) {
          //  Serial.print("dsol ve fbc :");Serial.println(dsol + "   " + fbcupercase);
          //efbtd[indis] = dsag;
          progmsg += (String)satirsayisip + " satır>" + yapilacakn + " degisti.<br>";
          //  Serial.print(fbcyol[indis] + " ------> ");Serial.println(fbtd[indis]);
          zamanfark = 1770;
        }
      }

      if (dsol == degis[indis]) {
        degdeg[indis] = dsag;
        PinState[indis] = dsag;
        progmsg += (String)satirsayisip + " satır>" + yapilacakn + " degisti.<br>";
        //Serial.print(pinname[indis] + " ------> ");Serial.println(degis[indis]);
        //Serial.print(pinname[indis] + " ------> ");Serial.println(dsag);
      }
    }
    if (indis >= 11 && indis < 30)  // degiskenleri tut
    {
      if (dsol == degis[indis]) {
        degdeg[indis] = dsag;
        progmsg += (String)satirsayisip + " satır>" + yapilacakn + " degisti.<br>";
        //Serial.print(pinname[indis] + " ------> ");Serial.println(degis[indis]);
      }
    }

    // 0-10  PİN     11-30 degisken    31-50 booldegisken  51-70 boolsonuc
  }
}

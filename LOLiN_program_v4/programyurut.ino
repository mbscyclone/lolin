  String satirp[100];
  String PinStatetmp[10];

  String boolname[10];
  int boolstate[10];

  int satirsayisip;
  uint8_t ifsonuc;
  String parantezici;

  int aktifpinno;
  int aktifboolno;

void programrun()
{






  for(int i=0;i<11;i++)
  {
    PinStatetmp[i]=PinState[i];
    boolname[i]="";
    boolstate[i]=255;
  }

      progmsg= "";

  perlog="";
  String ptm=programdata;
  for(int q=1;q<100;q++)
  {
    satirsayisip=q;
    if(ptm.length()<3)break;
    satirp[q]=ptm.substring(0,ptm.indexOf("\n"));
    ptm=ptm.substring(ptm.indexOf("\n")+1,ptm.length());
    //Serial.println("satirp "); Serial.println(satirp[q]);
    satirislem();
    if(perlog!="")return;
  }

// en son işlem burası //////////////////////////////////
    for (int sta=0;sta<pinsayisi+1;sta++)
    {
      PinState[sta]=PinStatetmp[sta];
      //Serial.print(pinname[sta] + " pinstate:");Serial.println(PinStatetmp[sta]);
    }
////////////////////////////////////////////////////////
}

void satirislem()
{
  String satiruppercase =satirp[satirsayisip]; satiruppercase.toUpperCase();
  //Serial.println(satiruppercase);
  // if için ///////////////////////////////////////////
  
  if(satiruppercase.indexOf("//")==0)return;
  if(satiruppercase.indexOf("IF")==0)gotoif();
  if(satiruppercase.indexOf("BOOL")==0)gotobool();

  // ????????????????????????????????????????????? sonra ne yaparız bilmem



}

void gotobool()
{
  String satiruppercase =satirp[satirsayisip]; satiruppercase.toUpperCase();
  String boolsonrasi=satiruppercase.substring(5,satiruppercase.length());
  boolsonrasi.trim();
String boolnametmp;
int boolstatetmp;

  if(boolsonrasi.indexOf("=")>-1)
  {
    boolnametmp=boolsonrasi.substring(0,boolsonrasi.indexOf("="));
    boolstatetmp=(boolsonrasi.substring(boolsonrasi.indexOf("=")+1,boolsonrasi.length()-1)).toInt();
    Serial.print(boolnametmp);Serial.println(boolstatetmp);
  }

  if(boolsonrasi.indexOf("=")<0)
  {
    boolnametmp=boolsonrasi.substring(0,boolsonrasi.indexOf(";"));
    boolstatetmp=0;
    Serial.print(boolnametmp);Serial.println(boolstatetmp);
  }


  for (int j=0;j<11;j++)
  {
    if(boolname[j]==boolnametmp)
    {
      boolstate[j]=boolstatetmp;
      break;
    }
    if(boolname[j]==""){boolname[j]=boolnametmp;boolstate[j]=boolstatetmp;break;}
  }
}

void gotoif()
{
  String sol="";
  String sag="";
  String solstate;
  String sagstate;
  ifsonuc=2;

  String sat=satirp[satirsayisip];
  if(sat.indexOf("(")<1){perlog += "if ten sonra ( işareti olmalı. Satır:" + (String)satirsayisip + "\n";}
  if(sat.indexOf(")")<1){perlog += "if te ) kapatılmamış." + (String)satirsayisip + "\n";}
  if(perlog!="")return;
  String parantezici=sat.substring(sat.indexOf("(")+1,sat.indexOf(")"));
  parantezici.trim();
  //Serial.print("parantezici ");Serial.println(parantezici);

uint8_t op;
if(parantezici.indexOf("==")>-1)
{
  op=1;
  sol=parantezici.substring(0,parantezici.indexOf("=="));
  sag=parantezici.substring(parantezici.indexOf("==")+2,parantezici.length());
  if(sag.indexOf("t")==0){sag=sag.substring(1,sag.length());}
  if(sag.indexOf("h")==0){sag=sag.substring(1,sag.length());}
}else
if(parantezici.indexOf(">=")>-1)
{
  op=2;
  sol=parantezici.substring(0,parantezici.indexOf(">="));
  sag=parantezici.substring(parantezici.indexOf(">=")+2,parantezici.length());
  if(sag.indexOf("t")==0){sag=sag.substring(1,sag.length());}
  if(sag.indexOf("h")==0){sag=sag.substring(1,sag.length());}
}else
if(parantezici.indexOf(">")>-1)
{
  op=3;
  sol=parantezici.substring(0,parantezici.indexOf(">"));
  sag=parantezici.substring(parantezici.indexOf(">")+1,parantezici.length());
  if(sag.indexOf("t")==0){sag=sag.substring(1,sag.length());}
  if(sag.indexOf("h")==0){sag=sag.substring(1,sag.length());}
}else
if(parantezici.indexOf("<=")>-1)
{
  op=4;
  sol=parantezici.substring(0,parantezici.indexOf("<="));
  sag=parantezici.substring(parantezici.indexOf("<=")+2,parantezici.length());
  if(sag.indexOf("t")==0){sag=sag.substring(1,sag.length());}
  if(sag.indexOf("h")==0){sag=sag.substring(1,sag.length());}
}else
if(parantezici.indexOf("<")>-1)
{
  op=5;
  sol=parantezici.substring(0,parantezici.indexOf("<"));
  sag=parantezici.substring(parantezici.indexOf("<")+1,parantezici.length());
  if(sag.indexOf("t")==0){sag=sag.substring(1,sag.length());}
  if(sag.indexOf("h")==0){sag=sag.substring(1,sag.length());}
}else
if(parantezici.indexOf("!=")>-1)
{
  op=6;
  sol=parantezici.substring(0,parantezici.indexOf("!="));
  sag=parantezici.substring(parantezici.indexOf("!=")+2,parantezici.length());
  if(sag.indexOf("t")==0){sag=sag.substring(1,sag.length());}
  if(sag.indexOf("h")==0){sag=sag.substring(1,sag.length());}
}else{
  perlog += "if kıyaslama işareti uygun değil '==,>=,>,<,<=,!=' kullanın. Satır:" + (String)satirsayisip + "\n";
}

if(sol=="") {perlog += "Kıyaslamada sol taraf boş! Satır:" + (String)satirsayisip + "\n";}
if(sag=="") {perlog += "Kıyaslamada sag taraf boş! Satır:" + (String)satirsayisip + "\n";}
if(perlog!="")return;
//Serial.print("sol: "); Serial.println(sol);
  Serial.print("sag: "); Serial.println(sag);
aktifpinno=-10000;
aktifboolno=-255;
    for (int boolbul=0;boolbul<11;boolbul++)
    { //Serial.print("pinname: "); Serial.println(pinname[pinbul]);
      if(sol==boolname[boolbul])
      {
      solstate=boolstate[boolbul];
      aktifboolno=boolbul;
      break;
      }
    }


    for (int pinbul=0;pinbul<11;pinbul++)
    { //Serial.print("pinname: "); Serial.println(pinname[pinbul]);
      if(sol==pinname[pinbul])
      {
      solstate=PinState[pinbul];
      aktifpinno=pinbul;
      break;
      }
    }


if(aktifpinno == -10000 && aktifboolno == 255) {perlog += "if içi soldaki tanımlı değil " + sol + " Satır:" +  (String)satirsayisip + "\n";}

if(perlog!="")return;




String satiruppercase =satirp[satirsayisip]; satiruppercase.toUpperCase();
String parantezdisisol=satiruppercase.substring(satiruppercase.indexOf(")")+1,satiruppercase.indexOf(";"));
parantezdisisol=parantezdisisol.substring(0,parantezdisisol.indexOf("="));

bool var=false;
    for (int pinbul=0;pinbul<11;pinbul++)
    {
      //Serial.print("pinname ");Serial.println(pinname[pinbul]);
      if(parantezdisisol==pinname[pinbul])
      {
        var=true;
      break;
      }
    }
if(var==false) {perlog += "if dışı soldaki pin yok " + parantezdisisol + " Satır:" +  (String)satirsayisip + "\n";}
if(perlog!="")return;

    

//Serial.print("op ");Serial.println(op);

if(op==1)
{
  if(solstate.toFloat()==sag.toFloat())ifsonuc = 1; 
  else ifsonuc =  0;
}else
if(op==2)
{
  if(solstate.toFloat()>=sag.toFloat())ifsonuc =  1; 
  else ifsonuc =  0;
}else
if(op==3)
{
  if(solstate.toFloat() > sag.toFloat()) ifsonuc =  1; 
  else ifsonuc =  0;
}else
if(op==4)
{
  if(solstate.toFloat()<=sag.toFloat())ifsonuc =  1; 
  else ifsonuc =  0;
}else
if(op==5)
{
  if(solstate.toFloat()<sag.toFloat())ifsonuc =  1; 
  else ifsonuc =  0;
}else
if(op==6)
{
  if(solstate.toFloat()!=sag.toFloat())ifsonuc =  1; 
  else ifsonuc =  0;
}
//Serial.print(parantezici + " ->  ");Serial.println (ifsonuc);

//PinStatetmp[aktifpinno]=sonucdegeri;
  satiruppercase =satirp[satirsayisip]; satiruppercase.toUpperCase();
  parantezdisisol=satiruppercase.substring(satiruppercase.indexOf(")")+1,satiruppercase.indexOf(";"));
  String parantezdisisag=parantezdisisol.substring(parantezdisisol.indexOf("=")+1,parantezdisisol.length());
  parantezdisisol=parantezdisisol.substring(0,parantezdisisol.indexOf("="));
  //Serial.print("parantezdisisol ");Serial.println(parantezdisisol + "  " + parantezdisisag);

  if(ifsonuc==1){
      for (int pinbu=0;pinbu<11;pinbu++)
      {
        if(parantezdisisol==pinname[pinbu])
        {
          PinStatetmp[pinbu]= parantezdisisag;
          progmsg+= pinname[pinbu] + " " + satirp[satirsayisip] + " yuzunden degisti. program satiri: "+ (String)satirsayisip + "\n";
          //Serial.print(pinname[pinbu] + " ------> ");Serial.println(PinStatetmp[pinbu]);
          break;
        }
      }
  }

}

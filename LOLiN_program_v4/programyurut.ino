String satirp[100];
int satirsayisip;

uint8_t ifsonuc;
String parantezici;

String PinStatetmp[10];
int aktifpinno;



void programrun()
{
  for(int i=0;i<11;i++)
  {
    PinStatetmp[i]=PinState[i];
  }


  String ptm=programdata;
  for(int q=1;q<100;q++)
  {
    satirsayisip=q;
    if(ptm.length()<3)break;
    satirp[q]=ptm.substring(0,ptm.indexOf("\n"));
    ptm=ptm.substring(ptm.indexOf("\n")+1,ptm.length());
    //Serial.println("satirp "); Serial.println(satirp[q]);
    satirislem();
  }

// en son işlem burası //////////////////////////////////
    for (int sta=0;sta<pinsayisi+1;sta++)
    {
      PinState[sta]=PinStatetmp[sta];
      Serial.print(pinname[sta] + " pinstate:");Serial.print(PinStatetmp[sta]);
    }
////////////////////////////////////////////////////////
}

void satirislem()
{
  String satirpuppercase =satirp[satirsayisip]; satirpuppercase.toUpperCase();
  //Serial.println(satirpuppercase);
  // if için ///////////////////////////////////////////
  if(satirpuppercase.indexOf("IF")==0)gotoif();
  // ????????????????????????????????????????????? sonra ne yaparız bilmem



}

void gotoif()
{
  String sol="";
  String sag="";
  String solstate;
  String sagstate;
  ifsonuc=2;

  String sat=satirp[satirsayisip];
  String parantezici=sat.substring(sat.indexOf("(")+1,sat.indexOf(")"));
  parantezici.trim();
  Serial.print("parantezici ");Serial.println(parantezici);

uint8_t op;
if(parantezici.indexOf("==")>-1)
{
  op=1;
  sol=parantezici.substring(0,parantezici.indexOf("=="));
  sag=parantezici.substring(parantezici.indexOf("==")+2,parantezici.length());
}else
if(parantezici.indexOf(">=")>-1)
{
  op=2;
  sol=parantezici.substring(0,parantezici.indexOf(">="));
  sag=parantezici.substring(parantezici.indexOf(">=")+2,parantezici.length());
}else
if(parantezici.indexOf(">")>-1)
{
  op=3;
  sol=parantezici.substring(0,parantezici.indexOf(">"));
  sag=parantezici.substring(parantezici.indexOf(">")+1,parantezici.length());
}else
if(parantezici.indexOf("<=")>-1)
{
  op=4;
  sol=parantezici.substring(0,parantezici.indexOf("<="));
  sag=parantezici.substring(parantezici.indexOf("<=")+2,parantezici.length());
}else
if(parantezici.indexOf("<")>-1)
{
  op=5;
  sol=parantezici.substring(0,parantezici.indexOf("<"));
  sag=parantezici.substring(parantezici.indexOf("<")+1,parantezici.length());
}else
if(parantezici.indexOf("!=")>-1)
{
  op=6;
  sol=parantezici.substring(0,parantezici.indexOf("!="));
  sag=parantezici.substring(parantezici.indexOf("!=")+2,parantezici.length());
}

Serial.print("sol: "); Serial.println(sol);

    for (int pinbul=0;pinbul<11;pinbul++)
    {
      if(sol==pinname[pinbul])
      {
      solstate=PinState[pinbul];
      aktifpinno=pinbul;
      break;
      }
    }

Serial.print("op ");Serial.println(op);

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
Serial.print(parantezici + " ->  ");Serial.println (ifsonuc);

//PinStatetmp[aktifpinno]=sonucdegeri;
String satirpuppercase =satirp[satirsayisip]; satirpuppercase.toUpperCase();
String parantezdisisol=satirpuppercase.substring(satirpuppercase.indexOf(")")+1,satirpuppercase.indexOf(";"));
String parantezdisisag=parantezdisisol.substring(parantezdisisol.indexOf("=")+1,parantezdisisol.length());
parantezdisisol=parantezdisisol.substring(0,parantezdisisol.indexOf("="));
Serial.print("parantezdisisol ");Serial.println(parantezdisisol + "  " + parantezdisisag);

if(ifsonuc==1){
    for (int pinbu=0;pinbu<11;pinbu++)
    {
      if(parantezdisisol==pinname[pinbu])
      {
        PinStatetmp[pinbu]= parantezdisisag;
        Serial.print(pinname[pinbu] + " pinstatetmp ppppppppppppppppppppppp :");Serial.println(PinStatetmp[pinbu]);
        break;
      }
    }
}

}

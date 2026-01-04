unsigned long duration=200;
double frequency;
void play(String melody)
{
      for(int ml=0;ml<melody.length()+1;ml++)
      {
          String nota=melody.substring(ml,ml+1);
          Serial.println("nota: " + nota);
                 if(nota=="Y")frequency=130.8;
            else if(nota=="U")frequency=146.8;
            else if(nota=="I")frequency=164.8;
            else if(nota=="O")frequency=174.6;
            else if(nota=="H")frequency=196;
            else if(nota=="J")frequency=220;
            else if(nota=="K")frequency=246.9;
            else if(nota=="C")frequency=261.8;
            else if(nota=="D")frequency=293.7;
            else if(nota=="E")frequency=329.6;
            else if(nota=="F")frequency=349.2;
            else if(nota=="G")frequency=392;
            else if(nota=="A")frequency=440;
            else if(nota=="B")frequency=493.9;
            else if(nota=="1")frequency=523.3;//987.8; // 7  // B
            else if(nota=="2")frequency=698.5;//587.3; // 4  // F
            else if(nota=="3")frequency=659.3;//698.5; // 2  // D
            else if(nota=="4")frequency=587.3;//784;  // 5  // G
            else if(nota=="5")frequency=784;//523.3;  // 1  // C
            else if(nota=="6")frequency=880;//659.3;  // 3  //E
            else if(nota=="7")frequency=987.8;//880;  //6   // A
            else if(nota=="_")frequency=0;
            else frequency=0;
           
           if(frequency!=0) tone(PIN_TONE, frequency, duration);
           delay(200);
           noTone(PIN_TONE);
      }
  noTone(PIN_TONE);
}

/*
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
*/


unsigned long duration = 100;
double frequency;

void play(String melody) {
if(melody.length()<1)return;
    duration=(100/(melody.length()));
    for (int ml = 0; ml < melody.length(); ml++) {
        char nota = melody.charAt(ml);  // Tek karakter al

        switch (nota) {
            case 'Y': frequency = 130.8; break;
            case 'U': frequency = 146.8; break;
            case 'I': frequency = 164.8; break;
            case 'O': frequency = 174.6; break;
            case 'H': frequency = 196;   break;
            case 'J': frequency = 220;   break;
            case 'K': frequency = 246.9; break;
            case 'C': frequency = 261.8; break;
            case 'D': frequency = 293.7; break;
            case 'E': frequency = 329.6; break;
            case 'F': frequency = 349.2; break;
            case 'G': frequency = 392;   break;
            case 'A': frequency = 440;   break;
            case 'B': frequency = 493.9; break;
            case '1': frequency = 523.3; break; // Özel mapping
            case '2': frequency = 698.5; break;
            case '3': frequency = 659.3; break;
            case '4': frequency = 587.3; break;
            case '5': frequency = 784;   break;
            case '6': frequency = 880;   break;
            case '7': frequency = 987.8; break;
            case '_': frequency = 0;     break; // Sessizlik
            default:  frequency = 0;     break;
        }

        if (frequency != 0) {
            tone(PIN_TONE, frequency, duration);
        }
        delay(duration);   // nota süresi kadar bekle
        noTone(PIN_TONE);  // sesi kes
    }
}

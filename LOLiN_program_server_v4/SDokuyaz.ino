//
// printdirectory files başı

void printDirectory(File dir, int numTabs) {
  while (true) {

    File entry = dir.openNextFile();
    if (!entry) {
      // no more files
      break;
    }
    for (uint8_t i = 0; i < numTabs; i++) { Serial.print('\t'); }
    Serial.print(entry.name());
    if (entry.isDirectory()) {
      Serial.println("/");
      printDirectory(entry, numTabs + 1);
    } else {
      // files have sizes, directories do not
      Serial.print("\t\t");
      Serial.print(entry.size(), DEC);
      time_t cr = entry.getCreationTime();
      time_t lw = entry.getLastWrite();
      struct tm* tmstruct = localtime(&cr);
      Serial.printf("\tCREATION: %d-%02d-%02d %02d:%02d:%02d", (tmstruct->tm_year) + 1900, (tmstruct->tm_mon) + 1, tmstruct->tm_mday, tmstruct->tm_hour, tmstruct->tm_min, tmstruct->tm_sec);
      tmstruct = localtime(&lw);
      Serial.printf("\tLAST WRITE: %d-%02d-%02d %02d:%02d:%02d\n", (tmstruct->tm_year) + 1900, (tmstruct->tm_mon) + 1, tmstruct->tm_mday, tmstruct->tm_hour, tmstruct->tm_min, tmstruct->tm_sec);
    }
    entry.close();
  }
}

// printdirectory files sonu



void SDyaz(String filepath,String sdyeyazilacak){

String dd;
String filename=filepath+zaman.substring(0,6)+"/"+zaman.substring(6,8)+".txt";
  mySdFile = SD.open(filename, FILE_WRITE);
  // if the file opened okay, write to it:
  dd=zaman+" " + sdyeyazilacak;
  if (mySdFile) {
    mySdFile.println(dd);
    // close the file:

    
    Serial.println(zaman);
    Serial.println();
    Serial.println(sdyeyazilacak);
    Serial.println();
    SERVERlogbuf+= zaman+" " + sdyeyazilacak +"\n";
    String testbuf=SERVERlogbuf;
    testbuf.replace("\n","");
    int fark=SERVERlogbuf.length()-testbuf.length();
    if(fark>20)
    {
      SERVERlogbuf = SERVERlogbuf.substring((SERVERlogbuf.indexOf("\n")+1),SERVERlogbuf.length());
    }
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening SERVERlog.txt");
  }
      mySdFile.close();
}


/*
void SDoku(String filename){
  String dosyaicerigi;
dosyaicerigi="";
  // re-open the file for reading:
  mySdFile = SD.open(filename, FILE_READ);
  if (mySdFile) {
    Serial.println(filename+":");

    // read from the file until there's nothing else in it:
    while (mySdFile.available()) 
    {
        dosyaicerigi=mySdFile.readString();

        if(dosyaicerigi.length()>50){
          dosyaicerigi.substring(dosyaicerigi.length()-50,dosyaicerigi.length());
        }
        Serial.println(dosyaicerigi);
        SERVERlogbuf=dosyaicerigi;
        eSERVERlogbuf=dosyaicerigi;
    // close the file:
    }

  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }
    mySdFile.close();
}
*/



/*
void SDoku(String filename){
  String okusatir;
  String biriktir_okusatir;
  String eskidosyadakalsin;
  int satirsayisi;
  // re-open the file for reading:
  mySdFile = SD.open(filename, FILE_READ);
  if (mySdFile) {
    Serial.println(filename+":");

    // read from the file until there's nothing else in it:
    while (mySdFile.available()) 
    {
      for(int sdfs=1;sdfs<1000;sdfs++)
      {
        okusatir=mySdFile.readStringUntil('\n');
        Serial.println(okusatir);
        if(biriktir_okusatir.length()<=100000){biriktir_okusatir+=okusatir;}
        if(biriktir_okusatir.length()>100000){eskidosyadakalsin=true}
        if(okusatir.length()<1) satirsayisi = sdfs;
      }
    }

if(eskidosyadakalsin==true){
    String eskidosya_filename=("/"+zaman.substring(0,zaman.length()-2)+"_mqserlog.txt";
    SDyaz(eskidosya_filename, String biriktir_okusatir);
    mySdFile.close();
    SD.remove(mySdFile);
}


    // close the file:
    mySdFile.close();
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }
}
*/

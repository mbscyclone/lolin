
//
// printdirectory files başı
  #include <SdFat.h>

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

  if (sd.begin(D8, SPI_HALF_SPEED)) {
    Serial.println("sd.card size byte:");Serial.println(sd.card()->sectorCount() * 512);
    sdsize=sd.card()->sectorCount() * 512;
    Serial.println("sd.card free byte:");Serial.println(sd.vol()->freeClusterCount() * sd.vol()->sectorsPerCluster() * 512);
    sdfree=sd.vol()->freeClusterCount() * sd.vol()->sectorsPerCluster() * 512;
    //sd.ls(LS_SIZE);
  }
  if (sdfree >0 && sdfree < 10000000) {
  deleteOldestLog();
}


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
    if(fark>10)
    {
      SERVERlogbuf = SERVERlogbuf.substring((SERVERlogbuf.indexOf("\n")+1),SERVERlogbuf.length());
    }
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening SERVERlog.txt");
  }
      mySdFile.close();
}



void deleteOldestLog() {
  File root = SD.open("/serverlog/");   // root dizini aç
  String oldestFolder = "";
  
  // Root içindeki klasörleri tara
  while (true) {
    File entry = root.openNextFile();
    if (!entry) break; // klasör kalmadı
    
    if (entry.isDirectory()) {
      String folderName = entry.name();
      // İlk klasörü al veya daha küçük tarihli olanı seç
      if (oldestFolder == "" || folderName < oldestFolder) {
        oldestFolder = folderName;
      }
    }
    entry.close();
  }
  root.close();

  if (oldestFolder != "") {
    // En eski klasörü aç
    File oldDir = SD.open("/serverlog/" + oldestFolder);
    while (true) {
      File file = oldDir.openNextFile();
      if (!file) break;
      String fileName = file.name();
      file.close();
      SD.remove("/serverlog/" + oldestFolder + "/" + fileName); // dosyaları sil
    }
    oldDir.close();
    SD.rmdir("/serverlog/" + oldestFolder); // klasörü sil
    Serial.println("Silindi: " + oldestFolder);
  }
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
        okusatir=mySdFile.readStringUntil('\n');
        Serial.println(okusatir);
    }

/*
if(eskidosyadakalsin==true){
    String eskidosya_filename=("/"+zaman.substring(0,zaman.length()-2)+"_mqserlog.txt";
    SDyaz(eskidosya_filename, String biriktir_okusatir);
    mySdFile.close();
    SD.remove(mySdFile);
}
*/

    // close the file:
    mySdFile.close();
  } else {
    // if the file didn't open, print an error:
    Serial.println(filename + "  error opening..");
  }
}


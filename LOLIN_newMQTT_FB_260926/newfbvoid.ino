

// 1. NOKTA ATIŞI VERİ GÜNCELLEME (PUT) FONKSİYONU
void firebasePutData(const char* url, String stringVeri) {
  fbisleniyor=true;
  WiFiClientSecure client;
  client.setInsecure(); // RAM dostu SSL ayarı

  HTTPClient http;
  http.begin(client, url);
  http.addHeader("Content-Type", "application/json");

  // Veriyi Firebase formatına uygun hale getirmek için çift tırnak içine alıyoruz
  String payload = "\"" + stringVeri + "\"";

  // PUT kullanarak doğrudan verinin üzerine yazıyoruz (Sabit anahtar yapısı için)
  int httpResponseCode = http.PUT(payload); 

  if (httpResponseCode > 0) {
    Serial.printf("Yazma Başarılı! Kod: %d\n", httpResponseCode);
  } else {
    Serial.printf("Yazma Hatası: %s\n", http.errorToString(httpResponseCode).c_str());
  }
  http.end();
    fbisleniyor=false;
}

// 2. NOKTA ATIŞI VERİ OKUMA (GET) FONKSİYONU
String firebaseGetData(const char* url) {
  fbisleniyor=true;
  WiFiClientSecure client;
  client.setInsecure();

  HTTPClient http;
  http.begin(client, url);

  int httpResponseCode = http.GET(); 
  String sonuc = "";

  if (httpResponseCode == 200) {
    sonuc = http.getString();
    
    // Firebase'den gelen verinin başındaki ve sonundaki çift tırnakları temizliyoruz
    if(sonuc.startsWith("\"") && sonuc.endsWith("\"")) {
      sonuc = sonuc.substring(1, sonuc.length() - 1);
    }
  } else {
    Serial.printf("Okuma Hatası: %s\n", http.errorToString(httpResponseCode).c_str());
  }
  http.end();
    fbisleniyor=false;
  return sonuc; // Temizlenmiş String'i döndürür
}

/*
void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    

    
    Serial.println("\n>>> Dinamik Adrese Pin Durumları Güncelleniyor...");
    String dat = "D1:0,D2:1,D3:0,D6:0,D7:1,";
    
    // .c_str() kullanarak String nesnesini const char* tipine dönüştürüyoruz
    firebasePutData(tamUrl.c_str(), dat); 

    delay(3000);

    Serial.println("\n>>> Dinamik Adresten Paylaşım Bilgisi Okunuyor...");
    String payYolu = "kev1/pays/MUTFAKpay";
    String tamPayUrl = anaUrl + payYolu + ".json";
    
    String mutfakAyarlari = firebaseGetData(tamPayUrl.c_str());
    Serial.print("Gelen Metin: ");
    Serial.println(mutfakAyarlari);
  }
  
  delay(20000);
}
*/
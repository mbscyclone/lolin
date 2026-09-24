//card info: AI Thinker ESP32-CAM... 3mb huge ram no ota

#include "esp_camera.h"
#include <WiFi.h>

#include <WiFiClientSecure.h>
#include <esp_timer.h>
#include <img_converters.h>
#include <Arduino.h>
#include "fb_gfx.h"
#include "camera_index.h"
#include "esp_http_server.h"
WiFiClientSecure clientTCP;
// ===========================
// Select camera model in board_config.h
// ===========================
#include "board_config.h"

#include "LittleFS.h"
// ===========================
// Enter your WiFi credentials
// ===========================

String ssid = "";
String pass = "";
int rescanwifi = 0;
unsigned int zamanfark;
unsigned long reConnectsayac = millis();

int hassasiyet=10;

//telegram bot link="t.me/kev1_bot";
bool telegram_hazir = false;


/*
// PIR sensor
//#define PIR_PIN 3
unsigned long lastMotionTime = 0;
const unsigned long motionCooldown = 15000;  // 15 seconds
*/


// --- Yazılımsal Hareket Algılama Ayarları ---
unsigned long lastMotionTime = 0;
unsigned long motionCooldown = 15000; // İstediğiniz gibi 15 saniye cooldown

// Karşılaştırma için bir önceki karenin piksellerini tutacağımız değişkenler
size_t prev_len = 0;
uint8_t *prev_buf = NULL;

// Hassasiyet Ayarları (Kendinize göre değiştirebilirsiniz)
#define MOTION_THRESHOLD 15   // Piksel değerindeki değişim eşiği (0-255 arası)
#define MOTION_PERCENTAGE 10  // Görüntünün yüzde kaçı değişirse hareket sayılsın? (%10)



bool WiFiAP = true;  // Do yo want the ESP as AP?

File dosya;

int Menu = 0;
String header;
String creator;

String esphostnameOnek = "E32CAMAIT";
String esphostname = "";
String YOL;

//NetworkServer server(8080);
WiFiServer htserver(8080);

void startCameraServer();
void setupLedFlash();

String telegram_botToken;  //= "8327870196:AAEjrwZMHcTuOXehzge7m5uk5VU2jmyTUg8"; // [BotFather] /start >>> /addnewbot >>> name kev1_bot >> //HTTP_API
String telegram_chatID;    //= "8411559509"; // [Chat I'd Info Bot] /start >>> name: Murat BEKTAŞ username: @Muratbk_141 chatid:8411559509

// Fonksiyonun başına durumMesaji parametresini ekledik
void sendPhotoTelegram(camera_fb_t *fb, String durumMesaji) {
  if (WiFi.status() != WL_CONNECTED) return;

  clientTCP.stop();
  clientTCP.setInsecure();
  if (!clientTCP.connect("api.telegram.org", 443)) {
    Serial.println("Telegram connection failed");
    return;
  }
  String boundary = "ESP32CAMBOUNDARY";
  String startRequest = "--" + boundary + "\r\n";
  startRequest += "Content-Disposition: form-data; name=\"chat_id\"\r\n\r\n";
  startRequest += telegram_chatID + "\r\n--" + boundary + "\r\n";
  startRequest += "Content-Disposition: form-data; name=\"caption\"\r\n\r\n";
  
  // SABİT METİN YERİNE BURAYA dinamik gelen durumMesaji değişkenini bağlıyoruz:
  startRequest += esphostname + " -> " + durumMesaji + "\r\n--" + boundary + "\r\n";

  startRequest += "Content-Disposition: form-data; name=\"photo\"; filename=\"image.jpg\"\r\n";
  startRequest += "Content-Type: image/jpeg\r\n\r\n";
  String endRequest = "\r\n--" + boundary + "--\r\n";

  int contentLength = startRequest.length() + fb->len + endRequest.length();

  String headers = "POST /bot" + String(telegram_botToken) + "/sendPhoto HTTP/1.1\r\n";
  headers += "Host: api.telegram.org\r\n";
  headers += "Content-Type: multipart/form-data; boundary=" + boundary + "\r\n";
  headers += "Content-Length: " + String(contentLength) + "\r\n\r\n";

  clientTCP.print(headers);
  clientTCP.print(startRequest);
  clientTCP.write(fb->buf, fb->len);
  clientTCP.print(endRequest);
  delay(500);
  while (clientTCP.connected()) {
    String line = clientTCP.readStringUntil('\n');
    if (line == "\r") break;
  }

  clientTCP.stop();
  Serial.println("📸 Photo sent to Telegram");
}


esp_err_t err;
void setup() {
  Serial.begin(115200);
  Serial.setDebugOutput(true);
  Serial.println();

  camera_config_t config;
  config.ledc_channel = LEDC_CHANNEL_0;
  config.ledc_timer = LEDC_TIMER_0;
  config.pin_d0 = Y2_GPIO_NUM;
  config.pin_d1 = Y3_GPIO_NUM;
  config.pin_d2 = Y4_GPIO_NUM;
  config.pin_d3 = Y5_GPIO_NUM;
  config.pin_d4 = Y6_GPIO_NUM;
  config.pin_d5 = Y7_GPIO_NUM;
  config.pin_d6 = Y8_GPIO_NUM;
  config.pin_d7 = Y9_GPIO_NUM;
  config.pin_xclk = XCLK_GPIO_NUM;
  config.pin_pclk = PCLK_GPIO_NUM;
  config.pin_vsync = VSYNC_GPIO_NUM;
  config.pin_href = HREF_GPIO_NUM;
  config.pin_sccb_sda = SIOD_GPIO_NUM;
  config.pin_sccb_scl = SIOC_GPIO_NUM;
  config.pin_pwdn = PWDN_GPIO_NUM;
  config.pin_reset = RESET_GPIO_NUM;
  config.xclk_freq_hz = 20000000;
  config.frame_size = FRAMESIZE_UXGA;
  config.pixel_format = PIXFORMAT_JPEG;  // for streaming
  //config.pixel_format = PIXFORMAT_RGB565;  // for face detection/recognition
  config.grab_mode = CAMERA_GRAB_WHEN_EMPTY;
  config.fb_location = CAMERA_FB_IN_PSRAM;
  config.jpeg_quality = 12;
  config.fb_count = 1;

  // if PSRAM IC present, init with UXGA resolution and higher JPEG quality
  //                      for larger pre-allocated frame buffer.
  if (config.pixel_format == PIXFORMAT_JPEG) {
    if (psramFound()) {
      config.jpeg_quality = 10;
      config.fb_count = 2;
      config.grab_mode = CAMERA_GRAB_LATEST;
    } else {
      // Limit the frame size when PSRAM is not available
      config.frame_size = FRAMESIZE_SVGA;
      config.fb_location = CAMERA_FB_IN_DRAM;
    }
  } else {
    // Best option for face detection/recognition
    config.frame_size = FRAMESIZE_240X240;
#if CONFIG_IDF_TARGET_ESP32S3
    config.fb_count = 2;
#endif
  }

#if defined(CAMERA_MODEL_ESP_EYE)
  pinMode(13, INPUT_PULLUP);
  pinMode(14, INPUT_PULLUP);
#endif

  // camera init
  ////esp_err_t err = esp_camera_init(&config);
  err = esp_camera_init(&config);
  if (err != ESP_OK) {
    Serial.printf("Camera init failed with error 0x%x", err);
    //return;
  }

  if (err == ESP_OK) {
    sensor_t *s = esp_camera_sensor_get();

    // initial sensors are flipped vertically and colors are a bit saturated
    if (s->id.PID == OV3660_PID) {
      s->set_vflip(s, 1);        // flip it back
      s->set_hmirror(s, 1);      // flip horizontal
      s->set_brightness(s, 1);   // up the brightness just a bit
      s->set_saturation(s, -2);  // lower the saturation
    }
    // drop down frame size for higher initial frame rate
    if (config.pixel_format == PIXFORMAT_JPEG) {
      s->set_framesize(s, FRAMESIZE_QVGA);
    }

#if defined(CAMERA_MODEL_M5STACK_WIDE) || defined(CAMERA_MODEL_M5STACK_ESP32CAM)
    s->set_vflip(s, 1);
    s->set_hmirror(s, 1);
#endif

#if defined(CAMERA_MODEL_ESP32S3_EYE)
    s->set_vflip(s, 1);
#endif

// Setup LED FLash if LED pin is defined in camera_pins.h
#if defined(LED_GPIO_NUM)
    setupLedFlash();
#endif
  }

  if (LittleFS.begin()) {
    Serial.println();
    Serial.println("Dosya sistemi başarılı");
  }

  dosyaokumyssidname();
  dosyaokufbyol();
  connectWifi();
  //  if(WiFi.status()==WL_CONNECTED)otasetup();

  startCameraServer();

  Serial.print("Camera Ready! Use 'http://");
  Serial.print(WiFi.localIP());
  Serial.println("' to connect");


  htserver.begin();
  Serial.println("HTTP server started");

  ////pinMode(PIR_PIN, INPUT);


  telegramtokendosyaoku();

  /*
  if (!MDNS.begin("esp32")) {
    Serial.println("Error setting up MDNS responder!");
    while (1) {
      delay(1000);
    }
  }
  Serial.println("mDNS responder started");

  // Start TCP (HTTP) server
  server.begin();
  Serial.println("TCP server started");

  // Add service to MDNS-SD
  MDNS.addService("http", "tcp", 8080);
  */

  dosyaokupirdevrede();
}

int pirpin = 0;
int pirdevrede;


void loop() {
  serin();
  htpcl();

  if (rescanwifi == 1) {
    wifiscan();
    rescanwifi = 0;
  }

  // Telegram hazırsa ve pir aktifse
  if (telegram_hazir == true && pirdevrede != 0) {
    
    // Kameradan anlık bir kare (frame) al
    camera_fb_t *fb = esp_camera_fb_get();
    if (!fb) {
      Serial.println("Kamera görüntüsü alınamadı!");
      return;
    }

    bool motionDetected = false;
    String telegramMesaji = ""; // Derleme hatası almamak için buraya ekledik

    // Eğer elimizde karşılaştıracak bir önceki karenin boyutu varsa
    if (prev_len > 0) {
      // İki fotoğrafın boyutu arasındaki farkı bul (Değişim miktarı)
      int size_diff = abs((int)fb->len - (int)prev_len);
      
      // ÖNEMLİ: Her döngü başında süreyi önce 15 saniyeye sıfırlıyoruz ki hafızada kilitli kalmasın!
      motionCooldown = 15000; 

      // ÖNEMLİ: String olan değişkeni formülde kullanabilmek için int'e çeviriyoruz
      int pirKatSayi = pirdevrede; 
      if(pirKatSayi < 1) pirKatSayi = 1;

      // Küçük hareket için daha düşük bir baraj (Örn: pir 2 ise %0.4)
      float kucuk_esik = (float)(2 * pirKatSayi) / 1000.0;
      
      // Büyük hareket için daha yüksek bir baraj (Örn: pir 2 ise %1.0)
      float buyuk_esik = (float)(5 * pirKatSayi) / 1000.0;

      // 1. Adım: Önce küçük eşikten büyük bir hareket var mı diye bakıyoruz
      if (size_diff > (prev_len * kucuk_esik)) {

        // 2. Adım: Eğer bu değişiklik büyük eşikten de büyükse süreyi 5 saniyeye düşür
        if (size_diff > (prev_len * buyuk_esik)) {
          motionCooldown = 5000;  
          telegramMesaji = "🔥 KRİTİK: Büyük Hareket Algılandı!";
          Serial.print("🔥 Büyük Hareket! ");
        } else {
          telegramMesaji = "🚨 UYARI: Küçük Hareket Algılandı.";
          Serial.print("🚨 Küçük Hareket! ");
        }

        // Zamanlama kontrolü ve Telegram'a gönderme bayrağı
        if (millis() - lastMotionTime > motionCooldown) {
          motionDetected = true;
          Serial.printf("Dosya Boyutu Farkı: %d bayt\n", size_diff);
        }
      }
    } // if (prev_len > 0) bloğunun kapanışı

    // Mevcut karenin boyutunu bir sonraki döngü için kaydet
    prev_len = fb->len;

    // Eğer hareket varsa VE 15 saniyelik süre dolmuşsa Telegram'a gönder
    if (motionDetected) {
      lastMotionTime = millis(); // 15 saniyelik bekleme sayacını TAM BU ANDA başlat

      // Flaş LED'ini yak
      pinMode(LED_GPIO_NUM, OUTPUT);
      int led_intensity1 = digitalRead(LED_GPIO_NUM);
      digitalWrite(LED_GPIO_NUM, 255); 
      delay(600);

      digitalWrite(LED_GPIO_NUM, led_intensity1); // Flaş kapat
      
      // Fotoğrafı Telegram'a gönder
      sendPhotoTelegram(fb,telegramMesaji);
    }

    // Bellek sızıntısını ve donmayı önlemek için buffer'ı mutlaka hemen iade et
    esp_camera_fb_return(fb);
  }
}





/*
void loop() {
  serin();
  htpcl();

  if (rescanwifi == 1) {
    wifiscan();
    rescanwifi = 0;
  }

  // Telegram hazırsa ve 15 saniyelik bekleme süresi (cooldown) dolduysa kontrol et
  if (telegram_hazir == true && pirdevrede == "1" && (millis() - lastMotionTime > motionCooldown)) {
    
    // Kameradan anlık bir kare (frame) al
    camera_fb_t *fb = esp_camera_fb_get();
    if (!fb) {
      Serial.println("Kamera görüntüsü alınamadı!");
      return;
    }

    bool motionDetected = false;

    // Eğer elimizde karşılaştıracak bir önceki kare varsa işleme başla
    if (prev_buf != NULL && prev_len == fb->len) {
      int changed_pixels = 0;
      int total_pixels = fb->len;

      // Pikselleri belirli aralıklarla (hız için her 20 pikselde bir) kontrol et
      for (size_t i = 0; i < fb->len; i += 20) {
        if (abs(fb->buf[i] - prev_buf[i]) > MOTION_THRESHOLD) {
          changed_pixels++;
        }
      }

      // Değişen piksellerin oranını hesapla
      float change_ratio = ((float)changed_pixels / (total_pixels / 20)) * 100;

      if (change_ratio > MOTION_PERCENTAGE) {
        motionDetected = true;
        Serial.printf("🚨 Hareket Algılandı! Değişim Oranı: %%.2f\n", change_ratio);
      }
    }

    // Mevcut kareyi, bir sonraki döngüde karşılaştırmak üzere hafızaya yedekle
    if (prev_buf == NULL) {
      prev_buf = (uint8_t *)malloc(fb->len);
    } else if (prev_len != fb->len) {
      prev_buf = (uint8_t *)realloc(prev_buf, fb->len);
    }
    
    if (prev_buf != NULL) {
      memcpy(prev_buf, fb->buf, fb->len);
      prev_len = fb->len;
    }

    // Eğer hareket algılandıysa Telegram'a gönder
    if (motionDetected) {
      // Flaş LED'ini yak (İsteğe bağlı)
      pinMode(LED_GPIO_NUM, OUTPUT);
      int led_intensity1 = digitalRead(LED_GPIO_NUM);
      digitalWrite(LED_GPIO_NUM, 255); 
      delay(600);

      lastMotionTime = millis(); // 15 saniyelik sayacı sıfırla

      digitalWrite(LED_GPIO_NUM, led_intensity1); // Flaş kapat
      
      // Fotoğrafı Telegram'a gönder
      sendPhotoTelegram(fb);
    }

    // Kamera buffer'ını sisteme geri iade et (Hafıza dolmaması için şart)
    esp_camera_fb_return(fb);
  }
}
*/

/*
void loop() {

  serin();
  htpcl();



  if (rescanwifi == 1) {
    wifiscan();
    rescanwifi = 0;
  }

  //if (digitalRead(PIR_PIN) == HIGH && millis() - lastMotionTime > motionCooldown) {


  if (telegram_hazir == true) {
    if (pirdevrede == "1" && pirpin == 1 && millis() - lastMotionTime > motionCooldown) {
      pinMode(LED_GPIO_NUM, OUTPUT);
      int led_intensity1 = digitalRead(LED_GPIO_NUM);
      digitalWrite(LED_GPIO_NUM,255);
      delay(600);
      pirpin = 0;
      lastMotionTime = millis();
      Serial.println("🚨 Motion detected!");

      camera_fb_t *fb = esp_camera_fb_get();
      if (!fb) {
        Serial.println("Camera capture failed");
        return;
      }
      delay(1);
      digitalWrite(LED_GPIO_NUM,led_intensity1);
      sendPhotoTelegram(fb);
      esp_camera_fb_return(fb);
    }
  }
}
*/

IPAddress AP_LOCAL_IP(192, 168, 4, 1);
IPAddress AP_GATEWAY_IP(192, 168, 4, 1);
IPAddress AP_NETWORK_MASK(255, 255, 255, 0);



void connectWifi(void) {
  WiFi.mode(WIFI_AP_STA); // Hem modeme bağlanabilme hem de AP modu açık
  
  dosyaokussidpass();
  if (esphostname != "") WiFi.hostname(esphostname);
  
  WiFi.begin(ssid, pass);
  WiFi.setSleep(false);

  if (testWifi()) {
    // BAŞARILI DURUM: Modeme bağlandı ama arka planda AP de açılıyor
    // Önce ismi başlatıyoruz:
    Serial.println("Connected to Router!!!");
    Serial.print("Station IP (Modemden Alınan): ");
    Serial.println(WiFi.localIP());
        Serial.println(WiFi.gatewayIP());
    // ==========================================
    // MODEME BAĞLIYKEN AP MODUNU DA DOĞRU BAŞLATMA
    // ==========================================
    
    // 1. Önce AP ağını ismiyle oluşturun
    if (esphostname != "") {
      WiFi.softAP(esphostname, pass);
    } else {
      WiFi.softAP("ESP32-CAM_AI-Thinker", "12345678");
    }
    
    // 2. Wi-Fi donanımının kendine gelmesi için çok kısa bir es verin (Çok Kritik!)
    delay(100); 
    
    // 3. AP için DHCP ve Statik IP havuzunu zorunlu kılın
    WiFi.softAPConfig(AP_LOCAL_IP, AP_GATEWAY_IP, AP_NETWORK_MASK);
    
    Serial.print("Arka Plan AP IP (Telefona Dağıtılan): ");
    Serial.println(WiFi.softAPIP()); // Seri portta 192.168.4.1 görmelisiniz

  } else {
    // BAŞARISIZ DURUM: Modeme bağlanamadı, sadece Access Point (HotSpot) olacak
    Serial.println("ConWifi timeout, open AP");
    
    // 1. Önce sadece AP moduna alıyoruz
    WiFi.mode(WIFI_AP); 
    
    // 2. Önce ağı (SSID ve Şifre) başlatıyoruz
    WiFi.softAP("ESP32-CAM_AI-Thinker", "12345678"); 
    
    // 3. EN ÖNEMLİSİ: Ağ başladıktan SONRA IP havuzunu ve DHCP'yi kilitliyoruz
    delay(100); // Kısa bir süre donanımın kendine gelmesini bekle
    WiFi.softAPConfig(AP_LOCAL_IP, AP_GATEWAY_IP, AP_NETWORK_MASK);
    
    // Hostname ayarı
    if (esphostname != "") {
      int str_len = esphostname.length() + 1;
      char ch[str_len];
      esphostname.toCharArray(ch, str_len);
      WiFi.softAPsetHostname(ch);
    }

    IPAddress IP = WiFi.softAPIP();
    Serial.print("softAPIP: ");
    Serial.println(IP); // Artık burada güvenle 192.168.4.1 göreceksiniz.
  }
}

int sayfayenile = 0;




bool testWifi(void) {
  if (ssid.length() < 2) {
    return false;
  }
  int c1 = 0;
  Serial.println("Con Wifi");
  //display.drawBitmap(0, 0,  Lan_off_logo8x16_glcd_bmp, 16, 8, 1);
  //display.println();
  //display.println("Modeme");
  //display.println("Baglaniyor");
  //display.display();
  Serial.print(ssid + "  " + pass);
  while (c1 < 11) {
    if (WiFi.status() == WL_CONNECTED) {
      //  display.drawBitmap(0, 0,  Lan_on_logo8x16_glcd_bmp, 16, 8, 1);
      //  display.display();
      return true;
    }
    delay(1000);
    Serial.print("*");
    c1++;
    serin();
  }
  Serial.println("");
  Serial.println("ConWifi timeout,open AP");
  return false;
}



String Karakterduzeltfunc(String gelent) {
  Serial.println("Karakterduzelte girdim");
  Serial.println(gelent);
  gelent.replace("+", " ");
  gelent.replace("%20", " ");
  gelent.replace("%26", "&");
  gelent.replace("%28", "(");
  gelent.replace("%29", ")");
  gelent.replace("%7C", "|");
  gelent.replace("%3B", ";");
  gelent.replace("%3D", "=");
  gelent.replace("%3F", "?");
  gelent.replace("%3E", ">");
  gelent.replace("%3C", "<");
  gelent.replace("%7B", "{");
  gelent.replace("%7D", "}");
  gelent.replace("%5B", "[");
  gelent.replace("%5D", "]");
  gelent.replace("%2B", "+");
  gelent.replace("%21", "!");
  gelent.replace("%0D%0A", "\n");
  gelent.replace("%22", "\"");
  gelent.replace("%3A", ":");
  gelent.replace("%3B", "\"");
  gelent.replace("%23", "#");
  gelent.replace("%27", "'");
  gelent.replace("%2C", ",");
  gelent.replace("%C5%9E", "Ş");
  gelent.replace("%C5%9F", "ş");
  gelent.replace("%C3%87", "Ç");
  gelent.replace("%C3%A7", "ç");
  gelent.replace("%C3%96", "Ö");
  gelent.replace("%C3%B6", "ö");
  gelent.replace("%C3%9C", "Ü");
  gelent.replace("%C3%BC", "ü");
  gelent.replace("%C4%9E", "Ğ");
  gelent.replace("%C4%9F", "ğ");
  gelent.replace("%C4%B1", "ı");
  gelent.replace("%C4%B0", "İ");
  gelent.replace("%2F", "/");
  gelent.replace("%25", "%");
  gelent.replace("%3E", ">");
  gelent.replace("%3C", "<");
  Serial.print("Düzeltme sonucu: ");
  Serial.println(gelent);
  return gelent;
}


int statusCode;
String st;
void wifiscan(void) {
  int n = WiFi.scanNetworks();
  Serial.println("scan done");
  if (n == 0)
    Serial.println("Wifi cihaz yok");
  else {
    st = "[ " + String(n) + " ] Wifi cihaz bulundu<br>";
    Serial.print(n);
    Serial.println(" networks found");
    for (int i = 0; i < n; ++i) {
      // Print SSID and RSSI for each network found
      Serial.print(i + 1);
      Serial.print(": ");
      Serial.print(WiFi.SSID(i));
      Serial.print(" (");
      Serial.print(WiFi.RSSI(i));
      Serial.print(")");

      //delay(4);
    }
  }
  Serial.println("");
  //st = "<ol>";
  st += "<ol>";
  for (int i = 0; i < n; ++i) {
    // Print SSID and RSSI for each network found
    st += "<li>";
    st += WiFi.SSID(i);
    st += " (";
    st += WiFi.RSSI(i);

    st += ")";
    st += "</li>";
  }
  st += "</ol><br>";
}

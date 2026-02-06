/*


#include "esp_camera.h"
#include <WiFi.h>

// ===========================
// Select camera model in board_config.h
// ===========================
#include "board_config.h"


// ===========================
// Enter your WiFi credentials
// ===========================

String ssid = "";
String pass = "";
int rescanwifi = 0;
unsigned int zamanfark;


bool WiFiAP = true;  // Do yo want the ESP as AP?


String header;
String creator;

String esphostnameOnek = "";
String esphostname = "esp-bos";



void startCameraServer();
void setupLedFlash();

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
  //config.pixel_format = PIXFORMAT_RGB565; // for face detection/recognition
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
  esp_err_t err = esp_camera_init(&config);
  if (err != ESP_OK) {
    Serial.printf("Camera init failed with error 0x%x", err);
    return;
  }

  sensor_t *s = esp_camera_sensor_get();
  // initial sensors are flipped vertically and colors are a bit saturated
  if (s->id.PID == OV3660_PID) {
    s->set_vflip(s, 1);        // flip it back
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

connectWifi();
  otasetup();

  startCameraServer();

  Serial.print("Camera Ready! Use 'http://");
  Serial.print(WiFi.localIP());
  Serial.println("' to connect");
}


void loop() {

    if (zamanfark > 297 && zamanfark < 300) {otaloop();zamanrak+=3;}
  yield();
  serin();
  if (zamanfark < 200) htpcl();



  if (rescanwifi == 1) {
    wifiscan();
    rescanwifi = 0;
  }


  
  if (Menu == 0) {
    zamanfark += 1;
    if (zamanfark > 1000) zamanfark = 1;
    }

}






void connectWifi(void) {
  WiFi.mode(WIFI_AP_STA); 1  //ESP8266 works in both AP mode and station mode
  //WiFi.mode(WIFI_STA); 2  // ESP8266 works in station mode
  // WiFi.begin(ssid, password); // given the network

  //    Serial.print(ssid);
  //    Serial.print("connecting to ");
  //    while (WiFi.status() != WL_CONNECTED) {
  //      // not connected to the network
  //    delay(500);
  //    Serial.print(".");
  //  }
  dosyaokussidpass();
  WiFi.hostname(esphostname);
  WiFi.begin(ssid, pass);
  //Serial.println(ssid);
  //Serial.println(pass);
  //delay(1000);
    WiFi.setSleep(false);


  if (testWifi()) {
    Serial.println("Connected!!!");
    Serial.println(WiFi.localIP());
    Serial.println(WiFi.gatewayIP());
    WiFi.softAP(esphostname, "12345678");  // bağlanınca ap kalksın için // koyabiliriz.

  IPAddress lip = WiFi.localIP();
  String mylocalip = String(lip[0]) + '.' + String(lip[1]) + '.' + String(lip[2]) + '.' + String(lip[3]);

    //buzzercal(2000, 3); delay(100);
    //buzzercal(3000, 2); delay(10);
  } else {

    WiFi.hostname(esphostname);
    Serial.println("HotSpot On");
    //                                wifiscan();
    //                                lookAP();// S etup HotSpot
    WiFi.softAP("Esp01-bos-v3", "12345678");
    //delay(100);
    Serial.println(WiFi.localIP());
    Serial.println(WiFi.gatewayIP());
    //buzzercal(3000, 50); delay(100);
    //buzzercal(2500, 70); delay(100);
    //buzzercal(1500, 100); delay(10);
  }

  //firebaseRealtime.begin(FIREBASE_REALTIME_URL, FIREBASE_REALTIME_SECRET);
}

int Menu = 0;





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
  return gelent;
}



*/
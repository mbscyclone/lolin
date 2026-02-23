
void httpgonder()
{
            WiFiClient client;
            HTTPClient http;
            http.setTimeout(1000);
            //Serial.print("[HTTP] begin...\n");
            // configure traged server and url
            http.begin(client, htyolla);  // HTTP
            //Serial.print("[HTTP] GET...\n");
            // start connection and send HTTP header and body
            int httpCode = http.GET();
            // httpCode will be negative on error
            if (httpCode > 0) {
              // file found at server
              if (httpCode == HTTP_CODE_OK) {
                const String& payload = http.getString();
                //Serial.println("received payload:\n<<");
                Serial.println(payload);
              }
            } else {
              Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
            }

            http.end();
            htyolla="";

}
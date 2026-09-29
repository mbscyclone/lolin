// FirebaseRealtime.cpp

#include "./FirebaseRealtime.h"

void FirebaseRealtime::begin(String url, String secret) {
  client.setInsecure();
  FirebaseRealtime::URL = url;
  FirebaseRealtime::secret = secret;
}


String FirebaseRealtime::getSecretParam() {
  if (secret != "")
    return "?auth=" + secret;
  return "";
}

int FirebaseRealtime::save(const String &parentNode, const String &childNode, const String &jsonData, bool isUpdate) {
  int httpResponseCode;
  http.begin(client, URL + "/" + parentNode + "/" + childNode + ".json" + getSecretParam());
  http.addHeader("Content-Type", "application/json");
  if (isUpdate)
    httpResponseCode = http.PATCH(jsonData);
  else
    httpResponseCode = http.PUT(jsonData);
  return httpResponseCode;
}

int FirebaseRealtime::fetch(const String &parentNode, const String &childNode, DynamicJsonDocument &doc) {
  http.begin(client, URL + "/" + parentNode + "/" + childNode + ".json" + getSecretParam());
  int httpResponseCode = http.GET();
  deserializeJson(doc, http.getString());
  return httpResponseCode;
}

int FirebaseRealtime::remove(const String &parentNode, const String &childNode) {
  http.begin(client, URL + "/" + parentNode + "/" + childNode + ".json" + getSecretParam());
  int httpResponseCode = http.DELETE();
  return httpResponseCode;
}

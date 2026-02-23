#ifndef USER_DEBUG_PRINT_H
#define USER_DEBUG_PRINT_H

#include <FirebaseClient.h>

// WiFi library used in the examples
#if defined(ESP32)
#include <WiFi.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#endif

// SSL Client used in the examples
#if defined(ESP32) || defined(ESP8266)
#include <WiFiClientSecure.h>
#define SSL_CLIENT WiFiClientSecure
#endif

#endif

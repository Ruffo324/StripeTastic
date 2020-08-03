/*********
  Rui Santos
  Complete project details at https://randomnerdtutorials.com  
*********/

// Import required libraries
#include <Configuration.h>
#include <Logger.h>
#include <WifiService.h>

#include "WiFi.h"
#include "ESPAsyncWebServer.h"
#include "SPIFFS.h"

// Replace with your network credentials
const char *ssid = "***REMOVED***";
const char *password = "***REMOVED***";

// Set LED GPIO
const int ledPin = 2;
// Stores LED state
String ledState;

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);
Services::WifiService *_wifiService;
Services::LoopService *_loopService;

// Replaces placeholder with LED state value
String processor(const String &var)
{
    Serial.println(var);
    if (var == "STATE")
    {
        if (digitalRead(ledPin))
        {
            ledState = "ON";
        }
        else
        {
            ledState = "OFF";
        }
        Serial.print(ledState);
        return ledState;
    }
    return String();
}

void setup()
{
    // Setup logger.
    auto logger = Services::Logger::GetInstance();
    logger->Setup(Configuration::Baudrate);

    // Setup loop service, and set loop delay.
    _loopService = Services::LoopService::GetInstance();
    _loopService->LoopDelayMs = Configuration::LoopDelayMs;

    _wifiService = new Services::WifiService();

    pinMode(ledPin, OUTPUT);

    // Initialize SPIFFS
    if (!SPIFFS.begin(true))
    {
        Serial.println("An Error has occurred while mounting SPIFFS");
        return;
    }

    // Create AP. //TODO: load from UserPreferences.
    _wifiService->CreateAccessPoint();

    // Route for root / web page
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
        Serial.println(SPIFFS.exists("/index.html"));
        request->send(SPIFFS, "/index.html", String(), false, processor);
    });

    // Route to load style.css file
    // TODO: Move to routemapping.cpp
    server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(SPIFFS, "/style.css", "text/css");
    });

    server.on("/vendor/js/jquery.js", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(SPIFFS, "/vendor/js/jquery.js", "application/script");
    });
    server.on("/vendor/js/bootstrap.js", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(SPIFFS, "/vendor/js/bootstrap.js", "application/script");
    });
    server.on("/vendor/css/bootstrap.css", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(SPIFFS, "/vendor/css/bootstrap.css", "text/css");
    });

    // Route to set GPIO to HIGH
    server.on("/on", HTTP_GET, [](AsyncWebServerRequest *request) {
        digitalWrite(ledPin, HIGH);
        request->send(SPIFFS, "/index.html", String(), false, processor);
    });

    // Route to set GPIO to LOW
    server.on("/off", HTTP_GET, [](AsyncWebServerRequest *request) {
        digitalWrite(ledPin, LOW);
        request->send(SPIFFS, "/index.html", String(), false, processor);
    });

    // Start server
    server.begin();
}

void loop()
{
    _loopService->InvokeLoop();
}
#pragma once
#include "../Logger/Logger.h"
#include "ArduinoJson.h"
#include "AsyncJson.h"
#include "ESPAsyncWebServer.h"
#include "FileSystem.h"
#include <Arduino.h>

namespace Services
{
    class WebServer
    {
    public:
        WebServer();
        void Start();
        void Stop();
        void RebuildFileRoutes(FileList fileList);

        void RegisterRestCall(String eventPath, std::function<void(JsonObject data)> function);
        void Unregister(String eventPath);
        void SendEvent(String eventName, String data);

    private:
        const String _loggerTag = "HTTP";
        Logger *_logger;
        AsyncWebServer _webServer;
        AsyncEventSource _serverEvents;
        std::map<String, AsyncCallbackJsonWebHandler *> _registeredJsonRequests;
        void addFileRoute(String requestPath, String path, String mimeType);
    };

    // // Route to set GPIO to HIGH
    // server.on("/on", HTTP_GET, [](AsyncWebServerRequest *request) {
    //     digitalWrite(ledPin, HIGH);
    //     request->send(SPIFFS, "/index.html", String(), false, processor);
    // });

    // // Route to set GPIO to LOW
    // server.on("/off", HTTP_GET, [](AsyncWebServerRequest *request) {
    //     digitalWrite(ledPin, LOW);
    //     request->send(SPIFFS, "/index.html", String(), false, processor);
    // });
} // namespace Services
#pragma once
#include <Arduino.h>
#include <Logger.h>
#include "ESPAsyncWebServer.h"
#include "FileService.h"

namespace Services
{
    class WebService
    {
    public:
        WebService();
        void Start();
        void Stop();
        void RebuildFileRoutes(FileList fileList);

        void Register(String key, std::function<void()> function);
        void Unregister(String key);

    private:
        Logger *_logger;
        AsyncWebServer _webServer;
        std::map<String, std::function<void()>> _registeredJsonRequests;
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
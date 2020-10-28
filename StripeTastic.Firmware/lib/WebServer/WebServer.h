#pragma once
#include "../Logger/Logger.h"
#include "ArduinoJson.h"
#include "AsyncJson.h"
#include "ESPAsyncWebServer.h"
#include <Arduino.h>
#include <AsyncWebdav.h>

namespace Services
{
    class WebServer
    {
    public:
        WebServer();
        void Start();
        void Stop();

        void RegisterRestCall(String eventPath, std::function<void(JsonObject data)> function);
        void Unregister(String eventPath);
        void SendEvent(String eventName, String data);

    private:
        const String _loggerTag = "HTTP";
        Logger *_logger;
        AsyncWebServer _webServer;
        AsyncEventSource _serverEvents;
        // Used to transfer files without manual SPIFFS upload.
        AsyncWebdav _webdavServer;
        std::map<String, AsyncCallbackJsonWebHandler *> _registeredJsonRequests;
        void Initialize();
    };
} // namespace Services
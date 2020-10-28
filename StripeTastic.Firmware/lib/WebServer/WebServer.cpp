#include "WebServer.h"
#include "ArduinoJson.h"
#include "AsyncJson.h"
#include <Configuration.h>
#include <Lit

namespace Services
{
    // TODO: Think about renaming "WebServer" to something like "ClientCommunicator".
    void WebServer::RegisterRestCall(String eventPath, std::function<void(JsonObject data)> function)
    {
        AsyncCallbackJsonWebHandler *handler = new AsyncCallbackJsonWebHandler(eventPath, [function](AsyncWebServerRequest *request, JsonVariant json) {
            JsonObject jsonObj = json.as<JsonObject>();
            // serializeJsonPretty(jsonObj, Serial); // Debug
            function(jsonObj);
            request->send(200);
        });
        _registeredJsonRequests[eventPath] = handler;
        _webServer.addHandler(handler);
    }

    void WebServer::SendEvent(String eventName, String data)
    {
        _serverEvents.send(data.c_str(), eventName.c_str());
    }

    void WebServer::Unregister(String eventPath)
    {
        auto position = _registeredJsonRequests.find(eventPath);
        if (position != _registeredJsonRequests.end())
        {
            _webServer.removeHandler(_registeredJsonRequests[eventPath]);
            _registeredJsonRequests.erase(position);
        }
    }

    void WebServer::Initialize()
    {

        if (_webServer.removeHandler(&_serverEvents))
            _logger->Logln(_loggerTag, "Event handler removed.");

        _webServer.reset();

LittleFS
        server.serveStatic("/", SPIFFS, "/wwwroot/");

        _webServer.addHandler(&_serverEvents);
    }

    void WebServer::Start()
    {
        _webServer.begin();
    }

    void WebServer::Stop()
    {
        _webServer.end();
    }

    // TODO: Create const for "/events"
    WebServer::WebServer()
        : _webServer(Configuration::DefaultWebServerPort), _serverEvents("/events"), _webdavServer("/dav")
    {
        _logger->Logger::GetInstance();
        _logger->Logln(_loggerTag, "Webserver started with port " + String(Configuration::DefaultWebServerPort) + ".");
    }
} // namespace Services

#include "WebServer.h"
#include "ArduinoJson.h"
#include "AsyncJson.h"
#include <Configuration.h>

namespace Services
{
    void WebServer::RebuildFileRoutes(FileList fileList)
    {
        if (_webServer.removeHandler(&_serverEvents))
            _logger->Logln(_loggerTag, "event handler removed.");

        _webServer.reset();
        for (auto &&file : fileList)
        {
            if (file.path.endsWith(Configuration::IndexPageName))
                addFileRoute("/", file.path, file.type);

            addFileRoute(file.path, file.path, file.type);
        }
        _webServer.addHandler(&_serverEvents);
    }

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

    void WebServer::Start()
    {
        _webServer.begin();
    }

    void WebServer::Stop()
    {
        _webServer.end();
    }

    WebServer::WebServer()
        : _webServer(Configuration::DefaultWebServerPort), _serverEvents("/events") // TODO: Create const for "/events"
    {
        _logger->Logger::GetInstance();
        _logger->Logln(_loggerTag, "Webserver started with port " + String(Configuration::DefaultWebServerPort) + ".");
    }

    void WebServer::addFileRoute(String requestPath, String path, String mimeType)
    {
        _webServer.on(requestPath.c_str(), HTTP_GET, [path, mimeType](AsyncWebServerRequest *request) {
            request->send(SPIFFS, path, mimeType);
        });
    }
} // namespace Services

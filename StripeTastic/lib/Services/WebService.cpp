#include <Configuration.h>
#include "WebService.h"
#include "ArduinoJson.h"
#include "AsyncJson.h"

namespace Services
{
    void WebService::RebuildFileRoutes(FileList fileList)
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

    void WebService::RegisterRestCall(String eventPath, std::function<void(JsonObject data)> function)
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

    void WebService::SendEvent(String eventName, String data)
    {
        if (_initialized)
        {
            _serverEvents.send(data.c_str(), eventName.c_str());
        }
    }

    void WebService::Unregister(String eventPath)
    {
        auto position = _registeredJsonRequests.find(eventPath);
        if (position != _registeredJsonRequests.end())
        {
            _webServer.removeHandler(_registeredJsonRequests[eventPath]);
            _registeredJsonRequests.erase(position);
        }
    }

    void WebService::Start()
    {
        _webServer.begin();
        _initialized = true;
    }

    void WebService::Stop()
    {
        _initialized = false;
        _webServer.end();
    }

    WebService::WebService()
        : _webServer(Configuration::DefaultWebServerPort), _serverEvents("/events") // TODO: Create const for "/events"
    {
        _logger->Logger::GetInstance();
        _logger->Logln(_loggerTag, "Webserver started with port " + String(Configuration::DefaultWebServerPort) + ".");
        _logger->Listen([this](String msg) { sendSerialMessage(msg); });
    }

    void WebService::sendSerialMessage(String message)
    {
        if (_initialized)
        {
            SendEvent("message", message);
        }
    }

    void WebService::addFileRoute(String requestPath, String path, String mimeType)
    {
        _webServer.on(requestPath.c_str(), HTTP_GET, [path, mimeType](AsyncWebServerRequest *request) {
            request->send(SPIFFS, path, mimeType);
        });
    }
} // namespace Services

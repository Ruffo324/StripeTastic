#include <Configuration.h>
#include "WebService.h"
#include "ArduinoJson.h"
#include "AsyncJson.h"

namespace Services
{
    const String _loggerTag = "HTTP";

    void WebService::RebuildFileRoutes(FileList fileList)
    {
        _webServer.reset();
        for (auto &&file : fileList)
        {
            if (file.path.endsWith(Configuration::IndexPageName))
                addFileRoute("/", file.path, file.type);

            addFileRoute(file.path, file.path, file.type);
        }
    }

    void WebService::RegisterRestCall(String eventPath, std::function<void(JsonObject data)> function)
    {
        // _registeredJsonRequests[eventPath] =
        //     new AsyncCallbackJsonWebHandler(eventPath, [function](AsyncWebServerRequest *request, JsonVariant json) {
        //         auto obj = json.as<JsonObject>();
        //         serializeJsonPretty(obj, Serial);
        //         // Serial.println(serializeJsonPretty(obj));
        //         // obj["speed"].as<String>());
        //         function(obj);
        //         request->send(200);
        //     });
        // _webServer.addHandler(_registeredJsonRequests[eventPath]);
        // _logger->Log("JSON registered.");

        AsyncCallbackJsonWebHandler *handler = new AsyncCallbackJsonWebHandler("/rest/endpoint", [](AsyncWebServerRequest *request, JsonVariant json) {
            JsonObject jsonObj = json.as<JsonObject>();
            serializeJsonPretty(jsonObj, Serial);
            request->send(200);
        });
        _webServer.addHandler(handler);
    }

    void WebService::Unregister(String eventPath)
    {
        auto position = _registeredJsonRequests.find(eventPath);
        if (position != _registeredJsonRequests.end())
        {
            _webServer.addHandler(_registeredJsonRequests[eventPath]);
            _registeredJsonRequests.erase(position);
        }
    }

    void WebService::Start()
    {
        _webServer.begin();
    }

    void WebService::Stop()
    {
        _webServer.end();
    }

    WebService::WebService() : _webServer(Configuration::DefaultWebServerPort)
    {
        _logger->Logger::GetInstance();
        _logger->Logln(_loggerTag, "Webserver started with port " + String(Configuration::DefaultWebServerPort) + ".");
    }

    void WebService::addFileRoute(String requestPath, String path, String mimeType)
    {
        _webServer.on(requestPath.c_str(), HTTP_GET, [path, mimeType](AsyncWebServerRequest *request) {
            request->send(SPIFFS, path, mimeType);
        });
    }

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

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
        void RebuildFileRoutes(FileList fileList);
        void Start();
        void Stop();

    private:
        Logger *_logger;
        AsyncWebServer::AsyncWebServer _webServer;
        void addFileRoute(String requestPath, String path, String mimeType);
    };
} // namespace Services
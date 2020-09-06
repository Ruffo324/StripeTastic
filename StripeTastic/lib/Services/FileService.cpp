#include "FileService.h"
#include "SPIFFS.h"
#include <ArduinoLinq.hpp>
#include <Configuration.h>

namespace Services
{
    FileService::FileService()
    {
        _logger = Logger::GetInstance();

        if (!SPIFFS.begin(true))
        {
            _logger->Error("Unable to mount SPIFFS");
            return;
        }
    }

    void FileService::ScanFileSystem()
    {
        File root = SPIFFS.open("/");
        File file;

        _files.clear();
        while (file = root.openNextFile())
            _files.push_back({.path = file.name(), .type = fileTypeByExtension(file.name()), .size = file.size()});

        _logger->Logln(_loggerTag, "Filesystem scan completed, found " + String(_files.size()) + " files.");
        if (Configuration::Debug)
            showFileServiceOverview();
    }

    void FileService::showFileServiceOverview()
    {
        auto totalMb = humanizeBytes(SPIFFS.totalBytes());
        auto usedMb = humanizeBytes(SPIFFS.usedBytes());
        auto freeMb = humanizeBytes(SPIFFS.totalBytes() - SPIFFS.usedBytes());

        LoggerTable spaceOverview = {
            {"total", "used", "free"},
            {totalMb, usedMb, freeMb},
        };
        _logger->LogTable(_loggerTag, spaceOverview, false, false);

        using namespace ArduinoLinq;

        auto fileToRow = [this](file_fileService f) { return (LoggerTableRow){f.path, f.type, humanizeBytes(f.size)}; };

        LoggerTable data = {{"File path", "web mime type", "size"}};
        auto filesData = from(_files) >> select(fileToRow) >> to_vector();
        data.insert(data.end(), filesData.begin(), filesData.end());

        _logger->LogTable(_loggerTag, data, true);
    }

    String FileService::fileTypeByExtension(String file)
    {
        const String unknown = "text/plain";

        if (file.indexOf(".") == -1)
            return unknown;

        const String mapping[][2] = {
            {".htm", "text/html"},
            {".html", "text/html"},
            {".css", "text/css"},
            {".js", "application/javascript"},
            {".png", "image/png"},
            {".gif", "image/gif"},
            {".jpg", "image/jpeg"},
            {".ico", "image/x-icon"},
            {".xml", "text/xml"},
            {".pdf", "application/x-pdf"},
            {".zip", "application/x-zip"},
            {".gz", "application/x-gzip"},
        };

        file.toLowerCase();
        for (auto &mimeMap : mapping)
            if (file.endsWith(mimeMap[0]))
                return mimeMap[1];

        return unknown;
    }

    String FileService::humanizeBytes(size_t byte)
    {
        vector<String> sizes = {"kb", "mb", "gb", "tb", "pt"};
        double converted = byte;
        for (size_t i = 0; i < sizes.size(); i++)
            if ((converted = converted / 1024) < 1)
                return String(converted, 4) + " " + sizes[i];
        return "NaN";
    }

    FileList FileService::GetStaticFiles()
    {
        return _files;
    }
} // namespace Services

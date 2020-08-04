#include "FileService.h"
#include "SPIFFS.h"
#include <ArduinoLinq.hpp>
#include <Configuration.h>

namespace Services
{
    const String _loggerTag = "FILE";
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
            _files.push_back({.path = file.name(), .type = fileTypeByExtension(file.name())});

        _logger->Logln(_loggerTag, "Filesystem scan completed, found " + String(_files.size()) + " files.");

        // Show files in debug mode. // TODO: extra function?
        using namespace ArduinoLinq;
        if (Configuration::Debug)
        {
            LoggerTable data = {{"File path", "web mime type"}};
            auto filesData = from(_files) >> select([](file_fileService f) { return (LoggerTableRow){f.path, f.type}; }) >> to_vector();
            data.insert(data.end(), filesData.begin(), filesData.end());

            _logger->LogTable(_loggerTag, data, true);
        }
    }

    String FileService::fileTypeByExtension(String file)
    {
        const String unknown = "text/plain";

        if (file.indexOf(".") == -1)
            return unknown;

        const String mapping[][2] = {
            {".js", "application/script"},
            {".css", "text/css"},
            {".html", "text/html"},
        };

        file.toLowerCase();
        for (auto &mimeMap : mapping)
            if (file.endsWith(mimeMap[0]))
                return mimeMap[1];

        return unknown;
    }

    FileList FileService::GetAllFiles()
    {
        return _files;
    }
} // namespace Services

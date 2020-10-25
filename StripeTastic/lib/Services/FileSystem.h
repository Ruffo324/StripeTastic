#pragma once
#include "../Logger/Logger.h"
#include <Arduino.h>

#include "SPIFFS.h"

namespace Services
{
    struct file_fileService
    {
        String path;
        String type;
        /**
         * Size of the file in bytes.
         */
        size_t size;
    };

    typedef vector<file_fileService> FileList;
    class FileSystem
    {
    public:
        FileSystem();
        void ScanFileSystem();
        FileList GetStaticFiles();

    private:
        const String _loggerTag = "FILE";
        String fileTypeByExtension(String file);
        Logger *_logger;
        FileList _files;
        void showFileServiceOverview();
        String humanizeBytes(size_t byte);
    };
} // namespace Services
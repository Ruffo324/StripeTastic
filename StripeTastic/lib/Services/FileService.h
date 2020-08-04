#pragma once
#include <Arduino.h>
#include <Logger.h>

#include "SPIFFS.h"

namespace Services
{
    struct file_fileService
    {
        String path;
        String type;
    };

    typedef vector<file_fileService> FileList;
    class FileService
    {
    public:
        FileService();
        void ScanFileSystem();
        FileList GetAllFiles();

    private:
        String fileTypeByExtension(String file);
        Logger *_logger;
        FileList _files;
    };
} // namespace Services
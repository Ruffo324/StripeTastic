#pragma once

#include <Arduino.h>

namespace Services
{
    class Logger
    {
    public:
        static Logger *GetInstance();
        void Setup(int baudrate);
        void Logln(const String tag, const String message);
        void Logln(const String message);
        void Log(const String tag, const String message);
        void Log(const String message);
        void Linebreak();

    private:
        Logger();
        static Logger *_instance;
        String TagToPrefix(const String tag);
        const String UnknownTag = "UNKNW";
    };
} // namespace Services
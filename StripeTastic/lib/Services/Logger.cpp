#include <Arduino.h>
#include "Logger.h"

namespace Services
{
    Logger *Logger::_instance = 0;

    Logger::Logger()
    {
    }

    Logger *Logger::GetInstance()
    {
        if (_instance == 0)
            _instance = new Logger();

        // return _instance == 0 ? _instance = new LoopService() : _instance;
        return _instance;
    }

    void Logger::Setup(int baudrate)
    {
        Serial.begin(baudrate);
    }

    void Logger::Logln(const String message)
    {
        this->Logln(UnknownTag, message);
    }

    void Logger::Log(const String message)
    {
        Serial.print(message);
    }

    void Logger::Logln(const String tag, const String message)
    {
        Serial.println(TagToPrefix(tag) + message);
    }

    void Logger::Log(const String tag, const String message)
    {
        this->Log(TagToPrefix(tag) + message);
    }

    void Logger::Linebreak()
    {
        Serial.println();
    }

    String Logger::TagToPrefix(const String tag)
    {
        // TODO: DateTime synced from NTP server.
        return "[" + tag + "] ";
    }

} // namespace Services
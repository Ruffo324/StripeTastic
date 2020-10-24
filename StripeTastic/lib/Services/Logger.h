#pragma once

#include <Arduino.h>
#include <functional>
using namespace std;

namespace Services
{
    typedef vector<String> LoggerTableRow;
    typedef vector<LoggerTableRow> LoggerTable;
    typedef function<void(String &)> LoggerListenFunction;

    class Logger
    {
    public:
        static Logger *GetInstance();
        void Setup(int baudrate);
        void Logln(const String tag, const String message);
        void Logln(const String message);
        void Log(const String tag, const String message);
        void Log(const String message);

        void Warning(const String message);
        void Error(const String message);
        void Debug(const String message);
        void Linebreak();

        void LogTable(const String tag, LoggerTable data, bool firstIsHeader = false, bool topBottomBorder = true);
        void PrintLine(const String tag, const int length);
        void PrintLine(const String tag);
        void PrintLine();
        void Listen(LoggerListenFunction outFunction);

    private:
        Logger();
        static Logger *_instance;
        String TagToPrefix(const String tag);
        String RepeatChar(const int length, const char padChar = ' ');
        void SendToListeners(String message);
        vector<LoggerListenFunction> _listeners;

        const int LineLength = 20;
        const String UnknownTag = "UNKNW";
        const String WarningTag = "WARN";
        const String ErrorTag = "ERROR";
        const String DebugTag = "DEBUG";
        const String LineTag = "----";
    };
} // namespace Services
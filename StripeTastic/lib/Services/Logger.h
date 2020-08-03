#pragma once

#include <Arduino.h>
using namespace std;

namespace Services
{
    typedef vector<String> LoggerTableRow;
    typedef vector<LoggerTableRow> LoggerTable;

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

        void LogTable(const String tag, LoggerTable data);
        void PrintLine(const String tag, const int length);
        void PrintLine(const String tag);
        void PrintLine();

    private:
        Logger();
        static Logger *_instance;
        String TagToPrefix(const String tag);
        String RepeatChar(const int length, const char padChar = ' ');
        const int LineLength = 20;
        const String UnknownTag = "UNKNW";
        const String WarningTag = "WARN";
        const String ErrorTag = "ERROR";
        const String DebugTag = "DEBUG";
        const String LineTag = "----";
    };
} // namespace Services
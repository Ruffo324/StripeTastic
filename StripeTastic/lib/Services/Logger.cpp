#include <Arduino.h>
#include "Logger.h"
#include "ArduinoLinq.hpp"

namespace Services
{
    using namespace std;
    Logger *Logger::_instance = 0;

    Logger::Logger()
    {
    }

    Logger *Logger::GetInstance()
    {
        return _instance == 0 ? _instance = new Logger() : _instance;
    }

    void Logger::Setup(int baudrate)
    {
        Serial.begin(baudrate);
        Serial.println();
        Serial.println();
    }

    void Logger::Logln(const string message)
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

    void Logger::LogTable(const String tag, LoggerTable data)
    {
        using namespace ArduinoLinq;
        // TODO: Rewrite function using boolinq, when isssue is resoolved. https://github.com/k06a/boolinq/issues/45
        // Invalid data -> stop here.
        if (data.empty() || data.at(0).empty())
        {
            Error("Logger::LogTable: Paramert data is not allowed to be empty.");
            return;
        }

        // Get for each column the longest content.
        auto columnsPerRow = data.at(0).size();
        Debug("columnsPerRow " + String(columnsPerRow));

        auto columnTextLengths = vector<int>(columnsPerRow, 0);

        for (auto &row : data)
            for (size_t i = 0; i < row.size(); i++)
            {
                if (columnTextLengths[i] < row[i].length())
                    columnTextLengths[i] = row[i].length();
            }

        auto tableWidth = (from(columnTextLengths) >> sum()) + columnsPerRow * 2 + 1; // " |" per col.
        Debug("tableWidth " + String(tableWidth));
        // auto tableWidth = boolinq::from(columnTextLengths).sum() + columnsPerRow * 2 + 1;

        // Now print the data.
        PrintLine(tag, tableWidth);
        for (auto &row : data)
        {
            String rowStr = "|";
            for (size_t i = 0; i < row.size(); i++)
            {
                auto missingSpaces = columnTextLengths[i] - row[i].length();
                rowStr += " " + row[i] + String(missingSpaces, ' ') + "|";
            }
            Logln(tag, rowStr);
        }
        PrintLine(tag, tableWidth);
    }

    void Logger::PrintLine(const String tag, const int length)
    {
        // TODO: REmove debug.
        auto x = std::string(length, '-');
        Debug(x);
        Logln(tag, x);
    }

    void Logger::PrintLine(const String tag)
    {
        Logln(tag, String(LineLength, '-'));
    }

    void Logger::PrintLine()
    {
        PrintLine(LineTag);
    }

    void Logger::Warning(const String message)
    {
        Logln(WarningTag, message);
    }

    void Logger::Error(const String message)
    {
        Logln(ErrorTag, message);
    }

    void Logger::Debug(const String message)
    {
        Logln(DebugTag, message);
    }
} // namespace Services
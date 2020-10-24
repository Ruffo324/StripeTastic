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

    void Logger::Listen(std::function<void(String)> outFunction)
    {
        _listeners.push_back(outFunction);
    }

    void Logger::SendToListeners(String message)
    {
        for (auto &listener : _listeners)
        {
            listener(message);
        }
    }

    void Logger::Logln(const String message)
    {
        Logln(UnknownTag, message);
    }

    void Logger::Log(const String message)
    {
        Serial.print(message);
        SendToListeners(message);
    }

    void Logger::Logln(const String tag, const String message)
    {
        auto combinedMessage = TagToPrefix(tag) + message;
        Serial.println(combinedMessage);
        SendToListeners(combinedMessage);
    }

    void Logger::Log(const String tag, const String message)
    {
        this->Log(TagToPrefix(tag) + message);
    }

    void Logger::Linebreak()
    {
        Serial.println();
        SendToListeners("\n");
    }

    String Logger::TagToPrefix(const String tag)
    {
        // TODO: DateTime synced from NTP server.
        return "[" + tag + "] ";
    }

    void Logger::LogTable(const String tag, LoggerTable data, bool firstIsHeader, bool topBottomBorder)
    {
        using namespace ArduinoLinq;
        // TODO: Rewrite function using boolinq, when isssue is resoolved. https://github.com/k06a/boolinq/issues/45
        // TODO: Create settings struct instead of parameters with default values.
        // Invalid data -> stop.
        if (data.empty() || data.at(0).empty())
        {
            Error("Logger::LogTable: Paramert data is not allowed to be empty.");
            return;
        }

        // Get for each column the longest content.
        auto columnsPerRow = data.at(0).size();
        auto columnTextLengths = vector<int>(columnsPerRow, 0);
        for (auto &row : data)
            for (size_t i = 0; i < row.size(); i++)
            {
                if (columnTextLengths[i] < row[i].length())
                    columnTextLengths[i] = row[i].length();
            }

        auto tableWidth = (from(columnTextLengths) >> sum()) + columnsPerRow * 3 + 1; // "| |" per col.

        if (topBottomBorder)
            PrintLine(tag, tableWidth);

        // Now print the data.
        auto headerWritten = false;
        for (auto &row : data)
        {
            String rowStr = "|";
            for (size_t i = 0; i < row.size(); i++)
            {
                auto missingSpaces = columnTextLengths[i] - row[i].length();
                rowStr += " " + row[i] + RepeatChar(missingSpaces, ' ') + " |";
            }
            Logln(tag, rowStr);

            // Write header border if wanted.
            if (firstIsHeader && !headerWritten)
            {
                PrintLine(tag, tableWidth);
                headerWritten = true;
            }
        }

        if (topBottomBorder)
            PrintLine(tag, tableWidth);
    }

    void Logger::PrintLine(const String tag, const int length)
    {
        Logln(tag, RepeatChar(length, '-'));
    }

    String Logger::RepeatChar(const int length, const char padChar)
    {
        // TODO: Rebuild this function. Not satisfied with it.
        String string = "";
        for (int i = 0; i < length; i++)
        {
            string += padChar;
        }
        return string;
    }

    void Logger::PrintLine(const String tag)
    {
        Logln(tag, RepeatChar(LineLength, '-'));
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
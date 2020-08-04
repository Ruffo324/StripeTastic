#pragma once
#include <Arduino.h>
#include <Logger.h>

namespace Services
{
    class WebService
    {
    public:
        WebService();

    private:
        Logger *_logger;
    };
} // namespace Services
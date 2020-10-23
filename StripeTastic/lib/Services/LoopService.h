#pragma once
#include <Arduino.h>
#include <functional>
#include <map>

namespace Services
{
    class LoopService
    {
    public:
        static LoopService *GetInstance();
        void InvokeLoop();
        void Register(String key, std::function<void()> function);
        void Register(String key, std::function<void()> function, int intervalMs);
        void Unregister(String key);

    private:
        LoopService();
        static LoopService *_instance;
        std::map<String, std::function<void()>> _registeredFunctions;
    };
} // namespace Services
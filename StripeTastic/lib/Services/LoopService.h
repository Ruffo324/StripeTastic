#pragma once
#include <Arduino.h>
#include <functional>
#include <map>

namespace Services
{
    class LoopService
    {
    public:
        struct Registration
        {
            int IntervalMs;
            long LastCalled;
            std::function<void()> Function;
        };
        static LoopService *GetInstance();
        void InvokeLoop();
        void Register(String key, std::function<void()> function, int intervalMs = 0);
        void Unregister(String key);

    private:
        LoopService();
        static LoopService *_instance;
        std::map<String, Registration> _registrations;
    };
} // namespace Services
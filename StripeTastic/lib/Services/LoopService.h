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
            String Key;
            int IntervalMs;
            long LastCalled;
            std::function<void()> Function;
        };
        static LoopService *GetInstance();
        void InvokeLoop();
        void Register(String key, std::function<void()> function);
        /**
         * @brief Registers the given function for loop calls, but with the given interval.
         * 
         * @param key The loop registration key.
         * @param function The function wich get's executed.
         * @param intervalMs intervall between each call.
         */
        void Register(String key, std::function<void()> function, int intervalMs);
        void Unregister(String key);

    private:
        LoopService();
        static LoopService *_instance;
        std::map<String, Registration> _registrations;
    };
} // namespace Services
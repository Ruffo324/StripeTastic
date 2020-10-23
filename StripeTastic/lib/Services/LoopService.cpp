#include "LoopService.h"

namespace Services
{
    LoopService *LoopService::_instance = 0;
    std::map<String, LoopService::Registration> _registrations;

    LoopService::LoopService()
    {
    }

    LoopService *LoopService::GetInstance()
    {
        return _instance == 0 ? _instance = new LoopService() : _instance;
    }

    void LoopService::InvokeLoop()
    {
        for (auto &item : _registrations)
        {
            auto registration = item.second;

            auto currentMs = millis();
            if (registration.IntervalMs == 0 || currentMs - registration.LastCalled >= registration.IntervalMs)
            {
                registration.LastCalled = currentMs;
                registration.Function();
            }
        }
    }

    void LoopService::Register(String key, std::function<void()> function, int intervalMs)
    {
        Registration newRegistration;
        newRegistration.Function = function;
        newRegistration.IntervalMs = intervalMs;
        newRegistration.LastCalled = 0;

        _registrations[key] = newRegistration;
    }

    void LoopService::Unregister(String key)
    {
        auto position = _registrations.find(key);
        if (position != _registrations.end())
            _registrations.erase(position);
    }
} // namespace Services
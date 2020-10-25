#include "Looper.h"

namespace Services
{
    Looper *Looper::_instance = 0;

    Looper::Looper()
    {
    }

    Looper *Looper::GetInstance()
    {
        return _instance == 0 ? _instance = new Looper() : _instance;
    }

    void Looper::InvokeLoop()
    {
        for (auto &item : _registrations)
        {
            // TODO: This does not look like the right way. Fix it.
            auto &registration = _registrations[item.first];

            auto currentMs = millis();
            if (registration.IntervalMs == 0 || currentMs - registration.LastCalled >= registration.IntervalMs)
            {
                registration.LastCalled = currentMs;
                registration.Function();
            }
        }
    }

    void Looper::Register(String key, std::function<void()> function, int intervalMs)
    {
        Registration newRegistration;
        newRegistration.Function = function;
        newRegistration.IntervalMs = intervalMs;
        newRegistration.LastCalled = 0;

        _registrations[key] = newRegistration;
    }

    void Looper::Unregister(String key)
    {
        auto position = _registrations.find(key);
        if (position != _registrations.end())
            _registrations.erase(position);
    }
} // namespace Services
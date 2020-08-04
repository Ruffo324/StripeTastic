#include "LoopService.h"

namespace Services
{
    LoopService *LoopService::_instance = 0;
    std::map<String, std::function<void()>> _registeredFunctions;

    LoopService::LoopService()
    {
    }

    LoopService *LoopService::GetInstance()
    {
        return _instance == 0 ? _instance = new LoopService() : _instance;
    }

    void LoopService::InvokeLoop()
    {
        for (auto &loopFunction : _registeredFunctions)
        {
            loopFunction.second();
        }
        delay(LoopDelayMs);
    }

    void LoopService::Register(String key, std::function<void()> function)
    {
        _registeredFunctions[key] = function;
    }

    void LoopService::Unregister(String key)
    {
        auto position = _registeredFunctions.find(key);
        if (position != _registeredFunctions.end())
            _registeredFunctions.erase(position);
    }
} // namespace Services
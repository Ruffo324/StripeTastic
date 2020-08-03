#include "LoopService.h"

namespace Services
{
    LoopService *LoopService::_instance = 0;

    LoopService::LoopService()
    {
    }

    LoopService *LoopService::GetInstance()
    {
        if (!_instance == 0)
            _instance = new LoopService();

        // return _instance == 0 ? _instance = new LoopService() : _instance;
        return _instance;
    }

    void LoopService::InvokeLoop()
    {
        for (auto loopFunction : _registeredFunctions)
        {
            loopFunction();
        }
    }

    void LoopService::RegisterFunction(std::function<void()> function)
    {
        _registeredFunctions.push_back(function);
    }

    void LoopService::UnregisterFunction(std::function<void()> function)
    {
        auto position = std::find(_registeredFunctions.begin(), _registeredFunctions.end(), function);
        if (position != _registeredFunctions.end())
            _registeredFunctions.erase(position);
    }
} // namespace Services
#include <Arduino.h>
#include <functional>

namespace Services
{
    class LoopService
    {
    public:
        static LoopService *GetInstance();
        void InvokeLoop();
        void RegisterFunction(std::function<void()> function);
        void UnregisterFunction(std::function<void()> function);

    private:
        LoopService();
        static LoopService *_instance;
        std::vector<std::function<void()>> _registeredFunctions;
    };
} // namespace Services
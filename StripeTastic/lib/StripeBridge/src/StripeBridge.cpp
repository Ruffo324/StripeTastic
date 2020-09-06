#include "StripeBridge.h"
#include "Services.h"
#include "Configuration.h"

namespace StripeBridge
{
    String StripeBridge::_loggerTag = "B-STRIPE";

    bool StripeBridge::_environmentSetupDone = false;
    int StripeBridge::_totalStripeInstances = 0;

    // StripeBridge::_logger = Services::Logger::GetInstance();
    // auto _loopService = Services::LoopService::GetInstance();

    void StripeBridge::EnvironmentSetup()
    {
        pinMode(Configuration::GPIOMicrophonePin, INPUT);
        pinMode(Configuration::GPIOAuxLeftPin, INPUT);
        pinMode(Configuration::GPIOAuxRightPin, INPUT);

        analogReadResolution(Configuration::AnalogReadResolutionBits);

        _environmentSetupDone = true;
        Services::Logger::GetInstance()->Log(_loggerTag, "Environment setup done..");
    }

    int StripeBridge::GetNewStripeInstanceId()
    {
        while (!_environmentSetupDone)
        {
            Services::Logger::GetInstance()->Error("Invalid operation: StripeBridge::EnvironmentSetup() must be executed before a StripeInstance can be created.");
            delay(10 * 1000); // TODO: Write clean exception handler.
        }

        return _totalStripeInstances++;
    }

} // namespace StripeBridge

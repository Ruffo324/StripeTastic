#include "StripeBridge.h"
#include "Services.h"
#include "Configuration.h"

namespace StripeBridge
{
    const String _loggerTag = "S-BRIDGE";
    auto _logger = Services::Logger::GetInstance();

    bool StripeBridge::_environmentSetupDone = false;
    int StripeBridge::_totalStripeInstances = 0;

    void StripeBridge::EnvironmentSetup()
    {
        pinMode(Configuration::GPIOMicrophonePin, INPUT);
        pinMode(Configuration::GPIOAuxLeftPin, INPUT);
        pinMode(Configuration::GPIOAuxRightPin, INPUT);

        analogReadResolution(Configuration::AnalogReadResolutionBits);

        _environmentSetupDone = true;
        _logger->Log(_loggerTag, "Environment setup done..");
    }

    int StripeBridge::GetNewStripeInstanceId()
    {
        while (!_environmentSetupDone)
        {
            _logger->Error("Invalid operation: StripeBridge::EnvironmentSetup() must be executed before a StripeInstance can be created.");
            delay(10 * 1000); // TODO: Write clean exception handler.
        }

        return _totalStripeInstances++;
    }

} // namespace StripeBridge
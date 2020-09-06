#include "StripeBridge.h"
#include "Services.h"

namespace StripeBridge
{
    const String _loggerTag = "S-BRIDGE";
    auto _logger = Services::Logger::GetInstance();

    bool StripeBridge::_environmentSetupDone = false;
    int StripeBridge::_totalStripeInstances = 0;

    void StripeBridge::EnvironmentSetup()
    {

        _logger->Log(_loggerTag, "Environment setup done..");
    }

    int StripeBridge::GetNewStripeInstanceId()
    {
    }

} // namespace StripeBridge
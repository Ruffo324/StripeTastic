#include <Arduino.h>
#include <functional>
#include "LoopService.h"

namespace Services
{
    /// Bundles all WiFi stuff in one usefull class.
    class WifiService
    {
    public:
        WifiService();
        bool Connect(const String ssid, const String password);

        void CreateAccessPoint();
        void Reset();

    private:
        std::function<void()> _processDnsFunction; // TODO: cleaner way, then store the lambad in an varible.
        bool _accesPointMode;
        LoopService *_loopService;
        void processDns();
    };
} // namespace Services
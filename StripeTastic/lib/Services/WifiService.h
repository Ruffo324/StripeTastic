#include <Arduino.h>
#include <functional>
#include <LoopService.h>
#include <Logger.h>
#include <DNSServer.h>

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
        bool _accesPointMode;
        LoopService *_loopService;
        Logger *_logger;
        DNSServer _dnsServer;
        void setHostname();
        String getMacSuffix();
    };
} // namespace Services
#include "../Logger/Logger.h"
#include "../Looper/Looper.h"
#include <Arduino.h>
#include <DNSServer.h>
#include <WiFi.h>
#include <functional>

namespace Services
{
    // TODO: Rename to WiFiService (cases..)
    /// Bundles all WiFi stuff in one usefull class.
    class WifiService
    {
    public:
        struct WiFiNetwork
        {
            // TODO: complete scanning of wifi networks
            WiFiNetwork(int scanId)
            {
                Ssid = WiFi.SSID(scanId);
                RssiDbm = WiFi.RSSI(scanId);
            }
            String Ssid;
            long RssiDbm;
        };

        WifiService();
        bool Connect(const String ssid, const String password);

        void CreateAccessPoint();
        void Reset();
        // Searchs for wifi networks and returns them as vector.
        std::vector<WiFiNetwork> GetAroundWiFiNetworks();

    private:
        const String _loggerTag = "WiFi";
        bool _accesPointMode;
        Looper *_loopService;
        Logger *_logger;
        DNSServer _dnsServer;
        void setHostname();
        String getMacSuffix();
    };
} // namespace Services
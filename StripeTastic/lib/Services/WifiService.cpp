#include <WifiService.h>
#include <Configuration.h>
#include <LoopService.h>
#include <Logger.h>
#include <DNSServer.h>

#include <WiFi.h>
#include <ESPAsyncWebServer.h>

namespace Services
{
    const String _loggerTag = "WiFi";
    const String _dnsLoopKey = "WIFI-DNS";

    WifiService::WifiService()
    {
        _logger = Logger::GetInstance();
        _loopService = LoopService::GetInstance();
        setHostname();
    }

    void WifiService::setHostname()
    {
        // TODO: Read hostname here from settings.
        auto hostname = Configuration::DefaultHostnamePrefix + getMacSuffix();
        WiFi.setHostname(hostname.c_str());
        _logger->Logln(_loggerTag, "Hostname set to \"" + hostname + "\"");
    }

    bool WifiService::Connect(const String ssid, const String password)
    {
        const int connectionCheckDelayMs = 500;
        _logger->Log(_loggerTag, "Connecting to \"" + ssid + "\" ...");

        WiFi.begin(ssid.c_str(), password.c_str());
        while (WiFi.status() != WL_CONNECTED)
        {
            _logger->Log(".");
            delay(connectionCheckDelayMs);

            if (WiFi.status() == WL_CONNECT_FAILED)
            {
                _logger->Linebreak();
                _logger->Logln(_loggerTag, "Connection failed. Check ssid and password.");
                return false;
            }
        }
        _logger->Linebreak();

        Services::LoggerTable logTable = {
            {"Connected with", ssid},
            {"Password", password},
            {"Local IP", WiFi.localIP().toString()},
            {"Gateway", WiFi.gatewayIP().toString()},
        };
        _logger->LogTable(_loggerTag, logTable);
        return true;
    }

    void WifiService::CreateAccessPoint()
    {
        const int dnsServerPort = 53;
        const int maxConnections = 4;
        const int channel = 1;

        _accesPointMode = true;
        auto ssid = Configuration::SsidPrefix + getMacSuffix();
        auto password = Configuration::DefaultPassword;

        WiFi.softAP(ssid.c_str(), password.c_str(), channel, 0, maxConnections);
        _dnsServer.start(dnsServerPort, "*", WiFi.softAPIP());

        _loopService->Register(_dnsLoopKey, [this]() { _dnsServer.processNextRequest(); });

        _logger->Logln(_loggerTag, "Access point should now be connectable.");
        Services::LoggerTable logTable = {
            {"SSID", ssid},
            {"Password", password},
            {"Gateway", WiFi.gatewayIP().toString()},
            {"DNS port", String(dnsServerPort)},
            {"Local IP", WiFi.localIP().toString()},
        };
        _logger->LogTable(_loggerTag, logTable);
    }

    String WifiService::getMacSuffix()
    {
        uint8_t mac[6];
        char macSuffix[6] = {0};
        WiFi.macAddress(mac);
        sprintf(macSuffix, "%02X%02X%02X", mac[3], mac[4], mac[5]);
        return macSuffix;
    }

    void WifiService::Reset()
    {
        _logger->Logln(_loggerTag, "Resetting WifiService..");
        if (_accesPointMode)
        {
            _logger->Logln(_loggerTag, "WifiService was in access point mode.");

            _loopService->Unregister(_dnsLoopKey);
            _dnsServer.stop();
            WiFi.softAPdisconnect();
            _accesPointMode = false;
        }
        else
        {
            _logger->Logln(_loggerTag, "WifiService was in router mode.");
            WiFi.disconnect();
        }
        _logger->Logln(_loggerTag, "Resetting WifiService done.");
    }
} // namespace Services

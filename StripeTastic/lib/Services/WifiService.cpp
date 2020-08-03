#include <WifiService.h>
#include <Configuration.h>
#include "LoopService.h"

#include <DNSServer.h>
#include <WiFi.h>
#include "ESPAsyncWebServer.h"

DNSServer dnsServer;

namespace Services
{
    WifiService::WifiService()
    {
        _loopService = LoopService::GetInstance();
        _processDnsFunction = [this]() { processDns(); };
    }

    bool WifiService::Connect(const String ssid, const String password)
    {
        return true;
    }

    void WifiService::CreateAccessPoint()
    {
        const int macAddressCutAt = 8;
        auto loopService = LoopService::GetInstance();

        _accesPointMode = true;
        auto ssid = Configuration::SsidPrefix + WiFi.macAddress().substring(macAddressCutAt);
        auto password = Configuration::DefaultPassword;
        WiFi.softAP(ssid.c_str(), password.c_str());
        dnsServer.start(53, "*", WiFi.softAPIP());

        _loopService->RegisterFunction(_processDnsFunction);
    }

    void WifiService::Reset()
    {
        if (_accesPointMode)
        {
            _loopService->UnregisterFunction(_processDnsFunction);
            dnsServer.stop();
            WiFi.softAPdisconnect();
        }
    }

    void WifiService::processDns()
    {
        dnsServer.processNextRequest();
    }
} // namespace Services

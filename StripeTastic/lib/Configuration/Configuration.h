#pragma once
#include <Arduino.h>

class Configuration
{
public:
    /// WiFi SSID prefix for the access point. Followed by the last MAC part.
    static String SsidPrefix;
    static String DefaultHostname;

    /// The default password for the access point.
    static String DefaultPassword;

    static int Baudrate;
    static int LoopDelayMs;

    static bool Debug;

    static uint16_t DefaultWebServerPort;
    static String IndexPageName;
};
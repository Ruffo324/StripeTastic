#pragma once
#include <Arduino.h>

class Configuration
{
public:
    /// WiFi SSID prefix for the access point. Followed by the last MAC part.
    static String SsidPrefix;
    static String DefaultHostnamePrefix;

    /// The default password for the access point.
    static String DefaultPassword;

    static int Baudrate;
    static int LoopDelayMs;

    static bool Debug;
};
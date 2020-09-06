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

    static bool Debug;

    static uint16_t DefaultWebServerPort;
    static String IndexPageName;

    /// GPIO Pin number for the microphone.
    static int GPIOMicrophonePin;
    /// GPIO Pin number for the left aux channel.
    static int GPIOAuxLeftPin;
    /// GPIO Pin number for the right aux channel.
    static int GPIOAuxRightPin;

    static int AnalogReadResolutionBits;
};
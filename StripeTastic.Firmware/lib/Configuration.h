#pragma once
#include <Arduino.h>

namespace Configuration
{
    /// WiFi SSID prefix for the access point. Followed by the last MAC part.
    static auto const SsidPrefix = "StripeTastic_";
    static auto const DefaultHostname = "led";

    /// The default password for the access point.
    static auto const DefaultPassword = "oase1234";

    static auto const Baudrate = 115200;

    static auto const Debug = true;

    static auto const DefaultWebServerPort = 80;
    static auto const IndexPageName = "index.html";

    /// GPIO Pin number for the microphone.
    static auto const GPIOMicrophonePin = 34;

    /// GPIO Pin number for the left aux channel.
    static auto const GPIOAuxLeftPin = 35;

    /// GPIO Pin number for the right aux channel.
    static auto const GPIOAuxRightPin = 25;

    static auto const AnalogReadResolutionBits = 10;
}; // namespace Configuration

#include <Arduino.h>

class Configuration
{
public:
    /// WiFi SSID prefix for the access point. Followed by the last MAC part.
    static String SsidPrefix;

    /// The default password for the access point.
    static String DefaultPassword;
};
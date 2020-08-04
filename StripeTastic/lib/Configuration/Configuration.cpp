#include <Configuration.h>

String Configuration::SsidPrefix = "StripeTastic_";
String Configuration::DefaultHostnamePrefix = "StripeTastic_";
String Configuration::DefaultPassword = "oase1234";

int Configuration::Baudrate = 115200;
int Configuration::LoopDelayMs = 1000;

bool Configuration::Debug = true;

uint16_t Configuration::DefaultWebServerPort = 80;
String Configuration::IndexPageName = "index.html";

#include <Configuration.h>
#include <Services.h>
#include <StripeBridge.h>
#include <StripeInstance.h>

auto logger = Services::Logger::GetInstance();
Services::WifiService *_wifiService;
Services::LoopService *_loopService;
Services::FileService *_fileService;
Services::WebService *_webService;

void setupServices()
{
    // Setup loop service.
    _loopService = Services::LoopService::GetInstance();
    _loopService->LoopDelayMs = Configuration::LoopDelayMs;

    // Initialize FileService.
    _fileService = new Services::FileService();
    _fileService->ScanFileSystem();

    // WifiService, accespoint (later from config)
    _wifiService = new Services::WifiService();
    // _wifiService->CreateAccessPoint();
    _wifiService->Connect("***REMOVED***", "***REMOVED***");
    _wifiService->Reset();

    // WebService, route static files.
    auto staticFiles = _fileService->GetStaticFiles();
    _webService = new Services::WebService();
    _webService->RebuildFileRoutes(staticFiles);
    _webService->Start();
}

StripeBridge::StripeInstance<NeoEsp32Rmt0800KbpsMethod> *_stripeOne;
StripeBridge::StripeInstance<NeoEsp32Rmt1800KbpsMethod> *_stripeTwo;

void setup()
{
    // Setup logger.
    logger->Setup(Configuration::Baudrate);

    // LedBridge
    StripeBridge::StripeBridge::EnvironmentSetup();

    // Led stripe one
    const int stripeOnePin = 23, stripeOnePixel = 60;
    _stripeOne = new StripeBridge::StripeInstance<NeoEsp32Rmt0800KbpsMethod>(stripeOnePin, stripeOnePixel);

    // Led stripe two
    const int stripeTwoPin = 23, stripeTwoPixel = 60;
    _stripeTwo = new StripeBridge::StripeInstance<NeoEsp32Rmt1800KbpsMethod>(stripeTwoPin, stripeTwoPixel);
}

void loop()
{
    _loopService->InvokeLoop();
}

// _webService->RegisterRestCall("/effects/strobe/speed", [](JsonObject data) { stroboSpeed = data["speed"]; });
// _webService->RegisterRestCall("/effects/color", [](JsonObject data) {
//     stripeColor = RgbColor(data["red"], data["green"], data["blue"]);
//     setColor(&stripe1, stripeColor);
//     // setColor(&stripe-2, stripeColor);
// });
// _webService->RegisterRestCall("/effects/strobe/on", [](JsonObject data) {
//     strobeOn = data["on"];
// });

// _loopService->Register("led_strobo", []() {
//     if (strobeOn)
//     {
//         strobo(&stripe1, stroboSpeed);
//         // strobo(&stripe2, stroboSpeed);
//     }
// });
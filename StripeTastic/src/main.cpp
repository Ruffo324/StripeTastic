
#include <Configuration.h>
#include <Services.h>
#include <LedBridge.h>

Services::WifiService *_wifiService;
Services::LoopService *_loopService;
Services::FileService *_fileService;
Services::WebService *_webService;

void setup()
{
    // Setup logger.
    auto logger = Services::Logger::GetInstance();
    logger->Setup(Configuration::Baudrate);

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

    // LedBridge
    LedBridge::Initalize();
    _loopService->Register("LEDBRIDGE_LOOP", []() { LedBridge::InvokeLoop(); });
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
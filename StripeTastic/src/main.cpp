
#define CONFIG_ASYNC_TCP_RUNNING_CORE 0 //any available core
#define CONFIG_ASYNC_TCP_USE_WDT 0      //if enabled, adds between 33us and 200us per event

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
    // _wifiService->Reset();

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

    setupServices();

    // LedBridge
    StripeBridge::StripeBridge::EnvironmentSetup();

    // Led stripe one
    const int stripeOnePin = 23, stripeOnePixel = 300;
    _stripeOne = new StripeBridge::StripeInstance<NeoEsp32Rmt0800KbpsMethod>(stripeOnePin, stripeOnePixel);

    // Led stripe two
    const int stripeTwoPin = 21, stripeTwoPixel = 300;
    _stripeTwo = new StripeBridge::StripeInstance<NeoEsp32Rmt1800KbpsMethod>(stripeTwoPin, stripeTwoPixel);

    // Register REST listener for both stripes.
    _webService->RegisterRestCall("/processdata/stripe1", [](JsonObject data) {
        auto newProcessData = StripeBridge::Models::StripeProcessingData::FromJsonObject(data);
        _stripeOne->UpdateProcessingData(newProcessData);
    });
    _webService->RegisterRestCall("/processdata/stripe2", [](JsonObject data) {
        auto newProcessData = StripeBridge::Models::StripeProcessingData::FromJsonObject(data);
        _stripeTwo->UpdateProcessingData(newProcessData);
    });
}

void loop()
{
    _loopService->InvokeLoop();
}
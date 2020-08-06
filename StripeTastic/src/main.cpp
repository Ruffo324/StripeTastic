
#include <Configuration.h>
#include <Services.h>
#include <NeoPixelBus.h>
#include <NeoPixelAnimator.h>

Services::WifiService *_wifiService;
Services::LoopService *_loopService;
Services::FileService *_fileService;
Services::WebService *_webService;

// typedef NeoGrbwFeature MyPixelColorFeature;

// Stripe setup
const int amountLeds = 20;
typedef NeoPixelBus<NeoRbgFeature, NeoEsp32BitBang800KbpsMethod> stripeDef;
stripeDef stripe1(amountLeds, 23);
stripeDef stripe2(amountLeds, 21);

// strobe Variablen
std::map<stripeDef *, long> timerJeLed = {
    {&stripe1, 0},
    {&stripe2, 0},
};

// strobe Variablen
unsigned long ltime = 0;
std::map<stripeDef *, bool> durchlaufJeLed = {
    {&stripe1, false},
    {&stripe2, false},
};

void strobo(stripeDef *stripe, int f)
{
    auto ntime = millis();
    if (ntime - timerJeLed[stripe] >= (1000 / f))
    {
        RgbColor color = (durchlaufJeLed[stripe] = !durchlaufJeLed[stripe]) ? RgbColor(255, 255, 255) : RgbColor(0, 0, 0);
        for (uint16_t i = 0; i < (*stripe).PixelCount(); i++)
            (*stripe).SetPixelColor(i, color);
        timerJeLed[stripe] = ntime;
        (*stripe).Show();
    }
}

void setColor(stripeDef *stripe, RgbColor color)
{
    for (uint16_t i = 0; i < (*stripe).PixelCount(); i++)
        (*stripe).SetPixelColor(i, color);
    (*stripe).Show();
}

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
    _wifiService->CreateAccessPoint();
    // _wifiService->Connect("***REMOVED***", "***REMOVED***");
    // _wifiService->Reset();

    // WebService, route static files.
    auto staticFiles = _fileService->GetStaticFiles();
    _webService = new Services::WebService();
    _webService->RebuildFileRoutes(staticFiles);
    _webService->Start();

    // _loopService->Register("Beispiel", []() { Serial.print("got called from loop"); });
    stripe1.Begin();
    stripe2.Begin();
    setColor(&stripe1, RgbColor(25, 0, 25));
    setColor(&stripe2, RgbColor(0, 25, 0));

    // auto takt = 70;
    // _loopService->Register("fun_service", [takt]() {
    //     strobo(&stripe1, takt);
    //     strobo(&stripe2, takt);
    // });
}

void loop()
{
    _loopService->InvokeLoop();
    // funLeds();
}
// void doWithPixels(function<void()> func)
// {
// }
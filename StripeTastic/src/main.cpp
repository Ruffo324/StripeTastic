
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
const int amountLeds = 12;
// typedef NeoPixelBus<NeoGrbFeature, NeoEsp32BitBang800KbpsMethod> stripeDef;
typedef NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod> stripeDef;
stripeDef stripe1(amountLeds, 23);
// stripeDef stripe2(amountLeds, 21);

// strobe Variablen
std::map<stripeDef *, long> timerJeLed = {
    {&stripe1, 0},
    // {&stripe2, 0},
};

// strobe Variablen
unsigned long ltime = 0;
std::map<stripeDef *, bool> durchlaufJeLed = {
    {&stripe1, false},
    // {&stripe2, false},
};

int stroboSpeed = 60;
RgbColor stripeColor(128, 128, 128);
RgbColor colorOff(0, 0, 0);

void strobo(stripeDef *stripe, int f)
{
    auto ntime = millis();
    if (ntime - timerJeLed[stripe] >= (1000 / f))
    {
        RgbColor color = (durchlaufJeLed[stripe] = !durchlaufJeLed[stripe]) ? stripeColor : colorOff;
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

bool strobeOn = true;
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

    // _loopService->Register("Beispiel", []() { Serial.print("got called from loop"); });
    stripe1.Begin();
    // stripe2.Begin();
    setColor(&stripe1, RgbColor(25, 0, 25));
    // setColor(&stripe2, RgbColor(0, 25, 0));

    _webService->RegisterRestCall("/effects/strobe/speed", [](JsonObject data) { stroboSpeed = data["speed"]; });
    _webService->RegisterRestCall("/effects/color", [](JsonObject data) {
        stripeColor = RgbColor(data["red"], data["green"], data["blue"]);
        setColor(&stripe1, stripeColor);
        // setColor(&stripe-2, stripeColor);
    });
    _webService->RegisterRestCall("/effects/strobe/on", [](JsonObject data) {
        strobeOn = data["on"];
    });

    _loopService->Register("led_strobo", []() {
        if (strobeOn)
        {
            strobo(&stripe1, stroboSpeed);
            // strobo(&stripe2, stroboSpeed);
        }
    });
}

void loop()
{
    _loopService->InvokeLoop();
    // funLeds();
}
// void doWithPixels(function<void()> func)
// {
// }
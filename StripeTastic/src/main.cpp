
#include <Configuration.h>
#include <Services.h>
#include <NeoPixelBus.h>
#include <NeoPixelAnimator.h>

Services::WifiService *_wifiService;
Services::LoopService *_loopService;
Services::FileService *_fileService;
Services::WebService *_webService;

// typedef NeoGrbwFeature MyPixelColorFeature;

const int amountLeds = 20;
NeoPixelBus<NeoRbgFeature, NeoEsp32BitBang800KbpsMethod> strip1(amountLeds, 21);
NeoPixelBus<NeoRgbFeature, NeoEsp32BitBang800KbpsMethod> strip2(amountLeds, 23);

int red = 0;
int green = 0;
int blue = 0;
int loopcounts = 0;

#define colorSaturation 128
RgbColor col_red(colorSaturation, 0, 0);
RgbColor col_green(0, colorSaturation, 0);
RgbColor col_blue(0, 0, colorSaturation);
RgbColor col_white(colorSaturation);
RgbColor black(0);

void funLeds()
{
    int max = 128;
    RgbColor color(red, green, blue);
    // Serial.println("r " + String(red) + " g " + String(green) + " b " + String(blue));
    for (int i = 0; i < amountLeds; i++)
    {
        strip1.SetPixelColor(i, color);
        strip2.SetPixelColor(i, color);
    }
    strip1.Show();
    strip2.Show();

    loopcounts++;
    if (loopcounts - max > 0)
    {
        red--;
        // green--;
        blue--;
    }
    else
    {
        red++;
        // green++;
        blue++;
    }

    if (loopcounts >= (2 * max))
        loopcounts = 0;
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
    // _loopService->Register("fun_service", funLeds);
    strip1.Begin();
    strip2.Begin();
    for (int i = 0; i < amountLeds; i++)
    {
        strip1.SetPixelColor(i, black);
        strip2.SetPixelColor(i, black);
    }
    strip1.Show();
    strip2.Show();
}

void loop()
{
    // _loopService->InvokeLoop();
    funLeds();
}
// void doWithPixels(function<void()> func)
// {
// }
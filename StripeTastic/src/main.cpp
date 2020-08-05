#include <Configuration.h>
#include <Services.h>

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
    _wifiService->CreateAccessPoint();
    // _wifiService->Connect("***REMOVED***", "***REMOVED***");
    // _wifiService->Reset();

    // WebService, route static files.
    auto staticFiles = _fileService->GetStaticFiles();
    _webService = new Services::WebService();
    _webService->RebuildFileRoutes(staticFiles);
    _webService->Start();

    // _loopService->Register("Beispiel", []() { Serial.print("got called from loop"); });
}

void loop()
{
    _loopService->InvokeLoop();
}
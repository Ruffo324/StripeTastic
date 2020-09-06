#include "StripeInstance.h"
#include "StripeBridge.h"
#include "Constants/Colors.h"
#include "Services.h"
#include "Enums/ColorModes.h"

namespace StripeBridge
{
    template <class TRmtMethod>
    void StripeInstance<TRmtMethod>::Initialize()
    {
        _stripeBus.Begin();
        LoadOrCreateProcessingData();
        _loopService->Register(_loopRegistrationKey, [this]() { LoopProcessing(); });

        _logger->Log(_loggerTag, "Stripe '" + _loopRegistrationKey + "' is ready.");
        Off();
    }

    template <class TRmtMethod>
    StripeInstance<TRmtMethod>::StripeInstance(int pin, int pixelCount)
        : _stripeBus(pixelCount, pin), _information(), _processingData()
    {
        _logger = Services::Logger::GetInstance();
        _loopService = Services::LoopService::GetInstance();

        pinMode(pin, OUTPUT);

        this->_information.GPIOPin = pin;
        this->_information.PixelCount = pixelCount;

        this->_loopRegistrationKey = "STRIPE_INSTANCE_" + StripeBridge::GetNewStripeInstanceId();

        _logger->Log(_loggerTag, "Stripe " + _loopRegistrationKey + "(GPIO: " + pin + ", Pixels:" + pixelCount + " ) created..");
        Initialize();
    }

    int solidColorsTest = 0;
    template <class TRmtMethod>
    void StripeInstance<TRmtMethod>::LoopProcessing()
    {
        delay(3000); // Debug
        switch (solidColorsTest)
        {
        case 0:
            SolidUserColor(Enums::ColorMode::OneUserColor);
            break;
        case 1:
            SolidUserColor(Enums::ColorMode::TwoUserColors);
            break;
        case 2:
            SolidUserColor(Enums::ColorMode::ThreeUserColors);
            solidColorsTest = -1;
            break;
        default:
            _logger->Log(_loggerTag, "Ahhh invalid debug test loop code. Fuu myself!");
            return;
        }
        solidColorsTest++;
        // TODO: LOOP processing.
    }

    template <class TRmtMethod>
    void StripeInstance<TRmtMethod>::LoadOrCreateProcessingData()
    {
        // TODO: Store and load processing data.!
        ResetProcessingData();
    }

    template <class TRmtMethod>
    void StripeInstance<TRmtMethod>::ResetProcessingData()
    {
        _processingData = Models::StripeProcessingData();
    }

    template <class TRmtMethod>
    void StripeInstance<TRmtMethod>::Show(bool setBrightness)
    {
        if (setBrightness)
            _stripeBus.SetBrightness(_processingData.Brightness);

        _stripeBus.Show();
    }

    template <class TRmtMethod>
    void StripeInstance<TRmtMethod>::SetPixelColor(uint16_t pixel, RgbColor color)
    {
        // TODO: Add here event call to web client for live preview.
        _stripeBus.SetPixelColor(pixel, color);
    }

    template <class TRmtMethod>
    void StripeInstance<TRmtMethod>::Off()
    {
        for (int i = 0; i < _information.PixelCount; i++)
            _stripeBus.SetPixelColor(i, Constants::Colors::Off);
        Show(false);
    }

    template <class TRmtMethod>
    void StripeInstance<TRmtMethod>::SolidUserColor(Enums::ColorMode colorMode)
    {
        auto totalPixel = _information.PixelCount;

        switch (colorMode)
        {
        // Single user ncolor.
        case Enums::ColorMode::OneUserColor:
        {
            for (int i = 0; i < totalPixel; i++)
                SetPixelColor(i, _processingData.LED_farbe_1);
            break;
        }
        // Two user colors.
        case Enums::ColorMode::TwoUserColors:
        {
            auto segmentPixel = _information.PixelCountTwoColors();

            for (uint16_t i = 0; i < segmentPixel; i++)
                SetPixelColor(i, _processingData.LED_farbe_1);
            for (uint16_t i = segmentPixel; i < totalPixel; i++)
                SetPixelColor(i, _processingData.LED_farbe_2);
            break;
        }
        // Three user colos.
        case Enums::ColorMode::ThreeUserColors:
        {
            auto segmentPixel = _information.PixelCountThreeColors();

            for (uint16_t i = 0; i < segmentPixel; i++)
                SetPixelColor(i, _processingData.LED_farbe_1);
            for (uint16_t i = segmentPixel; i < segmentPixel * 2; i++)
                SetPixelColor(i, _processingData.LED_farbe_2);
            for (uint16_t i = segmentPixel * 2; i < totalPixel; i++)
                SetPixelColor(i, _processingData.LED_farbe_3);
            break;
        }
        // Invalid ColorModes.
        default:
            _logger->Log(_loggerTag, "StripeInstance::SolidUserColor() can only be used with user base Enums::ColorModes.");
            return;
        }
        Show();
    }

} // namespace StripeBridge

template class StripeBridge::StripeInstance<NeoEsp32RmtMethodBase<NeoEsp32RmtSpeed800Kbps, NeoEsp32RmtChannel0>>;
template class StripeBridge::StripeInstance<NeoEsp32RmtMethodBase<NeoEsp32RmtSpeed800Kbps, NeoEsp32RmtChannel1>>;

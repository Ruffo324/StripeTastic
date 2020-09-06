#include "StripeInstance.h"
#include "StripeBridge.h"
#include "Constants/Colors.h"

namespace StripeBridge
{
    const String _loggerTag = "STRIPE";

    template <class TRmtMethod>
    void StripeInstance<TRmtMethod>::Initialize()
    {
        _stripeBus.Begin();
        _loopService->Register(_loopRegistrationKey, [this]() { LoopProcessing(); });

        _logger->Log(_loggerTag, "Stripe '" + _loopRegistrationKey + "' is ready.");
    }

    template <class TRmtMethod>
    StripeInstance<TRmtMethod>::StripeInstance(int pin, int pixelCount)
        : _stripeBus(pixelCount, pin), _information(), _processingData()
    {
        pinMode(pin, OUTPUT);

        _logger = Logger::GetInstance();
        _loopService = LoopService::GetInstance();

        this->_information.GPIOPin = pin;
        this->_information.PixelCount = pixelCount;

        this->_loopRegistrationKey = "STRIPE_INSTANCE_" + StripeBridge::GetNewStripeInstanceId();

        _logger->Log(_loggerTag, "Stripe " + _loopRegistrationKey + "(GPIO: " + pin + ", Pixels:" + pixelCount + " ) created..");
    }

    template <class TRmtMethod>
    void StripeInstance<TRmtMethod>::LoopProcessing()
    {
        // TODO: LOOP processing.
    }

    template <class TRmtMethod>
    void StripeInstance<TRmtMethod>::Off()
    {
        for (int i = 0; i < _information.PixelCount; i++)
            _stripeBus.SetPixelColor(i, Constants::Colors::Off);
        _stripeBus.Show();
    }

} // namespace StripeBridge
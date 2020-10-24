#pragma once

#include <type_traits>
#include <NeoPixelBrightnessBus.h>
#include "Models/StripeProcessingData.h"
#include "Models/StripeInformation.h"
#include "Models/StripeEffectsData.h"
#include "Services.h"

namespace StripeBridge
{
    template <typename TRmtMethod>
    class StripeInstance
    {
        static_assert(std::is_same<NeoEsp32I2s1800KbpsMethod, TRmtMethod>::value ||
                          std::is_same<NeoEsp32I2s0800KbpsMethod, TRmtMethod>::value,
                      "TRmtMethod must be one of the 'NeoEsp32I2sXYZKbpsMethod' types.");

        const String _loggerTag = "STRIPE";
    private:
        Services::Logger *_logger;
        Services::LoopService *_loopService;
        Services::WebService *_webService;

        NeoPixelBrightnessBus<NeoGrbFeature, TRmtMethod> _stripeBus;
        std::vector<long> _pixels;
        Models::StripeInformation _information;
        Models::StripeProcessingData _processingData;
        Models::StripeEffectsData _effectsData;
        String _loopRegistrationKey;
        bool _processingDataChanged;

        void Initialize();
        // TODO: Re-initialize, to change pixel count at runtime.
        void LoopProcessing();
        void PixelUpdateEvent();

        /// Loads the last used ProcessingData from the storage.
        void LoadOrCreateProcessingData();
        /// Saves the current ProcessingData to the storage.
        void StoreProcessingData();
        /// Resets the stored and current ProcessingData to default.
        void ResetProcessingData();

        /// Adjusts the stripe brightness and calls the stripe show function.
        void Show(bool setBrightness = true);
        /// Calls neopixel setPixelColor function and also stores the color as long in _pixels.
        void SetPixelColor(uint16_t pixel, RgbColor color);
        /// Turns every pixel on the stripe off.
        void Off(bool withShow = true);
        /// Solid color for each pixel, but based on the color mode. (1color, 2color, ...)
        void SolidUserColor(Enums::ColorMode colorMode);

        // TODO: Functions wich needs cleanup.
        void programm(); // TODO: Change name to "HandleProcessData"
        static int check_micro(bool micro_aux);
        void rainbow();
        void zufall();
        // ==================== Effects
        void strobo();
        void ball();
        void ballstackable();
        void ballStackableToCenter();
        void vu_centre();
        void vunormal();
        void lavalampemove();

        void movingRainbow();
        void fillup();
        void fillup2();
        void fillup3();
        void fillup4();

    public:
        StripeInstance(int pin, int pixelCount, Services::WebService *webService);
        /// Updates the stripe processing data struct.
        void UpdateProcessingData(Models::StripeProcessingData processingData);
    };

} // namespace StripeBridge
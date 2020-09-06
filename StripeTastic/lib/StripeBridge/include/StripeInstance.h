#pragma once

#include <type_traits>
#include <NeoPixelBrightnessBus.h>
#include "Models/StripeProcessingData.h"
#include "Models/StripeInformation.h"

namespace StripeBridge
{
    template <typename TRmtMethod>
    class StripeInstance
    {
        static_assert(
            std::is_same<NeoEsp32Rmt0800KbpsMethod, TRmtMethod>::value ||
                std::is_same<NeoEsp32Rmt0400KbpsMethod, TRmtMethod>::value ||
                std::is_same<NeoEsp32Rmt1800KbpsMethod, TRmtMethod>::value ||
                std::is_same<NeoEsp32Rmt1400KbpsMethod, TRmtMethod>::value ||
                std::is_same<NeoEsp32Rmt2800KbpsMethod, TRmtMethod>::value ||
                std::is_same<NeoEsp32Rmt2400KbpsMethod, TRmtMethod>::value ||
                std::is_same<NeoEsp32Rmt3800KbpsMethod, TRmtMethod>::value ||
                std::is_same<NeoEsp32Rmt3400KbpsMethod, TRmtMethod>::value,
            "TRmtMethod must be one of the 'NeoEsp32RmtXYYYKbpsMethod' types.");

    private:
        NeoPixelBrightnessBus<NeoGrbFeature, TRmtMethod> _stripeBus;
        Models::StripeInformation _information;
        Models::StripeProcessingData _processingData;
        String _loopRegistrationKey;

        void Initialize();
        void LoopProcessing();

        /// Loads the last used ProcessingData from the storage.
        void LoadOrCreateProcessingData();
        /// Saves the current ProcessingData to the storage.
        void StoreProcessingData();
        /// Resets the stored and current ProcessingData to default.
        void ResetProcessingData();

        /// Adjusts the stripe brightness and calls the stripe show function.
        void Show(bool setBrightness = true);
        /// Calls neopixel setPixelColor function, but can also send realtime informations to client for virtualization.
        void SetPixelColor(uint16_t pixel, RgbColor color);
        /// Turns every pixel on the stripe off.
        void Off();
        /// Solid color for each pixel, but based on the color mode. (1color, 2color, ...)
        void SolidUserColor(Enums::ColorMode colorMode);

        // TODO: Re-initialize, to change pixel count at runtime.
    public:
        StripeInstance(int pin, int pixelCount);
        /// Updates the stripe processing data struct.
        void UpdateProcessingData(Models::StripeProcessingData processingData);
    };

} // namespace StripeBridge
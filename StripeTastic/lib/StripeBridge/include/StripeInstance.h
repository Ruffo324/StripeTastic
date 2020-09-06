#pragma once

#include <type_traits>
#include <NeoPixelBrightnessBus.h>
#include "Models/StripeProcessingData.h"
#include "Models/StripeInformation.h"
#include "Services.h"

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
        /** Used to generate uniqe loop registrationkeys. */
        static int _stripeInstancesEverCreated; // TODO: Find cleaner solution.

        NeoPixelBrightnessBus<NeoGrbFeature, TRmtMethod> _stripeBus;
        Models::StripeInformation _information;
        Models::StripeProcessingData _processingData;
        String _loopRegistrationKey;

        Services::Logger *_logger;
        Services::LoopService *_loopService;

        void Initialize();
        void LoopProcessing();
        // TODO: Re-initialize, to change pixel count at runtime.
    public:
        StripeInstance(int pin, int pixelCount);
    };

} // namespace StripeBridge
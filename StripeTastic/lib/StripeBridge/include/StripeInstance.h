#pragma once

#include <type_traits>
#include <NeoPixelBrightnessBus.h>

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
        T _rmtMethod;

    public:
        StripeInstance(T /* args */);
    };

} // namespace StripeBridge
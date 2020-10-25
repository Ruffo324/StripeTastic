#pragma once

#include <NeoPixelBus.h>

namespace StripeBridge
{
    class Colors
    {
    private:
    public:
        /// No color, no light, just off.
        static RgbColor Off;

        static RgbColor Red;
        static RgbColor Green;
        static RgbColor Blue;
        static RgbColor White;
        static RgbColor Pink;
        static RgbColor Gelb;
        static RgbColor Orange;
        static RgbColor Teal;
        static RgbColor Lila;
        static RgbColor Cyan;

        /** 
             * Predefined color set used by ColorModes::Random. 
             */
        static std::vector<RgbColor> RandomColors;

        /// Gives u a random color from the RandomColors vector.
        static RgbColor GetRandomColor();
        static RgbColor Wheel(byte wheelPos);
        static RgbColor Wheel(long x, long in_min, long in_max, long out_min, long out_max);
        static long ToInt(RgbColor color);
    };
} // namespace StripeBridge
#pragma once

#include <NeoPixelBus.h>

namespace StripeBridge
{
    namespace Constants
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
            static RgbColor RandomColors[];
        };
    } // namespace Constants
} // namespace StripeBridge
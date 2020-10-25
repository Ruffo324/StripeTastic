#pragma once

#include <NeoPixelBus.h>

namespace StripeBridge
{
    namespace Colors
    {
        /// No color, no light, just off.
        static inline auto const Off = RgbColor(0, 0, 0);

        static inline auto const Red = RgbColor(255, 0, 0);
        static inline auto const Green = RgbColor(0, 255, 0);
        static inline auto const Blue = RgbColor(0, 0, 255);
        static inline auto const White = RgbColor(200, 200, 200);
        static inline auto const Pink = RgbColor(239, 79, 117);
        static inline auto const Yellow = RgbColor(255, 241, 82);
        static inline auto const Orange = RgbColor(255, 130, 1);
        static inline auto const Teal = RgbColor(0, 200, 200);
        static inline auto const Lila = RgbColor(200, 0, 200);
        static inline auto const Cyan = RgbColor(75, 196, 213);

        /**
         * Set of random colors.
         */
        static inline std::vector<RgbColor> const RandomColors = {
            Red,
            Green,
            Blue,
            White,
            Pink,
            Yellow,
            Orange,
            Teal,
            Lila,
            Cyan,
        };
        
        /// Gives u a random color from the RandomColors vector.
        RgbColor GetRandomColor()
        {
            return RandomColors[random((int)RandomColors.size() + 1)];
        }

        long ToInt(RgbColor color)
        {
            return ((color.R & 0xff) << 16) + ((color.G & 0xff) << 8) + (color.B & 0xff);
        }

        RgbColor FromIntValues(int red, int green, int blue)
        {
            return {static_cast<uint8_t>(red), static_cast<uint8_t>(green), static_cast<uint8_t>(blue)};
        }

        RgbColor Wheel(uint8_t wheelPos)
        {
            if (wheelPos < 85)
            {
                return FromIntValues(wheelPos * 3, 255 - wheelPos * 3, 0);
            }
            else if (wheelPos < 170)
            {
                wheelPos -= 85;
                return FromIntValues(255 - wheelPos * 3, 0, wheelPos * 3);
            }
            else
            {
                wheelPos -= 170;
                return FromIntValues(0, wheelPos * 3, 255 - wheelPos * 3);
            }
        }

        RgbColor Wheel(long x, long in_min, long in_max, long out_min, long out_max)
        {
            return Wheel((x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min);
        }
    } // namespace Colors
} // namespace StripeBridge
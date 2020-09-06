#include <iterator>
#include "Constants/Colors.h"

namespace StripeBridge
{
    namespace Constants
    {
        RgbColor Colors::Off = RgbColor(0, 0, 0);

        RgbColor Colors::Red = RgbColor(255, 0, 0);
        RgbColor Colors::Green = RgbColor(0, 255, 0);
        RgbColor Colors::Blue = RgbColor(0, 0, 255);
        RgbColor Colors::White = RgbColor(200, 200, 200);
        RgbColor Colors::Pink = RgbColor(239, 79, 117);
        RgbColor Colors::Gelb = RgbColor(255, 241, 82);
        RgbColor Colors::Orange = RgbColor(255, 130, 1);
        RgbColor Colors::Teal = RgbColor(0, 200, 200);
        RgbColor Colors::Lila = RgbColor(200, 0, 200);
        RgbColor Colors::Cyan = RgbColor(75, 196, 213);

        std::vector<RgbColor> Colors::RandomColors = {
            Colors::Red,
            Colors::Green,
            Colors::Blue,
            Colors::White,
            Colors::Pink,
            Colors::Gelb,
            Colors::Orange,
            Colors::Teal,
            Colors::Lila,
            Colors::Cyan,
        };

        RgbColor Colors::GetRandomColor()
        {
            return RandomColors[random(RandomColors.size())];
        }

        RgbColor Colors::Wheel(byte wheelPos)
        {
            if (wheelPos < 85)
            {
                return RgbColor(wheelPos * 3, 255 - wheelPos * 3, 0);
            }
            else if (wheelPos < 170)
            {
                wheelPos -= 85;
                return RgbColor(255 - wheelPos * 3, 0, wheelPos * 3);
            }
            else
            {
                wheelPos -= 170;
                return RgbColor(0, wheelPos * 3, 255 - wheelPos * 3);
            }
        }

        } // namespace Constants
} // namespace StripeBridge
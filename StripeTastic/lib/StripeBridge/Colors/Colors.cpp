#pragma once
#include "Colors.h"
#include <Arduino.h>
#include <stdio.h>

namespace StripeBridge
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
        return RandomColors[random(RandomColors.size() + 1)];
    }

    RgbColor Colors::Wheel(long x, long in_min, long in_max, long out_min, long out_max)
    {
        return Wheel((x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min);
    }

    long Colors::ToInt(RgbColor color)
    {
        return ((color.R & 0xff) << 16) + ((color.G & 0xff) << 8) + (color.B & 0xff);
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
} // namespace StripeBridge
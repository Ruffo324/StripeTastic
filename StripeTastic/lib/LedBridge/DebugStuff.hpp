#pragma once

#include <Arduino.h>
#include <NeoPixelBrightnessBus.h>
#include "arduinoFFT.h"
#include "./LedBridge.hpp"

namespace LedBridge
{
    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    //                                                Test                                                  //
    //////////////////////////////////////////////////////////////////////////////////////////////////////////

    void test1(void)
    {
        p_strip1.StripeIndex = 0;
        p_strip1.mode = Modes::Effect;
        p_strip1.effect = Effects::Strobo;
        p_strip1.effectDirection = EffectDirection::Left;
        p_strip1.Licht = ColorMode::UserColors;
        p_strip1.Brightness = 200;
        p_strip1.FlashPerSeconds = 30;
        p_strip1.EffectDelay = 50;
        p_strip1.Intensity = 100.0;
        p_strip1.LED_farbe_1 = RgbColor(0, 255, 255);
        p_strip1.LED_farbe_2 = RgbColor(255, 0, 0);
        p_strip1.LED_farbe_3 = RgbColor(0, 255, 0);
        p_strip1.LED_farbe_4 = RgbColor(0, 0, 255);
        p_strip1.Changed = 1;
        p_strip1.IsAux = 0;
        p_strip1.FFTAktive = 0;

        p_strip2.StripeIndex = 1;
        p_strip2.mode = Modes::Effect;
        p_strip2.effect = Effects::Strobo;
        p_strip2.effectDirection = EffectDirection::Left;
        p_strip2.Licht = ColorMode::UserColors;
        p_strip2.Brightness = 200;
        p_strip2.FlashPerSeconds = 35;
        p_strip2.EffectDelay = 50;
        p_strip2.Intensity = 100.0;
        p_strip2.LED_farbe_1 = RgbColor(255, 0, 255);
        p_strip2.LED_farbe_2 = RgbColor(255, 0, 0);
        p_strip2.LED_farbe_3 = RgbColor(0, 255, 0);
        p_strip2.LED_farbe_4 = RgbColor(0, 0, 255);
        p_strip2.Changed = 1;
        p_strip2.IsAux = 0;
        p_strip2.FFTAktive = 0;
    }

    void test2(void)
    {
        p_strip1.StripeIndex = 0;
        p_strip1.mode = Modes::Effect;
        p_strip1.effect = Effects::Ball;
        p_strip1.effectDirection = EffectDirection::Left;
        p_strip1.Licht = ColorMode::Random;
        p_strip1.Brightness = 200;
        p_strip1.FlashPerSeconds = 30;
        p_strip1.EffectDelay = 50;
        p_strip1.Intensity = 100.0;
        p_strip1.LED_farbe_1 = RgbColor(0, 255, 255);
        p_strip1.LED_farbe_2 = RgbColor(255, 0, 0);
        p_strip1.LED_farbe_3 = RgbColor(0, 255, 0);
        p_strip1.LED_farbe_4 = RgbColor(0, 0, 255);
        p_strip1.Changed = 1;
        p_strip1.IsAux = 0;
        p_strip1.FFTAktive = 0;

        p_strip2.StripeIndex = 1;
        p_strip2.mode = Modes::Effect;
        p_strip2.effect = Effects::Ball;
        p_strip2.effectDirection = EffectDirection::Left;
        p_strip2.Licht = ColorMode::Random;
        p_strip2.Brightness = 200;
        p_strip2.FlashPerSeconds = 30;
        p_strip2.EffectDelay = 50;
        p_strip2.Intensity = 100.0;
        p_strip2.LED_farbe_1 = RgbColor(255, 0, 255);
        p_strip2.LED_farbe_2 = RgbColor(255, 0, 0);
        p_strip2.LED_farbe_3 = RgbColor(0, 255, 0);
        p_strip2.LED_farbe_4 = RgbColor(0, 0, 255);
        p_strip2.Changed = 1;
        p_strip2.IsAux = 0;
        p_strip2.FFTAktive = 0;
    }

    void test3(void)
    {
        p_strip1.StripeIndex = 0;
        p_strip1.mode = Modes::Effect;
        p_strip1.effect = Effects::BallStackable;
        p_strip1.effectDirection = EffectDirection::Left;
        p_strip1.Licht = ColorMode::Random;
        p_strip1.Brightness = 200;
        p_strip1.FlashPerSeconds = 30;
        p_strip1.EffectDelay = 50;
        p_strip1.Intensity = 100.0;
        p_strip1.LED_farbe_1 = RgbColor(0, 255, 255);
        p_strip1.LED_farbe_2 = RgbColor(255, 0, 0);
        p_strip1.LED_farbe_3 = RgbColor(0, 255, 0);
        p_strip1.LED_farbe_4 = RgbColor(0, 0, 255);
        p_strip1.Changed = 1;
        p_strip1.IsAux = 0;
        p_strip1.FFTAktive = 0;

        p_strip2.StripeIndex = 1;
        p_strip2.mode = Modes::Effect;
        p_strip2.effect = Effects::BallStackable;
        p_strip2.effectDirection = EffectDirection::Left;
        p_strip2.Licht = ColorMode::Random;
        p_strip2.Brightness = 200;
        p_strip2.FlashPerSeconds = 30;
        p_strip2.EffectDelay = 50;
        p_strip2.Intensity = 100.0;
        p_strip2.LED_farbe_1 = RgbColor(255, 0, 255);
        p_strip2.LED_farbe_2 = RgbColor(255, 0, 0);
        p_strip2.LED_farbe_3 = RgbColor(0, 255, 0);
        p_strip2.LED_farbe_4 = RgbColor(0, 0, 255);
        p_strip2.Changed = 1;
        p_strip2.IsAux = 0;
        p_strip2.FFTAktive = 0;
    }

    void test4(void)
    {
        p_strip1.StripeIndex = 0;
        p_strip1.mode = Modes::Effect;
        p_strip1.effect = Effects::BallStackableToCenter;
        p_strip1.effectDirection = EffectDirection::Left;
        p_strip1.Licht = ColorMode::Random;
        p_strip1.Brightness = 200;
        p_strip1.FlashPerSeconds = 30;
        p_strip1.EffectDelay = 50;
        p_strip1.Intensity = 100.0;
        p_strip1.LED_farbe_1 = RgbColor(0, 255, 255);
        p_strip1.LED_farbe_2 = RgbColor(255, 0, 0);
        p_strip1.LED_farbe_3 = RgbColor(0, 255, 0);
        p_strip1.LED_farbe_4 = RgbColor(0, 0, 255);
        p_strip1.Changed = 1;
        p_strip1.IsAux = 0;
        p_strip1.FFTAktive = 0;

        p_strip2.StripeIndex = 1;
        p_strip2.mode = Modes::Effect;
        p_strip2.effect = Effects::BallStackableToCenter;
        p_strip2.effectDirection = EffectDirection::Left;
        p_strip2.Licht = ColorMode::Random;
        p_strip2.Brightness = 200;
        p_strip2.FlashPerSeconds = 30;
        p_strip2.EffectDelay = 50;
        p_strip2.Intensity = 100.0;
        p_strip2.LED_farbe_1 = RgbColor(255, 0, 255);
        p_strip2.LED_farbe_2 = RgbColor(255, 0, 0);
        p_strip2.LED_farbe_3 = RgbColor(0, 255, 0);
        p_strip2.LED_farbe_4 = RgbColor(0, 0, 255);
        p_strip2.Changed = 1;
        p_strip2.IsAux = 0;
        p_strip2.FFTAktive = 0;
    }

    void test5(void)
    {
        p_strip1.StripeIndex = 0;
        p_strip1.mode = Modes::Effect;
        p_strip1.effect = Effects::MusicFromCenter;
        p_strip1.effectDirection = EffectDirection::Left;
        p_strip1.Licht = ColorMode::Rainbow;
        p_strip1.Brightness = 200;
        p_strip1.FlashPerSeconds = 30;
        p_strip1.EffectDelay = 10;
        p_strip1.Intensity = 400.0;
        p_strip1.LED_farbe_1 = RgbColor(0, 255, 255);
        p_strip1.LED_farbe_2 = RgbColor(255, 0, 0);
        p_strip1.LED_farbe_3 = RgbColor(0, 255, 0);
        p_strip1.LED_farbe_4 = RgbColor(0, 0, 255);
        p_strip1.Changed = 1;
        p_strip1.IsAux = 0;
        p_strip1.FFTAktive = 0;

        p_strip2.StripeIndex = 1;
        p_strip2.mode = Modes::Effect;
        p_strip2.effect = Effects::MusicFromCenter;
        p_strip2.effectDirection = EffectDirection::Left;
        p_strip2.Licht = ColorMode::Rainbow;
        p_strip2.Brightness = 200;
        p_strip2.FlashPerSeconds = 30;
        p_strip2.EffectDelay = 10;
        p_strip2.Intensity = 400.0;
        p_strip2.LED_farbe_1 = RgbColor(255, 0, 255);
        p_strip2.LED_farbe_2 = RgbColor(255, 0, 0);
        p_strip2.LED_farbe_3 = RgbColor(0, 255, 0);
        p_strip2.LED_farbe_4 = RgbColor(0, 0, 255);
        p_strip2.Changed = 1;
        p_strip2.IsAux = 0;
        p_strip2.FFTAktive = 0;
    }

    void test16(void)
    {
        p_strip1.StripeIndex = 0;
        p_strip1.mode = Modes::Effect;
        p_strip1.effect = Effects::Music;
        p_strip1.effectDirection = EffectDirection::Left;
        p_strip1.Licht = ColorMode::Rainbow;
        p_strip1.Brightness = 200;
        p_strip1.FlashPerSeconds = 30;
        p_strip1.EffectDelay = 10;
        p_strip1.Intensity = 500.0;
        p_strip1.LED_farbe_1 = RgbColor(0, 255, 255);
        p_strip1.LED_farbe_2 = RgbColor(255, 0, 0);
        p_strip1.LED_farbe_3 = RgbColor(0, 255, 0);
        p_strip1.LED_farbe_4 = RgbColor(0, 0, 255);
        p_strip1.Changed = 1;
        p_strip1.IsAux = 0;
        p_strip1.FFTAktive = 0;

        p_strip2.StripeIndex = 1;
        p_strip2.mode = Modes::Effect;
        p_strip2.effect = Effects::Music;
        p_strip2.effectDirection = EffectDirection::Left;
        p_strip2.Licht = ColorMode::Rainbow;
        p_strip2.Brightness = 200;
        p_strip2.FlashPerSeconds = 30;
        p_strip2.EffectDelay = 10;
        p_strip2.Intensity = 500.0;
        p_strip2.LED_farbe_1 = RgbColor(255, 0, 255);
        p_strip2.LED_farbe_2 = RgbColor(255, 0, 0);
        p_strip2.LED_farbe_3 = RgbColor(0, 255, 0);
        p_strip2.LED_farbe_4 = RgbColor(0, 0, 255);
        p_strip2.Changed = 1;
        p_strip2.IsAux = 0;
        p_strip2.FFTAktive = 0;
    }

    void test6(void)
    {
        p_strip1.StripeIndex = 0;
        p_strip1.mode = Modes::Effect;
        p_strip1.effect = Effects::LavaLamp;
        p_strip1.effectDirection = EffectDirection::Left;
        p_strip1.Licht = ColorMode::Random;
        p_strip1.Brightness = 200;
        p_strip1.FlashPerSeconds = 30;
        p_strip1.EffectDelay = 50;
        p_strip1.Intensity = 100.0;
        p_strip1.LED_farbe_1 = RgbColor(0, 255, 255);
        p_strip1.LED_farbe_2 = RgbColor(255, 0, 0);
        p_strip1.LED_farbe_3 = RgbColor(0, 255, 0);
        p_strip1.LED_farbe_4 = RgbColor(0, 0, 255);
        p_strip1.Changed = 1;
        p_strip1.IsAux = 0;
        p_strip1.FFTAktive = 0;

        p_strip2.StripeIndex = 1;
        p_strip2.mode = Modes::Effect;
        p_strip2.effect = Effects::LavaLamp;
        p_strip2.effectDirection = EffectDirection::Left;
        p_strip2.Licht = ColorMode::Random;
        p_strip2.Brightness = 200;
        p_strip2.FlashPerSeconds = 30;
        p_strip2.EffectDelay = 50;
        p_strip2.Intensity = 100.0;
        p_strip2.LED_farbe_1 = RgbColor(255, 0, 255);
        p_strip2.LED_farbe_2 = RgbColor(255, 0, 0);
        p_strip2.LED_farbe_3 = RgbColor(0, 255, 0);
        p_strip2.LED_farbe_4 = RgbColor(0, 0, 255);
        p_strip2.Changed = 1;
        p_strip2.IsAux = 0;
        p_strip2.FFTAktive = 0;
    }

    void test7(void)
    {
        p_strip1.StripeIndex = 0;
        p_strip1.mode = Modes::Effect;
        p_strip1.effect = Effects::MovingRainbow;
        p_strip1.effectDirection = EffectDirection::Left;
        p_strip1.Licht = ColorMode::Rainbow;
        p_strip1.Brightness = 200;
        p_strip1.FlashPerSeconds = 30;
        p_strip1.EffectDelay = 5;
        p_strip1.Intensity = 100.0;
        p_strip1.LED_farbe_1 = RgbColor(0, 255, 255);
        p_strip1.LED_farbe_2 = RgbColor(255, 0, 0);
        p_strip1.LED_farbe_3 = RgbColor(0, 255, 0);
        p_strip1.LED_farbe_4 = RgbColor(0, 0, 255);
        p_strip1.Changed = 1;
        p_strip1.IsAux = 0;
        p_strip1.FFTAktive = 0;

        p_strip2.StripeIndex = 1;
        p_strip2.mode = Modes::Effect;
        p_strip2.effect = Effects::MovingRainbow;
        p_strip2.effectDirection = EffectDirection::Left;
        p_strip2.Licht = ColorMode::Rainbow;
        p_strip2.Brightness = 200;
        p_strip2.FlashPerSeconds = 30;
        p_strip2.EffectDelay = 50;
        p_strip2.Intensity = 100.0;
        p_strip2.LED_farbe_1 = RgbColor(255, 0, 255);
        p_strip2.LED_farbe_2 = RgbColor(255, 0, 0);
        p_strip2.LED_farbe_3 = RgbColor(0, 255, 0);
        p_strip2.LED_farbe_4 = RgbColor(0, 0, 255);
        p_strip2.Changed = 1;
        p_strip2.IsAux = 0;
        p_strip2.FFTAktive = 0;
    }

    void test8(void)
    {
        p_strip1.StripeIndex = 0;
        p_strip1.mode = Modes::Effect;
        p_strip1.effect = Effects::FillUp;
        p_strip1.effectDirection = EffectDirection::Left;
        p_strip1.Licht = ColorMode::Random;
        p_strip1.Brightness = 200;
        p_strip1.FlashPerSeconds = 30;
        p_strip1.EffectDelay = 5;
        p_strip1.Intensity = 100.0;
        p_strip1.LED_farbe_1 = RgbColor(0, 255, 255);
        p_strip1.LED_farbe_2 = RgbColor(255, 0, 0);
        p_strip1.LED_farbe_3 = RgbColor(0, 255, 0);
        p_strip1.LED_farbe_4 = RgbColor(0, 0, 255);
        p_strip1.Changed = 1;
        p_strip1.IsAux = 0;
        p_strip1.FFTAktive = 0;

        p_strip2.StripeIndex = 1;
        p_strip2.mode = Modes::Effect;
        p_strip2.effect = Effects::FillUp;
        p_strip2.effectDirection = EffectDirection::Left;
        p_strip2.Licht = ColorMode::Random;
        p_strip2.Brightness = 200;
        p_strip2.FlashPerSeconds = 30;
        p_strip2.EffectDelay = 50;
        p_strip2.Intensity = 100.0;
        p_strip2.LED_farbe_1 = RgbColor(255, 0, 255);
        p_strip2.LED_farbe_2 = RgbColor(255, 0, 0);
        p_strip2.LED_farbe_3 = RgbColor(0, 255, 0);
        p_strip2.LED_farbe_4 = RgbColor(0, 0, 255);
        p_strip2.Changed = 1;
        p_strip2.IsAux = 0;
        p_strip2.FFTAktive = 0;
    }

    void test9(void)
    {
        p_strip1.StripeIndex = 0;
        p_strip1.mode = Modes::Effect;
        p_strip1.effect = Effects::FillUp2;
        p_strip1.effectDirection = EffectDirection::Left;
        p_strip1.Licht = ColorMode::Random;
        p_strip1.Brightness = 200;
        p_strip1.FlashPerSeconds = 30;
        p_strip1.EffectDelay = 50;
        p_strip1.Intensity = 100.0;
        p_strip1.LED_farbe_1 = RgbColor(0, 255, 255);
        p_strip1.LED_farbe_2 = RgbColor(255, 0, 0);
        p_strip1.LED_farbe_3 = RgbColor(0, 255, 0);
        p_strip1.LED_farbe_4 = RgbColor(0, 0, 255);
        p_strip1.Changed = 1;
        p_strip1.IsAux = 0;
        p_strip1.FFTAktive = 0;

        p_strip2.StripeIndex = 1;
        p_strip2.mode = Modes::Effect;
        p_strip2.effect = Effects::FillUp2;
        p_strip2.effectDirection = EffectDirection::Left;
        p_strip2.Licht = ColorMode::Random;
        p_strip2.Brightness = 200;
        p_strip2.FlashPerSeconds = 30;
        p_strip2.EffectDelay = 50;
        p_strip2.Intensity = 100.0;
        p_strip2.LED_farbe_1 = RgbColor(255, 0, 255);
        p_strip2.LED_farbe_2 = RgbColor(255, 0, 0);
        p_strip2.LED_farbe_3 = RgbColor(0, 255, 0);
        p_strip2.LED_farbe_4 = RgbColor(0, 0, 255);
        p_strip2.Changed = 1;
        p_strip2.IsAux = 0;
        p_strip2.FFTAktive = 0;
    }

    void test10(void)
    {
        p_strip1.StripeIndex = 0;
        p_strip1.mode = Modes::Effect;
        p_strip1.effect = Effects::FillUp3;
        p_strip1.effectDirection = EffectDirection::Left;
        p_strip1.Licht = ColorMode::Rainbow;
        p_strip1.Brightness = 200;
        p_strip1.FlashPerSeconds = 30;
        p_strip1.EffectDelay = 50;
        p_strip1.Intensity = 100.0;
        p_strip1.LED_farbe_1 = RgbColor(0, 255, 255);
        p_strip1.LED_farbe_2 = RgbColor(255, 0, 0);
        p_strip1.LED_farbe_3 = RgbColor(0, 255, 0);
        p_strip1.LED_farbe_4 = RgbColor(0, 0, 255);
        p_strip1.Changed = 1;
        p_strip1.IsAux = 0;
        p_strip1.FFTAktive = 0;

        p_strip2.StripeIndex = 1;
        p_strip2.mode = Modes::Effect;
        p_strip2.effect = Effects::FillUp3;
        p_strip2.effectDirection = EffectDirection::Left;
        p_strip2.Licht = ColorMode::Rainbow;
        p_strip2.Brightness = 200;
        p_strip2.FlashPerSeconds = 30;
        p_strip2.EffectDelay = 50;
        p_strip2.Intensity = 100.0;
        p_strip2.LED_farbe_1 = RgbColor(255, 0, 255);
        p_strip2.LED_farbe_2 = RgbColor(255, 0, 0);
        p_strip2.LED_farbe_3 = RgbColor(0, 255, 0);
        p_strip2.LED_farbe_4 = RgbColor(0, 0, 255);
        p_strip2.Changed = 1;
        p_strip2.IsAux = 0;
        p_strip2.FFTAktive = 0;
    }

    void test11(void)
    {
        p_strip1.StripeIndex = 0;
        p_strip1.mode = Modes::Effect;
        p_strip1.effect = Effects::FillUp4;
        p_strip1.effectDirection = EffectDirection::Left;
        p_strip1.Licht = ColorMode::Random;
        p_strip1.Brightness = 200;
        p_strip1.FlashPerSeconds = 30;
        p_strip1.EffectDelay = 50;
        p_strip1.Intensity = 100.0;
        p_strip1.LED_farbe_1 = RgbColor(0, 255, 255);
        p_strip1.LED_farbe_2 = RgbColor(255, 0, 0);
        p_strip1.LED_farbe_3 = RgbColor(0, 255, 0);
        p_strip1.LED_farbe_4 = RgbColor(0, 0, 255);
        p_strip1.Changed = 1;
        p_strip1.IsAux = 0;
        p_strip1.FFTAktive = 0;

        p_strip2.StripeIndex = 1;
        p_strip2.mode = Modes::Effect;
        p_strip2.effect = Effects::FillUp4;
        p_strip2.effectDirection = EffectDirection::Left;
        p_strip2.Licht = ColorMode::Random;
        p_strip2.Brightness = 200;
        p_strip2.FlashPerSeconds = 30;
        p_strip2.EffectDelay = 50;
        p_strip2.Intensity = 100.0;
        p_strip2.LED_farbe_1 = RgbColor(255, 0, 255);
        p_strip2.LED_farbe_2 = RgbColor(255, 0, 0);
        p_strip2.LED_farbe_3 = RgbColor(0, 255, 0);
        p_strip2.LED_farbe_4 = RgbColor(0, 0, 255);
        p_strip2.Changed = 1;
        p_strip2.IsAux = 0;
        p_strip2.FFTAktive = 0;
    }

    // Static rainbow
    void test12(void)
    {
        p_strip1.StripeIndex = 0;
        p_strip1.mode = Modes::Static;
        p_strip1.effect = Effects::FillUp4;
        p_strip1.effectDirection = EffectDirection::Left;
        p_strip1.Licht = ColorMode::Rainbow;
        p_strip1.Brightness = 200;
        p_strip1.FlashPerSeconds = 30;
        p_strip1.EffectDelay = 50;
        p_strip1.Intensity = 100.0;
        p_strip1.LED_farbe_1 = RgbColor(0, 255, 255);
        p_strip1.LED_farbe_2 = RgbColor(255, 0, 0);
        p_strip1.LED_farbe_3 = RgbColor(0, 255, 0);
        p_strip1.LED_farbe_4 = RgbColor(0, 0, 255);
        p_strip1.Changed = 1;
        p_strip1.IsAux = 0;
        p_strip1.FFTAktive = 0;

        p_strip2.StripeIndex = 1;
        p_strip2.mode = Modes::Static;
        p_strip2.effect = Effects::FillUp4;
        p_strip2.effectDirection = EffectDirection::Left;
        p_strip2.Licht = ColorMode::Rainbow;
        p_strip2.Brightness = 200;
        p_strip2.FlashPerSeconds = 30;
        p_strip2.EffectDelay = 50;
        p_strip2.Intensity = 100.0;
        p_strip2.LED_farbe_1 = RgbColor(255, 0, 255);
        p_strip2.LED_farbe_2 = RgbColor(255, 0, 0);
        p_strip2.LED_farbe_3 = RgbColor(0, 255, 0);
        p_strip2.LED_farbe_4 = RgbColor(0, 0, 255);
        p_strip2.Changed = 1;
        p_strip2.IsAux = 0;
        p_strip2.FFTAktive = 0;
    }

    // Static Random
    void test13(void)
    {
        p_strip1.StripeIndex = 0;
        p_strip1.mode = Modes::Static;
        p_strip1.effect = Effects::FillUp4;
        p_strip1.effectDirection = EffectDirection::Left;
        p_strip1.Licht = ColorMode::UserColors;
        p_strip1.Brightness = 200;
        p_strip1.FlashPerSeconds = 30;
        p_strip1.EffectDelay = 50;
        p_strip1.Intensity = 100.0;
        p_strip1.LED_farbe_1 = RgbColor(0, 255, 255);
        p_strip1.LED_farbe_2 = RgbColor(255, 0, 0);
        p_strip1.LED_farbe_3 = RgbColor(0, 255, 0);
        p_strip1.LED_farbe_4 = RgbColor(0, 0, 255);
        p_strip1.Changed = 1;
        p_strip1.IsAux = 0;
        p_strip1.FFTAktive = 0;

        p_strip2.StripeIndex = 1;
        p_strip2.mode = Modes::Static;
        p_strip2.effect = Effects::FillUp4;
        p_strip2.effectDirection = EffectDirection::Left;
        p_strip2.Licht = ColorMode::UserColors;
        p_strip2.Brightness = 200;
        p_strip2.FlashPerSeconds = 30;
        p_strip2.EffectDelay = 50;
        p_strip2.Intensity = 100.0;
        p_strip2.LED_farbe_1 = RgbColor(255, 0, 255);
        p_strip2.LED_farbe_2 = RgbColor(255, 0, 0);
        p_strip2.LED_farbe_3 = RgbColor(0, 255, 0);
        p_strip2.LED_farbe_4 = RgbColor(0, 0, 255);
        p_strip2.Changed = 1;
        p_strip2.IsAux = 0;
        p_strip2.FFTAktive = 0;
    }
    // Two Colors
    void test14(void)
    {
        p_strip1.StripeIndex = 0;
        p_strip1.mode = Modes::Static;
        p_strip1.effect = Effects::FillUp4;
        p_strip1.effectDirection = EffectDirection::Left;
        p_strip1.Licht = ColorMode::TwoUsercolors;
        p_strip1.Brightness = 100;
        p_strip1.FlashPerSeconds = 30;
        p_strip1.EffectDelay = 50;
        p_strip1.Intensity = 100.0;
        p_strip1.LED_farbe_1 = RgbColor(0, 255, 255);
        p_strip1.LED_farbe_2 = RgbColor(255, 0, 0);
        p_strip1.LED_farbe_3 = RgbColor(0, 255, 0);
        p_strip1.LED_farbe_4 = RgbColor(0, 0, 255);
        p_strip1.Changed = 1;
        p_strip1.IsAux = 0;
        p_strip1.FFTAktive = 0;

        p_strip2.StripeIndex = 1;
        p_strip2.mode = Modes::Static;
        p_strip2.effect = Effects::FillUp4;
        p_strip2.effectDirection = EffectDirection::Left;
        p_strip2.Licht = ColorMode::TwoUsercolors;
        p_strip2.Brightness = 100;
        p_strip2.FlashPerSeconds = 30;
        p_strip2.EffectDelay = 50;
        p_strip2.Intensity = 100.0;
        p_strip2.LED_farbe_1 = RgbColor(255, 0, 255);
        p_strip2.LED_farbe_2 = RgbColor(255, 0, 0);
        p_strip2.LED_farbe_3 = RgbColor(0, 255, 0);
        p_strip2.LED_farbe_4 = RgbColor(0, 0, 255);
        p_strip2.Changed = 1;
        p_strip2.IsAux = 0;
        p_strip2.FFTAktive = 0;
    }

    // Two Colors
    void test15(void)
    {
        p_strip1.StripeIndex = 0;
        p_strip1.mode = Modes::Static;
        p_strip1.effect = Effects::FillUp4;
        p_strip1.effectDirection = EffectDirection::Left;
        p_strip1.Licht = ColorMode::ThreeUserColors;
        p_strip1.Brightness = 100;
        p_strip1.FlashPerSeconds = 30;
        p_strip1.EffectDelay = 50;
        p_strip1.Intensity = 100.0;
        p_strip1.LED_farbe_1 = RgbColor(0, 255, 255);
        p_strip1.LED_farbe_2 = RgbColor(255, 0, 0);
        p_strip1.LED_farbe_3 = RgbColor(0, 255, 0);
        p_strip1.LED_farbe_4 = RgbColor(0, 0, 255);
        p_strip1.Changed = 1;
        p_strip1.IsAux = 0;
        p_strip1.FFTAktive = 0;

        p_strip2.StripeIndex = 1;
        p_strip2.mode = Modes::Static;
        p_strip2.effect = Effects::FillUp4;
        p_strip2.effectDirection = EffectDirection::Left;
        p_strip2.Licht = ColorMode::ThreeUserColors;
        p_strip2.Brightness = 100;
        p_strip2.FlashPerSeconds = 30;
        p_strip2.EffectDelay = 50;
        p_strip2.Intensity = 100.0;
        p_strip2.LED_farbe_1 = RgbColor(255, 0, 255);
        p_strip2.LED_farbe_2 = RgbColor(255, 0, 0);
        p_strip2.LED_farbe_3 = RgbColor(0, 255, 0);
        p_strip2.LED_farbe_4 = RgbColor(0, 0, 255);
        p_strip2.Changed = 1;
        p_strip2.IsAux = 0;
        p_strip2.FFTAktive = 0;
    }

    void debugg(void)
    {
        Serial.print("Ball= ");
        Serial.print(LeadingBall[0]);
        Serial.print(" , ");
        Serial.print(LeadingBall2[0]);
        Serial.print(" , ");
        Serial.print(LeadingBall3[0]);
        Serial.print(" , ");
        Serial.println(LeadingBall4[0]);
        Serial.println("-----------------------------------------------------------------");
    }
} // namespace LedBridge
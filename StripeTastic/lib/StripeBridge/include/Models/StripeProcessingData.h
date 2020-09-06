#pragma once

#include <Arduino.h>
#include <NeoPixelBrightnessBus.h>
#include "Enums/OperationModes.h"
#include "Enums/ColorModes.h"
#include "Enums/Effects.h"
#include "Enums/EffectDirections.h"

namespace StripeBridge
{
    namespace Models
    {
        struct StripeProcessingData
        {
            /// Speichert Modus Static, Effect, OFF
            Enums::OperationModes OperationMode = Enums::OperationModes::Static;
            /// Speichert welcher Effect abgespielt werden soll
            Enums::Effects Effect = Enums::Effects::MovingRainbow;
            /// Richtung des Effekts
            Enums::EffectDirections EffectDirection = Enums::EffectDirections::Left;
            /// Speichert Farb quelle // TODO: Rename correct after whole source implementation.
            Enums::ColorMode Licht = Enums::ColorMode::ThreeUserColors;

            /// Speichert helligkeit
            uint8_t Brightness = 255;
            /// Strobo takt
            uint8_t FlashPerSeconds = 50;
            /// 10ms - x
            int EffectDelay = 10;
            /// Scaliert  Micro/AUX  0 - 500,100= Faktor 1, 200=faktor 2
            float Intensity = 100.0;
            /// aktiviert FFT für EffectDelay Steuerung durch Musik
            bool FFTActive = false; // TODO: Check optimal default
            /// Flag die anzeigt wenn sich was ändert
            bool Changed = true; // TODO: Get rid of this..
            /// True = aux, false = mic // TODO: Create Enum::SoundSource/Input
            bool IsAux = true;

            /// Speichert Farbe 1 UserColors
            RgbColor LED_farbe_1 = RgbColor(255, 0, 0);
            /// Speichert Farbe 2 UserColors
            RgbColor LED_farbe_2 = RgbColor(0, 255, 0);
            /// Speichert Farbe 3 UserColors
            RgbColor LED_farbe_3 = RgbColor(0, 0, 255);
            /// Speichert Farbe 4 UserColors
            RgbColor LED_farbe_4 = RgbColor(255, 0, 255);
        };
    } // namespace Models
} // namespace StripeBridge
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
        struct StripeConfiguration
        {
            /** Strip nummer */
            int StripeIndex;
            /** Speichert Modus Static, Effect, OFF */
            Enums::OperationModes OperationMode;
            /** Speichert welcher Effect abgespielt werden soll */
            Enums::Effects Effect;
            /** Richtung des Effekts */
            Enums::EffectDirections EffectDirection;
            /** Speichert Farb quelle // TODO: Rename correct after whole source implementation. */
            Enums::ColorMode Licht;
            /** Speichert helligkeit */
            uint8_t Brightness;
            /** Strobo takt */
            uint8_t FlashPerSeconds;
            /** 10ms - x */
            int EffectDelay;
            /** Scaliert  Micro/AUX  0 - 500,100 = Faktor 1, 200 =faktor 2 */
            float Intensity = 100.0;
            /** aktiviert FFT für EffectDelay Steuerung durch Musik */
            bool FFTAktive;
            /** Kann weg wird durch Modes abgedeckt */
            bool Repeat;
            /** Flag die anzeigt wenn sich was ändert */
            bool Changed;
            /** True = aux, false = mic */
            bool IsAux;

            /** Speichert Farbe 1 UserColors */
            RgbColor LED_farbe_1;
            /** Speichert Farbe 2 UserColors */
            RgbColor LED_farbe_2;
            /** Speichert Farbe 3 UserColors */
            RgbColor LED_farbe_3;
            /** Speichert Farbe 4 UserColors */
            RgbColor LED_farbe_4;
        };
    } // namespace Models
} // namespace StripeBridge
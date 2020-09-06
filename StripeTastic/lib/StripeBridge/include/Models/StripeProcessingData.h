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
            uint8_t Brightness = 10;
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

            /// Compares this processingData with another one, to detect changes.
            bool IsEqal(StripeProcessingData other)
            {
                return this->OperationMode == other.OperationMode &&
                       this->Effect == other.Effect &&
                       this->EffectDirection == other.EffectDirection &&
                       this->Licht == other.Licht &&
                       this->Brightness == other.Brightness &&
                       this->FlashPerSeconds == other.FlashPerSeconds &&
                       this->EffectDelay == other.EffectDelay &&
                       this->Intensity == other.Intensity &&
                       this->FFTActive == other.FFTActive &&
                       this->Changed == other.Changed &&
                       this->IsAux == other.IsAux &&
                       this->LED_farbe_1 == other.LED_farbe_1 &&
                       this->LED_farbe_2 == other.LED_farbe_2 &&
                       this->LED_farbe_3 == other.LED_farbe_3 &&
                       this->LED_farbe_4 == other.LED_farbe_4;
            }

            static StripeProcessingData FromJsonObject(JsonObject data)
            {
                StripeProcessingData pdata = {};
                pdata.OperationMode = data["OperationMode"];
                pdata.Effect = data["Effect"];
                pdata.EffectDirection = data["EffectDirection"];
                pdata.Licht = data["Licht"];
                pdata.Brightness = data["Brightness"];
                pdata.FlashPerSeconds = data["FlashPerSeconds"];
                pdata.EffectDelay = data["EffectDelay"];
                pdata.Intensity = data["Intensity"];
                pdata.FFTActive = data["FFTActive"];
                pdata.Changed = data["Changed"];
                pdata.IsAux = data["IsAux"];
                pdata.LED_farbe_1 = ColorFromJsonData(data["LED_farbe_1"]);
                pdata.LED_farbe_2 = ColorFromJsonData(data["LED_farbe_2"]);
                pdata.LED_farbe_3 = ColorFromJsonData(data["LED_farbe_3"]);
                pdata.LED_farbe_4 = ColorFromJsonData(data["LED_farbe_4"]);
                return pdata;
            }

            static RgbColor ColorFromJsonData(JsonObject data)
            {
                return RgbColor(data["red"], data["green"], data["blue"]);
            }
        };
    } // namespace Models
} // namespace StripeBridge
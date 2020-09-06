#pragma once

#include <Arduino.h>
#include <NeoPixelBrightnessBus.h>
#include "Constants/MoreConstants.h"

namespace StripeBridge
{
    namespace Models
    {
        struct StripeEffectsData
        {
            // könnte man in der UI im Setup einstellbar machen
            int balllengh;          // relative Ball länge
            int balllengh2;         // relative Ball länge
            int balllengh3;         // relative Ball länge
            int balllengh4;         // relative Ball länge
            int balllengh_max = 10; // maximale Ball länge

            bool StroboDurchlauf = 0;
            unsigned long effectsTimer = 0; // timerJeStripe
            int LeadingBallStack = 0;
            int LeadingBall = 0;
            int LeadingBall2 = 0;
            int LeadingBall3 = 0;
            int LeadingBall4 = 0;
            int BallOverFlow = 0;
            int BallOverFlowStack = 0;
            int lavaLampPositon = 0;
            bool RichtungLavalampe = 0;
            int stepJeStripe = 0;
            int lvlJeStripe = 0;
            int minLvlAvgJeStripe = 0;
            int maxLvlAvgJeStripe = 512;
            int peakJeStripe = 0;
            int volJeStripe[Constants::SAMPLES] = {0, 0};
            int volCountJeStripe = 0;
            int dotcountJeStripe = 0;
            int stackBallleft = 0;
            int stackBallright = 0;
            int LeadingBallleft = 0;
            int LeadingBallright = 0;
            int BallOverFlowleft = 0;
            int BallOverFlowright = 0;
            int mRainbowStep = 0;
            int fillupstep = 0;
            bool durchlauffillup = 0;
            int fillup2step = 0;
            bool durchlauffillup2 = 1;
            int fillup3step = 0;
            bool durchlauffillup3 = 0;
            int fillup4step = 0;
            bool durchlauffillup4 = 0;
            int stackBallcentreleft = 0;
            int stackBallcentreright = 0;
            int BallOverFlowCentreleft = 0;
            int BallOverFlowCentreright = 0;
            RgbColor fullup4color;
            RgbColor fullup4color2;
            RgbColor fullup4color3;
            RgbColor fullup4color4;
            RgbColor fullup3color;
            RgbColor fullup3color2;
            RgbColor fullup3color3;
            RgbColor fullup2color;
            RgbColor fullup2color2;
            RgbColor lavacolor_hoch;
            RgbColor lavacolor_runter;
            RgbColor stackcentrecolor_left;
            RgbColor stackcentrecolor_right;
            RgbColor stackcolor;
            RgbColor ballcolor;
            RgbColor ballcolor2;
            RgbColor ballcolor3;
            RgbColor ballcolor4;
            RgbColor StroboColor;
            bool frist_run_ball2;
            bool frist_run_ball3;
            bool frist_run_ball4;

            void SetPixelCount(int pixelCount)
            {
                stackBallcentreright = pixelCount;
            }
        };
    } // namespace Models
} // namespace StripeBridge
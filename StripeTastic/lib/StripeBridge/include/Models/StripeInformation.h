#pragma once

namespace StripeBridge
{
    namespace Models
    {
        /** 
         * Contains some "real-life" informations about the stripe. Used GPIO pin, connected led count, etc.. 
         * TODO: Better name for this.
         * */
        struct StripeInformation
        {
            /// GPIO of the stripe data connection.
            int GPIOPin;

            /// Total amount of single LED on the used stripe.
            int PixelCount;

            int PixelCountTwoColors()
            {
                return PixelCount / 2;
            }

            int PixelCountThreeColors()
            {
                return PixelCount / 3;
            }

            int PixelCountTop() // TODO: Warum?
            {
                return PixelCount + 2;
            }
        };
    } // namespace Models
} // namespace StripeBridge
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
        };
    } // namespace Models
} // namespace StripeBridge
#pragma once

namespace StripeBridge
{
    namespace Enums
    {
        /** Defines wich color logic is used. */
        enum ColorMode
        {
            /** Fades from red to light blue. */
            Rainbow,
            /** Random color from Colors::RaindomColors. */
            Random,
            /** Single color selected by user. */
            OneUserColor,
            /** Two colors selected by user. */
            TwoUserColors,
            /** Three colors selected by user. */
            ThreeUserColors
        };
    } // namespace Enums
} // namespace StripeBridge
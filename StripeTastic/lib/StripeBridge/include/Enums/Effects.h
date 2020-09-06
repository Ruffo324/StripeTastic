namespace StripeBridge
{
    namespace Enums
    {
        /** Possible effects the stripe can show in OperationModes::Effect. */
        enum Effects
        {
            /** Stroboskop Effect */
            Strobo,
            /** vier Bälle laufen den Strip entlang */
            Ball,
            /** Ball läuft Strip entlang und stuckt am Ende */
            BallStackable,
            /** Von beiden Seiten laufen Bälle zur mitte und stucken */
            BallStackableToCenter,
            /** VU Meter Start: Stripe Anfang */
            Music,
            /** VU Meter Start: Stripe Mitte */
            MusicFromCenter,
            /** Farbe1 läuft in eine Richtung Farbe2 die andere Richtung hin und her */
            LavaLamp,
            /** Regenbogen bewegt sich entlang des Streifens */
            MovingRainbow,
            /** Füllt Streifen wiederholend mit Farbe auf */
            FillUp,
            /** Füllt Streifen wiederholden mit 2 Farben auf */
            FillUp2,
            /** Füllt Streifen wiederholend mit 3 Farben auf */
            FillUp3,
            /** Füllt Streifen wiederholend mit 4 Farben auf */
            FillUp4,
        };
    } // namespace Enums
} // namespace StripeBridge
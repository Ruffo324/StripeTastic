// #include <Arduino.h>
// #include <NeoPixelBrightnessBus.h>

// enum Modes
// {
//     Off = 0,
//     Static = 1,
//     Effect = 2,
// };

// enum ColorMode
// {
//     Rainbow,
//     Random,
//     UserColors,
// };

// enum Effects
// {
//     Strobo,
//     Ball,
//     BallStackable,
//     BallStackableToCenter,
//     Music,
//     MusicFromCenter,
//     LavaLamp,
//     MovingRainbow,
//     FillUp,
//     FillUp2,
//     FillUp3,
//     FillUp4,
//     FillUp4,
// };

// enum EffectDirection
// {
//     Left,
//     Right
// };

// struct setup_stripe
// {
//     int StripeIndex;
//     Modes mode;
//     Effects effect;
//     EffectDirection EffectDirection; // Richtung des Effekts
//     ColorMode Licht;
//     uint8_t Brightness;
//     uint8_t FlashPerSeconds; // Strobo takt
//     uint8_t EffectDelay;     // 10 - x
//     float Intensity = 100.0; // Scaliert  Micro/AUX  0 - 500,100 = Faktor 1, 200 =faktor 2

//     RgbColor LED_farbe_1;
//     RgbColor LED_farbe_2;
//     RgbColor LED_farbe_3;
//     RgbColor LED_farbe_4;

//     bool Repeat;
//     bool Changed;
//     bool IsAux; // True = aux, false = mic
// };

// main()
// {
//     setup_stripe s_strip1;

//     if (s_strip1.Licht == ColorMode::Rainbow)
//     {
//         s.setPixelColor(i, weel());
//     }
//     else if (s_strip1.Licht == ColorMode::Random)
//     {

//         s.setPixelColor(i,RgbColor(random(255),random(255),random(255))
//     }
//     else if (s_strip1.Licht == ColorMode::UserColors)
//     {
//         s.sesetPixelColor(i, LED_farbe_1);
//     }
// }
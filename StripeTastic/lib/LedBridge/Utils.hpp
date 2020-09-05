// #include <Arduino.h>
// #include <NeoPixelBrightnessBus.h>

// namespace LedBridge
// {
//     extern int micro_e;
//     extern int aux_e;
//     extern int aux_e_r;
//     struct setup_stripe;

//     ////////////////////////////////////////////////////////////////////////
//     //                                   FUNKTIONEN                   //////
//     ////////////////////////////////////////////////////////////////////////

//     void ini_io(void)
//     {

//         pinMode(21, OUTPUT);
//         pinMode(23, OUTPUT);

//         pinMode(micro_e, INPUT);
//         pinMode(aux_e, INPUT);
//         pinMode(aux_e_r, INPUT);
//         analogReadResolution(10);
//     }

//     /////////////////////////////////////////////////////////////////////

//     // Funktion ließt Micro/AUX Signal ein
//     int check_micro(bool micro_aux)
//     {

//         int temp[10];
//         int tem = 0;

//         if (micro_aux)
//         {
//             for (int i = 0; i < 10; i++)
//             {
//                 temp[i] = analogRead(micro_e);
//             }
//         }
//         else
//         {
//             for (int i = 0; i < 10; i++)
//             {
//                 temp[i] = analogRead(aux_e);
//             }
//         }

//         for (int i = 0; i < 10; i++)
//         {
//             tem += temp[i];
//         }
//         tem = tem / 10;

//         return tem;
//     }
//     /////////////////////////////////////////////////////////////////////

//     /////////////////////////////////////////////////////////////////////////

//     template <class T>
//     void aus(T *stripe)
//     {

//         for (int i = 0; i < (*stripe).PixelCount(); i++)
//         {
//             (*stripe).SetPixelColor(i, RgbColor(0, 0, 0));
//         }
//         (*stripe).Show();
//     }

//     ////////////////////////////////////////////////////////////////////////
//     //                       STATIC                                    /////
//     ////////////////////////////////////////////////////////////////////////

//     template <class T>
//     void rainbow(T *stripe, setup_stripe values)
//     {

//         for (int i = 0; i < amountLeds; i++)
//         {
//             RgbColor color = Wheel(map(i, 0, amountLeds - 1, 30, 150));
//             (*stripe).SetPixelColor(amountLeds_top - i - 1, color);
//         }

//         (*stripe).SetBrightness(values.Brightness);
//         (*stripe).Show();
//     }

//     /////////////////////////////////////////////////////////////////////////

//     template <class T>
//     void zufall(T *stripe, setup_stripe values)
//     {

//         for (int i = 0; i < amountLeds; i++)
//         {
//             RgbColor color = RgbColor(random(255), random(255), random(255));
//             (*stripe).SetPixelColor(amountLeds_top - i - 1, color);
//         }

//         (*stripe).SetBrightness(values.Brightness);
//         (*stripe).Show();
//     }

//     ////////////////////////////////////////////////////////////////////////

//     template <class T>
//     void usercolor(T *stripe, setup_stripe values)
//     {

//         for (uint16_t i = 0; i < (*stripe).PixelCount(); i++)
//         {
//             (*stripe).SetPixelColor(i, values.LED_farbe_1);
//         }
//         (*stripe).SetBrightness(values.Brightness);
//         (*stripe).Show();
//     }

//     //////////////////////////////////////////////////////////////////////////////////

//     RgbColor Wheel(byte WheelPos)
//     {

//         if (WheelPos < 85)
//         {
//             return RgbColor(WheelPos * 3, 255 - WheelPos * 3, 0);
//         }
//         else if (WheelPos < 170)
//         {
//             WheelPos -= 85;
//             return RgbColor(255 - WheelPos * 3, 0, WheelPos * 3);
//         }
//         else
//         {
//             WheelPos -= 170;
//             return RgbColor(0, WheelPos * 3, 255 - WheelPos * 3);
//         }
//     }

//     ///////////////////////////////////////////////////////////////
//     //                      EFFECTS                            ////
//     ///////////////////////////////////////////////////////////////

//     template <class T>
//     void strobo(T *stripe, setup_stripe values)
//     {
//         auto ntime = millis();
//         RgbColor color;
//         if (ntime - timerJeStripe[values.StripeIndex] >= (1000 / values.FlashPerSeconds))
//         {

//             // Farbauswahl
//             if (values.Licht == ColorMode::UserColors)
//             {
//                 color = values.LED_farbe_1;
//             }
//             if (values.Licht == ColorMode::Random)
//             {
//                 color = RgbColor(random(255), random(255), random(255));
//             }
//             // macht kein Sinn aber lass ich mal drin
//             if (values.Licht == ColorMode::Rainbow)
//             {
//                 color = Wheel(map(LeadingBall[values.StripeIndex], 0, amountLeds - 1, 30, 150));
//                 ;
//             }

//             RgbColor color = (durchlaufJeStripe[values.StripeIndex] = !durchlaufJeStripe[values.StripeIndex]) ? values.LED_farbe_1 : RgbColor(0, 0, 0);
//             for (uint16_t i = 0; i < (*stripe).PixelCount(); i++)
//             {
//                 (*stripe).SetPixelColor(i, color);
//             }

//             (*stripe).SetBrightness(values.Brightness);
//             (*stripe).Show();
//             timerJeStripe[values.StripeIndex] = ntime;
//         }
//     }

//     //////////////////////////////////////////////////////////////////////////////////

//     template <class T>
//     void ball(T *stripe, setup_stripe values)
//     {
//         auto ntime = millis();
//         const int balllengh = 5;
//         int viertel = std::ceil(amountLeds / 4);
//         int halb = std::ceil(amountLeds / 2);
//         int dreiviertel = std::ceil(amountLeds * 3 / 4);
//         RgbColor color;

//         if (ntime - timerJeStripe[values.StripeIndex] >= (1000 / values.EffectDelay))
//         {

//             // Farbauswahl
//             if (values.Licht == ColorMode::UserColors)
//             {
//                 color = values.LED_farbe_1;
//             }
//             if (values.Licht == ColorMode::Random)
//             {
//                 color = RgbColor(random(255), random(255), random(255));
//             }
//             if (values.Licht == ColorMode::Rainbow)
//             {
//                 color = Wheel(map(LeadingBall[values.StripeIndex], 0, amountLeds - 1, 30, 150));
//                 ;
//             }

//             // Löscht alle Farben
//             for (int i = 0; i < amountLeds; i++)
//             {
//                 (*stripe).SetPixelColor(i, RgbColor(0, 0, 0));
//             }
//             // erster Ball
//             for (int i = LeadingBall[values.StripeIndex]; i == LeadingBall[values.StripeIndex] - balllengh; i--)
//             {

//                 (*stripe).SetPixelColor(i, color);
//             }
//             // Zweiter Ball startet wenn 1. bei viertel angekommen ist
//             if (LeadingBall[values.StripeIndex] > viertel)
//             {
//                 for (int i = LeadingBall[values.StripeIndex] - viertel; i == LeadingBall[values.StripeIndex] - balllengh; i--)
//                 {
//                     (*stripe).SetPixelColor(i, color);
//                 }
//             }
//             // Dritter Ball startet wenn 1. bei hälfte angekommen ist
//             if (LeadingBall[values.StripeIndex] > halb)
//             {
//                 for (int i = LeadingBall[values.StripeIndex] - halb; i == LeadingBall[values.StripeIndex] - balllengh; i--)
//                 {
//                     (*stripe).SetPixelColor(i, color);
//                 }
//             }
//             // 4. Ball startet wenn 1. Ball bei 3/4 ist
//             if (LeadingBall[values.StripeIndex] > dreiviertel)
//             {
//                 for (int i = LeadingBall[values.StripeIndex] - dreiviertel; i == LeadingBall[values.StripeIndex] - balllengh; i--)
//                 {
//                     (*stripe).SetPixelColor(i, color);
//                 }
//             }

//             (*stripe).SetBrightness(values.Brightness);
//             (*stripe).Show();

//             // Speichert Ball Position und rollover bei amountLeds
//             LeadingBall[values.StripeIndex] += 1;
//             if (LeadingBall[values.StripeIndex] == amountLeds)
//                 LeadingBall[values.StripeIndex] = balllengh;

//             timerJeStripe[values.StripeIndex] = ntime;
//         }
//     }

//     //////////////////////////////////////////////////////////////////////////////////

//     template <class T>
//     void ballstackable(T *stripe, setup_stripe values)
//     {
//         auto ntime = millis();
//         const int balllengh = 5;
//         int viertel = std::ceil(amountLeds / 4);
//         int hab = std::ceil(amountLeds / 2);
//         int dreiviertel = std::ceil(amountLeds * 3 / 4);
//         int zyklus = amountLeds / balllengh;
//         RgbColor color;

//         if (ntime - timerJeStripe[values.StripeIndex] >= (1000 / values.EffectDelay))
//         {

//             // Farbauswahl
//             if (values.Licht == ColorMode::UserColors)
//             {
//                 color = values.LED_farbe_1;
//             }
//             if (values.Licht == ColorMode::Random)
//             {
//                 color = RgbColor(random(255), random(255), random(255));
//             }
//             if (values.Licht == ColorMode::Rainbow)
//             {
//                 color = Wheel(map(LeadingBall[values.StripeIndex], 0, amountLeds - 1, 30, 150));
//                 ;
//             }
//             // Löscht alle Farben
//             for (int i = 0; i < amountLeds; i++)
//             {
//                 (*stripe).SetPixelColor(i, RgbColor(0, 0, 0));
//             }

//             // erster Ball
//             for (int i = LeadingBall[values.StripeIndex]; i <= LeadingBall[values.StripeIndex] - balllengh; i--)
//             {
//                 if (LeadingBall[values.StripeIndex] - balllengh > 0)
//                     (*stripe).SetPixelColor(i, color);
//             }

//             // stackt balls
//             if (BallOverFlow[values.StripeIndex] > 0)
//             {
//                 for (int i = amountLeds; i < (amountLeds - BallOverFlow[values.StripeIndex]); i--)
//                 {
//                     (*stripe).SetPixelColor(i, color);
//                 }
//             }

//             (*stripe).SetBrightness(values.Brightness);
//             (*stripe).Show();

//             // Speichert Ball Position und rollover bei amountLeds
//             LeadingBall[values.StripeIndex] += 1;
//             if (LeadingBall[values.StripeIndex] == amountLeds)
//             {
//                 LeadingBall[values.StripeIndex] = balllengh;
//                 BallOverFlow[values.StripeIndex] += balllengh;
//                 if (BallOverFlow[values.StripeIndex] == zyklus)
//                     BallOverFlow[values.StripeIndex] = 0;
//             }

//             timerJeStripe[values.StripeIndex] = ntime;
//         }
//     }

//     //////////////////////////////////////////////////////////////////////////////////

//     template <class T>
//     void ballStackableToCenter(T *stripe, setup_stripe values)
//     {
//     }

//     //////////////////////////////////////////////////////////////////////////////////

//     template <class T>
//     void vu_centre(T *stripe, setup_stripe values)
//     {
//         float scale = 0.0;
//         uint8_t i;
//         uint16_t minLvl, maxLvl;
//         int height;
//         float n = 0;
//         int value = 0;
//         auto ntime = millis();
//         RgbColor color;

//         if (ntime - timerJeStripe[values.StripeIndex] >= values.EffectDelay)
//         {

//             int mic = check_micro(values.IsAux);

//             if (values.IsAux)
//             {
//                 DC_OFFSET = 474;
//             }
//             else
//             {
//                 DC_OFFSET = 440;
//             }

//             scale = values.Intensity / 100.0;
//             n = abs(mic - DC_OFFSET);
//             n = n * scale;
//             value = (int)n;

//             lvlJeStripe[values.StripeIndex] = ((lvlJeStripe[values.StripeIndex] * 7) + value) >> 3;

//             // Calculate bar height based on dynamic min/max levels (fixed point):
//             height = amountLeds * (lvlJeStripe[values.StripeIndex] - minLvlAvgJeStripe[values.StripeIndex]) / (long)(maxLvlAvgJeStripe[values.StripeIndex] - minLvlAvgJeStripe[values.StripeIndex]);
//             if (height < 0L)
//                 height = 0; // Clip output
//             else if (height > amountLeds)
//                 height = amountLeds;
//             if (height > peakJeStripe[values.StripeIndex])
//                 peakJeStripe[values.StripeIndex] = height; // Keep 'peak' dot at top

//             // Color pixels based on rainbow gradient
//             for (i = 0; i < amountLeds_half; i++)
//             {
//                 if (i >= height)
//                 {
//                     (*stripe).SetPixelColor(amountLeds_half - i - 1, RgbColor(0, 0, 0));
//                     (*stripe).SetPixelColor(amountLeds_half + i, RgbColor(0, 0, 0));
//                 }
//                 else
//                 {
//                     RgbColor color = Wheel(map(i, 0, amountLeds_half - 1, 30, 150));
//                     (*stripe).SetPixelColor(amountLeds_half - i - 1, color);
//                     (*stripe).SetPixelColor(amountLeds_half + i, color);
//                 }
//             }

//             // Draw peak dot
//             if (peakJeStripe[values.StripeIndex] > 0 && peakJeStripe[values.StripeIndex] <= amountLeds - 1)
//             {
//                 RgbColor color = Wheel(map(peakJeStripe[values.StripeIndex], 0, amountLeds_half - 1, 30, 150));
//                 (*stripe).SetPixelColor(amountLeds_half - peakJeStripe[values.StripeIndex] - 1, color);
//                 (*stripe).SetPixelColor(amountLeds_half + peakJeStripe[values.StripeIndex], color);
//             }

//             (*stripe).SetBrightness(values.Brightness);

//             (*stripe).Show(); // Update strip

//             // Every few frames, make the peak pixel drop by 1:
//             if (++dotcountJeStripe[values.StripeIndex] >= PEAK_FALL)
//             { //fall rate
//                 if (peakJeStripe[values.StripeIndex] > 0)
//                     peakJeStripe[values.StripeIndex]--;
//                 dotcountJeStripe[values.StripeIndex] = 0;
//             }

//             volJeStripe[values.StripeIndex][volCountJeStripe[values.StripeIndex]] = n; // Save sample for dynamic leveling
//             if (++volCountJeStripe[values.StripeIndex] >= SAMPLES)
//                 volCountJeStripe[values.StripeIndex] = 0; // Advance/rollover sample counter

//             // Get volume range of prior frames
//             minLvl = maxLvl = volJeStripe[values.StripeIndex][0];
//             for (i = 1; i < SAMPLES; i++)
//             {
//                 if (volJeStripe[values.StripeIndex][i] < minLvl)
//                     minLvl = volJeStripe[values.StripeIndex][i];
//                 else if (volJeStripe[values.StripeIndex][i] > maxLvl)
//                     maxLvl = volJeStripe[values.StripeIndex][i];
//             }

//             if ((maxLvl - minLvl) < amountLeds_top)
//                 maxLvl = minLvl + amountLeds_top;
//             minLvlAvgJeStripe[values.StripeIndex] = (minLvlAvgJeStripe[values.StripeIndex] * 63 + minLvl) >> 6;
//             maxLvlAvgJeStripe[values.StripeIndex] = (maxLvlAvgJeStripe[values.StripeIndex] * 63 + maxLvl) >> 6;

//             timerJeStripe[values.StripeIndex] = ntime;
//         }
//     }

//     //////////////////////////////////////////////////////////////////////////////////

//     template <class T>
//     void vunormal(T *stripe, setup_stripe values)
//     {
//         float scale = 0.0;
//         uint8_t i;
//         uint16_t minLvl, maxLvl;
//         int height;
//         float n = 0;
//         int value = 0;
//         auto ntime = millis();
//         RgbColor color;

//         if (ntime - timerJeStripe[values.StripeIndex] >= values.EffectDelay)
//         {

//             int mic = check_micro(values.IsAux);

//             if (values.IsAux)
//             {
//                 DC_OFFSET = 474;
//             }
//             else
//             {
//                 DC_OFFSET = 440;
//             }

//             scale = values.Intensity / 100.0;
//             n = abs(mic - DC_OFFSET);
//             n = n * scale;
//             value = (int)n;

//             lvlJeStripe[values.StripeIndex] = ((lvlJeStripe[values.StripeIndex] * 7) + value) >> 3;

//             // Calculate bar height based on dynamic min/max levels (fixed point):
//             height = amountLeds * (lvlJeStripe[values.StripeIndex] - minLvlAvgJeStripe[values.StripeIndex]) / (long)(maxLvlAvgJeStripe[values.StripeIndex] - minLvlAvgJeStripe[values.StripeIndex]);

//             if (height < 0L)
//                 height = 0; // Clip output
//             else if (height > amountLeds)
//                 height = amountLeds;
//             if (height > peakJeStripe[values.StripeIndex])
//                 peakJeStripe[values.StripeIndex] = height; // Keep 'peak' dot at top

//             if (values.Licht == ColorMode::UserColors)
//             {
//                 color = values.LED_farbe_1;
//             }
//             if (values.Licht == ColorMode::Random)
//             {
//                 color = RgbColor(random(255), random(255), random(255));
//             }

//             // Color pixels based on rainbow gradient
//             for (i = 0; i < amountLeds; i++)
//             {
//                 if (i >= height)
//                 {
//                     (*stripe).SetPixelColor(i, RgbColor(0, 0, 0));
//                 }
//                 else
//                 {

//                     if (values.Licht == ColorMode::Rainbow)
//                     {
//                         color = Wheel(map(i, 0, amountLeds - 1, 30, 150));
//                     }

//                     (*stripe).SetPixelColor(i, color);
//                 }
//             }

//             // Draw peak dot
//             if (peakJeStripe[values.StripeIndex] > 0 && peakJeStripe[values.StripeIndex] <= amountLeds - 1)
//             {
//                 RgbColor color = Wheel(map(peakJeStripe[values.StripeIndex], 0, amountLeds - 1, 30, 150));
//                 (*stripe).SetPixelColor(peakJeStripe[values.StripeIndex], color);
//             }

//             (*stripe).SetBrightness(values.Brightness);

//             (*stripe).Show(); // Update strip

//             // Every few frames, make the peak pixel drop by 1:
//             if (++dotcountJeStripe[values.StripeIndex] >= PEAK_FALL)
//             { //fall rate

//                 if (peakJeStripe[values.StripeIndex] > 0)
//                     peakJeStripe[values.StripeIndex]--;
//                 dotcountJeStripe[values.StripeIndex] = 0;
//             }

//             volJeStripe[values.StripeIndex][volCountJeStripe[values.StripeIndex]] = n; // Save sample for dynamic leveling
//             if (++volCountJeStripe[values.StripeIndex] >= SAMPLES)
//                 volCountJeStripe[values.StripeIndex] = 0; // Advance/rollover sample counter

//             // Get volume range of prior frames
//             minLvl = maxLvl = volJeStripe[values.StripeIndex][0];
//             for (i = 1; i < SAMPLES; i++)
//             {
//                 if (volJeStripe[values.StripeIndex][i] < minLvl)
//                     minLvl = volJeStripe[values.StripeIndex][i];
//                 else if (volJeStripe[values.StripeIndex][i] > maxLvl)
//                     maxLvl = volJeStripe[values.StripeIndex][i];
//             }

//             if ((maxLvl - minLvl) < amountLeds_top)
//                 maxLvl = minLvl + amountLeds_top;
//             minLvlAvgJeStripe[values.StripeIndex] = (minLvlAvgJeStripe[values.StripeIndex] * 63 + minLvl) >> 6;
//             maxLvlAvgJeStripe[values.StripeIndex] = (maxLvlAvgJeStripe[values.StripeIndex] * 63 + maxLvl) >> 6;

//             timerJeStripe[values.StripeIndex] = ntime;
//         }
//     }

//     //////////////////////////////////////////////////////////////////////////////////

//     template <class T>
//     void lavalampemove(T *stripe, setup_stripe values)
//     {
//         auto ntime = millis();
//         RgbColor color_hoch;
//         RgbColor color_runter;
//         // Farbauswahl

//         if (ntime - timerJeStripe[values.StripeIndex] >= values.EffectDelay)
//         {
//             // Farbauswahl
//             if (values.Licht == ColorMode::UserColors)
//             {
//                 color_hoch = values.LED_farbe_1;
//                 color_runter = values.LED_farbe_2;
//             }
//             if (values.Licht == ColorMode::Random)
//             {
//                 color_hoch = RgbColor(random(255), random(255), random(255));
//                 color_runter = RgbColor(random(255), random(255), random(255));
//             }
//             if (values.Licht == ColorMode::Rainbow)
//             {
//                 color_hoch = Wheel(map(LeadingBall[values.StripeIndex], 0, amountLeds - 1, 30, 150));
//                 ;
//                 color_runter = Wheel(map(LeadingBall[values.StripeIndex], 0, amountLeds - 1, 30, 150));
//                 ;
//             }

//             if (values.effectDirection == EffectDirection::Left)
//             {
//                 (*stripe).SetPixelColor(lavaLampPositon[values.StripeIndex], color_hoch);
//                 (*stripe).SetBrightness(values.Brightness);
//                 (*stripe).Show();
//                 lavaLampPositon[values.StripeIndex]++;
//                 if (lavaLampPositon[values.StripeIndex] > (*stripe).PixelCount())
//                 {
//                     values.effectDirection = EffectDirection::Right;
//                     lavaLampPositon[values.StripeIndex] = (*stripe).PixelCount();
//                 }
//             }
//             else
//             {
//                 (*stripe).SetPixelColor(lavaLampPositon[values.StripeIndex], color_runter);
//                 (*stripe).SetBrightness(values.Brightness);
//                 (*stripe).Show();
//                 lavaLampPositon[values.StripeIndex]--;
//                 if (lavaLampPositon[values.StripeIndex] < 0)
//                 {
//                     values.effectDirection = EffectDirection::Left;
//                     lavaLampPositon[values.StripeIndex] = 0;
//                 }
//             }
//             (*stripe).SetBrightness(values.Brightness);
//             (*stripe).Show();
//             timerJeStripe[values.StripeIndex] = ntime;
//         }
//     }

//     //////////////////////////////////////////////////////////////////////////////////

//     template <class T>
//     void movingRainbow(T *stripe, setup_stripe values)
//     {
//         auto ntime = millis();
//         if (ntime - timerJeStripe[values.StripeIndex] >= values.EffectDelay)
//         {

//             stepJeStripe[values.StripeIndex]++;

//             if (stepJeStripe[values.StripeIndex] > (*stripe).PixelCount())
//                 stepJeStripe[values.StripeIndex] = 0;

//             for (int i = 0; i < (*stripe).PixelCount(); i++)
//             {
//                 RgbColor color = Wheel(map(i, 0, amountLeds - 1, 30, 150));
//                 (*stripe).SetPixelColor(((i + stepJeStripe[values.StripeIndex]) % amountLeds), color);
//             }

//             (*stripe).SetBrightness(values.Brightness);
//             (*stripe).Show();

//             timerJeStripe[values.StripeIndex] = ntime;
//         }
//     }

//     //////////////////////////////////////////////////////////////////////////////////

//     template <class T>
//     void fillup(T *stripe, setup_stripe values)
//     {
//     }

//     //////////////////////////////////////////////////////////////////////////////////

//     template <class T>
//     void fillup2(T *stripe, setup_stripe values)
//     {
//         int halb = amountLeds / 2;

//         RgbColor color1;
//         RgbColor color2;

//         auto ntime = millis();
//         if (ntime - timerJeStripe[values.StripeIndex] >= values.EffectDelay)
//         {

//             stepJeStripe[values.StripeIndex]++;

//             if (stepJeStripe[values.StripeIndex] > (*stripe).PixelCount() / 3)
//             {
//                 stepJeStripe[values.StripeIndex] = 0;
//                 durchlaufJeStripe[values.StripeIndex] = durchlaufJeStripe[values.StripeIndex] ^ 1;
//             }

//             // Farbauswahl
//             if (values.Licht == ColorMode::UserColors)
//             {
//                 color1 = values.LED_farbe_1;
//                 color2 = values.LED_farbe_2;
//             }

//             if (values.Licht == ColorMode::Random)
//             {
//                 color1 = RgbColor(random(255), random(255), random(255));
//                 color2 = RgbColor(random(255), random(255), random(255));
//             }

//             if (values.Licht == ColorMode::Rainbow)
//             {
//                 color1 = Wheel(map(LeadingBall[values.StripeIndex], 0, amountLeds - 1, 30, 150));
//                 ;
//                 color2 = color1;
//             }

//             if (durchlaufJeStripe[values.StripeIndex] == false)
//             {

//                 (*stripe).SetPixelColor(stepJeStripe[values.StripeIndex], color1);
//                 (*stripe).SetPixelColor(stepJeStripe[values.StripeIndex] + halb, color2);
//             }
//             else
//             {
//                 RgbColor color = RgbColor(0, 0, 0);
//                 (*stripe).SetPixelColor(stepJeStripe[values.StripeIndex], color);
//                 (*stripe).SetPixelColor(stepJeStripe[values.StripeIndex] + halb, color);
//             }

//             (*stripe).SetBrightness(values.Brightness);
//             (*stripe).Show();

//             timerJeStripe[values.StripeIndex] = ntime;
//         }
//     }

//     //////////////////////////////////////////////////////////////////////////////////

//     template <class T>
//     void fillup3(T *stripe, setup_stripe values)
//     {
//         int drittel = std::ceil(amountLeds / 3);
//         int zweidrittel = std::ceil(amountLeds * 2 / 3);

//         RgbColor color1;
//         RgbColor color2;
//         RgbColor color3;

//         auto ntime = millis();
//         if (ntime - timerJeStripe[values.StripeIndex] >= values.EffectDelay)
//         {

//             int einviertel = (*stripe).PixelCount() / 4;
//             int halb = (*stripe).PixelCount() / 2;
//             int dreiviertel = (*stripe).PixelCount() * 3 / 4;
//             int voll = (*stripe).PixelCount();

//             stepJeStripe[values.StripeIndex]++;

//             if (stepJeStripe[values.StripeIndex] > (*stripe).PixelCount() / 3)
//             {
//                 stepJeStripe[values.StripeIndex] = 0;
//                 durchlaufJeStripe[values.StripeIndex] = durchlaufJeStripe[values.StripeIndex] ^ 1;
//             }

//             // Farbauswahl
//             if (values.Licht == ColorMode::UserColors)
//             {
//                 color1 = values.LED_farbe_1;
//                 color2 = values.LED_farbe_2;
//                 color3 = values.LED_farbe_3;
//             }
//             if (values.Licht == ColorMode::Random)
//             {
//                 color1 = RgbColor(random(255), random(255), random(255));
//                 color2 = RgbColor(random(255), random(255), random(255));
//                 color3 = RgbColor(random(255), random(255), random(255));
//             }
//             if (values.Licht == ColorMode::Rainbow)
//             {
//                 color1 = Wheel(map(LeadingBall[values.StripeIndex], 0, amountLeds - 1, 30, 150));
//                 ;
//                 color2 = color1;
//                 color3 = color1;
//             }

//             if (durchlaufJeStripe[values.StripeIndex] == false)
//             {

//                 (*stripe).SetPixelColor(stepJeStripe[values.StripeIndex], color1);
//                 (*stripe).SetPixelColor(stepJeStripe[values.StripeIndex] + drittel, color2);
//                 (*stripe).SetPixelColor(stepJeStripe[values.StripeIndex] + zweidrittel, color3);
//             }
//             else
//             {
//                 RgbColor color = RgbColor(0, 0, 0);
//                 (*stripe).SetPixelColor(stepJeStripe[values.StripeIndex], color);
//                 (*stripe).SetPixelColor(stepJeStripe[values.StripeIndex] + drittel, color);
//                 (*stripe).SetPixelColor(stepJeStripe[values.StripeIndex] + zweidrittel, color);
//             }

//             (*stripe).SetBrightness(values.Brightness);
//             (*stripe).Show();

//             timerJeStripe[values.StripeIndex] = ntime;
//         }
//     }

//     //////////////////////////////////////////////////////////////////////////////////

//     template <class T>
//     void fillup4(T *stripe, setup_stripe values)
//     {
//         RgbColor color1;
//         RgbColor color2;
//         RgbColor color3;
//         RgbColor color4;

//         auto ntime = millis();
//         if (ntime - timerJeStripe[values.StripeIndex] >= values.EffectDelay)
//         {

//             int einviertel = (*stripe).PixelCount() / 4;
//             int halb = (*stripe).PixelCount() / 2;
//             int dreiviertel = (*stripe).PixelCount() * 3 / 4;
//             int voll = (*stripe).PixelCount();

//             stepJeStripe[values.StripeIndex]++;

//             // Farbauswahl
//             if (values.Licht == ColorMode::UserColors)
//             {
//                 color1 = values.LED_farbe_1;
//                 color2 = values.LED_farbe_2;
//                 color3 = values.LED_farbe_3;
//                 color4 = values.LED_farbe_4;
//             }

//             if (values.Licht == ColorMode::Random)
//             {
//                 color1 = RgbColor(random(255), random(255), random(255));
//                 color2 = RgbColor(random(255), random(255), random(255));
//                 color3 = RgbColor(random(255), random(255), random(255));
//                 color4 = RgbColor(random(255), random(255), random(255));
//             }

//             if (values.Licht == ColorMode::Rainbow)
//             {
//                 color1 = Wheel(map(LeadingBall[values.StripeIndex], 0, amountLeds - 1, 30, 150));
//                 ;
//                 color2 = color1;
//                 color3 = color1;
//                 color4 = color1;
//             }

//             if (stepJeStripe[values.StripeIndex] > (*stripe).PixelCount() / 4)
//             {
//                 stepJeStripe[values.StripeIndex] = 0;
//                 durchlaufJeStripe[values.StripeIndex] = durchlaufJeStripe[values.StripeIndex] ^ 1;
//             }

//             if (durchlaufJeStripe[values.StripeIndex] == false)
//             {
//                 (*stripe).SetPixelColor(stepJeStripe[values.StripeIndex], color1);
//                 (*stripe).SetPixelColor(stepJeStripe[values.StripeIndex] + einviertel, color2);
//                 (*stripe).SetPixelColor(stepJeStripe[values.StripeIndex] + halb, color3);
//                 (*stripe).SetPixelColor(stepJeStripe[values.StripeIndex] + dreiviertel, color4);
//             }
//             else
//             {
//                 RgbColor color = RgbColor(0, 0, 0);
//                 (*stripe).SetPixelColor(stepJeStripe[values.StripeIndex], color);
//                 (*stripe).SetPixelColor(stepJeStripe[values.StripeIndex] + einviertel, color);
//                 (*stripe).SetPixelColor(stepJeStripe[values.StripeIndex] + halb, color);
//                 (*stripe).SetPixelColor(stepJeStripe[values.StripeIndex] + dreiviertel, color);
//             }

//             (*stripe).SetBrightness(values.Brightness);
//             (*stripe).Show();

//             timerJeStripe[values.StripeIndex] = ntime;
//         }
//     }
// } // namespace LedBridge
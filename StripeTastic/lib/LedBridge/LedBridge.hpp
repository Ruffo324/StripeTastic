#pragma once

#include <Arduino.h>
#include <NeoPixelBrightnessBus.h>
#include "arduinoFFT.h"

#include "./DebugStuff.hpp"

namespace LedBridge
{
// Defines für Musik
#define SAMPLES 20   // für min/max Berechnung Musik
#define PEAK_FALL 15 // Gibt geschwindigkeit vom DotFall vor  // könnte man in der UI im Setup einstellbar machen

// Defines für FFT
#define SCL_INDEX 0x00
#define SCL_TIME 0x01
#define SCL_FREQUENCY 0x02
#define SCL_PLOT 0x03

    // Variablen für FFT
    arduinoFFT FFT = arduinoFFT();         /* Create FFT object */
    const int samples_fft = 128;           //This value MUST ALWAYS be a power of 2
    const double samplingFrequency = 1000; // Hz, must be less than 10000 due to ADC  ACHTUNG BEI ÄNDERUNG MUSS Sampledelay angepasst werden
    const long samplingDelay = 1000;       // Zeit in µS          1000 -> 1ms -> 1kHz

    double vReal[samples_fft]; // Speichert Real Anteil
    double vImag[samples_fft]; // Speichert Imag Anteil  z = vReal + vImag
    bool isRdy = 0;            // Zeigt an wenn Samplephase fertig ist
    unsigned long oldtime = 0; // Speichert alte Sampezeit
    int idex = 0;              // Speichert sich Index beim Samplen

    // könnte man in der UI im Setup einstellbar machen
    int maxfreq = 400; // gibt MaxFreq der FFT Auswertung
    int delayMax = 25; // Maximale Verzögerung
    int delaxMin = 1;  // Minimale Verzögerung

    // Typen vereinfachen
    typedef NeoPixelBrightnessBus<NeoGrbFeature, NeoEsp32Rmt0800KbpsMethod> RMT0;
    typedef NeoPixelBrightnessBus<NeoGrbFeature, NeoEsp32Rmt1800KbpsMethod> RMT1;

    // Analoge Eingeänge für Microfon und AUX
    const int MicroEingang = 34;      // esp32 - Pin 34
    const int AUX_EingangRechts = 35; // esp32 - Pin 35
    const int AUX_Eingang = 25;       // esp32 - Pin 25
    int CHANNEL = 34;                 // Channel für FFT - Defult MircoEingang
    int DC_OFFSET = 447;              // Offset für Miro bzw Aux -> bedeutet 0 da zum positiven und "negativen" Ausgelenkt werden muss

    // könnte man in der UI im Setup einstellbar machen
    int balllengh[2];       // relative Ball länge
    int balllengh2[2];      // relative Ball länge
    int balllengh3[2];      // relative Ball länge
    int balllengh4[2];      // relative Ball länge
    int balllengh_max = 10; // maximale Ball länge

    // Anzahl LED's pro Stripe
    const int amountLeds = 102; // Stripelänge // könnte man in der UI im Setup einstellbar machen
    const int amountLeds_half = amountLeds / 2;
    const int amountLeds_top = amountLeds + 2;

    // Speichert Werte Je Stripe für Effecte
    bool durchlaufJeStripe[2] = {0, 0};
    unsigned long timerJeStripe[2] = {0, 0};
    int LeadingBallStack[2] = {0, 0};
    int LeadingBall[2] = {0, 0};
    int LeadingBall2[2] = {0, 0};
    int LeadingBall3[2] = {0, 0};
    int LeadingBall4[2] = {0, 0};
    int BallOverFlow[2] = {0, 0};
    int BallOverFlowStack[2] = {0, 0};
    int lavaLampPositon[2] = {0, 0};
    bool RichtungLavalampe[2] = {0, 0};
    int stepJeStripe[2] = {0, 0};
    int lvlJeStripe[2] = {0, 0};
    int minLvlAvgJeStripe[2] = {0, 0};
    int maxLvlAvgJeStripe[2] = {512, 512};
    int peakJeStripe[2] = {0, 0};
    int volJeStripe[2][SAMPLES] = {0, 0};
    int volCountJeStripe[2] = {0, 0};
    int dotcountJeStripe[2] = {0, 0};
    int stackBallleft[2] = {0, 0};
    int stackBallright[2] = {0, 0};
    int LeadingBallleft[2] = {0, 0};
    int LeadingBallright[2] = {0, 0};
    int BallOverFlowleft[2] = {0, 0};
    int BallOverFlowright[2] = {0, 0};
    int mRainbowStep[2] = {0, 0};
    int fillupstep[2] = {0, 0};
    bool durchlauffillup[2] = {0, 0};
    int fillup2step[2] = {0, 0};
    bool durchlauffillup2[2] = {1, 1};
    int fillup3step[2] = {0, 0};
    bool durchlauffillup3[2] = {0, 0};
    int fillup4step[2] = {0, 0};
    bool durchlauffillup4[2] = {0, 0};
    int stackBallcentreleft[2] = {0, 0};
    int stackBallcentreright[2] = {amountLeds - 1, amountLeds - 1};
    int BallOverFlowCentreleft[2] = {0, 0};
    int BallOverFlowCentreright[2] = {0, 0};
    RgbColor fullup4color[2];
    RgbColor fullup4color2[2];
    RgbColor fullup4color3[2];
    RgbColor fullup4color4[2];
    RgbColor fullup3color[2];
    RgbColor fullup3color2[2];
    RgbColor fullup3color3[2];
    RgbColor fullup2color[2];
    RgbColor fullup2color2[2];
    RgbColor lavacolor_hoch[2];
    RgbColor lavacolor_runter[2];
    RgbColor stackcentrecolor_left[2];
    RgbColor stackcentrecolor_right[2];
    RgbColor stackcolor[2];
    RgbColor ballcolor[2];
    RgbColor ballcolor2[2];
    RgbColor ballcolor3[2];
    RgbColor ballcolor4[2];
    RgbColor StroboColor[2];
    bool frist_run_ball2[2];
    bool frist_run_ball3[2];
    bool frist_run_ball4[2];

    // Arry für random Farbe wird noch aufgefüllt
    const int anz = 10;
    RgbColor ranfarben[anz] = {
        RgbColor(255, 0, 0),     // red
        RgbColor(0, 255, 0),     // grren
        RgbColor(0, 0, 255),     // blue
        RgbColor(200, 200, 200), // white
        RgbColor(239, 79, 117),  // pink
        RgbColor(255, 241, 82),  // gelb
        RgbColor(255, 130, 1),   // orange
        RgbColor(0, 200, 200),   // teal
        RgbColor(200, 0, 200),   // lila
        RgbColor(75, 196, 213)};

    enum Modes
    {
        Off = 0,    // Off    = Schaltet Lampe aus
        Static = 1, // Static = nicht zeitlich Veränderte Funktionen
        Effect = 2, // Effect = zeitlich veränderliche Funktionen
    };

    enum ColorMode
    {
        Rainbow,         // Regenbogen farben von rot -> hellblau
        Random,          // Automatische farbauswahl aus ranfarben[anz]
        UserColors,      //       Farbe wird   durch UI vorgegeben
        TwoUsercolors,   // zwei Farben werden druch UI vorgegeben
        ThreeUserColors, // drei Farben werden durch UI vorgegeben
    };

    enum Effects
    {
        Strobo,                // Stroboskop Effect
        Ball,                  // vier Bälle laufen den Strip entlang
        BallStackable,         // Ball läuft Strip entlang und stuckt am Ende
        BallStackableToCenter, // Von beiden Seiten laufen Bälle zur mitte und stucken
        Music,                 // VU Meter Start: Stripe Anfang
        MusicFromCenter,       // VU Meter Start: Stripe Mitte
        LavaLamp,              // Farbe1 läuft in eine Richtung Farbe2 die andere Richtung hin und her
        MovingRainbow,         // Regenbogen bewegt sich entlang des Streifens
        FillUp,                // Füllt Streifen wiederholend mit Farbe auf
        FillUp2,               // Füllt Streifen wiederholden mit 2 Farben auf
        FillUp3,               // Füllt Streifen wiederholend mit 3 Farben auf
        FillUp4,               // Füllt Streifen wiederholend mit 4 Farben auf

    };

    // nicht implenmentiert
    enum EffectDirection
    {
        Left,
        Right
    };

    struct setup_stripe
    {
        int StripeIndex;                 // Strip nummer
        Modes mode;                      // Speichert Modus Static, Effect, OFF
        Effects effect;                  // Speichert welcher Effect abgespielt werden soll
        EffectDirection effectDirection; // Richtung des Effekts
        ColorMode Licht;                 // Speichert Farb quelle
        uint8_t Brightness;              // Speichert helligkeit
        uint8_t FlashPerSeconds;         // Strobo takt
        int EffectDelay;                 // 10ms - x
        float Intensity = 100.0;         // Scaliert  Micro/AUX  0 - 500,100 = Faktor 1, 200 =faktor 2
        bool FFTAktive;                  // aktiviert FFT für EffectDelay Steuerung durch Musik
        bool Repeat;                     // Kann weg wird durch Modes abgedeckt
        bool Changed;                    // Flag die anzeigt wenn sich was ändert
        bool IsAux;                      // True = aux, false = mic
        RgbColor LED_farbe_1;            // Speichert Farbe 1 UserColors
        RgbColor LED_farbe_2;            // Speichert Farbe 2 UserColors
        RgbColor LED_farbe_3;            // Speichert Farbe 3 UserColors
        RgbColor LED_farbe_4;            // Speichert Farbe 4 UserColors
    };

    //Stripe Objekte
    RMT0 stripe1(amountLeds, 23);
    RMT1 stripe2(amountLeds, 21);

    // Setup für Streifen
    extern setup_stripe p_strip1;
    extern setup_stripe p_strip2;

    // nur zum testen
    unsigned long millis_t = 0;
    int counter_t = 2;
    int max_t = 14;

    using namespace std;

    extern void Initalize()
    {
        // TODO: add SetLedCount function / add logic to setup led stripes.
        setup();
    }

    extern void InvokeLoop()
    {
        loop();
    }

    void setup()
    {
        ini_io(); // Setzt Ein- und Ausgänge
        // Serial.begin(115200); // DEBUG
        // TODO: Use LoggerService.

        stripe1.Begin();
        stripe2.Begin();

        test7();
    }

    void loop()
    {

        if (millis() - millis_t >= 5000)
        {
            reset_hilfsvariablen(p_strip1);
            reset_hilfsvariablen(p_strip2);
            counter_t++;
            if (counter_t > max_t)
                counter_t = 2;
            Serial.println(counter_t);
            if (counter_t == 1)
                test1();
            else if (counter_t == 2)
                test2();
            else if (counter_t == 3)
                test3();
            else if (counter_t == 4)
                test4();
            else if (counter_t == 5)
                test5();
            else if (counter_t == 6)
                test6();
            else if (counter_t == 7)
                test16();
            else if (counter_t == 8)
                test8();
            else if (counter_t == 9)
                test9();
            else if (counter_t == 10)
                test10();
            else if (counter_t == 11)
                test7();
            else if (counter_t == 12)
                test12();
            else if (counter_t == 13)
                test13();
            else if (counter_t == 14)
                test14();
            else if (counter_t == 15)
                test15();
            else if (counter_t == 16)
                test11();
            millis_t = millis();
        }

        // Diese Funktion muss mit aufgerufen werden wenn neues Programm ausgewählt wird
        //reset_hilfsvariablen();

        // Aktiviert FFT und Effectdelay steuerung durch Musik sonst durch vorgabe
        if (p_strip1.FFTAktive || p_strip2.FFTAktive)
            prozzesFFT();

        programm(&stripe1, p_strip1); // Hier stripe 1 eintragen
        programm(&stripe2, p_strip2); // Hier stripe 2 eintragen
    }

    template <class T>
    void programm(T *stripe, setup_stripe values)
    {

        switch (values.mode)
        {
        case (Modes::Off):
            aus(stripe);
            break;

        case (Modes::Effect):
            switch (values.effect)
            {
            case Effects::Strobo:
                strobo(stripe, values);
                break;
            case Effects::Ball:
                ball(stripe, values);
                break;
            case Effects::BallStackable:
                ballstackable(stripe, values);
                break;
            case Effects::BallStackableToCenter:
                ballStackableToCenter(stripe, values);
                break;
            case Effects::Music:
                vunormal(stripe, values);
                break;
            case Effects::MusicFromCenter:
                vu_centre(stripe, values);
                break;
            case Effects::LavaLamp:
                lavalampemove(stripe, values);
                break;
            case Effects::MovingRainbow:
                movingRainbow(stripe, values);
                break;
            case Effects::FillUp:
                fillup(stripe, values);
                break;
            case Effects::FillUp2:
                fillup2(stripe, values);
                break;
            case Effects::FillUp3:
                fillup3(stripe, values);
                break;
            case Effects::FillUp4:
                fillup4(stripe, values);
                break;
            }
            break;

        case (Modes::Static):
            switch (values.Licht)
            {
            case ColorMode::Rainbow:
                if (values.Changed)
                    rainbow(stripe, values);
                values.Changed = 0;
                break;
            case ColorMode::Random:
                if (values.Changed)
                    zufall(stripe, values);
                values.Changed = 0;
                break;
            case ColorMode::UserColors:
                if (values.Changed)
                    usercolor(stripe, values);
                values.Changed = 0;
                break;
            case ColorMode::TwoUsercolors:
                if (values.Changed)
                    twousercolor(stripe, values);
                values.Changed = 0;
                break;
            case ColorMode::ThreeUserColors:
                if (values.Changed)
                    threeusercolor(stripe, values);
                values.Changed = 0;
                break;
            }
            break;
        }
    }

    ////////////////////////////////////////////////////////////////////////
    //                            FUNKTIONEN                              //
    ////////////////////////////////////////////////////////////////////////

    void ini_io(void)
    {

        pinMode(21, OUTPUT);
        pinMode(23, OUTPUT);

        pinMode(MicroEingang, INPUT);
        pinMode(AUX_Eingang, INPUT);
        pinMode(AUX_EingangRechts, INPUT);
        analogReadResolution(10);
    }

    ////////////////////////////////////////////////////////////////////////

    // Funktion ließt Micro/AUX Signal ein
    int check_micro(bool micro_aux)
    {

        int temp[10];
        int tem = 0;

        if (micro_aux)
        {
            for (int i = 0; i < 10; i++)
            {
                temp[i] = analogRead(MicroEingang);
            }
        }
        else
        {
            for (int i = 0; i < 10; i++)
            {
                temp[i] = analogRead(AUX_Eingang);
            }
        }

        for (int i = 0; i < 10; i++)
        {
            tem += temp[i];
        }
        tem = tem / 10;

        return tem;
    }
    ////////////////////////////////////////////////////////////////////////
    //                              AUS                                   //
    ////////////////////////////////////////////////////////////////////////

    template <class T>
    void aus(T *stripe)
    {

        for (int i = 0; i < amountLeds; i++)
        {
            (*stripe).SetPixelColor(i, RgbColor(0, 0, 0));
        }
        (*stripe).Show();
    }

    ////////////////////////////////////////////////////////////////////////
    //                             STATIC                                 //
    ////////////////////////////////////////////////////////////////////////

    template <class T>
    void rainbow(T *stripe, setup_stripe values)
    {

        for (int i = 0; i < amountLeds; i++)
        {
            RgbColor color = Wheel(map(i, 0, amountLeds - 1, 30, 150));
            (*stripe).SetPixelColor(amountLeds_top - i - 1, color);
        }

        (*stripe).SetBrightness(values.Brightness);
        (*stripe).Show();
    }

    ////////////////////////////////////////////////////////////////////////

    template <class T>
    void zufall(T *stripe, setup_stripe values)
    {

        RgbColor color = ranfarben[random(anz)];
        for (int i = 0; i < amountLeds; i++)
        {
            (*stripe).SetPixelColor(amountLeds_top - i - 1, color);
        }

        (*stripe).SetBrightness(values.Brightness);
        (*stripe).Show();
    }

    /////////////////////////////////////////////////////////////////////////

    template <class T>
    void usercolor(T *stripe, setup_stripe values)
    {

        for (uint16_t i = 0; i < amountLeds; i++)
        {
            (*stripe).SetPixelColor(i, values.LED_farbe_1);
        }
        (*stripe).SetBrightness(values.Brightness);
        (*stripe).Show();
    }

    /////////////////////////////////////////////////////////////////////////

    template <class T>
    void twousercolor(T *stripe, setup_stripe values)
    {

        for (uint16_t i = 0; i < amountLeds_half; i++)
        {
            (*stripe).SetPixelColor(i, values.LED_farbe_1);
        }
        for (uint16_t i = amountLeds_half; i < amountLeds; i++)
        {
            (*stripe).SetPixelColor(i, values.LED_farbe_2);
        }
        (*stripe).SetBrightness(values.Brightness);
        (*stripe).Show();
    }

    /////////////////////////////////////////////////////////////////////////

    template <class T>
    void threeusercolor(T *stripe, setup_stripe values)
    {

        for (int i = 0; i < amountLeds_half; i++)
        {
            (*stripe).SetPixelColor(i, values.LED_farbe_1);
        }
        for (int i = amountLeds_half; i < amountLeds - 20; i++)
        {
            (*stripe).SetPixelColor(i, values.LED_farbe_2);
        }
        for (int i = amountLeds - 20; i < amountLeds; i++)
        {
            (*stripe).SetPixelColor(i, values.LED_farbe_3);
        }
        (*stripe).SetBrightness(values.Brightness);
        (*stripe).Show();
    }

    //////////////////////////////////////////////////////////////////////////

    RgbColor Wheel(byte WheelPos)
    {

        if (WheelPos < 85)
        {
            return RgbColor(WheelPos * 3, 255 - WheelPos * 3, 0);
        }
        else if (WheelPos < 170)
        {
            WheelPos -= 85;
            return RgbColor(255 - WheelPos * 3, 0, WheelPos * 3);
        }
        else
        {
            WheelPos -= 170;
            return RgbColor(0, WheelPos * 3, 255 - WheelPos * 3);
        }
    }

    /////////////////////////////////////////////////////////////////////////////
    //                                   EFFECTS                               //
    /////////////////////////////////////////////////////////////////////////////
    // Fertig
    template <class T>
    void strobo(T *stripe, setup_stripe values)
    {

        if (millis() - timerJeStripe[values.StripeIndex] >= (1000 / values.FlashPerSeconds))
        {

            // Farbauswahl
            if (values.Licht == ColorMode::UserColors)
            {
                StroboColor[values.StripeIndex] = values.LED_farbe_1;
            }
            if (values.Licht == ColorMode::Random)
            {
                StroboColor[values.StripeIndex] = ranfarben[random(anz)];
            }
            // macht kein Sinn aber lass ich mal drin
            if (values.Licht == ColorMode::Rainbow)
            {
                StroboColor[values.StripeIndex] = values.LED_farbe_1;
            }

            RgbColor color = (durchlaufJeStripe[values.StripeIndex] = !durchlaufJeStripe[values.StripeIndex]) ? StroboColor[values.StripeIndex] : RgbColor(0, 0, 0);
            for (uint16_t i = 0; i < amountLeds; i++)
            {
                (*stripe).SetPixelColor(i, StroboColor[values.StripeIndex]);
            }

            (*stripe).SetBrightness(values.Brightness);
            (*stripe).Show();
            timerJeStripe[values.StripeIndex] = millis();
        }
    }

    ///////////////////////////////////////////////////////////////////////////////
    // Fertig
    template <class T>
    void ball(T *stripe, setup_stripe values)
    {

        if (millis() - timerJeStripe[values.StripeIndex] >= values.EffectDelay)
        {

            int viertel = amountLeds / 4;
            int halb = amountLeds_half;
            int dreiviertel = amountLeds * 3 / 4;
            // Farbauswahl
            if (values.Licht == ColorMode::UserColors)
            {
                ballcolor[values.StripeIndex] = values.LED_farbe_1;
                ballcolor2[values.StripeIndex] = values.LED_farbe_2;
                ballcolor3[values.StripeIndex] = values.LED_farbe_3;
                ballcolor4[values.StripeIndex] = values.LED_farbe_4;
            }

            if (values.Licht == ColorMode::Random && LeadingBall[values.StripeIndex] == 0)
            {
                ballcolor[values.StripeIndex] = ranfarben[random(anz)];
            }
            if (values.Licht == ColorMode::Random && LeadingBall2[values.StripeIndex] == 0)
            {
                ballcolor2[values.StripeIndex] = ranfarben[random(anz)];
            }
            if (values.Licht == ColorMode::Random && LeadingBall3[values.StripeIndex] == 0)
            {
                ballcolor3[values.StripeIndex] = ranfarben[random(anz)];
            }
            if (values.Licht == ColorMode::Random && LeadingBall4[values.StripeIndex] == 0)
            {
                ballcolor4[values.StripeIndex] = ranfarben[random(anz)];
            }

            if (values.Licht == ColorMode::Rainbow)
            {
                if (LeadingBall[values.StripeIndex] == 0)
                {
                    ballcolor[values.StripeIndex] = Wheel(map(LeadingBall[values.StripeIndex], 0, amountLeds - 1, 30, 150));
                    ;
                    ballcolor2[values.StripeIndex] = Wheel(map(LeadingBall[values.StripeIndex], 0, amountLeds - 1, 30, 150));
                    ;
                    ballcolor3[values.StripeIndex] = Wheel(map(LeadingBall[values.StripeIndex], 0, amountLeds - 1, 30, 150));
                    ;
                    ballcolor4[values.StripeIndex] = Wheel(map(LeadingBall[values.StripeIndex], 0, amountLeds - 1, 30, 150));
                    ;
                }
            }
            // Löscht alle Farben
            for (int i = 0; i < amountLeds; i++)
            {
                (*stripe).SetPixelColor(i, RgbColor(0, 0, 0));
            }

            // Ball1 reinrollen lassen
            if (LeadingBall[values.StripeIndex] < balllengh_max)
            {
                balllengh[values.StripeIndex] = LeadingBall[values.StripeIndex];
            }
            else
            {
                balllengh[values.StripeIndex] = balllengh_max;
            }
            // Ball2 reinrollen lassen
            if (LeadingBall2[values.StripeIndex] < balllengh_max)
            {
                balllengh2[values.StripeIndex] = LeadingBall2[values.StripeIndex];
            }
            else
            {
                balllengh2[values.StripeIndex] = balllengh_max;
            }
            // Ball3 reinrollen lassen
            if (LeadingBall3[values.StripeIndex] < balllengh_max)
            {
                balllengh3[values.StripeIndex] = LeadingBall3[values.StripeIndex];
            }
            else
            {
                balllengh3[values.StripeIndex] = balllengh_max;
            }
            // Ball4 reinrollen lassen
            if (LeadingBall4[values.StripeIndex] < balllengh_max)
            {
                balllengh4[values.StripeIndex] = LeadingBall4[values.StripeIndex];
            }
            else
            {
                balllengh4[values.StripeIndex] = balllengh_max;
            }

            // Ball rausrollen lassen
            if (LeadingBall[values.StripeIndex] > amountLeds - balllengh_max)
            {
                balllengh[values.StripeIndex] = amountLeds - LeadingBall[values.StripeIndex];
            }
            else
            {
                balllengh[values.StripeIndex] = balllengh_max;
            }
            // Ball2 rausrollen lassen
            if (LeadingBall2[values.StripeIndex] > amountLeds - balllengh_max)
            {
                balllengh2[values.StripeIndex] = amountLeds - LeadingBall2[values.StripeIndex];
            }
            else
            {
                balllengh2[values.StripeIndex] = balllengh_max;
            }
            // Ball3 rausrollen lassen
            if (LeadingBall3[values.StripeIndex] > amountLeds - balllengh_max)
            {
                balllengh3[values.StripeIndex] = amountLeds - LeadingBall3[values.StripeIndex];
            }
            else
            {
                balllengh3[values.StripeIndex] = balllengh_max;
            }
            // Ball4 rausrollen lassen
            if (LeadingBall4[values.StripeIndex] > amountLeds - balllengh_max)
            {
                balllengh4[values.StripeIndex] = amountLeds - LeadingBall4[values.StripeIndex];
            }
            else
            {
                balllengh4[values.StripeIndex] = balllengh_max;
            }

            // Zeichnet 1. Ball
            for (int i = LeadingBall[values.StripeIndex]; i > LeadingBall[values.StripeIndex] - balllengh[values.StripeIndex]; i--)
            {
                (*stripe).SetPixelColor(i, ballcolor[values.StripeIndex]);
            }

            // Zeichent 2. Ball startet wenn 1. bei viertel angekommen ist
            for (int i = LeadingBall2[values.StripeIndex]; i > LeadingBall2[values.StripeIndex] - balllengh2[values.StripeIndex]; i--)
            {
                (*stripe).SetPixelColor(i, ballcolor2[values.StripeIndex]);
            }

            // Zeichent 3. Ball startet wenn 1. bei hälfte angekommen ist
            for (int i = LeadingBall3[values.StripeIndex]; i > LeadingBall3[values.StripeIndex] - balllengh3[values.StripeIndex]; i--)
            {
                (*stripe).SetPixelColor(i, ballcolor3[values.StripeIndex]);
            }

            // Zeichent 4. Ball startet wenn 1. Ball bei 3/4 ist
            for (int i = LeadingBall4[values.StripeIndex]; i > LeadingBall4[values.StripeIndex] - balllengh4[values.StripeIndex]; i--)
            {
                (*stripe).SetPixelColor(i, ballcolor4[values.StripeIndex]);
            }

            (*stripe).SetBrightness(values.Brightness);
            (*stripe).Show();

            // Speichert Ball Position und Rollover bei amountLeds
            LeadingBall[values.StripeIndex] += 1;

            // Counter für Ball2 startet wenn Ball1 bei 1/4 ist.
            if (LeadingBall[values.StripeIndex] >= viertel)
                frist_run_ball2[values.StripeIndex] = 1;
            if (frist_run_ball2[values.StripeIndex])
                LeadingBall2[values.StripeIndex] += 1;

            // Counter für Ball3 startet wenn Ball1 bei 2/4 ist.
            if (LeadingBall[values.StripeIndex] >= halb)
                frist_run_ball3[values.StripeIndex] = 1;
            if (frist_run_ball3[values.StripeIndex])
                LeadingBall3[values.StripeIndex] += 1;

            // Counter für Ball3 startet wenn Ball1 bei 3/4 ist.
            if (LeadingBall[values.StripeIndex] >= dreiviertel)
                frist_run_ball4[values.StripeIndex] = 1;
            if (frist_run_ball4[values.StripeIndex])
                LeadingBall4[values.StripeIndex] += 1;

            // Resetbedingung Ball1
            if (LeadingBall[values.StripeIndex] >= amountLeds - 1)
            {
                LeadingBall[values.StripeIndex] = 0;
            }

            // Resetbedingung Ball2
            if (LeadingBall2[values.StripeIndex] >= amountLeds - 1)
            {
                LeadingBall2[values.StripeIndex] = 0;
            }

            // Resetbedingung Ball3
            if (LeadingBall3[values.StripeIndex] >= amountLeds - 1)
            {
                LeadingBall3[values.StripeIndex] = 0;
            }

            // Resetbedingung Ball4
            if (LeadingBall4[values.StripeIndex] >= amountLeds - 1)
            {
                LeadingBall4[values.StripeIndex] = 0;
            }

            timerJeStripe[values.StripeIndex] = millis();
        }
    }

    //////////////////////////////////////////////////////////////////////////////////
    // Fertig
    template <class T>
    void ballstackable(T *stripe, setup_stripe values)
    {

        if (millis() - timerJeStripe[values.StripeIndex] >= values.EffectDelay)
        {

            // Farbauswahl
            if (values.Licht == ColorMode::UserColors)
            {
                stackcolor[values.StripeIndex] = values.LED_farbe_1;
            }
            if (values.Licht == ColorMode::Random && LeadingBallStack[values.StripeIndex] == 0)
            {
                stackcolor[values.StripeIndex] = ranfarben[random(anz)];
            }
            if (values.Licht == ColorMode::Rainbow)
            {
                stackcolor[values.StripeIndex] = Wheel(map(LeadingBallStack[values.StripeIndex], 0, amountLeds - 1, 30, 150));
                ;
            }
            // Löscht alle Farben
            for (int i = 0; i < amountLeds; i++)
            {
                (*stripe).SetPixelColor(i, RgbColor(0, 0, 0));
            }

            // Ball1 reinrollen lassen
            if (LeadingBallStack[values.StripeIndex] < balllengh_max)
            {
                balllengh[values.StripeIndex] = LeadingBallStack[values.StripeIndex];
            }
            else
            {
                balllengh[values.StripeIndex] = balllengh_max;
            }

            // Zeichnet 1. Ball
            for (int i = LeadingBallStack[values.StripeIndex]; i > LeadingBallStack[values.StripeIndex] - balllengh[values.StripeIndex]; i--)
            {
                (*stripe).SetPixelColor(i, stackcolor[values.StripeIndex]);
            }

            // Zeichnet stacked Ball
            for (int i = amountLeds; i > (amountLeds - BallOverFlowStack[values.StripeIndex]); i--)
            {
                (*stripe).SetPixelColor(i, stackcolor[values.StripeIndex]);
            }

            (*stripe).SetBrightness(values.Brightness);
            (*stripe).Show();

            // Speichert Ball Position und Rollover bei amountLeds und löscht Streifen
            if (LeadingBallStack[values.StripeIndex] < amountLeds - BallOverFlowStack[values.StripeIndex])
            {
                LeadingBallStack[values.StripeIndex] += 1;
            }
            else
            {
                LeadingBallStack[values.StripeIndex] = 0;
                BallOverFlowStack[values.StripeIndex] += balllengh[values.StripeIndex];
                if (BallOverFlowStack[values.StripeIndex] > amountLeds - balllengh[values.StripeIndex])
                    BallOverFlowStack[values.StripeIndex] = 0;
                // Löscht alle Farben
                for (int i = 0; i < amountLeds; i++)
                {
                    (*stripe).SetPixelColor(i, RgbColor(0, 0, 0));
                }
                (*stripe).Show();
            }

            timerJeStripe[values.StripeIndex] = millis();
        }
    }

    //////////////////////////////////////////////////////////////////////////////////
    // Fertig
    template <class T>
    void ballStackableToCenter(T *stripe, setup_stripe values)
    {

        if (millis() - timerJeStripe[values.StripeIndex] >= values.EffectDelay)
        {
            // Farbauswahl
            if (values.Licht == ColorMode::UserColors)
            {
                stackcentrecolor_left[values.StripeIndex] = values.LED_farbe_1;
                stackcentrecolor_right[values.StripeIndex] = values.LED_farbe_2;
            }
            if (values.Licht == ColorMode::Random && stackBallcentreleft[values.StripeIndex] == 0)
            {
                stackcentrecolor_left[values.StripeIndex] = ranfarben[random(anz)];
                stackcentrecolor_right[values.StripeIndex] = ranfarben[random(anz)];
            }
            if (values.Licht == ColorMode::Random && stackBallcentreright[values.StripeIndex] == amountLeds - 1)
            {
                stackcentrecolor_right[values.StripeIndex] = ranfarben[random(anz)];
                stackcentrecolor_right[values.StripeIndex] = ranfarben[random(anz)];
            }

            // Löscht alle Farben
            for (int i = 0; i < amountLeds; i++)
            {
                (*stripe).SetPixelColor(i, RgbColor(0, 0, 0));
            }

            // Ball1 reinrollen lassen
            if (stackBallcentreleft[values.StripeIndex] < balllengh_max)
            {
                balllengh[values.StripeIndex] = stackBallcentreleft[values.StripeIndex];
            }
            else
            {
                balllengh[values.StripeIndex] = balllengh_max;
            }

            // BAll von links
            for (int i = stackBallcentreleft[values.StripeIndex]; i > stackBallcentreleft[values.StripeIndex] - balllengh[values.StripeIndex]; i--)
            {
                (*stripe).SetPixelColor(i, stackcentrecolor_left[values.StripeIndex]);
            }
            // Stackt ball left
            for (int i = amountLeds_half; i > amountLeds_half - BallOverFlowCentreleft[values.StripeIndex]; i--)
            {
                (*stripe).SetPixelColor(i, stackcentrecolor_left[values.StripeIndex]);
            }

            // BAll von rechts
            for (int i = stackBallcentreright[values.StripeIndex]; i > stackBallcentreright[values.StripeIndex] - balllengh[values.StripeIndex]; i--)
            {
                (*stripe).SetPixelColor(i, stackcentrecolor_right[values.StripeIndex]);
            }
            // Stackt ball rechts
            for (int i = amountLeds_half; i < amountLeds_half + BallOverFlowCentreleft[values.StripeIndex]; i++)
            {
                (*stripe).SetPixelColor(i, stackcentrecolor_right[values.StripeIndex]);
            }

            (*stripe).SetBrightness(values.Brightness);
            (*stripe).Show();

            // Händelt links position und stack
            if (stackBallcentreleft[values.StripeIndex] + balllengh[values.StripeIndex] < amountLeds_half - BallOverFlowCentreleft[values.StripeIndex])
            {
                stackBallcentreleft[values.StripeIndex]++;
            }
            else
            {
                stackBallcentreleft[values.StripeIndex] = 0;
                BallOverFlowCentreleft[values.StripeIndex] += balllengh[values.StripeIndex];
                if (BallOverFlowCentreleft[values.StripeIndex] > amountLeds_half - balllengh[values.StripeIndex])
                {
                    BallOverFlowCentreleft[values.StripeIndex] = 0;
                    // Löscht alle Farben
                    for (int i = 0; i < amountLeds; i++)
                    {
                        (*stripe).SetPixelColor(i, RgbColor(0, 0, 0));
                    }
                    (*stripe).Show();
                }
            }

            // Händelt rechts position und stack
            if (stackBallcentreright[values.StripeIndex] - balllengh[values.StripeIndex] > amountLeds_half + BallOverFlowCentreright[values.StripeIndex])
            {
                stackBallcentreright[values.StripeIndex]--;
            }
            else
            {
                stackBallcentreright[values.StripeIndex] = amountLeds;
                BallOverFlowCentreright[values.StripeIndex] += balllengh[values.StripeIndex];
                if (BallOverFlowCentreright[values.StripeIndex] > amountLeds_half - balllengh[values.StripeIndex])
                {
                    BallOverFlowCentreright[values.StripeIndex] = 0;
                    // Löscht alle Farben
                    for (int i = 0; i < amountLeds; i++)
                    {
                        (*stripe).SetPixelColor(i, RgbColor(0, 0, 0));
                    }
                    (*stripe).Show();
                }
            }

            timerJeStripe[values.StripeIndex] = millis();
        }
    }

    //////////////////////////////////////////////////////////////////////////////////
    // Fertig
    template <class T>
    void vu_centre(T *stripe, setup_stripe values)
    {

        if (millis() - timerJeStripe[values.StripeIndex] >= values.EffectDelay)
        {

            float scale = 0.0;
            uint8_t i;
            uint16_t minLvl, maxLvl;
            int height;
            float n = 0;
            int value = 0;
            RgbColor color;

            int mic = check_micro(!values.IsAux);

            if (!values.IsAux)
            {
                DC_OFFSET = 474; // Offset für Micro
            }
            else
            {
                DC_OFFSET = 440; // Offset für AUX
            }
            //Serial.print("mic = ");Serial.print(mic);Serial.print(" n= ");
            scale = values.Intensity / 100.0;
            n = abs(mic - DC_OFFSET);
            n = n * scale;
            value = (int)n;
            //Serial.println(n);
            lvlJeStripe[values.StripeIndex] = ((lvlJeStripe[values.StripeIndex] * 7) + value) >> 3;

            // Calculate bar height based on dynamic min/max levels (fixed point):
            height = amountLeds * (lvlJeStripe[values.StripeIndex] - minLvlAvgJeStripe[values.StripeIndex]) / (long)(maxLvlAvgJeStripe[values.StripeIndex] - minLvlAvgJeStripe[values.StripeIndex]);
            if (height < 0L)
                height = 0; // Clip output
            else if (height > amountLeds)
                height = amountLeds;
            if (height > peakJeStripe[values.StripeIndex])
                peakJeStripe[values.StripeIndex] = height; // Keep 'peak' dot at top

            // Farbauswahl // Radom macht kein Sinn
            if (values.Licht == ColorMode::UserColors)
            {
                color = values.LED_farbe_1;
            }

            // Color pixels based on rainbow gradient
            for (i = 0; i < amountLeds_half; i++)
            {
                if (i >= height)
                {
                    (*stripe).SetPixelColor(amountLeds_half - i - 1, RgbColor(0, 0, 0));
                    (*stripe).SetPixelColor(amountLeds_half + i, RgbColor(0, 0, 0));
                }
                else
                {
                    if (values.Licht == ColorMode::Rainbow)
                        color = Wheel(map(i, 0, amountLeds_half - 1, 30, 150));
                    (*stripe).SetPixelColor(amountLeds_half - i - 1, color);
                    (*stripe).SetPixelColor(amountLeds_half + i, color);
                }
            }

            // Draw peak dot
            if (peakJeStripe[values.StripeIndex] > 0 && peakJeStripe[values.StripeIndex] <= amountLeds - 1)
            {
                RgbColor color_peak = Wheel(map(peakJeStripe[values.StripeIndex], 0, amountLeds_half - 1, 30, 150));
                (*stripe).SetPixelColor(amountLeds_half - peakJeStripe[values.StripeIndex] - 1, color_peak);
                (*stripe).SetPixelColor(amountLeds_half + peakJeStripe[values.StripeIndex], color_peak);
            }

            (*stripe).SetBrightness(values.Brightness);
            (*stripe).Show(); // Update strip

            // Every few frames, make the peak pixel drop by 1:
            if (++dotcountJeStripe[values.StripeIndex] >= PEAK_FALL)
            { //fall rate
                if (peakJeStripe[values.StripeIndex] > 0)
                    peakJeStripe[values.StripeIndex]--;
                dotcountJeStripe[values.StripeIndex] = 0;
            }

            volJeStripe[values.StripeIndex][volCountJeStripe[values.StripeIndex]] = n; // Save sample for dynamic leveling
            if (++volCountJeStripe[values.StripeIndex] >= SAMPLES)
                volCountJeStripe[values.StripeIndex] = 0; // Advance/rollover sample counter

            // Get volume range of prior frames
            minLvl = maxLvl = volJeStripe[values.StripeIndex][0];
            for (i = 1; i < SAMPLES; i++)
            {
                if (volJeStripe[values.StripeIndex][i] < minLvl)
                    minLvl = volJeStripe[values.StripeIndex][i];
                else if (volJeStripe[values.StripeIndex][i] > maxLvl)
                    maxLvl = volJeStripe[values.StripeIndex][i];
            }

            if ((maxLvl - minLvl) < amountLeds_top)
                maxLvl = minLvl + amountLeds_top;
            minLvlAvgJeStripe[values.StripeIndex] = (minLvlAvgJeStripe[values.StripeIndex] * 63 + minLvl) >> 6;
            maxLvlAvgJeStripe[values.StripeIndex] = (maxLvlAvgJeStripe[values.StripeIndex] * 63 + maxLvl) >> 6;

            timerJeStripe[values.StripeIndex] = millis();
        }
    }

    //////////////////////////////////////////////////////////////////////////////////
    // Fertig
    template <class T>
    void vunormal(T *stripe, setup_stripe values)
    {

        if (millis() - timerJeStripe[values.StripeIndex] >= values.EffectDelay)
        {
            float scale = 0.0;
            uint8_t i;
            uint16_t minLvl, maxLvl;
            int height;
            float n = 0;
            int value = 0;
            RgbColor color;

            int mic = check_micro(!values.IsAux);

            if (!values.IsAux)
            {
                DC_OFFSET = 474; // Offset für Micro
            }
            else
            {
                DC_OFFSET = 440; // Offset für AUX
            }

            scale = values.Intensity / 100.0;
            n = abs(mic - DC_OFFSET);
            n = n * scale;
            value = (int)n;

            lvlJeStripe[values.StripeIndex] = ((lvlJeStripe[values.StripeIndex] * 7) + value) >> 3;

            int nenner = (long)(maxLvlAvgJeStripe[values.StripeIndex] - minLvlAvgJeStripe[values.StripeIndex]);
            int zaehler = amountLeds * (lvlJeStripe[values.StripeIndex] - minLvlAvgJeStripe[values.StripeIndex]);
            // Calculate bar height based on dynamic min/max levels (fixed point):
            height = zaehler / nenner;

            if (height < 0L)
                height = 0; // Clip output
            else if (height > amountLeds)
                height = amountLeds;
            if (height > peakJeStripe[values.StripeIndex])
                peakJeStripe[values.StripeIndex] = height; // Keep 'peak' dot at top

            if (values.Licht == ColorMode::UserColors)
            {
                color = values.LED_farbe_1;
            }
            if (values.Licht == ColorMode::Random)
            {
                color = ranfarben[random(anz)];
            }

            // Color pixels based on rainbow gradient
            for (i = 0; i < amountLeds; i++)
            {
                if (i >= height)
                {
                    (*stripe).SetPixelColor(i, RgbColor(0, 0, 0));
                }
                else
                {
                    if (values.Licht == ColorMode::Rainbow)
                    {
                        color = Wheel(map(i, 0, amountLeds - 1, 30, 150));
                    }
                    (*stripe).SetPixelColor(i, color);
                }
            }

            // Draw peak dot
            if (peakJeStripe[values.StripeIndex] > 0 && peakJeStripe[values.StripeIndex] <= amountLeds - 1)
            {
                RgbColor color_peak = Wheel(map(peakJeStripe[values.StripeIndex], 0, amountLeds - 1, 30, 150));
                (*stripe).SetPixelColor(peakJeStripe[values.StripeIndex], color_peak);
            }

            (*stripe).SetBrightness(values.Brightness);

            (*stripe).Show(); // Update strip

            // Every few frames, make the peak pixel drop by 1:
            if (++dotcountJeStripe[values.StripeIndex] >= PEAK_FALL)
            { //fall rate

                if (peakJeStripe[values.StripeIndex] > 0)
                    peakJeStripe[values.StripeIndex]--;
                dotcountJeStripe[values.StripeIndex] = 0;
            }

            volJeStripe[values.StripeIndex][volCountJeStripe[values.StripeIndex]] = n; // Save sample for dynamic leveling
            if (++volCountJeStripe[values.StripeIndex] >= SAMPLES)
                volCountJeStripe[values.StripeIndex] = 0; // Advance/rollover sample counter

            // Get volume range of prior frames
            minLvl = maxLvl = volJeStripe[values.StripeIndex][0];
            for (i = 1; i < SAMPLES; i++)
            {
                if (volJeStripe[values.StripeIndex][i] < minLvl)
                    minLvl = volJeStripe[values.StripeIndex][i];
                else if (volJeStripe[values.StripeIndex][i] > maxLvl)
                    maxLvl = volJeStripe[values.StripeIndex][i];
            }

            if ((maxLvl - minLvl) < amountLeds_top)
                maxLvl = minLvl + amountLeds_top;
            minLvlAvgJeStripe[values.StripeIndex] = (minLvlAvgJeStripe[values.StripeIndex] * 63 + minLvl) >> 6;
            maxLvlAvgJeStripe[values.StripeIndex] = (maxLvlAvgJeStripe[values.StripeIndex] * 63 + maxLvl) >> 6;

            timerJeStripe[values.StripeIndex] = millis();
        }
    }

    //////////////////////////////////////////////////////////////////////////////////
    // Fertig
    template <class T>
    void lavalampemove(T *stripe, setup_stripe values)
    {

        if (millis() - timerJeStripe[values.StripeIndex] >= values.EffectDelay)
        {
            // Farbauswahl
            if (values.Licht == ColorMode::UserColors)
            {
                lavacolor_hoch[values.StripeIndex] = values.LED_farbe_1;
                lavacolor_runter[values.StripeIndex] = values.LED_farbe_2;
            }
            if (values.Licht == ColorMode::Random)
            {
                if (lavaLampPositon[values.StripeIndex] == 0)
                    lavacolor_hoch[values.StripeIndex] = ranfarben[random(anz)];
                if (lavaLampPositon[values.StripeIndex] == amountLeds - 1)
                    lavacolor_runter[values.StripeIndex] = ranfarben[random(anz)];
            }
            if (values.Licht == ColorMode::Rainbow)
            {
                lavacolor_hoch[values.StripeIndex] = Wheel(map(lavaLampPositon[values.StripeIndex], 0, amountLeds - 1, 30, 150));
                ;
                lavacolor_runter[values.StripeIndex] = Wheel(map(amountLeds - lavaLampPositon[values.StripeIndex], 0, amountLeds - 1, 30, 150));
                ;
            }

            // Zeichet Streifen je nach Richtung
            if (RichtungLavalampe[values.StripeIndex] == 0)
            {
                (*stripe).SetPixelColor(lavaLampPositon[values.StripeIndex], lavacolor_hoch[values.StripeIndex]);
                (*stripe).SetBrightness(values.Brightness);
                (*stripe).Show();
                lavaLampPositon[values.StripeIndex]++;
                if (lavaLampPositon[values.StripeIndex] >= amountLeds)
                {
                    RichtungLavalampe[values.StripeIndex] = 1;
                    lavaLampPositon[values.StripeIndex] = amountLeds;
                }
            }
            else
            {
                (*stripe).SetPixelColor(lavaLampPositon[values.StripeIndex], lavacolor_runter[values.StripeIndex]);
                (*stripe).SetBrightness(values.Brightness);
                (*stripe).Show();
                lavaLampPositon[values.StripeIndex]--;
                if (lavaLampPositon[values.StripeIndex] <= 0)
                {
                    RichtungLavalampe[values.StripeIndex] = 0;
                    lavaLampPositon[values.StripeIndex] = 0;
                }
            }
            (*stripe).SetBrightness(values.Brightness);
            (*stripe).Show();
            timerJeStripe[values.StripeIndex] = millis();
        }
    }

    //////////////////////////////////////////////////////////////////////////////////
    // Fertig
    template <class T>
    void movingRainbow(T *stripe, setup_stripe values)
    {

        if (millis() - timerJeStripe[values.StripeIndex] >= values.EffectDelay)
        {

            for (int i = 0; i < amountLeds; i++)
            {
                RgbColor color = Wheel(map(i, 0, amountLeds - 1, 30, 150));
                (*stripe).SetPixelColor(((i + mRainbowStep[values.StripeIndex]) % amountLeds), color);
            }

            (*stripe).SetBrightness(values.Brightness);
            (*stripe).Show();

            // updatet Position nach aufruf
            mRainbowStep[values.StripeIndex]++;
            if (mRainbowStep[values.StripeIndex] > amountLeds)
                mRainbowStep[values.StripeIndex] = 0;

            timerJeStripe[values.StripeIndex] = millis();
        }
    }

    //////////////////////////////////////////////////////////////////////////////////
    // Fertig
    template <class T>
    void fillup(T *stripe, setup_stripe values)
    {

        if (millis() - timerJeStripe[values.StripeIndex] >= values.EffectDelay)
        {
            RgbColor color;

            // Farbauswahl
            if (values.Licht == ColorMode::UserColors)
            {
                color = values.LED_farbe_1;
            }
            if (values.Licht == ColorMode::Random && fillupstep[values.StripeIndex] == 0)
            {
                color = ranfarben[random(anz)];
            }
            if (values.Licht == ColorMode::Rainbow)
            {
                color = Wheel(map(fillupstep[values.StripeIndex], 0, amountLeds - 1, 30, 150));
                ;
            }

            // Zeichnet Streifen
            if (durchlauffillup[values.StripeIndex])
            {
                (*stripe).SetPixelColor(fillupstep[values.StripeIndex], color);
            }
            else
            {
                (*stripe).SetPixelColor(fillupstep[values.StripeIndex], RgbColor(0, 0, 0));
            }
            (*stripe).SetBrightness(values.Brightness);
            (*stripe).Show();

            // updatet Position nach aufruf
            fillupstep[values.StripeIndex]++;
            if (fillupstep[values.StripeIndex] > amountLeds)
            {
                fillupstep[values.StripeIndex] = 0;
                durchlauffillup[values.StripeIndex] = durchlauffillup[values.StripeIndex] ^ 1;
            }
            timerJeStripe[values.StripeIndex] = millis();
        }
    }

    //////////////////////////////////////////////////////////////////////////////////

    template <class T>
    void fillup2(T *stripe, setup_stripe values)
    {

        if (millis() - timerJeStripe[values.StripeIndex] >= values.EffectDelay)
        {

            // Farbauswahl
            if (values.Licht == ColorMode::UserColors)
            {
                fullup2color[values.StripeIndex] = values.LED_farbe_1;
                fullup2color2[values.StripeIndex] = values.LED_farbe_2;
            }

            if (values.Licht == ColorMode::Random && fillup2step[values.StripeIndex] == 0)
            {
                fullup2color[values.StripeIndex] = ranfarben[random(anz)];
                fullup2color2[values.StripeIndex] = ranfarben[random(anz)];
            }

            if (values.Licht == ColorMode::Rainbow)
            {
                fullup2color[values.StripeIndex] = Wheel(map(fillup2step[values.StripeIndex], 0, amountLeds_half - 1, 30, 150));
                ;
                fullup2color2[values.StripeIndex] = fullup2color[values.StripeIndex];
            }

            // Zeichnet Streifen
            if (durchlauffillup2[values.StripeIndex])
            {
                (*stripe).SetPixelColor(fillup2step[values.StripeIndex], fullup2color[values.StripeIndex]);
                (*stripe).SetPixelColor(fillup2step[values.StripeIndex] + amountLeds_half, fullup2color2[values.StripeIndex]);
            }
            else
            {
                RgbColor color = RgbColor(0, 0, 0);
                (*stripe).SetPixelColor(fillup2step[values.StripeIndex], color);
                (*stripe).SetPixelColor(fillup2step[values.StripeIndex] + amountLeds_half, color);
            }

            (*stripe).SetBrightness(values.Brightness);
            (*stripe).Show();

            // updatet Position nach aufruf
            fillup2step[values.StripeIndex]++;
            if (fillup2step[values.StripeIndex] > amountLeds_half)
            {
                fillup2step[values.StripeIndex] = 0;
                durchlauffillup2[values.StripeIndex] = durchlauffillup2[values.StripeIndex] ^ 1;
            }

            timerJeStripe[values.StripeIndex] = millis();
        }
    }

    //////////////////////////////////////////////////////////////////////////////////
    // Fertig
    template <class T>
    void fillup3(T *stripe, setup_stripe values)
    {
        int drittel = std::ceil(amountLeds / 3);
        int zweidrittel = std::ceil(amountLeds * 2 / 3);

        if (millis() - timerJeStripe[values.StripeIndex] >= values.EffectDelay)
        {

            int einviertel = amountLeds / 4;
            int halb = amountLeds_half;
            int dreiviertel = amountLeds * 3 / 4;
            int voll = amountLeds;

            // Farbauswahl
            if (values.Licht == ColorMode::UserColors)
            {
                fullup3color[values.StripeIndex] = values.LED_farbe_1;
                fullup3color2[values.StripeIndex] = values.LED_farbe_2;
                fullup3color3[values.StripeIndex] = values.LED_farbe_3;
            }
            if (values.Licht == ColorMode::Random && fillup3step[values.StripeIndex] == 0)
            {
                fullup3color[values.StripeIndex] = ranfarben[random(anz)];
                fullup3color2[values.StripeIndex] = ranfarben[random(anz)];
                fullup3color3[values.StripeIndex] = ranfarben[random(anz)];
            }
            if (values.Licht == ColorMode::Rainbow)
            {
                fullup3color[values.StripeIndex] = Wheel(map(fillup3step[values.StripeIndex], 0, (amountLeds - 1) / 4, 30, 150));
                ;
                fullup3color2[values.StripeIndex] = fullup3color[values.StripeIndex];
                fullup3color3[values.StripeIndex] = fullup3color[values.StripeIndex];
            }

            // Zeichnet Streifen
            if (durchlauffillup3[values.StripeIndex] == false)
            {
                (*stripe).SetPixelColor(fillup3step[values.StripeIndex], fullup3color[values.StripeIndex]);
                (*stripe).SetPixelColor(fillup3step[values.StripeIndex] + drittel, fullup3color2[values.StripeIndex]);
                (*stripe).SetPixelColor(fillup3step[values.StripeIndex] + zweidrittel, fullup3color3[values.StripeIndex]);
            }
            else
            {
                RgbColor color = RgbColor(0, 0, 0);
                (*stripe).SetPixelColor(fillup3step[values.StripeIndex], color);
                (*stripe).SetPixelColor(fillup3step[values.StripeIndex] + drittel, color);
                (*stripe).SetPixelColor(fillup3step[values.StripeIndex] + zweidrittel, color);
            }

            (*stripe).SetBrightness(values.Brightness);
            (*stripe).Show();

            // updatet Position nach aufruf
            fillup3step[values.StripeIndex]++;
            if (fillup3step[values.StripeIndex] > amountLeds / 3)
            {
                fillup3step[values.StripeIndex] = 0;
                durchlauffillup3[values.StripeIndex] = durchlauffillup3[values.StripeIndex] ^ 1;
            }

            timerJeStripe[values.StripeIndex] = millis();
        }
    }

    //////////////////////////////////////////////////////////////////////////////////
    // Fertig
    template <class T>
    void fillup4(T *stripe, setup_stripe values)
    {

        auto ntime = millis();
        if (ntime - timerJeStripe[values.StripeIndex] >= values.EffectDelay)
        {

            int einviertel = amountLeds / 4;
            int halb = amountLeds / 2;
            int dreiviertel = amountLeds * 3 / 4;
            int voll = amountLeds;

            Serial.println(fillup4step[values.StripeIndex]);

            // Farbauswahl
            if (values.Licht == ColorMode::UserColors)
            {
                fullup4color[values.StripeIndex] = values.LED_farbe_1;
                fullup4color2[values.StripeIndex] = values.LED_farbe_2;
                fullup4color3[values.StripeIndex] = values.LED_farbe_3;
                fullup4color4[values.StripeIndex] = values.LED_farbe_4;
            }

            if (values.Licht == ColorMode::Random && fillup4step[values.StripeIndex] == 0)
            {
                fullup4color[values.StripeIndex] = ranfarben[random(anz)];
                fullup4color2[values.StripeIndex] = ranfarben[random(anz)];
                fullup4color3[values.StripeIndex] = ranfarben[random(anz)];
                fullup4color4[values.StripeIndex] = ranfarben[random(anz)];
            }

            if (values.Licht == ColorMode::Rainbow)
            {
                fullup4color[values.StripeIndex] = Wheel(map(fillup4step[values.StripeIndex], 0, (amountLeds - 1) / 4, 30, 150));
                ;
                fullup4color2[values.StripeIndex] = fullup4color[values.StripeIndex];
                fullup4color3[values.StripeIndex] = fullup4color[values.StripeIndex];
                fullup4color4[values.StripeIndex] = fullup4color[values.StripeIndex];
            }

            // Zeichnet Streifen
            if (durchlauffillup4[values.StripeIndex] == false)
            {
                (*stripe).SetPixelColor(fillup4step[values.StripeIndex], fullup4color[values.StripeIndex]);
                (*stripe).SetPixelColor(fillup4step[values.StripeIndex] + einviertel, fullup4color2[values.StripeIndex]);
                (*stripe).SetPixelColor(fillup4step[values.StripeIndex] + halb, fullup4color3[values.StripeIndex]);
                (*stripe).SetPixelColor(fillup4step[values.StripeIndex] + dreiviertel, fullup4color4[values.StripeIndex]);
            }
            else
            {
                RgbColor color = RgbColor(0, 0, 0);
                (*stripe).SetPixelColor(fillup4step[values.StripeIndex], color);
                (*stripe).SetPixelColor(fillup4step[values.StripeIndex] + einviertel, color);
                (*stripe).SetPixelColor(fillup4step[values.StripeIndex] + halb, color);
                (*stripe).SetPixelColor(fillup4step[values.StripeIndex] + dreiviertel, color);
            }

            (*stripe).SetBrightness(values.Brightness);
            (*stripe).Show();

            // updatet Position nach aufruf
            fillup4step[values.StripeIndex]++;
            if (fillup4step[values.StripeIndex] > amountLeds / 4)
            {
                fillup4step[values.StripeIndex] = 0;
                durchlauffillup4[values.StripeIndex] = durchlauffillup4[values.StripeIndex] ^ 1;
            }

            timerJeStripe[values.StripeIndex] = ntime;
        }
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Fertig
    void reset_hilfsvariablen(setup_stripe values)
    {
        frist_run_ball2[values.StripeIndex] = 0;
        frist_run_ball3[values.StripeIndex] = 0;
        frist_run_ball4[values.StripeIndex] = 0;
    }

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////

    inline void prozzesFFT(void)
    {
        // Fertig
        if (micros() - oldtime >= samplingDelay)
        {

            //Channel Auswahl
            (p_strip1.IsAux) ? CHANNEL = AUX_Eingang : CHANNEL = MicroEingang;
            (p_strip2.IsAux) ? CHANNEL = AUX_Eingang : CHANNEL = MicroEingang;

            // Ließt Analogwert ins Array
            vReal[idex] = analogRead(CHANNEL);
            vImag[idex] = 0;

            // nach einlesen Update Index
            idex++;
            if (idex > samples_fft)
            {
                idex = 0;  // Index wird zurückgesetzt
                isRdy = 1; // Zeigt an das genug Samples für FFT Berechnung vorhanden sind
            }

            oldtime = micros();
        }

        if (isRdy)
        {
            FFT.Windowing(vReal, samples_fft, FFT_WIN_TYP_HAMMING, FFT_FORWARD); /* Weigh data */
            FFT.Compute(vReal, vImag, samples_fft, FFT_FORWARD);                 /* Compute FFT */
            FFT.ComplexToMagnitude(vReal, vImag, samples_fft);                   /* Compute magnitudes */
            double x = FFT.MajorPeak(vReal, samples_fft, samplingFrequency);     // Gibt Frequenz mit höhster Amplitude zurück
            x = (int)x;
            if (x > maxfreq)
                x = maxfreq;
            int S1delay = map(x, 0, maxfreq, delaxMin, delayMax); // Skalliert Effectdelay jeh dominierende Frequenz
            int S2delay = map(x, 0, maxfreq, delaxMin, delayMax); // Skalliert Effectdelay jeh dominierende Frequenz
            p_strip1.EffectDelay = S1delay;                       // Schreibt neuen Delaywert
            p_strip2.EffectDelay = S2delay;                       // Schreibt neuen Delaywert
            isRdy = 0;
        }
    }

} // namespace LedBridge
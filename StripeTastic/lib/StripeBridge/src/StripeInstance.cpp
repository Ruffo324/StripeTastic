#include "StripeInstance.h"
#include "StripeBridge.h"
#include "Constants/Colors.h"
#include "Constants/MoreConstants.h"
#include "Services.h"
#include "Enums/ColorModes.h"

namespace StripeBridge
{
    template <class TRmtMethod>
    void StripeInstance<TRmtMethod>::Initialize()
    {
        _processingDataChanged = false;
        _stripeBus.Begin();
        LoadOrCreateProcessingData();
        _loopService->Register(_loopRegistrationKey, [this]() { LoopProcessing(); });

        _logger->Logln(_loggerTag, "Stripe '" + _loopRegistrationKey + "' is ready.");
        Off();
    }

    template <class TRmtMethod>
    StripeInstance<TRmtMethod>::StripeInstance(int pin, int pixelCount)
        : _stripeBus(pixelCount, pin), _information(), _processingData(), _effectsData()
    {
        _logger = Services::Logger::GetInstance();
        _loopService = Services::LoopService::GetInstance();

        pinMode(pin, OUTPUT);

        _information.GPIOPin = pin;
        _information.PixelCount = pixelCount;
        _effectsData.SetPixelCount(pixelCount);

        _loopRegistrationKey = "STRIPE_INSTANCE_" + String(StripeBridge::GetNewStripeInstanceId());

        _logger->Logln(_loggerTag, "Stripe " + _loopRegistrationKey + "(GPIO: " + pin + ", Pixels:" + pixelCount + " ) created..");
        Initialize();
    }

    template <class TRmtMethod>
    void StripeInstance<TRmtMethod>::LoopProcessing()
    {
        // if (_processingData.FFTActive)
        //     processFFT();

        programm();
    }

    template <class TRmtMethod>
    void StripeInstance<TRmtMethod>::LoadOrCreateProcessingData()
    {
        // TODO: Store and load processing data.!
        ResetProcessingData();
    }

    template <class TRmtMethod>
    void StripeInstance<TRmtMethod>::ResetProcessingData()
    {
        _processingData = Models::StripeProcessingData();
    }

    template <class TRmtMethod>
    void StripeInstance<TRmtMethod>::UpdateProcessingData(Models::StripeProcessingData data)
    {
        _processingDataChanged = !_processingData.IsEqal(data);
        _processingData = data;
    }

    template <class TRmtMethod>
    void StripeInstance<TRmtMethod>::Show(bool setBrightness)
    {
        if (setBrightness)
            _stripeBus.SetBrightness(_processingData.Brightness);

        _stripeBus.Show();
    }

    template <class TRmtMethod>
    void StripeInstance<TRmtMethod>::SetPixelColor(uint16_t pixel, RgbColor color)
    {
        // TODO: Add here event call to web client for live preview.
        _stripeBus.SetPixelColor(pixel, color);
    }

    template <class TRmtMethod>
    void StripeInstance<TRmtMethod>::Off(bool withShow = true)
    {
        for (int i = 0; i < _information.PixelCount; i++)
            _stripeBus.SetPixelColor(i, Constants::Colors::Off);

        if (withShow)
            Show(false);
    }

    template <class TRmtMethod>
    void StripeInstance<TRmtMethod>::SolidUserColor(Enums::ColorMode colorMode)
    {
        auto totalPixel = _information.PixelCount;

        switch (colorMode)
        {
        // Single user ncolor.
        case Enums::ColorMode::OneUserColor:
        {
            for (int i = 0; i < totalPixel; i++)
                SetPixelColor(i, _processingData.LED_farbe_1);
            break;
        }
        // Two user colors.
        case Enums::ColorMode::TwoUserColors:
        {
            auto segmentPixel = _information.PixelCountTwoColors();

            for (uint16_t i = 0; i < segmentPixel; i++)
                SetPixelColor(i, _processingData.LED_farbe_1);
            for (uint16_t i = segmentPixel; i < totalPixel; i++)
                SetPixelColor(i, _processingData.LED_farbe_2);
            break;
        }
        // Three user colos.
        case Enums::ColorMode::ThreeUserColors:
        {
            auto segmentPixel = _information.PixelCountThreeColors();

            for (uint16_t i = 0; i < segmentPixel; i++)
                SetPixelColor(i, _processingData.LED_farbe_1);
            for (uint16_t i = segmentPixel; i < segmentPixel * 2; i++)
                SetPixelColor(i, _processingData.LED_farbe_2);
            for (uint16_t i = segmentPixel * 2; i < totalPixel; i++)
                SetPixelColor(i, _processingData.LED_farbe_3);
            break;
        }
        // Invalid ColorModes.
        default:
            _logger->Logln(_loggerTag, "StripeInstance::SolidUserColor() can only be used with user base Enums::ColorModes.");
            return;
        }
        Show();
    }

    //=========================================================================================================
    //========================== // TODO: Code below needs Cleanup & refactoring sometimes.. ==================
    //=========================================================================================================
    template <class TRmtMethod>
    void StripeInstance<TRmtMethod>::programm()
    {
        switch (_processingData.OperationMode)
        {
        case (Enums::OperationModes::Off):
            Off();
            break;
        // TODO: Create subclass for effects only.
        case (Enums::OperationModes::Effect):
            switch (_processingData.Effect)
            {
            case Enums::Effects::Strobo:
                strobo();
                break;
            case Enums::Effects::Ball:
                ball();
                break;
            case Enums::Effects::BallStackable:
                ballstackable();
                break;
            case Enums::Effects::BallStackableToCenter:
                ballStackableToCenter();
                break;
            case Enums::Effects::Music:
                vunormal();
                break;
            case Enums::Effects::MusicFromCenter:
                vu_centre();
                break;
            case Enums::Effects::LavaLamp:
                lavalampemove();
                break;
            case Enums::Effects::MovingRainbow:
                movingRainbow();
                break;
            case Enums::Effects::FillUp:
                fillup();
                break;
            case Enums::Effects::FillUp2:
                fillup2();
                break;
            case Enums::Effects::FillUp3:
                fillup3();
                break;
            case Enums::Effects::FillUp4:
                fillup4();
                break;
            }
            break;

        case (Enums::OperationModes::Static):
            if (_processingDataChanged)
            {
                switch (_processingData.Licht)
                {
                case Enums::ColorMode::Rainbow:
                    rainbow(stripe, values);
                    break;
                case Enums::ColorMode::Random:
                    zufall(stripe, values);
                    break;
                case Enums::ColorMode::OneUserColor:
                case Enums::ColorMode::TwoUserColors:
                case Enums::ColorMode::ThreeUserColors:
                    SolidUserColor(_processingData.Licht);
                    break;
                }
                _processingDataChanged = false;
            }
            break;
        }
    }

    template <class TRmtMethod>
    int StripeInstance<TRmtMethod>::check_micro(bool micro_aux)
    {
        int temp[10];
        int tem = 0;

        if (micro_aux)
            for (int i = 0; i < 10; i++)
                temp[i] = analogRead(MicroEingang);
        else
            for (int i = 0; i < 10; i++)
                temp[i] = analogRead(AUX_Eingang);

        for (int i = 0; i < 10; i++)
            tem += temp[i];

        return tem / 10;
    }

    template <class TRmtMethod>
    void StripeInstance<TRmtMethod>::rainbow()
    {
        auto pixelCount = _information.PixelCount;
        auto pixelCountTop = _information.PixelCountTop();
        for (int i = 0; i < pixelCount; i++)
        {
            RgbColor color = Wheel(map(i, 0, pixelCount - 1, 30, 150));
            SetPixelColor(pixelCountTop - i - 1, color);
        }
        Show();
    }

    template <class TRmtMethod>
    void StripeInstance<TRmtMethod>::zufall()
    {
        auto color = Constants::Colors::GetRandomColor();
        auto pixelCount = _information.PixelCount;
        auto pixelCountTop = _information.PixelCountTop();

        for (int i = 0; i < pixelCount; i++)
            SetPixelColor(pixelCountTop - i - 1, color);

        Show();
    }

    /////////////////////////////////////////////////////////////////////////////
    //                                   EFFECTS                               //
    /////////////////////////////////////////////////////////////////////////////

    template <class TRmtMethod>
    void StripeInstance<TRmtMethod>::strobo()
    {
        if (millis() - _effectsData.effectsTimer >= (1000 / _processingData.FlashPerSeconds))
        {
            // Farbauswahl
            if (_processingData.Licht == Enums::ColorMode::OneUserColor)
                _effectsData.StroboColor = _processingData.LED_farbe_1;
            else if (_processingData.Licht == Enums::ColorMode::Random)
                _effectsData.StroboColor = Constants::Colors::GetRandomColor();
            else if (_processingData.Licht == Enums::ColorMode::Rainbow) // macht kein Sinn aber lass ich mal drin
                _effectsData.StroboColor = _processingData.LED_farbe_1;

            RgbColor color = (_effectsData.StroboDurchlauf = !_effectsData.StroboDurchlauf) ? _effectsData.StroboColor : Constants::Colors::Off;
            for (uint16_t i = 0; i < _information.PixelCount; i++)
                SetPixelColor(i, _effectsData.StroboColor);

            Show();
            _effectsData.effectsTimer = millis();
        }
    }

    template <class TRmtMethod>
    void StripeInstance<TRmtMethod>::ball()
    {

        if (!(millis() - effectsTimer >= _processingData.EffectDelay))
            return;

        auto pixelCount = _information.PixelCount;
        int viertel = pixelCount / 4;
        int halb = _information.PixelCountTwoColors();
        int dreiviertel = pixelCount * 3 / 4;

        // Farbauswahl
        if (_processingData.Licht == Enums::ColorMode::OneUserColor)
        {
            _effectsData.ballcolor = _processingData.LED_farbe_1;
            _effectsData.ballcolor2 = _processingData.LED_farbe_2;
            _effectsData.ballcolor3 = _processingData.LED_farbe_3;
            _effectsData.ballcolor4 = _processingData.LED_farbe_4;
        }
        else if (_processingData.Licht == Enums::ColorMode::Random)
        {
            if (_effectsData.LeadingBall == 0)
                _effectsData.ballcolor = Constants::Colors::GetRandomColor();
            if (_effectsData.LeadingBall2 == 0)
                _effectsData.ballcolor2 = Constants::Colors::GetRandomColor();
            if (_effectsData.LeadingBall3 == 0)
                _effectsData.ballcolor3 = Constants::Colors::GetRandomColor();
            if (_effectsData.LeadingBall4 == 0)
                _effectsData.ballcolor4 = Constants::Colors::GetRandomColor();
        }
        else if (_processingData.Licht == Enums::ColorMode::Rainbow)
        {
            if (_effectsData.LeadingBall == 0)
            {
                _effectsData.ballcolor = Constants::Colors::Wheel(map(_effectsData.LeadingBall, 0, pixelCount - 1, 30, 150));
                _effectsData.ballcolor2 = Constants::Colors::Wheel(map(_effectsData.LeadingBall, 0, pixelCount - 1, 30, 150));
                _effectsData.ballcolor3 = Constants::Colors::Wheel(map(_effectsData.LeadingBall, 0, pixelCount - 1, 30, 150));
                _effectsData.ballcolor4 = Constants::Colors::Wheel(map(_effectsData.LeadingBall, 0, pixelCount - 1, 30, 150));
            }
            // TODO, fehlen hier ggf. noch die anderen bälle?
        }

        // Löscht alle Farben
        Off(false);

        auto maxBallLength = _effectsData.balllengh_max;

        // Ball1 reinrollen lassen
        _effectsData.balllengh = _effectsData.LeadingBall < maxBallLength ? _effectsData.LeadingBall : maxBallLength;

        // Ball2 reinrollen lassen
        _effectsData.balllengh2 = _effectsData.LeadingBall2 < maxBallLength ? _effectsData.LeadingBall2 : maxBallLength;

        // Ball3 reinrollen lassen
        _effectsData.balllengh3 = _effectsData.LeadingBall3 < maxBallLength ? _effectsData.LeadingBall3 : maxBallLength;

        // Ball4 reinrollen lassen
        _effectsData.balllengh4 = _effectsData.LeadingBall4 < maxBallLength ? _effectsData.LeadingBall4 : maxBallLength;

        // Ball rausrollen lassen
        _effectsData.balllengh = (_effectsData.LeadingBall > pixelCount - maxBallLength) ? pixelCount - _effectsData.LeadingBall : maxBallLength;

        // Ball2 rausrollen lassen
        _effectsData.balllengh2 = (_effectsData.LeadingBall2 > pixelCount - maxBallLength) ? pixelCount - _effectsData.LeadingBall2 : maxBallLength;

        // Ball3 rausrollen lassen
        _effectsData.balllengh3 = (_effectsData.LeadingBall3 > pixelCount - maxBallLength) ? pixelCount - _effectsData.LeadingBall3 : maxBallLength;
        // Ball4 rausrollen lassen
        _effectsData.balllengh4 = (_effectsData.LeadingBall4 > pixelCount - maxBallLength) ? pixelCount - _effectsData.LeadingBall4 : maxBallLength;

        // Zeichnet 1. Ball
        for (int i = _effectsData.LeadingBall; i > _effectsData.LeadingBall - _effectsData.balllengh; i--)
            SetPixelColor(i, _effectsData.ballcolor);

        // Zeichent 2. Ball startet wenn 1. bei viertel angekommen ist
        for (int i = _effectsData.LeadingBall2; i > _effectsData.LeadingBall2 - _effectsData.balllengh2; i--)
            SetPixelColor(i, _effectsData.ballcolor2);

        // Zeichent 3. Ball startet wenn 1. bei hälfte angekommen ist
        for (int i = _effectsData.LeadingBall3; i > _effectsData.LeadingBall3 - _effectsData.balllengh3; i--)
            SetPixelColor(i, _effectsData.ballcolor3);

        // Zeichent 4. Ball startet wenn 1. Ball bei 3/4 ist
        for (int i = _effectsData.LeadingBall4; i > _effectsData.LeadingBall4 - _effectsData.balllengh4; i--)
            SetPixelColor(i, _effectsData.ballcolor4);

        Show();

        // Speichert Ball Position und Rollover bei pixelCount
        _effectsData.LeadingBall++;

        // Counter für Ball2 startet wenn Ball1 bei 1/4 ist.
        if (_effectsData.LeadingBall >= viertel)
            _effectsData.frist_run_ball2 = 1;
        if (_effectsData.frist_run_ball2)
            _effectsData.LeadingBall2 += 1;

        // Counter für Ball3 startet wenn Ball1 bei 2/4 ist.
        if (_effectsData.LeadingBall >= halb)
            _effectsData.frist_run_ball3 = 1;
        if (_effectsData.frist_run_ball3)
            _effectsData.LeadingBall3 += 1;

        // Counter für Ball3 startet wenn Ball1 bei 3/4 ist.
        if (_effectsData.LeadingBall >= dreiviertel)
            _effectsData.frist_run_ball4 = 1;
        if (_effectsData.frist_run_ball4)
            _effectsData.LeadingBall4 += 1;

        // Resetbedingung Ball1
        if (_effectsData.LeadingBall >= pixelCount - 1)
            _effectsData.LeadingBall = 0;

        // Resetbedingung Ball2
        if (_effectsData.LeadingBall2 >= pixelCount - 1)
            _effectsData.LeadingBall2 = 0;

        // Resetbedingung Ball3
        if (_effectsData.LeadingBall3 >= pixelCount - 1)
            _effectsData.LeadingBall3 = 0;

        // Resetbedingung Ball4
        if (_effectsData.LeadingBall4 >= pixelCount - 1)
            _effectsData.LeadingBall4 = 0;

        effectsTimer = millis();
    }

    template <class TRmtMethod>
    void StripeInstance<TRmtMethod>::ballstackable()
    {
        if (!(millis() - _effectsData.effectsTimer >= _processingData.EffectDelay))
            return;

        auto pixelCount = _information.PixelCount;

        // Farbauswahl
        if (_processingData.Licht == Enums::ColorMode::OneUserColor)
            _effectsData.stackcolor = _processingData.LED_farbe_1;
        else if (_processingData.Licht == Enums::ColorMode::Random && _effectsData.LeadingBallStack == 0)
            _effectsData.stackcolor = Constants::Colors::GetRandomColor();
        else if (_processingData.Licht == Enums::ColorMode::Rainbow)
            _effectsData.stackcolor = Constants::Colors::Wheel(map(_effectsData.LeadingBallStack, 0, pixelCount - 1, 30, 150));

        // Löscht alle Farben
        Off(false);

        // Ball1 reinrollen lassen
        _effectsData.balllengh = (_effectsData.LeadingBallStack < _effectsData.balllengh_max) ? _effectsData.LeadingBallStack : _effectsData.balllengh_max;

        // Zeichnet 1. Ball
        for (int i = _effectsData.LeadingBallStack; i > _effectsData.LeadingBallStack - _effectsData.balllengh; i--)
            SetPixelColor(i, _effectsData.stackcolor);

        // Zeichnet stacked Ball
        for (int i = pixelCount; i > (pixelCount - _effectsData.BallOverFlowStack); i--)
            SetPixelColor(i, _effectsData.stackcolor);

        Show();

        // Speichert Ball Position und Rollover bei pixelCount und löscht Streifen
        if (_effectsData.LeadingBallStack < pixelCount - _effectsData.BallOverFlowStack)
            _effectsData.LeadingBallStack++;
        else
        {
            _effectsData.LeadingBallStack = 0;
            _effectsData.BallOverFlowStack += _effectsData.balllengh;

            if (_effectsData.BallOverFlowStack > pixelCount - _effectsData.balllengh)
                _effectsData.BallOverFlowStack = 0;

            // // Löscht alle Farben // TODO WEG?
            // Off();
        }

        _effectsData.effectsTimer = millis();
    } // namespace StripeBridge

    template <class TRmtMethod>
    void StripeInstance<TRmtMethod>::ballStackableToCenter()
    {
        if (!(millis() - _effectsData.effectsTimer >= _processingData.EffectDelay))
            return;

        auto pixelCount = _information.PixelCount;
        auto pixelCountHalf = _information.PixelCountTwoColors();

        // Farbauswahl
        if (_processingData.Licht == Enums::ColorMode::Random)
        {
            if (_effectsData.stackBallcentreleft == 0)
                _effectsData.stackcentrecolor_left = Constants::Colors::GetRandomColor();
            else if (_effectsData.stackBallcentreright == pixelCount - 1)
                _effectsData.stackcentrecolor_right = Constants::Colors::GetRandomColor();
        }
        else
        {
            _effectsData.stackcentrecolor_left = _processingData.LED_farbe_1;
            _effectsData.stackcentrecolor_right = (_processingData.Licht == Enums::ColorMode::TwoUserColors) ? _processingData.LED_farbe_2 : _processingData.LED_farbe_1;
        }

        // Löscht alle Farben
        Off(false);

        // Ball1 reinrollen lassen
        _effectsData.balllengh = (_effectsData.stackBallcentreleft < _effectsData.balllengh_max) ? _effectsData.stackBallcentreleft : _effectsData.balllengh_max;

        // BAll von links
        for (int i = _effectsData.stackBallcentreleft; i > _effectsData.stackBallcentreleft - _effectsData.balllengh; i--)
            SetPixelColor(i, _effectsData.stackcentrecolor_left);

        // Stackt ball left
        for (int i = pixelCountHalf; i > pixelCountHalf - _effectsData.BallOverFlowCentreleft; i--)
            SetPixelColor(i, _effectsData.stackcentrecolor_left);

        // BAll von rechts
        for (int i = _effectsData.stackBallcentreright; i > _effectsData.stackBallcentreright - _effectsData.balllengh; i--)
            SetPixelColor(i, _effectsData.stackcentrecolor_right);
        // Stackt ball rechts
        for (int i = pixelCountHalf; i < pixelCountHalf + _effectsData.BallOverFlowCentreleft; i++)
            SetPixelColor(i, _effectsData.stackcentrecolor_right);

        Show();

        // Händelt links position und stack
        if (_effectsData.stackBallcentreleft + _effectsData.balllengh < pixelCountHalf - _effectsData.BallOverFlowCentreleft)
            _effectsData.stackBallcentreleft++;
        else
        {
            _effectsData.stackBallcentreleft = 0;
            _effectsData.BallOverFlowCentreleft += _effectsData.balllengh;

            if (_effectsData.BallOverFlowCentreleft > pixelCountHalf - _effectsData.balllengh)
                _effectsData.BallOverFlowCentreleft = 0;
        }

        // Händelt rechts position und stack
        if (_effectsData.stackBallcentreright - _effectsData.balllengh > pixelCountHalf + _effectsData.BallOverFlowCentreright)
            _effectsData.stackBallcentreright--;
        else
        {
            _effectsData.stackBallcentreright = pixelCount;
            _effectsData.BallOverFlowCentreright += _effectsData.balllengh;

            if (_effectsData.BallOverFlowCentreright > pixelCountHalf - _effectsData.balllengh)
                _effectsData.BallOverFlowCentreright = 0;
        }

        _effectsData.effectsTimer = millis();
    }

    template <class TRmtMethod>
    void StripeInstance<TRmtMethod>::vu_centre()
    {
        if (!(millis() - _effectsData.effectsTimer >= _processingData.EffectDelay))
            return;

        float scale = 0.0;
        uint8_t i;
        uint16_t minLvl, maxLvl;
        int height;
        float n = 0;
        int value = 0;
        RgbColor color;

        int mic = check_micro(!_processingData.IsAux);

        if (!_processingData.IsAux)
            Constants::DC_OFFSET = 474; // Offset für Micro
        else
            Constants::DC_OFFSET = 440; // Offset für AUX

        //Serial.print("mic = ");Serial.print(mic);Serial.print(" n= ");
        scale = _processingData.Intensity / 100.0;
        n = abs(mic - Constants::DC_OFFSET);
        n = n * scale;
        value = (int)n;
        //Serial.println(n);
        _effectsData.lvlJeStripe = ((_effectsData.lvlJeStripe * 7) + value) >> 3;

        auto pixelCount = _information.PixelCount;
        auto pixelCountHalf = _information.PixelCountTwoColors();
        auto pixelCountTop = _information.PixelCountTop();

        // Calculate bar height based on dynamic min/max levels (fixed point):
        height = pixelCount * (_effectsData.lvlJeStripe - _effectsData.minLvlAvgJeStripe) / (long)(_effectsData.maxLvlAvgJeStripe - _effectsData.minLvlAvgJeStripe);
        if (height < 0L)
            height = 0; // Clip output
        else if (height > pixelCount)
            height = pixelCount;
        if (height > _effectsData.peakJeStripe)
            _effectsData.peakJeStripe = height; // Keep 'peak' dot at top

        // Farbauswahl // Radom macht kein Sinn
        if (_processingData.Licht == Enums::ColorMode::UserColors)
            color = _processingData.LED_farbe_1;

        // Color pixels based on rainbow gradient
        for (i = 0; i < pixelCountHalf; i++)
        {
            if (i >= height)
            {
                SetPixelColor(pixelCountHalf - i - 1, Constants::Colors::Off);
                SetPixelColor(pixelCountHalf + i, Constants::Colors::Off);
            }
            else
            {
                if (_processingData.Licht == Enums::ColorMode::Rainbow)
                    color = Constants::Colors::Wheel(map(i, 0, pixelCountHalf - 1, 30, 150));
                SetPixelColor(pixelCountHalf - i - 1, color);
                SetPixelColor(pixelCountHalf + i, color);
            }
        }

        // Draw peak dot
        if (_effectsData.peakJeStripe > 0 && _effectsData.peakJeStripe <= pixelCount - 1)
        {
            RgbColor color_peak = Constants::Colors::Wheel(map(_effectsData.peakJeStripe, 0, pixelCountHalf - 1, 30, 150));
            SetPixelColor(pixelCountHalf - _effectsData.peakJeStripe - 1, color_peak);
            SetPixelColor(pixelCountHalf + _effectsData.peakJeStripe, color_peak);
        }

        Show(); // Update strip

        // Every few frames, make the peak pixel drop by 1:
        if (++_effectsData.dotcountJeStripe >= Constants::PEAK_FALL)
        { //fall rate
            if (_effectsData.peakJeStripe > 0)
                _effectsData.peakJeStripe--;
            _effectsData.dotcountJeStripe = 0;
        }

        _effectsData.volJeStripe[_effectsData.volCountJeStripe] = n; // Save sample for dynamic leveling
        if (++_effectsData.volCountJeStripe >= Constants::SAMPLES)
            _effectsData.volCountJeStripe = 0; // Advance/rollover sample counter

        // Get volume range of prior frames
        minLvl = maxLvl = _effectsData.volJeStripe[0];
        for (i = 1; i < Constants::SAMPLES; i++)
        {
            if (_effectsData.volJeStripe[i] < minLvl)
                minLvl = _effectsData.volJeStripe[i];
            else if (_effectsData.volJeStripe[i] > maxLvl)
                maxLvl = _effectsData.volJeStripe[i];
        }

        if ((maxLvl - minLvl) < pixelCountTop)
            maxLvl = minLvl + pixelCountTop;
        _effectsData.minLvlAvgJeStripe = (_effectsData.minLvlAvgJeStripe * 63 + minLvl) >> 6;
        _effectsData.maxLvlAvgJeStripe = (_effectsData.maxLvlAvgJeStripe * 63 + maxLvl) >> 6;

        _effectsData.effectsTimer = millis();
    }

    template <class TRmtMethod>
    void StripeInstance<TRmtMethod>::vunormal()
    {
        if (!(millis() - _effectsData.effectsTimer >= _processingData.EffectDelay))
            return;

        auto pixelCount = _information.PixelCount;
        auto pixelCountHalf = _information.PixelCountTwoColors();
        auto pixelCountTop = _information.PixelCountTop();

        float scale = 0.0;
        uint8_t i;
        uint16_t minLvl, maxLvl;
        int height;
        float n = 0;
        int value = 0;
        RgbColor color;

        int mic = check_micro(!_processingData.IsAux);

        if (!_processingData.IsAux)
            Constants::DC_OFFSET = 474; // Offset für Micro
        else
            Constants::DC_OFFSET = 440; // Offset für AUX

        scale = _processingData.Intensity / 100.0;
        n = abs(mic - Constants::DC_OFFSET);
        n = n * scale;
        value = (int)n;

        _effectsData.lvlJeStripe = ((_effectsData.lvlJeStripe * 7) + value) >> 3;

        int nenner = (long)(_effectsData.maxLvlAvgJeStripe - _effectsData.minLvlAvgJeStripe);
        int zaehler = pixelCount * (_effectsData.lvlJeStripe - _effectsData.minLvlAvgJeStripe);
        // Calculate bar height based on dynamic min/max levels (fixed point):
        height = zaehler / nenner;

        if (height < 0L)
            height = 0; // Clip output
        else if (height > pixelCount)
            height = pixelCount;
        if (height > _effectsData.peakJeStripe)
            _effectsData.peakJeStripe = height; // Keep 'peak' dot at top

        if (_processingData.Licht == Constants::ColorMode::UserColors)
        {
            color = _processingData.LED_farbe_1;
        }
        if (_processingData.Licht == Constants::ColorMode::Random)
        {
            color = Constants::Colors::GetRandomColor();
        }

        // Color pixels based on rainbow gradient
        for (i = 0; i < pixelCount; i++)
        {
            if (i >= height)
            {
                SetPixelColor(i, RgbColor(0, 0, 0));
            }
            else
            {
                if (_processingData.Licht == Constants::ColorMode::Rainbow)
                {
                    color = Constants::Colors::Wheel(map(i, 0, pixelCount - 1, 30, 150));
                }
                SetPixelColor(i, color);
            }
        }

        // Draw peak dot
        if (_effectsData.peakJeStripe > 0 && _effectsData.peakJeStripe <= pixelCount - 1)
        {
            RgbColor color_peak = Constants::Colors::Wheel(map(_effectsData.peakJeStripe, 0, pixelCount - 1, 30, 150));
            SetPixelColor(_effectsData.peakJeStripe, color_peak);
        }

        Show(); // Update strip

        // Every few frames, make the peak pixel drop by 1:
        if (++_effectsData.dotcountJeStripe >= Constants::PEAK_FALL)
        { //fall rate

            if (_effectsData.peakJeStripe > 0)
                _effectsData.peakJeStripe--;
            _effectsData.dotcountJeStripe = 0;
        }

        _effectsData.volJeStripe[_effectsData.volCountJeStripe] = n; // Save sample for dynamic leveling
        if (++_effectsData.volCountJeStripe >= Constants::SAMPLES)
            _effectsData.volCountJeStripe = 0; // Advance/rollover sample counter

        // Get volume range of prior frames
        minLvl = maxLvl = _effectsData.volJeStripe[0];
        for (i = 1; i < Constants::SAMPLES; i++)
        {
            if (_effectsData.volJeStripe[i] < minLvl)
                minLvl = _effectsData.volJeStripe[i];
            else if (_effectsData.volJeStripe[i] > maxLvl)
                maxLvl = _effectsData.volJeStripe[i];
        }

        if ((maxLvl - minLvl) < pixelCountTop)
            maxLvl = minLvl + pixelCountTop;
        _effectsData.minLvlAvgJeStripe = (_effectsData.minLvlAvgJeStripe * 63 + minLvl) >> 6;
        _effectsData.maxLvlAvgJeStripe = (_effectsData.maxLvlAvgJeStripe * 63 + maxLvl) >> 6;

        _effectsData.effectsTimer = millis();
    }

    template <class TRmtMethod>
    void StripeInstance<TRmtMethod>::lavalampemove()
    {
        if (!(millis() - _effectsData.effectsTimer >= _processingData.EffectDelay))
            return;

        auto pixelCount = _information.PixelCount;
        auto pixelCountHalf = _information.PixelCountTwoColors();
        auto pixelCountTop = _information.PixelCountTop();
        // Farbauswahl
        if (_processingData.Licht == Constants::ColorMode::UserColors)
        {
            _effectsData.lavacolor_hoch = _processingData.LED_farbe_1;
            _effectsData.lavacolor_runter = _processingData.LED_farbe_2;
        }
        if (_processingData.Licht == Constants::ColorMode::Random)
        {
            if (_effectsData.lavaLampPositon == 0)
                _effectsData.lavacolor_hoch = Constants::Colors::GetRandomColor();
            if (_effectsData.lavaLampPositon == pixelCount - 1)
                _effectsData.lavacolor_runter = Constants::Colors::GetRandomColor();
        }
        if (_processingData.Licht == Constants::ColorMode::Rainbow)
        {
            _effectsData.lavacolor_hoch = Constants::Colors::Wheel(map(_effectsData.lavaLampPositon, 0, pixelCount - 1, 30, 150));
            ;
            _effectsData.lavacolor_runter = Constants::Colors::Wheel(map(pixelCount - _effectsData.lavaLampPositon, 0, pixelCount - 1, 30, 150));
            ;
        }

        // Zeichet Streifen je nach Richtung
        if (_effectsData.RichtungLavalampe == 0)
        {
            SetPixelColor(_effectsData.lavaLampPositon, _effectsData.lavacolor_hoch);

            Show();
            _effectsData.lavaLampPositon++;
            if (_effectsData.lavaLampPositon >= pixelCount)
            {
                _effectsData.RichtungLavalampe = 1;
                _effectsData.lavaLampPositon = pixelCount;
            }
        }
        else
        {
            SetPixelColor(_effectsData.lavaLampPositon, _effectsData.lavacolor_runter);

            Show();
            _effectsData.lavaLampPositon--;
            if (_effectsData.lavaLampPositon <= 0)
            {
                _effectsData.RichtungLavalampe = 0;
                _effectsData.lavaLampPositon = 0;
            }
        }

        Show();
        _effectsData.effectsTimer = millis();
    }

    template <class TRmtMethod>
    void StripeInstance<TRmtMethod>::movingRainbow()
    {
        auto pixelCount = _information.PixelCount;
        auto pixelCountHalf = _information.PixelCountTwoColors();
        auto pixelCountTop = _information.PixelCountTop();

        if (!(millis() - _effectsData.effectsTimer >= _processingData.EffectDelay))
            return;

        for (int i = 0; i < pixelCount; i++)
        {
            RgbColor color = Constants::Colors::Wheel(map(i, 0, pixelCount - 1, 30, 150));
            SetPixelColor(((i + _effectsData.mRainbowStep) % pixelCount), color);
        }

        Show();

        // updatet Position nach aufruf
        _effectsData.mRainbowStep++;
        if (_effectsData.mRainbowStep > pixelCount)
            _effectsData.mRainbowStep = 0;

        _effectsData.effectsTimer = millis();
    }

    template <class TRmtMethod>
    void StripeInstance<TRmtMethod>::fillup()
    {
        auto pixelCount = _information.PixelCount;
        auto pixelCountHalf = _information.PixelCountTwoColors();
        auto pixelCountTop = _information.PixelCountTop();

        if (!(millis() - _effectsData.effectsTimer >= _processingData.EffectDelay))
            return;
        RgbColor color;

        // Farbauswahl
        if (_processingData.Licht == ColorMode::UserColors)
        {
            color = _processingData.LED_farbe_1;
        }
        if (_processingData.Licht == ColorMode::Random && _effectsData.fillupstep == 0)
        {
            color = Constants::Colors::GetRandomColor();
        }
        if (_processingData.Licht == ColorMode::Rainbow)
        {
            color = Constants::Colors::Wheel(map(_effectsData.fillupstep, 0, pixelCount - 1, 30, 150));
            ;
        }

        // Zeichnet Streifen
        if (_effectsData.durchlauffillup)
        {
            SetPixelColor(_effectsData.fillupstep, color);
        }
        else
        {
            SetPixelColor(_effectsData.fillupstep, RgbColor(0, 0, 0));
        }

        Show();

        // updatet Position nach aufruf
        _effectsData.fillupstep++;
        if (_effectsData.fillupstep > pixelCount)
        {
            _effectsData.fillupstep = 0;
            _effectsData.durchlauffillup = _effectsData.durchlauffillup ^ 1;
        }
        _effectsData.effectsTimer = millis();
    }

    template <class TRmtMethod>
    void StripeInstance<TRmtMethod>::fillup2()
    {
        auto pixelCount = _information.PixelCount;
        auto pixelCountHalf = _information.PixelCountTwoColors();
        auto pixelCountTop = _information.PixelCountTop();

        if (!(millis() - _effectsData.effectsTimer >= _processingData.EffectDelay))
            return;

        // Farbauswahl
        if (_processingData.Licht == ColorMode::UserColors)
        {
            _effectsData.fullup2color = _processingData.LED_farbe_1;
            _effectsData.fullup2color2 = _processingData.LED_farbe_2;
        }

        if (_processingData.Licht == ColorMode::Random && _effectsData.fillup2step == 0)
        {
            _effectsData.fullup2color = Constants::Colors::GetRandomColor();
            _effectsData.fullup2color2 = Constants::Colors::GetRandomColor();
        }

        if (_processingData.Licht == ColorMode::Rainbow)
        {
            _effectsData.fullup2color = Constants::Colors::Wheel(map(_effectsData.fillup2step, 0, pixelCountHalf - 1, 30, 150));
            ;
            _effectsData.fullup2color2 = _effectsData.fullup2color;
        }

        // Zeichnet Streifen
        if (_effectsData.durchlauffillup2)
        {
            SetPixelColor(_effectsData.fillup2step, _effectsData.fullup2color);
            SetPixelColor(_effectsData.fillup2step + pixelCountHalf, _effectsData.fullup2color2);
        }
        else
        {
            RgbColor color = RgbColor(0, 0, 0);
            SetPixelColor(_effectsData.fillup2step, color);
            SetPixelColor(_effectsData.fillup2step + pixelCountHalf, color);
        }

        Show();

        // updatet Position nach aufruf
        _effectsData.fillup2step++;
        if (_effectsData.fillup2step > pixelCountHalf)
        {
            _effectsData.fillup2step = 0;
            _effectsData.durchlauffillup2 = _effectsData.durchlauffillup2 ^ 1;
        }

        _effectsData.effectsTimer = millis();
    }

    template <class TRmtMethod>
    void StripeInstance<TRmtMethod>::fillup3()
    {
        auto pixelCount = _information.PixelCount;
        auto pixelCountHalf = _information.PixelCountTwoColors();
        auto pixelCountTop = _information.PixelCountTop();

        int drittel = std::ceil(pixelCount / 3);
        int zweidrittel = std::ceil(pixelCount * 2 / 3);

        if (!(millis() - _effectsData.effectsTimer >= _processingData.EffectDelay))
            return;

        int einviertel = pixelCount / 4;
        int halb = pixelCountHalf;
        int dreiviertel = pixelCount * 3 / 4;
        int voll = pixelCount;

        // Farbauswahl
        if (_processingData.Licht == ColorMode::UserColors)
        {
            _effectsData.fullup3color = _processingData.LED_farbe_1;
            _effectsData.fullup3color2 = _processingData.LED_farbe_2;
            _effectsData.fullup3color3 = _processingData.LED_farbe_3;
        }
        if (_processingData.Licht == ColorMode::Random && _effectsData.fillup3step == 0)
        {
            _effectsData.fullup3color = Constants::Colors::GetRandomColor();
            _effectsData.fullup3color2 = Constants::Colors::GetRandomColor();
            _effectsData.fullup3color3 = Constants::Colors::GetRandomColor();
        }
        if (_processingData.Licht == ColorMode::Rainbow)
        {
            _effectsData.fullup3color = Constants::Colors::Wheel(map(_effectsData.fillup3step, 0, (pixelCount - 1) / 4, 30, 150));
            ;
            _effectsData.fullup3color2 = _effectsData.fullup3color;
            _effectsData.fullup3color3 = _effectsData.fullup3color;
        }

        // Zeichnet Streifen
        if (_effectsData.durchlauffillup3 == false)
        {
            SetPixelColor(_effectsData.fillup3step, _effectsData.fullup3color);
            SetPixelColor(_effectsData.fillup3step + drittel, _effectsData.fullup3color2);
            SetPixelColor(_effectsData.fillup3step + zweidrittel, _effectsData.fullup3color3);
        }
        else
        {
            RgbColor color = RgbColor(0, 0, 0);
            SetPixelColor(_effectsData.fillup3step, color);
            SetPixelColor(_effectsData.fillup3step + drittel, color);
            SetPixelColor(_effectsData.fillup3step + zweidrittel, color);
        }

        Show();

        // updatet Position nach aufruf
        _effectsData.fillup3step++;
        if (_effectsData.fillup3step > pixelCount / 3)
        {
            _effectsData.fillup3step = 0;
            _effectsData.durchlauffillup3 = _effectsData.durchlauffillup3 ^ 1;
        }

        _effectsData.effectsTimer = millis();
    }

    template <class TRmtMethod>
    void StripeInstance<TRmtMethod>::fillup4()
    {
        auto pixelCount = _information.PixelCount;
        auto pixelCountHalf = _information.PixelCountTwoColors();
        auto pixelCountTop = _information.PixelCountTop();

        auto ntime = millis();
        if (ntime - _effectsData.effectsTimer >= _processingData.EffectDelay)
        {

            int einviertel = pixelCount / 4;
            int halb = pixelCount / 2;
            int dreiviertel = pixelCount * 3 / 4;
            int voll = pixelCount;

            Serial.println(_effectsData.fillup4step);

            // Farbauswahl
            if (_processingData.Licht == ColorMode::UserColors)
            {
                _effectsData.fullup4color = _processingData.LED_farbe_1;
                _effectsData.fullup4color2 = _processingData.LED_farbe_2;
                _effectsData.fullup4color3 = _processingData.LED_farbe_3;
                _effectsData.fullup4color4 = _processingData.LED_farbe_4;
            }

            if (_processingData.Licht == ColorMode::Random && _effectsData.fillup4step == 0)
            {
                _effectsData.fullup4color = Constants::Colors::GetRandomColor();
                _effectsData.fullup4color2 = Constants::Colors::GetRandomColor();
                _effectsData.fullup4color3 = Constants::Colors::GetRandomColor();
                _effectsData.fullup4color4 = Constants::Colors::GetRandomColor();
            }

            if (_processingData.Licht == ColorMode::Rainbow)
            {
                _effectsData.fullup4color = Constants::Colors::Wheel(map(_effectsData.fillup4step, 0, (pixelCount - 1) / 4, 30, 150));
                ;
                _effectsData.fullup4color2 = _effectsData.fullup4color;
                _effectsData.fullup4color3 = _effectsData.fullup4color;
                _effectsData.fullup4color4 = _effectsData.fullup4color;
            }

            // Zeichnet Streifen
            if (_effectsData.durchlauffillup4 == false)
            {
                SetPixelColor(_effectsData.fillup4step, _effectsData.fullup4color);
                SetPixelColor(_effectsData.fillup4step + einviertel, _effectsData.fullup4color2);
                SetPixelColor(_effectsData.fillup4step + halb, _effectsData.fullup4color3);
                SetPixelColor(_effectsData.fillup4step + dreiviertel, _effectsData.fullup4color4);
            }
            else
            {
                RgbColor color = RgbColor(0, 0, 0);
                SetPixelColor(_effectsData.fillup4step, color);
                SetPixelColor(_effectsData.fillup4step + einviertel, color);
                SetPixelColor(_effectsData.fillup4step + halb, color);
                SetPixelColor(_effectsData.fillup4step + dreiviertel, color);
            }

            Show();

            // updatet Position nach aufruf
            _effectsData.fillup4step++;
            if (_effectsData.fillup4step > pixelCount / 4)
            {
                _effectsData.fillup4step = 0;
                _effectsData.durchlauffillup4 = _effectsData.durchlauffillup4 ^ 1;
            }

            _effectsData.effectsTimer = ntime;
        }
    }

} // namespace StripeBridge

template class StripeBridge::StripeInstance<NeoEsp32RmtMethodBase<NeoEsp32RmtSpeed800Kbps, NeoEsp32RmtChannel0>>;
template class StripeBridge::StripeInstance<NeoEsp32RmtMethodBase<NeoEsp32RmtSpeed800Kbps, NeoEsp32RmtChannel1>>;

// TODO: Replace
// pixelCount = pixelCount
// pixelCountHalf = pixelCountHalf
// pixelCountTop =

// TODO:
// inline void prozzesFFT(void)
// {
// 	// Fertig
// 	if (micros() - Constants::oldtime >= Constants::samplingDelay)
// 	{

// 		//Channel Auswahl
// 		(p_strip1.IsAux) ? CHANNEL = AUX_Eingang : CHANNEL = MicroEingang;
// 		(p_strip2.IsAux) ? CHANNEL = AUX_Eingang : CHANNEL = MicroEingang;

// 		// Ließt Analogwert ins Array
// 		vReal[idex] = analogRead(CHANNEL);
// 		vImag[idex] = 0;

// 		// nach einlesen Update Index
// 		idex++;
// 		if (idex > samples_fft)
// 		{
// 			idex = 0;  // Index wird zurückgesetzt
// 			isRdy = 1; // Zeigt an das genug Samples für FFT Berechnung vorhanden sind
// 		}

// 		oldtime = micros();
// 	}

// 	if (isRdy)
// 	{
// 		FFT.Windowing(vReal, samples_fft, FFT_WIN_TYP_HAMMING, FFT_FORWARD); /* Weigh data */
// 		FFT.Compute(vReal, vImag, samples_fft, FFT_FORWARD);				 /* Compute FFT */
// 		FFT.ComplexToMagnitude(vReal, vImag, samples_fft);					 /* Compute magnitudes */
// 		double x = FFT.MajorPeak(vReal, samples_fft, samplingFrequency);	 // Gibt Frequenz mit höhster Amplitude zurück
// 		x = (int)x;
// 		if (x > maxfreq)
// 			x = maxfreq;
// 		int S1delay = map(x, 0, maxfreq, delaxMin, delayMax); // Skalliert Effectdelay jeh dominierende Frequenz
// 		int S2delay = map(x, 0, maxfreq, delaxMin, delayMax); // Skalliert Effectdelay jeh dominierende Frequenz
// 		p_strip1.EffectDelay = S1delay;						  // Schreibt neuen Delaywert
// 		p_strip2.EffectDelay = S2delay;						  // Schreibt neuen Delaywert
// 		isRdy = 0;
// 	}
// }
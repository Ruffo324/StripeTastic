#pragma once

namespace StripeBridge
{
    // TODO: Sort all constants.
    namespace Constants
    {
        // Defines für Musik
        const int SAMPLES = 20;   // für min/max Berechnung Musik
        const int PEAK_FALL = 15; // Gibt geschwindigkeit vom DotFall vor  // könnte man in der UI im Setup einstellbar machen

        // Defines für FFT
        const int SCL_INDEX = 0x00;
        const int SCL_TIME = 0x01;
        const int SCL_FREQUENCY = 0x02;
        const int SCL_PLOT = 0x03;

        // Variablen für FFT
        const int samples_fft = 128;           //This value MUST ALWAYS be a power of 2
        const double samplingFrequency = 1000; // Hz, must be less than 10000 due to ADC  ACHTUNG BEI ÄNDERUNG MUSS Sampledelay angepasst werden
        const long samplingDelay = 1000;       // Zeit in µS          1000 -> 1ms -> 1kHz

        static double vReal[samples_fft]; // Speichert Real Anteil
        static double vImag[samples_fft]; // Speichert Imag Anteil  z = vReal + vImag
        static bool isRdy = 0;            // Zeigt an wenn Samplephase fertig ist
        static unsigned long oldtime = 0; // Speichert alte Sampezeit
        static int idex = 0;              // Speichert sich Index beim Samplen

        // // könnte man in der UI im Setup einstellbar machen
        static int maxfreq = 400; // gibt MaxFreq der FFT Auswertung
        static int delayMax = 25; // Maximale Verzögerung
        static int delaxMin = 1;  // Minimale Verzögerung

        static int CHANNEL = 34;    // Channel für FFT - Defult MircoEingang
        static int DC_OFFSET = 447; // Offset für Miro bzw Aux -> bedeutet 0 da zum positiven und "negativen" Ausgelenkt werden muss

    } // namespace Constants
} // namespace StripeBridge
// TODO: Create enum models for the effects and more..
export interface IStripeProcessingData {
    OperationMode: number;//": 0,
    Effect: number;//": 7,
    EffectDirection: number;//": 0,
    Licht: number;//": 4,
    Brightness: number;//": 255,
    FlashPerSeconds: number;//": 50,
    EffectDelay: number;//": 10,
    Intensity: number;//": 100.0,
    FFTActive: boolean;//": false,
    Changed: boolean;//": true, /*TODO: REMOVE*/
    IsAux: boolean;//": true,
    LED_farbe_1: ILedColor;//": { red: 255, green: 0, blue: 0 },
    LED_farbe_2: ILedColor;//": { red: 0, green: 255, blue: 0 },
    LED_farbe_3: ILedColor;//": { red: 0, green: 0, blue: 255 },
    LED_farbe_4: ILedColor;//": { red: 255, green: 0, blue: 255 }
}

/** Color for an LED. **/
export interface ILedColor {
    Red: number;
    Green: number;
    Blue: number;
}
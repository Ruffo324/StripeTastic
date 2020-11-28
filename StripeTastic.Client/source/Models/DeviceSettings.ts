/**
 * Stores and modifies the current known device settings.
 */
export interface IDeviceSettings {
    ConnectionMode: ConnectionMode;
    AdHoc: IWiFiSettings;
    Router: IWiFiSettings;

    StripeOne: IStripeSettings;
    StripeTwo: IStripeSettings;

    AudioSource: AudioSource;
}

export interface IWiFiSettings {
    Ssid: string;
    Password: string;
    Channel: number;
}

export interface IStripeSettings {
    PixelCount: number;
}

export enum ConnectionMode {
    AdHoc = 0,
    Router = 1,
    Both = 2,
}

export enum AudioSource {
    AuxInput = 0,
    Microphone = 1,
    NetzworkStream = 2,
}

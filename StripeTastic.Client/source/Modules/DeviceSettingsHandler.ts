import { EventNames } from "../Constants/EventNames";
import { IDeviceSettings } from "../Models/IDeviceSettings";
import { AlertProvider } from "./AlertProvider";
import { Communication } from "./Communication";

export module DeviceSettingsHandler {
    export var DeviceSettings: IDeviceSettings;

    export function RequestDeviceSettings(): void {
        Communication.SendRequest(EventNames.RequestDeviceSettings);
    }

    export function Initialize() {
        Communication.AddListener<IDeviceSettings>(EventNames.RequestDeviceSettings, (data) => DeviceSettings = data);
        AlertProvider.Debug(`DeviceSettingsHandler initialized.`);
    }

    /**
        Settings form dom id's:
        #container-device-settings
        #device-settings-connection-mode


        .wifi-settings-card
        #card-wifi-settings-adhoc
            .device-settings-adhoc-ssid
            .device-settings-adhoc-password
            .device-settings-adhoc-channel
            
        #card-wifi-settings-router
            .device-settings-router-ssid
            .device-settings-router-password
            .device-settings-router-channel
    */
}

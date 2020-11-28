import { EventNames } from "../Constants/EventNames";
import { IDeviceSettings } from "../Models/DeviceSettings";
import { AlertProvider } from "./AlertProvider";
import { DeviceCommunicator } from "./DeviceCommunicator";

export module DeviceSettingsHandler {
    export var DeviceSettings: IDeviceSettings;

    export function RequestDeviceSettings(): void {
        DeviceCommunicator.SendRequest(EventNames.DeviceSettings);
    }

    export function Initialize() {
        DeviceCommunicator.AddListener<IDeviceSettings>(EventNames.DeviceSettings, (data) => DeviceSettings = data);
        AlertProvider.Debug(`DeviceSettingsHandler initialized.`);
    }
}

import { NavigationModule } from "./Modules/NavigationModule";
import { ServerEventListener } from "./Modules/ServerEventListener";
import { DeviceSettingsHandler } from "./Modules/DeviceSettingsHandler";

// Load, Bind and setup all required modules.
$(() => {
    NavigationModule.Bind();
    ServerEventListener.Listen();

    DeviceSettingsHandler.RequestDeviceSettings();
});
import { NavigationModule } from "./Modules/NavigationModule";
import { ServerEventListener } from "./Modules/ServerEventListener";
import { DeviceSettingsHandler } from "./Modules/DeviceSettingsHandler";
import { AlertHandler } from "./Modules/AlertHandler";

// Load, Bind and setup all required modules.
$(() => {

    setInterval(() => AlertHandler.Danger("test"), 3000);
    NavigationModule.Bind();
    ServerEventListener.Listen();

    DeviceSettingsHandler.RequestDeviceSettings();
});
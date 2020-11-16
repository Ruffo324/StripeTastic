import { NavigationModule } from "./Modules/NavigationModule";
import { ServerEventListener } from "./Modules/ServerEventListener";
import { DeviceSettingsHandler } from "./Modules/DeviceSettingsHandler";
import { AlertHandler } from "./Modules/AlertHandler";

// Load, Bind and setup all required modules.
$(() => {
    setInterval(function alertTestFunc() {
        const maxWaitMs = 15 * 1000;
        setTimeout(() => AlertHandler.Primary(Date.now().toLocaleString()), Math.random() * maxWaitMs);
        setTimeout(() => AlertHandler.Secondary(Date.now().toLocaleString()), Math.random() * maxWaitMs);
        setTimeout(() => AlertHandler.Success(Date.now().toLocaleString()), Math.random() * maxWaitMs);
        setTimeout(() => AlertHandler.Danger(Date.now().toLocaleString()), Math.random() * maxWaitMs);
        setTimeout(() => AlertHandler.Warning(Date.now().toLocaleString()), Math.random() * maxWaitMs);
        setTimeout(() => AlertHandler.Info(Date.now().toLocaleString()), Math.random() * maxWaitMs);
        setTimeout(() => AlertHandler.Light(Date.now().toLocaleString()), Math.random() * maxWaitMs);
        setTimeout(() => AlertHandler.Dark(Date.now().toLocaleString()), Math.random() * maxWaitMs);
        return alertTestFunc;
    }(), Math.random() * 60000); // Debug.


    NavigationModule.Bind();
    ServerEventListener.Listen();

    DeviceSettingsHandler.RequestDeviceSettings();
});
import { NavigationModule } from "./Modules/NavigationModule";
import { DeviceCommunicator } from "./Modules/DeviceCommunicator";
import { DeviceSettingsHandler } from "./Modules/DeviceSettingsHandler";
import { AlertProvider } from "./Modules/AlertProvider";

export module App {
    var invokeActions = [];
    var appStartedOnce = false;

    export function InjectAppStart(invokeAction: Function): void {
        invokeActions.push(invokeAction)
    }

    export function AppStart(): void {
        if (appStartedOnce) {
            AlertProvider.Danger("AppStart is only allowed to be called once!");
            throw new Error("AppStart is only allowed to be called once!");
        }
        appStartedOnce = true;
        invokeActions.forEach(a => a());
    }
}

// Load, Bind and setup all required modules.
$(() => {
    App.AppStart();
    //     NavigationModule.Bind();
    // DeviceCommunicator.Listen();

    // DeviceSettingsHandler.RequestDeviceSettings();
});
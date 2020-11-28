import { AlertProvider } from "./Modules/AlertProvider";
import { NavigationModule } from "./Modules/NavigationModule";
import { Communication } from "./Modules/Communication";
import { DeviceSettingsHandler } from "./Modules/DeviceSettingsHandler";

export module App {
    export const Debug: boolean = true;
    const invokeActions = [];
    let appStartedOnce = false;

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


App.InjectAppStart(() => NavigationModule.Initialize());
App.InjectAppStart(() => Communication.Initialize());
App.InjectAppStart(() => DeviceSettingsHandler.Initialize());


// Load, Bind and setup all required modules.
$(() => App.AppStart());

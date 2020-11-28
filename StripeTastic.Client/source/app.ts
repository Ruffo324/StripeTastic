import {AlertProvider} from "./Modules/AlertProvider";
import {NavigationModule} from "./Modules/NavigationModule";
import {DeviceCommunicator} from "./Modules/DeviceCommunicator";

export module App {
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
App.InjectAppStart(() => DeviceCommunicator.Initialize());


// Load, Bind and setup all required modules.
$(() => App.AppStart());

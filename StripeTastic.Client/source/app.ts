import { NavigationModule } from "./Modules/NavigationModule";
import { ServerEventListener } from "./Modules/ServerEventListener";

// Load and Bind all required modules.
$(() => {
    NavigationModule.Bind();
    ServerEventListener.Listen();
});
define("Modules/AlertProvider", ["require", "exports", "app"], function (require, exports, app_1) {
    "use strict";
    Object.defineProperty(exports, "__esModule", { value: true });
    exports.AlertProvider = void 0;
    var AlertProvider;
    (function (AlertProvider) {
        var alertCounter = 0;
        function innerAlert(type, message) {
            const showAlertFor = 10 * 1000;
            const destroyAfterMs = 5 * 1000;
            var alertId = `ah-alert-${alertCounter++}`;
            // Create alert element.
            $("#ah-container").append(`<div class="ah-alert ah-alert-${type}" id="${alertId}">${message}</div>`);
            let newAlert = $(`#${alertId}`);
            newAlert.toggleClass("visible");
            setTimeout(() => {
                newAlert.toggleClass("visible");
                setTimeout(() => {
                    newAlert.remove();
                }, destroyAfterMs);
            }, showAlertFor);
        }
        function Primary(message) {
            innerAlert("primary", message);
        }
        AlertProvider.Primary = Primary;
        function Secondary(message) {
            innerAlert("secondary", message);
        }
        AlertProvider.Secondary = Secondary;
        function Success(message) {
            innerAlert("success", message);
        }
        AlertProvider.Success = Success;
        function Danger(message) {
            innerAlert("danger", message);
        }
        AlertProvider.Danger = Danger;
        function Warning(message) {
            innerAlert("warning", message);
        }
        AlertProvider.Warning = Warning;
        function Info(message) {
            innerAlert("info", message);
        }
        AlertProvider.Info = Info;
        function Light(message) {
            innerAlert("light", message);
        }
        AlertProvider.Light = Light;
        function Dark(message) {
            innerAlert("dark", message);
        }
        AlertProvider.Dark = Dark;
        /** TODO: Disable in production. */
        function Debug(message) {
            if (app_1.App.Debug)
                innerAlert("debug", message);
        }
        AlertProvider.Debug = Debug;
    })(AlertProvider = exports.AlertProvider || (exports.AlertProvider = {}));
});
define("Utils/Utils", ["require", "exports"], function (require, exports) {
    "use strict";
    Object.defineProperty(exports, "__esModule", { value: true });
    exports.UrlManipulation = void 0;
    /**
     * Contains util function's for url manipulation.
     */
    var UrlManipulation;
    (function (UrlManipulation) {
        /**
         * Return the value of the url get parameter.
         * @param parameterName The name of the wanted get parameter.
         * @returns {string} The value of the get parameter or undefined.
         */
        function GetParameter(parameterName) {
            const getValues = {};
            location.search.substr(1).split("&").forEach(item => {
                getValues[item.split("=")[0]] = item.split("=")[1];
            });
            return getValues[parameterName];
        }
        UrlManipulation.GetParameter = GetParameter;
        /**
         * Sets the value for a get url parameter.
         * Leave value empty, to delete a get parameter.
         * @param parameterName Name of the get parameter.
         * @param value Value of the get parameter.
         */
        function SetGetParameter(parameterName, value) {
            const getValues = {};
            location.search.substr(1).split("&").forEach(item => {
                getValues[item.split("=")[0]] = item.split("=")[1];
            });
            getValues[parameterName] = [value];
            let newSearch = "";
            Object.keys(getValues).forEach((key) => {
                if (getValues.hasOwnProperty(key) && key !== "" && getValues[key] !== "") {
                    newSearch += `&${key}=${getValues[key]}`;
                }
            });
            if (newSearch.length > 0)
                newSearch = newSearch.substr(1);
            history.pushState({}, "", `?${newSearch}`);
        }
        UrlManipulation.SetGetParameter = SetGetParameter;
    })(UrlManipulation = exports.UrlManipulation || (exports.UrlManipulation = {}));
});
define("Modules/NavigationModule", ["require", "exports", "Utils/Utils", "app", "Modules/AlertProvider"], function (require, exports, Utils_1, app_2, AlertProvider_1) {
    "use strict";
    Object.defineProperty(exports, "__esModule", { value: true });
    exports.NavigationModule = void 0;
    var NavigationModule;
    (function (NavigationModule) {
        const defaultPage = "./pages/led-config.html";
        function Initialize() {
            $(".nav-link").on("click", (element) => {
                let clickedItem = $(element.target);
                let targetPage = clickedItem.data("page-file-name");
                loadPage(targetPage);
            });
            if (app_2.App.Debug)
                setInterval(() => LoadPageFromUrl(), 1000); // Debug
            LoadPageFromUrl(); // Load url by checking the current link.
            AlertProvider_1.AlertProvider.Debug(`NavigationModule - initialized.`);
        }
        NavigationModule.Initialize = Initialize;
        function LoadPageFromUrl() {
            const pageParameterValue = Utils_1.UrlManipulation.GetParameter("page");
            if (typeof pageParameterValue === "undefined")
                loadPage(defaultPage);
            else
                loadPage(pageParameterValue);
        }
        NavigationModule.LoadPageFromUrl = LoadPageFromUrl;
        function loadPage(pageFile) {
            Utils_1.UrlManipulation.SetGetParameter("page", pageFile);
            $("#container-page").load(pageFile);
            $(".nav-item").removeClass("active");
            $(`.nav-link[data-page-file-name="${pageFile}"]`).parent().addClass("active");
        }
    })(NavigationModule = exports.NavigationModule || (exports.NavigationModule = {}));
});
define("Constants/EventNames", ["require", "exports"], function (require, exports) {
    "use strict";
    Object.defineProperty(exports, "__esModule", { value: true });
    exports.EventNames = void 0;
    /**
     * The event names for the communication with the web client.
     * Ensure that the values are identical to "source\Constants\EventNames.h"!
     */
    var EventNames;
    (function (EventNames) {
        EventNames["RequestDeviceSettings"] = "RequestDeviceSettings";
        EventNames["UpdateDeviceSettings"] = "UpdateDeviceSettings";
        EventNames["RequestWiFiScan"] = "RequestWiFiScan";
    })(EventNames = exports.EventNames || (exports.EventNames = {}));
});
define("Modules/Communication", ["require", "exports", "Modules/AlertProvider"], function (require, exports, AlertProvider_2) {
    "use strict";
    Object.defineProperty(exports, "__esModule", { value: true });
    exports.Communication = void 0;
    var Communication;
    (function (Communication) {
        const _deviceEventSource = '/events';
        let _eventSource;
        function GetEventSource() {
            try {
                return (_eventSource !== null && _eventSource !== void 0 ? _eventSource : (_eventSource = new EventSource(_deviceEventSource)));
            }
            catch (error) {
                const message = "Unable to setup event source. Please use an up to date server!";
                AlertProvider_2.AlertProvider.Danger(message);
                throw new Error(message);
            }
        }
        function AddListener(eventName, eventCallback) {
            let eventSource = GetEventSource();
            eventSource.addEventListener(eventName, (e) => {
                try {
                    let eventData = JSON.parse(e.data);
                    eventCallback(eventData);
                    AlertProvider_2.AlertProvider.Debug(`DeviceCommunication - Event received: ${eventName}`);
                }
                catch (error) {
                    AlertProvider_2.AlertProvider.Danger(error);
                    console.error(error);
                }
            });
        }
        Communication.AddListener = AddListener;
        function SendRequest(eventName, data) {
            AlertProvider_2.AlertProvider.Debug(`DeviceCommunication - RequestSend: ${eventName}`);
            $.ajax({
                type: 'POST',
                url: eventName,
                dataType: 'json',
                contentType: 'application/json',
                processData: false,
                data: data !== null && data !== void 0 ? data : {},
                success: function (resp) {
                    console.log(resp);
                }
            });
        }
        Communication.SendRequest = SendRequest;
        function Initialize() {
            let eventSource = GetEventSource();
            eventSource.addEventListener('message', function (e) {
                AlertProvider_2.AlertProvider.Secondary(JSON.stringify(e));
            }, false);
            eventSource.addEventListener('open', function (_) {
                AlertProvider_2.AlertProvider.Info("Connection to device established.");
            }, false);
            eventSource.addEventListener('error', function (e) {
                if (this.readyState == EventSource.CLOSED) {
                    AlertProvider_2.AlertProvider.Warning("Connection closed!");
                    return;
                }
                AlertProvider_2.AlertProvider.Danger(e.message);
            }, false);
            AlertProvider_2.AlertProvider.Debug(`DeviceCommunicator initialized.`);
        }
        Communication.Initialize = Initialize;
    })(Communication = exports.Communication || (exports.Communication = {}));
});
define("Models/IDeviceSettings", ["require", "exports"], function (require, exports) {
    "use strict";
    Object.defineProperty(exports, "__esModule", { value: true });
    exports.AudioSource = exports.ConnectionMode = void 0;
    var ConnectionMode;
    (function (ConnectionMode) {
        ConnectionMode[ConnectionMode["AdHoc"] = 0] = "AdHoc";
        ConnectionMode[ConnectionMode["Router"] = 1] = "Router";
        ConnectionMode[ConnectionMode["Both"] = 2] = "Both";
    })(ConnectionMode = exports.ConnectionMode || (exports.ConnectionMode = {}));
    var AudioSource;
    (function (AudioSource) {
        AudioSource[AudioSource["AuxInput"] = 0] = "AuxInput";
        AudioSource[AudioSource["Microphone"] = 1] = "Microphone";
        AudioSource[AudioSource["NetzworkStream"] = 2] = "NetzworkStream";
    })(AudioSource = exports.AudioSource || (exports.AudioSource = {}));
});
define("Modules/DeviceSettingsHandler", ["require", "exports", "Constants/EventNames", "Modules/AlertProvider", "Modules/Communication"], function (require, exports, EventNames_1, AlertProvider_3, Communication_1) {
    "use strict";
    Object.defineProperty(exports, "__esModule", { value: true });
    exports.DeviceSettingsHandler = void 0;
    var DeviceSettingsHandler;
    (function (DeviceSettingsHandler) {
        function RequestDeviceSettings() {
            Communication_1.Communication.SendRequest(EventNames_1.EventNames.RequestDeviceSettings);
        }
        DeviceSettingsHandler.RequestDeviceSettings = RequestDeviceSettings;
        function Initialize() {
            Communication_1.Communication.AddListener(EventNames_1.EventNames.RequestDeviceSettings, (data) => DeviceSettingsHandler.DeviceSettings = data);
            AlertProvider_3.AlertProvider.Debug(`DeviceSettingsHandler initialized.`);
        }
        DeviceSettingsHandler.Initialize = Initialize;
        /**
            Settings form dom id's:
            #container-device-settings
            #device-settings-connection-mode
            .wifi-settings-card
        */
    })(DeviceSettingsHandler = exports.DeviceSettingsHandler || (exports.DeviceSettingsHandler = {}));
});
define("app", ["require", "exports", "Modules/AlertProvider", "Modules/NavigationModule", "Modules/Communication", "Modules/DeviceSettingsHandler"], function (require, exports, AlertProvider_4, NavigationModule_1, Communication_2, DeviceSettingsHandler_1) {
    "use strict";
    Object.defineProperty(exports, "__esModule", { value: true });
    exports.App = void 0;
    var App;
    (function (App) {
        App.Debug = true;
        const invokeActions = [];
        let appStartedOnce = false;
        function InjectAppStart(invokeAction) {
            invokeActions.push(invokeAction);
        }
        App.InjectAppStart = InjectAppStart;
        function AppStart() {
            if (appStartedOnce) {
                AlertProvider_4.AlertProvider.Danger("AppStart is only allowed to be called once!");
                throw new Error("AppStart is only allowed to be called once!");
            }
            appStartedOnce = true;
            invokeActions.forEach(a => a());
        }
        App.AppStart = AppStart;
    })(App = exports.App || (exports.App = {}));
    App.InjectAppStart(() => NavigationModule_1.NavigationModule.Initialize());
    App.InjectAppStart(() => Communication_2.Communication.Initialize());
    App.InjectAppStart(() => DeviceSettingsHandler_1.DeviceSettingsHandler.Initialize());
    // Load, Bind and setup all required modules.
    $(() => App.AppStart());
});
define("Models/IStripeProcessingData", ["require", "exports"], function (require, exports) {
    "use strict";
    Object.defineProperty(exports, "__esModule", { value: true });
});
define("Models/IWiFiScanResult", ["require", "exports"], function (require, exports) {
    "use strict";
    Object.defineProperty(exports, "__esModule", { value: true });
});
// TODO: Rewrite the commented code below..
/**

 // Prefill textareas..
 $("#stripe1").val(JSON.stringify(defaultProcessing, null, 2));
 $("#stripe2").val(JSON.stringify(defaultProcessing, null, 2));

 $("#updateStripe1").click(() => {
    let jsonStr = $("#stripe1").val();
    if (!IsJsonString(jsonStr)) {
        console.error("invalid data.");
        return;
    }
    simpleRestRequest("/processdata/stripe1", jsonStr);
    console.log("send");
});

 $("#updateStripe2").click(() => {
    let jsonStr = $("#stripe2").val();
    if (!IsJsonString(jsonStr)) {
        console.error("invalid data.");
        return;
    }
    simpleRestRequest("/processdata/stripe2", jsonStr);
    console.log("send");
});

 function IsJsonString(str) {
    try {
        var json = JSON.parse(str);
        return (typeof json === 'object');
    } catch (e) {
        return false;
    }
}

 // function changeStroboSpeed(speed) {
//     simpleRestRequest("/effects/strobe/speed", JSON.stringify({ 'speed': speed }));
//     $("#value-strobo-speed").html(`${speed}/s`);
// }

 // function changeColor(colorHex) {
//     let rgbColor = hexToRgb(colorHex);
//     simpleRestRequest("/effects/color", JSON.stringify({ 'red': rgbColor.red, 'green': rgbColor.green, 'blue': rgbColor.blue }));
// }
 // function strobeOnOff() {
//     simpleRestRequest("/effects/strobe/on", JSON.stringify({ 'on': $('#strobo-on-off').is(":checked") }));
// }

 function simpleRestRequest(path, data) {
}

 function hexToRgb(hex) {
    var result = /^#?([a-f\d]{2})([a-f\d]{2})([a-f\d]{2})$/i.exec(hex);
    return result ? {
        red: parseInt(result[1], 16),
        green: parseInt(result[2], 16),
        blue: parseInt(result[3], 16)
    } : null;
}
 */
define("Utils/Cookies", ["require", "exports"], function (require, exports) {
    "use strict";
    Object.defineProperty(exports, "__esModule", { value: true });
    exports.Cookies = void 0;
    var Cookies;
    (function (Cookies) {
        function Set(name, value, days) {
            let expires = "";
            if (days) {
                const date = new Date();
                date.setTime(date.getTime() + (days * 24 * 60 * 60 * 1000));
                expires = `; expires=${date.toUTCString()}`;
            }
            document.cookie = name + "=" + (value || "") + expires + "; path=/";
        }
        Cookies.Set = Set;
        function Get(name) {
            const nameEq = name + "=";
            const ca = document.cookie.split(";");
            for (let i = 0; i < ca.length; i++) {
                let c = ca[i];
                while (c.charAt(0) === " ")
                    c = c.substring(1, c.length);
                if (c.indexOf(nameEq) === 0)
                    return c.substring(nameEq.length, c.length);
            }
            return null;
        }
        Cookies.Get = Get;
        function Erase(name) {
            if (Get(name) === null)
                return false;
            document.cookie = name + "=; Max-Age=-99999999;";
            return true;
        }
        Cookies.Erase = Erase;
    })(Cookies = exports.Cookies || (exports.Cookies = {}));
});
define("Utils/TypeChecker", ["require", "exports"], function (require, exports) {
    "use strict";
    Object.defineProperty(exports, "__esModule", { value: true });
    exports.TypeChecker = void 0;
    var TypeChecker;
    (function (TypeChecker) {
        /**
         * Checks if any of the arguments is undefined.
         * @param objects Objects to check.
         */
        function isAnyUndefined(...objects) {
            return objects.some((obj) => typeof obj === "undefined");
        }
        TypeChecker.isAnyUndefined = isAnyUndefined;
    })(TypeChecker = exports.TypeChecker || (exports.TypeChecker = {}));
});
//# sourceMappingURL=app.js.map
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
            var getValues = {};
            location.search.substr(1).split("&").forEach(item => { getValues[item.split("=")[0]] = item.split("=")[1]; });
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
            var getValues = {};
            location.search.substr(1).split("&").forEach(item => { getValues[item.split("=")[0]] = item.split("=")[1]; });
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
define("Modules/NavigationModule", ["require", "exports", "Utils/Utils"], function (require, exports, Utils_1) {
    "use strict";
    Object.defineProperty(exports, "__esModule", { value: true });
    exports.NavigationModule = void 0;
    var NavigationModule;
    (function (NavigationModule) {
        const defaultPage = "./pages/led-config.html";
        function Bind() {
            $(".nav-link").on("click", (element) => {
                let clickedItem = $(element.target);
                let targetPage = clickedItem.data("page-file-name");
                loadPage(targetPage);
            });
            LoadPageFromUrl(); // Load url by checking the current link.
        }
        NavigationModule.Bind = Bind;
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
     * Ensure that the values are identical to "source\Constants\EventNames.ts"!
     */
    var EventNames;
    (function (EventNames) {
        EventNames["DeviceSettings"] = "DeviceSettings";
    })(EventNames = exports.EventNames || (exports.EventNames = {}));
});
define("Modules/ServerEventListener", ["require", "exports"], function (require, exports) {
    "use strict";
    Object.defineProperty(exports, "__esModule", { value: true });
    exports.ServerEventListener = void 0;
    var ServerEventListener;
    (function (ServerEventListener) {
        function Listen() {
            setupEventSource();
            listenToEvents();
        }
        ServerEventListener.Listen = Listen;
        function AddListener(eventName, eventCallback) {
            ServerEventListener.eventSource.addEventListener(eventName, (e) => {
                try {
                    let eventData = JSON.parse(e.data);
                    eventCallback(eventData);
                }
                catch (error) {
                    console.error(error);
                }
            });
        }
        ServerEventListener.AddListener = AddListener;
        function listenToEvents() {
            ServerEventListener.eventSource.addEventListener('message', function (e) {
                console.debug(e); // debug
                // var data = JSON.parse(e.data);
                // console.log(data);
            }, false);
            ServerEventListener.eventSource.addEventListener('open', function (e) {
                // Connection was opened.
                console.debug("Now lisetn to esp events.");
            }, false);
            ServerEventListener.eventSource.addEventListener('error', function (e) {
                if (this.readyState == EventSource.CLOSED) {
                    console.debug("Connection closed!");
                    return;
                }
                console.error(e);
            }, false);
        }
        function setupEventSource() {
            var eventUrl = '/events';
            if (!!window.EventSource) {
                ServerEventListener.eventSource = new EventSource(eventUrl);
            }
            else {
                // Result to xhr polling :(
                console.error("HTML 5 not supported by browser!"); // TODO: Just don't allow outdated browsers.
                alert("Use a modern Browser.");
            }
        }
    })(ServerEventListener = exports.ServerEventListener || (exports.ServerEventListener = {}));
});
define("Models/DeviceSettings", ["require", "exports"], function (require, exports) {
    "use strict";
    Object.defineProperty(exports, "__esModule", { value: true });
});
define("Modules/DeviceSettingsHandler", ["require", "exports"], function (require, exports) {
    "use strict";
    Object.defineProperty(exports, "__esModule", { value: true });
    exports.DeviceSettingsHandler = void 0;
    var DeviceSettingsHandler;
    (function (DeviceSettingsHandler) {
        var currentSettings;
        function RequestDeviceSettings() {
        }
        DeviceSettingsHandler.RequestDeviceSettings = RequestDeviceSettings;
    })(DeviceSettingsHandler = exports.DeviceSettingsHandler || (exports.DeviceSettingsHandler = {}));
});
define("Modules/AlertHandler", ["require", "exports"], function (require, exports) {
    "use strict";
    Object.defineProperty(exports, "__esModule", { value: true });
    exports.AlertHandler = void 0;
    var AlertHandler;
    (function (AlertHandler) {
        var alertCounter = 0;
        function innerAlert(type, message) {
            const showAlertFor = 1 * 1000;
            var alertId = `ah-alert-${alertCounter++}`;
            var newAlert = $("body#ah-container").append(`<div class="ah-alert" id="${alertId}">`);
            newAlert.toggleClass("visible");
            setTimeout(() => {
                newAlert.toggleClass("visible");
            }, showAlertFor);
        }
        function Primary(message) {
            innerAlert("primary", message);
        }
        AlertHandler.Primary = Primary;
        function Secondary(message) {
            innerAlert("secondary", message);
        }
        AlertHandler.Secondary = Secondary;
        function Success(message) {
            innerAlert("success", message);
        }
        AlertHandler.Success = Success;
        function Danger(message) {
            innerAlert("danger", message);
        }
        AlertHandler.Danger = Danger;
        function Warning(message) {
            innerAlert("warning", message);
        }
        AlertHandler.Warning = Warning;
        function Info(message) {
            innerAlert("info", message);
        }
        AlertHandler.Info = Info;
        function Light(message) {
            innerAlert("light", message);
        }
        AlertHandler.Light = Light;
        function Dark(message) {
            innerAlert("dark", message);
        }
        AlertHandler.Dark = Dark;
    })(AlertHandler = exports.AlertHandler || (exports.AlertHandler = {}));
});
define("app", ["require", "exports", "Modules/NavigationModule", "Modules/ServerEventListener", "Modules/DeviceSettingsHandler", "Modules/AlertHandler"], function (require, exports, NavigationModule_1, ServerEventListener_1, DeviceSettingsHandler_1, AlertHandler_1) {
    "use strict";
    Object.defineProperty(exports, "__esModule", { value: true });
    // Load, Bind and setup all required modules.
    $(() => {
        setInterval(() => AlertHandler_1.AlertHandler.Danger("test"), 3000);
        NavigationModule_1.NavigationModule.Bind();
        ServerEventListener_1.ServerEventListener.Listen();
        DeviceSettingsHandler_1.DeviceSettingsHandler.RequestDeviceSettings();
    });
});
define("Models/IStripeProcessingData", ["require", "exports"], function (require, exports) {
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
    $.ajax({
        type: 'POST',
        url: path,
        dataType: 'json',
        contentType: 'application/json',
        processData: false,
        data: data,
        success: function (resp) {
            console.log(resp);
        }
    });
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
import { EventNames } from "../Constants/EventNames";
import { AlertProvider } from "./AlertProvider";

export module ServerEventListener {
    export var eventSource: EventSource;

    export function Listen(): void {
        setupEventSource();
        listenToEvents();
    }

    export function AddListener<TResultData>(eventName: EventNames, eventCallback: (eventData: TResultData) => void) {
        eventSource.addEventListener(eventName, (e: any) => {
            try {
                let eventData: TResultData = JSON.parse(e.data);
                eventCallback(eventData);
            } catch (error) {
                AlertProvider.Danger(error);
                console.error(error);
            }
        });
    }

    function listenToEvents() {
        eventSource.addEventListener('message', function (e) {
            console.debug(e); // debug
            // var data = JSON.parse(e.data);
            // console.log(data);
        }, false);

        eventSource.addEventListener('open', function (e) {
            AlertProvider.Info("Connection to device established.");
        }, false);

        eventSource.addEventListener('error', function (e: ErrorEvent) {
            if (this.readyState == EventSource.CLOSED) {
                AlertProvider.Warning("Connection closed!");
                return;
            }
            AlertProvider.Danger(e.message);
        }, false);

    }

    function setupEventSource() {
        var eventUrl: string = '/events';

        if (!!window.EventSource) {
            eventSource = new EventSource(eventUrl);
        } else {
            // Result to xhr polling :(
            console.error("HTML 5 not supported by browser!"); // TODO: Just don't allow outdated browsers.
            alert("Use a modern Browser.");
        }

    }
}
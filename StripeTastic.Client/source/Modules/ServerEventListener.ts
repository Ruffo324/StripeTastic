export module ServerEventListener {
    export var eventSource: EventSource;
    export function Listen(): void {
        setupEventSource();
        listenToEvents();
    }

    function listenToEvents() {
        eventSource.addEventListener('message', function (e) {
            console.debug(e); // debug
            // var data = JSON.parse(e.data);
            // console.log(data);
        }, false);

        eventSource.addEventListener('DeviceSettings', function (e: any) {

        }, false);

        eventSource.addEventListener('open', function (e) {
            // Connection was opened.
            console.debug("Now lisetn to esp events.");
        }, false);

        eventSource.addEventListener('error', function (e) {
            if (this.readyState == EventSource.CLOSED) {
                console.debug("Connection closed!");
            }
            console.error(e);
        }, false);

    }

    function setupEventSource() {
        var eventUrl: string = '/events';

        if (!!window.EventSource) {
            eventSource = new EventSource(eventUrl);
        } else {
            // Result to xhr polling :(
            console.error("HTML 5 not supported by browser!"); // TODO: Just don't allow outdated browsers.
        }

    }
}
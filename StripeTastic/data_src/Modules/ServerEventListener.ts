export module ServerEventListener {
    interface SetPixelColorData {
        Pin: number;
        Pixel: number;

        Color: {
            Red: number;
            Green: number;
            Blue: number;
        }
    };

    var eventSource: EventSource;
    export function Listen(): void {
        setupEventSource();
        listenToEvents();
    }

    function listenToEvents() {
        eventSource.addEventListener('message', function (e) {
            var data = JSON.parse(e.data);
            console.log(data);
        }, false);

        eventSource.addEventListener('SetPixelColor', function (e: any) {
            var pixelData: SetPixelColorData = JSON.parse(e.data);

            // var $element = $('#stripe_23');
            // if(!$element.length)
            let parentId = `#stripe_${pixelData.Pin}`;
            let parentContainer = $(parentId);
            if (!parentContainer.length) parentContainer = $(`<div id="stripe_${pixelData.Pin}"></div>`).appendTo('#stripe_container');

            let pixelClass = `.pixel-${pixelData.Pixel}`;
            let pixelElement = $(pixelClass);
            if (!pixelElement.length) pixelElement = $(`<div class="pixel pixel-${pixelData.Pixel}"></div>`).appendTo(parentContainer);

            pixelElement.css('background-color', 'rgb(' + pixelData.Color.Red + ',' + pixelData.Color.Green + ',' + pixelData.Color.Blue + ')');

            // $("#debug-pixel-data").append(e.data);
            //            let pixelData: SetPixelColorData = JSON.parse(e.data);
        }, false);

        eventSource.addEventListener('open', function (e) {
            // Connection was opened.
            console.debug("Now listen to esp events.");
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
        if (window.location.host != "192.168.178.38")
            eventUrl = "http://192.168.178.38" + eventUrl;

        if (!!window.EventSource) {
            eventSource = new EventSource(eventUrl);
        } else {
            // Result to xhr polling :(
            console.error("HTML 5 not supported by browser!"); // TODO: Just don't allow outdated browsers.
        }

    }
}
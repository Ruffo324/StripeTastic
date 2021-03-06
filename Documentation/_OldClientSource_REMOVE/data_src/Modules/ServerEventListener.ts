export module ServerEventListener {
    // interface LedColor {
    //     Red: number;
    //     Green: number;
    //     Blue: number;
    // }
    interface PixelData {
        Pin: number;
        Pixels: number[];
    };

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

        eventSource.addEventListener('PixelData', function (e: any) {
            // console.debug(e); // Debug
            var pixelData: PixelData = JSON.parse(e.data);
            // console.debug(pixelData);

            // var $element = $('#stripe_23');
            // if(!$element.length)
            var parentId = `#stripe_${pixelData.Pin}`;
            var parentContainer = $(parentId);
            if (!parentContainer.length) parentContainer = $(`<div id="stripe_${pixelData.Pin}"></div>`).appendTo('#stripe_container');

            var timeoutForEachPixel = (1000 / pixelData.Pixels.length);
            for (let i = 0; i < pixelData.Pixels.length; i++) {
                let color = pixelData.Pixels[i].toString(16);
                let pixelClass = `${parentId} > .pixel-${i}`;
                let pixelElement = $(pixelClass);
                if (!pixelElement.length) pixelElement = $(`<div class="pixel pixel-${i}"></div>`).appendTo(parentContainer);
                let timeoutForThisPixel = timeoutForEachPixel * i;
                setTimeout(() => pixelElement.css('background-color', color == "0" ? "transparent" : `#${color}`), timeoutForThisPixel);
            }

            // $("#debug-pixel-data").append(e.data);
            //            let pixelData: SetPixelColorData = JSON.parse(e.data);
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
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

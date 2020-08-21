
function changeStroboSpeed(speed) {
    simpleRestRequest("/effects/strobe/speed", JSON.stringify({ 'speed': speed }));
    $("#value-strobo-speed").html(`${speed}/s`);
}

function changeColor(colorHex) {
    let rgbColor = hexToRgb(colorHex);
    simpleRestRequest("/effects/color", JSON.stringify({ 'red': rgbColor.red, 'green': rgbColor.green, 'blue': rgbColor.blue }));
}
function strobeOnOff() {
    simpleRestRequest("/effects/strobe/on", JSON.stringify({ 'on': $('#strobo-on-off').is(":checked") }));
}

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
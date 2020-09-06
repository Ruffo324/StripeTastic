var defaultProcessing = {
    "OperationMode": 0,
    "Effect": 7,
    "EffectDirection": 0,
    "Licht": 4,
    "Brightness": 255,
    "FlashPerSeconds": 50,
    "EffectDelay": 10,
    "Intensity": 100.0,
    "FFTActive": false,
    "Changed": true,
    "IsAux": true,
    "LED_farbe_1": { red: 255, green: 0, blue: 0 },
    "LED_farbe_2": { red: 0, green: 255, blue: 0 },
    "LED_farbe_3": { red: 0, green: 0, blue: 255 },
    "LED_farbe_4": { red: 255, green: 0, blue: 255 }
};

// Prefill textareas..
$("#stripe1").val(JSON.stringify(defaultProcessing));
$("#stripe2").val(JSON.stringify(defaultProcessing));

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
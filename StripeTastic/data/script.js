
function changeStroboSpeed(speed) {
    $.ajax({
        type: 'POST',
        url: '/rest/endpoint',
        // url: '/effects/strobe/speed',
        dataType: 'json',
        contentType: 'application/json',
        processData: false,
        data: JSON.stringify({ 'speed': speed }),
        success: function (resp) {
            console.log(resp);
        }
    });
}
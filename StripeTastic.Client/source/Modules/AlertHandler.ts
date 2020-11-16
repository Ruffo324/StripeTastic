
export module AlertHandler {
	var alertCounter = 0;

	function innerAlert(type: string, message: string) {
		const showAlertFor = 10 * 1000;
		var alertId = `ah-alert-${alertCounter++}`;
		console.debug(`alertId: ${alertId}`); // debug

		// Create alert element.
		$("#ah-container").append(`<div class="ah-alert ah-alert-${type}" id="${alertId}">${message}</div>`);

		let newAlert = $(`#${alertId}`);
		newAlert.toggleClass("visible");
		setTimeout(() => {
			newAlert.toggleClass("visible");
			console.debug(`alertId: ${alertId} visible.`);
		}, showAlertFor);

	}

	export function Primary(message: string) {
		innerAlert("primary", message);
	}
	export function Secondary(message: string) {
		innerAlert("secondary", message);
	}
	export function Success(message: string) {
		innerAlert("success", message);
	}
	export function Danger(message: string) {
		innerAlert("danger", message);
	}
	export function Warning(message: string) {
		innerAlert("warning", message);
	}
	export function Info(message: string) {
		innerAlert("info", message);
	}
	export function Light(message: string) {
		innerAlert("light", message);
	}
	export function Dark(message: string) {
		innerAlert("dark", message);
	}


}
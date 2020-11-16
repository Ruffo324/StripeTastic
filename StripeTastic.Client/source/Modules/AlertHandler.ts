
export module AlertHandler {
	var alertCounter = 0;
	function innerAlert(type: string, message: string) {
		const showAlertFor = 1 * 1000;
		var alertId = `ah-alert-${alertCounter++}`;
		var newAlert = $("body#ah-container").append(`<div class="ah-alert" id="${alertId}">`);
		newAlert.toggleClass("visible");
		setTimeout(() => {
			newAlert.toggleClass("visible");
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
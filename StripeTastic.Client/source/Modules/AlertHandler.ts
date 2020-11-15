
export module AlertHandler {
	var alertCounter = 0;
	const toastContainer = $("#toast-container");
	const toastTemplate = `
	<div class="toast" role="alert" aria-live="assertive" aria-atomic="true">
		<div class="toast-header">
			<strong class="mr-auto">Bootstrap</strong>
			<small>11 mins ago</small>
			<button type="button" class="ml-2 mb-1 close" data-dismiss="toast" aria-label="Close">
				<span aria-hidden="true">&times;</span>
			</button>
			</div>
			<div class="toast-body">
			Hello, world! This is a toast message.
		</div>
	  </div>`


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
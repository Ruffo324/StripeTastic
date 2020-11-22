import { App } from "../app";
import { EventNames } from "../Constants/EventNames";
import { AlertProvider } from "./AlertProvider";


export module DeviceCommunicator {
	const _deviceEventSource: string = '/events';
	let _eventSource: EventSource;

	App.InjectAppStart(() => Initialize());

	function GetEventSource(): EventSource {
		try {
			if(typeof(_eventSource) === "undefined")
				_eventSource = new EventSource(_deviceEventSource);

			return _eventSource;
		} catch (error) {
			const message = "Unable to setup event source. Please use an up to date server!";
			alert(message);
			throw new Error(message);
		}
	}

	export function AddListener<TResultData>(eventName: EventNames, eventCallback: (eventData: TResultData) => void) {
		let eventSource = GetEventSource();
		eventSource.addEventListener(eventName, (e: any) => {
			try {
				let eventData: TResultData = JSON.parse(e.data);
				eventCallback(eventData);
			} catch (error) {
				AlertProvider.Danger(error);
				console.error(error);
			}
		});
	}

	function Initialize() {
		let eventSource = GetEventSource();
		eventSource.addEventListener('message', function (e) {
			AlertProvider.Secondary(JSON.stringify(e));
		}, false);

		eventSource.addEventListener('open', function (_) {
			AlertProvider.Info("Connection to device established.");
		}, false);

		eventSource.addEventListener('error', function (e: ErrorEvent) {
			if (this.readyState == EventSource.CLOSED) {
				AlertProvider.Warning("Connection closed!");
				return;
			}
			AlertProvider.Danger(e.message);
		}, false);

	}
}
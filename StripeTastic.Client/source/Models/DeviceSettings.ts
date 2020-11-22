/**
 * Stores and modifies the current known device settings.
 */
export interface IDeviceSettings {
	ConnectionMode: ConnectionMode;


}

export enum ConnectionMode {
	AdHoc = 0,
	Router = 1,
}
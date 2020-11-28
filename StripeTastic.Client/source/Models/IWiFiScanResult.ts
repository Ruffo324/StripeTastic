

export interface IWiFiScanResult {
	Networks: IWiFiScanEntry[];
}

export interface IWiFiScanEntry {
	Ssid: string;
	Channel: number;
	SignalStrength: number;
}
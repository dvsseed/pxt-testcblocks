// Auto-generated. Do not edit.

//% weight=110 color=#ff00ff icon="\uf079"
declare namespace DS3231 {

    /**
     * Sets the current datetime on the external DS3231 rtc sensor
     * @param sYear describe parameter here, eg: 18
     * @param sMonth describe parameter here, eg: 1
     * @param sMonth describe parameter here, eg: 1
     * @param sDay describe parameter here, eg: 5
     * @param sHour describe parameter here, eg: 11
     * @param sMinute describe parameter here, eg: 1
     * @param sSecond describe parameter here, eg: 59
	 */
    //% weight=100
    //% blockId="id_setDateTime"
    //% block="set datetime to DS3231 sensor => 20|%sYear-|%sMonth-|%sDay |%sHour:|%sMinute-|%sSecond"
	//% shim="DS3231::fn_setDateTime"
    function fn_setDateTime(sYear: number, sMonth: number, sDay: number, sHour: number, sMinute: number, sSecond: number): void;

    /**
     * Gets the current date on the DS3231 rtc sensor
     */
    //% weight=90
    //% blockId="id_displayDate"
    //% block="display Date (ex: 2018-1-4)"
    //% shim="DS3231::fn_displayDate"
    function fn_displayDate(): void;

    /**
     * Gets the current time on the DS3231 rtc sensor
     */
	//% weight=80
    //% blockId="id_displayTime"
    //% block="display Time (ex: 12:59:59)"
    //% shim="DS3231::fn_displayTime"
    function fn_displayTime(): void;

    /**
     * Gets the current temperature value on the DS3231 temperature sensor
     */
	//% weight=70
	//% blockId="id_displayTemp"
    //% block="display temperature sensor value (°C)"
    //% shim="DS3231::fn_displayTemp"
    function fn_displayTemp(): void;

}

// Auto-generated. Do not edit. Really.

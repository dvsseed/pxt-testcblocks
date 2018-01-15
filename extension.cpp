/*
This program uses the Maxim Integrated DS3231 library to create a BBC MicroBit Real-Time Clock.
Requires a DS3231 Real Time clock connected to pin 19(SCL) and 20(SDA).

Recommended that an edge connector is used for DS3231 connection.

Pressing Button A to display the Date
Pressing Button B to display the Time
Pressing Buttons A and B together to show the temperature degree

Modified by Davis, 2018/1/4
*/
#include "pxt.h"
#include "MicroBit.h"
#include "ds3231.h"

MicroBit uBit;

namespace ds3231 {
    int iss, imm, ihh, iDD, iMM, iYY;
    ManagedString ss, mm, hh, dOw, DD, MM, YY, txtMonth, txtDay, tempOut;
    ManagedString tsep = ":";
    ManagedString spc = "-";

    Ds3231 mRTC(I2C_SDA0, I2C_SCL0);

    uint16_t rtn;
    uint16_t rval;

    ds3231_time_t mTime = {0, 0, 0, false, false};  // 24 hr mode - seconds, minutes, hours, am_pm(pm=1, am=0), mode(0=24, 1=12hr)
    ds3231_calendar_t mCalendar; // day(day of week), date(day), month, year

    // Seconds and am1 not used for alarm2
    uint16_t mTemp; // raw temp data
    char * monthn[12] = {"01", "02", "03", "04", "05", "06", "07", "08", "09", "10", "11", "12"};
    int displayMode = 0;

    // predeclare functions
    void getTimeAndDate();
    void setDateTimeByUser(int uYear, int uMonth, int uDay, int uHour, int uMinute, int uSecond);
    void displayDate();
    void displayTime();
    void displayTemp();

    void getTimeAndDate()
    {
        // get date and time and populate data vars
        mTime.mode = false; // 24 hour
        rval = mRTC.get_time(&mTime); // get time
        mTemp = mRTC.get_temperature(); // get temperature
        rtn = mRTC.get_calendar(&mCalendar); // get date
        YY = (int)(mCalendar.year + 2000); // 4 digit
        txtMonth = monthn[((int)mCalendar.month) - 1];

        iss = (int)mTime.seconds;
        imm = (int)mTime.minutes;
        ihh = (int)mTime.hours;
        iDD = (int)mCalendar.date;
        iMM = (int)mCalendar.month;
        iYY = (int)mCalendar.year;

        ManagedString s1 (iss / 10);
        ManagedString s2 (iss % 10);
        ss = s1 + s2;
        ManagedString m1 (imm / 10);
        ManagedString m2 (imm % 10);
        mm = m1 + m2;
        ManagedString h1 (ihh / 10);
        ManagedString h2 (ihh % 10);
        hh = h1 + h2;
        ManagedString D1 (iDD / 10);
        ManagedString D2 (iDD % 10);
        DD = D1 + D2;
        ManagedString M1 (iMM / 10);
        ManagedString M2 (iMM % 10);

        // lets setup the Temperature here too
        mTemp = mTemp / 256;
        ManagedString tmp (mTemp);
        tempOut = (tmp + " degC");
    }

    void setDateTimeByUser(int uYear, int uMonth, int uDay, int uHour, int uMinute, int uSecond)
    {
        int rVal;
        bool setMode, setAM_PM;
        getTimeAndDate(); // get latest

        // set date
        mCalendar.year = uYear;
        mCalendar.month = uMonth;
        mCalendar.date = uDay;
        rVal = mRTC.set_calendar(mCalendar);
        mTime.hours = uHour;
        mTime.minutes = uMinute;
        mTime.seconds = uSecond;
        setMode = false; // 24 hour clock only
        mTime.mode = setMode;
        mTime.am_pm = setAM_PM;
        rVal = mRTC.set_time(mTime);
    }

    void displayDate()
    {
        ManagedString dateOut (YY + spc + txtMonth + spc + DD);
        uBit.display.scroll(dateOut);
        uBit.sleep(1000);
    }

    void displayTime()
    {
        ManagedString timeOut (hh + tsep + mm + tsep + ss);
        uBit.display.scroll(timeOut);
        uBit.sleep(1000);
    }

    void displayTemp()
    {
        uBit.display.scroll(tempOut);
        uBit.sleep(1000);
    }

    /**
    * Sets the current datetime on the external ds3231 rtc sensor
    */
    //% blockId="id_setDateTime"
    //% block="set datetime to ds3231 sensor => 20%sYear-%sMonth-%sDay %sHour:%sMinute-%sSecond"
    void fn_setDateTime(int sYear, int sMonth, int sDay, int sHour, int sMinute, int sSecond) {
        setDateTimeByUser(sYear, sMonth, sDay, sHour, sMinute, sSecond); // ex: 2018-1-4 14:53:50
        uBit.sleep(100);
    }

    /**
    * Gets the current date on the ds3231 rtc sensor
    */
    //% blockId="id_displayDate"
    //% block="display Date (ex: 2018-1-5)"
    void fn_displayDate() {
        getTimeAndDate();
        uBit.sleep(100);
        displayDate();
    }

    /**
    * Gets the current time on the ds3231 rtc sensor
    */
    //% blockId="id_displayTime"
    //% block="display Time (ex: 12:59:59)"
    void fn_displayTime() {
        getTimeAndDate();
        uBit.sleep(100);
        displayTime();
    }

    /**
    * Gets the current temperature value on the ds3231 temperature sensor
    */
    //% blockId="id_displayTemp"
    //% block="display temperature sensor value (°C)"
    void fn_displayTemp() {
        // Display the temperature
        getTimeAndDate();
        uBit.sleep(100);
        displayTemp();
    }
}

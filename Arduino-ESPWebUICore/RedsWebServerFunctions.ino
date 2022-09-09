#pragma once
#include "GlobalVariables.h"
#include "RedsTime.h"

String Relay_switch()
{
    byte state;
    if (digitalRead(PinRelay))
        state = 0;
    else
        state = 1;
    digitalWrite(PinRelay, state);
    return String(state);
}

String Relay_status_logic()
{
    byte state;
    if (digitalRead(PinRelay))
        state = 1;
    else
        state = 0;
    return String(state);
}

String Relay_status_text()
{
    String state;
    if (digitalRead(PinRelay))
        state = "ON";
    else
        state = "OFF";
    return String(state);
}

String Relay_status_full()
{
    String result = "";

    String brake = "<br>";
    String separator = "--------------------------------" + brake;

    time_t t = time(0); // get time now
    tm *now = localtime(&t);

    byte NowHour = now->tm_hour;
    byte NowMin = now->tm_min;
    byte NowSec = now->tm_sec;

    result += "System clock->" + GetTimeString(NowHour, NowMin, NowSec) + brake;
    result += separator;
    result += "Work start--->" + GetTimeString(StartHour, StartMinute) + brake;
    result += "Work end----->" + GetTimeString(EndHour, EndMinute) + brake;
    result += "Interval----->" + GetTimeString(IntervalHours, IntervalMins) + brake;
    // result += "Next work---->" + GetTimeString(LastWorkHour, LastWorkMin) + brake;
    result += "Last work---->" + GetTimeString(LastWorkHour, LastWorkMin) + brake;
    result += separator;
    result += "Uptime------->" + GetUptimeString() + brake;
    return result;
}

String Set(String Argument, String Value)
{
    return "pizza lol>" + Value + "<pizza lol" + "<br>" + Argument;
}
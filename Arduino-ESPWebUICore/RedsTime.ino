#pragma once
#include "GlobalVariables.h"

bool GetNTPtime(int sec)
{
    {
        uint32_t start = millis();
        do
        {
            time(&now);
            localtime_r(&now, &timeinfo);
            Serial.print(".");
            delay(10);
        } while (((millis() - start) <= (1000 * sec)) && (timeinfo.tm_year < (2016 - 1900)));
        if (timeinfo.tm_year <= (2016 - 1900))
            return false; // the NTP call was not successful
        Serial.print("now ");
        Serial.println(now);
        char time_output[30];
        strftime(time_output, 30, "%a  %d-%m-%y %T", localtime(&now));
    }
    return true;
}

int GetTotalMins(byte hours, byte mins)
{
    return hours * 60 + mins;
}

String GetTimeString(byte hour, byte min, byte sec)
{
    String stringHour = String(hour);
    String stringMin = String(min);
    String stringSec = String(sec);

    if (stringHour.length() == 1)
    {
        stringHour = "0" + stringHour;
    }

    if (stringMin.length() == 1)
    {
        stringMin = "0" + stringMin;
    }

    if (stringSec.length() == 1)
    {
        stringSec = "0" + stringSec;
    }

    return stringHour + ":" + stringMin + ":" + stringSec;
}
String GetTimeString(byte hour, byte min)
{
    String stringHour = String(hour);
    String stringMin = String(min);

    if (stringHour.length() == 1)
    {
        stringHour = "0" + stringHour;
    }

    if (stringMin.length() == 1)
    {
        stringMin = "0" + stringMin;
    }

    return stringHour + ":" + stringMin;
}
String GetUptimeString()
{
    uint32_t sec = millis() / 1000ul;
    int timeHours = (sec / 3600ul);
    int timeMins = (sec % 3600ul) / 60ul;
    int timeSecs = (sec % 3600ul) % 60ul;

    String hours = String(timeHours);
    String mins = String(timeMins);
    String secs = String(timeSecs);

    if (hours.length() <= 1)
    {
        hours = "0" + hours;
    }

    if (mins.length() <= 1)
    {
        mins = "0" + mins;
    }

    if (secs.length() <= 1)
    {
        secs = "0" + secs;
    }

    return hours + ":" + mins + ":" + secs;
}
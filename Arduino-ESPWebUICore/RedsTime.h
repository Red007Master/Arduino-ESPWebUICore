#pragma once

bool GetNTPtime(int sec);

int GetTotalMins(byte hours, byte mins);

String GetTimeString(byte hour, byte min, byte sec);
String GetTimeString(byte hour, byte min);
String GetUptimeString();
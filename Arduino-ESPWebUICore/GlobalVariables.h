#pragma once
#include <ESP8266WebServer.h>
#include <ESP8266FtpServer.h>

////{TIME
byte StartHour;
byte StartMinute;

byte EndHour;
byte EndMinute;

byte IntervalHours;
byte IntervalMins;
int IntervalTotalMins;

byte LastWorkHour;
byte LastWorkMin;
int LastWorkTotalMins;

const char *NTP_SERVER = "ch.pool.ntp.org";
const char *TZ_INFO = "EET-2EEST,M3.5.0/3,M10.5.0/4"; // enter your time zone (https://remotemonitoringsystems.ca/time-zone-abbreviations.php)

tm timeinfo;
time_t now;

long unsigned lastNTPtime;
unsigned long lastEntryTime;
////}TIME

////{PINS
const byte PinRelay = 2; // 12;
const byte PinLed = 2;
////}PINS

////{Servers
ESP8266WebServer WebServer(80);
FtpServer ftpSrv;
////}Servers
#pragma once
#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>
#include <FS.h>
#include <time.h>
#include "RedsTime.h"
#include "RedsWebServerFunctions.h"
#include "GlobalVariables.h"
#include "credentials.h"

void Initialization()
{
    InitializeGlobalVariables();
    InitializePinsAndCom();
    InitializeWIFI();
    InitializeTime();
    InitializeServersAndFileSystem();
}

void InitializeGlobalVariables()
{
    StartHour = 2;
    StartMinute = 34;

    EndHour = 5;
    EndMinute = 50;

    IntervalHours = 5;
    IntervalMins = 44;
    IntervalTotalMins = GetTotalMins(IntervalHours, IntervalMins);

    LastWorkHour = 0;
    LastWorkMin = 0;
    LastWorkTotalMins = 0;
}

void InitializePinsAndCom()
{
    pinMode(PinRelay, OUTPUT);
    Serial.begin(9600);
}

void InitializeWIFI()
{
    int counter = 0;

    WiFi.begin(ssid, password);

    Serial.println("\n\nTry connect to WIFI\n\n");
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(200);
        if (++counter > 100)
            ESP.restart();
        Serial.print(".");
    }
    Serial.println("\n\nWiFi connected\n\n");
}

void InitializeTime()
{
    configTime(0, 0, NTP_SERVER);
    setenv("TZ", TZ_INFO, 1);

    if (GetNTPtime(10))
    { // wait up to 10sec to sync
    }
    else
    {
        Serial.println("Time not set");
        ESP.restart();
    }

    lastNTPtime = time(&now);
    lastEntryTime = millis();
}

void InitializeServersAndFileSystem()
{
    SPIFFS.begin();
    WebServer.begin();
    ftpSrv.begin("relay", "relay");

    WebServer.on("/relay_switch", []()
                 { WebServer.send(200, "text/plain", Relay_switch()); });

    WebServer.on("/relay_status_text", []()
                 { WebServer.send(200, "text/plain", Relay_status_text()); });

    WebServer.on("/relay_status_logic", []()
                 { WebServer.send(200, "text/plain", Relay_status_logic()); });

    WebServer.on("/relay_status_full", []()
                 { WebServer.send(200, "text/plain", Relay_status_full()); });

    WebServer.on("/input", []()
                 { WebServer.send(200, "text/plain", "v>" + WebServer.arg("input1") + "<v"); });

    WebServer.on("/input_set_work_start", []()
                 { WebServer.send(200, "text/plain", Set("input_set_work_start", WebServer.arg("i_s_w_s"))); });

    WebServer.onNotFound([]()
                         {
    if (!handleFileRead(WebServer.uri()))
      {
        WebServer.send(404, "text/plain", "Not Found");
      } });
}
bool handleFileRead(String path)
{
    if (path.endsWith("/"))
        path += "index.html";
    String contentType = getContentType(path);
    if (SPIFFS.exists(path))
    {
        File file = SPIFFS.open(path, "r");
        size_t sent = WebServer.streamFile(file, contentType);
        file.close();
        return true;
    }
    return false;
}
String getContentType(String filename)
{
    if (filename.endsWith(".html"))
        return "text/html";
    else if (filename.endsWith(".css"))
        return "text/css";
    else if (filename.endsWith(".js"))
        return "application/javascript";
    else if (filename.endsWith(".png"))
        return "image/png";
    else if (filename.endsWith(".jpg"))
        return "image/jpeg";
    else if (filename.endsWith(".gif"))
        return "image/gif";
    else if (filename.endsWith(".ico"))
        return "image/x-icon";
    return "text/plain";
}
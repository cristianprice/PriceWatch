#include "price_watch_local_time.h"
#include "price_watch_wifi.h"

void check_wifi_and_setup_time(void *parameter)
{
    for (int i = 0; i <= 10; i++)
    {
        if (!wifiStaConnected)
        {
            delay(500);
#ifdef DEBUG
            Serial.println("Waiting for WiFi connection...");
#endif
        }
    }

    if (!wifiStaConnected)
    {
#ifdef DEBUG
        Serial.println("WiFi not connected. Cannot setup time.");
#endif
    }
    else
    {
#if DEBUG
        Serial.println("WiFi connected. Setting up local time...");
#endif
        setup_local_time();
    }

    // do work
    vTaskDelete(NULL); // or just return
}

void setup_local_time()
{
    const char *ntpServer = "pool.ntp.org";

    // Bucharest / Romania timezone
    const char *tz = BUCHAREST_TZ;

    configTzTime(tz, ntpServer);

    struct tm timeinfo;
    if (!getLocalTime(&timeinfo, 10000))
    {
        Serial.println("Failed to obtain time");
        return;
    }
#ifdef DEBUG
    Serial.println(&timeinfo, "Local time: %Y-%m-%d %H:%M:%S");
#endif
}

const char *local_time_get_time_str()
{
    static char timeStr[6]; // HH:MM + null terminator
    struct tm timeinfo;
    if (getLocalTime(&timeinfo))
    {
        snprintf(timeStr, sizeof(timeStr), "%02d:%02d", timeinfo.tm_hour, timeinfo.tm_min);
    }
    else
    {
        snprintf(timeStr, sizeof(timeStr), "00:00");
    }
    return timeStr;
}

const char *local_time_get_date_str()
{
    static char dateStr[11]; // YYYY-MM-DD + null terminator
    struct tm timeinfo;
    if (getLocalTime(&timeinfo))
    {
        snprintf(dateStr, sizeof(dateStr), "%04d-%02d-%02d", timeinfo.tm_year + 1900, timeinfo.tm_mon + 1, timeinfo.tm_mday);
    }
    else
    {
        snprintf(dateStr, sizeof(dateStr), "1970-01-01");
    }
    return dateStr;
}

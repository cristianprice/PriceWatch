#include "price_watch.h"

const char *ssid = "YOUR_SSID";
const char *password = "YOUR_PASSWORD";

// Event handler
void WiFiEvent(WiFiEvent_t event)
{
    switch (event)
    {
    case SYSTEM_EVENT_STA_GOT_IP:
        Serial.println("Connected, IP acquired!");
        Serial.println(WiFi.localIP());
        break;
    case SYSTEM_EVENT_STA_DISCONNECTED:
        Serial.println("Disconnected! Attempting to reconnect...");
        WiFi.begin(ssid, password); // Manual reconnect
        break;
    default:
        break;
    }
}

void start_wifi()
{
    WiFi.mode(WIFI_STA);     // Station mode
    WiFi.onEvent(WiFiEvent); // Attach event handler
    WiFi.begin(ssid, password);
};

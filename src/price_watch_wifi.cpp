#include <WiFi.h>
#include "price_watch.h"

volatile bool wifiApConnected = false;
volatile bool wifiStaConnected = false;
WifiConfig currentWifiConfig;

void wiFiEventHandler(WiFiEvent_t event)
{
    switch (event)
    {
    /* ===== STA EVENTS ===== */
    case SYSTEM_EVENT_STA_START:
#ifdef DEBUG
        Serial.println("STA started");
#endif
        wifiStaConnected = false; // Not connected yet
        break;

    case SYSTEM_EVENT_STA_GOT_IP:
#ifdef DEBUG
        Serial.print("STA connected, IP: ");
        Serial.println(WiFi.localIP());
#endif
        wifiStaConnected = true; // STA connected
        break;

    case SYSTEM_EVENT_STA_DISCONNECTED:
#ifdef DEBUG
        Serial.println("STA disconnected, reconnecting...");
#endif
        wifiStaConnected = false;                                               // STA disconnected
        WiFi.begin(currentWifiConfig.sta_ssid, currentWifiConfig.sta_password); // Attempt reconnect
        break;

    /* ===== AP EVENTS ===== */
    case SYSTEM_EVENT_AP_START:
#ifdef DEBUG
        Serial.println("AP started");
        Serial.print("AP IP: ");
        Serial.println(WiFi.softAPIP());
#endif
        wifiApConnected = false; // No clients yet
        break;

    case SYSTEM_EVENT_AP_STACONNECTED:
#ifdef DEBUG
        Serial.println("Client connected to AP");
#endif
        wifiApConnected = true; // At least one client connected
        break;

    case SYSTEM_EVENT_AP_STADISCONNECTED:
#ifdef DEBUG
        Serial.println("Client disconnected from AP");
#endif
        // Check if there are still clients connected
        if (WiFi.softAPgetStationNum() == 0)
            wifiApConnected = false;
        break;

    default:
        break;
    }
}

void start_wifi(const WifiConfig *config)
{
    WiFi.mode(WIFI_AP_STA);
    WiFi.onEvent(wiFiEventHandler);
    /* Start STAtion */
    if (config->start_sta)
        WiFi.begin(config->sta_ssid, config->sta_password);
    /* Start Access Point */
    if (config->start_ap)
        WiFi.softAP(config->ap_ssid, config->ap_password);
}
void stop_wifi(bool stop_sta, bool stop_ap)
{
    if (stop_sta)
        WiFi.disconnect(true, true); // Disconnect STA and erase credentials
    if (stop_ap)
        WiFi.softAPdisconnect(true); // Disconnect AP
}
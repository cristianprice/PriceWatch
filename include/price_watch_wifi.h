#pragma once
#include <Arduino.h>
#include <WiFi.h>

class PriceWatchWiFiEventHandler
{
public:
    PriceWatchWiFiEventHandler();
    virtual ~PriceWatchWiFiEventHandler();

    virtual void onEvent(WiFiEvent_t event) = 0;
};
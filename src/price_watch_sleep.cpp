#include "price_watch_sleep.h"
#include "esp_sleep.h"
#include <LilyGoWatch.h>

extern TTGOClass *ttgo;

void enter_deep_sleep()
{
    ttgo->shake();
    ttgo->closeBL();
    // ttgo->powerOff();
    // ttgo->shutdown();

    // Enter deep sleep
    esp_deep_sleep_start();
}
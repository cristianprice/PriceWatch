#pragma once
#include <Arduino.h>
#include <LilyGoWatch.h>
#include "price_watch_lvgl.h"
#include "price_watch_wifi.h"

extern TTGOClass *ttgo;

/* Initialize the Price Watch application */
void price_watch_init();
/* Main loop for the Price Watch application */
void price_watch_loop();

#pragma once
#include <Arduino.h>
#include <LilyGoWatch.h>

extern TTGOClass *ttgo;

/* Initialize the Price Watch application */
void price_watch_init();
/* Main loop for the Price Watch application */
void price_watch_loop();

/*LVGL ui*/
void create_main_screen_watch(lv_obj_t *parent);
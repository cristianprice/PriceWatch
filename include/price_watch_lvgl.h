#pragma once
#include <Arduino.h>
#include <LilyGoWatch.h>

/*LVGL ui*/
void create_main_screen();
void update_time_date_watch(const char *time_str, const char *date_str);
void set_battery_level(uint8_t percent);
void set_wifi_connected(bool connected);
#pragma once
#include "Arduino.h"
#include <WiFi.h>
#include <time.h>

#define BUCHAREST_TZ "EET-2EEST,M3.5.0/3,M10.5.0/4"

void check_wifi_and_setup_time(void *parameter);
void setup_local_time();
const char *local_time_get_time_str();
const char *local_time_get_date_str();
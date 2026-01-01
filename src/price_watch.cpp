#include "price_watch.h"
#include "price_watch_local_time.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

TTGOClass *ttgo = TTGOClass::getWatch();

void price_watch_init()
{
    ttgo->begin();
    ttgo->openBL();
    ttgo->enableTouchIRQ();
    ttgo->lvgl_begin();
    ttgo->enableLDO3();

    ttgo->motor_begin();

    // Config wifi
    currentWifiConfig.start_sta = true;
    currentWifiConfig.sta_ssid = "LaPupupu";
    currentWifiConfig.sta_password = "hidden01";

    start_wifi(&currentWifiConfig);

    xTaskCreate(
        check_wifi_and_setup_time, // Task function
        "UpdateTime",              // Name of the task
        2048,                      // Stack size in words
        NULL,                      // Task input parameter
        1,                         // Priority of the task
        NULL                       // Task handle
    );
}

void price_watch_loop()
{
    update_time_date_watch(local_time_get_time_str(), local_time_get_date_str());

    lv_task_handler();
    delay(5);
}
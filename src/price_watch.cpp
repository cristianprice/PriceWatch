#include "price_watch.h"

TTGOClass *ttgo = TTGOClass::getWatch();

void price_watch_init()
{
    ttgo->begin();
    ttgo->openBL();
    ttgo->enableTouchIRQ();
    ttgo->lvgl_begin();
    ttgo->enableLDO3();

    ttgo->motor_begin();
}

void price_watch_loop()
{
    lv_task_handler();
    delay(5);
}
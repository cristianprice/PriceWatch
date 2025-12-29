#include "price_watch.h"
#include "esp_sleep.h"

LV_FONT_DECLARE(lv_font_montserrat_28);

void setup()
{
#ifdef DEBUG
  Serial.begin(115200);
#endif
  price_watch_init();

  // Initialize the main screen
  create_main_screen_watch(nullptr);
}

void loop()
{
  price_watch_loop();
}

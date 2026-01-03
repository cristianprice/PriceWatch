#include "price_watch.h"
#include "price_watch_sleep.h"

static lv_obj_t *time_label;
static lv_obj_t *date_label;
static lv_obj_t *wifi_icon;
static lv_obj_t *battery_icon;
static lv_obj_t *power_btn;

LV_FONT_DECLARE(lv_font_montserrat_48);
LV_FONT_DECLARE(lv_font_montserrat_16);

static void power_btn_event_cb(lv_obj_t *obj, lv_event_t event);

static void remove_container_border(lv_obj_t *obj)
{
    lv_obj_set_style_local_border_width(
        obj, LV_CONT_PART_MAIN, LV_STATE_DEFAULT, 0);

    lv_obj_set_style_local_border_width(
        obj, LV_CONT_PART_MAIN, LV_STATE_PRESSED, 0);

    lv_obj_set_style_local_border_width(
        obj, LV_CONT_PART_MAIN, LV_STATE_FOCUSED, 0);

    lv_obj_set_style_local_border_width(
        obj, LV_CONT_PART_MAIN,
        LV_STATE_FOCUSED | LV_STATE_PRESSED, 0);
}

void create_main_screen()
{
    lv_obj_t *scr = lv_obj_create(NULL, NULL);
    lv_scr_load(scr);

    /* ---------- HEADER (15%) ---------- */
    lv_obj_t *header = lv_cont_create(scr, NULL);
    lv_obj_set_size(header, 240, 240 * 0.10);
    lv_obj_align(header, NULL, LV_ALIGN_IN_TOP_MID, 0, 0);
    lv_cont_set_layout(header, LV_LAYOUT_OFF);
    remove_container_border(header);

    /* ---------- WIFI ICON (LEFT) ---------- */
    wifi_icon = lv_label_create(header, NULL);
    lv_label_set_text(wifi_icon, LV_SYMBOL_WIFI);
    lv_obj_align(wifi_icon, NULL, LV_ALIGN_IN_LEFT_MID, 6, 0);

    /* ---------- BATTERY ICON (RIGHT) ---------- */
    battery_icon = lv_label_create(header, NULL);
    lv_label_set_text(battery_icon, LV_SYMBOL_BATTERY_FULL);
    lv_obj_align(battery_icon, NULL, LV_ALIGN_IN_RIGHT_MID, -6, 0);

    /* ---------- CONTENT (85%) ---------- */
    lv_obj_t *content = lv_cont_create(scr, NULL);
    lv_obj_set_size(content, 240, 240 * 0.90);
    lv_obj_align(content, header, LV_ALIGN_OUT_BOTTOM_MID, 0, 0);
    lv_cont_set_layout(content, LV_LAYOUT_OFF);
    remove_container_border(content);

    /* ---------- TIME LABEL (LARGE) ---------- */
    time_label = lv_label_create(content, NULL);
    lv_label_set_text(time_label, "12:34");
    lv_obj_align(time_label, NULL, LV_ALIGN_CENTER, 0, -20);

    lv_obj_set_style_local_text_font(
        time_label,
        LV_LABEL_PART_MAIN,
        LV_STATE_DEFAULT,
        &lv_font_montserrat_48);

    /* ---------- DATE LABEL (SMALL) ---------- */
    date_label = lv_label_create(content, NULL);
    lv_label_set_text(date_label, "2026-01-01");
    lv_obj_align(date_label, time_label, LV_ALIGN_OUT_BOTTOM_MID, 0, 0);

    lv_obj_set_style_local_text_font(
        date_label,
        LV_LABEL_PART_MAIN,
        LV_STATE_DEFAULT,
        &lv_font_montserrat_16);

    /* ---------- POWER OFF BUTTON (BOTTOM-LEFT) ---------- */
    power_btn = lv_btn_create(content, NULL);
    lv_obj_set_size(power_btn, 36, 36);
    lv_obj_align(power_btn, NULL, LV_ALIGN_IN_BOTTOM_LEFT, 6, -6);

    /* Remove button border */
    lv_obj_set_style_local_border_width(
        power_btn, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, 0);
    lv_obj_set_style_local_border_width(
        power_btn, LV_BTN_PART_MAIN, LV_STATE_PRESSED, 0);

    /* Optional: subtle background */
    lv_obj_set_style_local_bg_opa(
        power_btn, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, LV_OPA_40);

    /* Button label (power symbol) */
    lv_obj_t *power_label = lv_label_create(power_btn, NULL);
    lv_label_set_text(power_label, LV_SYMBOL_POWER);
    lv_obj_align(power_label, NULL, LV_ALIGN_CENTER, 0, 0);
    /* Red border */
    lv_obj_set_style_local_border_width(
        power_btn, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, 2);
    lv_obj_set_style_local_border_color(
        power_btn, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_RED);

    /* Keep border on press (no LVGL default highlight) */
    lv_obj_set_style_local_border_width(
        power_btn, LV_BTN_PART_MAIN, LV_STATE_PRESSED, 2);
    lv_obj_set_style_local_border_color(
        power_btn, LV_BTN_PART_MAIN, LV_STATE_PRESSED, LV_COLOR_RED);

    /* Click handler */
    lv_obj_set_event_cb(power_btn, power_btn_event_cb);
};

// Call this periodically to update time & date
void update_time_date_watch(const char *time_str, const char *date_str)
{
    lv_label_set_text(time_label, time_str);
    lv_label_set_text(date_label, date_str);
}

void set_battery_level(uint8_t percent)
{
#ifdef DEBUG
    Serial.printf("Battery level: %d%%\n", percent);
#endif
    if (percent > 80)
        lv_label_set_text(battery_icon, LV_SYMBOL_BATTERY_FULL);
    else if (percent > 60)
        lv_label_set_text(battery_icon, LV_SYMBOL_BATTERY_3);
    else if (percent > 40)
        lv_label_set_text(battery_icon, LV_SYMBOL_BATTERY_2);
    else if (percent > 20)
        lv_label_set_text(battery_icon, LV_SYMBOL_BATTERY_1);
    else
        lv_label_set_text(battery_icon, LV_SYMBOL_BATTERY_EMPTY);
}

void set_wifi_connected(bool connected)
{
    lv_label_set_text(
        wifi_icon,
        connected ? LV_SYMBOL_WIFI : LV_SYMBOL_CLOSE);
}

// Enter deep sleep on content click (for testing)
static void power_btn_event_cb(lv_obj_t *obj, lv_event_t event)
{
    if (event == LV_EVENT_CLICKED)
    {
#ifdef DEBUG
        Serial.println("Power button clicked");
#endif

        ttgo->shake();
        ttgo->enableTouchIRQ();

        esp_sleep_enable_ext0_wakeup(GPIO_NUM_38, 0); // Power button GPIO
        enter_deep_sleep();
    }
}

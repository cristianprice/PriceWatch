#include "price_watch.h"

static lv_obj_t *time_label;
static lv_obj_t *date_label;

LV_FONT_DECLARE(lv_font_montserrat_48);
LV_FONT_DECLARE(lv_font_montserrat_16);

void create_main_screen()
{
    lv_obj_t *scr = lv_obj_create(NULL, NULL);
    lv_scr_load(scr);

    /* ---------- HEADER (15%) ---------- */
    lv_obj_t *header = lv_cont_create(scr, NULL);
    lv_obj_set_size(header, 240, 36); // 15% of 240
    lv_obj_align(header, NULL, LV_ALIGN_IN_TOP_MID, 0, 0);
    lv_cont_set_layout(header, LV_LAYOUT_OFF);

    /* ---------- CONTENT (85%) ---------- */
    lv_obj_t *content = lv_cont_create(scr, NULL);
    lv_obj_set_size(content, 240, 204);
    lv_obj_align(content, header, LV_ALIGN_OUT_BOTTOM_MID, 0, 0);
    lv_cont_set_layout(content, LV_LAYOUT_OFF);

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
};

// Call this periodically to update time & date
void update_time_date_watch(const char *time_str, const char *date_str)
{
    lv_label_set_text(time_label, time_str);
    lv_label_set_text(date_label, date_str);
}

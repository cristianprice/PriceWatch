#include "price_watch.h"

/* Font declaration */
LV_FONT_DECLARE(lv_font_montserrat_14);

/* Styles */
static lv_style_t style_arc_bg;
static lv_style_t style_arc_indic;
static lv_style_t style_arc_label;
static lv_style_t style_knob;

/* ---------- Main screen creation ---------- */

void create_main_screen_watch(lv_obj_t *parent)
{
    LV_UNUSED(parent);

    lv_obj_t *scr = lv_scr_act();

    lv_coord_t sw = lv_obj_get_width(scr);
    lv_coord_t sh = lv_obj_get_height(scr);

    const lv_coord_t arc_spacing = 5;
    const lv_coord_t arc_size = (sw / 3) - (arc_spacing * 2);

    lv_coord_t total_width = (3 * arc_size) + (2 * arc_spacing);
    lv_coord_t start_x = (sw - total_width) / 2;
    lv_coord_t y_pos = (sh - arc_size) / 2;

    /* ---------- Initialize styles ---------- */

    /* Background arc */
    lv_style_init(&style_arc_bg);
    lv_style_set_line_width(&style_arc_bg, LV_STATE_DEFAULT, 6);
    lv_style_set_line_color(&style_arc_bg, LV_STATE_DEFAULT, LV_COLOR_WHITE);

    /* Indicator arc (slim blue) */
    lv_style_init(&style_arc_indic);
    lv_style_set_line_width(&style_arc_indic, LV_STATE_DEFAULT, 4);
    lv_style_set_line_color(&style_arc_indic, LV_STATE_DEFAULT, LV_COLOR_RED);
    lv_style_set_line_rounded(&style_arc_indic, LV_STATE_DEFAULT, true);

    /* Label inside arc */
    lv_style_init(&style_arc_label);
    lv_style_set_text_font(&style_arc_label, LV_STATE_DEFAULT, &lv_font_montserrat_28);
    lv_style_set_text_color(&style_arc_label, LV_STATE_DEFAULT, LV_COLOR_RED);

    /* Knob hidden */
    lv_style_init(&style_knob);
    lv_style_set_bg_opa(&style_knob, LV_STATE_DEFAULT, LV_OPA_TRANSP);
    lv_style_set_border_width(&style_knob, LV_STATE_DEFAULT, 0);
    lv_style_set_pad_all(&style_knob, LV_STATE_DEFAULT, 0);

    /* ---------- Create arcs ---------- */

    for (uint8_t i = 0; i < 3; i++)
    {
        lv_obj_t *arc = lv_arc_create(scr, NULL);

        lv_obj_set_size(arc, arc_size, arc_size);
        lv_obj_set_pos(
            arc,
            start_x + i * (arc_size + arc_spacing),
            y_pos);

        lv_arc_set_bg_angles(arc, 0, 360);
        lv_arc_set_angles(arc, 0, 270);
        lv_arc_set_value(arc, 0);

        /* Apply styles */
        lv_obj_add_style(arc, LV_ARC_PART_BG, &style_arc_bg);
        lv_obj_add_style(arc, LV_ARC_PART_INDIC, &style_arc_indic);
        lv_obj_add_style(arc, LV_ARC_PART_KNOB, &style_knob);

        /* Label inside arc */
        lv_obj_t *label = lv_label_create(arc, NULL);
        lv_label_set_text(label, "00");
        lv_style_set_text_font(&style_arc_label, LV_STATE_DEFAULT, &lv_font_montserrat_14);
        lv_obj_add_style(label, LV_LABEL_PART_MAIN, &style_arc_label);
        lv_obj_align(label, arc, LV_ALIGN_CENTER, 0, 0);

        /* Target values per arc */
        uint8_t value;
        if (i == 0)
            value = 25;
        else if (i == 1)
            value = 60;
        else
            value = 90;

        /* Update label */
        char buf[5];
        lv_snprintf(buf, sizeof(buf), "%02d", value);
        lv_label_set_text(label, buf);
    }
}
